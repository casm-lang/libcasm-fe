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

#include "TypeInferencePass.h"

#include "../pass/src/PassRegistry.h"
#include "../pass/src/PassResult.h"
#include "../pass/src/PassUsage.h"

#include "../Logger.h"
#include "../analyze/SymbolResolverPass.h"
#include "../ast/RecursiveVisitor.h"

#include "../casm-ir/src/Builtin.h"

using namespace libcasm_fe;
using namespace Ast;

char TypeInferencePass::id = 0;

static libpass::PassRegistration< TypeInferencePass > PASS(
    "ASTTypeInferencePass",
    "resolve all unknown types in the AST representation", "ast-check", 0 );

//
// TypeCheckVisitor
//

class TypeCheckVisitor final : public RecursiveVisitor
{
  public:
    TypeCheckVisitor( Logger& log, Namespace& symboltable );

    void visit( BasicType& node ) override;
    void visit( ComposedType& node ) override;
    void visit( FixedSizedType& node ) override;

    u64 errors( void ) const;

  private:
    Logger& m_log;
    u64 m_err;
    Namespace& m_symboltable;
};

static const std::unordered_map< std::string, libcasm_ir::Type::Ptr > basicTypes
    = {
        { "RuleRef", libstdhl::get< libcasm_ir::RuleReferenceType >() },
        { "Boolean", libstdhl::get< libcasm_ir::BooleanType >() },
        { "Integer", libstdhl::get< libcasm_ir::IntegerType >() },
        { "Bit", libstdhl::get< libcasm_ir::BitType >( 1 ) },
        { "String", libstdhl::get< libcasm_ir::StringType >() },
        { "Floating", libstdhl::get< libcasm_ir::FloatingType >() },
      };

TypeCheckVisitor::TypeCheckVisitor( Logger& log, Namespace& symboltable )
: m_log( log )
, m_err( 0 )
, m_symboltable( symboltable )
{
}

void TypeCheckVisitor::visit( BasicType& node )
{
    if( not node.type() )
    {
        const auto& name = node.name()->baseName();

        auto result = basicTypes.find( name );
        if( result != basicTypes.end() )
        {
            node.setType( result->second );
        }
        else if( name.compare( "Agent" ) == 0 )
        {
            m_log.debug( "TODO: FIXME: handle 'Agent' case!" ); // TODO: PPA:
        }
        else
        {
            try
            {
                auto symbol = m_symboltable.find( node );

                assert( symbol.targetType()
                        == CallExpression::TargetType::ENUMERATION );

                auto& definition = static_cast< EnumerationDefinition& >(
                    symbol.definition() );

                if( not definition.type() )
                {
                    m_log.debug( "enum IR type not set yet" );

                    auto kind
                        = libstdhl::make< libcasm_ir::Enumeration >( name );
                    for( auto e : *definition.enumerators() )
                    {
                        kind->add( e->name() );
                    }

                    auto type
                        = libstdhl::make< libcasm_ir::EnumerationType >( kind );
                    definition.setType( type );
                }

                node.setType( definition.type() );
            }
            catch( const std::domain_error& e )
            {
                // m_err++; // TODO: enable this line!
                m_log.error( { node.sourceLocation() },
                    "unknown type '" + name + "' found" );
            }
        }
    }

    RecursiveVisitor::visit( node );
}

void TypeCheckVisitor::visit( ComposedType& node )
{
    assert( !" TODO! " ); // TODO: List, Tuple etc.
    RecursiveVisitor::visit( node );
}

void TypeCheckVisitor::visit( FixedSizedType& node )
{
    if( not node.type() )
    {
        const auto& name = node.name()->baseName();
        const auto& expr = *node.size();

        if( name.compare( "Bit" ) == 0 )
        {
            if( expr.id() == Node::ID::VALUE_ATOM and expr.type()->isInteger() )
            {
                const auto& atom = static_cast< const ValueAtom& >( expr );

                const auto value
                    = std::static_pointer_cast< libcasm_ir::IntegerConstant >(
                        atom.value() );

                auto type
                    = libstdhl::get< libcasm_ir::BitType >( value );

                node.setType( type );
            }
            else
            {
                m_log.error( { expr.sourceLocation() },
                    "unsupported expr for 'Bit' type" );
            }
        }
        else if( name.compare( "Integer" ) == 0 )
        {
            if( expr.id()
                == Node::ID::RANGE_EXPRESSION /* and TODO lhs and rhs */ )
            {
                // TODO: handle range case, check if the range is for
                //       Integer'[n..m] : n <= m
            }
            else
            {
                m_log.error( { expr.sourceLocation() },
                    "unsupported expr for 'Integer' type" );
            }
        }
        else
        {
            // m_err++;
            m_log.error( { node.sourceLocation() },
                "unknown type '" + name + "' found" );
        }
    }

    RecursiveVisitor::visit( node );
}

u64 TypeCheckVisitor::errors( void ) const
{
    return m_err;
}

//
// TypeInferenceVisitor
//

class TypeInferenceVisitor final : public RecursiveVisitor
{
  public:
    TypeInferenceVisitor( Logger& log );

    void visit( DirectCallExpression& node ) override;

    u64 errors( void ) const;

  private:
    Logger& m_log;
    u64 m_err;
};

TypeInferenceVisitor::TypeInferenceVisitor( Logger& log )
: m_log( log )
, m_err( 0 )
{
}

void TypeInferenceVisitor::visit( DirectCallExpression& node )
{
    const auto& name = node.identifier()
                           ->identifiers()
                           ->back()
                           ->name(); // TODO: PPA:; change this to new
                                     // path() method from IdentifierPath

    const auto arity = node.arguments()->size();

    m_log.debug( "call: " + name + "{ " + node.targetTypeName() + " } arity="
                 + std::to_string( arity ) );

    if( node.targetType() == CallExpression::TargetType::BUILTIN )
    {
        m_log.debug( "builtin: " );

        const auto& annotation = libcasm_ir::Annotation::find( name );
    }

    RecursiveVisitor::visit( node );
}

u64 TypeInferenceVisitor::errors( void ) const
{
    return m_err;
}

//
// TypeInferencePass
//

void TypeInferencePass::usage( libpass::PassUsage& pu )
{
    pu.require< SymbolResolverPass >();
}

u1 TypeInferencePass::run( libpass::PassResult& pr )
{
    Logger log( &id, stream() );

    const auto data = pr.result< SymbolResolverPass >();
    const auto specification = data->specification();
    const auto symboltable = data->symboltable();

    TypeCheckVisitor typChkVisitor( log, *symboltable );
    specification->accept( typChkVisitor );

    const auto typChkErr = typChkVisitor.errors();
    if( typChkErr )
    {
        log.debug( "found %lu error(s) during type checking", typChkErr );
        return false;
    }

    TypeInferenceVisitor visitor( log );
    specification->accept( visitor );

    const auto errors = visitor.errors();
    if( errors )
    {
        log.debug( "found %lu error(s) during type inference", errors );
        return false;
    }

    pr.setResult< TypeInferencePass >(
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
