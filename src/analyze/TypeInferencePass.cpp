//
//  Copyright (C) 2014-2019 CASM Organization <https://casm-lang.org>
//  All rights reserved.
//
//  Developed by: Philipp Paulweber
//                Emmanuel Pescosta
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

#include "TypeInferencePass.h"

#include <libcasm-fe/Logger>
#include <libcasm-fe/Namespace>
#include <libcasm-fe/Specification>
#include <libcasm-fe/TypeInfo>
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
    TypeInferenceVisitor( libcasm_fe::Logger& log, const Namespace& symboltable );

    void visit( InitDefinition& node ) override;
    void visit( VariableDefinition& node ) override;
    void visit( FunctionDefinition& node ) override;
    void visit( DerivedDefinition& node ) override;
    void visit( RuleDefinition& node ) override;
    void visit( InvariantDefinition& node ) override;

    void visit( UndefLiteral& node ) override;
    void visit( ReferenceLiteral& node ) override;
    void visit( ListLiteral& node ) override;
    void visit( RangeLiteral& node ) override;
    void visit( TupleLiteral& node ) override;
    void visit( RecordLiteral& node ) override;

    void visit( EmbracedExpression& node ) override;
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
    void visit( CardinalityExpression& node ) override;

    void visit( ConditionalRule& node ) override;
    void visit( WhileRule& node ) override;

    void visit( CaseRule& node ) override;
    void visit( ExpressionCase& node ) override;
    void visit( DefaultCase& node ) override;

    void visit( LetRule& node ) override;
    void visit( ForallRule& node ) override;
    void visit( ChooseRule& node ) override;
    void visit( UpdateRule& node ) override;

    void visit( VariableBinding& node ) override;

  private:
    bool tryResolveCallInTypeNamespace( DirectCallExpression& node ) const;

    void assignment(
        TypedNode& lhs,
        TypedNode& rhs,
        const std::string& dst,
        const std::string& src,
        const Code assignmentErr );

    const libcasm_ir::Annotation* annotate(
        Node& node, const std::vector< Expression::Ptr >& expressions = {} );

    void inference(
        const std::string& description,
        const libcasm_ir::Annotation* annotation,
        TypedNode& node,
        const std::vector< Expression::Ptr >& arguments = {} );

    void inferenceQuantifierExpression( QuantifierExpression& node );

    template < typename T >
    void annotateNodes( const NodeList< T >& nodes, const libcasm_ir::Type::ID typeId );

    /**
     * Removes all annotations of \a node from m_typeIDs which are not of kind \a kind.
     */
    void filterAnnotationsByKind( const Node& node, const libcasm_ir::Type::Kind kind );

    void checkIfNodeHasTypeOfKind(
        const TypedNode& node,
        const libcasm_ir::Type::Kind expectedKind,
        const std::string& errorDescription,
        const Code errorCode ) const;

  private:
    libcasm_fe::Logger& m_log;
    const Namespace& m_symboltable;

    std::unordered_map< const Node*, std::set< libcasm_ir::Type::ID > > m_typeIDs;
};

TypeInferenceVisitor::TypeInferenceVisitor( libcasm_fe::Logger& log, const Namespace& symboltable )
: m_log( log )
, m_symboltable( symboltable )
{
}

void TypeInferenceVisitor::visit( InitDefinition& node )
{
    RecursiveVisitor::visit( node );
    const auto programFunction = node.programFunction();
    if( programFunction )
    {
        programFunction->accept( *this );
    }
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

    // annotate the defined expression (default value/expression) with the return type
    m_typeIDs[ node.defined()->expression().get() ].emplace( returnType.id() );
    node.defined()->expression()->accept( *this );

    if( node.defined()->expression()->type() and
        node.defined()->expression()->type() != node.returnType()->type() )
    {
        if( node.defined()->expression()->type()->isInteger() ==
            node.returnType()->type()->isInteger() )
        {
            // relaxation: mixed ranged and non-ranged integer types are allowed and checked in a
            // later pass or step!
        }
        else
        {
            m_log.error(
                { node.defined()->expression()->sourceLocation(),
                  node.returnType()->sourceLocation() },
                "type mismatch: type of default value was '" +
                    node.defined()->expression()->type()->description() + "', function expects '" +
                    node.returnType()->type()->description() + "'",
                Code::TypeInferenceFunctionDefaultValueTypeMismatch );
        }
    }

    node.initially()->accept( *this );
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
        const auto& expTy = *node.expression()->type();

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

void TypeInferenceVisitor::visit( InvariantDefinition& node )
{
    m_typeIDs[ node.expression().get() ].emplace( libcasm_ir::Type::Kind::BOOLEAN );

    RecursiveVisitor::visit( node );

    checkIfNodeHasTypeOfKind(
        *node.expression(),
        libcasm_ir::Type::Kind::BOOLEAN,
        "expression",
        Code::TypeInferenceInvariantDefinitionInvalidExpressionType );
}

void TypeInferenceVisitor::visit( UndefLiteral& node )
{
    RecursiveVisitor::visit( node );
    inference( "undef literal", nullptr, node );
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

void TypeInferenceVisitor::visit( EmbracedExpression& node )
{
    for( const auto typeId : m_typeIDs[&node ] )
    {
        m_typeIDs[ node.expression().get() ].emplace( typeId );
    }
    RecursiveVisitor::visit( node );
    node.setType( node.expression()->type() );
}

void TypeInferenceVisitor::visit( NamedExpression& node )
{
    RecursiveVisitor::visit( node );
    node.setType( node.expression()->type() );
}

void TypeInferenceVisitor::visit( DirectCallExpression& node )
{
    if( node.type() )
    {
        return;
    }

    assert( node.identifier() );
    const auto identifier = node.identifier();

    if( node.targetType() == DirectCallExpression::TargetType::UNKNOWN )
    {
        inference( "direct call", nullptr, node );
        if( not tryResolveCallInTypeNamespace( node ) )
        {
            // unable to resolve the call -> not enough information to continue
            return;
        }
    }

    assert( node.targetType() != DirectCallExpression::TargetType::UNKNOWN );

    std::vector< libcasm_ir::Type::Ptr > argumentTypes;

    switch( node.targetType() )
    {
        case DirectCallExpression::TargetType::VARIABLE:
        {
            const auto& variable = node.targetDefinition();

            m_typeIDs[ variable.get() ] = m_typeIDs[&node ];
            variable->accept( *this );

            node.setType( variable->type() );
            break;
        }
        case DirectCallExpression::TargetType::BUILTIN:
        {
            auto directCallArguments = node.arguments()->data();
            const auto* annotation = annotate( node, directCallArguments );

            RecursiveVisitor::visit( node );

            const auto description = "built-in '" + identifier->path() + "'";
            inference( description, annotation, node, directCallArguments );

            RecursiveVisitor::visit( node );

            for( auto argumentType : *node.arguments() )
            {
                if( not argumentType->type() )
                {
                    m_log.debug(
                        { argumentType->sourceLocation() },
                        "TODO: '" + identifier->path() + "' has a non-typed argument(s)" );
                    return;
                }

                argumentTypes.emplace_back( argumentType->type() );
            }

            if( node.type() )
            {
                const auto relationType = libstdhl::Memory::make< libcasm_ir::RelationType >(
                    node.type(), argumentTypes );

                if( not annotation->valid( *relationType ) )
                {
                    m_log.error(
                        { node.sourceLocation() },
                        "built-in '" + identifier->path() + "' has no type relation '" +
                            relationType->description() + "'",
                        Code::TypeInferenceBuiltinRelationTypeInvalid );
                    return;
                }

                node.setTargetBuiltinType( relationType );
            }

            break;
        }
        case DirectCallExpression::TargetType::DERIVED:   // [[fallthrough]]
        case DirectCallExpression::TargetType::FUNCTION:  // [[fallthrough]]
        case DirectCallExpression::TargetType::RULE:      // [[fallthrough]]
        case DirectCallExpression::TargetType::SELF:      // [[fallthrough]]
        case DirectCallExpression::TargetType::CONSTANT:
        {
            // make sure that the definition has been typed
            const auto& definition = node.targetDefinition();
            if( not definition )
            {
                // break inference of not defined direct calls!
                return;
            }

            definition->accept( *this );

            const auto& arguments = *node.arguments();
            argumentTypes = definition->type()->arguments().data();
            for( std::size_t i = 0; i < arguments.size(); i++ )
            {
                m_typeIDs[ arguments.at( i ).get() ].emplace( argumentTypes.at( i )->id() );
            }

            node.setType( definition->type()->ptr_result() );
            break;
        }
        case DirectCallExpression::TargetType::TYPE_DOMAIN:
        {
            assert( node.arguments()->size() == 0 );

            // if the type domain has FE definition use this type!
            const auto& definition = node.targetDefinition();
            if( definition )
            {
                definition->accept( *this );
                assert( definition->type()->arguments().size() == 0 );
                node.setType( definition->type() );
                break;
            }

            try
            {
                const auto& typeDomain = TypeInfo::instance().getType( identifier->path() );
                node.setType( typeDomain );
            }
            catch( const std::domain_error& e )
            {
                m_log.error( { node.sourceLocation() }, e.what() );
            }
            break;
        }
        case DirectCallExpression::TargetType::UNKNOWN:
        {
            assert( !"unknown target type" );
            return;
        }
    }

    if( node.type() )
    {
        m_typeIDs[&node ].emplace( node.type()->id() );
    }

    RecursiveVisitor::visit( node );

    const auto& arguments = *node.arguments();
    assert( arguments.size() == argumentTypes.size() );

    for( std::size_t pos = 0; pos < arguments.size(); pos++ )
    {
        const auto& exprArg = arguments.at( pos );
        if( not exprArg->type() )
        {
            continue;
        }

        const auto exprArgType = exprArg->type();
        const auto callArgType = argumentTypes.at( pos );

        if( callArgType->isInteger() and exprArgType->isInteger() )
        {
            continue;
        }

        if( *callArgType != *exprArgType )
        {
            const std::map< DirectCallExpression::TargetType, Code > codes = {
                { DirectCallExpression::TargetType::FUNCTION,
                  Code::TypeInferenceFunctionArgumentTypeMismatch },
                { DirectCallExpression::TargetType::DERIVED,
                  Code::TypeInferenceDerivedArgumentTypeMismatch },
                { DirectCallExpression::TargetType::BUILTIN,
                  Code::TypeInferenceBuiltinArgumentTypeMismatch },
                { DirectCallExpression::TargetType::RULE,
                  Code::TypeInferenceRuleArgumentTypeMismatch },
            };

            const auto code = codes.find( node.targetType() );
            assert( code != codes.end() and " invalid target type with arguments " );

            m_log.error(
                { exprArg->sourceLocation() },
                "type mismatch: " + node.targetTypeName() + " argument type at position " +
                    std::to_string( pos + 1 ) + " was '" + exprArgType->description() + "', " +
                    node.targetTypeName() + " definition expects '" + callArgType->description() +
                    "'",
                code->second );
        }
    }
}

void TypeInferenceVisitor::visit( MethodCallExpression& node )
{
    if( node.type() )
    {
        return;
    }

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

    std::vector< Expression::Ptr > methodCallArguments;
    methodCallArguments.reserve( 1 + node.arguments()->size() );
    methodCallArguments.emplace_back( node.object() );  // pass object instance as first argument
    methodCallArguments.insert(
        methodCallArguments.end(), node.arguments()->begin(), node.arguments()->end() );

    const auto* annotation = annotate( node, methodCallArguments );
    if( not annotation )
    {
        return;
    }

    // for the time being only builtin method calls are supported
    node.setMethodType( MethodCallExpression::MethodType::BUILTIN );
    node.setTargetBuiltinId( annotation->valueID() );

    RecursiveVisitor::visit( node );

    const auto description = "built-in method '" + methodName + "'";
    inference( description, annotation, node, methodCallArguments );

    RecursiveVisitor::visit( node );

    std::vector< libcasm_ir::Type::Ptr > argumentTypes;
    argumentTypes.emplace_back( node.object()->type() );
    for( auto argumentType : *node.arguments() )
    {
        if( not argumentType->type() )
        {
            m_log.debug(
                { argumentType->sourceLocation() },
                "TODO: '" + methodName + "' has a non-typed argument(s)" );
            return;
        }

        argumentTypes.emplace_back( argumentType->type() );
    }

    const auto relationType =
        libstdhl::Memory::make< libcasm_ir::RelationType >( node.type(), argumentTypes );

    if( not annotation->valid( *relationType ) )
    {
        m_log.error(
            { node.sourceLocation() },
            "built-in '" + methodName + "' has no type relation '" + relationType->description() +
                "'" );
        return;
    }

    node.setTargetBuiltinType( relationType );
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

        if( value >= 1 and value <= objectType->arguments().size() )
        {
            const auto& resultType = objectType->arguments()[ value.value() - 1 ];
            node.setType( resultType );
        }
        else
        {
            m_log.error(
                { node.sourceLocation() },
                "element access of '" + objectType->description() + "' at position '" +
                    value.to_string() + "' is out-of-bounds",
                Code::TypeInferenceInvalidLiteralCallExpression );
        }
    }
    else
    {
        m_log.error(
            { node.sourceLocation() },
            "unsupported literal call expression of '" + objectType->description() + "' and '" +
                literalType->description() + "'",
            Code::TypeInferenceInvalidLiteralCallExpression );
    }
}

void TypeInferenceVisitor::visit( IndirectCallExpression& node )
{
    RecursiveVisitor::visit( node );

    const auto& expressionType = node.expression()->type();

    if( not expressionType )
    {
        m_log.error(
            { node.expression()->sourceLocation() },
            "unable to resolve type of indirect call expression" );
        return;
    }

    if( not expressionType->isReference() )
    {
        m_log.error(
            { node.expression()->sourceLocation() },
            "expression is not a reference",
            Code::TypeInferenceInvalidIndirectCallExpression );
        return;
    }

    const auto& refType = std::static_pointer_cast< libcasm_ir::ReferenceType >( expressionType );
    node.setType( refType->dereference() );
}

void TypeInferenceVisitor::visit( TypeCastingExpression& node )
{
    node.asType()->accept( *this );

    if( node.asType()->type() )
    {
        m_typeIDs[ node.fromExpression().get() ].emplace( node.asType()->type()->id() );
    }

    node.fromExpression()->accept( *this );

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
    argumentTypes.emplace_back( fromExpressionType );

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

        node.setTargetBuiltinType( relationType );
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

    node.setType( resultType );
}

void TypeInferenceVisitor::visit( UnaryExpression& node )
{
    if( node.op() == libcasm_ir::Value::ADD_INSTRUCTION )
    {
        // add unary expression (e.g. '+4') will not be annotated,
        // just visit sub-nodes, propagate the expression type to this node and return
        RecursiveVisitor::visit( node );
        node.setType( node.expression()->type() );
        return;
    }

    const auto* annotation = annotate( node, { node.expression() } );

    RecursiveVisitor::visit( node );

    const auto description = "unary operator '" + libcasm_ir::Value::token( node.op() ) + "'";

    inference( description, annotation, node, { node.expression() } );

    RecursiveVisitor::visit( node );

    if( node.type() and node.expression()->type() )
    {
        const std::vector< libcasm_ir::Type::Ptr > argTypeList{ node.expression()->type() };

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

    RecursiveVisitor::visit( node );

    if( node.type() and node.left()->type() and node.right()->type() )
    {
        const std::vector< libcasm_ir::Type::Ptr > argTypeList{ node.left()->type(),
                                                                node.right()->type() };

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
    if( node.type() )
    {
        return;
    }

    filterAnnotationsByKind( node, libcasm_ir::Type::Kind::LIST );

    // propagate type annotation to all list elements
    for( const auto typeId : m_typeIDs[&node ] )
    {
        const auto type = libcasm_ir::Type::fromID( typeId );
        assert( type->isList() );
        const auto listType = std::static_pointer_cast< libcasm_ir::ListType >( type );
        annotateNodes( *node.expressions(), listType->ptr_result()->id() );
    }

    node.expressions()->accept( *this );

    for( const auto& expression : *node.expressions() )
    {
        if( expression->type() )
        {
            annotateNodes( *node.expressions(), expression->type()->id() );
        }
    }

    node.expressions()->accept( *this );

    inference( "list literal", nullptr, node );
    if( not node.type() )
    {
        // inference failed, use type of first typed expression instead
        for( const auto& expression : *node.expressions() )
        {
            if( expression->type() )
            {
                const auto listType =
                    libstdhl::Memory::get< libcasm_ir::ListType >( expression->type() );
                node.setType( listType );
                break;
            }
        }
    }

    if( node.type() )
    {
        for( const auto& expression : *node.expressions() )
        {
            if( not expression->type() )
            {
                continue;
            }

            if( *expression->type() != node.type()->result() )
            {
                m_log.error(
                    { expression->sourceLocation() },
                    "list element has invalid type '" + expression->type()->description() +
                        "', expected '" + node.type()->result().description() + "'",
                    Code::TypeInferenceListLiteralTypeMismatch );
            }
        }
    }
}

void TypeInferenceVisitor::visit( RangeLiteral& node )
{
    node.left()->accept( *this );

    if( node.left()->type() )
    {
        m_typeIDs[ node.right().get() ].emplace( node.left()->type()->id() );
    }

    node.right()->accept( *this );

    if( node.right()->type() and not node.left()->type() )
    {
        m_typeIDs[ node.left().get() ].emplace( node.right()->type()->id() );
        node.left()->accept( *this );
    }

    const auto lhsType = node.left()->type();
    const auto rhsType = node.right()->type();
    if( not( lhsType and rhsType ) )
    {
        return;
    }

    if( *lhsType != *rhsType )
    {
        m_log.error(
            { node.sourceLocation() },
            "types of range does not match, " + lhsType->description() +
                " != " + rhsType->description(),
            Code::TypeInferenceRangeLiteralTypeMismatch );
        return;
    }

    const auto rangeType = libstdhl::Memory::get< libcasm_ir::RangeType >( lhsType );
    node.setType( rangeType );
}

void TypeInferenceVisitor::visit( TupleLiteral& node )
{
    if( node.type() )
    {
        return;
    }

    filterAnnotationsByKind( node, libcasm_ir::Type::Kind::TUPLE );

    // propagate type annotation to all tuple elements
    for( const auto typeId : m_typeIDs[&node ] )
    {
        const auto type = libcasm_ir::Type::fromID( typeId );
        assert( type->isTuple() );
        const auto tupleType = std::static_pointer_cast< libcasm_ir::TupleType >( type );
        const auto& expressionTypes = tupleType->arguments();
        if( expressionTypes.size() != node.expressions()->size() )
        {
            continue;
        }

        for( std::size_t i = 0; i < expressionTypes.size(); i++ )
        {
            const auto& expression = node.expressions()->at( i );
            const auto& expressionType = expressionTypes.at( i );
            m_typeIDs[ expression.get() ].emplace( expressionType->id() );
        }
    }

    RecursiveVisitor::visit( node );

    libcasm_ir::Types expressionTypes;
    for( const auto& expression : *node.expressions() )
    {
        if( not expression->type() )
        {
            // cannot create a tuple type if not all element types are known, thus the return
            return;
        }

        expressionTypes.add( expression->type() );
    }

    const auto tupleType = libstdhl::Memory::get< libcasm_ir::TupleType >( expressionTypes );
    node.setType( tupleType );
}

void TypeInferenceVisitor::visit( RecordLiteral& node )
{
    if( node.type() )
    {
        return;
    }

    filterAnnotationsByKind( node, libcasm_ir::Type::Kind::RECORD );

    // propagate type annotation to all record elements
    for( const auto typeId : m_typeIDs[&node ] )
    {
        const auto type = libcasm_ir::Type::fromID( typeId );
        assert( type->isRecord() );
        const auto recordType = std::static_pointer_cast< libcasm_ir::RecordType >( type );
        const auto& expressionTypes = recordType->arguments();
        if( expressionTypes.size() != node.namedExpressions()->size() )
        {
            continue;
        }

        for( std::size_t i = 0; i < expressionTypes.size(); i++ )
        {
            const auto& expression = node.namedExpressions()->at( i );
            const auto& expressionType = expressionTypes.at( i );
            m_typeIDs[ expression.get() ].emplace( expressionType->id() );
        }
    }

    RecursiveVisitor::visit( node );

    std::vector< std::string > expressionNames;
    libcasm_ir::Types expressionTypes;
    for( const auto& namedExpression : *node.namedExpressions() )
    {
        if( not namedExpression->type() )
        {
            // cannot create a record type if not all element types are known, thus the return
            return;
        }

        expressionTypes.add( namedExpression->type() );
        expressionNames.emplace_back( namedExpression->identifier()->name() );
    }

    const auto recordType =
        libstdhl::Memory::get< libcasm_ir::RecordType >( expressionTypes, expressionNames );
    node.setType( recordType );
}

void TypeInferenceVisitor::visit( LetExpression& node )
{
    if( node.type() )
    {
        return;
    }

    m_typeIDs[ node.expression().get() ] = m_typeIDs[&node ];

    node.variableBindings()->accept( *this );

    node.expression()->accept( *this );

    // revisit the variable bindings to infer again the variable type from underlying let expression
    node.variableBindings()->accept( *this );

    node.setType( node.expression()->type() );
}

void TypeInferenceVisitor::visit( ConditionalExpression& node )
{
    if( node.type() )
    {
        return;
    }

    m_typeIDs[ node.thenExpression().get() ] = m_typeIDs[&node ];
    m_typeIDs[ node.elseExpression().get() ] = m_typeIDs[&node ];

    const auto& condExpr = *node.condition();
    const auto& thenExpr = *node.thenExpression();
    const auto& elseExpr = *node.elseExpression();

    node.thenExpression()->accept( *this );

    if( thenExpr.type() )
    {
        m_typeIDs[&elseExpr ].emplace( thenExpr.type()->id() );
    }

    node.elseExpression()->accept( *this );

    if( elseExpr.type() )
    {
        m_typeIDs[&thenExpr ].emplace( elseExpr.type()->id() );
    }

    node.thenExpression()->accept( *this );

    m_typeIDs[ node.condition().get() ].emplace( libcasm_ir::Type::Kind::BOOLEAN );

    node.condition()->accept( *this );

    checkIfNodeHasTypeOfKind(
        *node.condition(),
        libcasm_ir::Type::Kind::BOOLEAN,
        "condition",
        Code::TypeInferenceInvalidConditionalExpressionCondition );

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
        }
    }

    node.setType( thenExpr.type() );
}

void TypeInferenceVisitor::visit( ChooseExpression& node )
{
    if( node.type() )
    {
        return;
    }

    m_typeIDs[ node.expression().get() ] = m_typeIDs[&node ];

    node.variables()->accept( *this );

    for( const auto& variable : *node.variables() )
    {
        if( variable->type() )
        {
            m_typeIDs[ node.universe().get() ].emplace( variable->type()->id() );
        }
    }

    node.universe()->accept( *this );

    if( node.universe()->type() )
    {
        const auto universeTypeId = node.universe()->type()->ptr_result()->id();
        annotateNodes( *node.variables(), universeTypeId );
    }

    node.variables()->accept( *this );

    node.expression()->accept( *this );

    if( node.universe()->type() )
    {
        for( const auto& variable : *node.variables() )
        {
            if( not variable->type() )
            {
                continue;
            }

            if( *variable->type() != node.universe()->type()->result() )
            {
                m_log.error(
                    { variable->sourceLocation(), node.universe()->sourceLocation() },
                    node.description() + " variable '" + variable->identifier()->name() +
                        "' of type '" + variable->type()->description() +
                        "' does not match the universe of type '" +
                        node.universe()->type()->description() + "'",
                    Code::TypeInferenceInvalidChooseExpressionVariableTypeMismatch );
            }
        }
    }

    node.setType( node.expression()->type() );
}

void TypeInferenceVisitor::visit( UniversalQuantifierExpression& node )
{
    inferenceQuantifierExpression( node );
}

void TypeInferenceVisitor::visit( ExistentialQuantifierExpression& node )
{
    inferenceQuantifierExpression( node );
}

void TypeInferenceVisitor::visit( CardinalityExpression& node )
{
    if( node.type() )
    {
        return;
    }

    RecursiveVisitor::visit( node );

    const std::string description = "cardinality operator";
    if( not node.expression()->type() )
    {
        m_log.error(
            { node.expression()->sourceLocation() },
            "unable to infer expression type of '" + description + "'",
            Code::TypeInferenceCardinalityExpressionHasNoType );
        return;
    }

    // FIXME: TODO: for now we only support IR built-in size calculation
    node.setCardinalityType( CardinalityExpression::CardinalityType::BUILTIN );
    node.setTargetBuiltinId( libcasm_ir::Value::SIZE_BUILTIN );

    // if it is a IR built-in, we can annotate it and due to the annotation, we can infer the
    // resulting type of this expression
    const std::vector< Expression::Ptr > expression = { node.expression() };
    inference( description, annotate( node, expression ), node, expression );

    if( not node.type() )
    {
        return;
    }

    const auto resultType = node.type();
    std::vector< libcasm_ir::Type::Ptr > argumentTypes;
    argumentTypes.emplace_back( node.expression()->type() );

    const auto relationType =
        libstdhl::Memory::make< libcasm_ir::RelationType >( resultType, argumentTypes );

    const auto& annotation = libcasm_ir::Annotation::find( node.targetBuiltinId() );
    if( not annotation.valid( *relationType ) )
    {
        m_log.error(
            { node.sourceLocation() },
            "invalid '" + description + "' type relation '" + relationType->description() +
                "' found'",
            Code::TypeInferenceCardinalityExpressionInvalid );
        return;
    }

    node.setTargetBuiltinType( relationType );
}

void TypeInferenceVisitor::visit( ConditionalRule& node )
{
    m_typeIDs[ node.condition().get() ].emplace( libcasm_ir::Type::Kind::BOOLEAN );

    RecursiveVisitor::visit( node );

    checkIfNodeHasTypeOfKind(
        *node.condition(),
        libcasm_ir::Type::Kind::BOOLEAN,
        "condition",
        Code::TypeInferenceConditionalRuleInvalidConditionType );
}

void TypeInferenceVisitor::visit( WhileRule& node )
{
    m_typeIDs[ node.condition().get() ].emplace( libcasm_ir::Type::Kind::BOOLEAN );

    RecursiveVisitor::visit( node );

    checkIfNodeHasTypeOfKind(
        *node.condition(),
        libcasm_ir::Type::Kind::BOOLEAN,
        "condition",
        Code::TypeInferenceWhileRuleInvalidConditionType );
}

void TypeInferenceVisitor::visit( CaseRule& node )
{
    node.expression()->accept( *this );

    if( node.expression()->type() )
    {
        const auto caseExprTypeID = node.expression()->type()->id();
        annotateNodes( *node.cases(), caseExprTypeID );
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
    node.variableBindings()->accept( *this );

    node.rule()->accept( *this );

    // revisit the variable bindings to infer again the variable type from underlying let rule
    node.variableBindings()->accept( *this );
}

void TypeInferenceVisitor::visit( ForallRule& node )
{
    node.variables()->accept( *this );

    for( const auto& variable : *node.variables() )
    {
        if( variable->type() )
        {
            m_typeIDs[ node.universe().get() ].emplace( variable->type()->id() );
        }
    }

    node.universe()->accept( *this );

    if( node.universe()->type() )
    {
        const auto universeTypeId = node.universe()->type()->ptr_result()->id();
        annotateNodes( *node.variables(), universeTypeId );
    }

    node.variables()->accept( *this );

    m_typeIDs[ node.condition().get() ].emplace( libcasm_ir::Type::Kind::BOOLEAN );

    node.condition()->accept( *this );

    node.rule()->accept( *this );

    if( node.universe()->type() )
    {
        for( const auto& variable : *node.variables() )
        {
            if( not variable->type() )
            {
                continue;
            }

            if( *variable->type() != node.universe()->type()->result() )
            {
                m_log.error(
                    { variable->sourceLocation(), node.universe()->sourceLocation() },
                    node.description() + " variable '" + variable->identifier()->name() +
                        "' of type '" + variable->type()->description() +
                        "' does not match the universe of type '" +
                        node.universe()->type()->description() + "'",
                    Code::TypeInferenceForallRuleTypeMismatch );
            }
        }
    }

    checkIfNodeHasTypeOfKind(
        *node.condition(),
        libcasm_ir::Type::Kind::BOOLEAN,
        "condition",
        Code::TypeInferenceForallRuleInvalidConditionType );
}

void TypeInferenceVisitor::visit( ChooseRule& node )
{
    node.variables()->accept( *this );

    for( const auto& variable : *node.variables() )
    {
        if( variable->type() )
        {
            m_typeIDs[ node.universe().get() ].emplace( variable->type()->id() );
        }
    }

    node.universe()->accept( *this );

    if( node.universe()->type() )
    {
        const auto universeTypeId = node.universe()->type()->ptr_result()->id();
        annotateNodes( *node.variables(), universeTypeId );
    }

    node.variables()->accept( *this );

    node.rule()->accept( *this );

    if( node.universe()->type() )
    {
        for( const auto& variable : *node.variables() )
        {
            if( not variable->type() )
            {
                continue;
            }

            if( *variable->type() != node.universe()->type()->result() )
            {
                m_log.error(
                    { variable->sourceLocation(), node.universe()->sourceLocation() },
                    node.description() + " variable '" + variable->identifier()->name() +
                        "' of type '" + variable->type()->description() +
                        "' does not match the universe of type '" +
                        node.universe()->type()->description() + "'",
                    Code::TypeInferenceInvalidChooseRuleVariableTypeMismatch );
            }
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
        m_typeIDs[&expr ].emplace( func.type()->id() );
    }

    node.expression()->accept( *this );

    assignment(
        func,
        expr,
        "updated function",
        "updating expression",
        Code::TypeInferenceUpdateRuleTypesMismatch );
}

void TypeInferenceVisitor::visit( VariableBinding& node )
{
    node.variable()->accept( *this );

    if( node.variable()->type() )
    {
        const auto variableTypeId = node.variable()->type()->id();
        m_typeIDs[ node.expression().get() ].emplace( variableTypeId );
    }

    node.expression()->accept( *this );

    if( node.expression()->type() )
    {
        const auto expressionTypeId = node.expression()->type()->id();
        m_typeIDs[ node.variable().get() ].emplace( expressionTypeId );
    }

    node.variable()->accept( *this );

    if( node.variable()->type() or node.expression()->type() )
    {
        assignment(
            *node.variable(),
            *node.expression(),
            "variable '" + node.variable()->identifier()->name() + "'",
            "expression",
            Code::TypeInferenceInvalidVariableBindingTypeMismatch );
    }
}

bool TypeInferenceVisitor::tryResolveCallInTypeNamespace( DirectCallExpression& node ) const
{
    if( not node.type() )
    {
        return false;
    }

    const auto& name = node.identifier()->path();
    const auto& typeName = node.type()->description();

    // TODO: this will need some extra care when we add the import feature. (e.g. namespace
    // lookup by type)
    const auto typeNamespace = m_symboltable.findNamespace( typeName );
    if( not typeNamespace )
    {
        return false;
    }

    const auto symbol = typeNamespace->findSymbol( *node.identifier() );
    if( not symbol )
    {
        m_log.error(
            { node.identifier()->sourceLocation() },
            "'" + name + "' has not been defined in namespace '" + typeName + "'",
            Code::SymbolIsUnknown );
        return false;
    }

    std::size_t expectedNumberOfArguments = 0;

    switch( symbol->id() )
    {
        case Node::ID::ENUMERATOR_DEFINITION:
        {
            node.setTargetType( DirectCallExpression::TargetType::CONSTANT );
            break;
        }
        default:
        {
            m_log.error(
                { node.identifier()->sourceLocation() },
                "cannot reference " + symbol->description() + " '" + name + "'" );
            return false;
        }
    }

    if( node.arguments()->size() != expectedNumberOfArguments )
    {
        m_log.error(
            { node.sourceLocation() },
            "invalid argument size: " + symbol->description() + " '" + name + "' expects " +
                std::to_string( expectedNumberOfArguments ) + " arguments",
            Code::SymbolArgumentSizeMismatch );
        return false;
    }

    node.setTargetDefinition( symbol );

    return true;
}

void TypeInferenceVisitor::assignment(
    TypedNode& lhs,
    TypedNode& rhs,
    const std::string& dst,
    const std::string& src,
    const Code assignmentErr )
{
    if( not lhs.type() or not rhs.type() )
    {
        return;
    }

    const auto& tyLhs = *lhs.type();
    const auto& tyRhs = *rhs.type();

    if( tyLhs != tyRhs )
    {
        u1 mismatch = true;
        if( tyLhs.isInteger() and tyRhs.isInteger() )
        {
            // relaxation: mixed integer with range properties are checked
            //             at run-time
            mismatch = false;
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

            if( recordTyLhs.contains( recordTyRhs ) )
            {
                mismatch = false;
            }
        }

        if( mismatch )
        {
            auto lhsSourceLocation = lhs.sourceLocation();

            if( lhs.id() == Node::ID::DIRECT_CALL_EXPRESSION )
            {
                const auto& directCall = static_cast< DirectCallExpression& >( lhs );
                if( directCall.targetType() == DirectCallExpression::TargetType::FUNCTION )
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
        const auto& methodCall = static_cast< MethodCallExpression& >( node );
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

        const auto expectedNumberOfArguments = annotation->relations().front().argument.size();
        if( expressions.size() != expectedNumberOfArguments )
        {
            m_log.error(
                { node.sourceLocation() },
                "invalid argument size: method '" + methodName + "' expects " +
                    std::to_string( expectedNumberOfArguments - 1 ) + " arguments",
                Code::SymbolArgumentSizeMismatch );
            return nullptr;
        }
    }
    else if( node.id() == libcasm_fe::Ast::Type::ID::CARDINALITY_EXPRESSION )
    {
        const auto& cardinalityExpression = static_cast< CardinalityExpression& >( node );

        if( cardinalityExpression.cardinalityType() ==
            CardinalityExpression::CardinalityType::BUILTIN )
        {
            assert( cardinalityExpression.targetBuiltinId() );
            const auto& builtin_annotation =
                libcasm_ir::Annotation::find( cardinalityExpression.targetBuiltinId() );
            annotation = &builtin_annotation;
        }
        else
        {
            return nullptr;
        }
    }
    else
    {
        assert( !"no annotation possible for this node type" );
        return nullptr;
    }

    assert( annotation != nullptr );

    assert( expressions.size() == annotation->relations().front().argument.size() );
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
            argTypes.emplace_back( arguments[ c ]->type() );
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
        }

        if( unknownTypeArgCnt == 0 )
        {
            try
            {
                const auto inferredTypeID = annotation->inference( argTypes, argValues );
                typeIDs = { inferredTypeID };
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

    if( topTypeIDs.size() == 1 and typeIDs.size() == 0 )
    {
        const auto topTypeID = *topTypeIDs.begin();
        node.setType( libcasm_ir::Type::fromID( topTypeID ) );
    }
}

void TypeInferenceVisitor::inferenceQuantifierExpression( QuantifierExpression& node )
{
    if( node.type() )
    {
        return;
    }

    node.predicateVariables()->accept( *this );

    for( const auto& predicateVariable : *node.predicateVariables() )
    {
        if( predicateVariable->type() )
        {
            m_typeIDs[ node.universe().get() ].emplace( predicateVariable->type()->id() );
        }
    }

    node.universe()->accept( *this );

    if( node.universe()->type() )
    {
        const auto universeTypeId = node.universe()->type()->ptr_result()->id();
        annotateNodes( *node.predicateVariables(), universeTypeId );
    }

    node.predicateVariables()->accept( *this );

    m_typeIDs[ node.proposition().get() ].emplace( libcasm_ir::Type::Kind::BOOLEAN );

    node.proposition()->accept( *this );

    if( node.universe()->type() )
    {
        for( const auto& predicateVariable : *node.predicateVariables() )
        {
            if( not predicateVariable->type() )
            {
                continue;
            }

            if( *predicateVariable->type() != node.universe()->type()->result() )
            {
                m_log.error(
                    { predicateVariable->sourceLocation(), node.universe()->sourceLocation() },
                    node.description() + " predicate variable '" +
                        predicateVariable->identifier()->name() + "' of type '" +
                        predicateVariable->type()->description() +
                        "' does not match the universe of type '" +
                        node.universe()->type()->description() + "'",

                    ( node.id() == Node::ID::EXISTENTIAL_QUANTIFIER_EXPRESSION )
                        ? Code::TypeInferenceQuantifierExistentialPredicateTypeMismatch
                        : Code::TypeInferenceQuantifierUniversalPredicateTypeMismatch );
            }
        }
    }

    checkIfNodeHasTypeOfKind(
        *node.proposition(),
        libcasm_ir::Type::Kind::BOOLEAN,
        "proposition",
        ( node.id() == Node::ID::EXISTENTIAL_QUANTIFIER_EXPRESSION )
            ? Code::TypeInferenceQuantifierExistentialPropositionTypeMismatch
            : Code::TypeInferenceQuantifierUniversalPropositionTypeMismatch );

    node.setType( libstdhl::Memory::get< libcasm_ir::BooleanType >() );
}

template < typename T >
void TypeInferenceVisitor::annotateNodes(
    const NodeList< T >& nodes, const libcasm_ir::Type::ID typeId )
{
    for( const auto& node : nodes )
    {
        m_typeIDs[ node.get() ].emplace( typeId );
    }
}

void TypeInferenceVisitor::filterAnnotationsByKind(
    const Node& node, const libcasm_ir::Type::Kind kind )
{
    auto& annotations = m_typeIDs[&node ];

    for( auto it = annotations.begin(); it != annotations.end(); )
    {
        const auto type = libcasm_ir::Type::fromID( *it );
        if( type->kind() != kind )
        {
            it = annotations.erase( it );
        }
        else
        {
            ++it;
        }
    }
}

void TypeInferenceVisitor::checkIfNodeHasTypeOfKind(
    const TypedNode& node,
    const libcasm_ir::Type::Kind expectedKind,
    const std::string& errorDescription,
    const Code errorCode ) const
{
    const auto& actualType = node.type();
    if( actualType )
    {
        if( actualType->kind() != expectedKind )
        {
            m_log.error(
                { node.sourceLocation() },
                errorDescription + " has invalid type '" + actualType->description() +
                    "', expected '" + libcasm_ir::Type::token( expectedKind ) + "'",
                errorCode );
        }
    }
}

class CallTargetCheckVisitor final : public RecursiveVisitor
{
  public:
    CallTargetCheckVisitor( libcasm_fe::Logger& log );

    void visit( DirectCallExpression& node ) override;
    void visit( MethodCallExpression& node ) override;

  private:
    libcasm_fe::Logger& m_log;
};

CallTargetCheckVisitor::CallTargetCheckVisitor( libcasm_fe::Logger& log )
: m_log( log )
{
}

void CallTargetCheckVisitor::visit( DirectCallExpression& node )
{
    if( node.targetType() == DirectCallExpression::TargetType::UNKNOWN )
    {
        m_log.error(
            { node.sourceLocation() },
            "unknown symbol '" + node.identifier()->path() + "' found",
            Code::SymbolIsUnknown );
    }
}

void CallTargetCheckVisitor::visit( MethodCallExpression& node )
{
    if( node.methodType() == MethodCallExpression::MethodType::UNKNOWN )
    {
        m_log.error(
            { node.methodName()->sourceLocation() },
            "unknown method '" + node.methodName()->name() + "' found",
            Code::MethodIsUnknown );
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

    TypeInferenceVisitor typeInferenceVisitor( log, *specification->symboltable() );
    specification->definitions()->accept( typeInferenceVisitor );

    CallTargetCheckVisitor callTargetCheckVisitor( log );
    specification->definitions()->accept( callTargetCheckVisitor );

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
