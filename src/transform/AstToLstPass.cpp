//
//  Copyright (C) 2014-2020 CASM Organization <https://casm-lang.org>
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

#include "AstToLstPass.h"

#include <libcasm-fe/Logger>
#include <libcasm-fe/Namespace>
#include <libcasm-fe/Specification>
#include <libcasm-fe/analyze/FrameSizeDeterminationPass>
#include <libcasm-fe/analyze/SymbolResolverPass>
#include <libcasm-fe/ast/Declaration>
#include <libcasm-fe/ast/Literal>
#include <libcasm-fe/ast/Visitor>
#include <libcasm-fe/import/SpecificationMergerPass>
#include <libcasm-fe/lst/Literal>

#include <libpass/PassRegistry>
#include <libpass/PassResult>
#include <libpass/PassUsage>

using namespace libcasm_fe;
using namespace AST;

char AstToLstPass::id = 0;

static libpass::PassRegistration< AstToLstPass > PASS(
    "AST To LST Pass", "transforms AST to LST representation", "cst2ast", 0 );

//
//
// AstToLstVisitor
//

namespace libcasm_fe
{
    namespace AST
    {
        class AstToLstVisitor final : public Visitor
        {
          public:
            AstToLstVisitor( libcasm_fe::Logger& log, const Namespace& symboltable );

            LST::Root::Ptr transform( const Root::Ptr& node );

            void visit( Root& node ) override;

            void visit( InitDefinition& node ) override;
            void visit( VariableDefinition& node ) override;
            void visit( FunctionDefinition& node ) override;
            void visit( DerivedDefinition& node ) override;
            void visit( RuleDefinition& node ) override;
            void visit( EnumeratorDefinition& node ) override;
            void visit( EnumerationDefinition& node ) override;
            void visit( UsingDefinition& node ) override;
            void visit( UsingPathDefinition& node ) override;
            void visit( InvariantDefinition& node ) override;
            void visit( ImportDefinition& node ) override;
            void visit( DomainDefinition& node ) override;
            void visit( StructureDefinition& node ) override;
            void visit( BehaviorDefinition& node ) override;
            void visit( ImplementDefinition& node ) override;
            void visit( BuiltinDefinition& node ) override;
            void visit( Declaration& node ) override;

            void visit( ValueLiteral& node ) override;
            void visit( ReferenceLiteral& node ) override;
            void visit( UndefLiteral& node ) override;
            void visit( SetLiteral& node ) override;
            void visit( ListLiteral& node ) override;
            void visit( RangeLiteral& node ) override;
            void visit( TupleLiteral& node ) override;
            void visit( RecordLiteral& node ) override;

            void visit( AbstractExpression& node ) override;
            void visit( NamedExpression& node ) override;
            void visit( MappedExpression& node ) override;
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

            void visit( SkipRule& node ) override;
            void visit( ConditionalRule& node ) override;
            void visit( CaseRule& node ) override;
            void visit( LetRule& node ) override;
            void visit( LocalRule& node ) override;
            void visit( ForallRule& node ) override;
            void visit( ChooseRule& node ) override;
            void visit( IterateRule& node ) override;
            void visit( BlockRule& node ) override;
            void visit( SequenceRule& node ) override;
            void visit( UpdateRule& node ) override;
            void visit( CallRule& node ) override;

            void visit( UnresolvedType& node ) override;
            void visit( BasicType& node ) override;
            void visit( TupleType& node ) override;
            void visit( RecordType& node ) override;
            void visit( TemplateType& node ) override;
            void visit( FixedSizedType& node ) override;
            void visit( RelationType& node ) override;

            void visit( Identifier& node ) override;
            void visit( IdentifierPath& node ) override;
            void visit( ExpressionCase& node ) override;
            void visit( DefaultCase& node ) override;
            void visit( VariableBinding& node ) override;

          private:
            template < typename T >
            typename T::Ptr fetch( const AST::Node::Ptr& node )
            {
                auto search = m_lst.find( node.get() );
                if( search == m_lst.end() )
                {
                    node->accept( *this );
                }

                search = m_lst.find( node.get() );
                if( search == m_lst.end() )
                {
                    const auto& msg = " unimplemented '" + node->description() + "'";
                    m_log.error( { node->sourceLocation() }, msg, Code::Internal );
                    return nullptr;
                }

                auto result = search->second;
                if( result )
                {
                    return result->ptr< T >();
                }
                return nullptr;
            }

            template < typename T, typename A, typename C >
            typename T::Ptr fetch( const typename AST::NodeList< C >::Ptr& node )
            {
                const auto& list = LST::make< T >( node->sourceLocation() );
                for( const auto& nodeElement : *node )
                {
                    const auto& element = fetch< A >( nodeElement );
                    if( element )
                    {
                        list->add( element );
                    }
                }

                return list;
            }

            template < typename T, typename... Args >
            typename T::Ptr store( AST::Node& node, Args&&... args )
            {
                const auto& result =
                    LST::make< T >( node.sourceLocation(), std::forward< Args >( args )... );
                set( node, result );
                return result;
            }

            void set( AST::Node& node, const LST::Node::Ptr& result )
            {
                const auto check = m_lst.emplace( &node, result );
                if( not check.second )
                {
                    const auto& msg = "already transformed '" + node.description() + "'";
                    m_log.debug( { node.sourceLocation() }, msg );  //, Code::Internal );
                }
            }

          private:
            libcasm_fe::Logger& m_log;
            const Namespace& m_symboltable;
            std::unordered_map< AST::Node*, LST::Node::Ptr > m_lst;

            const LST::Definitions::Ptr m_lstDefinitions;
        };
    }
}

AstToLstVisitor::AstToLstVisitor( libcasm_fe::Logger& log, const Namespace& symboltable )
: m_log( log )
, m_symboltable( symboltable )
, m_lstDefinitions( std::make_shared< LST::Definitions >() )
{
}

LST::Root::Ptr AstToLstVisitor::transform( const Root::Ptr& node )
{
    return fetch< LST::Root >( node );
}

void AstToLstVisitor::visit( Root& node )
{
    for( const auto& definition : *node.definitions() )
    {
        switch( definition->id() )
        {
            case AST::Node::ID::USING_DEFINITION:
            case AST::Node::ID::USING_PATH_DEFINITION:
            {
                continue;
            }
            default:
            {
                definition->accept( *this );
                break;
            }
        }
    }

    store< LST::Root >( node, m_lstDefinitions );
}

void AstToLstVisitor::visit( InitDefinition& node )
{
}

void AstToLstVisitor::visit( VariableDefinition& node )
{
    const auto& identifier = fetch< LST::Identifier >( node.identifier() );
    store< LST::VariableDefinition >(
        node,
        node.type(),
        node.properties(),
        identifier,
        node.maximumNumberOfLocals(),
        node.localIndex() );
}

void AstToLstVisitor::visit( FunctionDefinition& node )
{
    const auto& identifier = fetch< LST::Identifier >( node.identifier() );
    const auto& defined = fetch< LST::Expression >( node.defined() );
    const auto& initiallyLocation = node.initially()->sourceLocation();
    const auto& initiallyRules = LST::make< LST::Rules >( initiallyLocation );
    const auto& initially = LST::make< LST::SequenceRule >( initiallyLocation, initiallyRules );

    const auto& lstNode = store< LST::FunctionDefinition >(
        node,
        node.type(),
        node.properties(),
        identifier,
        node.maximumNumberOfLocals(),
        defined,
        initially,
        node.symbolic(),
        node.program(),
        node.local() );

    const auto& lstInitially = fetch< LST::SequenceRule >( node.initiallyRule() );
    for( const auto& lstInitiallyRule : *lstInitially->rules() )
    {
        initiallyRules->add( lstInitiallyRule );
    }

    m_lstDefinitions->add( lstNode );
}

void AstToLstVisitor::visit( DerivedDefinition& node )
{
    const auto& identifier = fetch< LST::Identifier >( node.identifier() );
    const auto& arguments =
        fetch< LST::VariableDefinitions, LST::VariableDefinition, AST::VariableDefinition >(
            node.arguments() );
    const auto& expression = fetch< LST::Expression >( node.expression() );
    const auto& lstNode = store< LST::DerivedDefinition >(
        node,
        node.type(),
        node.properties(),
        identifier,
        node.maximumNumberOfLocals(),
        arguments,
        expression );

    m_lstDefinitions->add( lstNode );
}

void AstToLstVisitor::visit( RuleDefinition& node )
{
    const auto& identifier = fetch< LST::Identifier >( node.identifier() );
    const auto& arguments =
        fetch< LST::VariableDefinitions, LST::VariableDefinition, AST::VariableDefinition >(
            node.arguments() );
    const auto& rule = fetch< LST::Rule >( node.rule() );
    const auto& lstNode = store< LST::RuleDefinition >(
        node,
        node.type(),
        node.properties(),
        identifier,
        node.maximumNumberOfLocals(),
        arguments,
        rule );

    m_lstDefinitions->add( lstNode );
}

void AstToLstVisitor::visit( EnumeratorDefinition& node )
{
}

void AstToLstVisitor::visit( EnumerationDefinition& node )
{
    // astNode->setExported( node.exported() );
}

void AstToLstVisitor::visit( UsingDefinition& node )
{
    m_log.error( { node.sourceLocation() }, "invalid transformation 'using'", Code::Internal );
}

void AstToLstVisitor::visit( UsingPathDefinition& node )
{
    m_log.error( { node.sourceLocation() }, "invalid transformation 'using path'", Code::Internal );
}

void AstToLstVisitor::visit( ImportDefinition& node )
{
}

void AstToLstVisitor::visit( InvariantDefinition& node )
{
    // astNode->setExported( node.exported() );
}

void AstToLstVisitor::visit( DomainDefinition& node )
{
    // const auto& templateSymbols =
    //     fetch< LST::VariableDefinitions, LST::VariableDefinition, AST::VariableDefinition >(
    //         node.templateNode()->symbols() );
    // const auto& domainType = node.domainType();
    const auto& identifier = fetch< LST::Identifier >( node.identifier() );
    const auto& lstNode = store< LST::DomainDefinition >(
        node, node.type(), node.properties(), identifier, node.maximumNumberOfLocals() );

    m_lstDefinitions->add( lstNode );
}

void AstToLstVisitor::visit( StructureDefinition& node )
{
    // const auto& templateSymbols =
    //     fetch< LST::VariableDefinitions, LST::VariableDefinition, AST::VariableDefinition >(
    //         node.templateNode()->symbols() );
    // const auto& domainType = node.domainType();

    const auto& lstFunctionDefinitions =
        fetch< LST::FunctionDefinitions, LST::FunctionDefinition, AST::FunctionDefinition >(
            node.functions() );

    for( const auto& lstFunctionDefinition : *lstFunctionDefinitions )
    {
        m_lstDefinitions->add( lstFunctionDefinition );
    }
}

void AstToLstVisitor::visit( BehaviorDefinition& node )
{
}

void AstToLstVisitor::visit( ImplementDefinition& node )
{
}

void AstToLstVisitor::visit( BuiltinDefinition& node )
{
    // const auto& templateSymbols =
    //     fetch< LST::VariableDefinitions, LST::VariableDefinition, AST::VariableDefinition >(
    //         node.templateNode()->symbols() );
    const auto& identifier = fetch< LST::Identifier >( node.identifier() );
    const auto& lstNode = store< LST::BuiltinDefinition >(
        node,
        node.type(),
        node.properties(),
        identifier,
        node.maximumNumberOfLocals(),
        node.targetId() );

    m_lstDefinitions->add( lstNode );
}

void AstToLstVisitor::visit( Declaration& node )
{
    m_log.error( { node.sourceLocation() }, "invalid transformation", Code::Internal );
}

void AstToLstVisitor::visit( UndefLiteral& node )
{
    const auto& undefLiteral =
        std::make_shared< libcasm_ir::Constant >( libcasm_ir::Constant::undef( node.type() ) );
    store< LST::ValueLiteral >( node, node.properties(), undefLiteral );
}

void AstToLstVisitor::visit( ValueLiteral& node )
{
    store< LST::ValueLiteral >( node, node.properties(), node.value() );
}

void AstToLstVisitor::visit( ReferenceLiteral& node )
{
    const auto& identifier = fetch< LST::IdentifierPath >( node.identifier() );
    const auto& reference = fetch< LST::Definition >( node.reference() );
    store< LST::ReferenceLiteral >( node, node.type(), node.properties(), identifier, reference );
}

void AstToLstVisitor::visit( SetLiteral& node )
{
    const auto& expressions =
        fetch< LST::Expressions, LST::Expression, AST::Expression >( node.expressions() );
    store< LST::SetLiteral >( node, node.type(), node.properties(), expressions );
}

void AstToLstVisitor::visit( ListLiteral& node )
{
    const auto& expressions =
        fetch< LST::Expressions, LST::Expression, AST::Expression >( node.expressions() );
    store< LST::ListLiteral >( node, node.type(), node.properties(), expressions );
}

void AstToLstVisitor::visit( RangeLiteral& node )
{
    const auto& left = fetch< LST::Expression >( node.left() );
    const auto& right = fetch< LST::Expression >( node.right() );
    store< LST::RangeLiteral >( node, node.type(), node.properties(), left, right );
}

void AstToLstVisitor::visit( TupleLiteral& node )
{
    const auto& expressions =
        fetch< LST::Expressions, LST::Expression, AST::Expression >( node.expressions() );
    store< LST::TupleLiteral >( node, node.type(), node.properties(), expressions );
}

void AstToLstVisitor::visit( RecordLiteral& node )
{
    const auto& namedExpressions =
        fetch< LST::NamedExpressions, LST::NamedExpression, AST::NamedExpression >(
            node.namedExpressions() );
    store< LST::RecordLiteral >( node, node.type(), node.properties(), namedExpressions );
}

void AstToLstVisitor::visit( AbstractExpression& node )
{
    m_log.error( { node.sourceLocation() }, "invalid transformation", Code::Internal );
}

void AstToLstVisitor::visit( NamedExpression& node )
{
}

void AstToLstVisitor::visit( MappedExpression& node )
{
}

void AstToLstVisitor::visit( DirectCallExpression& node )
{
    const auto& targetDefinition = fetch< LST::Definition >( node.targetDefinition() );
    const auto& arguments =
        fetch< LST::Expressions, LST::Expression, AST::Expression >( node.arguments() );
    store< LST::DirectCallExpression >(
        node, node.type(), node.properties(), arguments, targetDefinition, node.targetType() );
}

void AstToLstVisitor::visit( MethodCallExpression& node )
{
    const auto& targetDefinition = fetch< LST::Definition >( node.targetDefinition() );
    const auto& arguments =
        fetch< LST::Expressions, LST::Expression, AST::Expression >( node.arguments() );
    store< LST::DirectCallExpression >(
        node, node.type(), node.properties(), arguments, targetDefinition, node.targetType() );
}

void AstToLstVisitor::visit( IndirectCallExpression& node )
{
}

void AstToLstVisitor::visit( TypeCastingExpression& node )
{
    const auto& targetDefinition = fetch< LST::Definition >( node.targetDefinition() );
    const auto& arguments =
        fetch< LST::Expressions, LST::Expression, AST::Expression >( node.arguments() );
    store< LST::DirectCallExpression >(
        node, node.type(), node.properties(), arguments, targetDefinition, node.targetType() );
}

void AstToLstVisitor::visit( UnaryExpression& node )
{
    const auto& targetDefinition = fetch< LST::Definition >( node.targetDefinition() );
    const auto& arguments =
        fetch< LST::Expressions, LST::Expression, AST::Expression >( node.arguments() );
    store< LST::DirectCallExpression >(
        node, node.type(), node.properties(), arguments, targetDefinition, node.targetType() );
}

void AstToLstVisitor::visit( BinaryExpression& node )
{
    const auto& targetDefinition = fetch< LST::Definition >( node.targetDefinition() );
    const auto& arguments =
        fetch< LST::Expressions, LST::Expression, AST::Expression >( node.arguments() );
    store< LST::DirectCallExpression >(
        node, node.type(), node.properties(), arguments, targetDefinition, node.targetType() );
}

void AstToLstVisitor::visit( LiteralCallExpression& node )
{
    const auto& targetDefinition = fetch< LST::Definition >( node.targetDefinition() );
    const auto& arguments =
        fetch< LST::Expressions, LST::Expression, AST::Expression >( node.arguments() );
    store< LST::DirectCallExpression >(
        node, node.type(), node.properties(), arguments, targetDefinition, node.targetType() );
}

void AstToLstVisitor::visit( CardinalityExpression& node )
{
    const auto& targetDefinition = fetch< LST::Definition >( node.targetDefinition() );
    const auto& arguments =
        fetch< LST::Expressions, LST::Expression, AST::Expression >( node.arguments() );
    store< LST::DirectCallExpression >(
        node, node.type(), node.properties(), arguments, targetDefinition, node.targetType() );
}

void AstToLstVisitor::visit( LetExpression& node )
{
}

void AstToLstVisitor::visit( ConditionalExpression& node )
{
    const auto& condition = fetch< LST::Expression >( node.condition() );
    const auto& thenExpression = fetch< LST::Expression >( node.thenExpression() );
    const auto& elseExpression = fetch< LST::Expression >( node.elseExpression() );
    store< LST::ConditionalExpression >(
        node, node.type(), node.properties(), condition, thenExpression, elseExpression );
}

void AstToLstVisitor::visit( ChooseExpression& node )
{
}

void AstToLstVisitor::visit( UniversalQuantifierExpression& node )
{
}

void AstToLstVisitor::visit( ExistentialQuantifierExpression& node )
{
}

void AstToLstVisitor::visit( SkipRule& node )
{
    store< LST::SkipRule >( node );
}

void AstToLstVisitor::visit( ConditionalRule& node )
{
    // use skip rule for else!
}

void AstToLstVisitor::visit( CaseRule& node )
{
}

void AstToLstVisitor::visit( LetRule& node )
{
    const auto& variableBindings =
        fetch< LST::VariableBindings, LST::VariableBinding, AST::VariableBinding >(
            node.variableBindings() );
    const auto& rule = fetch< LST::Rule >( node.rule() );
    store< LST::LetRule >( node, variableBindings, rule );
}

void AstToLstVisitor::visit( LocalRule& node )
{
}

void AstToLstVisitor::visit( ForallRule& node )
{
    // std::make_shared< ValueLiteral >(
    // libstdhl::Memory::get< libcasm_ir::BooleanConstant >( true ) )
}

void AstToLstVisitor::visit( ChooseRule& node )
{
}

void AstToLstVisitor::visit( IterateRule& node )
{
}

void AstToLstVisitor::visit( BlockRule& node )
{
    const auto& rules = fetch< LST::Rules, LST::Rule, AST::Rule >( node.rules() );
    store< LST::BlockRule >( node, rules );
}

void AstToLstVisitor::visit( SequenceRule& node )
{
    const auto& rules = fetch< LST::Rules, LST::Rule, AST::Rule >( node.rules() );
    store< LST::SequenceRule >( node, rules );
}

void AstToLstVisitor::visit( UpdateRule& node )
{
    const auto& function = fetch< LST::CallExpression >( node.function() );
    const auto& expression = fetch< LST::Expression >( node.expression() );
    store< LST::UpdateRule >( node, function, expression );
}

void AstToLstVisitor::visit( CallRule& node )
{
    const auto& call = fetch< LST::CallExpression >( node.call() );
    store< LST::CallRule >( node, call );
}

void AstToLstVisitor::visit( UnresolvedType& node )
{
    m_log.error( { node.sourceLocation() }, "invalid transformation", Code::Internal );
}

void AstToLstVisitor::visit( BasicType& node )
{
    m_log.error( { node.sourceLocation() }, "invalid transformation", Code::Internal );
}

void AstToLstVisitor::visit( TupleType& node )
{
    m_log.error( { node.sourceLocation() }, "invalid transformation", Code::Internal );
}

void AstToLstVisitor::visit( RecordType& node )
{
    m_log.error( { node.sourceLocation() }, "invalid transformation", Code::Internal );
}

void AstToLstVisitor::visit( TemplateType& node )
{
    m_log.error( { node.sourceLocation() }, "invalid transformation", Code::Internal );
}

void AstToLstVisitor::visit( FixedSizedType& node )
{
    m_log.error( { node.sourceLocation() }, "invalid transformation", Code::Internal );
}

void AstToLstVisitor::visit( RelationType& node )
{
    m_log.error( { node.sourceLocation() }, "invalid transformation", Code::Internal );
}

void AstToLstVisitor::visit( Identifier& node )
{
    store< LST::Identifier >( node, node.name() );
}

void AstToLstVisitor::visit( IdentifierPath& node )
{
    const auto& identifiers =
        fetch< LST::Identifiers, LST::Identifier, AST::Identifier >( node.identifiers() );
    store< LST::IdentifierPath >( node, identifiers );
}

void AstToLstVisitor::visit( ExpressionCase& node )
{
}

void AstToLstVisitor::visit( DefaultCase& node )
{
}

void AstToLstVisitor::visit( VariableBinding& node )
{
    const auto& variable = fetch< LST::VariableDefinition >( node.variable() );
    const auto& expression = fetch< LST::Expression >( node.expression() );
    store< LST::VariableBinding >(
        node, node.type(), libcasm_ir::Properties{}, variable, expression );
}

//
//
// AstToLstPass
//

void AstToLstPass::usage( libpass::PassUsage& pu )
{
    pu.require< SpecificationMergerPass >();
    pu.require< SymbolResolverPass >();
    pu.scheduleAfter< FrameSizeDeterminationPass >();
}

u1 AstToLstPass::run( libpass::PassResult& pr )
{
    libcasm_fe::Logger log( &id, stream() );

    const auto& data = pr.output< SpecificationMergerPass >();
    const auto& specification = data->specification();

    AstToLstVisitor visitor{ log, *specification->symboltable() };
    const auto& lst = visitor.transform( specification->ast() );

    const auto errors = log.errors();
    if( errors > 0 )
    {
        log.debug( "symbol table =\n" + specification->symboltable()->dump() );
        log.debug( "found %lu error(s) during transformation", errors );
        return false;
    }

    const auto& transformedSpecification = std::make_shared< Specification >();
    transformedSpecification->setAsmType( specification->asmType() );
    transformedSpecification->setLocation( specification->location() );
    transformedSpecification->setSymboltable( specification->symboltable() );
    transformedSpecification->setLst( lst );

    pr.setOutput< AstToLstPass >( transformedSpecification );
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
