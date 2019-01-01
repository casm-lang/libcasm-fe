//
//  Copyright (C) 2014-2019 CASM Organization <https://casm-lang.org>
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

#include "TypeCheckPass.h"

#include <libcasm-fe/Logger>
#include <libcasm-fe/Namespace>
#include <libcasm-fe/Specification>
#include <libcasm-fe/TypeInfo>
#include <libcasm-fe/ast/RecursiveVisitor>

#include <libcasm-fe/analyze/SymbolResolverPass>
#include <libcasm-fe/transform/SourceToAstPass>

#include <libpass/PassRegistry>
#include <libpass/PassResult>
#include <libpass/PassUsage>

#include <libstdhl/String>

using namespace libcasm_fe;
using namespace Ast;

char TypeCheckPass::id = 0;

static libpass::PassRegistration< TypeCheckPass > PASS(
    "ASTTypeCheckPass", "type check of all types in the AST representation", "ast-type-chk", 0 );

class TypeCheckVisitor final : public RecursiveVisitor
{
  public:
    TypeCheckVisitor( libcasm_fe::Logger& log, Namespace& symboltable );

    void visit( UsingDefinition& node ) override;

    void visit( BasicType& node ) override;
    void visit( TupleType& node ) override;
    void visit( RecordType& node ) override;
    void visit( TemplateType& node ) override;
    void visit( RelationType& node ) override;
    void visit( FixedSizedType& node ) override;

  private:
    libcasm_fe::Logger& m_log;
    Namespace& m_symboltable;
};

TypeCheckVisitor::TypeCheckVisitor( libcasm_fe::Logger& log, Namespace& symboltable )
: m_log( log )
, m_symboltable( symboltable )
{
}

void TypeCheckVisitor::visit( UsingDefinition& node )
{
    RecursiveVisitor::visit( node );
    node.setType( node.type()->type() );  // TODO top-sort using definitions
}

void TypeCheckVisitor::visit( BasicType& node )
{
    RecursiveVisitor::visit( node );

    if( node.type() )
    {
        return;
    }

    const auto& name = node.name()->path();

    if( TypeInfo::instance().isBasicType( name ) )
    {
        assert( TypeInfo::instance().hasType( name ) );
        node.setType( TypeInfo::instance().getType( name ) );
        return;
    }

    const auto symbol = m_symboltable.findSymbol( *node.name() );
    if( symbol )
    {
        switch( symbol->id() )
        {
            case Node::ID::USING_DEFINITION:  // [[fallthrough]]
            case Node::ID::ENUMERATION_DEFINITION:
            {
                break;
            }
            default:
            {
                m_log.error(
                    { node.sourceLocation() },
                    "cannot use " + symbol->description() + " '" + name + "' as type",
                    Code::TypeAnnotationInvalidBasicTypeName );
                return;
            }
        }

        const auto& type = symbol->type();
        node.setType( type );
        return;
    }

    // error handling
    if( TypeInfo::instance().isTemplateType( name ) )
    {
        m_log.error(
            { node.sourceLocation() },
            "template type '" + name + "' defined without sub-types, use '" + name +
                "< /* sub-type(s) */  >'",
            Code::TypeAnnotationTemplateTypeHasNoSubType );
    }
    else if( TypeInfo::instance().isReferenceType( name ) )
    {
        m_log.error(
            { node.sourceLocation() },
            "reference type '" + name + "' defined without a relation, use '" + name +
                "< /* relation type */  >'",
            Code::TypeAnnotationRelationTypeHasNoSubType );
    }
    else
    {
        m_log.error(
            { node.sourceLocation() },
            "unknown type '" + name + "' found",
            Code::TypeAnnotationInvalidBasicTypeName );
    }
}

void TypeCheckVisitor::visit( TupleType& node )
{
    RecursiveVisitor::visit( node );

    if( node.type() )
    {
        return;
    }

    libcasm_ir::Types subTypeList;
    for( auto subType : *node.subTypes() )
    {
        if( not subType->type() )
        {
            // early return, due to partial sub-types
            return;
        }

        subTypeList.add( subType->type() );
    }

    assert( subTypeList.size() >= 2 );  // constrain from parser

    const auto type = libstdhl::Memory::make< libcasm_ir::TupleType >( subTypeList );
    node.setType( type );
}

void TypeCheckVisitor::visit( RecordType& node )
{
    RecursiveVisitor::visit( node );

    if( node.type() )
    {
        return;
    }

    libcasm_ir::Types subTypeList;
    std::vector< std::string > recordIdentifiers;
    for( const auto& namedSubType : *node.namedSubTypes() )
    {
        if( not namedSubType->variableType()->type() )
        {
            // early return, due to partial sub-types
            return;
        }

        subTypeList.add( namedSubType->variableType()->type() );
        recordIdentifiers.emplace_back( namedSubType->identifier()->name() );
    }

    assert( subTypeList.size() >= 2 );  // constrain from parser

    const auto type =
        libstdhl::Memory::make< libcasm_ir::RecordType >( subTypeList, recordIdentifiers );
    node.setType( type );
}

void TypeCheckVisitor::visit( TemplateType& node )
{
    RecursiveVisitor::visit( node );

    if( node.type() )
    {
        return;
    }

    const auto& name = node.name()->path();

    libcasm_ir::Types subTypeList;
    for( auto subType : *node.subTypes() )
    {
        if( not subType->type() )
        {
            m_log.info(
                { subType->sourceLocation() }, "TODO: '" + name + "' has a non-typed sub-type" );
            return;
        }

        subTypeList.add( subType->type() );
    }

    if( name == TypeInfo::TYPE_NAME_RANGE )
    {
        if( subTypeList.size() == 1 )
        {
            const auto type = libstdhl::Memory::make< libcasm_ir::RangeType >( subTypeList[ 0 ] );
            node.setType( type );
        }
        else
        {
            m_log.error(
                { node.sourceLocation() },
                "template type '" + name + "' can only have one sub-type",
                Code::TypeAnnotationInvalidTemplateTypeSize );
        }
    }
    else if( name == TypeInfo::TYPE_NAME_TUPLE )
    {
        if( subTypeList.size() >= 2 )
        {
            const auto type = libstdhl::Memory::make< libcasm_ir::TupleType >( subTypeList );
            m_log.error(
                { node.sourceLocation() },
                "'" + name + "' is a built-in composed type, use syntax '" + type->description() +
                    "'",
                Code::TypeAnnotationInvalidTemplateTypeName );
        }
        else
        {
            m_log.error(
                { node.sourceLocation() },
                "'" + name + "' is a built-in composed type, use syntax '(" +
                    subTypeList[ 0 ]->description() + ", ...)'",
                Code::TypeAnnotationInvalidTemplateTypeName );
            m_log.info(
                { node.sourceLocation() },
                "'" + name + "' is a built-in composed type, and needs at least 2 sub-types" );
        }
    }
    else if( name == TypeInfo::TYPE_NAME_LIST )
    {
        if( subTypeList.size() == 1 )
        {
            const auto type = libstdhl::Memory::make< libcasm_ir::ListType >( subTypeList[ 0 ] );
            node.setType( type );
        }
        else
        {
            m_log.error(
                { node.sourceLocation() },
                "template type '" + name + "' can only have one sub-type",
                Code::TypeAnnotationInvalidTemplateTypeSize );
        }
    }
    else if( name == TypeInfo::TYPE_NAME_FILE )
    {
        if( subTypeList.size() == 1 )
        {
            m_log.info( { node.sourceLocation() }, "template type '" + name + "' is experimental" );

            const auto type = libstdhl::Memory::make< libcasm_ir::FileType >( subTypeList[ 0 ] );
            node.setType( type );
        }
        else
        {
            m_log.error(
                { node.sourceLocation() },
                "template type '" + name + "' can only have one sub-type",
                Code::TypeAnnotationInvalidTemplateTypeSize );
        }
    }
    else if( name == TypeInfo::TYPE_NAME_PORT )
    {
        if( subTypeList.size() == 1 )
        {
            m_log.info( { node.sourceLocation() }, "template type '" + name + "' is experimental" );

            const auto type = libstdhl::Memory::make< libcasm_ir::PortType >( subTypeList[ 0 ] );
            node.setType( type );
        }
        else
        {
            m_log.error(
                { node.sourceLocation() },
                "template type '" + name + "' can only have one sub-type",
                Code::TypeAnnotationInvalidTemplateTypeSize );
        }
    }
    else
    {
        m_log.error(
            { node.sourceLocation() },
            "unknown template type '" + name + "' found",
            Code::TypeAnnotationInvalidTemplateTypeName );
    }
}

void TypeCheckVisitor::visit( RelationType& node )
{
    RecursiveVisitor::visit( node );

    if( node.type() )
    {
        return;
    }

    const auto& name = node.name()->path();

    std::vector< libcasm_ir::Type::Ptr > argTypeList;
    for( auto argumentType : *node.argumentTypes() )
    {
        if( not argumentType->type() )
        {
            m_log.info(
                { argumentType->sourceLocation() },
                "TODO: '" + name + "' has a non-typed argument(s)" );
            return;
        }

        argTypeList.emplace_back( argumentType->type() );
    }

    if( name == TypeInfo::TYPE_NAME_RULEREF )
    {
        if( node.returnType()->type() )
        {
            const auto type = libstdhl::Memory::make< libcasm_ir::RuleReferenceType >(
                node.returnType()->type(), argTypeList );
            node.setType( type );
        }
    }
    else if( name == TypeInfo::TYPE_NAME_FUNCREF )
    {
        if( node.returnType()->type() )
        {
            const auto type = libstdhl::Memory::make< libcasm_ir::FunctionReferenceType >(
                node.returnType()->type(), argTypeList );
            node.setType( type );
        }
    }
    else
    {
        m_log.error(
            { node.sourceLocation() },
            "unknown relation type '" + name + "' found",
            Code::TypeAnnotationInvalidRelationTypeName );
    }
}

void TypeCheckVisitor::visit( FixedSizedType& node )
{
    RecursiveVisitor::visit( node );

    if( node.type() )
    {
        return;
    }

    const auto& name = node.name()->path();
    auto& expr = *node.size();

    if( name == TypeInfo::TYPE_NAME_BINARY )
    {
        if( not( expr.id() == Node::ID::VALUE_LITERAL and expr.type()->isInteger() ) )
        {
            m_log.error(
                { expr.sourceLocation() },
                "unsupported expr for 'Binary' type, constant Integer value "
                "expected" );
            return;
        }

        const auto& literal = static_cast< const ValueLiteral& >( expr );
        const auto value =
            std::static_pointer_cast< libcasm_ir::IntegerConstant >( literal.value() );

        try
        {
            auto type = libstdhl::Memory::get< libcasm_ir::BinaryType >( value );
            node.setType( type );
        }
        catch( const std::domain_error& e )
        {
            m_log.error( { expr.sourceLocation() }, e.what(), Code::TypeBinarySizeIsInvalid );
        }
    }
    else if( name == TypeInfo::TYPE_NAME_INTEGER )
    {
        if( expr.id() != Node::ID::RANGE_LITERAL )
        {
            m_log.error(
                { expr.sourceLocation() },
                "unsupported expr for 'Integer' type, only range "
                "expressions are allowed, e.g. `Integer'[5..10]`" );

            return;
        }

        const auto& rangeExpr = static_cast< const RangeLiteral& >( expr );

        const auto& lhs = *rangeExpr.left();
        if( not( lhs.id() == Node::ID::VALUE_LITERAL and lhs.type()->isInteger() ) )
        {
            m_log.error(
                { rangeExpr.left()->sourceLocation() },
                "unsupported expr for ranged expression, constant Integer value "
                "expected",
                Code::TypeAnnotationInvalidFixedSizeExpression );
            return;
        }

        const auto& rhs = *rangeExpr.right();
        if( not( rhs.id() == Node::ID::VALUE_LITERAL and rhs.type()->isInteger() ) )
        {
            m_log.error(
                { rangeExpr.right()->sourceLocation() },
                "unsupported expr for ranged expression, constant Integer value "
                "expected",
                Code::TypeAnnotationInvalidFixedSizeExpression );
            return;
        }

        const auto lhsValue = std::static_pointer_cast< libcasm_ir::IntegerConstant >(
            static_cast< const ValueLiteral& >( lhs ).value() );
        const auto rhsValue = std::static_pointer_cast< libcasm_ir::IntegerConstant >(
            static_cast< const ValueLiteral& >( rhs ).value() );
        auto range = libstdhl::Memory::make< libcasm_ir::Range >( lhsValue, rhsValue );

        auto rangeType = libstdhl::Memory::get< libcasm_ir::RangeType >( range );
        assert( not expr.type() );
        expr.setType( rangeType );

        try
        {
            auto type = libstdhl::Memory::get< libcasm_ir::IntegerType >( rangeType );
            node.setType( type );
        }
        catch( const std::domain_error& e )
        {
            m_log.error( { expr.sourceLocation() }, e.what() );
        }
    }
    else
    {
        m_log.error(
            { node.sourceLocation() },
            "unknown type '" + name + "' found",
            Code::TypeAnnotationInvalidFixedSizeTypeName );
    }
}

void TypeCheckPass::usage( libpass::PassUsage& pu )
{
    pu.require< SourceToAstPass >();
    pu.scheduleAfter< SymbolResolverPass >();
}

u1 TypeCheckPass::run( libpass::PassResult& pr )
{
    libcasm_fe::Logger log( &id, stream() );

    const auto data = pr.output< SourceToAstPass >();
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
