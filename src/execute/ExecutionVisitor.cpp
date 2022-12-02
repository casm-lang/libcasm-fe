//
//  Copyright (C) 2014-2022 CASM Organization <https://casm-lang.org>
//  All rights reserved.
//
//  Developed by: Philipp Paulweber et al.
//                <https://github.com/casm-lang/libcasm-fe/graphs/contributors>
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

#include "ExecutionVisitor.h"

#include <libcasm-fe/Logger>
#include <libcasm-fe/execute/RuntimeException>
#include <libcasm-fe/execute/UpdateException>
#include <libcasm-fe/lst/Expression>
#include <libcasm-fe/lst/Rule>

#include <libcasm-ir/Exception>
#include <libcasm-ir/Instruction>
#include <libcasm-ir/Operation>

#include <libstdhl/RestoreOnScopeExit>

#include <memory>
#include <mutex>
#include <stdexcept>
#include <thread>

using namespace libcasm_fe;
using namespace LST;

namespace IR = libcasm_ir;

template < typename T >
class ScopedOverwrite : public libstdhl::RestoreOnScopeExit< T >
{
  public:
    ScopedOverwrite( T& target, const T& value )
    : RestoreOnScopeExit< T >( target )
    {
        target = value;
    }
};

std::string ExecutionVisitor::updateAsString( const ExecutionUpdateSet::Update& update )
{
    const auto& location = update.location;
    const auto& value = update.value;

    auto locationStr = location.function()->identifier()->name();

    if( not location.arguments().empty() )
    {
        locationStr += "(";
        bool isFirst = true;
        for( const auto& arg : location.arguments() )
        {
            if( not isFirst )
            {
                locationStr += ", ";
            }
            locationStr += arg.name();
            isFirst = false;
        }
        locationStr += ")";
    }

    return locationStr + " := " + value.value.name();
}

UpdateException::UpdateInfo ExecutionVisitor::updateAsUpdateInfo(
    const ExecutionUpdateSet::Update& update )
{
    return { update.value.producer->ptr< Node >(),
             update.location.function()->ptr< FunctionDefinition >(),
             update.location.arguments(),
             update.value.value };
}

Storage::Storage( void )
: m_programState( 1 )
, m_functionState( 100 )
{
}

void Storage::fireUpdateSet( ExecutionUpdateSet* updateSet )
{
    const auto end = updateSet->end();
    for( auto it = updateSet->begin(); it != end; ++it )
    {
        const auto& location = it.key();
        const auto& update = it.value();
        set( location, update.value );
    }
}

void Storage::set( const Location& location, const Value& value )
{
    if( location.function()->program() )
    {
        m_programState.set( location, value );
    }
    else
    {
        m_functionState.set( location, value );
    }
}

void Storage::remove( const Location& location )
{
    if( location.function()->program() )
    {
        m_programState.remove( location );
    }
    else
    {
        m_functionState.remove( location );
    }
}

libstdhl::Optional< Storage::Value > Storage::get( const Location& location ) const
{
    if( location.function()->program() )
    {
        return m_programState.get( location );
    }
    else
    {
        return m_functionState.get( location );
    }
}

const Storage::ExecutionFunctionState& Storage::programState( void ) const
{
    return m_programState;
}

ExecutionVisitor::ExecutionVisitor(
    ExecutionLocationRegistry& locationRegistry,
    Storage& globalState,
    UpdateSetManager< ExecutionUpdateSet >& updateSetManager,
    const IR::Constant& agentId )
: m_globalState( globalState )
, m_locationRegistry( locationRegistry )
, m_updateSetManager( updateSetManager )
, m_agentId( agentId )
, m_evaluationStack()
, m_frameStack()
, m_evaluateUpdateLocation( false )
, m_updateLocation( ExecutionLocationRegistry::Location::invalid() )
{
}

void ExecutionVisitor::execute( const ReferenceConstant& value )
{
    assert( value.defined() && "Reference must be defined" );

    const auto& literal = value.value();
    const auto& literalReference = literal->reference();
    assert( literalReference->id() == Node::ID::RULE_DEFINITION and " shall be rule reference " );

    const auto& rule = std::static_pointer_cast< RuleDefinition >( literalReference );
    assert( rule->type()->arguments().size() == 0 and " only parameter-less rules are supported" );

    execute( rule );
}

void ExecutionVisitor::execute( const Definition::Ptr& definition )
{
    m_frameStack.push(
        makeFrame( nullptr, definition.get(), definition->maximumNumberOfLocals() ) );
    definition->accept( *this );
    m_frameStack.pop();
}

void ExecutionVisitor::visit( Root& node )
{
    node.definitions()->accept( *this );
}

void ExecutionVisitor::visit( VariableDefinition& node )
{
    const auto* frame = m_frameStack.top();
    m_evaluationStack.push( frame->local( node.localIndex() ) );
}

void ExecutionVisitor::visit( FunctionDefinition& node )
{
    if( m_evaluateUpdateLocation )
    {
        validateArguments(
            node,
            node.type()->arguments(),
            { ValidationFlag::ValueMustBeDefined },
            Code::FunctionArgumentInvalidValueAtUpdate );

        m_updateLocation = m_locationRegistry.get( &node, m_frameStack.top()->locals() );
    }
    else
    {
        validateArguments(
            node,
            node.type()->arguments(),
            { ValidationFlag::ValueMustBeDefined },
            Code::FunctionArgumentInvalidValueAtLookup );

        const auto location = m_locationRegistry.lookup( &node, m_frameStack.top()->locals() );
        if( location )
        {
            const auto update = m_updateSetManager.lookup( *location );
            if( update )
            {
                m_evaluationStack.push( update->value );
                return;
            }

            if( not node.local() )
            {
                const auto function = m_globalState.get( *location );
                if( function )
                {
                    m_evaluationStack.push( function.value() );
                    return;
                }
            }
        }

        node.defined()->accept( *this );  // return value already on stack
    }
}

void ExecutionVisitor::visit( DerivedDefinition& node )
{
    validateArguments( node, node.type()->arguments(), {}, Code::DerivedArgumentValueInvalid );

    node.expression()->accept( *this );  // return value already on stack

    // validate return value
    const auto& returnType = node.type()->result();
    const auto& returnValue = m_evaluationStack.top();  // keep it on stack
    try
    {
        validateValue( returnValue, returnType );
    }
    catch( const IR::ValidationException& e )
    {
        throw RuntimeException(
            { node.sourceLocation() },
            e.what(),
            m_frameStack.generateBacktrace( node.sourceLocation(), m_agentId ),
            Code::DerivedReturnValueInvalid );
    }
}

void ExecutionVisitor::visit( RuleDefinition& node )
{
    validateArguments( node, node.type()->arguments(), {}, Code::RuleArgumentValueInvalid );

    node.rule()->accept( *this );

    const auto& returnType = node.type()->ptr_result();
    if( not returnType->isVoid() )
    {
        if( false /* update set has result update */ )
        {
            // const auto& value = TODO get update value and REMOVE update from
            // update set
            // TODO validate return value
            // m_evaluationStack.push( value );
        }
        else
        {
            m_evaluationStack.push( IR::Constant::undef( returnType ) );
        }
    }
}

void ExecutionVisitor::visit( EnumeratorDefinition& node )
{
    assert( node.type()->isEnumeration() );
    const auto& enumType = std::static_pointer_cast< IR::EnumerationType >( node.type() );
    m_evaluationStack.push( IR::EnumerationConstant( enumType, node.identifier()->name() ) );
}

void ExecutionVisitor::visit( EnumerationDefinition& node )
{
    throw RuntimeException(
        { node.sourceLocation() },
        "unimplemented",  // TODO: FIXME: @ppaulweber
        m_frameStack.generateBacktrace( node.sourceLocation(), m_agentId ),
        Code::Internal );
}

void ExecutionVisitor::visit( InvariantDefinition& node )
{
    node.expression()->accept( *this );
    const auto result = m_evaluationStack.pop< IR::BooleanConstant >();

    if( not result.defined() )
    {
        throw RuntimeException(
            { node.expression()->sourceLocation() },
            "result must be true or false but was undefined",
            m_frameStack.generateBacktrace( node.sourceLocation(), m_agentId ),
            Code::InvariantDefinitionInvalidExpression );
    }
    else if( result.value() == false )
    {
        throw RuntimeException(
            { node.sourceLocation() },
            "invariant '" + node.identifier()->name() + "' violated",
            m_frameStack.generateBacktrace( node.sourceLocation(), m_agentId ),
            Code::InvariantDefinitionInvariantViolated );
    }
}

void ExecutionVisitor::visit( DomainDefinition& node )
{
    throw RuntimeException(
        { node.sourceLocation() },
        "unimplemented",  // TODO: FIXME: @ppaulweber
        m_frameStack.generateBacktrace( node.sourceLocation(), m_agentId ),
        Code::Internal );
}

void ExecutionVisitor::visit( BuiltinDefinition& node )
{
    const auto& type = node.type();
    validateArguments( node, type->arguments(), {}, Code::BuiltinArgumentValueInvalid );

    if( node.targetId() == IR::SelfInstruction::classid() )
    {
        m_evaluationStack.push( m_agentId );
        return;
    }

    const auto& arguments = m_frameStack.top()->locals();
    IR::Constant result;

    IR::Operation::execute( node.targetId(), type, result, arguments.data(), arguments.size() );

    const auto& returnType = type->result();
    if( not returnType.isVoid() )
    {
        m_evaluationStack.push( result );
    }
}

void ExecutionVisitor::visit( ValueLiteral& node )
{
    m_evaluationStack.push( *node.value() );
}

void ExecutionVisitor::visit( ReferenceLiteral& node )
{
    m_evaluationStack.push( ReferenceConstant( &node ) );
}

void ExecutionVisitor::visit( SetLiteral& node )
{
    throw RuntimeException(
        { node.sourceLocation() },
        "unimplemented",  // TODO: FIXME: @ppaulweber
        m_frameStack.generateBacktrace( node.sourceLocation(), m_agentId ),
        Code::Internal );
}

void ExecutionVisitor::visit( ListLiteral& node )
{
    assert( node.type()->isList() );
    const auto listType = std::static_pointer_cast< IR::ListType >( node.type() );
    auto list = std::make_shared< IR::List >( listType );

    for( const auto& expression : *node.expressions() )
    {
        expression->accept( *this );
        const auto constantElement = m_evaluationStack.pop();
        list->append( constantElement );
    }

    m_evaluationStack.push( IR::ListConstant( listType, list ) );
}

void ExecutionVisitor::visit( RangeLiteral& node )
{
    node.left()->accept( *this );
    const auto lhs = m_evaluationStack.pop();

    node.right()->accept( *this );
    const auto rhs = m_evaluationStack.pop();

    m_evaluationStack.push( IR::RangeConstant( node.type(), lhs, rhs ) );
}

void ExecutionVisitor::visit( TupleLiteral& node )
{
    assert( node.type()->isTuple() );
    const auto& tupleType = std::static_pointer_cast< IR::TupleType >( node.type() );

    const auto tupleSize = node.expressions()->size();
    std::vector< IR::Constant > tupleElements;
    tupleElements.reserve( tupleSize );

    for( std::size_t index = 0; index < tupleSize; index++ )
    {
        const auto& expression = ( *node.expressions() )[ index ];
        expression->accept( *this );
        const auto constantElement = m_evaluationStack.pop();
        tupleElements.emplace_back( constantElement );
    }

    const auto& tupleConstant = IR::TupleConstant( tupleType, tupleElements );
    m_evaluationStack.push( tupleConstant );
}

void ExecutionVisitor::visit( RecordLiteral& node )
{
    assert( node.type()->isRecord() );
    const auto& recordType = std::static_pointer_cast< IR::RecordType >( node.type() );

    // iterate through the in-order, out-of-order, or partial named expressions and assign the
    // element name with the given expression
    const auto recordSize = node.namedExpressions()->size();
    std::unordered_map< std::string, IR::Constant > recordElements;
    recordElements.reserve( recordSize );

    for( const auto& namedExpression : *node.namedExpressions() )
    {
        namedExpression->accept( *this );
        recordElements.emplace( namedExpression->identifier()->name(), m_evaluationStack.pop() );
    }

    const auto& recordConstant = IR::RecordConstant( recordType, recordElements );
    m_evaluationStack.push( recordConstant );
}

void ExecutionVisitor::visit( NamedExpression& node )
{
    // just evaluate the embraced expression and push it to the stack
    node.expression()->accept( *this );
}

void ExecutionVisitor::visit( DirectCallExpression& node )
{
    switch( node.targetType() )
    {
        case DirectCallExpression::TargetType::FUNCTION:  // [[fallthrough]]
        case DirectCallExpression::TargetType::DERIVED:   // [[fallthrough]]
        case DirectCallExpression::TargetType::BUILTIN:
        {
            const auto& definition = node.targetDefinition();
            m_frameStack.push(
                makeFrame( &node, definition.get(), definition->maximumNumberOfLocals() ) );
            definition->accept( *this );
            m_frameStack.pop();
            break;
        }
        case DirectCallExpression::TargetType::RULE:
        {
            Transaction transaction( &m_updateSetManager, Semantics::Parallel, 100 );
            const auto& definition = node.targetDefinition();
            m_frameStack.push(
                makeFrame( &node, definition.get(), definition->maximumNumberOfLocals() ) );

            try
            {
                definition->accept( *this );
            }
            catch( const std::exception& e )
            {
                throw RuntimeException(
                    { node.sourceLocation() },
                    "rule has thrown an exception: " + std::string( e.what() ),
                    m_frameStack.generateBacktrace( node.sourceLocation(), m_agentId ),
                    Code::RuntimeException );
            }

            m_frameStack.pop();
            try
            {
                transaction.merge();
            }
            catch( const ExecutionUpdateSet::Conflict& conflict )
            {
                handleMergeConflict( node, conflict );
            }
            break;
        }
        case DirectCallExpression::TargetType::DOMAINTYPE:
        {
            m_evaluationStack.push( IR::DomainConstant( node.type() ) );
            break;
        }
        case DirectCallExpression::TargetType::CONSTANT:  // [[fallthrough]]
        case DirectCallExpression::TargetType::VARIABLE:
        {
            node.targetDefinition()->accept( *this );
            break;
        }
        case DirectCallExpression::TargetType::UNKNOWN:
        {
            assert( !"cannot call an unknown target" );
            break;
        }
    }
}

void ExecutionVisitor::visit( IndirectCallExpression& node )
{
    node.expression()->accept( *this );
    const auto value = m_evaluationStack.pop< ReferenceConstant >();
    if( not value.defined() )
    {
        throw RuntimeException(
            { node.expression()->sourceLocation() },
            "cannot call an undefined target",
            m_frameStack.generateBacktrace( node.sourceLocation(), m_agentId ),
            Code::RuntimeException );
    }

    const auto& literal = value.value();
    const auto& literalReference = literal->reference();
    switch( literal->reference()->id() )
    {
        case Node::ID::FUNCTION_DEFINITION:  // [[fallthrough]]
        case Node::ID::DERIVED_DEFINITION:
        {
            const auto& definition = std::static_pointer_cast< Definition >( literal->reference() );
            m_frameStack.push(
                makeFrame( &node, definition.get(), definition->maximumNumberOfLocals() ) );
            definition->accept( *this );
            m_frameStack.pop();
            break;
        }
        case Node::ID::RULE_DEFINITION:
        {
            Transaction transaction( &m_updateSetManager, Semantics::Parallel, 100 );
            const auto& definition = std::static_pointer_cast< Definition >( literal->reference() );
            m_frameStack.push(
                makeFrame( &node, definition.get(), definition->maximumNumberOfLocals() ) );
            definition->accept( *this );
            m_frameStack.pop();
            try
            {
                transaction.merge();
            }
            catch( const ExecutionUpdateSet::Conflict& conflict )
            {
                handleMergeConflict( node, conflict );
            }
            break;
        }
        default:
        {
            assert( !"cannot call an unknown target" );
            break;
        }
    }
}

void ExecutionVisitor::visit( LetExpression& node )
{
    node.variableBindings()->accept( *this );
    node.expression()->accept( *this );
}

void ExecutionVisitor::visit( ConditionalExpression& node )
{
    node.condition()->accept( *this );
    const auto condition = m_evaluationStack.pop< IR::BooleanConstant >();

    if( not condition.defined() )
    {
        throw RuntimeException(
            { node.condition()->sourceLocation() },
            "condition must be true or false but was undefined",
            m_frameStack.generateBacktrace( node.sourceLocation(), m_agentId ),
            Code::ConditionalExpressionInvalidCondition );
    }
    else if( condition.value() == true )
    {
        node.thenExpression()->accept( *this );
    }
    else
    {
        node.elseExpression()->accept( *this );
    }
}

void ExecutionVisitor::visit( ChooseExpression& node )
{
    node.universe()->accept( *this );
    const auto universe = m_evaluationStack.pop();

    if( not universe.defined() )
    {
        throw RuntimeException(
            { node.universe()->sourceLocation() },
            "universe must be defined",
            m_frameStack.generateBacktrace( node.sourceLocation(), m_agentId ),
            Code::ChooseExpressionInvalidUniverse );
    }

    auto* frame = m_frameStack.top();
    const auto variableIndex = node.variable()->localIndex();

    auto repeatChoose = true;
    size_t repeatCount = 0;
    while( repeatChoose )
    {
        frame->setLocal( variableIndex, universe.choose() );

        node.condition()->accept( *this );
        const auto condition = m_evaluationStack.pop< IR::BooleanConstant >();

        if( not condition.defined() )
        {
            throw RuntimeException(
                { node.condition()->sourceLocation() },
                "condition cannot be undefined",
                m_frameStack.generateBacktrace( node.sourceLocation(), m_agentId ),
                Code::Unspecified );
        }

        repeatChoose = ( condition.value() != true );
        repeatCount++;

        if( repeatCount > 1000000 )
        {
            throw RuntimeException(
                { node.condition()->sourceLocation() },
                "aborting after 10^6 unsuccessful attempts to choose a value under the given condition",
                m_frameStack.generateBacktrace( node.sourceLocation(), m_agentId ),
                Code::Unspecified );
        }
    }

    node.expression()->accept( *this );
}

void ExecutionVisitor::visit( UniversalQuantifierExpression& node )
{
    bool result = true;
    bool defined = true;

    node.universe()->accept( *this );
    const auto universe = m_evaluationStack.pop();

    if( not universe.defined() )
    {
        throw RuntimeException(
            { node.universe()->sourceLocation() },
            "universe must be defined",
            m_frameStack.generateBacktrace( node.sourceLocation(), m_agentId ),
            Code::QuantifierExpressionInvalidUniverse );
    }

    foreachInUniverse( *node.predicateVariables(), universe, [ & ]() {
        node.proposition()->accept( *this );
        const auto prop = m_evaluationStack.pop< IR::BooleanConstant >();

        if( not prop.defined() )
        {
            defined = false;
        }
        else if( prop.value() == false )
        {
            result = false;
            // break; TODO optimization
        }
    } );

    if( defined )
    {
        m_evaluationStack.push( IR::BooleanConstant( result ) );
    }
    else
    {
        if( result == false )
        {
            m_evaluationStack.push( IR::BooleanConstant( false ) );
        }
        else
        {
            m_evaluationStack.push( IR::BooleanConstant() );
        }
    }
}

void ExecutionVisitor::visit( ExistentialQuantifierExpression& node )
{
    bool result = false;
    bool defined = true;

    node.universe()->accept( *this );
    const auto universe = m_evaluationStack.pop();

    if( not universe.defined() )
    {
        throw RuntimeException(
            { node.universe()->sourceLocation() },
            "universe must be defined",
            m_frameStack.generateBacktrace( node.sourceLocation(), m_agentId ),
            Code::QuantifierExpressionInvalidUniverse );
    }

    foreachInUniverse( *node.predicateVariables(), universe, [ & ]() {
        node.proposition()->accept( *this );
        const auto prop = m_evaluationStack.pop< IR::BooleanConstant >();

        if( not prop.defined() )
        {
            defined = false;
        }
        else if( prop.value() == true )
        {
            result = true;
            // break; TODO optimization
        }
    } );

    if( defined )
    {
        m_evaluationStack.push( IR::BooleanConstant( result ) );
    }
    else
    {
        if( result == true )
        {
            m_evaluationStack.push( IR::BooleanConstant( true ) );
        }
        else
        {
            m_evaluationStack.push( IR::BooleanConstant() );
        }
    }
}

void ExecutionVisitor::visit( SkipRule& node )
{
}

void ExecutionVisitor::visit( ConditionalRule& node )
{
    node.condition()->accept( *this );
    const auto condition = m_evaluationStack.pop< IR::BooleanConstant >();

    if( not condition.defined() )
    {
        throw RuntimeException(
            { node.condition()->sourceLocation() },
            "condition must be true or false but was undefined",
            m_frameStack.generateBacktrace( node.sourceLocation(), m_agentId ),
            Code::ConditionalRuleInvalidCondition );
    }
    else if( condition.value() == true )
    {
        node.thenRule()->accept( *this );
    }
    else
    {
        node.elseRule()->accept( *this );
    }
}

void ExecutionVisitor::visit( CaseRule& node )
{
    node.expression()->accept( *this );
    const auto value = m_evaluationStack.pop();

    Case* defaultCase = nullptr;

    for( const auto& _case : *node.cases() )
    {
        switch( _case->id() )
        {
            case Node::ID::DEFAULT_CASE:
            {
                assert(
                    defaultCase == nullptr &&
                    "case rule should not contain multiple default cases" );
                defaultCase = _case.get();
                break;
            }
            case Node::ID::EXPRESSION_CASE:
            {
                const auto& exprCase = std::static_pointer_cast< ExpressionCase >( _case );
                exprCase->expression()->accept( *this );

                const auto caseValue = m_evaluationStack.pop();
                if( value == caseValue )
                {
                    // match
                    _case->rule()->accept( *this );
                    return;
                }
                break;
            }
            default:
            {
                assert( !"unknown case" );
                break;
            }
        }
    }

    if( defaultCase )
    {
        defaultCase->rule()->accept( *this );
    }
}

void ExecutionVisitor::visit( LetRule& node )
{
    Transaction transaction( &m_updateSetManager, Semantics::Sequential, 100 );

    {
        Transaction initTransaction( &m_updateSetManager, Semantics::Parallel, 100 );
        node.variableBindings()->accept( *this );
        initTransaction.merge();
    }

    node.rule()->accept( *this );

    try
    {
        transaction.merge();
    }
    catch( const ExecutionUpdateSet::Conflict& conflict )
    {
        handleMergeConflict( node, conflict );
    }
}

void ExecutionVisitor::visit( LocalRule& node )
{
    Transaction transaction( &m_updateSetManager, Semantics::Sequential, 100 );

    std::unordered_set< LST::FunctionDefinition* > localFunctions;

    {
        Transaction initTransaction( &m_updateSetManager, Semantics::Parallel, 100 );
        for( const auto& function : *node.localFunctions() )
        {
            localFunctions.insert( function.get() );
            function->initially()->accept( *this );
        }
        initTransaction.merge();
    }

    node.rule()->accept( *this );

    // ignore local function updates
    auto* updateSet = m_updateSetManager.currentUpdateSet();
    updateSet->setUpdateFilter(
        [ &localFunctions ](
            const UpdateSetDetails::Location& location, const UpdateSetDetails::Value& value ) {
            return localFunctions.find( location.function() ) == localFunctions.cend();
        } );

    try
    {
        transaction.merge();
    }
    catch( const ExecutionUpdateSet::Conflict& conflict )
    {
        handleMergeConflict( node, conflict );
    }
}

void ExecutionVisitor::visit( ForallRule& node )
{
    Transaction transaction( &m_updateSetManager, Semantics::Parallel, 100 );

    node.universe()->accept( *this );
    const auto universe = m_evaluationStack.pop();

    if( not universe.defined() )
    {
        throw RuntimeException(
            { node.universe()->sourceLocation() },
            "universe must be defined",
            m_frameStack.generateBacktrace( node.sourceLocation(), m_agentId ),
            Code::ForallRuleInvalidUniverse );
    }

    foreachInUniverse( *node.variables(), universe, [ & ]() {
        // check if values satisfy the condition
        node.condition()->accept( *this );
        const auto condition = m_evaluationStack.pop< IR::BooleanConstant >();

        if( not condition.defined() )
        {
            throw RuntimeException(
                { node.condition()->sourceLocation() },
                "condition must be true or false but was undefined",
                m_frameStack.generateBacktrace( node.sourceLocation(), m_agentId ),
                Code::ForallRuleInvalidCondition );
        }
        else if( condition.value() == true )
        {
            node.rule()->accept( *this );
        }
    } );

    try
    {
        transaction.merge();
    }
    catch( const ExecutionUpdateSet::Conflict& conflict )
    {
        handleMergeConflict( node, conflict );
    }
}

void ExecutionVisitor::visit( ChooseRule& node )
{
    node.universe()->accept( *this );
    const auto universe = m_evaluationStack.pop();

    if( not universe.defined() )
    {
        throw RuntimeException(
            { node.universe()->sourceLocation() },
            "universe must be defined",
            m_frameStack.generateBacktrace( node.sourceLocation(), m_agentId ),
            Code::ChooseRuleInvalidUniverse );
    }

    auto* frame = m_frameStack.top();

    for( const auto& variable : *node.variables() )
    {
        const auto variableIndex = variable->localIndex();
        frame->setLocal( variableIndex, universe.choose() );
    }

    node.rule()->accept( *this );
}

void ExecutionVisitor::visit( IterateRule& node )
{
    Transaction transaction( &m_updateSetManager, Semantics::Sequential, 100 );
    const auto* updateSet = m_updateSetManager.currentUpdateSet();

    std::size_t previousEpoch;
    do
    {
        previousEpoch = updateSet->epoch();
        node.rule()->accept( *this );
    } while( previousEpoch != updateSet->epoch() );

    try
    {
        transaction.merge();
    }
    catch( const ExecutionUpdateSet::Conflict& conflict )
    {
        handleMergeConflict( node, conflict );
    }
}

void ExecutionVisitor::visit( BlockRule& node )
{
    Transaction transaction( &m_updateSetManager, Semantics::Parallel, 100 );
    node.rules()->accept( *this );

    try
    {
        transaction.merge();
    }
    catch( const ExecutionUpdateSet::Conflict& conflict )
    {
        handleMergeConflict( node, conflict );
    }
}

void ExecutionVisitor::visit( SequenceRule& node )
{
    Transaction transaction( &m_updateSetManager, Semantics::Sequential, 100 );
    node.rules()->accept( *this );

    try
    {
        transaction.merge();
    }
    catch( const ExecutionUpdateSet::Conflict& conflict )
    {
        handleMergeConflict( node, conflict );
    }
}

void ExecutionVisitor::visit( UpdateRule& node )
{
    const auto& expression = node.expression();
    const auto& function = node.function();

    // evalute update value
    expression->accept( *this );
    const auto updateValue = m_evaluationStack.pop();
    try
    {
        validateValue( updateValue, *function->type() );
    }
    catch( const IR::ValidationException& e )
    {
        throw RuntimeException(
            { expression->sourceLocation() },
            e.what(),
            m_frameStack.generateBacktrace( node.sourceLocation(), m_agentId ),
            Code::FunctionUpdateInvalidValueAtUpdate );
    }

    {
        ScopedOverwrite< bool > withLocationEvaluation( m_evaluateUpdateLocation, true );
        function->accept( *this );
    }
    assert( m_updateLocation.isValid() );

    try
    {
        const Update update{ updateValue, &node, m_agentId };
        m_updateSetManager.add( m_updateLocation, update );
    }
    catch( const ExecutionUpdateSet::Conflict& conflict )
    {
        throw UpdateException(
            { node.sourceLocation() },
            "Conflict while adding an update in agent " + m_agentId.name() + ". Update '" +
                updateAsString( conflict.conflictingUpdate() ) + "' clashed with update '" +
                updateAsString( conflict.existingUpdate() ) + "'",
            m_frameStack.generateBacktrace( node.sourceLocation(), m_agentId ),
            { updateAsUpdateInfo( conflict.existingUpdate() ),
              updateAsUpdateInfo( conflict.conflictingUpdate() ) },
            libcasm_fe::Code::UpdateSetClash );
    }
}

void ExecutionVisitor::visit( CallRule& node )
{
    node.call()->accept( *this );

    const auto& returnType = node.call()->type()->result();
    if( not returnType.isVoid() )
    {
        m_evaluationStack.pop();  // drop return value
    }
}

void ExecutionVisitor::visit( VariableBinding& node )
{
    node.expression()->accept( *this );
    const auto value = m_evaluationStack.pop();

    // validate value
    const auto& variableType = node.variable()->type();
    try
    {
        validateValue( value, *variableType );
    }
    catch( const IR::ValidationException& e )
    {
        throw RuntimeException(
            { node.expression()->sourceLocation() },
            e.what(),
            m_frameStack.generateBacktrace( node.sourceLocation(), m_agentId ),
            Code::LetAssignedValueInvalid );
    }

    auto* frame = m_frameStack.top();
    const auto variableIndex = node.variable()->localIndex();
    frame->setLocal( variableIndex, value );
}

void ExecutionVisitor::visit( Identifier& node )
{
}

void ExecutionVisitor::visit( IdentifierPath& node )
{
}

void ExecutionVisitor::visit( DefaultCase& node )
{
}

void ExecutionVisitor::visit( ExpressionCase& node )
{
}

std::unique_ptr< Frame > ExecutionVisitor::makeFrame(
    CallExpression* call, Node* callee, std::size_t numberOfLocals )
{
    ScopedOverwrite< bool > withoutLocationEvaluation( m_evaluateUpdateLocation, false );

    auto frame = libstdhl::Memory::make_unique< Frame >( call, callee, numberOfLocals );

    if( call != nullptr )
    {
        assert( numberOfLocals >= call->arguments()->size() );

        std::size_t localIndex = 0;
        for( const auto& argument : *call->arguments() )
        {
            argument->accept( *this );
            const auto value = m_evaluationStack.pop();
            frame->setLocal( localIndex, value );
            ++localIndex;
        }
    }

    return frame;
}

void ExecutionVisitor::validateValue(
    const IR::Constant& value, const IR::Type& type, ValidationFlags flags ) const
{
    if( flags.isSet( ValidationFlag::ValueMustBeDefined ) and not value.defined() )
    {
        throw IR::ValidationException( "value must be defined" );
    }

    if( value.symbolic() )
    {
        auto& sym = static_cast< const IR::SymbolicConstant& >( value );
        if( sym.type() != type )
        {
            throw IR::ValidationException( "types do not match" );
        }
        return;
    }

    type.validate( value );
}

void ExecutionVisitor::validateArguments(
    const Node& node, const IR::Types& argumentTypes, ValidationFlags flags, Code errorCode ) const
{
    const auto* frame = m_frameStack.top();

    const auto size = argumentTypes.size();
    assert( frame->locals().size() >= size );

    for( std::size_t i = 0; i < size; ++i )
    {
        const auto& argumentType = argumentTypes.at( i );
        const auto& argumentValue = frame->local( i );

        try
        {
            validateValue( argumentValue, *argumentType, flags );
        }
        catch( const IR::ValidationException& e )
        {
            const auto& callArgument = frame->call()->arguments()->at( i );
            throw RuntimeException(
                { callArgument->sourceLocation() },
                e.what(),
                m_frameStack.generateBacktrace( node.sourceLocation(), m_agentId ),
                errorCode );
        }
    }
}

void ExecutionVisitor::handleMergeConflict(
    const Node& node, const ExecutionUpdateSet::Conflict& conflict ) const
{
    throw UpdateException(
        { node.sourceLocation() },
        "Conflict while merging update sets in agent " + m_agentId.name() + ". Update '" +
            updateAsString( conflict.conflictingUpdate() ) + "' clashed with update '" +
            updateAsString( conflict.existingUpdate() ) + "'",
        m_frameStack.generateBacktrace( node.sourceLocation(), m_agentId ),
        { updateAsUpdateInfo( conflict.existingUpdate() ),
          updateAsUpdateInfo( conflict.conflictingUpdate() ) },
        libcasm_fe::Code::UpdateSetMergeConflict );
}

void ExecutionVisitor::foreachInUniverse(
    const VariableDefinitions& variables,
    const IR::Constant& universe,
    const std::function< void() >& subRule ) const
{
    auto* frame = m_frameStack.top();

    // TODO: FIXME: @ppaulweber: move this to CST to AST transformation
    // Handle multiple forall variables by creating a lambda-function chain
    // e.g. forall x, y in U do
    //          subRule()
    // becomes:
    //      U.foreach(v -> x := v;
    //          U.foreach(w -> y := w;
    //              subRule()))
    std::function< void( const IR::Constant& ) > chain = nullptr;
    for( const auto& variable : variables )
    {
        const auto variableIndex = variable->localIndex();

        if( chain == nullptr )
        {
            chain = [ frame, variableIndex, subRule ]( const IR::Constant& value ) {
                frame->setLocal( variableIndex, value );
                subRule();
            };
        }
        else
        {
            chain = [ frame, variableIndex, chain, &universe ]( const IR::Constant& value ) {
                frame->setLocal( variableIndex, value );
                universe.foreach( chain );
            };
        }
    }

    universe.foreach( chain );
}

StateInitializationVisitor::StateInitializationVisitor(
    ExecutionLocationRegistry& locationRegistry, Storage& globalState )
: EmptyVisitor()
, m_globalState( globalState )
, m_locationRegistry( locationRegistry )
, m_updateSetManager()
{
}

void StateInitializationVisitor::visit( Specification& node )
{
    m_updateSetManager.fork( Semantics::Sequential, 100 );

    node.lst()->definitions()->accept( *this );

    auto updateSet = m_updateSetManager.currentUpdateSet();
    m_globalState.fireUpdateSet( updateSet );
    m_updateSetManager.clear();
}

void StateInitializationVisitor::visit( FunctionDefinition& node )
{
    assert( not node.local() );

    Transaction transaction( &m_updateSetManager, Semantics::Parallel, 100 );
    ExecutionVisitor executionVisitor(
        m_locationRegistry, m_globalState, m_updateSetManager, ReferenceConstant() );
    node.initially()->accept( executionVisitor );
    transaction.merge();
}

InvariantChecker::InvariantChecker(
    ExecutionLocationRegistry& locationRegistry, Storage& globalState )
: m_globalState( globalState )
, m_locationRegistry( locationRegistry )
{
}

void InvariantChecker::check( const Specification& specification )
{
    // UpdateSetManager< ExecutionUpdateSet > updateSetManager;
    // ExecutionVisitor visitor(
    //     m_locationRegistry, m_globalState, updateSetManager, ReferenceConstant() );

    // for( const auto& definition : *specification.lst()->definitions() )
    // {
    //     if( definition->id() != Node::ID::INVARIANT_DEFINITION )
    //     {
    //         continue;
    //     }

    //     visitor.execute( definition );
    // }
}

SymbolicExecutionVisitor::SymbolicExecutionVisitor(
    ExecutionLocationRegistry& locationRegistry,
    Storage& globalState,
    UpdateSetManager< ExecutionUpdateSet >& updateSetManager,
    const IR::Constant& agentId,
    IR::SymbolicExecutionEnvironment& environment )
: ExecutionVisitor( locationRegistry, globalState, updateSetManager, agentId )
, m_environment( environment )
{
}

void SymbolicExecutionVisitor::visit( FunctionDefinition& node )
{
    const auto* frame = m_frameStack.top();
    if( m_evaluateUpdateLocation )
    {
        validateArguments(
            node,
            node.type()->arguments(),
            { ValidationFlag::ValueMustBeDefined },
            Code::FunctionArgumentInvalidValueAtUpdate );

        m_updateLocation = m_locationRegistry.get( &node, frame->locals() );
    }
    else
    {
        validateArguments(
            node,
            node.type()->arguments(),
            { ValidationFlag::ValueMustBeDefined },
            Code::FunctionArgumentInvalidValueAtLookup );

        const auto location = not node.symbolic()
                                  ? m_locationRegistry.lookup( &node, m_frameStack.top()->locals() )
                                  : m_locationRegistry.get( &node, frame->locals() );
        if( location )
        {
            const auto update = m_updateSetManager.lookup( *location );
            if( update )
            {
                m_evaluationStack.push( update->value );
                return;
            }

            if( not node.local() )
            {
                const auto function = m_globalState.get( *location );
                if( node.symbolic() )
                {
                    if( function && function.value().symbolic() )
                    {
                        m_evaluationStack.push( function.value() );
                        return;
                    }
                    auto sym = m_environment.get(
                        node.identifier()->name(), node.type(), location->arguments() );
                    m_evaluationStack.push( sym );
                    m_globalState.set( *location, sym );
                    return;
                }
                if( function )
                {
                    m_evaluationStack.push( function.value() );
                    return;
                }
            }
        }

        node.defined()->accept( *this );  // return value already on stack
    }
}

void SymbolicExecutionVisitor::visit( DirectCallExpression& node )
{
    ExecutionVisitor::visit( node );
}

// void SymbolicExecutionVisitor::visit( MethodCallExpression& node )
// {
//     ExecutionVisitor::visit( node );
// }

// void SymbolicExecutionVisitor::visit( LiteralCallExpression& node )
// {
//     ExecutionVisitor::visit( node );
// }

void SymbolicExecutionVisitor::visit( IndirectCallExpression& node )
{
    ExecutionVisitor::visit( node );
}

// void SymbolicExecutionVisitor::visit( UnaryExpression& node )
// {
//     ExecutionVisitor::visit( node );
// }

// void SymbolicExecutionVisitor::visit( BinaryExpression& node )
// {
//     ExecutionVisitor::visit( node );
// }

void SymbolicExecutionVisitor::visit( LetExpression& node )
{
    ExecutionVisitor::visit( node );
}

void SymbolicExecutionVisitor::visit( ConditionalExpression& node )
{
    node.condition()->accept( *this );
    const auto condition = m_evaluationStack.pop();

    if( not condition.defined() )
    {
        throw RuntimeException(
            { node.condition()->sourceLocation() },
            "condition must be true or false but was undefined",
            m_frameStack.generateBacktrace( node.sourceLocation(), m_agentId ),
            Code::ConditionalRuleInvalidCondition );
    }

    if( condition.symbolic() )
    {
        const auto tptpCondition = m_environment.tptpAtomFromConstant( condition );
        {
            // environment crates implications for condition until end of scope
            auto environment = m_environment.makeEnvironment( tptpCondition );

            node.thenExpression()->accept( *this );
        }
        auto thenVal = m_evaluationStack.pop();
        {
            const auto inverse = std::make_shared< libtptp::UnaryLogic >(
                libtptp::UnaryLogic::Connective::NEGATION, tptpCondition );
            // environment crates implications for condition until end of scope
            auto environment = m_environment.makeEnvironment( inverse );
            node.elseExpression()->accept( *this );
        }
        auto elseVal = m_evaluationStack.pop();
        auto mergedSym = m_environment.mergeSymbolPaths( tptpCondition, thenVal, elseVal );
        m_evaluationStack.push( mergedSym );
    }
    else
    {
        const auto literalCondition = static_cast< const IR::BooleanConstant& >( condition );

        if( literalCondition.value() == true )
        {
            node.thenExpression()->accept( *this );
        }
        else
        {
            node.elseExpression()->accept( *this );
        }
    }
}

void SymbolicExecutionVisitor::visit( ChooseExpression& node )
{
    // TODO: if universe is symbolic: create symbolic trace
    ExecutionVisitor::visit( node );
}

void SymbolicExecutionVisitor::visit( UniversalQuantifierExpression& node )
{
    // TODO: visit universe, if symbolic: create quantified expression
    ExecutionVisitor::visit( node );
}

void SymbolicExecutionVisitor::visit( ExistentialQuantifierExpression& node )
{
    // TODO: visit universe, if symbolic: create quantified expression
    ExecutionVisitor::visit( node );
}

// void SymbolicExecutionVisitor::visit( CardinalityExpression& node )
// {
//     // TODO: fix me
//     ExecutionVisitor::visit( node );
// }

void SymbolicExecutionVisitor::visit( ConditionalRule& node )
{
    /*
    if(node.symbolic())
    {...}
    else {
        ExecutionVisitor::visit(node);
    }
    */
    node.condition()->accept( *this );
    const auto condition = m_evaluationStack.pop();

    if( not condition.defined() )
    {
        throw RuntimeException(
            { node.condition()->sourceLocation() },
            "condition must be true or false but was undefined",
            m_frameStack.generateBacktrace( node.sourceLocation(), m_agentId ),
            Code::ConditionalRuleInvalidCondition );
    }

    if( condition.symbolic() )
    {
        // all functions are symbolic, so overwriting updates is irrelevant
        // then and else branch may create colliding updates
        Transaction thenTransaction( &m_updateSetManager, Semantics::Parallel, 100 );
        const auto tptpCondition = m_environment.tptpAtomFromConstant( condition );
        {
            // environment crates implications for condition until end of scope
            auto environment = m_environment.makeEnvironment( tptpCondition );
            node.thenRule()->accept( *this );
        }
        auto thenSet = thenTransaction.rollback();
        Transaction elseTransaction( &m_updateSetManager, Semantics::Parallel, 100 );
        {
            const auto inverse = std::make_shared< libtptp::UnaryLogic >(
                libtptp::UnaryLogic::Connective::NEGATION, tptpCondition );
            // environment crates implications for condition until end of scope
            auto environment = m_environment.makeEnvironment( inverse );
            node.elseRule()->accept( *this );
        }
        auto elseSet = elseTransaction.rollback();
        Transaction transaction( &m_updateSetManager, Semantics::Parallel, 100 );
        std::vector< std::pair< UpdateSetDetails::Location, Update > > mergedUpdates;
        for( auto it = thenSet->begin(); it != thenSet->end(); ++it )
        {
            auto elseValue = elseSet->get( it.key() );
            if( elseValue )
            {
                auto mergedSym = m_environment.mergeSymbolPaths(
                    tptpCondition, it.value().value, elseValue->value );
                const Update newUpdate{ mergedSym, &node, m_agentId };
                m_updateSetManager.add( it.key(), newUpdate );
            }
            else
            {
                IR::Constant value;
                auto update = m_updateSetManager.lookup( it.key() );
                if( !update )
                {
                    auto function = m_globalState.get( it.key() );
                    if( !function || not function->symbolic() )
                    {
                        auto sym = m_environment.get(
                            it.key().function()->identifier()->name(),
                            it.key().function()->type(),
                            it.key().arguments() );
                        m_globalState.set( it.key(), sym );
                        value = sym;
                    }
                    else
                    {
                        value = function.value();
                    }
                }
                else
                {
                    value = update->value;
                }
                auto mergedSym =
                    m_environment.mergeSymbolPaths( tptpCondition, it.value().value, value );
                const Update newUpdate{ mergedSym, it.value().producer, m_agentId };
                m_updateSetManager.add( it.key(), newUpdate );
            }
        }
        for( auto it = elseSet->begin(); it != elseSet->end(); ++it )
        {
            auto thenValue = thenSet->get( it.key() );
            if( !thenValue )
            {
                IR::Constant value;
                auto update = m_updateSetManager.lookup( it.key() );
                if( !update )
                {
                    auto function = m_globalState.get( it.key() );
                    if( !function || not function->symbolic() )
                    {
                        auto sym = m_environment.get(
                            it.key().function()->identifier()->name(),
                            it.key().function()->type(),
                            it.key().arguments() );
                        m_globalState.set( it.key(), sym );
                        value = sym;
                    }
                    else
                    {
                        value = function.value();
                    }
                }
                else
                {
                    value = update->value;
                }
                auto mergedSym =
                    m_environment.mergeSymbolPaths( tptpCondition, value, it.value().value );
                const Update newUpdate{ mergedSym, it.value().producer, m_agentId };
                m_updateSetManager.add( it.key(), newUpdate );
            }
        }
        try
        {
            transaction.merge();
        }
        catch( const ExecutionUpdateSet::Conflict& conflict )
        {
            handleMergeConflict( node, conflict );
        }
    }
    else
    {
        const auto literalCondition = static_cast< const IR::BooleanConstant& >( condition );

        if( literalCondition.value() == true )
        {
            node.thenRule()->accept( *this );
        }
        else
        {
            node.elseRule()->accept( *this );
        }
    }
}

void SymbolicExecutionVisitor::visit( CaseRule& node )
{
    // TODO: similar to ConditionalRule: if condition symbolic: create all cases in trace with
    // respective environment
    ExecutionVisitor::visit( node );
}

void SymbolicExecutionVisitor::visit( ForallRule& node )
{
    // TODO: if universe symbolic: create quantified logic
    ExecutionVisitor::visit( node );
}

void SymbolicExecutionVisitor::visit( ChooseRule& node )
{
    // TODO: if universe symbolic: create symbolic trace
    ExecutionVisitor::visit( node );
}

void SymbolicExecutionVisitor::visit( IterateRule& node )
{
    // TODO: fix me
    ExecutionVisitor::visit( node );
}

void SymbolicExecutionVisitor::visit( BlockRule& node )
{
    ExecutionVisitor::visit( node );
}

void SymbolicExecutionVisitor::visit( SequenceRule& node )
{
    ExecutionVisitor::visit( node );
}

void SymbolicExecutionVisitor::visit( UpdateRule& node )
{
    const auto& expression = node.expression();
    const auto& function = node.function();

    // evalute update value
    expression->accept( *this );
    const auto updateValue = m_evaluationStack.pop();
    try
    {
        // validateValue( updateValue, *function->type() );
    }
    catch( const IR::ValidationException& e )
    {
        throw RuntimeException(
            { expression->sourceLocation() },
            e.what(),
            m_frameStack.generateBacktrace( node.sourceLocation(), m_agentId ),
            Code::FunctionUpdateInvalidValueAtUpdate );
    }

    {
        ScopedOverwrite< bool > withLocationEvaluation( m_evaluateUpdateLocation, true );
        function->accept( *this );
    }
    assert( m_updateLocation.isValid() );

    try
    {
        const Update update{ updateValue, &node, m_agentId };

        if( !m_updateLocation.function()->symbolic() && updateValue.symbolic() )
        {
            throw UpdateException(
                { node.sourceLocation() },
                "trying to assign a symbolic value to a numeric function",
                { m_frameStack.generateBacktrace( node.sourceLocation(), m_agentId ) },
                { updateAsUpdateInfo( { m_updateLocation, update } ) },
                libcasm_fe::Code::UpdateSetInvalidExpression );
        }

        m_updateSetManager.add( m_updateLocation, update );

        // TODO: @moosbruggerj add local variable handling
        if( m_updateLocation.function()->symbolic() )
        {
            auto value = m_environment.tptpAtomFromConstant( updateValue );
            m_environment.set(
                m_updateLocation.function()->identifier()->name(),
                m_updateLocation.function()->type(),
                m_updateLocation.arguments(),
                value );
        }
    }
    catch( const ExecutionUpdateSet::Conflict& conflict )
    {
        throw UpdateException(
            { node.sourceLocation() },
            "Conflict while adding an update in agent " + m_agentId.name() + ". Update '" +
                updateAsString( conflict.conflictingUpdate() ) + "' clashed with update '" +
                updateAsString( conflict.existingUpdate() ) + "'",
            m_frameStack.generateBacktrace( node.sourceLocation(), m_agentId ),
            { updateAsUpdateInfo( conflict.existingUpdate() ),
              updateAsUpdateInfo( conflict.conflictingUpdate() ) },
            libcasm_fe::Code::UpdateSetClash );
    }
}

// void SymbolicExecutionVisitor::visit( WhileRule& node )
// {
//     // TODO: fix me
//     ExecutionVisitor::visit( node );
// }

IR::SymbolicExecutionEnvironment& SymbolicExecutionVisitor::environment()
{
    return m_environment;
}

SymbolicStateInitializationVisitor::SymbolicStateInitializationVisitor(
    ExecutionLocationRegistry& locationRegistry,
    Storage& globalState,
    IR::SymbolicExecutionEnvironment& environment )
: EmptyVisitor()
, m_globalState( globalState )
, m_locationRegistry( locationRegistry )
, m_updateSetManager()
, m_environment( environment )
{
}

void SymbolicStateInitializationVisitor::visit( Specification& node )
{
    // m_updateSetManager.fork( Semantics::Sequential, 100 );

    // node.lst()->definitions()->accept( *this );

    // // for( const auto& definition : *specification.lst()->definitions() )
    // // {
    // //     if( definition->id() != Node::ID::INVARIANT_DEFINITION )
    // //     {
    // //         continue;
    // //     }

    // auto updateSet = m_updateSetManager.currentUpdateSet();
    // m_globalState.fireUpdateSet( updateSet );
    // m_updateSetManager.clear();
}

// void SymbolicStateInitializationVisitor::visit( InitDefinition& node )
// {
//     assert( node.programFunction() and "checked during frame size determination pass!" );
//     node.programFunction()->accept( *this );
// }

void SymbolicStateInitializationVisitor::visit( FunctionDefinition& node )
{
    Transaction transaction( &m_updateSetManager, Semantics::Parallel, 100 );
    if( node.symbolic() )
    {
        m_environment.addFunctionDeclaration( node.identifier()->name(), *node.type() );
    }
    SymbolicExecutionVisitor executionVisitor(
        m_locationRegistry, m_globalState, m_updateSetManager, ReferenceConstant(), m_environment );
    node.initially()->accept( executionVisitor );
    transaction.merge();
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
