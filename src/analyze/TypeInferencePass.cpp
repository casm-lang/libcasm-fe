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

#include "TypeInferencePass.h"

#include "../various/GrammarToken.h"

#include <libcasm-fe/Logger>
#include <libcasm-fe/Namespace>
#include <libcasm-fe/Specification>
#include <libcasm-fe/TypeInfo>
#include <libcasm-fe/ast/RecursiveVisitor>
#include <libcasm-fe/import/SpecificationMergerPass>
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
    TypeInferenceVisitor( libcasm_fe::Logger& log, Namespace& symboltable );

    void visit( Initializer& node ) override;

    void visit( InitDefinition& node ) override;
    void visit( VariableDefinition& node ) override;
    void visit( FunctionDefinition& node ) override;
    void visit( DerivedDefinition& node ) override;
    void visit( RuleDefinition& node ) override;
    void visit( InvariantDefinition& node ) override;
    void visit( Declaration& node ) override;

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
    void resolveTypeFeatureSymbol(
        TargetCallExpression& node,
        const std::string& typeName,
        const std::string& featureName,
        const std::string& symbolName,
        const libcasm_ir::Type::Ptr& resultType = nullptr );

    void assignment(
        TypedNode& lhs,
        TypedNode& rhs,
        const std::string& dst,
        const std::string& src,
        const Code assignmentErr );

    void inference(
        const std::string& description,
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
    Namespace& m_symboltable;

    std::unordered_map< const Node*, std::set< libcasm_ir::Type::ID > > m_typeIDs;
};

TypeInferenceVisitor::TypeInferenceVisitor( libcasm_fe::Logger& log, Namespace& symboltable )
: m_log( log )
, m_symboltable( symboltable )
{
}

void TypeInferenceVisitor::visit( Initializer& node )
{
    auto& value = *node.value();
    auto& arguments = *node.arguments();
    auto& function = *node.function();

    function.accept( *this );
    if( not function.type() )
    {
        return;
    }

    const auto& resultType = function.type()->ptr_result();
    const auto& argumentTypes = function.type()->arguments().data();

    if( arguments.size() != argumentTypes.size() )
    {
        m_log.error(
            { arguments.sourceLocation() },
            "invalid number of arguments: function '" + function.identifier()->name() +
                "' expects " + std::to_string( argumentTypes.size() ) + " arguments but " +
                std::to_string( arguments.size() ) + " were given",
            Code::SymbolArgumentSizeMismatch );
        return;
    }

    m_typeIDs[&value ].emplace( resultType->id() );
    for( std::size_t i = 0; i < arguments.size(); i++ )
    {
        m_typeIDs[ arguments.at( i ).get() ].emplace( argumentTypes.at( i )->id() );
    }

    value.accept( *this );
    assignment(
        *function.returnType(),
        value,
        "updated function",
        "updating expression",
        Code::TypeInferenceUpdateRuleTypesMismatch );

    arguments.accept( *this );
    for( std::size_t pos = 0; pos < arguments.size(); pos++ )
    {
        const auto& argument = arguments.at( pos );
        if( not argument->type() )
        {
            continue;
        }

        const auto exprArgType = argument->type();
        const auto callArgType = argumentTypes.at( pos );

        if( *callArgType != *exprArgType )
        {
            if( callArgType->isInteger() and exprArgType->isInteger() )
            {
                argument->setType( callArgType );
                continue;
            }

            m_log.error(
                { argument->sourceLocation() },
                "type mismatch: function argument type at position " + std::to_string( pos + 1 ) +
                    " was '" + exprArgType->description() + "', function definition expects '" +
                    callArgType->description() + "'",
                Code::TypeInferenceFunctionArgumentTypeMismatch );
        }
    }
}

void TypeInferenceVisitor::visit( InitDefinition& node )
{
    RecursiveVisitor::visit( node );
    node.programFunction()->accept( *this );
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
    else if( node.objectDefinition() and node.objectDefinition()->type() )
    {
        node.setType( node.objectDefinition()->type() );
    }

    const auto description = "variable '" + node.identifier()->name() + "'";
    inference( description, node );
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

void TypeInferenceVisitor::visit( Declaration& node )
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
    for( const auto& argument : *node.argumentTypes() )
    {
        assert( argument->type() && "argument type must be specified" );
        argTypeList.emplace_back( argument->type() );
    }

    const auto type = libstdhl::Memory::make< libcasm_ir::RelationType >(
        node.returnType()->type(), argTypeList );
    node.setType( type );
}

void TypeInferenceVisitor::visit( UndefLiteral& node )
{
    RecursiveVisitor::visit( node );
    inference( "undef literal", node );
}

void TypeInferenceVisitor::visit( ReferenceLiteral& node )
{
    if( node.type() )
    {
        return;
    }

    RecursiveVisitor::visit( node );
    inference( "reference literal", node );

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
        inference( "direct call", node );
        if( not tryResolveCallInTypeNamespace( node ) )
        {
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
        case DirectCallExpression::TargetType::BUILTIN:   // [[fallthrough]]
        case DirectCallExpression::TargetType::DERIVED:   // [[fallthrough]]
        case DirectCallExpression::TargetType::FUNCTION:  // [[fallthrough]]
        case DirectCallExpression::TargetType::RULE:      // [[fallthrough]]
        case DirectCallExpression::TargetType::SELF:      // [[fallthrough]]
        case DirectCallExpression::TargetType::THIS:      // [[fallthrough]]
        case DirectCallExpression::TargetType::CONSTANT:  // [[fallthrough]]
        case DirectCallExpression::TargetType::DOMAIN:
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

        if( callArgType->isObject() and not exprArgType->isObject() )
        {
            // OK if argument expression type (not Object) passed to argument call type (Object)
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

    const auto& methodType = node.object()->type()->result().description();

    try
    {
        const auto& nspace = m_symboltable.findNamespace( methodType );
        if( not nspace )
        {
            throw std::domain_error( "invalid type namespace '" + methodType + "'" );
        }

        std::vector< Definition::Ptr > methods = {};
        for( const auto& ns : nspace->namespaces() )
        {
            const auto& symbol = nspace->findNamespace( ns.first )->findSymbol( methodName );
            if( symbol )
            {
                m_log.debug(
                    { node.sourceLocation() },
                    "method found: " + methodType + Namespace::delimiter() + ns.first +
                        Namespace::delimiter() + methodName );
                methods.emplace_back( symbol );
            }
        }

        if( methods.size() == 0 )
        {
            throw std::domain_error(
                "type '" + methodType + "' does not have a method '" + methodName + "'" );
        }

        if( methods.size() > 1 )
        {
            throw std::domain_error(
                "type '" + methodType + "' has more than one method '" + methodName + "'" );
        }

        // nspace->findNamespace( methodType )->findSymbol( methodName );
        const auto& symbol = methods.front();

        switch( symbol->id() )
        {
            case Node::ID::FUNCTION_DEFINITION:
            {
                node.setMethodType( MethodCallExpression::MethodType::FUNCTION );
                break;
            }
            case Node::ID::DERIVED_DEFINITION:
            {
                node.setMethodType( MethodCallExpression::MethodType::DERIVED );
                break;
            }
            case Node::ID::RULE_DEFINITION:
            {
                node.setMethodType( MethodCallExpression::MethodType::RULE );
                break;
            }
            case Node::ID::DECLARATION:
            {
                const auto declaration = std::static_pointer_cast< Declaration >( symbol );
                switch( declaration->kind() )
                {
                    case Declaration::Kind::DERIVED:
                    {
                        node.setMethodType( MethodCallExpression::MethodType::DERIVED );
                        break;
                    }
                    case Declaration::Kind::RULE:
                    {
                        node.setMethodType( MethodCallExpression::MethodType::RULE );
                        break;
                    }
                }
                // validateArgumentsCount( symbol->description(), expectedNumberOfArguments );
                // return;
                break;
            }
            default:
            {
                throw std::domain_error( "invalid symbol '" + symbol->description() + "'" );
                break;
            }
        }

        node.setTargetDefinition( symbol );

        // make sure that the definition has been typed
        const auto& definition = node.targetDefinition();
        assert( definition );
        definition->accept( *this );

        const auto& arguments = *node.arguments();
        const auto& argumentTypes = definition->type()->arguments();
        for( std::size_t i = 0; i < arguments.size(); i++ )
        {
            m_typeIDs[ arguments.at( i ).get() ].emplace( argumentTypes.at( i )->id() );
        }

        node.setType( definition->type()->ptr_result() );
    }
    catch( const std::domain_error& e )
    {
        m_log.error(
            { node.sourceLocation() },
            "type '" + methodType + "' does not have a symbol '" + methodName + "': " + e.what() );
    }

    RecursiveVisitor::visit( node );
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

    const std::string description = "'as' operator";
    if( not node.fromExpression()->type() )
    {
        m_log.error(
            { node.fromExpression()->sourceLocation() },
            "unable to infer expression type of " + description,
            Code::TypeInferenceTypeCastingExpressionFromHasNoType );
    }

    if( not node.fromExpression()->type() or not node.asType()->type() )
    {
        return;
    }

    const auto& resultType = node.asType()->type();
    const auto& resultTypeName = resultType->description();
    const auto& expressionType = node.fromExpression()->type();
    const auto& expressionTypeName = expressionType->description();

    const auto& typeName = expressionTypeName;
    const auto& featureName = "TypeCasting" + resultTypeName;
    const auto& symbolName = "to" + resultTypeName;

    try
    {
        resolveTypeFeatureSymbol( node, typeName, featureName, symbolName, resultType );
    }
    catch( const std::domain_error& e )
    {
        m_log.error(
            { node.sourceLocation() },
            "invalid " + description + ", because " + std::string( e.what() ),
            Code::TypeInferenceInvalidTypeCastingExpression );
    }
}

void TypeInferenceVisitor::visit( UnaryExpression& node )
{
    RecursiveVisitor::visit( node );

    const auto& operationToken = *node.operationToken();
    const auto& operationTokenName = operationToken.tokenString();
    const auto& description = "unary operator '" + operationTokenName + "'";

    const auto& expression = node.expression();
    inference( description, node, { expression } );

    if( not expression->type() )
    {
        m_log.error(
            { expression->sourceLocation() },
            "unable to infer expression type of " + description,
            Code::TypeInferenceTypeCastingExpressionFromHasNoType );
        return;
    }

    const auto& expressionType = expression->type();
    const auto& expressionTypeName = expressionType->description();

    static const std::unordered_map< std::string, std::pair< std::string, std::string > >
        featureToSymbol = {
            { Grammar::tokenAsString( Grammar::Token::PLUS ), { "Positive", "sign" } },
            { Grammar::tokenAsString( Grammar::Token::MINUS ), { "Inversion", "invert" } },
            { Grammar::tokenAsString( Grammar::Token::NOT ), { "Negation", "negate" } },
        };

    const auto operation = featureToSymbol.find( operationTokenName );
    if( operation == featureToSymbol.end() )
    {
        m_log.error(
            { node.sourceLocation() },
            "unimplemented " + description + " type inference mapping",
            Code::Unspecified );
        return;
    }

    const auto& typeName = expressionTypeName;
    const auto& featureName = operation->second.first;
    const auto& symbolName = operation->second.second;

    try
    {
        resolveTypeFeatureSymbol( node, typeName, featureName, symbolName );
    }
    catch( const std::domain_error& e )
    {
        m_log.error(
            { node.sourceLocation() },
            "invalid " + description + ", because " + std::string( e.what() ),
            Code::Unspecified );
    }
}

void TypeInferenceVisitor::visit( BinaryExpression& node )
{
    RecursiveVisitor::visit( node );

    if( node.left()->type() )
    {
        m_typeIDs[ node.right().get() ].emplace( node.left()->type()->id() );
    }

    if( node.right()->type() )
    {
        m_typeIDs[ node.left().get() ].emplace( node.right()->type()->id() );
    }

    RecursiveVisitor::visit( node );

    const auto& operationToken = *node.operationToken();
    const auto& operationTokenName = operationToken.tokenString();
    const auto& description = "binary operator '" + operationTokenName + "'";

    const auto& lhsExpression = node.left();
    const auto& rhsExpression = node.right();
    inference( description, node, { lhsExpression, rhsExpression } );

    if( not lhsExpression->type() )
    {
        m_log.error(
            { lhsExpression->sourceLocation() },
            "unable to infer left expression type of " + description,
            Code::Unspecified );
    }

    if( not rhsExpression->type() )
    {
        m_log.error(
            { rhsExpression->sourceLocation() },
            "unable to infer right expression type of " + description,
            Code::Unspecified );
    }

    if( not lhsExpression->type() or not rhsExpression->type() )
    {
        return;
    }

    const auto& lhsType = lhsExpression->type();
    const auto& lhsTypeName = lhsType->description();
    const auto& rhsType = rhsExpression->type();
    const auto& rhsTypeName = rhsType->description();

    static const std::unordered_map< std::string, std::pair< std::string, std::string > >
        featureToSymbol = {
            { Grammar::tokenAsString( Grammar::Token::PLUS ), { "Addition", "add" } },
            { Grammar::tokenAsString( Grammar::Token::MINUS ), { "Subtraction", "subtract" } },
            { Grammar::tokenAsString( Grammar::Token::ASTERIX ), { "Multiplication", "multiply" } },
            { Grammar::tokenAsString( Grammar::Token::SLASH ), { "Division", "divide" } },
            { Grammar::tokenAsString( Grammar::Token::PERCENT ), { "Modulus", "modulo" } },
            { Grammar::tokenAsString( Grammar::Token::CARET ), { "Exponentiation", "power" } },
            { Grammar::tokenAsString( Grammar::Token::EQUAL ), { "Equality", "equal" } },
            { Grammar::tokenAsString( Grammar::Token::NEQUAL ), { "Equality", "unequal" } },
            { Grammar::tokenAsString( Grammar::Token::LESSER ), { "PartialOrder", "lessThan" } },
            { Grammar::tokenAsString( Grammar::Token::GREATER ),
              { "PartialOrder", "greaterThan" } },
            { Grammar::tokenAsString( Grammar::Token::LESSEQ ),
              { "TotalOrder", "lessThanOrEqual" } },
            { Grammar::tokenAsString( Grammar::Token::GREATEREQ ),
              { "TotalOrder", "greaterThanOrEqual" } },
            { Grammar::tokenAsString( Grammar::Token::OR ), { "Logical", "or_" } },
            { Grammar::tokenAsString( Grammar::Token::XOR ), { "Logical", "xor_" } },
            { Grammar::tokenAsString( Grammar::Token::AND ), { "Logical", "and_" } },
            { Grammar::tokenAsString( Grammar::Token::ARROW ), { "Logical", "implies_" } },
            { Grammar::tokenAsString( Grammar::Token::IMPLIES ), { "Logical", "implies_" } },
        };

    const auto operation = featureToSymbol.find( operationTokenName );
    if( operation == featureToSymbol.end() )
    {
        m_log.error(
            { node.sourceLocation() },
            "unimplemented " + description + " type inference mapping",
            Code::Unspecified );
        return;
    }

    const auto& typeName = lhsTypeName;
    const auto& featureName = operation->second.first;
    const auto& symbolName = operation->second.second;

    try
    {
        resolveTypeFeatureSymbol( node, typeName, featureName, symbolName );
    }
    catch( const std::domain_error& e )
    {
        m_log.error(
            { node.sourceLocation() },
            "invalid " + description + ", because " + std::string( e.what() ),
            Code::Unspecified );
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

    inference( "list literal", node );
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
            "unable to infer expression type of " + description,
            Code::TypeInferenceCardinalityExpressionHasNoType );
        return;
    }

    const auto& expressionType = node.expression()->type();
    const auto& expressionTypeName = expressionType->description();

    const auto& typeName = expressionTypeName;
    const auto& featureName = "Cardinality";
    const auto& symbolName = "size";

    try
    {
        resolveTypeFeatureSymbol( node, typeName, featureName, symbolName );
    }
    catch( const std::domain_error& e )
    {
        m_log.error(
            { node.sourceLocation() },
            "invalid " + description + ", because " + std::string( e.what() ),
            Code::TypeInferenceCardinalityExpressionInvalid );
    }
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
    m_log.info(
        { node.sourceLocation() }, node.identifier()->path() + " @ " + node.targetTypeName() );

    if( not node.type() )
    {
        return false;
    }

    const auto& name = node.identifier()->path();
    const auto& typeName = node.type()->description();

    m_log.info( { node.sourceLocation() }, name + " & " + typeName );

    // TODO: this will need some extra care when we add the import feature. (e.g. namespace
    // lookup by type)
    const auto typeNamespace = m_symboltable.findNamespace( typeName );
    if( not typeNamespace )
    {
        m_log.error(
            { node.sourceLocation() },
            "'" + node.identifier()->path() + "' is unknown",
            Code::SymbolIsUnknown );

        return false;
    }

    const auto maybeSymbol = typeNamespace->findSymbol( *node.identifier() );
    const auto symbol = maybeSymbol.first;
    const auto accessible = maybeSymbol.second;

    if( not symbol )
    {
        m_log.error(
            { node.identifier()->sourceLocation() },
            "'" + name + "' has not been defined in namespace '" + typeName + "'",
            Code::SymbolIsUnknown );
        return false;
    }
    else if( not accessible )
    {
        m_log.error(
            { node.identifier()->sourceLocation() },
            "'" + name + "' is not accessible in namespace '" + typeName + "'",
            Code::SymbolIsInaccessible );
        m_log.warning(
            { symbol->sourceLocation() },
            "'" + symbol->identifier()->name() + "' has not been exported" );
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

void TypeInferenceVisitor::resolveTypeFeatureSymbol(
    TargetCallExpression& node,
    const std::string& typeName,
    const std::string& featureName,
    const std::string& symbolName,
    const libcasm_ir::Type::Ptr& resultType )
{
    const auto typeNamespace = m_symboltable.findNamespace( typeName );
    if( not typeNamespace )
    {
        throw std::domain_error( "the type '" + typeName + "' is unknown" );
    }

    const auto featureNamespace = typeNamespace->findNamespace( featureName );
    if( not featureNamespace )
    {
        throw std::domain_error(
            "the feature 'CASM::" + featureName + "' is not implemented for type '" + typeName +
            "'" );
    }

    const auto symbol = featureNamespace->findSymbol( symbolName );
    if( not symbol )
    {
        throw std::domain_error(
            "the method '" + symbolName + "' is not defined in the namespace '" + featureName +
            "'" );
    }

    if( not symbol->type() )
    {
        symbol->accept( *this );
    }

    const auto& symbolType = symbol->type();
    const auto returnType = ( resultType ? resultType : symbolType->ptr_result() );

    std::vector< libcasm_ir::Type::Ptr > argumentTypes;
    for( const auto& expression : *node.arguments() )
    {
        argumentTypes.emplace_back( expression->type()->ptr_result() );
    }
    const auto relationType =
        libstdhl::Memory::make< libcasm_ir::RelationType >( returnType, argumentTypes );

    if( *symbolType != *relationType )
    {
        const auto& symbolArgumentTypes = symbolType->arguments();
        const auto& relationArgumentTypes = relationType->arguments();

        u1 valid = true;
        for( std::size_t i = 0; i < symbolArgumentTypes.size(); i++ )
        {
            const auto& symbolArgumentType = symbolArgumentTypes[ i ];
            const auto& relationArgumentType = relationArgumentTypes[ i ];
            if( relationArgumentType->isEnumeration() and symbolArgumentType->isObject() )
            {
                continue;
            }

            if( symbolArgumentType != relationArgumentType )
            {
                valid = false;
                break;
            }
        }

        if( not valid )
        {
            const auto msg = "use: '" + relationType->description() + ", def: '" +
                             symbolType->description() + "'";
            m_log.info( { symbol->sourceLocation() }, msg );
            throw std::domain_error( msg );
        }
    }

    node.setTargetDefinition( symbol );
    node.setType( relationType->ptr_result() );
}

void TypeInferenceVisitor::inference(
    const std::string& description,
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
    pu.require< SpecificationMergerPass >();
}

u1 TypeInferencePass::run( libpass::PassResult& pr )
{
    libcasm_fe::Logger log( &id, stream() );

    const auto data = pr.output< SpecificationMergerPass >();
    const auto specification = data->specification();

    TypeInferenceVisitor typeInferenceVisitor( log, *specification->symboltable() );
    specification->definitions()->accept( typeInferenceVisitor );

#ifndef NDEBUG
    log.debug( "symbol table = \n" + specification->symboltable()->dump() );
#endif

#ifndef NDEBUG
    log.debug( "symbol table = \n" + specification->symboltable()->dump() );
#endif

    const auto errors = log.errors();
    if( errors > 0 )
    {
        log.debug( "found %lu error(s) during type inference", errors );
        return false;
    }

    CallTargetCheckVisitor callTargetCheckVisitor( log );
    specification->definitions()->accept( callTargetCheckVisitor );

    const auto checkErrors = log.errors();
    if( checkErrors > 0 )
    {
        log.debug( "found %lu error(s) during call target checks", checkErrors );
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
