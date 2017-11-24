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

#include "TypeCheckPass.h"

#include "../Logger.h"
#include "../ast/RecursiveVisitor.h"

#include <libpass/PassRegistry>
#include <libpass/PassResult>
#include <libpass/PassUsage>

#include <libstdhl/String>

using namespace libcasm_fe;
using namespace Ast;

char TypeCheckPass::id = 0;

static libpass::PassRegistration< TypeCheckPass > PASS( "ASTTypeCheckPass",
    "type check of all types in the AST representation", "ast-type-chk", 0 );

class TypeCheckVisitor final : public RecursiveVisitor
{
  public:
    TypeCheckVisitor( libcasm_fe::Logger& log, Namespace& symboltable );

    void visit( BasicType& node ) override;
    void visit( ComposedType& node ) override;
    void visit( RelationType& node ) override;
    void visit( FixedSizedType& node ) override;

  private:
    libcasm_fe::Logger& m_log;
    Namespace& m_symboltable;
};

TypeCheckVisitor::TypeCheckVisitor(
    libcasm_fe::Logger& log, Namespace& symboltable )
: m_log( log )
, m_symboltable( symboltable )
{
}

static const std::string TYPE_STRING_VOID = "Void";
static const std::string TYPE_STRING_BOOLEAN = "Boolean";
static const std::string TYPE_STRING_BIT = "Bit";
static const std::string TYPE_STRING_INTEGER = "Integer";
static const std::string TYPE_STRING_STRING = "String";
static const std::string TYPE_STRING_DECIMAL = "Decimal";
static const std::string TYPE_STRING_RATIONAL = "Rational";

static const std::string TYPE_STRING_RULEREF = "RuleRef";
static const std::string TYPE_STRING_FUNCREF = "FuncRef";

static const std::unordered_set< std::string > TYPE_STRINGS_FOR_REFERENCE_TYPES
    = { TYPE_STRING_RULEREF, TYPE_STRING_FUNCREF };

static const std::string TYPE_STRING_TUPLE = "Tuple";
static const std::string TYPE_STRING_LIST = "List";

static const std::unordered_set< std::string > TYPE_STRINGS_FOR_COMPOSED_TYPES
    = { TYPE_STRING_TUPLE, TYPE_STRING_LIST };

void TypeCheckVisitor::visit( BasicType& node )
{
    RecursiveVisitor::visit( node );

    if( node.type() )
    {
        return;
    }

    const auto& name = node.name()->path();

    if( name == TYPE_STRING_VOID )
    {
        node.setType( libstdhl::Memory::get< libcasm_ir::VoidType >() );
    }
    else if( name == TYPE_STRING_BOOLEAN )
    {
        node.setType( libstdhl::Memory::get< libcasm_ir::BooleanType >() );
    }
    else if( name == TYPE_STRING_BIT )
    {
        node.setType( libstdhl::Memory::get< libcasm_ir::BitType >( 1 ) );
    }
    else if( name == TYPE_STRING_INTEGER )
    {
        node.setType( libstdhl::Memory::get< libcasm_ir::IntegerType >() );
    }
    else if( name == TYPE_STRING_STRING )
    {
        node.setType( libstdhl::Memory::get< libcasm_ir::StringType >() );
    }
    else if( name == TYPE_STRING_DECIMAL )
    {
        node.setType( libstdhl::Memory::get< libcasm_ir::DecimalType >() );
    }
    else if( name == TYPE_STRING_RATIONAL )
    {
        node.setType( libstdhl::Memory::get< libcasm_ir::RationalType >() );
    }
    else if( TYPE_STRINGS_FOR_REFERENCE_TYPES.count( name ) )
    {
        m_log.error( { node.sourceLocation() },
            "reference type '" + name + "' defined without a relation, use '"
                + name + "< /* relation type */  >'",
            Code::TypeAnnotationRelationTypeHasNoSubType );
    }
    else if( TYPE_STRINGS_FOR_COMPOSED_TYPES.count( name ) )
    {
        m_log.error( { node.sourceLocation() },
            "composed type '" + name + "' defined without sub-types, use '"
                + name + "< /* sub-type(s) */  >'",
            Code::TypeAnnotationComposedTypeHasNoSubType );
    }
    else
    {
        try
        {
            const auto symbol = m_symboltable.find( *node.name() );

            switch( symbol->id() )
            {
                case Node::ID::ENUMERATION_DEFINITION: // [[fallthrough]]
                case Node::ID::TYPE_DEFINITION:
                {
                    break;
                }
                default:
                {
                    m_log.error( { node.sourceLocation() },
                        "cannot use " + symbol->description() + " '" + name
                            + "' as type" );
                    return;
                }
            }

            const auto& type = symbol->type();
            assert( type );
            node.setType( type );
        }
        catch( const std::domain_error& e )
        {
            m_log.error( { node.sourceLocation() },
                "unknown type '" + name + "' found",
                Code::TypeAnnotationInvalidBasicTypeName );
        }
    }
}

void TypeCheckVisitor::visit( ComposedType& node )
{
    RecursiveVisitor::visit( node );

    if( node.type() )
    {
        return;
    }

    const auto& name = node.name()->baseName();

    libcasm_ir::Types subTypeList;
    for( auto subType : *node.subTypes() )
    {
        if( not subType->type() )
        {
            m_log.info( { subType->sourceLocation() },
                "TODO: '" + name + "' has a non-typed sub type" );
            return;
        }

        subTypeList.add( subType->type() );
    }

    if( name == TYPE_STRING_TUPLE )
    {
        const auto type
            = libstdhl::Memory::make< libcasm_ir::TupleType >( subTypeList );
        node.setType( type );
    }
    else if( name == TYPE_STRING_LIST )
    {
        if( subTypeList.size() == 1 )
        {
            const auto type = libstdhl::Memory::make< libcasm_ir::ListType >(
                subTypeList[ 0 ] );
            node.setType( type );
        }
        else
        {
            m_log.error( { node.sourceLocation() },
                "composed type '" + name + "' can only have one sub-type" );
        }
    }
    else
    {
        m_log.error( { node.sourceLocation() },
            "unknown composed type '" + name + "' found",
            Code::TypeAnnotationInvalidComposedTypeName );
    }
}

void TypeCheckVisitor::visit( RelationType& node )
{
    RecursiveVisitor::visit( node );

    if( node.type() )
    {
        return;
    }

    const auto& name = node.name()->baseName();

    std::vector< libcasm_ir::Type::Ptr > argTypeList;
    for( auto argumentType : *node.argumentTypes() )
    {
        if( not argumentType->type() )
        {
            m_log.info( { argumentType->sourceLocation() },
                "TODO: '" + name + "' has a non-typed argument(s)" );
            return;
        }

        argTypeList.emplace_back( argumentType->type() );
    }

    if( name == TYPE_STRING_RULEREF )
    {
        if( node.returnType()->type() )
        {
            const auto type
                = libstdhl::Memory::make< libcasm_ir::RuleReferenceType >(
                    node.returnType()->type(), argTypeList );
            node.setType( type );
        }
    }
    else if( name == TYPE_STRING_FUNCREF )
    {
        if( node.returnType()->type() )
        {
            const auto type
                = libstdhl::Memory::make< libcasm_ir::FunctionReferenceType >(
                    node.returnType()->type(), argTypeList );
            node.setType( type );
        }
    }
    else
    {
        m_log.error( { node.sourceLocation() },
            "unknown relation type '" + name + "' found",
            Code::TypeAnnotationInvalidRelationTypeName );
    }
}

void TypeCheckVisitor::visit( FixedSizedType& node )
{
    RecursiveVisitor::visit( node );

    if( not node.type() )
    {
        const auto& name = node.name()->baseName();
        auto& expr = *node.size();

        if( name == TYPE_STRING_BIT )
        {
            if( expr.id() == Node::ID::VALUE_ATOM and expr.type()->isInteger() )
            {
                const auto& atom = static_cast< const ValueAtom& >( expr );

                const auto value
                    = std::static_pointer_cast< libcasm_ir::IntegerConstant >(
                        atom.value() );

                try
                {
                    auto type
                        = libstdhl::Memory::get< libcasm_ir::BitType >( value );
                    node.setType( type );
                }
                catch( const std::domain_error& e )
                {
                    m_log.error( { expr.sourceLocation() }, e.what(),
                        Code::TypeBitSizeIsInvalid );
                }
            }
            else
            {
                m_log.error( { expr.sourceLocation() },
                    "unsupported expr for 'Bit' type, constant Integer value "
                    "expected" );
            }
        }
        else if( name == TYPE_STRING_INTEGER )
        {
            if( expr.id() == Node::ID::RANGE_EXPRESSION )
            {
                const auto& range_expr
                    = static_cast< const RangeExpression& >( expr );

                const auto& lhs = *range_expr.left();
                const auto& rhs = *range_expr.right();

                if( lhs.id() == Node::ID::VALUE_ATOM and lhs.type()->isInteger()
                    and rhs.id() == Node::ID::VALUE_ATOM
                    and rhs.type()->isInteger() )
                {
                    const auto ir_lhs = std::static_pointer_cast<
                        libcasm_ir::IntegerConstant >(
                        static_cast< const ValueAtom& >( lhs ).value() );

                    const auto ir_rhs = std::static_pointer_cast<
                        libcasm_ir::IntegerConstant >(
                        static_cast< const ValueAtom& >( rhs ).value() );

                    auto range = libstdhl::Memory::make< libcasm_ir::Range >(
                        ir_lhs, ir_rhs );

                    auto range_type
                        = libstdhl::Memory::get< libcasm_ir::RangeType >(
                            range );

                    assert( not expr.type() );
                    expr.setType( range_type );

                    try
                    {
                        auto type
                            = libstdhl::Memory::get< libcasm_ir::IntegerType >(
                                range_type );

                        node.setType( type );
                    }
                    catch( const std::domain_error& e )
                    {
                        m_log.error( { expr.sourceLocation() }, e.what() );
                    }
                }
            }
            else
            {
                m_log.error( { expr.sourceLocation() },
                    "unsupported expr for 'Integer' type, only range "
                    "expressions are allowed, e.g. `Integer'[5..10]`" );
            }
        }
        else
        {
            m_log.error( { node.sourceLocation() },
                "unknown type '" + name + "' found",
                Code::TypeAnnotationInvalidFixedSizeTypeName );
        }
    }
}

void TypeCheckPass::usage( libpass::PassUsage& pu )
{
    pu.require< SymbolResolverPass >();
}

u1 TypeCheckPass::run( libpass::PassResult& pr )
{
    libcasm_fe::Logger log( &id, stream() );

    const auto data = pr.result< SymbolResolverPass >();
    const auto specification = data->specification();

    TypeCheckVisitor visitor( log, *specification->symboltable() );
    specification->definitions()->accept( visitor );

#ifndef NDEBUG
    log.debug( "symbol table = \n" + specification->symboltable()->dump() );
#endif

    const auto errors = log.errors();
    if( errors > 0 )
    {
        log.debug( "found %lu error(s) during type checking", errors );
        return false;
    }

    pr.setResult< TypeCheckPass >( data );

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
