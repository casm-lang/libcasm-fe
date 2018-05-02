//
//  Copyright (C) 2014-2018 CASM Organization <https://casm-lang.org>
//  All rights reserved.
//
//  Developed by: Philipp Paulweber
//                Emmanuel Pescosta
//                Florian Hahn
//                <https://github.com/casm-lang/libcasm-fe>
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
//  Additional permission under GNU GPL version 3 section 7
//
//  libcasm-fe is distributed under the terms of the GNU General Public License
//  with the following clarification and special exception: Linking libcasm-fe
//  statically or dynamically with other modules is making a combined work
//  based on libcasm-fe. Thus, the terms and conditions of the GNU General
//  Public License cover the whole combination. As a special exception,
//  the copyright holders of libcasm-fe give you permission to link libcasm-fe
//  with independent modules to produce an executable, regardless of the
//  license terms of these independent modules, and to copy and distribute
//  the resulting executable under terms of your choice, provided that you
//  also meet, for each linked independent module, the terms and conditions
//  of the license of that module. An independent module is a module which
//  is not derived from or based on libcasm-fe. If you modify libcasm-fe, you
//  may extend this exception to your version of the library, but you are
//  not obliged to do so. If you do not wish to do so, delete this exception
//  statement from your version.
//

#include "SymbolRegistrationPass.h"

#include <libcasm-fe/Logger>
#include <libcasm-fe/Namespace>
#include <libcasm-fe/Specification>
#include <libcasm-fe/TypeInfo>
#include <libcasm-fe/ast/RecursiveVisitor>

#include <libcasm-fe/analyze/AttributionPass>
#include <libcasm-fe/transform/SourceToAstPass>

#include <libcasm-ir/Builtin>

#include <libpass/PassRegistry>
#include <libpass/PassResult>
#include <libpass/PassUsage>

using namespace libcasm_fe;
using namespace Ast;

char SymbolRegistrationPass::id = 0;

static libpass::PassRegistration< SymbolRegistrationPass > PASS(
    "ASTSymbolRegistrationPass",
    "registers declared symbols in the symbol table",
    "ast-sym-reg",
    0 );

class SymbolRegistrationVisitor final : public RecursiveVisitor
{
  public:
    SymbolRegistrationVisitor( libcasm_fe::Logger& log, Namespace& symboltable );

    void visit( FunctionDefinition& node ) override;
    void visit( DerivedDefinition& node ) override;
    void visit( RuleDefinition& node ) override;
    void visit( EnumeratorDefinition& node ) override;
    void visit( EnumerationDefinition& node ) override;
    void visit( UsingDefinition& node ) override;

  private:
    void registerSymbol( const Definition& node );

  private:
    libcasm_fe::Logger& m_log;
    Namespace& m_symboltable;
};

SymbolRegistrationVisitor::SymbolRegistrationVisitor(
    libcasm_fe::Logger& log, Namespace& symboltable )
: m_log( log )
, m_symboltable( symboltable )
{
}

void SymbolRegistrationVisitor::visit( FunctionDefinition& node )
{
    registerSymbol( node );

    RecursiveVisitor::visit( node );
}

void SymbolRegistrationVisitor::visit( DerivedDefinition& node )
{
    registerSymbol( node );

    RecursiveVisitor::visit( node );
}

void SymbolRegistrationVisitor::visit( RuleDefinition& node )
{
    registerSymbol( node );

    RecursiveVisitor::visit( node );
}

void SymbolRegistrationVisitor::visit( EnumeratorDefinition& node )
{
    registerSymbol( node );
}

void SymbolRegistrationVisitor::visit( EnumerationDefinition& node )
{
    const auto& name = node.identifier()->name();
    m_log.debug( "creating IR enumeration type '" + name + "'" );
    const auto kind = std::make_shared< libcasm_ir::Enumeration >( name );
    for( const auto& enumerator : *node.enumerators() )
    {
        try
        {
            kind->add( enumerator->identifier()->name() );
        }
        catch( const std::domain_error& e )
        {
            m_log.debug( { enumerator->sourceLocation() }, e.what() );
        }
    }

    const auto type = std::make_shared< libcasm_ir::EnumerationType >( kind );
    node.setType( type );

    for( const auto& enumerator : *node.enumerators() )
    {
        enumerator->setType( type );
    }

    registerSymbol( node );

    // register enumerators in a sub-namespace
    const auto enumeratorNamespace = std::make_shared< Namespace >();
    SymbolRegistrationVisitor enumeratorVisitor( m_log, *enumeratorNamespace );
    node.enumerators()->accept( enumeratorVisitor );

    try
    {
        m_symboltable.registerNamespace( name, enumeratorNamespace );
    }
    catch( const std::domain_error& e )
    {
        m_log.debug( { node.sourceLocation() }, e.what() );
    }
}

void SymbolRegistrationVisitor::visit( UsingDefinition& node )
{
    registerSymbol( node );

    RecursiveVisitor::visit( node );
}

void SymbolRegistrationVisitor::registerSymbol( const Definition& node )
{
    const auto& name = node.identifier()->name();

    if( libcasm_ir::Builtin::available( name ) )
    {
        m_log.error(
            { node.identifier()->sourceLocation() },
            "cannot use built-in name '" + name + "' as " + node.description() + " symbol",
            Code::IdentifierIsBuiltinName );
        return;
    }

    if( TypeInfo::instance().hasType( name ) )
    {
        m_log.error(
            { node.identifier()->sourceLocation() },
            "cannot use type name '" + name + "' as " + node.description() + " symbol",
            Code::IdentifierIsTypeName );
        return;
    }

    try
    {
        m_symboltable.registerSymbol(
            name, const_cast< Definition& >( node ).ptr< Definition >() );
    }
    catch( const std::domain_error& e )
    {
        const auto& symbol = m_symboltable.findSymbol( name );
        m_log.error( { node.sourceLocation() }, e.what(), Code::IdentifierIsAlreadyUsed );
        m_log.info( { symbol->sourceLocation() }, e.what() );
    }
}

void SymbolRegistrationPass::usage( libpass::PassUsage& pu )
{
    pu.require< SourceToAstPass >();
    pu.scheduleAfter< AttributionPass >();
}

u1 SymbolRegistrationPass::run( libpass::PassResult& pr )
{
    libcasm_fe::Logger log( &id, stream() );

    const auto data = pr.output< SourceToAstPass >();
    const auto specification = data->specification();

    SymbolRegistrationVisitor visitor( log, *specification->symboltable() );
    specification->definitions()->accept( visitor );

#ifndef NDEBUG
    log.debug( "symbol table = \n" + specification->symboltable()->dump() );
#endif

    const auto errors = log.errors();
    if( errors > 0 )
    {
        log.debug( "found %lu error(s) during symbol table creation", errors );
        return false;
    }

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
