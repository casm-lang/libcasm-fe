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
    SymbolResolverVisitor( libstdhl::Logger& log );

    void visit( Specification& node ) override;

    // void visit( VariableDefinition& node ) override;
    void visit( FunctionDefinition& node ) override;
    void visit( DerivedDefinition& node ) override;
    void visit( RuleDefinition& node ) override;
    void visit( EnumerationDefinition& node ) override;

    void visit( DirectCallExpression& node ) override;

    void registerSymbol(
        const std::string& identifier, CallExpression::TargetType targetType );

    u64 errors( void ) const;

  private:
    libstdhl::Logger& m_log;
    u64 m_err;

    std::unordered_map< std::string, CallExpression::TargetType >
        m_symbol_table;

    std::unordered_map< std::string, DirectCallExpression* > m_late_resolve;
};

SymbolResolverVisitor::SymbolResolverVisitor( libstdhl::Logger& log )
: m_log( log )
, m_err( 0 )
{
}

void SymbolResolverVisitor::visit( Specification& node )
{
    RecursiveVisitor::visit( node );

    m_log.debug( "symbol_table:" );
    for( auto v : m_symbol_table )
    {
        const auto identifier = v.first;
        const auto targetType = v.second;

        m_log.debug( "    '" + identifier + "' --> "
                     + CallExpression::targetTypeString( targetType ) );
    }

    for( auto v : m_late_resolve )
    {
        const auto identifier = v.first;
        const auto node = v.second;

        auto result = m_symbol_table.find( identifier );
        if( result != m_symbol_table.end() )
        {
            node->setTargetType( result->second );
        }
        else
        {
            m_log.error( "symbol '" + identifier + "' cannot be resolved" );
            m_err++;
        }
    }
}

// void SymbolResolverVisitor::visit( VariableDefinition& node )
// {
//     TODO: PPA:
//     RecursiveVisitor::visit( node );
// }

void SymbolResolverVisitor::visit( FunctionDefinition& node )
{
    const auto identifier = node.identifier()->identifier();
    registerSymbol( identifier, CallExpression::TargetType::FUNCTION );
    RecursiveVisitor::visit( node );
}

void SymbolResolverVisitor::visit( DerivedDefinition& node )
{
    const auto identifier = node.identifier()->identifier();
    registerSymbol( identifier, CallExpression::TargetType::DERIVED );
    RecursiveVisitor::visit( node );
}

void SymbolResolverVisitor::visit( RuleDefinition& node )
{
    const auto identifier = node.identifier()->identifier();
    registerSymbol( identifier, CallExpression::TargetType::RULE );
    RecursiveVisitor::visit( node );
}

void SymbolResolverVisitor::visit( EnumerationDefinition& node )
{
    // const auto ident = node.identifier()->identifier();
    // registerSymbol( ident, CallExpression::TargetType::ENUMERATION );
    RecursiveVisitor::visit( node );
}

void SymbolResolverVisitor::visit( DirectCallExpression& node )
{
    const auto identifier = node.identifier()->identifier();

    auto result = m_symbol_table.find( identifier );
    if( result != m_symbol_table.end() )
    {
        node.setTargetType( result->second );
    }
    else
    {
        if( libcasm_ir::Builtin::available(
                identifier, node.arguments()->size() ) )
        {
            registerSymbol( identifier, CallExpression::TargetType::BUILTIN );
            node.setTargetType( CallExpression::TargetType::BUILTIN );
        }
        else
        {
            m_log.debug( "memorize '" + identifier + "'" );
            m_late_resolve.emplace( identifier, &node );
        }
    }

    m_log.debug( "Call: " + node.identifier()->identifier() + "{ "
                 + node.targetTypeName()
                 + " }" );

    RecursiveVisitor::visit( node );
}

void SymbolResolverVisitor::registerSymbol(
    const std::string& identifier, CallExpression::TargetType targetType )
{
    auto result = m_symbol_table.emplace( identifier, targetType );

    if( not result.second )
    {
        m_log.error( "symbol '" + result.first->first + "' already defined as '"
                     + CallExpression::targetTypeString( result.first->second )
                     + "'" );
        m_err++;
    }

    m_log.debug( "registered new symbol '" + result.first->first + "' as '"
                 + CallExpression::targetTypeString( result.first->second )
                 + "'" );
}

u64 SymbolResolverVisitor::errors( void ) const
{
    return m_err;
}

void SymbolResolverPass::usage( libpass::PassUsage& pu )
{
    pu.require< AttributionPass >();
}

u1 SymbolResolverPass::run( libpass::PassResult& pr )
{
    libpass::PassLogger log( &id, stream() );

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
