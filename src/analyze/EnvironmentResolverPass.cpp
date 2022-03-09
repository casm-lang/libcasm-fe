//
//  Copyright (C) 2014-2021 CASM Organization <https://casm-lang.org>
//  All rights reserved.
//
//  Developed by: Philipp Paulweber
//                Emmanuel Pescosta
//                Jakob Moosbrugger
//                Florian Hahn
//                Ioan Molnar
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

#include "EnvironmentResolverPass.h"

#include <libcasm-fe/Specification>
#include <libcasm-fe/TypeInfo>
#include <libcasm-fe/analyze/ProjectResolverPass>
#include <libcasm-fe/analyze/SymbolResolverPass>
#include <libcasm-fe/analyze/TypeCheckPass>
#include <libcasm-fe/analyze/TypeInferencePass>
#include <libcasm-fe/ast/Declaration>
#include <libcasm-fe/ast/Definition>
#include <libcasm-fe/ast/Literal>
#include <libcasm-fe/import/SpecificationMergerPass>

#include <libcasm-ir/Constant>

#include <libpass/PassRegistry>
#include <libpass/PassResult>
#include <libpass/PassUsage>

#include <libstdhl/Memory>
#include <libstdhl/String>

using namespace libcasm_fe;
using namespace AST;

char EnvironmentResolverPass::id = 0;

static libpass::PassRegistration< EnvironmentResolverPass > PASS(
    "Environment Resolver Pass", "TBA", "ast-env-res", 0 );

//
//
// EnvironmentResolverVisitor
//

namespace libcasm_fe
{
    namespace AST
    {
        class EnvironmentResolverVisitor final : public RecursiveVisitor
        {
          public:
            EnvironmentResolverVisitor(
                libcasm_fe::Logger& log, Namespace& symboltable, Configuration& configuration );

            void visit( Root& node ) override;
            void visit( FunctionDefinition& node ) override;

            // private:
            //   void registerSymbol( Definition& node );

          private:
            libcasm_fe::Logger& m_log;
            Namespace& m_symboltable;
            Configuration& m_configuration;
            std::unordered_map< Definition::Ptr, std::pair< std::string, std::string > >
                m_definitionToValue;
        };
    }
}

EnvironmentResolverVisitor::EnvironmentResolverVisitor(
    libcasm_fe::Logger& log, Namespace& symboltable, Configuration& configuration )
: m_log( log )
, m_configuration( configuration )
, m_symboltable( symboltable )
, m_definitionToValue()
{
}

void EnvironmentResolverVisitor::visit( Root& node )
{
    const auto& inFunctions = m_configuration.inFunctions();
    for( auto&& entry : inFunctions )
    {
        const auto& location = entry.first;
        const auto& value = entry.second;

        const auto& identifierPath = IdentifierPath::fromString( node.sourceLocation(), location );
        const auto& symbol = m_symboltable.findSymbol( *identifierPath );
        const auto definition = symbol.first;
        const auto accessible = symbol.second;

        if( not definition )
        {
            m_log.error(
                "environment 'in' function '" + location +
                "' is not defined in the scope of specification '" + m_configuration.fileName() +
                "'" );
            continue;
        }

        if( definition->id() != Node::ID::FUNCTION_DEFINITION )
        {
            m_log.error(
                "environment 'in' function '" + location +
                "' is not a function definition, it is a " + definition->description() );
            continue;
        }

        if( not accessible )
        {
            m_log.error(
                "environment 'in' function '" + location +
                "' is not accessible by specification '" + m_configuration.fileName() + "'" );
            continue;
        }

        m_definitionToValue.emplace( definition, entry );
    }

    const auto& outFunctions = m_configuration.outFunctions();
    for( auto&& entry : outFunctions )
    {
        const auto& location = entry.first;
        const auto& value = entry.second;

        const auto& identifierPath = IdentifierPath::fromString( node.sourceLocation(), location );
        const auto& symbol = m_symboltable.findSymbol( *identifierPath );
        const auto definition = symbol.first;
        const auto accessible = symbol.second;

        if( not definition )
        {
            m_log.error(
                "environment 'out' function '" + location +
                "' is not defined in the scope of specification '" + m_configuration.fileName() +
                "'" );
            continue;
        }

        if( definition->id() != Node::ID::FUNCTION_DEFINITION )
        {
            m_log.error(
                "environment 'out' function '" + location +
                "' is not a function definition, it is a " + definition->description() );
            continue;
        }

        if( not accessible )
        {
            m_log.error(
                "environment 'out' function '" + location +
                "' is not accessible by specification '" + m_configuration.fileName() + "'" );
            continue;
        }

        m_definitionToValue.emplace( definition, entry );
    }

    RecursiveVisitor::visit( node );
}

void EnvironmentResolverVisitor::visit( FunctionDefinition& node )
{
    if( node.classification() == FunctionDefinition::Classification::IN )
    {
        const auto& identifier = node.identifier();
        const auto& sourceLocation = identifier->sourceLocation();
        const auto& identifierName = identifier->name();

        const auto& result = m_definitionToValue.find( node.ptr< Definition >() );
        if( result == m_definitionToValue.end() )
        {
            m_log.info(
                { node.sourceLocation() },
                "environment 'in' function '" + identifierName +
                    "' remains 'undef', since no input value was provided" );
            return;
        }

        const auto& entry = result->second;
        const auto& location = entry.first;
        const auto& value = entry.second;

        m_log.debug(
            { node.sourceLocation() },
            "environment 'in' function '" + node.identifier()->name() + "' := '" + value + "'" );

        const auto& type = node.type();
        const auto& resultType = type->result();
        const auto& argumentTypes = type->arguments();

        libcasm_ir::Constant::Ptr valueConstant = nullptr;

        if( argumentTypes.size() == 0 )
        {
            try
            {
                if( resultType.isString() )
                {
                    if( libstdhl::String::startsWith( value, "\"" ) and
                        libstdhl::String::endsWith( value, "\"" ) )
                    {
                        valueConstant = libstdhl::Memory::get< libcasm_ir::StringConstant >(
                            value.substr( 1, value.size() - 2 ) );
                    }
                    else
                    {
                        throw std::domain_error( "invalid String literal" );
                    }
                }
                else if( resultType.isInteger() )
                {
                    valueConstant = libstdhl::Memory::get< libcasm_ir::IntegerConstant >( value );
                }
                else if( resultType.isBoolean() )
                {
                    valueConstant = libstdhl::Memory::get< libcasm_ir::BooleanConstant >( value );
                }
            }
            catch( const std::domain_error& e )
            {
                m_log.error(
                    { node.sourceLocation() },
                    "invalid value '" + value + "' for result type '" + resultType.description() +
                        "' provided for environment 'in' function '" + node.identifier()->name() +
                        "'" );
                m_log.debug( { node.sourceLocation() }, e.what() );
                return;
            }
        }

        if( not valueConstant )
        {
            m_log.error(
                { node.sourceLocation() },
                "environment 'in' function '" + location + "' is using an unsupported type" +
                    node.typeDescription() );
            return;
        }

        const auto& arguments = AST::make< Expressions >( sourceLocation );

        const auto& locationCall = AST::make< DirectCallExpression >(
            sourceLocation, AST::IdentifierPath::fromIdentifier( identifier ), arguments );

        const auto& valueLiteral = AST::make< ValueLiteral >( sourceLocation, valueConstant );

        const auto& updateRule =
            AST::make< UpdateRule >( sourceLocation, locationCall, valueLiteral );

        static_cast< const AST::SequenceRule& >( *node.initiallyRule() ).rules()->add( updateRule );

        auto& astNode = *updateRule;
        SymbolResolverPass::visit( astNode, m_log, m_symboltable );
        TypeCheckPass::visit( astNode, m_log, m_symboltable );
        TypeInferencePass::visit( astNode, m_log, m_symboltable );
        return;
    }

    if( node.classification() == FunctionDefinition::Classification::OUT )
    {
        const auto& identifier = node.identifier();
        const auto& sourceLocation = identifier->sourceLocation();
        const auto& identifierName = identifier->name();

        const auto& result = m_definitionToValue.find( node.ptr< Definition >() );
        if( result == m_definitionToValue.end() )
        {
            m_log.info(
                { node.sourceLocation() },
                "environment 'out' function '" + identifierName +
                    "' remains hidden, since no output protocol was provided" );
            return;
        }

        const auto& entry = result->second;
        const auto& location = entry.first;
        const auto& value = entry.second;

        m_log.debug(
            { node.sourceLocation() },
            "environment 'out' function '" + node.identifier()->name() + "' := '" + value + "'" );

        const auto& type = node.type();
        const auto& resultType = type->result();
        const auto& argumentTypes = type->arguments();

        libcasm_ir::Constant::Ptr valueConstant = nullptr;

        if( argumentTypes.size() != 0 )
        {
            m_log.error(
                { node.sourceLocation() },
                "environment 'out' function '" + location + "' is using an unsupported type" +
                    node.typeDescription() );
            return;
        }

        const auto& lookupArgs = AST::make< Expressions >( sourceLocation );
        const auto& lookupCall = AST::make< DirectCallExpression >(
            sourceLocation,
            AST::IdentifierPath::fromString( sourceLocation, location ),
            lookupArgs );

        const auto& stringType = AST::make< BasicType >(
            sourceLocation, AST::IdentifierPath::fromString( sourceLocation, "String" ) );
        const auto& typeCast =
            AST::make< TypeCastingExpression >( sourceLocation, lookupCall, stringType );

        const auto& printlnArgs = AST::make< Expressions >( sourceLocation );
        printlnArgs->add( typeCast );
        const auto& printlnCall = AST::make< DirectCallExpression >(
            sourceLocation,
            AST::IdentifierPath::fromString( sourceLocation, "println" ),
            printlnArgs );

        const auto& callRule = AST::make< CallRule >( sourceLocation, printlnCall );

        auto& astNode = *callRule;
        SymbolResolverPass::visit( astNode, m_log, m_symboltable );
        TypeCheckPass::visit( astNode, m_log, m_symboltable );
        TypeInferencePass::visit( astNode, m_log, m_symboltable );

        static_cast< const AST::SequenceRule& >( *node.epilogRule() ).rules()->add( callRule );
    }
}

//
//
// EnvironmentResolverPass
//

void EnvironmentResolverPass::usage( libpass::PassUsage& pu )
{
    pu.require< SpecificationMergerPass >();
    pu.require< ProjectResolverPass >();
    pu.scheduleAfter< TypeInferencePass >();
}

u1 EnvironmentResolverPass::run( libpass::PassResult& pr )
{
    libcasm_fe::Logger log( &id, stream() );

    const auto& data = pr.output< SpecificationMergerPass >();
    const auto& specification = data->specification();
    auto& symboltable = *specification->symboltable();

    const auto& projectResolver = pr.output< ProjectResolverPass >();
    const auto& project = projectResolver->project();
    const auto& configuration = project->configuration();

    EnvironmentResolverVisitor visitor( log, symboltable, *configuration );
    specification->ast()->accept( visitor );

    const auto errors = log.errors();
    if( errors > 0 )
    {
        // log.debug( "symbol table =\n" + specification->symboltable()->dump() );
        log.debug( "found %lu error(s) during environment resolving", errors );
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
