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

#include "TypeInferencePass.h"

#include <libcasm-fe/Logger>
#include <libcasm-fe/Namespace>
#include <libcasm-fe/Specification>
#include <libcasm-fe/ast/RecursiveVisitor>

#include <libcasm-fe/analyze/TypeCheckPass>
#include <libcasm-fe/transform/SourceToAstPass>

#include <libcasm-ir/Builtin>
#include <libcasm-ir/Exception>

#include <libpass/PassRegistry>
#include <libpass/PassResult>
#include <libpass/PassUsage>

#include <libstdhl/String>

using namespace libcasm_fe;
using namespace Ast;

char TypeInferencePass::id = 0;

static libpass::PassRegistration< TypeInferencePass > PASS(
    "ASTTypeInferencePass",
    "type inference of all types in the AST representation",
    "ast-infer",
    0 );

class TypeInferenceVisitor final : public RecursiveVisitor
{
  public:
    TypeInferenceVisitor( libcasm_fe::Logger& log );

    void visit( VariableDefinition& node ) override;
    void visit( FunctionDefinition& node ) override;
    void visit( DerivedDefinition& node ) override;
    void visit( RuleDefinition& node ) override;

    void visit( UndefLiteral& node ) override;
    void visit( ValueLiteral& node ) override;
    void visit( ReferenceLiteral& node ) override;
    void visit( ListLiteral& node ) override;
    void visit( RangeLiteral& node ) override;
    void visit( TupleLiteral& node ) override;
    void visit( RecordLiteral& node ) override;

    void visit( NamedExpression& node ) override;
    void visit( DirectCallExpression& node ) override;
    void visit( MethodCallExpression& node ) override;
    void visit( LiteralCallExpression& node ) override;
    void visit( IndirectCallExpression& node ) override;
    void visit( TypeCastingExpression& node ) override;
    void visit( UnaryExpression& node ) override;
    void visit( BinaryExpression& node ) override;
    void visit( LetExpression& node ) override;
    void visit( ConditionalExpression& node ) override;
    void visit( ChooseExpression& node ) override;
    void visit( UniversalQuantifierExpression& node ) override;
    void visit( ExistentialQuantifierExpression& node ) override;

    void visit( ConditionalRule& node ) override;

    void visit( CaseRule& node ) override;
    void visit( ExpressionCase& node ) override;
    void visit( DefaultCase& node ) override;

    void visit( LetRule& node ) override;
    void visit( ForallRule& node ) override;
    void visit( ChooseRule& node ) override;
    void visit( UpdateRule& node ) override;

    void assignment(
        const Node& node,
        TypedNode& lhs,
        TypedNode& rhs,
        const std::string& dst,
        const std::string& src,
        const Code& dstErr,
        const Code& srcErr,
        const Code& assignmentErr );

    const libcasm_ir::Annotation* annotate(
        Node& node, const std::vector< Expression::Ptr >& expressions = {} );

    void inference(
        const std::string& description,
        const libcasm_ir::Annotation* annotation,
        TypedNode& node,
        const std::vector< Expression::Ptr >& arguments = {} );

    void inference( QuantifierExpression& node );

  private:
    libcasm_fe::Logger& m_log;

    std::unordered_map< const Node*, std::set< libcasm_ir::Type::ID > > m_typeIDs;
};

TypeInferenceVisitor::TypeInferenceVisitor( libcasm_fe::Logger& log )
: m_log( log )
{
}

void TypeInferenceVisitor::visit( VariableDefinition& node )
{
    if( node.type() )
    {
        // may be invoked multiple times -> only type once
        return;
    }

    RecursiveVisitor::visit( node );

    if( node.variableType()->type() )
    {
        node.setType( node.variableType()->type() );
    }

    const auto description = "variable '" + node.identifier()->name() + "'";
    inference( description, nullptr, node );
}

void TypeInferenceVisitor::visit( FunctionDefinition& node )
{
    if( node.type() )
    {
        // may be invoked multiple times -> only type once
        return;
    }

    node.returnType()->accept( *this );
    assert( node.returnType()->type() && "return type must be specified" );

    node.argumentTypes()->accept( *this );
    std::vector< libcasm_ir::Type::Ptr > argTypeList;
    argTypeList.reserve( node.argumentTypes()->size() );
    for( const auto& argumentType : *node.argumentTypes() )
    {
        assert( argumentType->type() && "argument type must be specified" );
        argTypeList.emplace_back( argumentType->type() );
    }

    const auto type = libstdhl::Memory::make< libcasm_ir::RelationType >(
        node.returnType()->type(), argTypeList );
    node.setType( type );

    auto& returnType = *node.returnType()->type();
    m_typeIDs[ node.defaultValue().get() ].emplace( returnType.id() );
    node.defaultValue()->accept( *this );

    if( node.defaultValue() and node.defaultValue()->type() and
        node.defaultValue()->type() != node.returnType()->type() )
    {
        if( node.defaultValue()->type()->isInteger() == node.returnType()->type()->isInteger() )
        {
            // relaxation: mixed ranged and non-ranged integer types are allowed and checked in a
            // later pass or step!
        }
        else
        {
            m_log.error(
                { node.defaultValue()->sourceLocation(), node.returnType()->sourceLocation() },
                "type mismatch: type of default value was '" +
                    node.defaultValue()->type()->description() + "', function expects '" +
                    node.returnType()->type()->description() + "'",
                Code::TypeInferenceFunctionDefaultValueTypeMismatch );
        }
    }

    node.initializers()->accept( *this );
}

void TypeInferenceVisitor::visit( DerivedDefinition& node )
{
    if( node.type() )
    {
        // may be invoked multiple times -> only type once
        return;
    }

    node.returnType()->accept( *this );
    assert( node.returnType()->type() && "return type must be specified" );

    node.arguments()->accept( *this );
    std::vector< libcasm_ir::Type::Ptr > argTypeList;
    argTypeList.reserve( node.arguments()->size() );
    for( const auto& argument : *node.arguments() )
    {
        assert( argument->type() && "argument type must be specified" );
        argTypeList.emplace_back( argument->type() );
    }

    const auto type = libstdhl::Memory::make< libcasm_ir::RelationType >(
        node.returnType()->type(), argTypeList );
    node.setType( type );

    auto& returnType = *node.returnType()->type();
    m_typeIDs[ node.expression().get() ].emplace( returnType.id() );
    node.expression()->accept( *this );

    if( node.expression()->type() )
    {
        const auto& expTy = node.expression()->type()->result();

        if( returnType != expTy )
        {
            if( expTy.isInteger() and returnType.isInteger() )
            {
                return;
            }

            m_log.error(
                { node.expression()->sourceLocation() },
                "type mismatch: result type was '" + expTy.description() + "', derived expects '" +
                    returnType.description() + "'",
                Code::TypeInferenceDerivedReturnTypeMismatch );
        }
    }
}

void TypeInferenceVisitor::visit( RuleDefinition& node )
{
    if( node.type() )
    {
        // may be invoked multiple times -> only type once
        return;
    }

    node.returnType()->accept( *this );
    assert( node.returnType()->type() && "return type must be specified" );

    node.arguments()->accept( *this );
    std::vector< libcasm_ir::Type::Ptr > argTypeList;
    argTypeList.reserve( node.arguments()->size() );
    for( const auto& argument : *node.arguments() )
    {
        assert( argument->type() && "argument type must be specified" );
        argTypeList.emplace_back( argument->type() );
    }

    const auto type = libstdhl::Memory::make< libcasm_ir::RelationType >(
        node.returnType()->type(), argTypeList );
    node.setType( type );

    node.rule()->accept( *this );
}

void TypeInferenceVisitor::visit( UndefLiteral& node )
{
    RecursiveVisitor::visit( node );
    inference( "undef literal", nullptr, node );
}

void TypeInferenceVisitor::visit( ValueLiteral& node )
{
    assert( node.value() and node.type() );
    m_typeIDs[&node ] = { node.type()->id() };

    RecursiveVisitor::visit( node );

    inference( "value literal", nullptr, node );
}

void TypeInferenceVisitor::visit( ReferenceLiteral& node )
{
    if( node.type() )
    {
        return;
    }

    RecursiveVisitor::visit( node );
    inference( "reference literal", nullptr, node );

    switch( node.referenceType() )
    {
        case ReferenceLiteral::ReferenceType::FUNCTION:  // [[fallthrough]]
        case ReferenceLiteral::ReferenceType::DERIVED:
        {
            // make sure that the reference has been typed
            node.reference()->accept( *this );

            const auto type = libstdhl::Memory::make< libcasm_ir::FunctionReferenceType >(
                std::static_pointer_cast< libcasm_ir::RelationType >( node.reference()->type() ) );
            node.setType( type );
            break;
        }
        case ReferenceLiteral::ReferenceType::BUILTIN:
        {
            libcasm_ir::Annotation const* annotation = nullptr;
            try
            {
                annotation = &libcasm_ir::Annotation::find( node.builtinId() );
            }
            catch( const std::domain_error& e )
            {
                assert( !"reference should have been resolved" );
                return;
            }
            assert( annotation );

            if( node.type() )
            {
                // type has been inferred -> check if relation type is valid
                assert( node.type()->isReference() );
                const auto& referenceType =
                    std::static_pointer_cast< libcasm_ir::ReferenceType >( node.type() );
                const auto relationType = referenceType->dereference();

                if( not annotation->valid( *relationType ) )
                {
                    m_log.error(
                        { node.sourceLocation() },
                        "built-in '" + node.identifier()->path() + "' has no type relation '" +
                            relationType->description() + "'",
                        Code::TypeInferenceBuiltinRelationTypeInvalid );
                }
            }
            else if( annotation->relations().size() == 1 )
            {
                // only unambiguous annotations can be used for type resolving
                const auto& relation = annotation->relations().at( 0 );

                std::vector< libcasm_ir::Type::Ptr > argumentTypes;
                for( const auto& argumentId : relation.argument )
                {
                    argumentTypes.emplace_back( libcasm_ir::Type::fromID( argumentId ) );
                }

                const auto& returnType = libcasm_ir::Type::fromID( relation.result );

                const auto type = libstdhl::Memory::make< libcasm_ir::FunctionReferenceType >(
                    returnType, argumentTypes );
                node.setType( type );
            }
            break;
        }
        case ReferenceLiteral::ReferenceType::RULE:
        {
            // make sure that the reference has been typed
            node.reference()->accept( *this );

            const auto type = libstdhl::Memory::make< libcasm_ir::RuleReferenceType >(
                std::static_pointer_cast< libcasm_ir::RelationType >( node.reference()->type() ) );
            node.setType( type );
            break;
        }
        default:
        {
            assert( !" unknown reference type! " );
        }
    }
}

void TypeInferenceVisitor::visit( NamedExpression& node )
{
    RecursiveVisitor::visit( node );
    node.setType( node.expression()->type() );
}

void TypeInferenceVisitor::visit( DirectCallExpression& node )
{
    assert( node.identifier() );
    const auto identifier = node.identifier();

    switch( node.targetType() )
    {
        case CallExpression::TargetType::VARIABLE:
        {
            const auto& variable = node.targetDefinition();

            m_typeIDs[ variable.get() ] = m_typeIDs[&node ];
            variable->accept( *this );

            node.setType( variable->type() );
            break;
        }
        case CallExpression::TargetType::BUILTIN:
        {
            if( node.type() )
            {
                break;
            }

            std::vector< libcasm_ir::Type::Ptr > argTypeList;
            auto directCallArguments = node.arguments()->data();

            const auto* annotation = annotate( node, directCallArguments );
            RecursiveVisitor::visit( node );
            const auto description = "built-in '" + identifier->path() + "'";
            inference( description, annotation, node, directCallArguments );

            for( auto argumentType : *node.arguments() )
            {
                if( not argumentType->type() )
                {
                    m_log.debug(
                        { argumentType->sourceLocation() },
                        "TODO: '" + identifier->path() + "' has a non-typed argument(s)" );
                    return;
                }

                argTypeList.emplace_back( argumentType->type()->ptr_result() );
            }

            if( node.type() )
            {
                const auto type =
                    libstdhl::Memory::make< libcasm_ir::RelationType >( node.type(), argTypeList );

                node.setType( type );

                if( not annotation->valid( *type ) )
                {
                    m_log.error(
                        { node.sourceLocation() },
                        "built-in '" + identifier->path() + "' has no type relation '" +
                            type->description() + "'",
                        Code::TypeInferenceBuiltinRelationTypeInvalid );
                    return;
                }
            }

            break;
        }
        case CallExpression::TargetType::DERIVED:      // [[fallthrough]]
        case CallExpression::TargetType::FUNCTION:     // [[fallthrough]]
        case CallExpression::TargetType::RULE:         // [[fallthrough]]
        case CallExpression::TargetType::SELF:         // [[fallthrough]]
        case CallExpression::TargetType::TYPE_DOMAIN:  // [[fallthrough]]
        case CallExpression::TargetType::CONSTANT:
        {
            if( node.type() )
            {
                break;
            }

            // make sure that the definition has been typed
            const auto& definition = node.targetDefinition();
            if( not definition )
            {
                // break inference of not defined direct calls!
                break;
            }

            definition->accept( *this );

            const auto& arguments = *node.arguments();
            const auto& argumentTypes = definition->type()->arguments();
            for( std::size_t i = 0; i < arguments.size(); i++ )
            {
                m_typeIDs[ arguments.at( i ).get() ].emplace( argumentTypes.at( i )->id() );
            }

            node.setType( definition->type() );
            break;
        }
        case CallExpression::TargetType::UNKNOWN:
        {
            if( identifier->type() != IdentifierPath::Type::RELATIVE )
            {
                m_log.error( { node.sourceLocation() }, "target type 'UNKNOWN' found!" );
            }
            else
            {
                inference( "relative path", nullptr, node );
            }
            break;
        }
    }

    RecursiveVisitor::visit( node );

    if( node.type() )
    {
        const auto& call_type_args = node.type()->arguments();
        const auto& call_expr_args = *node.arguments();

        for( std::size_t pos = 0; pos < call_expr_args.size(); pos++ )
        {
            const auto& exprArg = call_expr_args.at( pos );
            if( not exprArg->type() )
            {
                continue;
            }

            const auto& callArgType = call_type_args.at( pos );
            if( callArgType->isInteger() and exprArg->type()->result().isInteger() )
            {
                continue;
            }

            if( *callArgType != exprArg->type()->result() )
            {
                const std::unordered_map< CallExpression::TargetType, Code > codes = {
                    { CallExpression::TargetType::FUNCTION,
                      Code::TypeInferenceFunctionArgumentTypeMismatch },
                    { CallExpression::TargetType::DERIVED,
                      Code::TypeInferenceDerivedArgumentTypeMismatch },
                    { CallExpression::TargetType::BUILTIN,
                      Code::TypeInferenceBuiltinArgumentTypeMismatch },
                    { CallExpression::TargetType::RULE,
                      Code::TypeInferenceRuleArgumentTypeMismatch },
                };

                const auto code = codes.find( node.targetType() );
                assert( code != codes.end() and " invalid target type with arguments " );

                m_log.error(
                    { exprArg->sourceLocation() },
                    "type mismatch: " + node.targetTypeName() + " argument type at position " +
                        std::to_string( pos + 1 ) + " was '" + exprArg->type()->description() +
                        "', " + node.targetTypeName() + " definition expects '" +
                        callArgType->description() + "'",
                    code->second );
            }
        }
    }
}

void TypeInferenceVisitor::visit( MethodCallExpression& node )
{
    const auto& methodName = node.methodName()->name();

    node.object()->accept( *this );

    if( not node.object()->type() )
    {
        // the object type is essential to resolve the method
        m_log.error(
            { node.sourceLocation() },
            "unable to resolve object type",
            Code::TypeInferenceInvalidMethodCallExpression );
        return;
    }

    // for the time being only builtin method calls are supported
    node.setMethodType( MethodCallExpression::MethodType::BUILTIN );

    std::vector< Expression::Ptr > methodCallArguments;
    methodCallArguments.reserve( 1 + node.arguments()->size() );
    methodCallArguments.emplace_back( node.object() );  // pass object instance as first argument
    methodCallArguments.insert(
        methodCallArguments.end(), node.arguments()->begin(), node.arguments()->end() );

    const auto* annotation = annotate( node, methodCallArguments );
    if( not annotation )
    {
        m_log.error(
            { node.sourceLocation() }, "unable to resolve built-in method '" + methodName + "'" );
        return;
    }

    node.setTargetBuiltinId( annotation->valueID() );

    RecursiveVisitor::visit( node );

    if( node.type() )
    {
        return;
    }

    const auto description = "built-in method '" + methodName + "'";
    inference( description, annotation, node, methodCallArguments );

    std::vector< libcasm_ir::Type::Ptr > argumentTypes;
    argumentTypes.emplace_back( node.object()->type()->ptr_result() );
    for( auto argumentType : *node.arguments() )
    {
        if( not argumentType->type() )
        {
            m_log.debug(
                { argumentType->sourceLocation() },
                "TODO: '" + methodName + "' has a non-typed argument(s)" );
            return;
        }

        argumentTypes.emplace_back( argumentType->type()->ptr_result() );
    }

    const auto type =
        libstdhl::Memory::make< libcasm_ir::RelationType >( node.type(), argumentTypes );

    if( not annotation->valid( *type ) )
    {
        m_log.error(
            { node.sourceLocation() },
            "built-in '" + methodName + "' has no type relation '" + type->description() + "'" );
        node.setType( nullptr );
    }
    else
    {
        node.setType( type );
    }
}

void TypeInferenceVisitor::visit( LiteralCallExpression& node )
{
    node.object()->accept( *this );

    const auto& objectType = node.object()->type();
    if( not objectType )
    {
        // the object type is essential to resolve the literal access
        m_log.error(
            { node.sourceLocation() },
            "unable to resolve object type",
            Code::TypeInferenceInvalidLiteralCallExpression );
        return;
    }

    node.literal()->accept( *this );

    const auto& literalType = node.literal()->type();
    if( not literalType )
    {
        m_log.error(
            { node.sourceLocation() },
            "unable to resolve literal type",
            Code::TypeInferenceInvalidLiteralCallExpression );
        return;
    }

    if( objectType->isTuple() and literalType->isInteger() )
    {
        const auto& literal = static_cast< const ValueLiteral& >( *node.literal() );
        const auto& constant =
            static_cast< const libcasm_ir::IntegerConstant& >( *literal.value() );
        const auto& value = static_cast< const libstdhl::Type::Integer& >( constant.value() );

        if( value >= 0 and value < objectType->arguments().size() )
        {
            assert( value.trivial() );

            const auto& resultType = objectType->arguments()[ value.value() ];
            std::vector< libcasm_ir::Type::Ptr > argumentTypes;
            argumentTypes.emplace_back( objectType->ptr_result() );
            argumentTypes.emplace_back( literalType->ptr_result() );

            const auto type =
                libstdhl::Memory::make< libcasm_ir::RelationType >( resultType, argumentTypes );
            node.setType( type );
        }
    }
}

void TypeInferenceVisitor::visit( IndirectCallExpression& node )
{
    RecursiveVisitor::visit( node );

    if( not node.expression()->type() )
    {
        m_log.error(
            { node.sourceLocation() }, "unable to resolve type of indirect call expression" );
    }

    node.setType( node.expression()->type() );

    assert( node.type()->isReference() );

    if( node.type()->isRuleReference() )
    {
        node.setTargetType( CallExpression::TargetType::RULE );
    }
    else if( node.type()->isFunctionReference() )
    {
        node.setTargetType( CallExpression::TargetType::FUNCTION );
    }
    else
    {
        m_log.debug(
            { node.expression()->sourceLocation() },
            "unable to set indirect call expression target type for expression "
            "kind of '" +
                node.expression()->description() + "'" );
    }

    const auto& refType = std::static_pointer_cast< libcasm_ir::ReferenceType >( node.type() );
    node.setType( refType->dereference() );
}

void TypeInferenceVisitor::visit( TypeCastingExpression& node )
{
    RecursiveVisitor::visit( node );

    if( not node.fromExpression()->type() )
    {
        m_log.error(
            { node.fromExpression()->sourceLocation() },
            "unable to infer expression type of 'as operator'",
            Code::TypeInferenceTypeCastingExpressionFromHasNoType );
    }

    if( not node.fromExpression()->type() or not node.asType()->type() )
    {
        return;
    }

    const auto resultType = node.asType()->type();
    std::vector< libcasm_ir::Type::Ptr > argumentTypes;

    const auto& fromExpressionType = node.fromExpression()->type();
    if( fromExpressionType->isRelation() )
    {
        argumentTypes.emplace_back( fromExpressionType->ptr_result() );
    }
    else
    {
        argumentTypes.emplace_back( fromExpressionType );
    }

    const auto relationType =
        libstdhl::Memory::make< libcasm_ir::RelationType >( resultType, argumentTypes );

    switch( resultType->kind() )
    {
        case libcasm_ir::Type::Kind::VOID:      // [fallthrough]
        case libcasm_ir::Type::Kind::LABEL:     // [fallthrough]
        case libcasm_ir::Type::Kind::LOCATION:  // [fallthrough]
        case libcasm_ir::Type::Kind::RELATION:
        {
            m_log.error(
                { node.asType()->sourceLocation() },
                "invalid 'as' operator type '" + resultType->description() +
                    "' to perform type casting",
                Code::TypeInferenceTypeCastingExpressionAsHasInvalidType );
            return;
        }
        case libcasm_ir::Type::Kind::BOOLEAN:
        {
            node.setCastingType( TypeCastingExpression::CastingType::BUILTIN );
            node.setTargetBuiltinId( libcasm_ir::Value::AS_BOOLEAN_BUILTIN );
            break;
        }
        case libcasm_ir::Type::Kind::INTEGER:
        {
            node.setCastingType( TypeCastingExpression::CastingType::BUILTIN );
            node.setTargetBuiltinId( libcasm_ir::Value::AS_INTEGER_BUILTIN );
            break;
        }
        case libcasm_ir::Type::Kind::RATIONAL:
        {
            node.setCastingType( TypeCastingExpression::CastingType::BUILTIN );
            node.setTargetBuiltinId( libcasm_ir::Value::AS_RATIONAL_BUILTIN );
            break;
        }
        case libcasm_ir::Type::Kind::BINARY:
        {
            node.setCastingType( TypeCastingExpression::CastingType::BUILTIN );
            node.setTargetBuiltinId( libcasm_ir::Value::AS_BINARY_BUILTIN );
            break;
        }
        case libcasm_ir::Type::Kind::DECIMAL:
        {
            node.setCastingType( TypeCastingExpression::CastingType::BUILTIN );
            node.setTargetBuiltinId( libcasm_ir::Value::AS_DECIMAL_BUILTIN );
            break;
        }
        case libcasm_ir::Type::Kind::STRING:
        {
            node.setCastingType( TypeCastingExpression::CastingType::BUILTIN );
            node.setTargetBuiltinId( libcasm_ir::Value::AS_STRING_BUILTIN );
            break;
        }
        case libcasm_ir::Type::Kind::ENUMERATION:
        {
            node.setCastingType( TypeCastingExpression::CastingType::BUILTIN );
            node.setTargetBuiltinId( libcasm_ir::Value::AS_ENUMERATION_BUILTIN );
            break;
        }
        case libcasm_ir::Type::Kind::RANGE:               // [fallthrough]
        case libcasm_ir::Type::Kind::TUPLE:               // [fallthrough]
        case libcasm_ir::Type::Kind::RECORD:              // [fallthrough]
        case libcasm_ir::Type::Kind::LIST:                // [fallthrough]
        case libcasm_ir::Type::Kind::RULE_REFERENCE:      // [fallthrough]
        case libcasm_ir::Type::Kind::FUNCTION_REFERENCE:  // [fallthrough]
        case libcasm_ir::Type::Kind::FILE:                // [fallthrough]
        case libcasm_ir::Type::Kind::PORT:
        {
            // TODO: PPA: FIXME: continue here with missing casting
            // functionality
            break;
        }
        case libcasm_ir::Type::Kind::_SIZE_:
        {
            assert( !" internal error!" );
            break;
        }
    }

    if( node.castingType() == TypeCastingExpression::CastingType::BUILTIN )
    {
        const auto& annotation = libcasm_ir::Annotation::find( node.targetBuiltinId() );

        if( not annotation.valid( *relationType ) )
        {
            m_log.error(
                { node.sourceLocation() },
                "invalid 'as operator' type casting relation '" + relationType->description() +
                    "' found'",
                Code::TypeInferenceInvalidTypeCastingExpression );
            return;
        }
    }
    else
    {
        // TODO: PPA: FIXME: implement here possible derived and feature type
        // casting expressions
        m_log.error(
            { node.sourceLocation() },
            "unknown 'as operator' type casting relation '" + relationType->description() +
                "' found",
            Code::TypeInferenceInvalidTypeCastingExpression );
        return;
    }

    node.setType( relationType );
}

void TypeInferenceVisitor::visit( UnaryExpression& node )
{
    const auto* annotation = annotate( node, { node.expression() } );

    RecursiveVisitor::visit( node );

    const auto description = "unary operator '" + libcasm_ir::Value::token( node.op() ) + "'";
    inference( description, annotation, node, { node.expression() } );

    if( node.type() and node.expression()->type() )
    {
        const std::vector< libcasm_ir::Type::Ptr > argTypeList{
            node.expression()->type()->ptr_result()
        };

        const libcasm_ir::RelationType relationType( node.type(), argTypeList );

        if( not annotation->valid( relationType ) )
        {
            m_log.error(
                { node.sourceLocation() },
                description + " has no type relation '" + relationType.description() + "'",
                Code::TypeInferenceOperatorUnaryRelationTypeInvalid );
        }
    }
}

void TypeInferenceVisitor::visit( BinaryExpression& node )
{
    const auto* annotation = annotate( node, { node.left(), node.right() } );

    RecursiveVisitor::visit( node );

    const auto description = "binary operator '" + libcasm_ir::Value::token( node.op() ) + "'";
    inference( description, annotation, node, { node.left(), node.right() } );

    if( node.type() and node.left()->type() and node.right()->type() )
    {
        const std::vector< libcasm_ir::Type::Ptr > argTypeList{
            node.left()->type()->ptr_result(), node.right()->type()->ptr_result()
        };

        const libcasm_ir::RelationType relationType( node.type(), argTypeList );

        if( not annotation->valid( relationType ) )
        {
            m_log.error(
                { node.sourceLocation() },
                description + " has no type relation '" + relationType.description() + "'",
                Code::TypeInferenceOperatorBinaryRelationTypeInvalid );
        }
    }
}

void TypeInferenceVisitor::visit( ListLiteral& node )
{
    RecursiveVisitor::visit( node );

    for( auto expression : *node.expressions() )
    {
        if( not expression->type() )
        {
            m_log.info( { expression->sourceLocation() }, "TODO: has a non-typed sub-type" );
            return;
        }
    }

    const auto& typeIDs = m_typeIDs[&node ];
    if( typeIDs.size() == 1 )
    {
        // there is a type inferred, check if the list expression types match!
        const auto typeID = *typeIDs.begin();
        const auto type = libcasm_ir::Type::fromID( typeID );

        if( type->isList() )
        {
            for( auto expression : *node.expressions() )
            {
                if( *expression->type() != type->result() )
                {
                    return;
                }
            }

            node.setType( type );
        }
    }
    else
    {
        // no type inferred, try to find one from the expression types
        libcasm_ir::Type::Ptr listInnerType = nullptr;

        for( auto expression : *node.expressions() )
        {
            if( not listInnerType )
            {
                listInnerType = expression->type();
            }

            if( *listInnerType != *expression->type() )
            {
                return;
            }
        }

        if( listInnerType )
        {
            const auto listType = libstdhl::Memory::get< libcasm_ir::ListType >( listInnerType );
            node.setType( listType );
        }
    }
}

void TypeInferenceVisitor::visit( RangeLiteral& node )
{
    RecursiveVisitor::visit( node );

    const auto& lhs = node.left()->type()->result();
    const auto& rhs = node.right()->type()->result();

    if( lhs != rhs )
    {
        m_log.error(
            { node.sourceLocation() },
            "types of range does not match, " + lhs.description() + " != " + rhs.description(),
            Code::TypeInferenceRangeLiteralTypeMismatch );
        return;
    }

    const auto range_type =
        libstdhl::Memory::get< libcasm_ir::RangeType >( node.left()->type()->ptr_result() );

    node.setType( range_type );
}

void TypeInferenceVisitor::visit( TupleLiteral& node )
{
    RecursiveVisitor::visit( node );

    assert( node.expressions()->size() >= 2 );  // constrain from parser
    libcasm_ir::Types expressionTypes;
    for( auto expression : *node.expressions() )
    {
        if( not expression->type() )
        {
            m_log.info( { expression->sourceLocation() }, "TODO: has a non-typed sub-type" );
            return;
        }

        expressionTypes.add( expression->type() );
    }

    const auto type = libstdhl::Memory::get< libcasm_ir::TupleType >( expressionTypes );
    node.setType( type );
}

void TypeInferenceVisitor::visit( RecordLiteral& node )
{
    RecursiveVisitor::visit( node );

    const auto& typeIDs = m_typeIDs[&node ];
    if( typeIDs.size() == 1 )
    {
        const auto typeID = *typeIDs.begin();
        const auto type = libcasm_ir::Type::fromID( typeID );

        if( type->isRecord() )
        {
            const auto recordType = std::static_pointer_cast< libcasm_ir::RecordType >( type );
            assert( node.namedExpressions()->size() >= 1 );  // constrain from parser
            for( auto namedExpression : *node.namedExpressions() )
            {
                if( not namedExpression->type() )
                {
                    m_log.info(
                        { namedExpression->sourceLocation() }, "TODO: has a non-typed sub-type" );
                    return;
                }

                const auto expressionName = namedExpression->identifier()->name();
                const auto& expressionType = namedExpression->type();

                const auto it = recordType->elements().find( expressionName );
                if( it != recordType->elements().cend() )
                {
                    if( *expressionType != *( recordType->arguments()[ it->second ] ) )
                    {
                        return;
                    }
                }
            }

            node.setType( type );
        }
    }
}

void TypeInferenceVisitor::visit( LetExpression& node )
{
    // annotate let expression variable with annotation information from parent expression node
    m_typeIDs[ node.expression().get() ] = m_typeIDs[&node ];

    node.variable()->accept( *this );

    if( node.variable()->type() )
    {
        auto& variableType = node.variable()->type();
        if( variableType->isRelation() )
        {
            m_typeIDs[ node.initializer().get() ].emplace( variableType->ptr_result()->id() );
        }
        else
        {
            m_typeIDs[ node.initializer().get() ].emplace( variableType->id() );
        }
    }

    node.initializer()->accept( *this );

    if( not node.variable()->type() and node.initializer()->type() )
    {
        node.variable()->setType( node.initializer()->type()->ptr_result() );
    }

    if( node.type() )
    {
        m_typeIDs[ node.expression().get() ].emplace( node.type()->id() );
    }

    node.expression()->accept( *this );

    if( not node.type() )
    {
        node.setType( node.expression()->type() );
    }

    if( not node.variable()->type() )
    {
        // revisit the expression to infer again the variable type from underlying let expression
        node.expression()->accept( *this );
    }

    assignment(
        node,
        *node.variable(),
        *node.initializer(),
        "let variable '" + node.variable()->identifier()->name() + "'",
        "let initializer",
        Code::TypeInferenceInvalidLetExpressionVariableType,
        Code::TypeInferenceInvalidLetExpressionInitializerType,
        Code::TypeInferenceInvalidLetExpressionTypeMismatch );

    if( not node.expression()->type() )
    {
        m_log.error(
            { node.expression()->sourceLocation() },
            "no type found",
            Code::TypeInferenceInvalidExpression );
    }
    else
    {
        const auto& exprType = node.expression()->type()->result();
        if( node.type()->result() != exprType )
        {
            m_log.error(
                { node.sourceLocation(), node.expression()->sourceLocation() },
                node.description() + " has invalid expression type '" + exprType.description() +
                    "' shall be '" + node.type()->result().description() + "'",
                Code::TypeInferenceInvalidLetExpressionTypeMismatch );
        }
    }
}

void TypeInferenceVisitor::visit( ConditionalExpression& node )
{
    for( auto typeID : m_typeIDs[&node ] )
    {
        m_typeIDs[ node.thenExpression().get() ].emplace( typeID );
        m_typeIDs[ node.elseExpression().get() ].emplace( typeID );
    }

    RecursiveVisitor::visit( node );

    const auto& condExpr = *node.condition();
    auto& thenExpr = *node.thenExpression();
    auto& elseExpr = *node.elseExpression();

    if( condExpr.type() )
    {
        if( condExpr.type()->kind() != libcasm_ir::Type::Kind::BOOLEAN )
        {
            m_log.error(
                { condExpr.sourceLocation() },
                "condition type of conditional expression is not of type "
                "'Boolean', "
                "found type '" +
                    condExpr.type()->description() + "'",
                Code::TypeInferenceInvalidConditionalExpressionCondition );
        }
    }

    inference( "conditional expression", nullptr, node );

    if( thenExpr.type() and elseExpr.type() )
    {
        if( *thenExpr.type() != *elseExpr.type() )
        {
            m_log.error(
                { thenExpr.sourceLocation(), elseExpr.sourceLocation() },
                "types of conditional expression paths does not match, "
                "found type '" +
                    thenExpr.type()->description() + "' at 'then' path, and type '" +
                    elseExpr.type()->description() + "' at 'else' path",
                Code::TypeInferenceInvalidConditionalExpressionPaths );
            return;
        }
    }

    if( thenExpr.type() and elseExpr.id() == Node::ID::UNDEF_LITERAL )
    {
        elseExpr.setType( thenExpr.type() );
    }

    if( thenExpr.id() == Node::ID::UNDEF_LITERAL and elseExpr.type() )
    {
        thenExpr.setType( elseExpr.type() );
    }

    if( node.type() and thenExpr.id() == Node::ID::UNDEF_LITERAL and
        elseExpr.id() == Node::ID::UNDEF_LITERAL )
    {
        thenExpr.setType( node.type() );
        elseExpr.setType( node.type() );
    }

    if( not node.type() )
    {
        node.setType( thenExpr.type() );
    }
}

void TypeInferenceVisitor::visit( ChooseExpression& node )
{
    node.variable()->accept( *this );

    if( node.variable()->type() )
    {
        m_typeIDs[ node.universe().get() ].emplace( node.variable()->type()->id() );
    }

    node.universe()->accept( *this );

    if( not node.variable()->type() and node.universe()->type() )
    {
        node.variable()->setType( node.universe()->type()->ptr_result() );
    }

    if( node.type() )
    {
        m_typeIDs[ node.expression().get() ].emplace( node.type()->id() );
    }

    node.expression()->accept( *this );

    if( not node.type() )
    {
        node.setType( node.expression()->type() );
    }

    if( not node.variable()->type() )
    {
        m_log.error(
            { node.variable()->sourceLocation() },
            "no type found",
            Code::TypeInferenceInvalidExpression );
    }
    else if( not node.universe()->type() )
    {
        m_log.error(
            { node.universe()->sourceLocation() },
            "no type found",
            Code::TypeInferenceInvalidExpression );
    }
    else
    {
        if( *node.variable()->type() != node.universe()->type()->result() )
        {
            m_log.error(
                { node.variable()->sourceLocation(), node.universe()->sourceLocation() },
                node.description() + " variable '" + node.variable()->identifier()->name() +
                    "' of type '" + node.variable()->type()->description() +
                    "' does not match the universe of type '" +
                    node.universe()->type()->result().description() + "'",
                Code::TypeInferenceInvalidChooseExpressionVariableTypeMismatch );
        }
    }

    if( not node.expression()->type() )
    {
        m_log.error(
            { node.expression()->sourceLocation() },
            "no type found",
            Code::TypeInferenceInvalidExpression );
    }
    else
    {
        const auto& exprType = node.expression()->type()->result();
        if( *node.type() != exprType )
        {
            m_log.error(
                { node.sourceLocation(), node.expression()->sourceLocation() },
                node.description() + " has invalid expression type '" + exprType.description() +
                    "' shall be '" + node.type()->description() + "'",
                Code::TypeInferenceInvalidChooseExpressionTypeMismatch );
        }
    }
}

void TypeInferenceVisitor::visit( UniversalQuantifierExpression& node )
{
    inference( node );
}

void TypeInferenceVisitor::visit( ExistentialQuantifierExpression& node )
{
    inference( node );
}

void TypeInferenceVisitor::visit( ConditionalRule& node )
{
    RecursiveVisitor::visit( node );

    const auto& condExpr = *node.condition();

    if( condExpr.type() )
    {
        if( condExpr.type()->result().kind() != libcasm_ir::Type::Kind::BOOLEAN )
        {
            m_log.error(
                { condExpr.sourceLocation() },
                "invalid condition type '" + condExpr.type()->result().description() +
                    ", shall be '" + libcasm_ir::Type::token( libcasm_ir::Type::Kind::BOOLEAN ) +
                    "'",
                Code::TypeInferenceConditionalRuleInvalidConditionType );
        }
    }
}

void TypeInferenceVisitor::visit( CaseRule& node )
{
    node.expression()->accept( *this );

    if( node.expression()->type() )
    {
        const auto caseExprTypeID = node.expression()->type()->ptr_result()->id();

        for( auto caseExpr : *node.cases() )
        {
            m_typeIDs[ caseExpr.get() ].emplace( caseExprTypeID );
        }
    }

    node.cases()->accept( *this );

    if( not node.expression()->type() )
    {
        // if CaseRule expression is still not typed, try to infer the type from the ExpressionCase
        // types
        for( auto _case : *node.cases() )
        {
            if( _case->id() == Node::ID::EXPRESSION_CASE )
            {
                const auto& expressionCase = std::static_pointer_cast< ExpressionCase >( _case );
                if( expressionCase->expression()->type() )
                {
                    m_typeIDs[ node.expression().get() ].emplace(
                        expressionCase->expression()->type()->id() );
                }
            }
        }

        // re-run the inference of the CaseRule expression
        node.expression()->accept( *this );
    }
}

void TypeInferenceVisitor::visit( ExpressionCase& node )
{
    m_typeIDs[ node.expression().get() ] = m_typeIDs[&node ];
    RecursiveVisitor::visit( node );
}

void TypeInferenceVisitor::visit( DefaultCase& node )
{
    RecursiveVisitor::visit( node );
}

void TypeInferenceVisitor::visit( LetRule& node )
{
    node.variable()->accept( *this );

    if( node.variable()->type() )
    {
        auto& variableType = node.variable()->type();
        if( variableType->isRelation() )
        {
            m_typeIDs[ node.expression().get() ].emplace( variableType->ptr_result()->id() );
        }
        else
        {
            m_typeIDs[ node.expression().get() ].emplace( variableType->id() );
        }
    }

    node.expression()->accept( *this );

    if( not node.variable()->type() and node.expression()->type() )
    {
        node.variable()->setType( node.expression()->type()->ptr_result() );
    }

    node.rule()->accept( *this );

    if( not node.variable()->type() )
    {
        // revisit the rule to infer again the variable type from underlying let
        // definitions or rules
        node.rule()->accept( *this );
    }

    assignment(
        node,
        *node.variable(),
        *node.expression(),
        "let variable '" + node.variable()->identifier()->name() + "'",
        "let expression",
        Code::TypeInferenceInvalidLetRuleVariableType,
        Code::TypeInferenceInvalidLetRuleExpressionType,
        Code::TypeInferenceLetRuleTypesMismatch );
}

void TypeInferenceVisitor::visit( ForallRule& node )
{
    node.variable()->accept( *this );

    if( node.variable()->type() )
    {
        m_typeIDs[ node.universe().get() ].emplace( node.variable()->type()->id() );
    }

    node.universe()->accept( *this );

    if( not node.variable()->type() and node.universe()->type() )
    {
        node.variable()->setType( node.universe()->type()->ptr_result() );
    }

    node.condition()->accept( *this );
    const auto& conditionType = node.condition()->type();
    if( conditionType )
    {
        if( conditionType->result().kind() != libcasm_ir::Type::Kind::BOOLEAN )
        {
            m_log.error(
                { node.condition()->sourceLocation() },
                "invalid condition type '" + conditionType->result().description() +
                    ", shall be '" + libcasm_ir::Type::token( libcasm_ir::Type::Kind::BOOLEAN ) +
                    "'",
                Code::TypeInferenceForallRuleInvalidConditionType );
        }
    }

    node.rule()->accept( *this );

    if( not node.variable()->type() )
    {
        m_log.error(
            { node.variable()->sourceLocation() },
            "no type found for 'forall' variable",
            Code::TypeInferenceForallVariableHasNoType );
    }

    if( not node.universe()->type() )
    {
        m_log.error(
            { node.universe()->sourceLocation() },
            "no type found for 'forall' universe",
            Code::TypeInferenceForallUniverseHasNoType );
    }

    if( node.variable()->type() and node.universe()->type() )
    {
        if( *node.variable()->type() != node.universe()->type()->result() )
        {
            m_log.error(
                { node.variable()->sourceLocation(), node.universe()->sourceLocation() },
                node.description() + " variable '" + node.variable()->identifier()->name() +
                    "' of type '" + node.variable()->type()->description() +
                    "' does not match the universe of type '" +
                    node.universe()->type()->result().description() + "'",
                Code::TypeInferenceForallRuleTypeMismatch );
        }
    }

    if( node.universe()->type() )
    {
        const auto& universeType = node.universe()->type();
        if( universeType->isPrimitive() )
        {
            m_log.error(
                { node.universe()->sourceLocation() },
                node.description() + " has an invalid universe type '" +
                    universeType->description() + "'",
                Code::TypeInferenceForallRuleInvalidUniverseType );
        }
    }
}

void TypeInferenceVisitor::visit( ChooseRule& node )
{
    node.variable()->accept( *this );

    if( node.variable()->type() )
    {
        m_typeIDs[ node.universe().get() ].emplace( node.variable()->type()->id() );
    }

    node.universe()->accept( *this );

    if( not node.variable()->type() and node.universe()->type() )
    {
        node.variable()->setType( node.universe()->type()->ptr_result() );
    }

    node.rule()->accept( *this );

    if( not node.variable()->type() )
    {
        m_log.error(
            { node.variable()->sourceLocation() },
            "no type found",
            Code::TypeInferenceInvalidExpression );
    }
    else if( not node.universe()->type() )
    {
        m_log.error(
            { node.universe()->sourceLocation() },
            "no type found",
            Code::TypeInferenceInvalidExpression );
    }
    else
    {
        if( *node.variable()->type() != node.universe()->type()->result() )
        {
            m_log.error(
                { node.variable()->sourceLocation(), node.universe()->sourceLocation() },
                node.description() + " variable '" + node.variable()->identifier()->name() +
                    "' of type '" + node.variable()->type()->description() +
                    "' does not match the universe of type '" +
                    node.universe()->type()->result().description() + "'",
                Code::TypeInferenceInvalidChooseRuleVariableTypeMismatch );
        }
    }
}

void TypeInferenceVisitor::visit( UpdateRule& node )
{
    auto& func = *node.function();
    auto& expr = *node.expression();

    func.accept( *this );

    if( func.type() )
    {
        m_typeIDs[&expr ].emplace( func.type()->ptr_result()->id() );
    }

    node.expression()->accept( *this );

    if( func.targetType() == CallExpression::TargetType::BUILTIN )
    {
        m_log.error(
            { func.sourceLocation() },
            "performing update rule on built-in '" + func.identifier()->path() + "' is not allowed",
            Code::TypeInferenceUpdateRuleFunctionIsBuiltin );
        return;
    }

    assignment(
        node,
        func,
        expr,
        "updated function",
        "updating expression",
        Code::TypeInferenceInvalidUpdateRuleFunctionType,
        Code::TypeInferenceInvalidUpdateRuleExpressionType,
        Code::TypeInferenceUpdateRuleTypesMismatch );
}

void TypeInferenceVisitor::assignment(
    const Node& node,
    TypedNode& lhs,
    TypedNode& rhs,
    const std::string& dst,
    const std::string& src,
    const Code& dstErr,
    const Code& srcErr,
    const Code& assignmentErr )
{
    if( lhs.type() and not rhs.type() and rhs.id() == Node::ID::UNDEF_LITERAL )
    {
        if( lhs.type()->isRelation() )
        {
            rhs.setType( lhs.type()->ptr_result() );
        }
        else
        {
            rhs.setType( lhs.type() );
        }
    }

    const auto error_count = m_log.errors();

    if( not lhs.type() )
    {
        m_log.error( { lhs.sourceLocation() }, "unable to infer type of " + dst, dstErr );
    }

    if( not rhs.type() )
    {
        m_log.error( { rhs.sourceLocation() }, "unable to infer type of " + src, srcErr );
    }

    if( error_count != m_log.errors() )
    {
        return;
    }

    const auto& tyLhs = lhs.type()->result();
    const auto& tyRhs = rhs.type()->result();

    if( tyLhs != tyRhs )
    {
        u1 mismatch = true;
        if( tyLhs.isInteger() and tyRhs.isInteger() )
        {
            // relaxation: mixed integer with range properties are checked
            //             at run-time
            mismatch = false;
        }
        else if(
            tyLhs.isBinary() and tyRhs.isBinary() and
            static_cast< const libcasm_ir::BinaryType& >( tyLhs ).bitsize() >=
                static_cast< const libcasm_ir::BinaryType& >( tyRhs ).bitsize() )
        {
            // relaxation: mixed binary types are OK as long as
            //             bitsize(lhs) >= bitsize(rhs)
            mismatch = false;
        }
        else if( tyLhs.isBinary() and tyRhs.isInteger() and rhs.id() == Node::ID::VALUE_LITERAL )
        {
            // relaxation: lhs binary and rhs integer are OK as long as rhs is a
            //             integer constant with bitsize(lhs) >= bitsize(rhs)
            mismatch = false;

            try
            {
                auto& valueLiteral = static_cast< ValueLiteral& >( rhs );
                assert( libcasm_ir::isa< libcasm_ir::IntegerConstant >( valueLiteral.value() ) );
                auto constant =
                    std::static_pointer_cast< libcasm_ir::IntegerConstant >( valueLiteral.value() );

                const auto value = libstdhl::Memory::get< libcasm_ir::BinaryConstant >(
                    lhs.type()->ptr_result(),
                    static_cast< const libstdhl::Type::Natural& >( constant->value() ) );

                valueLiteral.setValue( value );
            }
            catch( const std::exception& e )
            {
                mismatch = true;
            }
        }
        else if( tyLhs.isRecord() and tyRhs.isTuple() )
        {
            const auto& recordTyLhs = static_cast< const libcasm_ir::RecordType& >( tyLhs );
            const auto& tupleTyRhs = static_cast< const libcasm_ir::TupleType& >( tyRhs );

            const auto tupleTyLhs = libcasm_ir::TupleType( recordTyLhs.arguments() );
            if( tupleTyLhs == tupleTyRhs )
            {
                mismatch = false;
            }
        }
        else if( tyLhs.isRecord() and tyRhs.isRecord() )
        {
            const auto& recordTyLhs = static_cast< const libcasm_ir::RecordType& >( tyLhs );
            const auto& recordTyRhs = static_cast< const libcasm_ir::RecordType& >( tyRhs );

            if( recordTyLhs.identifiers().size() > recordTyRhs.identifiers().size() )
            {
                // TODO
            }
        }

        if( mismatch )
        {
            auto lhsSourceLocation = lhs.sourceLocation();

            if( lhs.id() == Node::ID::DIRECT_CALL_EXPRESSION )
            {
                const auto& directCall = static_cast< DirectCallExpression& >( lhs );
                if( directCall.targetType() == CallExpression::TargetType::FUNCTION )
                {
                    const auto functionDefinition = std::static_pointer_cast< FunctionDefinition >(
                        directCall.targetDefinition() );

                    lhsSourceLocation = functionDefinition->returnType()->sourceLocation();
                }
            }

            m_log.error(
                { rhs.sourceLocation(), lhsSourceLocation },
                "type mismatch: " + src + " was '" + tyRhs.description() + "', but " + dst +
                    " expects '" + tyLhs.description() + "'",
                assignmentErr );
        }
    }
}

const libcasm_ir::Annotation* TypeInferenceVisitor::annotate(
    Node& node, const std::vector< Expression::Ptr >& expressions )
{
    const libcasm_ir::Annotation* annotation = nullptr;

    if( node.id() == libcasm_fe::Ast::Type::ID::UNARY_EXPRESSION )
    {
        annotation =
            &libcasm_ir::Annotation::find( static_cast< const UnaryExpression& >( node ).op() );
    }
    else if( node.id() == libcasm_fe::Ast::Type::ID::BINARY_EXPRESSION )
    {
        annotation =
            &libcasm_ir::Annotation::find( static_cast< const BinaryExpression& >( node ).op() );
    }
    else if( node.id() == libcasm_fe::Ast::Type::ID::DIRECT_CALL_EXPRESSION )
    {
        auto& directCall = static_cast< DirectCallExpression& >( node );
        assert( directCall.identifier() );
        const auto identifier = directCall.identifier();

        try
        {
            const auto& builtin_annotation =
                libcasm_ir::Annotation::find( directCall.targetBuiltinId() );
            annotation = &builtin_annotation;
        }
        catch( const std::domain_error& e )
        {
            m_log.error(
                { directCall.sourceLocation() },
                "unable to resolve built-in symbol '" + identifier->path() +
                    "', due to missing annotation information from 'libcasm-ir'" );
            return nullptr;
        }
    }
    else if( node.id() == libcasm_fe::Ast::Type::ID::METHOD_CALL_EXPRESSION )
    {
        auto& methodCall = static_cast< MethodCallExpression& >( node );
        const auto& methodName = methodCall.methodName()->name();

        try
        {
            const auto& builtin_annotation = libcasm_ir::Annotation::find( methodName );
            annotation = &builtin_annotation;
        }
        catch( const std::domain_error& e )
        {
            return nullptr;
        }
    }
    else
    {
        assert( !"no annotation possible for this node type" );
        return nullptr;
    }

    for( std::size_t c = 0; c < expressions.size(); c++ )
    {
        for( auto argumentTypeID : annotation->argumentTypeIDs( c ) )
        {
            m_typeIDs[ expressions[ c ].get() ].emplace( argumentTypeID );
        }
    }

    for( auto resultTypeID : annotation->resultTypeIDs() )
    {
        m_typeIDs[&node ].emplace( resultTypeID );
    }

    return annotation;
}

void TypeInferenceVisitor::inference(
    const std::string& description,
    const libcasm_ir::Annotation* annotation,
    TypedNode& node,
    const std::vector< Expression::Ptr >& arguments )
{
    if( node.type() )
    {
        return;
    }

    auto& typeIDs = m_typeIDs[&node ];

    std::vector< libcasm_ir::Type::Ptr > argTypes = {};
    std::vector< libcasm_ir::Value::Ptr > argValues = {};
    for( std::size_t c = 0; c < arguments.size(); c++ )
    {
        if( arguments[ c ]->type() )
        {
            argTypes.emplace_back( arguments[ c ]->type()->ptr_result() );
        }
        else
        {
            argTypes.emplace_back( nullptr );
        }

        if( arguments[ c ]->id() == Node::ID::VALUE_LITERAL )
        {
            const auto argumentValue =
                static_cast< Ast::ValueLiteral* >( arguments[ c ].get() )->value();
            argValues.emplace_back( argumentValue );
        }
        else
        {
            argValues.emplace_back( nullptr );
        }
    }

    if( annotation and arguments.size() > 0 )
    {
        annotation->resolve( argTypes );

        auto unknownTypeArgCnt = 0;
        for( std::size_t c = 0; c < arguments.size(); c++ )
        {
            if( not argTypes[ c ] )
            {
                unknownTypeArgCnt++;
                continue;
            }

            m_typeIDs[ arguments[ c ].get() ].emplace( argTypes[ c ]->id() );
            inference( description, nullptr, *arguments[ c ] );
        }

        if( unknownTypeArgCnt == 0 )
        {
            try
            {
                const auto inferredTypeID = annotation->inference( argTypes, argValues );
                typeIDs.insert( inferredTypeID );
            }
            catch( const libcasm_ir::TypeArgumentException& e )
            {
                m_log.error(
                    { arguments[ e.position() ]->sourceLocation() },
                    "type mismatch: " + description + " argument type at position " +
                        std::to_string( e.position() + 1 ) + ": " + e.what(),
                    Code::TypeInferenceArgumentTypeMismatch );
                return;
            }
            catch( const std::domain_error& e )
            {
                m_log.error(
                    { node.sourceLocation() },
                    "unable to infer result type of " + description + ": " + e.what(),
                    Code::TypeInferenceNotDefinedForExpression );
            }
            catch( const std::invalid_argument& e )
            {
                m_log.error( { node.sourceLocation() }, e.what() );
                return;
            }
        }
    }

    std::set< libcasm_ir::Type::ID > topTypeIDs = {};
    for( auto typeID : typeIDs )
    {
        for( auto topTypeID : libcasm_ir::Type::fromKind( typeID.kind() ) )
        {
            topTypeIDs.emplace( topTypeID );
        }
    }

    std::vector< libcasm_ir::Type::ID > tmpTypeIDs = {};

    std::set_intersection(
        typeIDs.begin(),
        typeIDs.end(),
        topTypeIDs.begin(),
        topTypeIDs.end(),
        std::back_inserter( tmpTypeIDs ) );

    typeIDs.clear();
    for( auto typeID : tmpTypeIDs )
    {
        typeIDs.emplace( typeID );
    }

    if( typeIDs.size() == 1 )
    {
        const auto typeID = *typeIDs.begin();
        node.setType( libcasm_ir::Type::fromID( typeID ) );
    }
}

void TypeInferenceVisitor::inference( QuantifierExpression& node )
{
    node.setType( libstdhl::Memory::get< libcasm_ir::BooleanType >() );

    m_typeIDs[ node.proposition().get() ].emplace( node.type()->id() );

    if( node.predicateVariable()->type() )
    {
        m_typeIDs[ node.universe().get() ].emplace( node.predicateVariable()->type()->id() );
    }

    node.universe()->accept( *this );

    node.predicateVariable()->accept( *this );

    if( not node.predicateVariable()->type() and node.universe()->type() )
    {
        node.predicateVariable()->setType( node.universe()->type()->ptr_result() );
    }

    node.proposition()->accept( *this );

    if( not node.predicateVariable()->type() )
    {
        m_log.error(
            { node.predicateVariable()->sourceLocation() },
            "no type found",
            Code::TypeInferenceInvalidExpression );
    }
    else if( not node.universe()->type() )
    {
        m_log.error(
            { node.universe()->sourceLocation() },
            "no type found",
            Code::TypeInferenceInvalidExpression );
    }
    else
    {
        if( *node.predicateVariable()->type() != node.universe()->type()->result() )
        {
            m_log.error(
                { node.predicateVariable()->sourceLocation(), node.universe()->sourceLocation() },
                node.description() + " predicate variable '" +
                    node.predicateVariable()->identifier()->name() + "' of type '" +
                    node.predicateVariable()->type()->description() +
                    "' does not match the universe of type '" +
                    node.universe()->type()->result().description() + "'",

                ( node.id() == Node::ID::EXISTENTIAL_QUANTIFIER_EXPRESSION )
                    ? Code::TypeInferenceQuantifierExistentialPredicateTypeMismatch
                    : Code::TypeInferenceQuantifierUniversalPredicateTypeMismatch );
        }
    }

    if( not node.proposition()->type() )
    {
        m_log.error(
            { node.proposition()->sourceLocation() },
            "no type found",
            Code::TypeInferenceInvalidExpression );
    }
    else
    {
        const auto& propType = node.proposition()->type()->result();
        if( *node.type() != propType )
        {
            m_log.error(
                { node.proposition()->sourceLocation() },

                node.description() + " has invalid proposition type '" + propType.description() +
                    "' shall be '" + node.type()->description() + "'",

                ( node.id() == Node::ID::EXISTENTIAL_QUANTIFIER_EXPRESSION )
                    ? Code::TypeInferenceQuantifierExistentialPropositionTypeMismatch
                    : Code::TypeInferenceQuantifierUniversalPropositionTypeMismatch );
        }
    }
}

class TypeResolveVisitor final : public RecursiveVisitor
{
  public:
    TypeResolveVisitor( libcasm_fe::Logger& log, const Namespace& symboltable );

    void visit( DirectCallExpression& node ) override;

  private:
    libcasm_fe::Logger& m_log;
    const Namespace& m_symboltable;
};

TypeResolveVisitor::TypeResolveVisitor( libcasm_fe::Logger& log, const Namespace& symboltable )
: m_log( log )
, m_symboltable( symboltable )
{
}

void TypeResolveVisitor::visit( DirectCallExpression& node )
{
    RecursiveVisitor::visit( node );

    if( node.targetType() != CallExpression::TargetType::UNKNOWN )
    {
        return;
    }

    if( node.identifier()->type() != IdentifierPath::Type::RELATIVE )
    {
        m_log.debug( { node.sourceLocation() }, "target type 'UNKNOWN' found!" );
        return;
    }

    if( not node.type() )
    {
        m_log.error(
            { node.sourceLocation() },
            "unable to infer type of relative path '" + node.identifier()->baseName() + "'",
            Code::DirectCallExpressionInvalidRelativePath );
        return;
    }

    std::vector< std::string > identifierPath;
    identifierPath.reserve( 2 );
    identifierPath.emplace_back( node.type()->description() );  // TODO: this will need some extra
                                                                // care when we add the import
                                                                // feature. (e.g. namespace lookup
                                                                // by type)
    identifierPath.emplace_back( node.identifier()->baseName() );

    try
    {
        const auto& symbol = m_symboltable.find( identifierPath );

        switch( symbol->id() )
        {
            case Node::ID::ENUMERATOR_DEFINITION:
            {
                node.setTargetType( CallExpression::TargetType::CONSTANT );
                break;
            }
            default:
            {
                throw std::domain_error( "cannot reference '" + symbol->description() + "'" );
                break;
            }
        }

        node.setTargetDefinition( symbol );
    }
    catch( const std::domain_error& e )
    {
        m_log.error(
            { node.sourceLocation() },
            "type '" + node.type()->description() +
                "' does not have a symbol with relative path '" + node.identifier()->baseName() +
                "'",
            Code::DirectCallExpressionInvalidRelativePath );
    }
}

void TypeInferencePass::usage( libpass::PassUsage& pu )
{
    pu.require< SourceToAstPass >();
    pu.scheduleAfter< TypeCheckPass >();
}

u1 TypeInferencePass::run( libpass::PassResult& pr )
{
    libcasm_fe::Logger log( &id, stream() );

    const auto data = pr.output< SourceToAstPass >();
    const auto specification = data->specification();

    TypeInferenceVisitor typeInferenceVisitor( log );
    specification->definitions()->accept( typeInferenceVisitor );

    TypeResolveVisitor typeResolveVisitor( log, *specification->symboltable() );
    specification->definitions()->accept( typeResolveVisitor );

    const auto errors = log.errors();
    if( errors > 0 )
    {
        log.debug( "found %lu error(s) during type inference", errors );
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
