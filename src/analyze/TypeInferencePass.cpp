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

#include "../Logger.h"
#include "../Namespace.h"
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
    TypeCheckVisitor( Logger& log );

    void visit( BasicType& node ) override;
    void visit( ComposedType& node ) override;
    void visit( FixedSizedType& node ) override;
    void visit( RangedType& node ) override;

    u64 errors( void ) const;

  private:
    Logger& m_log;
    u64 m_err;
};

static const std::unordered_map< std::string, libcasm_ir::Type::Ptr > basicTypes
    = {
        { "RuleRef", libstdhl::get< libcasm_ir::RuleReferenceType >() },
        { "Boolean", libstdhl::get< libcasm_ir::BooleanType >() },
        { "Integer", libstdhl::get< libcasm_ir::IntegerType >() },
        { "Bit", libstdhl::get< libcasm_ir::BitType >( 1 ) },
        { "String", libstdhl::get< libcasm_ir::StringType >() },
        { "Floating", libstdhl::get< libcasm_ir::FloatingType >() },
        // enumeration
        // agent
      };

TypeCheckVisitor::TypeCheckVisitor( Logger& log )
: m_log( log )
, m_err( 0 )
{
}

void TypeCheckVisitor::visit( BasicType& node )
{
    if( not node.type() )
    {
        const auto& name = node.name()->identifier();

        auto result = basicTypes.find( name );
        if( result == basicTypes.end() )
        {
            m_err++;
            m_log.error( { node.sourceLocation() },
                "unknown type '" + name + "' found, expect {TODO}" );

            // TODO: it could be the agent domain type or a enumation etc.
        }
        else
        {
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
    assert( !" TODO! " ); // TODO: Bit
    RecursiveVisitor::visit( node );
}

void TypeCheckVisitor::visit( RangedType& node )
{
    assert( !" TODO! " ); // TODO Integer
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
    const auto& name = node.identifier()->identifier();
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

    TypeCheckVisitor typChkVisitor( log );
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
