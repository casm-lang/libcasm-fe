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

#include "../Logger.h"
#include "../ast/RecursiveVisitor.h"

#include "../casm-ir/src/Builtin.h"

using namespace libcasm_fe;
using namespace Ast;

char SymbolResolverPass::id = 0;

static libpass::PassRegistration< SymbolResolverPass > PASS(
    "ASTSymbolResolverPass",
    "resolves all AST identifiers and creates a symbol table", "ast-symtbl",
    0 );

class SymbolResolverVisitor final : public RecursiveVisitor
{
  public:
    SymbolResolverVisitor( Logger& log );

    u64 errors( void ) const;

    void visit( Specification& node ) override;

    void visit( FunctionDefinition& node ) override;
    void visit( DerivedDefinition& node ) override;
    void visit( RuleDefinition& node ) override;
    void visit( EnumerationDefinition& node ) override;

    void visit( DirectCallExpression& node ) override;

    void visit( UniversalQuantifierExpression& node ) override;
    void visit( ExistentialQuantifierExpression& node ) override;

    void visit( LetRule& node ) override;
    void visit( ForallRule& node ) override;

  private:
    void registerSymbol(
        const IdentifierNode& node, CallExpression::TargetType targetType );

    void unregisterSymbol( const IdentifierNode& node );

    Logger& log;

    u64 err;

    std::unordered_map< std::string, CallExpression::TargetType > m_symbolTable;

    std::unordered_map< std::string, DirectCallExpression* > m_late_resolve;
};

SymbolResolverVisitor::SymbolResolverVisitor( Logger& log )
: log( log )
, err( 0 )
{
}

void SymbolResolverVisitor::visit( Specification& node )
{
    RecursiveVisitor::visit( node );

    log.debug( "symbol_table:" );
    for( const auto& v : m_symbolTable )
    {
        const auto& identifier = v.first;
        const auto targetType = v.second;

        log.debug( "    '" + identifier + "' --> "
                   + CallExpression::targetTypeString( targetType ) );
    }

    for( const auto& v : m_late_resolve )
    {
        const auto& identifier = v.first;
        const auto node = v.second;

        auto result = m_symbolTable.find( identifier );
        if( result != m_symbolTable.end() )
        {
            node->setTargetType( result->second );
        }
        else
        {
            err++;
            log.error( { node->sourceLocation() },
                "symbol '" + identifier + "' cannot be resolved" );
        }
    }
}

void SymbolResolverVisitor::visit( FunctionDefinition& node )
{
    registerSymbol( *node.identifier(), CallExpression::TargetType::FUNCTION );
    RecursiveVisitor::visit( node );
}

void SymbolResolverVisitor::visit( DerivedDefinition& node )
{
    registerSymbol( *node.identifier(), CallExpression::TargetType::DERIVED );

    for( auto e : *node.arguments() )
    {
        registerSymbol(
            *e->identifier(), CallExpression::TargetType::VARIABLE );
    }

    RecursiveVisitor::visit( node );

    for( auto e : *node.arguments() )
    {
        unregisterSymbol( *e->identifier() );
    }
}

void SymbolResolverVisitor::visit( RuleDefinition& node )
{
    registerSymbol( *node.identifier(), CallExpression::TargetType::RULE );

    for( auto e : *node.arguments() )
    {
        registerSymbol(
            *e->identifier(), CallExpression::TargetType::VARIABLE );
    }

    RecursiveVisitor::visit( node );

    for( auto e : *node.arguments() )
    {
        unregisterSymbol( *e->identifier() );
    }
}

void SymbolResolverVisitor::visit( EnumerationDefinition& node )
{
    registerSymbol(
        *node.identifier(), CallExpression::TargetType::ENUMERATION );

    for( auto e : *node.enumerators() )
    {
        registerSymbol( *e, CallExpression::TargetType::ENUMERATION );
    }

    RecursiveVisitor::visit( node );
}

void SymbolResolverVisitor::visit( DirectCallExpression& node )
{
    const auto identifier = node.identifier()->identifier();

    auto result = m_symbolTable.find( identifier );
    if( result != m_symbolTable.end() )
    {
        node.setTargetType( result->second );
    }
    else
    {
        if( libcasm_ir::Builtin::available(
                identifier, node.arguments()->size() ) )
        {
            registerSymbol(
                *node.identifier(), CallExpression::TargetType::BUILTIN );
            node.setTargetType( CallExpression::TargetType::BUILTIN );
        }
        else
        {
            log.debug( "memorize '" + identifier + "'" );
            m_late_resolve.emplace( identifier, &node );
        }
    }

    log.debug( "Call: " + identifier + "{ " + node.targetTypeName() + " }" );

    RecursiveVisitor::visit( node );
}

void SymbolResolverVisitor::visit( UniversalQuantifierExpression& node )
{
    const auto& id = *node.predicateVariable()->identifier();

    registerSymbol( id, CallExpression::TargetType::VARIABLE );
    RecursiveVisitor::visit( node );
    unregisterSymbol( id );
}

void SymbolResolverVisitor::visit( ExistentialQuantifierExpression& node )
{
    const auto& id = *node.predicateVariable()->identifier();

    registerSymbol( id, CallExpression::TargetType::VARIABLE );
    RecursiveVisitor::visit( node );
    unregisterSymbol( id );
}

void SymbolResolverVisitor::visit( LetRule& node )
{
    const auto& id = *node.variable()->identifier();

    registerSymbol( id, CallExpression::TargetType::VARIABLE );
    RecursiveVisitor::visit( node );
    unregisterSymbol( id );
}

void SymbolResolverVisitor::visit( ForallRule& node )
{
    const auto& id = *node.variable()->identifier();

    registerSymbol( id, CallExpression::TargetType::VARIABLE );
    RecursiveVisitor::visit( node );
    unregisterSymbol( id );
}

void SymbolResolverVisitor::registerSymbol(
    const IdentifierNode& node, CallExpression::TargetType targetType )
{
    const auto identifier = node.identifier();

    auto result = m_symbolTable.emplace( identifier, targetType );

    if( not result.second )
    {
        err++;
        log.error( { node.sourceLocation() },
            "symbol '" + result.first->first + "' already defined as '"
                + CallExpression::targetTypeString( result.first->second )
                + "'" );
    }

    log.debug( "registered new symbol '" + result.first->first + "' as '"
               + CallExpression::targetTypeString( result.first->second )
               + "'" );
}

void SymbolResolverVisitor::unregisterSymbol( const IdentifierNode& node )
{
    const auto identifier = node.identifier();

    if( m_symbolTable.erase( identifier ) != 1 )
    {
        throw std::domain_error(
            "symbol '" + identifier + "' was erased more than once" );
    }

    log.debug( "unregistered symbol '" + identifier + "'" );
}

u64 SymbolResolverVisitor::errors( void ) const
{
    return err;
}

void SymbolResolverPass::usage( libpass::PassUsage& pu )
{
    pu.require< AttributionPass >();
}

u1 SymbolResolverPass::run( libpass::PassResult& pr )
{
    Logger log( &id, stream() );

    const auto data = pr.result< AttributionPass >();
    const auto specification = data->specification();

    SymbolResolverVisitor visitor( log );
    specification->accept( visitor );

    if( visitor.errors() )
    {
        log.debug( "%lu error(s)", visitor.errors() );
        return false;
    }

    pr.setResult< SymbolResolverPass >(
        libstdhl::make< Data >( specification ) );

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
