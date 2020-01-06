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
#include <libcasm-fe/analyze/SymbolRegistrationPass>
#include <libcasm-fe/analyze/SymbolResolverPass>
#include <libcasm-fe/analyze/TypeCheckPass>
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

    void visit( VariableDefinition& node ) override;
    void visit( FunctionDefinition& node ) override;
    void visit( DerivedDefinition& node ) override;
    void visit( RuleDefinition& node ) override;
    void visit( EnumerationDefinition& node ) override;
    void visit( BuiltinDefinition& node ) override;
    void visit( DomainDefinition& node ) override;
    void visit( StructureDefinition& node ) override;
    void visit( BehaviorDefinition& node ) override;
    void visit( ImplementDefinition& node ) override;
    void visit( Declaration& node ) override;
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

    void visit( BasicType& node ) override;
    void visit( TupleType& node ) override;
    void visit( RecordType& node ) override;
    void visit( FixedSizedType& node ) override;
    void visit( TemplateType& node ) override;
    void visit( RelationType& node ) override;

    void visit( VariableBinding& node ) override;

  private:
    void resolveDomainTypeBehaviorImplementSymbol(
        TargetCallExpression& node,
        const libcasm_ir::Type::Ptr& domainType,
        const Ast::Type::Ptr& behaviorType,
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
        Removes all annotations of \a node from m_typeIDs which are not of kind \a kind.
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

void TypeInferenceVisitor::visit( VariableDefinition& node )
{
    if( node.type() and node.type()->isObject() )
    {
        node.setType( nullptr );
    }

    if( node.type() )
    {
        return;
    }

    const auto description = "variable '" + node.identifier()->name() + "'";
    inference( description, node );

    RecursiveVisitor::visit( node );

    if( node.variableType()->type() )
    {
        node.setType( node.variableType()->type() );
    }
    else if( node.objectDefinition() and node.objectDefinition()->type() )
    {
        node.setType( node.objectDefinition()->type() );
    }
}

void TypeInferenceVisitor::visit( FunctionDefinition& node )
{
    assert( node.type() and " inconsistent state @ TypeCheckPass " );

    const auto& expression = node.defined()->expression();
    const auto& returnType = node.returnType();

    // annotate the function defined expression (default) with the return type information
    m_typeIDs[ expression.get() ].emplace( returnType->type()->id() );

    // infer type of expression
    expression->accept( *this );
    node.initially()->accept( *this );

    if( expression->type() and expression->type() != returnType->type() )
    {
        if( expression->type()->isInteger() == returnType->type()->isInteger() )
        {
            // relax passing expression Integer'[a..b] to Integer
            return;
        }

        const std::string msg = "type mismatch: result type was '" +
                                expression->type()->description() + "', but " + node.description() +
                                " expects '" + returnType->type()->description() + "'";
        m_log.error(
            { expression->sourceLocation() },
            msg,
            Code::TypeInferenceFunctionDefaultValueTypeMismatch );
        m_log.info( { returnType->sourceLocation() }, msg );
    }
}

void TypeInferenceVisitor::visit( DerivedDefinition& node )
{
    assert( node.type() and " inconsistent state @ TypeCheckPass " );

    const auto& expression = node.expression();
    const auto& returnType = node.returnType();

    // annotate the derived expression with the return type information
    m_typeIDs[ expression.get() ].emplace( returnType->type()->id() );

    // infer type of expression
    expression->accept( *this );

    if( expression->type() and expression->type() != returnType->type() )
    {
        if( expression->type()->isInteger() == returnType->type()->isInteger() )
        {
            // relax passing expression Integer'[a..b] to Integer
            return;
        }

        const std::string msg = "type mismatch: result type was '" +
                                expression->type()->description() + "', but " + node.description() +
                                " expects '" + returnType->type()->description() + "'";
        m_log.error(
            { expression->sourceLocation() }, msg, Code::TypeInferenceDerivedReturnTypeMismatch );
        m_log.info( { returnType->sourceLocation() }, msg );
    }
}

void TypeInferenceVisitor::visit( RuleDefinition& node )
{
    assert( node.type() and " inconsistent state @ TypeCheckPass " );

    RecursiveVisitor::visit( node );
}

void TypeInferenceVisitor::visit( EnumerationDefinition& node )
{
    for( const auto& templateInstance : *node.templateInstances() )
    {
        assert( templateInstance->id() == Node::ID::ENUMERATION_DEFINITION );
        const auto& templateDefinition = templateInstance->ptr< EnumerationDefinition >();
        templateDefinition->accept( *this );
    }

    assert( node.type() and " inconsistent state @ TypeCheckPass " );

    node.templateInstances()->accept( *this );
}

void TypeInferenceVisitor::visit( BuiltinDefinition& node )
{
    assert( node.type() and " inconsistent state @ TypeCheckPass " );

    RecursiveVisitor::visit( node );
}

void TypeInferenceVisitor::visit( DomainDefinition& node )
{
    assert( node.type() and " inconsistent state @ TypeCheckPass " );

    RecursiveVisitor::visit( node );
}

void TypeInferenceVisitor::visit( StructureDefinition& node )
{
    assert( node.type() and " inconsistent state @ TypeCheckPass " );

    RecursiveVisitor::visit( node );
}

void TypeInferenceVisitor::visit( BehaviorDefinition& node )
{
    assert( node.type() and " inconsistent state @ TypeCheckPass " );

    RecursiveVisitor::visit( node );
}

void TypeInferenceVisitor::visit( ImplementDefinition& node )
{
    assert( node.type() and " inconsistent state @ TypeCheckPass " );

    RecursiveVisitor::visit( node );
}

void TypeInferenceVisitor::visit( Declaration& node )
{
    assert( node.type() and " inconsistent state @ TypeCheckPass " );

    RecursiveVisitor::visit( node );
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
            assert( node.reference()->type() and " inconsistent state @ TypeCheckPass " );
            const auto type = libstdhl::Memory::make< libcasm_ir::FunctionReferenceType >(
                std::static_pointer_cast< libcasm_ir::RelationType >( node.reference()->type() ) );
            node.setType( type );
            break;
        }
        case ReferenceLiteral::ReferenceType::RULE:
        {
            assert( node.reference()->type() and " inconsistent state @ TypeCheckPass " );
            const auto type = libstdhl::Memory::make< libcasm_ir::RuleReferenceType >(
                std::static_pointer_cast< libcasm_ir::RelationType >( node.reference()->type() ) );
            node.setType( type );
            break;
        }
        case ReferenceLiteral::ReferenceType::UNKNOWN:
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
    assert(
        node.targetType() != DirectCallExpression::TargetType::UNKNOWN and
        " inconsistent state @ SymbolResolverPass " );

    const auto& symbolPath = node.identifier();
    const auto& symbolName = symbolPath->path();

    const auto& symbol = node.targetDefinition();
    assert( symbol and " inconsistent state @ SymbolResolverPass " );

    auto& arguments = *node.arguments();
    std::vector< libcasm_ir::Type::Ptr > argumentTypes;

    switch( node.targetType() )
    {
        case DirectCallExpression::TargetType::RULE:      // [[fallthrough]]
        case DirectCallExpression::TargetType::DERIVED:   // [[fallthrough]]
        case DirectCallExpression::TargetType::FUNCTION:  // [[fallthrough]]
        case DirectCallExpression::TargetType::BUILTIN:   // [[fallthrough]]
        case DirectCallExpression::TargetType::DOMAIN:
        {
            break;
        }
        case DirectCallExpression::TargetType::THIS:      // [[fallthrough]]
        case DirectCallExpression::TargetType::CONSTANT:  // [[fallthrough]]
        case DirectCallExpression::TargetType::VARIABLE:
        {
            symbol->accept( *this );
            node.setType( symbol->type() );
            return;
        }
        case DirectCallExpression::TargetType::UNKNOWN:
        {
            m_log.error(
                { node.sourceLocation() },
                "unimplemented " + node.description() + " symbol '" + symbolName +
                    "' found of target type " + node.targetTypeName() );
            return;
        }
    }

    assert( symbol->type() and " inconsistent state @ TypeCheckPass " );

    // annotate type information to arguments
    argumentTypes = symbol->type()->arguments().data();
    for( std::size_t i = 0; i < arguments.size(); i++ )
    {
        m_typeIDs[ arguments.at( i ).get() ].emplace( argumentTypes.at( i )->id() );
    }

    // infer argument types
    arguments.accept( *this );

    assert( node.type() and " inconsistent state @ TypeCheckPass " );
    assert(
        *node.type() == *symbol->type()->ptr_result() and " inconsistent state @ TypeCheckPass " );
    m_typeIDs[&node ].emplace( node.type()->id() );

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

        if( node.targetType() == DirectCallExpression::TargetType::BUILTIN )
        {
            if( ( not exprArgType->isObject() ) and callArgType->isObject() )
            {
                // relaxing: OK if argument expression concrete type (not Object) passed to argument
                // call generic type (Object)
                continue;
            }

            if( exprArgType->isObject() and callArgType->isReference() )
            {
                // relaxing: OK if argument expression generic type (Object) and passed to argument
                // call {Rule,Func}Ref type
                continue;
            }

            if( ( exprArgType->isObject() and
                  exprArgType->description() == TypeInfo::TYPE_NAME_ENUMERATION ) and
                callArgType->isObject() )
            {
                // relaxing: OK if argument expression 'enumeration' type (Object) passed to
                // argument call generic type (Object)
                continue;
            }
        }

        if( callArgType->isInteger() and exprArgType->isInteger() )
        {
            // relaxing: OK, if arguments are integer and/or integer ranged types
            continue;
        }

        if( *exprArgType != *callArgType )
        {
            const std::unordered_map< DirectCallExpression::TargetType, Code > codes = {
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
            assert( code != codes.end() and " inconsistent state @ target type with arguments " );

            const std::string msg =
                "type mismatch: " + node.targetTypeName() + " argument type at position " +
                std::to_string( pos + 1 ) + " was '" + exprArgType->description() + "', " +
                node.targetTypeName() + " definition expects '" + callArgType->description() + "'";
            m_log.error( { exprArg->sourceLocation() }, msg, code->second );
            m_log.info( { symbol->sourceLocation() }, msg );
        }
    }
}

void TypeInferenceVisitor::visit( MethodCallExpression& node )
{
    const std::string description = "'.' operator";
    const auto& sourceLocation = node.sourceLocation();
    const auto& methodName = node.methodName()->name();

    if( node.type() )
    {
        m_log.debug(
            { sourceLocation },
            "found inferred " + node.description() + " '" + methodName + "' with type '" +
                node.type()->description() + "' " );
        return;
    }

    node.arguments()->accept( *this );  // include object at first position

    if( not node.object()->type() )
    {
        // the object type is essential to resolve the method
        m_log.error(
            { sourceLocation },
            "unable to resolve object type",
            Code::TypeInferenceInvalidMethodCallExpression );
        return;
    }

    const auto& objectType = node.object()->type();
    const auto& objectTypeDefinition = m_symboltable.findTypeDefinition( objectType->id() );
    assert( objectTypeDefinition and " inconsistent state @ TypeCheckPass " );
    const auto& objectTypeName = objectTypeDefinition->domainType()->signature();
    const auto& objectTypePath = objectTypeDefinition->domainType()->signaturePath();

    const auto& objectTypeNamespace = m_symboltable.findNamespace( *objectTypePath );
    if( not objectTypeNamespace )
    {
        m_log.error(
            { sourceLocation },
            "type '" + objectTypeName + "' does not have a symbol '" + methodName + "'",
            Code::Unspecified );
        return;
    }

    u1 structureMember = false;
    if( objectTypeDefinition->id() == Node::ID::STRUCTURE_DEFINITION )
    {
        const auto& symbol = objectTypeNamespace->findSymbol( methodName );
        if( symbol )
        {
            m_log.debug(
                { sourceLocation },
                "method found: " + objectTypeName + Namespace::delimiter() + methodName );
            structureMember = true;
        }
    }

    Ast::Type::Ptr behaviorType = nullptr;
    if( not structureMember )
    {
        std::vector< TypeDefinition::Ptr > behaviors = {};
        for( const auto& inner : objectTypeNamespace->symbols() )
        {
            const auto& innerName = inner.first;
            const auto& innerSymbol = objectTypeNamespace->findSymbol( innerName );
            assert( innerSymbol and " inconsistent state " );

            if( innerSymbol->id() != Node::ID::BEHAVIOR_DEFINITION and
                innerSymbol->id() != Node::ID::IMPLEMENT_DEFINITION )
            {
                continue;
            }

            const auto& innerDefinition = innerSymbol->ptr< TypeDefinition >();
            const auto& innerPath = innerDefinition->domainType()->signaturePath();
            const auto& innerNamespace = objectTypeNamespace->findNamespace( *innerPath );
            if( not innerNamespace )
            {
                continue;
            }
            assert( innerNamespace and " inconsistent state " );

            const auto& symbol = innerNamespace->findSymbol( methodName );
            if( symbol )
            {
                m_log.debug(
                    { sourceLocation },
                    "method found: " + objectTypeName + Namespace::delimiter() + innerName +
                        Namespace::delimiter() + methodName );
                behaviors.emplace_back( innerDefinition );
            }
        }

        if( behaviors.size() == 0 )
        {
            m_log.error(
                { sourceLocation },
                "type '" + objectTypeName + "' does not have a method '" + methodName + "'",
                Code::Unspecified );
            return;
        }

        if( behaviors.size() > 1 )
        {
            m_log.error(
                { sourceLocation },
                "type '" + objectTypeName + "' does have multiple methods '" + methodName + "'",
                Code::Unspecified );
            return;
        }

        behaviorType = behaviors.front()->domainType();
    }

    try
    {
        resolveDomainTypeBehaviorImplementSymbol( node, objectType, behaviorType, methodName );
    }
    catch( const std::domain_error& e )
    {
        m_log.error(
            { sourceLocation },
            "invalid " + description + ", because " + std::string( e.what() ),
            Code::Unspecified );
        return;
    }

    const auto& symbol = node.targetDefinition();
    assert( symbol and " inconsistent state " );

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
            const auto& declaration = static_cast< const Declaration& >( *symbol );
            switch( declaration.kind() )
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
            break;
        }
        default:
        {
            m_log.error(
                { sourceLocation },
                "invalid symbol '" + symbol->description() + "'",
                Code::Unspecified );
            break;
        }
    }
}

void TypeInferenceVisitor::visit( LiteralCallExpression& node )
{
    const std::string description = "'.' operator";

    node.object()->accept( *this );
    const auto& objectType = node.object()->type();
    if( not objectType )
    {
        // the object type is essential to resolve the literal access
        m_log.error(
            { node.object()->sourceLocation() },
            "unable to infer object type of " + description,
            Code::TypeInferenceInvalidLiteralCallExpression );
    }

    node.literal()->accept( *this );

    const auto& literalType = node.literal()->type();
    if( not literalType )
    {
        m_log.error(
            { node.literal()->sourceLocation() },
            "unable to infer literal type of " + description,
            Code::TypeInferenceInvalidLiteralCallExpression );
    }

    if( not objectType or not literalType )
    {
        return;
    }

    const auto& sourceLocation = node.sourceLocation();
    const auto& expressionType = node.object()->type();

    const auto& behaviorType = Ast::make< TemplateType >(
        sourceLocation,
        IdentifierPath::fromIdentifier(
            Ast::make< Identifier >( sourceLocation, "ElementAccess" ) ),
        Token::unresolved(),
        std::make_shared< Types >(),
        Token::unresolved() );

    const auto& symbolName = "at";

    assert(
        node.literal()->id() == Node::ID::VALUE_LITERAL and
        " inconsistent state @ GrammarParser " );
    assert( literalType->isInteger() and " inconsistent state @ TypeCheckPass " );
    const auto& literal = static_cast< const ValueLiteral& >( *node.literal() );
    const auto& index = std::static_pointer_cast< libcasm_ir::IntegerConstant >( literal.value() );

    const auto& objectTypeDefinition = m_symboltable.findTypeDefinition( objectType->id() );
    assert( objectTypeDefinition and " inconsistent state @ TypeCheckPass " );

    if( objectTypeDefinition->domainType()->id() == Node::ID::TUPLE_TYPE )
    {
        const auto& tupleTypeDefinition =
            static_cast< const TupleType& >( *objectTypeDefinition->domainType() );

        if( index->value() < 0 or index->value() > tupleTypeDefinition.subTypes()->size() )
        {
            m_log.error(
                { sourceLocation, tupleTypeDefinition.sourceLocation() },
                "unable to infer " + description + ", because " +
                    tupleTypeDefinition.description() + " has only " +
                    std::to_string( tupleTypeDefinition.subTypes()->size() ) +
                    " elements and the index is " + index->toString(),
                Code::TypeInferenceInvalidLiteralCallExpression );
            return;
        }

        behaviorType->subTypes()->add(
            ( *tupleTypeDefinition.subTypes() )[ index->value_i64() - 1 ] );
    }
    else
    {
        m_log.error(
            { sourceLocation, objectTypeDefinition->sourceLocation() },
            "unimplemented literal call for '" + objectTypeDefinition->typeDescription() +
                "' and index " + index->toString(),
            Code::TypeInferenceInvalidLiteralCallExpression );
        return;
    }

    try
    {
        resolveDomainTypeBehaviorImplementSymbol( node, expressionType, behaviorType, symbolName );
    }
    catch( const std::domain_error& e )
    {
        m_log.error(
            { sourceLocation },
            "invalid " + description + ", because " + std::string( e.what() ),
            Code::Unspecified );
    }
}

void TypeInferenceVisitor::visit( IndirectCallExpression& node )
{
    RecursiveVisitor::visit( node );
    m_log.error(
        { node.sourceLocation() },
        "UNIMPLEMENTED " + node.description() +
            " current type: " + ( node.type() ? node.type()->description() : "$unresolved$" ) );

    // RecursiveVisitor::visit( node );

    // const auto& expressionType = node.expression()->type();

    // if( not expressionType )
    // {
    //     m_log.error(
    //         { node.expression()->sourceLocation() },
    //         "unable to resolve type of indirect call expression" );
    //     return;
    // }

    // if( not expressionType->isReference() )
    // {
    //     m_log.error(
    //         { node.expression()->sourceLocation() },
    //         "expression is not a reference",
    //         Code::TypeInferenceInvalidIndirectCallExpression );
    //     return;
    // }

    // const auto& refType = std::static_pointer_cast< libcasm_ir::ReferenceType >( expressionType
    // ); node.setType( refType->dereference() );
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

    const auto& sourceLocation = node.sourceLocation();
    const auto& expressionType = node.fromExpression()->type();

    const auto& behaviorType = Ast::make< TemplateType >(
        sourceLocation,
        IdentifierPath::fromIdentifier( Ast::make< Identifier >( sourceLocation, "TypeCasting" ) ),
        Token::unresolved(),
        std::make_shared< Types >(),
        Token::unresolved() );

    const auto& resultTypeDefinition =
        m_symboltable.findTypeDefinition( node.asType()->type()->id() );
    assert( resultTypeDefinition and " inconsistent state " );
    behaviorType->subTypes()->add( node.asType() );

    const auto& symbolName = "convertTo";
    const auto& resultType = node.asType()->type();

    try
    {
        resolveDomainTypeBehaviorImplementSymbol(
            node, expressionType, behaviorType, symbolName, resultType );
    }
    catch( const std::domain_error& e )
    {
        m_log.error(
            { sourceLocation },
            "invalid " + description + ", because " + std::string( e.what() ),
            Code::TypeInferenceInvalidTypeCastingExpression );
    }
}

void TypeInferenceVisitor::visit( UnaryExpression& node )
{
    const auto& operationToken = *node.operationToken();
    const auto& operationTokenName = operationToken.tokenString();
    const auto& description = "unary operator '" + operationTokenName + "'";
    const auto& expression = node.expression();

    RecursiveVisitor::visit( node );

    if( node.type() )
    {
        return;
    }

    if( node.expression()->type() )
    {
        m_typeIDs[ node.expression().get() ].emplace( node.expression()->type()->id() );
    }

    inference( description, node, { expression } );

    if( not expression->type() )
    {
        m_log.error(
            { expression->sourceLocation() },
            "unable to infer expression type of " + description,
            Code::TypeInferenceTypeCastingExpressionFromHasNoType );
        return;
    }

    static const std::unordered_map< std::string, std::pair< std::string, std::string > >
        behaviorToSymbol = {
            { Grammar::tokenAsString( Grammar::Token::PLUS ), { "Positive", "sign" } },
            { Grammar::tokenAsString( Grammar::Token::MINUS ), { "Inversion", "invert" } },
            { Grammar::tokenAsString( Grammar::Token::NOT ), { "Negation", "negate" } },
        };

    const auto operation = behaviorToSymbol.find( operationTokenName );
    if( operation == behaviorToSymbol.end() )
    {
        m_log.error(
            { node.sourceLocation() },
            "unimplemented " + description + " type inference mapping",
            Code::Unspecified );
        return;
    }

    const auto& sourceLocation = node.sourceLocation();
    const auto& expressionType = expression->type();

    const auto& behaviorType = Ast::make< BasicType >(
        sourceLocation,
        IdentifierPath::fromIdentifier(
            Ast::make< Identifier >( sourceLocation, operation->second.first ) ) );

    const auto& symbolName = operation->second.second;

    try
    {
        resolveDomainTypeBehaviorImplementSymbol( node, expressionType, behaviorType, symbolName );
    }
    catch( const std::domain_error& e )
    {
        m_log.error(
            { sourceLocation },
            "invalid " + description + ", because " + std::string( e.what() ),
            Code::Unspecified );
    }
}

void TypeInferenceVisitor::visit( BinaryExpression& node )
{
    const auto& operationToken = *node.operationToken();
    const auto& operationTokenName = operationToken.tokenString();
    const auto& description = "binary operator '" + operationTokenName + "'";
    const auto& lhsExpression = node.left();
    const auto& rhsExpression = node.right();

    RecursiveVisitor::visit( node );

    if( node.type() )
    {
        return;
    }

    if( node.left()->type() )
    {
        m_typeIDs[ node.right().get() ].emplace( node.left()->type()->id() );
    }

    if( node.right()->type() )
    {
        m_typeIDs[ node.left().get() ].emplace( node.right()->type()->id() );
    }

    RecursiveVisitor::visit( node );

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

    static const std::unordered_map< std::string, std::pair< std::string, std::string > >
        behaviorToSymbol = {
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

    const auto operation = behaviorToSymbol.find( operationTokenName );
    if( operation == behaviorToSymbol.end() )
    {
        m_log.error(
            { node.sourceLocation() },
            "unimplemented " + description + " type inference mapping",
            Code::Unspecified );
        return;
    }

    const auto& sourceLocation = node.sourceLocation();
    const auto& expressionType = lhsExpression->type();

    const auto& behaviorType = Ast::make< BasicType >(
        sourceLocation,
        IdentifierPath::fromIdentifier(
            Ast::make< Identifier >( sourceLocation, operation->second.first ) ) );

    const auto& symbolName = operation->second.second;

    try
    {
        resolveDomainTypeBehaviorImplementSymbol( node, expressionType, behaviorType, symbolName );
    }
    catch( const std::domain_error& e )
    {
        m_log.error(
            { sourceLocation },
            "invalid " + description + ", because " + std::string( e.what() ),
            Code::Unspecified );
    }
}

void TypeInferenceVisitor::visit( ListLiteral& node )
{
    RecursiveVisitor::visit( node );
    m_log.error(
        { node.sourceLocation() },
        "UNIMPLEMENTED " + node.description() +
            " current type: " + ( node.type() ? node.type()->description() : "$unresolved$" ) );

    // if( node.type() )
    // {
    //     return;
    // }

    // filterAnnotationsByKind( node, libcasm_ir::Type::Kind::LIST );

    // // propagate type annotation to all list elements
    // for( const auto typeId : m_typeIDs[&node ] )
    // {
    //     const auto type = libcasm_ir::Type::fromID( typeId );
    //     assert( type->isList() );
    //     const auto listType = std::static_pointer_cast< libcasm_ir::ListType >( type );
    //     annotateNodes( *node.expressions(), listType->ptr_result()->id() );
    // }

    // node.expressions()->accept( *this );

    // u1 valid = true;
    // for( const auto& expression : *node.expressions() )
    // {
    //     if( not expression->type() )
    //     {
    //         valid = false;
    //         m_log.error(
    //             { expression->sourceLocation() },
    //             "unable to infer list element type",
    //             Code::Unspecified );
    //     }
    // }

    // if( not valid )
    // {
    //     return;
    // }

    // const auto& subTypeDefinition =
    //     m_symboltable.findTypeDefinition( node.expressions()->front()->type()->id() );
    // assert( subTypeDefinition and " inconsistent state " );
    // subTypeDefinition->accept( *this );

    // const auto& subType = subTypeDefinition->domainType()->duplicate< Ast::Type >();

    // const auto& domainSymbol = m_symboltable.findSymbol( TypeInfo::TYPE_NAME_LIST );
    // assert( domainSymbol and " inconsistent state, checked during symbol registration " );
    // const auto& domainDefinition = domainSymbol->ptr< DomainDefinition >();
    // assert(
    //     domainDefinition->domainType()->id() == Node::ID::TEMPLATE_TYPE and
    //     " inconsistent state " );

    // const auto& duplicateDomainDefinition = domainSymbol->duplicate< DomainDefinition >();
    // for( auto const& templateSymbol : *domainDefinition->templateSymbols() )
    // {
    //     const auto& fromBasicType = Ast::make< BasicType >(
    //         templateSymbol->sourceLocation(),
    //         IdentifierPath::fromIdentifier( templateSymbol->identifier() ) );

    //     ReplaceTypeVisitor replaceTypeVisitor( m_log, fromBasicType, subType );
    //     duplicateDomainDefinition->accept( replaceTypeVisitor );
    //     m_log.warning( "'" + fromBasicType->signature() + "' ==> '" + subType->signature() + "'"
    //     );
    // }
    // duplicateDomainDefinition->templateSymbols()->clear();

    // SymbolRegistrationVisitor symbolRegistrationVisitor( m_log, m_symboltable );
    // duplicateDomainDefinition->accept( symbolRegistrationVisitor );

    // SymbolResolveVisitor symbolResolveVisitor( m_log, m_symboltable );
    // duplicateDomainDefinition->accept( symbolResolveVisitor );

    // TypeCheckVisitor typeCheckVisitor( m_log, m_symboltable );
    // duplicateDomainDefinition->accept( typeCheckVisitor );

    // m_log.info(
    //     { node.sourceLocation() },
    //     "new domain type '" + domainDefinition->typeDescription() + "' -> '" +
    //         duplicateDomainDefinition->typeDescription() + "'" );

    // node.setType( duplicateDomainDefinition->type() );

    // // for( const auto& expression : *node.expressions() )
    // // {
    // //     if( expression->type() )
    // //     {
    // //         annotateNodes( *node.expressions(), expression->type()->id() );
    // //     }
    // // }

    // // node.expressions()->accept( *this );

    // // inference( "list literal", node );
    // // if( not node.type() )
    // // {
    // //     // inference failed, use type of first typed expression instead
    // //     for( const auto& expression : *node.expressions() )
    // //     {
    // //         if( expression->type() )
    // //         {
    // //             const auto listType =
    // //                 libstdhl::Memory::get< libcasm_ir::ListType >( expression->type() );
    // //             node.setType( listType );
    // //             break;
    // //         }
    // //     }
    // // }

    // // if( node.type() )
    // // {
    // //     for( const auto& expression : *node.expressions() )
    // //     {
    // //         if( not expression->type() )
    // //         {
    // //             continue;
    // //         }

    // //         if( *expression->type() != node.type()->result() )
    // //         {
    // //             m_log.error(
    // //                 { expression->sourceLocation() },
    // //                 "list element has invalid type '" + expression->type()->description() +
    // //                     "', expected '" + node.type()->result().description() + "'",
    // //                 Code::TypeInferenceListLiteralTypeMismatch );
    // //         }
    // //     }
    // // }
}

void TypeInferenceVisitor::visit( RangeLiteral& node )
{
    if( node.type() )
    {
        return;
    }

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

    const auto& lhsType = node.left()->type();
    const auto& rhsType = node.right()->type();
    if( not( lhsType and rhsType ) )
    {
        return;
    }

    const auto& sourceLocation = node.sourceLocation();
    if( *lhsType != *rhsType )
    {
        m_log.error(
            { sourceLocation },
            "types of range does not match, " + lhsType->description() +
                " != " + rhsType->description(),
            Code::TypeInferenceRangeLiteralTypeMismatch );
        return;
    }

    const auto& subTypeDefinition = m_symboltable.findTypeDefinition( lhsType->id() );
    assert( subTypeDefinition and " inconsistent state " );
    subTypeDefinition->accept( *this );

    const auto& subType = subTypeDefinition->domainType()->duplicate< Ast::Type >();

    const auto& domainSymbol = m_symboltable.findSymbol( TypeInfo::TYPE_NAME_RANGE );
    assert( domainSymbol and " inconsistent state, checked during symbol registration " );
    const auto& domainDefinition = domainSymbol->ptr< DomainDefinition >();
    assert(
        domainDefinition->domainType()->id() == Node::ID::TEMPLATE_TYPE and
        " inconsistent state " );

    const auto& duplicateDomainDefinition = domainSymbol->duplicate< DomainDefinition >();
    for( auto const& templateSymbol : *domainDefinition->templateNode()->symbols() )
    {
        const auto& fromBasicType = Ast::make< BasicType >(
            templateSymbol->sourceLocation(),
            IdentifierPath::fromIdentifier( templateSymbol->identifier() ) );

        ReplaceTypeVisitor replaceTypeVisitor( m_log, fromBasicType, subType );
        duplicateDomainDefinition->domainType()->accept( replaceTypeVisitor );
        m_log.warning( "'" + fromBasicType->signature() + "' ==> '" + subType->signature() + "'" );
    }
    duplicateDomainDefinition->templateNode()->symbols()->clear();

    SymbolRegistrationVisitor symbolRegistrationVisitor( m_log, m_symboltable );
    duplicateDomainDefinition->accept( symbolRegistrationVisitor );

    SymbolResolveVisitor symbolResolveVisitor( m_log, m_symboltable );
    duplicateDomainDefinition->accept( symbolResolveVisitor );

    TypeCheckVisitor typeCheckVisitor( m_log, m_symboltable );
    duplicateDomainDefinition->accept( typeCheckVisitor );

    m_log.info(
        { node.sourceLocation() },
        "new domain type '" + domainDefinition->typeDescription() + "' -> '" +
            duplicateDomainDefinition->typeDescription() + "'" );
    domainDefinition->addTemplateInstance( duplicateDomainDefinition );

    node.setType( duplicateDomainDefinition->type() );
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

    m_log.info( { node.sourceLocation() }, "new domain type '" + tupleType->description() + "'" );
}

void TypeInferenceVisitor::visit( RecordLiteral& node )
{
    RecursiveVisitor::visit( node );
    m_log.error(
        { node.sourceLocation() },
        "UNIMPLEMENTED " + node.description() +
            " current type: " + ( node.type() ? node.type()->description() : "$unresolved$" ) );

    // if( node.type() )
    // {
    //     return;
    // }

    // filterAnnotationsByKind( node, libcasm_ir::Type::Kind::RECORD );

    // // propagate type annotation to all record elements
    // for( const auto typeId : m_typeIDs[&node ] )
    // {
    //     const auto type = libcasm_ir::Type::fromID( typeId );
    //     assert( type->isRecord() );
    //     const auto recordType = std::static_pointer_cast< libcasm_ir::RecordType >( type );
    //     const auto& expressionTypes = recordType->arguments();
    //     if( expressionTypes.size() != node.namedExpressions()->size() )
    //     {
    //         continue;
    //     }

    //     for( std::size_t i = 0; i < expressionTypes.size(); i++ )
    //     {
    //         const auto& expression = node.namedExpressions()->at( i );
    //         const auto& expressionType = expressionTypes.at( i );
    //         m_typeIDs[ expression.get() ].emplace( expressionType->id() );
    //     }
    // }

    // RecursiveVisitor::visit( node );

    // std::vector< std::string > expressionNames;
    // libcasm_ir::Types expressionTypes;
    // for( const auto& namedExpression : *node.namedExpressions() )
    // {
    //     if( not namedExpression->type() )
    //     {
    //         // cannot create a record type if not all element types are known, thus the return
    //         return;
    //     }

    //     expressionTypes.add( namedExpression->type() );
    //     expressionNames.emplace_back( namedExpression->identifier()->name() );
    // }

    // const auto recordType =
    //     libstdhl::Memory::get< libcasm_ir::RecordType >( expressionTypes, expressionNames );
    // node.setType( recordType );
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
    const std::string description = "cardinality operator";

    node.expression()->accept( *this );
    if( not node.expression()->type() )
    {
        m_log.error(
            { node.expression()->sourceLocation() },
            "unable to infer expression type of " + description,
            Code::TypeInferenceCardinalityExpressionHasNoType );
        return;
    }

    const auto& sourceLocation = node.sourceLocation();
    const auto& expressionType = node.expression()->type();
    const auto& behaviorType = Ast::make< BasicType >(
        sourceLocation,
        IdentifierPath::fromIdentifier(
            Ast::make< Identifier >( sourceLocation, "Cardinality" ) ) );
    const auto& symbolName = "size";

    try
    {
        resolveDomainTypeBehaviorImplementSymbol( node, expressionType, behaviorType, symbolName );
    }
    catch( const std::domain_error& e )
    {
        m_log.error(
            { sourceLocation },
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
        // if CaseRule expression is still not typed
        // try to infer the type from the ExpressionCase types
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
    RecursiveVisitor::visit( node );
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
        func.setType( func.type()->ptr_result() );

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

void TypeInferenceVisitor::visit( BasicType& node )
{
    if( node.type() )
    {
        return;
    }

    const auto& symbolName = node.signaturePath();
    const auto& typeName = node.signature();
    const auto symbolResult = m_symboltable.findSymbol( *symbolName );
    const auto symbol = symbolResult.first;
    assert( symbol and " inconsistent state @ SymbolRegistrationPass " );
    assert( symbol->type() and " inconsistent state @ TypeCheckPass " );
    node.setType( symbol->type() );
}

void TypeInferenceVisitor::visit( TupleType& node )
{
    if( node.type() )
    {
        return;
    }

    const auto& symbolName = node.signaturePath();
    const auto& typeName = node.signature();
    const auto symbolResult = m_symboltable.findSymbol( *symbolName );
    const auto symbol = symbolResult.first;
    assert( symbol and " inconsistent state @ SymbolRegistrationPass " );
    assert( symbol->type() and " inconsistent state @ TypeCheckPass " );
    node.setType( symbol->type() );
}

void TypeInferenceVisitor::visit( RecordType& node )
{
    if( node.type() )
    {
        return;
    }

    m_log.error(
        { node.sourceLocation() },
        "unable to infer " + node.description() + " '" + node.signature() + "'",
        Code::Unspecified );
}

void TypeInferenceVisitor::visit( FixedSizedType& node )
{
    node.size()->accept( *this );

    if( node.type() )
    {
        return;
    }

    m_log.error(
        { node.sourceLocation() },
        "unable to infer " + node.description() + " '" + node.signature() + "'",
        Code::Unspecified );
}

void TypeInferenceVisitor::visit( TemplateType& node )
{
    if( node.type() )
    {
        return;
    }

    const auto& symbolName = node.signaturePath();
    const auto& typeName = node.signature();
    const auto symbolResult = m_symboltable.findSymbol( *symbolName );
    const auto symbol = symbolResult.first;
    if( symbol )
    {
        assert( symbol->type() and " inconsistent state @ TypeCheckPass " );
        node.setType( symbol->type() );
        return;
    }

    m_log.error(
        { node.sourceLocation() },
        "unable to infer " + node.description() + " '" + node.signature() + "'",
        Code::Unspecified );
}

void TypeInferenceVisitor::visit( RelationType& node )
{
    if( node.type() )
    {
        return;
    }

    RecursiveVisitor::visit( node );
    const auto& symbol = node.typeDefinition();
    assert( symbol and " inconsistent state @ SymbolResolverPass " );
    assert( symbol->type() and " inconsistent state @ TypeCheckPass " );
    node.setType( symbol->type() );
}

void TypeInferenceVisitor::visit( VariableBinding& node )
{
    if( node.type() )
    {
        return;
    }

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

        node.variable()->accept( *this );
    }

    assignment(
        *node.variable(),
        *node.expression(),
        "variable '" + node.variable()->identifier()->name() + "'",
        "expression",
        Code::TypeInferenceInvalidVariableBindingTypeMismatch );

    node.setType( node.variable()->type() );
    if( not node.type() )
    {
        m_log.error(
            { node.sourceLocation() },
            "unable to infer type of " + node.description() + " '" +
                node.variable()->identifier()->name() + "'",
            Code::Unspecified );
    }
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

            const std::string msg = "type mismatch: " + src + " was '" + tyRhs.description() +
                                    "', but " + dst + " expects '" + tyLhs.description() + "'";
            m_log.error( { rhs.sourceLocation() }, msg, assignmentErr );
            m_log.info( { lhsSourceLocation }, msg );
        }
    }
}

void TypeInferenceVisitor::resolveDomainTypeBehaviorImplementSymbol(
    TargetCallExpression& node,
    const libcasm_ir::Type::Ptr& domainType,
    const Ast::Type::Ptr& behaviorType,
    const std::string& symbolName,
    const libcasm_ir::Type::Ptr& resultType )
{
    const auto& definition = m_symboltable.findTypeDefinition( domainType->id() );
    // assert( definition and " inconsistent state @ TypeCheckPass " );
    if( not definition )
    {
        throw std::domain_error(
            "no def ty @ '" + std::to_string( domainType->id() ) + "' with '" +
            domainType->description() + "'" );
    }

    const auto& definitionDomainTypeName = definition->domainType()->signature();
    const auto& definitionDomainTypePath = definition->domainType()->signaturePath();
    const auto& definitionNamespace = m_symboltable.findNamespace( *definitionDomainTypePath );
    // assert( definitionNamespace and " inconsistent state " );
    if( not definitionNamespace )
    {
        throw std::domain_error( "no def ns @ '" + definitionDomainTypePath->path() + "'" );
    }

    Namespace::Ptr implementTypeNamespace = definitionNamespace;
    if( behaviorType )
    {
        const auto& behaviorName = behaviorType->name()->path();
        const auto& behaviorPath = IdentifierPath::fromIdentifier(
            Ast::make< Identifier >( node.sourceLocation(), "CASM" ) );
        for( const auto& behaviorTypeNameIdentifier : *behaviorType->name()->identifiers() )
        {
            behaviorPath->addIdentifier( behaviorTypeNameIdentifier );
        }

        auto behaviorSymbolResult = m_symboltable.findSymbol( *behaviorPath );
        auto behaviorSymbol = behaviorSymbolResult.first;
        if( not behaviorSymbol )
        {
            // search for the behavior in the CASM prelude namespace as well!
            behaviorSymbolResult = m_symboltable.findSymbol( *behaviorType->name() );
            behaviorSymbol = behaviorSymbolResult.first;
            // assert( behaviorSymbol and " inconsistent state @ CASM prelude specification " );
            if( not behaviorSymbol )
            {
                throw std::domain_error( "inconsistent state @ CASM prelude specification" );
            }
        }

        const auto& behaviorTypeName = behaviorType->signature();
        const auto& behaviorTypeNamespace = definitionNamespace->findNamespace( behaviorTypeName );
        if( not behaviorTypeNamespace )
        {
            throw std::domain_error(
                "the behavior '" + behaviorTypeName + "' is not registered for type '" +
                definition->domainType()->signature() + "'" );
        }

        implementTypeNamespace = behaviorTypeNamespace->findNamespace( behaviorTypeName );
        if( not implementTypeNamespace )
        {
            throw std::domain_error(
                "the behavior '" + behaviorTypeName + "' is not implemented for type '" +
                definition->domainType()->signature() + "'" );
        }
    }

    const auto symbol = implementTypeNamespace->findSymbol( symbolName );
    if( not symbol )
    {
        throw std::domain_error(
            "the method '" + symbolName + "' is not defined for domain '" +
            definitionDomainTypeName + "'" );
    }

    if( not symbol->type() )
    {
        throw std::domain_error( "the method '" + symbolName + "' is not typed" );
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

            if( relationArgumentType->isInteger() and symbolArgumentType->isInteger() )
            {
                // relax passing argument use Integer'[a..b] to def Integer
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
    void visit( LiteralCallExpression& node ) override;
    void visit( CardinalityExpression& node ) override;
    void visit( TypeCastingExpression& node ) override;

  private:
    void check( TargetCallExpression& node ) const;

  private:
    libcasm_fe::Logger& m_log;
};

CallTargetCheckVisitor::CallTargetCheckVisitor( libcasm_fe::Logger& log )
: m_log( log )
{
}

void CallTargetCheckVisitor::visit( DirectCallExpression& node )
{
    RecursiveVisitor::visit( node );
    check( node );

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
    RecursiveVisitor::visit( node );
    check( node );

    if( node.methodType() == MethodCallExpression::MethodType::UNKNOWN )
    {
        m_log.error(
            { node.methodName()->sourceLocation() },
            "unknown method '" + node.methodName()->name() + "' found",
            Code::MethodIsUnknown );
    }
}

void CallTargetCheckVisitor::visit( LiteralCallExpression& node )
{
    RecursiveVisitor::visit( node );
    check( node );
}

void CallTargetCheckVisitor::visit( CardinalityExpression& node )
{
    RecursiveVisitor::visit( node );
    check( node );
}

void CallTargetCheckVisitor::visit( TypeCastingExpression& node )
{
    RecursiveVisitor::visit( node );
    check( node );
}

void CallTargetCheckVisitor::check( TargetCallExpression& node ) const
{
    if( not node.hasTargetDefinition() )
    {
        m_log.error(
            { node.sourceLocation() },
            "unable to infer " + node.description(),
            Code::SymbolIsUnknown );
    }
}

void TypeInferencePass::usage( libpass::PassUsage& pu )
{
    pu.require< SpecificationMergerPass >();
    pu.scheduleAfter< TypeCheckPass >();
}

u1 TypeInferencePass::run( libpass::PassResult& pr )
{
    libcasm_fe::Logger log( &id, stream() );

    const auto data = pr.output< SpecificationMergerPass >();
    const auto specification = data->specification();

    TypeInferenceVisitor typeInferenceVisitor( log, *specification->symboltable() );
    specification->definitions()->accept( typeInferenceVisitor );

    const auto errors = log.errors();
    if( errors > 0 )
    {
        log.debug( "symbol table =\n" + specification->symboltable()->dump() );
        log.debug( "found %lu error(s) during type inference", errors );
        return false;
    }

    CallTargetCheckVisitor callTargetCheckVisitor( log );
    specification->definitions()->accept( callTargetCheckVisitor );

    const auto checkErrors = log.errors();
    if( checkErrors > 0 )
    {
        log.debug( "symbol table =\n" + specification->symboltable()->dump() );
        log.debug( "found %lu error(s) during call target checking", checkErrors );
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
