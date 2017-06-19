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

#include "NumericExecutionPass.h"

#include <stdexcept>
#include <thread>

#include "../stdhl/cpp/Default.h"
#include "../stdhl/cpp/Enum.h"
#include "../stdhl/cpp/Hash.h"

#include "../pass/src/PassRegistry.h"
#include "../pass/src/PassResult.h"
#include "../pass/src/PassUsage.h"

#include "../casm-ir/src/Instruction.h"
#include "../casm-ir/src/Value.h"

#include "../casm-rt/src/Value.h"

#include "../Exception.h"
#include "../Logger.h"
#include "../analyze/ConsistencyCheckPass.h"
#include "../ast/EmptyVisitor.h"
#include "../ast/RecursiveVisitor.h"
#include "../ast/Specification.h"

#include "Frame.h"
#include "FunctionState.h"
#include "LocationRegistry.h"
#include "ReferenceConstant.h"
#include "Stack.h"
#include "UpdateSet.h"

using namespace libcasm_fe;
using namespace Ast;

namespace ir = libcasm_ir;

char NumericExecutionPass::id = 0;

static libpass::PassRegistration< NumericExecutionPass > PASS(
    "NumericExecutionPass",
    "execute numerically over the AST input specification", "ast-exec-num", 0 );

class ConstantStack : public Stack< ir::Constant >
{
  public:
    using Stack::Stack;

    using Stack::pop;

    template < typename T >
    T pop( void )
    {
        const auto& value = Stack::pop();
        assert( ir::isa< T >( value ) );
        return static_cast< const T& >( value );
    }
};

struct ConstantsHash
{
    inline std::size_t operator()(
        const std::vector< ir::Constant >& constants ) const
    {
        return libstdhl::Hash::value( constants );
    }
};

/**
 * @brief Represents an update
 */
struct Update
{
    ir::Constant value; /**< The value of the update */
    SourceLocation
        sourceLocation; /**< The source-code location of the update producer */
};

struct UpdateEquals
    : public std::binary_function< const Update&, const Update&, bool >
{
    bool operator()( const Update& lhs, const Update& rhs ) const
    {
        return lhs.value == rhs.value;
    }
};

struct LocationRegistryDetails
{
    using Function = std::string;
    using FunctionHash = std::hash< Function >;
    using FunctionEquals = std::equal_to< Function >;
    using Arguments = std::vector< ir::Constant >;
    using ArgumentsHash = ConstantsHash;
    using ArgumentsEquals = std::equal_to< Arguments >;
};

using ExecutionLocationRegistry = LocationRegistry< LocationRegistryDetails >;

struct UpdateSetDetails
{
    using Location = ExecutionLocationRegistry::Location;
    using Value = Update;
    using LocationHash = ExecutionLocationRegistry::LocationHash;
    using LocationEquals = ExecutionLocationRegistry::LocationEquals;
    using ValueEquals = UpdateEquals;
};

using ExecutionUpdateSet = UpdateSet< UpdateSetDetails >;
using ForkGuard = UpdateSetForkGuard< ExecutionUpdateSet >;
using Semantics = ExecutionUpdateSet::Semantics;

class Storage
{
    using Location = ExecutionLocationRegistry::Location;
    using Value = ir::Constant;

    struct FunctionStateDetails
    {
        using Location = Storage::Location;
        using Value = Storage::Value;
        using LocationHash = ExecutionLocationRegistry::LocationHash;
        using LocationEquals = ExecutionLocationRegistry::LocationEquals;
    };

    using ExecutionFunctionState = FunctionState< FunctionStateDetails >;

  public:
    Storage( void );

    void fireUpdateSet( ExecutionUpdateSet* updateSet );

    void set( const Location& location, const Value& value );
    void remove( const Location& location );
    std::experimental::optional< Value > get( const Location& location ) const;

    const ExecutionFunctionState& programState( void ) const;

  private:
    /**
     * Program function state is stored separately to allow efficient iteration
     * over all program locations (e.g. when determining the set of runnable
     * agents).
     */
    ExecutionFunctionState m_programState;
    ExecutionFunctionState m_functionState;
};

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
    if( location.function() == "program" )
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
    if( location.function() == "program" )
    {
        m_programState.remove( location );
    }
    else
    {
        m_functionState.remove( location );
    }
}

std::experimental::optional< Storage::Value > Storage::get(
    const Location& location ) const
{
    if( location.function() == "program" )
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

class ExecutionVisitor final : public EmptyVisitor
{
  public:
    ExecutionVisitor( ExecutionLocationRegistry& locationRegistry,
        const Storage& globalState,
        UpdateSetManager< ExecutionUpdateSet >& updateSetManager,
        const ir::Constant& agentId );

    /**
     * Executes the rule reference stored in \a value.
     *
     * @note It only support rules without arguments.
     *
     * @param value Rule reference (must be defined and the atom reference type
     *        must be RULE)
     */
    void execute( const ReferenceConstant& value );

    void visit( VariableDefinition& node ) override;
    void visit( FunctionDefinition& node ) override;
    void visit( DerivedDefinition& node ) override;
    void visit( RuleDefinition& node ) override;
    void visit( EnumerationDefinition& node ) override;

    void visit( ValueAtom& node ) override;
    void visit( ReferenceAtom& node ) override;
    void visit( UndefAtom& node ) override;
    void visit( DirectCallExpression& node ) override;
    void visit( IndirectCallExpression& node ) override;
    void visit( UnaryExpression& node ) override;
    void visit( BinaryExpression& node ) override;
    void visit( RangeExpression& node ) override;
    void visit( ListExpression& node ) override;
    void visit( ConditionalExpression& node ) override;
    void visit( UniversalQuantifierExpression& node ) override;
    void visit( ExistentialQuantifierExpression& node ) override;

    void visit( ConditionalRule& node ) override;
    void visit( CaseRule& node ) override;
    void visit( LetRule& node ) override;
    void visit( ForallRule& node ) override;
    void visit( ChooseRule& node ) override;
    void visit( IterateRule& node ) override;
    void visit( BlockRule& node ) override;
    void visit( SequenceRule& node ) override;
    void visit( UpdateRule& node ) override;
    void visit( CallRule& node ) override;

    void visit( ExpressionCase& node ) override;
    void visit( DefaultCase& node ) override;

  private:
    u1 hasEmptyUpdateSet( void ) const;

    std::unique_ptr< Frame > makeFrame( const CallExpression::Ptr& call,
        const Node::Ptr& callee, std::size_t numberOfLocals );

    void invokeBuiltin( ir::Value::ID id, const ir::Type::Ptr& type );

    enum class ValidationFlag
    {
        ValueMustBeDefined,
    };
    using ValidationFlags = libstdhl::Enum::Flags< ValidationFlag >;

    /**
     * Checks if the \a value is correct, i.e. if it complies to the \a type
     * specification.
     *
     * @param value The value whose correcteness should be checked
     * @param type The specified type
     * @param flags Disables or enables various validation properties
     *
     * @throws std::domain_error in case of an invalid value
     */
    void validateValue( const ir::Constant& value,
        const libcasm_ir::Type::Ptr& type,
        ValidationFlags flags = ValidationFlags() );

    void handleMergeConflict(
        const Node& node, const ExecutionUpdateSet::Conflict& conflict ) const;

  private:
    const Storage& m_globalState;
    ExecutionLocationRegistry& m_locationRegistry;
    UpdateSetManager< ExecutionUpdateSet >& m_updateSetManager;
    const ir::Constant& m_agentId;

    ConstantStack m_evaluationStack;
    FrameStack m_frameStack;
};

ExecutionVisitor::ExecutionVisitor( ExecutionLocationRegistry& locationRegistry,
    const Storage& globalState,
    UpdateSetManager< ExecutionUpdateSet >& updateSetManager,
    const ir::Constant& agentId )
: m_globalState( globalState )
, m_locationRegistry( locationRegistry )
, m_updateSetManager( updateSetManager )
, m_agentId( agentId )
, m_evaluationStack()
, m_frameStack()
{
}

void ExecutionVisitor::execute( const ReferenceConstant& value )
{
    assert( value.defined() && "Reference must be defined" );

    const auto& atom = value.atom();
    assert( ( atom->referenceType() == ReferenceAtom::ReferenceType::RULE )
            && "Must be a rule reference" );

    const auto& rule
        = std::static_pointer_cast< RuleDefinition >( atom->reference() );
    assert( ( rule->arguments()->size() == 0 )
            && "Only parameter-less rules are supported" );

    m_frameStack.push(
        makeFrame( nullptr, rule, rule->maximumNumberOfLocals() ) );
    rule->accept( *this );
    m_frameStack.pop();
}

void ExecutionVisitor::visit( VariableDefinition& node )
{
    const auto* frame = m_frameStack.top();
    m_evaluationStack.push( frame->local( node.localIndex() ) );
}

void ExecutionVisitor::visit( FunctionDefinition& node )
{
    auto* frame = m_frameStack.top();

    // validate arguments
    const auto& argumentTypes = node.type()->arguments();
    for( std::size_t i = 0; i < argumentTypes.size(); ++i )
    {
        const auto& argumentType = argumentTypes.at( i );
        const auto& argumentValue = frame->local( i );

        try
        {
            validateValue( argumentValue, argumentType,
                ValidationFlag::ValueMustBeDefined );
        }
        catch( const std::domain_error& e )
        {
            const auto& argumentDefinition = node.argumentTypes()->at( i );
            const auto& callArgument = frame->call()->arguments()->at( i );

            throw RuntimeException( { callArgument->sourceLocation(),
                                        argumentDefinition->sourceLocation() },
                e.what(),
                m_frameStack.generateBacktrace( node.sourceLocation() ),
                Code::FunctionArgumentInvalidValueAtLookup );
        }
    }

    const auto location = m_locationRegistry.lookup(
        node.identifier()->name(), frame->locals() );
    if( not location )
    {
        // location is not registered -> no update and no state
        node.defaultValue()->accept( *this ); // return value already on stack
        return;
    }

    const auto update = m_updateSetManager.lookup( *location );
    if( update )
    {
        m_evaluationStack.push( update->value );
        return;
    }

    const auto function = m_globalState.get( *location );
    if( function )
    {
        m_evaluationStack.push( function.value() );
        return;
    }

    node.defaultValue()->accept( *this ); // return value already on stack
}

void ExecutionVisitor::visit( DerivedDefinition& node )
{
    auto* frame = m_frameStack.top();

    // validate arguments
    const auto& argumentTypes = node.type()->arguments();
    for( std::size_t i = 0; i < argumentTypes.size(); ++i )
    {
        const auto& argumentType = argumentTypes.at( i );
        const auto& argumentValue = frame->local( i );

        try
        {
            validateValue( argumentValue, argumentType );
        }
        catch( const std::domain_error& e )
        {
            const auto& argumentDefinition = node.arguments()->at( i );
            const auto& callArgument = frame->call()->arguments()->at( i );

            throw RuntimeException( { callArgument->sourceLocation(),
                                        argumentDefinition->sourceLocation() },
                e.what(),
                m_frameStack.generateBacktrace( node.sourceLocation() ),
                Code::DerivedArgumentValueInvalid );
        }
    }

    node.expression()->accept( *this ); // return value already on stack

    // validate return value
    const auto& returnType = node.type()->ptr_result();
    const auto& returnValue = m_evaluationStack.top(); // keep it on stack
    try
    {
        validateValue( returnValue, returnType );
    }
    catch( const std::domain_error& e )
    {
        throw RuntimeException( { node.expression()->sourceLocation() },
            e.what(), m_frameStack.generateBacktrace( node.sourceLocation() ),
            Code::DerivedReturnValueInvalid );
    }
}

void ExecutionVisitor::visit( RuleDefinition& node )
{
    node.rule()->accept( *this );

    const auto& returnType = node.type()->ptr_result();
    if( not returnType->isVoid() )
    {
        if( false /* update set has result update */ )
        {
            // const auto& value = TODO get update value and REMOVE update from
            // update set
            // m_evaluationStack.push( value );
        }
        else
        {
            m_evaluationStack.push( ir::Constant::undef( returnType ) );
        }
    }
}

void ExecutionVisitor::visit( EnumerationDefinition& node )
{
    assert( node.type()->isEnumeration() );
    const auto& enumType
        = std::static_pointer_cast< ir::EnumerationType >( node.type() );
    m_evaluationStack.push( ir::EnumerationConstant( enumType ) );
}

void ExecutionVisitor::visit( ValueAtom& node )
{
    m_evaluationStack.push( *node.value() );
}

void ExecutionVisitor::visit( ReferenceAtom& node )
{
    m_evaluationStack.push( ReferenceConstant( node.ptr< ReferenceAtom >() ) );
}

void ExecutionVisitor::visit( UndefAtom& node )
{
    m_evaluationStack.push( ir::Constant::undef( node.type() ) );
}

void ExecutionVisitor::visit( DirectCallExpression& node )
{
    switch( node.targetType() )
    {
        case CallExpression::TargetType::FUNCTION: // [[fallthrough]]
        case CallExpression::TargetType::DERIVED:
        {
            const auto& definition = node.targetDefinition();
            m_frameStack.push( makeFrame( node.ptr< CallExpression >(),
                definition, node.arguments()->size() ) );
            definition->accept( *this );
            m_frameStack.pop();
            break;
        }
        case CallExpression::TargetType::RULE:
        {
            const auto& rule = std::static_pointer_cast< RuleDefinition >(
                node.targetDefinition() );
            m_frameStack.push( makeFrame( node.ptr< CallExpression >(), rule,
                rule->maximumNumberOfLocals() ) );
            rule->accept( *this );
            m_frameStack.pop();
            break;
        }
        case CallExpression::TargetType::BUILTIN:
        {
            m_frameStack.push( makeFrame( node.ptr< CallExpression >(), nullptr,
                node.arguments()->size() ) );
            try
            {
                invokeBuiltin( node.targetBuiltinId(), node.type() );
            }
            catch( const std::exception& e )
            {
                throw RuntimeException( node.sourceLocation(),
                    "builtin has thrown an exception: "
                        + std::string( e.what() ),
                    m_frameStack.generateBacktrace( node.sourceLocation() ),
                    Code::AssertInvalidExpression );
            }
            m_frameStack.pop();
            break;
        }
        case CallExpression::TargetType::TYPE_DOMAIN:
        {
            node.targetDefinition()->accept( *this );
            break;
        }
        case CallExpression::TargetType::CONSTANT:
        {
            assert( node.type()->isEnumeration() );
            const auto& enumType
                = std::static_pointer_cast< ir::EnumerationType >(
                    node.type() );
            m_evaluationStack.push( ir::EnumerationConstant(
                enumType, node.identifier()->baseName() ) );
            break;
        }
        case CallExpression::TargetType::VARIABLE:
        {
            node.targetDefinition()->accept( *this );
            break;
        }
        case CallExpression::TargetType::SELF:
        {
            m_evaluationStack.push( m_agentId );
            break;
        }
        case CallExpression::TargetType::UNKNOWN:
        {
            assert( !"cannot call an unknown target" );
            break;
        }
    }
}

void ExecutionVisitor::visit( IndirectCallExpression& node )
{
    node.expression()->accept( *this );
    const auto& value = m_evaluationStack.pop< ReferenceConstant >();
    if( not value.defined() )
    {
        throw RuntimeException( node.expression()->sourceLocation(),
            "cannot call an undefined target",
            m_frameStack.generateBacktrace( node.sourceLocation() ),
            Code::Unspecified );
    }

    const auto& atom = value.atom();
    switch( atom->referenceType() )
    {
        case ReferenceAtom::ReferenceType::FUNCTION: // [[fallthrough]]
        case ReferenceAtom::ReferenceType::DERIVED:
        {
            m_frameStack.push( makeFrame( node.ptr< CallExpression >(),
                atom->reference(), node.arguments()->size() ) );
            atom->reference()->accept( *this );
            m_frameStack.pop();
            break;
        }
        case ReferenceAtom::ReferenceType::RULE:
        {
            const auto& rule = std::static_pointer_cast< RuleDefinition >(
                atom->reference() );
            m_frameStack.push( makeFrame( node.ptr< CallExpression >(), rule,
                rule->maximumNumberOfLocals() ) );
            rule->accept( *this );
            m_frameStack.pop();
            break;
        }
        case ReferenceAtom::ReferenceType::BUILTIN:
        {
            m_frameStack.push( makeFrame( node.ptr< CallExpression >(), nullptr,
                node.arguments()->size() ) );
            try
            {
                invokeBuiltin( atom->builtinId(), node.type() );
            }
            catch( const std::exception& e )
            {
                throw RuntimeException( node.sourceLocation(),
                    "builtin has thrown an exception: "
                        + std::string( e.what() ),
                    m_frameStack.generateBacktrace( node.sourceLocation() ),
                    Code::Unspecified );
            }
            m_frameStack.pop();
            break;
        }
        case ReferenceAtom::ReferenceType::VARIABLE:
        {
            atom->reference()->accept( *this );
            break;
        }
        case ReferenceAtom::ReferenceType::UNKNOWN:
        {
            assert( !"cannot call an unknown target" );
            break;
        }
    }
}

void ExecutionVisitor::visit( UnaryExpression& node )
{
    node.expression()->accept( *this );
    const auto& value = m_evaluationStack.pop();

    try
    {
        const auto result
            = libcasm_rt::Value::execute_( node.op(), node.type(), &value, 1 );
        m_evaluationStack.push( result );
    }
    catch( const std::exception& e )
    {
        throw RuntimeException( node.sourceLocation(),
            "unary expression has thrown an exception: "
                + std::string( e.what() ),
            m_frameStack.generateBacktrace( node.sourceLocation() ),
            Code::Unspecified );
    }
}

void ExecutionVisitor::visit( BinaryExpression& node )
{
    node.left()->accept( *this );
    const auto& lhs = m_evaluationStack.pop();

    node.right()->accept( *this );
    const auto& rhs = m_evaluationStack.pop();

    try
    {
        const auto result
            = libcasm_rt::Value::execute( node.op(), node.type(), lhs, rhs );
        m_evaluationStack.push( result );
    }
    catch( const std::exception& e )
    {
        throw RuntimeException( node.sourceLocation(),
            "binary expression has thrown an exception: "
                + std::string( e.what() ),
            m_frameStack.generateBacktrace( node.sourceLocation() ),
            Code::Unspecified );
    }
}

void ExecutionVisitor::visit( RangeExpression& node )
{
    node.left()->accept( *this );
    const auto& lhs = m_evaluationStack.pop();

    node.right()->accept( *this );
    const auto& rhs = m_evaluationStack.pop();

    m_evaluationStack.push( ir::RangeConstant( node.type(), lhs, rhs ) );
}

void ExecutionVisitor::visit( ListExpression& node )
{
    // TODO
}

void ExecutionVisitor::visit( ConditionalExpression& node )
{
    node.condition()->accept( *this );
    const auto& condition = m_evaluationStack.pop< ir::BooleanConstant >();

    if( not condition.defined() )
    {
        throw RuntimeException( node.condition()->sourceLocation(),
            "condition must be true or false but was undef",
            m_frameStack.generateBacktrace( node.sourceLocation() ),
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

void ExecutionVisitor::visit( UniversalQuantifierExpression& node )
{
    bool result = true;
    bool defined = true;

    auto* frame = m_frameStack.top();
    const auto variableIndex = node.predicateVariable()->localIndex();

    node.universe()->accept( *this );
    const auto& universe = m_evaluationStack.pop();

    if( not universe.defined() )
    {
        throw RuntimeException( node.universe()->sourceLocation(),
            "universe must not be undef",
            m_frameStack.generateBacktrace( node.sourceLocation() ),
            Code::QuantifierExpressionInvalidUniverse );
    }

    universe.foreach( [&]( const ir::Constant& value ) {
        frame->setLocal( variableIndex, value );

        node.proposition()->accept( *this );
        const auto& prop = m_evaluationStack.pop< ir::BooleanConstant >();

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
        m_evaluationStack.push( ir::BooleanConstant( result ) );
    }
    else
    {
        if( result == false )
        {
            m_evaluationStack.push( ir::BooleanConstant( false ) );
        }
        else
        {
            m_evaluationStack.push( ir::BooleanConstant() );
        }
    }
}

void ExecutionVisitor::visit( ExistentialQuantifierExpression& node )
{
    bool result = false;
    bool defined = true;

    auto* frame = m_frameStack.top();
    const auto variableIndex = node.predicateVariable()->localIndex();

    node.universe()->accept( *this );
    const auto& universe = m_evaluationStack.pop();

    if( not universe.defined() )
    {
        throw RuntimeException( node.universe()->sourceLocation(),
            "universe must not be undef",
            m_frameStack.generateBacktrace( node.sourceLocation() ),
            Code::QuantifierExpressionInvalidUniverse );
    }

    universe.foreach( [&]( const ir::Constant& value ) {
        frame->setLocal( variableIndex, value );

        node.proposition()->accept( *this );
        const auto& prop = m_evaluationStack.pop< ir::BooleanConstant >();

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
        m_evaluationStack.push( ir::BooleanConstant( result ) );
    }
    else
    {
        if( result == true )
        {
            m_evaluationStack.push( ir::BooleanConstant( true ) );
        }
        else
        {
            m_evaluationStack.push( ir::BooleanConstant() );
        }
    }
}

void ExecutionVisitor::visit( ConditionalRule& node )
{
    node.condition()->accept( *this );
    const auto& condition = m_evaluationStack.pop< ir::BooleanConstant >();

    if( not condition.defined() )
    {
        throw RuntimeException( node.condition()->sourceLocation(),
            "condition must be true or false but was undef",
            m_frameStack.generateBacktrace( node.sourceLocation() ),
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
    const auto& value = m_evaluationStack.pop();

    Case::Ptr defaultCase = nullptr;

    for( const auto& _case : *node.cases() )
    {
        if( _case->id() == Node::ID::DEFAULT_CASE )
        {
            assert( not defaultCase
                    && "case rule should not contain multiple default cases" );
            defaultCase = _case;
            continue;
        }

        _case->accept( *this ); // only evaluates the case expression
        const auto& caseValue = m_evaluationStack.pop();
        if( value == caseValue )
        {
            // match
            _case->rule()->accept( *this );
            return;
        }
    }

    if( defaultCase )
    {
        defaultCase->rule()->accept( *this );
    }
}

void ExecutionVisitor::visit( LetRule& node )
{
    node.expression()->accept( *this );
    const auto& value = m_evaluationStack.pop();

    auto* frame = m_frameStack.top();
    const auto variableIndex = node.variable()->localIndex();
    frame->setLocal( variableIndex, value );

    node.rule()->accept( *this );
}

void ExecutionVisitor::visit( ForallRule& node )
{
    ForkGuard parGuard( &m_updateSetManager, Semantics::Parallel, 100UL );

    auto* frame = m_frameStack.top();
    const auto variableIndex = node.variable()->localIndex();

    node.universe()->accept( *this );
    const auto& universe = m_evaluationStack.pop();

    universe.foreach( [&]( const ir::Constant& value ) {
        frame->setLocal( variableIndex, value );
        node.rule()->accept( *this );
    } );

    try
    {
        parGuard.merge();
    }
    catch( const ExecutionUpdateSet::Conflict& conflict )
    {
        handleMergeConflict( node, conflict );
    }
}

void ExecutionVisitor::visit( ChooseRule& node )
{
    auto* frame = m_frameStack.top();
    const auto variableIndex = node.variable()->localIndex();

    node.universe()->accept( *this );
    const auto& universe = m_evaluationStack.pop();

    frame->setLocal( variableIndex, universe.choose() );
    node.rule()->accept( *this );
}

void ExecutionVisitor::visit( IterateRule& node )
{
    ForkGuard seqGuard( &m_updateSetManager, Semantics::Sequential, 100UL );

    while( true )
    {
        // uses a new parallel update set on each iteration only to check if the
        // current iteration actually produced any updates
        ForkGuard parGuard( &m_updateSetManager, Semantics::Parallel, 100UL );
        node.rule()->accept( *this );
        if( hasEmptyUpdateSet() )
        {
            // the current iteration hasn't produced any updates -> done
            break;
        }
        parGuard.merge(); // should not throw a merge conflict because of the
                          // surrounding sequential block, thus no conflict
                          // handling required
    }

    try
    {
        seqGuard.merge();
    }
    catch( const ExecutionUpdateSet::Conflict& conflict )
    {
        handleMergeConflict( node, conflict );
    }
}

void ExecutionVisitor::visit( BlockRule& node )
{
    ForkGuard parGuard( &m_updateSetManager, Semantics::Parallel, 100UL );
    node.rules()->accept( *this );

    try
    {
        parGuard.merge();
    }
    catch( const ExecutionUpdateSet::Conflict& conflict )
    {
        handleMergeConflict( node, conflict );
    }
}

void ExecutionVisitor::visit( SequenceRule& node )
{
    ForkGuard seqGuard( &m_updateSetManager, Semantics::Sequential, 100UL );
    node.rules()->accept( *this );

    try
    {
        seqGuard.merge();
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
    const auto& updateValue = m_evaluationStack.pop();
    try
    {
        validateValue( updateValue, function->type()->ptr_result() );
    }
    catch( const std::domain_error& e )
    {
        throw RuntimeException( { expression->sourceLocation() }, e.what(),
            m_frameStack.generateBacktrace( node.sourceLocation() ),
            Code::FunctionUpdateInvalidValue );
    }

    // evaluate function arguments
    const auto& arguments = function->arguments();
    const auto& argumentTypes = function->type()->arguments();
    std::vector< ir::Constant > argumentValues;
    argumentValues.reserve( arguments->size() );
    for( std::size_t i = 0; i < arguments->size(); ++i )
    {
        const auto& argument = arguments->at( i );
        const auto& argumentType = argumentTypes.at( i );

        argument->accept( *this );
        const auto& value = m_evaluationStack.pop();

        try
        {
            validateValue(
                value, argumentType, ValidationFlag::ValueMustBeDefined );
        }
        catch( const std::domain_error& e )
        {
            throw RuntimeException( { argument->sourceLocation() }, e.what(),
                m_frameStack.generateBacktrace( node.sourceLocation() ),
                Code::FunctionArgumentsInvalidValue );
        }

        argumentValues.emplace_back( value );
    }

    const auto location = m_locationRegistry.get(
        function->identifier()->path(), argumentValues );
    const Update update{ updateValue, node.sourceLocation() };

    try
    {
        m_updateSetManager.add( location, update );
    }
    catch( const ExecutionUpdateSet::Conflict& e )
    {
        const auto& conflictingUpdate = e.conflictingUpdate();
        const auto& existingUpdate = e.existingUpdate();

        const auto& existingLocation = existingUpdate.first;

        const auto& conflictingValue = conflictingUpdate.second;
        const auto& existingValue = existingUpdate.second;

        const auto info
            = "Conflict while adding update " + existingLocation.function()
              //+ to_string( existingLocation.arguments )
              + " = " + conflictingValue.value.description()
              + ". Update for same location  with another value '"
              + existingValue.value.description() + "' exists already.";
        throw RuntimeException(
            { existingValue.sourceLocation, conflictingValue.sourceLocation },
            info, m_frameStack.generateBacktrace( node.sourceLocation() ),
            libcasm_fe::Code::UpdateSetClash );
    }
}

void ExecutionVisitor::visit( CallRule& node )
{
    node.call()->accept( *this );

    const auto& returnType = node.call()->type()->ptr_result();
    if( not returnType->isVoid() )
    {
        m_evaluationStack.pop(); // drop return value
    }
}

void ExecutionVisitor::visit( ExpressionCase& node )
{
    node.expression()->accept( *this );
    // note: rule will be invoked in visit(CaseRule) if expressions match
}

void ExecutionVisitor::visit( DefaultCase& node )
{
    assert( !"default case should not be executed, "
             "accept rule of default case instead!" );
    // note: rule will be invoked in visit(CaseRule)
}

u1 ExecutionVisitor::hasEmptyUpdateSet( void ) const
{
    return m_updateSetManager.currentUpdateSet()->empty();
}

std::unique_ptr< Frame > ExecutionVisitor::makeFrame(
    const CallExpression::Ptr& call, const Node::Ptr& callee,
    std::size_t numberOfLocals )
{
    auto frame = libstdhl::make_unique< Frame >( call, callee, numberOfLocals );

    if( call != nullptr )
    {
        assert( numberOfLocals >= call->arguments()->size() );

        std::size_t localIndex = 0;
        for( const auto& argument : *call->arguments() )
        {
            argument->accept( *this );
            const auto& value = m_evaluationStack.pop();
            frame->setLocal( localIndex, value );
            ++localIndex;
        }
    }

    return frame;
}

void ExecutionVisitor::invokeBuiltin(
    ir::Value::ID id, const ir::Type::Ptr& type )
{
    const auto& locals = m_frameStack.top()->locals();

    const auto result
        = libcasm_rt::Value::execute_( id, type, locals.data(), locals.size() );

    const auto& returnType = type->ptr_result();
    if( not returnType->isVoid() )
    {
        m_evaluationStack.push( result );
    }
}

void ExecutionVisitor::validateValue( const ir::Constant& value,
    const libcasm_ir::Type::Ptr& type, ValidationFlags flags )
{
    if( flags.isSet( ValidationFlag::ValueMustBeDefined )
        and not value.defined() )
    {
        throw std::domain_error(
            "value isn't defined, but undef isn't allowed" );
    }

    // TODO type->isValid( value );
}

void ExecutionVisitor::handleMergeConflict(
    const Node& node, const ExecutionUpdateSet::Conflict& conflict ) const
{
    const auto& conflictingUpdate = conflict.conflictingUpdate();
    const auto& existingUpdate = conflict.existingUpdate();

    const auto& existingLocation = existingUpdate.first;

    const auto& conflictingValue = conflictingUpdate.second;
    const auto& existingValue = existingUpdate.second;

    const auto info
        = "Conflict while merging updateset " + existingLocation.function()
          + " at line "
          + std::to_string( conflictingValue.sourceLocation.begin.line )
          + " with value '" + conflictingValue.value.description() + "'"
          + " and at line "
          + std::to_string( existingValue.sourceLocation.begin.line )
          + " with value '" + existingValue.value.description() + "'";
    throw RuntimeException(
        { existingValue.sourceLocation, conflictingValue.sourceLocation }, info,
        m_frameStack.generateBacktrace( node.sourceLocation() ),
        libcasm_fe::Code::UpdateSetMergeConflict );
}

class StateInitializationVisitor final : public EmptyVisitor
{
  public:
    StateInitializationVisitor(
        ExecutionLocationRegistry& locationRegistry, Storage& globalState );

    void visit( Specification& node ) override;

    void visit( FunctionDefinition& node ) override;

  private:
    Storage& m_globalState;
    ExecutionLocationRegistry& m_locationRegistry;
    UpdateSetManager< ExecutionUpdateSet > m_updateSetManager;
};

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
    m_updateSetManager.fork( Semantics::Sequential, 100UL );

    node.definitions()->accept( *this );

    auto updateSet = m_updateSetManager.currentUpdateSet();
    m_globalState.fireUpdateSet( updateSet );
    m_updateSetManager.clear();
}

void StateInitializationVisitor::visit( FunctionDefinition& node )
{
    ForkGuard parGuard( &m_updateSetManager, Semantics::Parallel, 100UL );
    ExecutionVisitor executionVisitor( m_locationRegistry, m_globalState,
        m_updateSetManager, ReferenceConstant() );
    node.initializers()->accept( executionVisitor );
    parGuard.merge();
}

class Agent
{
  public:
    Agent( ExecutionLocationRegistry& locationRegistry,
        const Storage& globalState, const ir::Constant& agentId,
        const ReferenceConstant& rule );

    void run( void );

    ExecutionUpdateSet* updateSet( void ) const;

  private:
    const Storage& m_globalState;
    ExecutionLocationRegistry& m_locationRegistry;
    const ir::Constant& m_agentId;
    const ReferenceConstant& m_rule;
    UpdateSetManager< ExecutionUpdateSet > m_updateSetManager;
};

Agent::Agent( ExecutionLocationRegistry& locationRegistry,
    const Storage& globalState, const ir::Constant& agentId,
    const ReferenceConstant& rule )
: m_globalState( globalState )
, m_locationRegistry( locationRegistry )
, m_agentId( agentId )
, m_rule( rule )
, m_updateSetManager()
{
}

void Agent::run( void )
{
    ExecutionVisitor executionVisitor(
        m_locationRegistry, m_globalState, m_updateSetManager, m_agentId );
    executionVisitor.execute( m_rule );
}

ExecutionUpdateSet* Agent::updateSet( void ) const
{
    return m_updateSetManager.currentUpdateSet();
}

class DispatchStrategy
{
  public:
    virtual void dispatch( std::vector< Agent >& agents ) = 0;
};

class ParallelDispatchStrategy : public DispatchStrategy
{
  public:
    void dispatch( std::vector< Agent >& agents ) override;
};

void ParallelDispatchStrategy::dispatch( std::vector< Agent >& agents )
{
    if( agents.size() == 1 )
    {
        agents.at( 0 ).run();
    }
    else
    {
        std::vector< std::thread > threads;
        threads.reserve( agents.size() );
        for( auto& agent : agents )
        {
            threads.emplace_back( [&] { agent.run(); } );
        }
        for( auto& thread : threads )
        {
            thread.join();
        }
    }
}

class SequentialDispatchStrategy : public DispatchStrategy
{
  public:
    void dispatch( std::vector< Agent >& agents ) override;
};

void SequentialDispatchStrategy::dispatch( std::vector< Agent >& agents )
{
    for( auto& agent : agents )
    {
        agent.run();
    }
}

class AgentScheduler
{
  public:
    AgentScheduler(
        ExecutionLocationRegistry& locationRegistry, Storage& globalState );

    void setDispatchStrategy(
        std::unique_ptr< DispatchStrategy > dispatchStrategy );

    /**
     * Performs an ASM step.
     */
    void step( void );

    /**
     * @return A boolean value indicating wheter the ASM has reached an end
     *         state, meaning that no further steps need to be done.
     */
    bool done( void ) const;

    std::size_t numberOfSteps( void ) const;

  private:
    std::vector< Agent > collectAgents( void ) const;
    void dispatch( std::vector< Agent >& agents );
    ExecutionUpdateSet* collectUpdates( const std::vector< Agent >& agents );

  private:
    std::unique_ptr< DispatchStrategy > m_dispatchStrategy;
    Storage& m_globalState;
    ExecutionLocationRegistry& m_locationRegistry;
    UpdateSetManager< ExecutionUpdateSet > m_updateSetManager;
    bool m_done;
    std::size_t m_stepCounter;
};

AgentScheduler::AgentScheduler(
    ExecutionLocationRegistry& locationRegistry, Storage& globalState )
: m_dispatchStrategy( libstdhl::make_unique< SequentialDispatchStrategy >() )
, m_globalState( globalState )
, m_locationRegistry( locationRegistry )
, m_updateSetManager()
, m_done( false )
, m_stepCounter( 0UL )
{
}

void AgentScheduler::setDispatchStrategy(
    std::unique_ptr< DispatchStrategy > dispatchStrategy )
{
    m_dispatchStrategy = std::move( dispatchStrategy );
}

void AgentScheduler::step( void )
{
    auto agents = collectAgents();
    if( agents.empty() )
    {
        m_done = true;
        return;
    }

    dispatch( agents );

    auto* updates = collectUpdates( agents );
    m_globalState.fireUpdateSet( updates );
    m_done = updates->empty();
    m_updateSetManager.clear();

    ++m_stepCounter;
}

bool AgentScheduler::done( void ) const
{
    return m_done;
}

std::size_t AgentScheduler::numberOfSteps( void ) const
{
    return m_stepCounter;
}

std::vector< Agent > AgentScheduler::collectAgents( void ) const
{
    std::vector< Agent > agents;

    const auto& programs = m_globalState.programState();
    const auto end = programs.end();
    for( auto it = programs.begin(); it != end; ++it )
    {
        const auto& location = it.key();
        const auto& value = it.value();

        const auto& agentId = location.arguments().at( 0 );

        assert( ir::isa< ReferenceConstant >( value ) );
        const auto& rule = static_cast< const ReferenceConstant& >( value );

        if( rule.defined() )
        {
            agents.emplace_back(
                Agent( m_locationRegistry, m_globalState, agentId, rule ) );
        }
    }

    return agents;
}

void AgentScheduler::dispatch( std::vector< Agent >& agents )
{
    assert( m_dispatchStrategy );
    m_dispatchStrategy->dispatch( agents );
}

ExecutionUpdateSet* AgentScheduler::collectUpdates(
    const std::vector< Agent >& agents )
{
    if( agents.size() == 1 )
    {
        return agents.at( 0 ).updateSet();
    }
    else
    {
        m_updateSetManager.fork( Semantics::Parallel, 100UL );
        auto* updates = m_updateSetManager.currentUpdateSet();
        for( const auto& agent : agents )
        {
            agent.updateSet()->mergeInto( updates );
        }
        return updates;
    }
}

void NumericExecutionPass::usage( libpass::PassUsage& pu )
{
    pu.require< ConsistencyCheckPass >();
}

u1 NumericExecutionPass::run( libpass::PassResult& pr )
{
    Logger log( &id, stream() );

    const auto data = pr.result< ConsistencyCheckPass >();
    const auto specification = data->specification();

    ExecutionLocationRegistry locationRegistry;
    Storage globalState;

    AgentScheduler scheduler( locationRegistry, globalState );
    /*scheduler.setDispatchStrategy(
        libstdhl::make_unique< ParallelDispatchStrategy >() );*/

    try
    {
        StateInitializationVisitor stateInitializationVisitor(
            locationRegistry, globalState );
        specification->accept( stateInitializationVisitor );

        while( not scheduler.done() )
        {
            scheduler.step();
        }

        log.info( "Finished execution after "
                  + std::to_string( scheduler.numberOfSteps() )
                  + " steps" );
    }
    catch( const RuntimeException& e )
    {
        log.error( e );
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
