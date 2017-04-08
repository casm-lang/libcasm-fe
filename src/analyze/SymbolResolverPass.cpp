//
//  Copyright (c) 2014-2017 CASM Organization
//  All rights reserved.
//
//  Developed by: Philipp Paulweber
//                Emmanuel Pescosta
//                Florian Hahn
//                https://github.com/casm-lang/libcasm-fe
//
//  This file is part of libcasm-fe.
//
//  libcasm-fe is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  libcasm-fe is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with libcasm-fe. If not, see <http://www.gnu.org/licenses/>.
//

#include "SymbolResolverPass.h"

#include "../pass/src/PassRegistry.h"
#include "../pass/src/PassResult.h"
#include "../pass/src/PassUsage.h"

#include "../Logger.h"
#include "../analyze/AttributionPass.h"
#include "../ast/RecursiveVisitor.h"

#include "../casm-ir/src/Builtin.h"

using namespace libcasm_fe;
using namespace Ast;

char SymbolResolverPass::id = 0;

static libpass::PassRegistration< SymbolResolverPass > PASS(
    "ASTSymbolResolverPass",
    "resolves all AST identifiers and creates a symbol table", "ast-symtbl",
    0 );

//
// SymbolTableVisitor
//

class SymbolTableVisitor final : public RecursiveVisitor
{
  public:
    SymbolTableVisitor( Logger& m_log );

    void visit( Specification& node ) override;

    void visit( FunctionDefinition& node ) override;
    void visit( DerivedDefinition& node ) override;
    void visit( RuleDefinition& node ) override;
    void visit( EnumerationDefinition& node ) override;

    u64 errors( void ) const;

    Namespace::Ptr symboltable( void ) const;

  private:
    Logger& m_log;
    u64 m_err;
    Namespace::Ptr m_symboltable;
};

SymbolTableVisitor::SymbolTableVisitor( Logger& log )
: m_log( log )
, m_err( 0 )
{
}

void SymbolTableVisitor::visit( Specification& node )
{
    m_symboltable = libstdhl::make< Namespace >();
    RecursiveVisitor::visit( node );
}

void SymbolTableVisitor::visit( FunctionDefinition& node )
{
    m_err += m_symboltable->registerSymbol( m_log, node );
    RecursiveVisitor::visit( node );
}

void SymbolTableVisitor::visit( DerivedDefinition& node )
{
    m_err += m_symboltable->registerSymbol( m_log, node );
    RecursiveVisitor::visit( node );
}

void SymbolTableVisitor::visit( RuleDefinition& node )
{
    m_err += m_symboltable->registerSymbol( m_log, node );
    RecursiveVisitor::visit( node );
}

void SymbolTableVisitor::visit( EnumerationDefinition& node )
{
    m_err += m_symboltable->registerSymbol( m_log, node );
    RecursiveVisitor::visit( node );
}

Namespace::Ptr SymbolTableVisitor::symboltable( void ) const
{
    return m_symboltable;
}

u64 SymbolTableVisitor::errors( void ) const
{
    return m_err;
}

//
// SymbolResolveVisitor
//

class SymbolResolveVisitor final : public RecursiveVisitor
{
  public:
    SymbolResolveVisitor( Logger& log, Namespace& symboltable );

    void visit( DirectCallExpression& node ) override;

    void visit( UniversalQuantifierExpression& node ) override;
    void visit( ExistentialQuantifierExpression& node ) override;

    void visit( LetRule& node ) override;
    void visit( ForallRule& node ) override;

    u64 errors( void ) const;

  private:
    void push( const VariableDefinition& identifier );
    void pop( const VariableDefinition& identifier );

    Logger& m_log;
    u64 m_err;
    Namespace& m_symboltable;
    std::unordered_set< std::string > m_variables;
};

SymbolResolveVisitor::SymbolResolveVisitor(
    Logger& log, Namespace& symboltable )
: m_log( log )
, m_err( 0 )
, m_symboltable( symboltable )
{
}

void SymbolResolveVisitor::visit( DirectCallExpression& node )
{
    const auto& path = *node.identifier();

    if( path.type() == IdentifierPath::Type::RELATIVE )
    {
        m_log.debug( "call: symbol '" + path.path() + "' is relative" );

        if( path.identifiers()->size() != 1 )
        {
            m_err++;
            m_log.error( { node.sourceLocation() },
                "invalid relative path '" + path.path() + "' found" );
        }
    }
    else
    {
        try
        {
            auto symbol = m_symboltable.find( node );
            node.setTargetType( symbol.targetType() );

            if( symbol.targetType() == CallExpression::TargetType::ENUMERATION
                or symbol.targetType() == CallExpression::TargetType::CONSTANT )
            {
                auto& definition = static_cast< EnumerationDefinition& >(
                    symbol.definition() );

                if( not definition.type() )
                {
                    const auto& name
                        = ( symbol.targetType()
                              == CallExpression::TargetType::CONSTANT )
                              ? path.baseDir()
                              : path.path();

                    m_log.debug(
                        "creating IR enumeration type '" + name + "'" );

                    auto kind
                        = libstdhl::make< libcasm_ir::Enumeration >( name );

                    for( auto e : *definition.enumerators() )
                    {
                        kind->add( e->identifier() );
                    }

                    const auto type
                        = libstdhl::make< libcasm_ir::EnumerationType >( kind );

                    definition.setType( type );
                }

                node.setType( definition.type() );
            }
        }
        catch( const std::domain_error& e )
        {
            const auto& name = path.baseName();

            if( libcasm_ir::Builtin::available(
                    name, node.arguments()->size() ) )
            {
                m_err += m_symboltable.registerSymbol( m_log, node );
                node.setTargetType( CallExpression::TargetType::BUILTIN );
            }
            else if( m_variables.find( name ) != m_variables.end() )
            {
                node.setTargetType( CallExpression::TargetType::VARIABLE );
            }
            else
            {
                m_err++;
                m_log.error( { node.sourceLocation() },
                    "invalid symbol '" + name + "' found" );
            }
        }

        m_log.debug(
            "call: " + path.path() + "{ " + node.targetTypeName() + " }" );
    }

    RecursiveVisitor::visit( node );
}

void SymbolResolveVisitor::visit( UniversalQuantifierExpression& node )
{
    push( *node.predicateVariable() );
    RecursiveVisitor::visit( node );
    pop( *node.predicateVariable() );
}

void SymbolResolveVisitor::visit( ExistentialQuantifierExpression& node )
{
    push( *node.predicateVariable() );
    RecursiveVisitor::visit( node );
    pop( *node.predicateVariable() );
}

void SymbolResolveVisitor::visit( LetRule& node )
{
    push( *node.variable() );
    RecursiveVisitor::visit( node );
    pop( *node.variable() );
}

void SymbolResolveVisitor::visit( ForallRule& node )
{
    push( *node.variable() );
    RecursiveVisitor::visit( node );
    pop( *node.variable() );
}

void SymbolResolveVisitor::push( const VariableDefinition& node )
{
    const auto& name = node.identifier()->identifier();

    auto result = m_variables.emplace( name );
    if( not result.second )
    {
        m_err++;
        m_log.error( { node.sourceLocation() },
            "symbol '" + name + "' already defined" );
    }
}

void SymbolResolveVisitor::pop( const VariableDefinition& node )
{
    const auto& name = node.identifier()->identifier();

    if( m_variables.erase( name ) != 1 )
    {
        assert( !" internal error! " );
    }
}

u64 SymbolResolveVisitor::errors( void ) const
{
    return m_err;
}

//
// SymbolResolverPass
//

void SymbolResolverPass::usage( libpass::PassUsage& pu )
{
    pu.require< AttributionPass >();
}

u1 SymbolResolverPass::run( libpass::PassResult& pr )
{
    Logger log( &id, stream() );

    const auto data = pr.result< AttributionPass >();
    const auto specification = data->specification();

    SymbolTableVisitor symTblVisitor( log );
    specification->accept( symTblVisitor );

    const auto symTblErr = symTblVisitor.errors();
    if( symTblErr )
    {
        log.debug(
            "found %lu error(s) during symbol table creation", symTblErr );
        return false;
    }

    SymbolResolveVisitor symResVisitor( log, *symTblVisitor.symboltable() );
    specification->accept( symResVisitor );

    const auto symResErr = symResVisitor.errors();
    if( symResErr )
    {
        log.debug( "found %lu error(s) during symbol resolving", symResErr );
        return false;
    }

#ifndef NDEBUG
    log.debug( "symbol table = \n" + symTblVisitor.symboltable()->dump() );
#endif

    pr.setResult< SymbolResolverPass >(
        libstdhl::make< Data >( specification, symTblVisitor.symboltable() ) );

    return true;
}

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
