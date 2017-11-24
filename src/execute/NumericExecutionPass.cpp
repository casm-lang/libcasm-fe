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

#include "NumericExecutionPass.h"

#include "../Exception.h"
#include "../Logger.h"
#include "../Specification.h"
#include "../analyze/FrameSizeDeterminationPass.h"
#include "../ast/Definition.h"
#include "../ast/EmptyVisitor.h"
#include "../ast/Expression.h"
#include "../ast/RecursiveVisitor.h"
#include "../ast/Rule.h"
#include "Frame.h"
#include "FunctionState.h"
#include "LocationRegistry.h"
#include "ReferenceConstant.h"
#include "Stack.h"
#include "UpdateSet.h"

#include <libcasm-rt/Value>

#include <libcasm-ir/Exception>
#include <libcasm-ir/Instruction>
#include <libcasm-ir/Value>

#include <libpass/PassRegistry>
#include <libpass/PassResult>
#include <libpass/PassUsage>

#include <libstdhl/Enum>
#include <libstdhl/Hash>

#include <stdexcept>
#include <thread>

using namespace libcasm_fe;
using namespace Ast;

namespace IR = libcasm_ir;
namespace RT = libcasm_rt;

char NumericExecutionPass::id = 0;

static libpass::PassRegistration< NumericExecutionPass > PASS(
    "NumericExecutionPass",
    "execute numerically over the AST input specification", "ast-exec-num", 0 );

class ConstantStack : public Stack< IR::Constant >
{
  public:
    using Stack::Stack;

    using Stack::pop;

    template < typename T >
    T pop( void )
    {
        const auto value = Stack::pop();
        assert( IR::isa< T >( value ) );
        return static_cast< const T& >( value );
    }
};

struct ConstantsHash
{
    inline std::size_t operator()(
        const std::vector< IR::Constant >& constants ) const
    {
        return libstdhl::Hash::value( constants );
    }
};

/**
 * @brief Represents an update
 */
struct Update
{
    IR::Constant value;   /**< The value of the update */
    UpdateRule* producer; /**< The update producer */
    IR::Constant agent;   /**< The contributing agent */
                          // TODO maybe a list of agents (multi-agent case)?
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
    using Function = FunctionDefinition::UID;
    using FunctionHash = std::hash< Function >;
    using FunctionEquals = std::equal_to< Function >;
    using Arguments = std::vector< IR::Constant >;
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
using Transaction = UpdateSetTransaction< ExecutionUpdateSet >;
using Semantics = ExecutionUpdateSet::Semantics;

static std::string updateAsString( const ExecutionUpdateSet::Update& update )
{
    const auto& location = update.location;
    const auto& value = update.value;

    auto locationStr = value.producer->function()->identifier()->name();

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

class Storage
{
    using Location = ExecutionLocationRegistry::Location;
    using Value = IR::Constant;

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
    if( location.function() == FunctionDefinition::UID::PROGRAM )
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
    if( location.function() == FunctionDefinition::UID::PROGRAM )
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
    if( location.function() == FunctionDefinition::UID::PROGRAM )
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
        const IR::Constant& agentId );

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
    void visit( EnumeratorDefinition& node ) override;
    void visit( EnumerationDefinition& node ) override;

    void visit( TypeCastingExpression& node ) override;
    void visit( ValueAtom& node ) override;
    void visit( ReferenceAtom& node ) override;
    void visit( UndefAtom& node ) override;
    void visit( BasicType& node ) override;
    void visit( DirectCallExpression& node ) override;
    void visit( IndirectCallExpression& node ) override;
    void visit( MethodCallExpression& node ) override;
    void visit( UnaryExpression& node ) override;
    void visit( BinaryExpression& node ) override;
    void visit( RangeExpression& node ) override;
    void visit( ListExpression& node ) override;
    void visit( LetExpression& node ) override;
    void visit( ConditionalExpression& node ) override;
    void visit( ChooseExpression& node ) override;
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

  private:
    u1 hasEmptyUpdateSet( void ) const;

    std::unique_ptr< Frame > makeFrame(
        CallExpression* call, Node* callee, std::size_t numberOfLocals );

    /**
     * Calls the builtin with id \a id.
     *
     * It uses the locals of the current frame as argument values.
     *
     * @param node The AST node in whose context the invocation is performed
     *             (used for the error location and stack trace generation)
     * @param id ID of the builtin
     * @param type Relation type of the builtin
     *
     * @throws RuntimeException in case of an error
     */
    void invokeBuiltin(
        const Node& node, IR::Value::ID id, const IR::Type::Ptr& type );

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
     * @throws libcasm_IR::ValidationException in case of an invalid value
     */
    void validateValue( const IR::Constant& value,
        const IR::Type& type,
        ValidationFlags flags = {} ) const;

    /**
     * Validates the arguments, i.e. if the values comply to the argument types
     * \a argumentTypes.
     *
     * It uses the locals of the current frame as argument values.
     *
     * @param node The AST node in whose context the validation is performed
     *             (used for the error location and stack trace generation)
     * @param argumentTypes A list of arguments types used for the validation
     * @param flags Disables or enables various validation properties
     * @param errorCode Defines the error code which should be applied to the
     *                  exception in case of a validation error
     *
     * @throws RuntimeException in case of an invalid argument value with proper
     *                          error and location information
     */
    void validateArguments( const Node& node, const IR::Types& argumentTypes,
        ValidationFlags flags, Code errorCode ) const;

    void handleMergeConflict(
        const Node& node, const ExecutionUpdateSet::Conflict& conflict ) const;

  private:
    const Storage& m_globalState;
    ExecutionLocationRegistry& m_locationRegistry;
    UpdateSetManager< ExecutionUpdateSet >& m_updateSetManager;
    const IR::Constant& m_agentId;

    ConstantStack m_evaluationStack;
    FrameStack m_frameStack;
};

ExecutionVisitor::ExecutionVisitor( ExecutionLocationRegistry& locationRegistry,
    const Storage& globalState,
    UpdateSetManager< ExecutionUpdateSet >& updateSetManager,
    const IR::Constant& agentId )
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

    const auto& atom = value.value();
    assert( ( atom->referenceType() == ReferenceAtom::ReferenceType::RULE )
            && "Must be a rule reference" );

    const auto& rule
        = std::static_pointer_cast< RuleDefinition >( atom->reference() );
    assert( ( rule->arguments()->size() == 0 )
            && "Only parameter-less rules are supported" );

    m_frameStack.push(
        makeFrame( nullptr, rule.get(), rule->maximumNumberOfLocals() ) );
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
    validateArguments( node, node.type()->arguments(),
        ValidationFlag::ValueMustBeDefined,
        Code::FunctionArgumentInvalidValueAtLookup );

    const auto location
        = m_locationRegistry.lookup( node.uid(), m_frameStack.top()->locals() );
    if( location )
    {
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
    }

    node.defaultValue()->accept( *this ); // return value already on stack
}

void ExecutionVisitor::visit( DerivedDefinition& node )
{
    validateArguments(
        node, node.type()->arguments(), {}, Code::DerivedArgumentValueInvalid );

    node.expression()->accept( *this ); // return value already on stack

    // validate return value
    const auto& returnType = node.type()->result();
    const auto& returnValue = m_evaluationStack.top(); // keep it on stack
    try
    {
        validateValue( returnValue, returnType );
    }
    catch( const IR::ValidationException& e )
    {
        throw RuntimeException( { node.expression()->sourceLocation() },
            e.what(),
            m_frameStack.generateBacktrace( node.sourceLocation(), m_agentId ),
            Code::DerivedReturnValueInvalid );
    }
}

void ExecutionVisitor::visit( RuleDefinition& node )
{
    validateArguments(
        node, node.type()->arguments(), {}, Code::RuleArgumentValueInvalid );

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
    const auto& enumType
        = std::static_pointer_cast< IR::EnumerationType >( node.type() );
    m_evaluationStack.push(
        IR::EnumerationConstant( enumType, node.identifier()->name() ) );
}

void ExecutionVisitor::visit( EnumerationDefinition& node )
{
    assert( node.type()->isEnumeration() );
    const auto& enumType
        = std::static_pointer_cast< IR::EnumerationType >( node.type() );
    m_evaluationStack.push( IR::EnumerationConstant( enumType ) );
}

void ExecutionVisitor::visit( TypeCastingExpression& node )
{
    if( node.builtin() )
    {
        m_frameStack.push(
            makeFrame( &node, nullptr, node.arguments()->size() ) );
        invokeBuiltin( node, node.targetBuiltinId(), node.type() );
        m_frameStack.pop();
    }
    else
    {
        const auto& definition
            = std::static_pointer_cast< Definition >( node.targetDefinition() );
        m_frameStack.push( makeFrame(
            &node, definition.get(), definition->maximumNumberOfLocals() ) );
        definition->accept( *this );
        m_frameStack.pop();
    }
}

void ExecutionVisitor::visit( ValueAtom& node )
{
    m_evaluationStack.push( *node.value() );
}

void ExecutionVisitor::visit( ReferenceAtom& node )
{
    m_evaluationStack.push( ReferenceConstant( &node ) );
}

void ExecutionVisitor::visit( UndefAtom& node )
{
    m_evaluationStack.push( IR::Constant::undef( node.type() ) );
}

void ExecutionVisitor::visit( BasicType& node )
{
    const auto rangeType = std::make_shared< IR::RangeType >( node.type() );
    const auto range = std::make_shared< IR::Range >( rangeType );
    m_evaluationStack.push( IR::RangeConstant( rangeType, range ) );
}

void ExecutionVisitor::visit( DirectCallExpression& node )
{
    switch( node.targetType() )
    {
        case CallExpression::TargetType::FUNCTION: // [[fallthrough]]
        case CallExpression::TargetType::DERIVED:  // [[fallthrough]]
        case CallExpression::TargetType::RULE:
        {
            const auto& definition = std::static_pointer_cast< Definition >(
                node.targetDefinition() );
            m_frameStack.push( makeFrame( &node, definition.get(),
                definition->maximumNumberOfLocals() ) );
            definition->accept( *this );
            m_frameStack.pop();
            break;
        }
        case CallExpression::TargetType::BUILTIN:
        {
            m_frameStack.push(
                makeFrame( &node, nullptr, node.arguments()->size() ) );
            invokeBuiltin( node, node.targetBuiltinId(), node.type() );
            m_frameStack.pop();
            break;
        }
        case CallExpression::TargetType::TYPE_DOMAIN: // [[fallthrough]]
        case CallExpression::TargetType::CONSTANT:    // [[fallthrough]]
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
    const auto value = m_evaluationStack.pop< ReferenceConstant >();
    if( not value.defined() )
    {
        throw RuntimeException( node.expression()->sourceLocation(),
            "cannot call an undefined target",
            m_frameStack.generateBacktrace( node.sourceLocation(), m_agentId ),
            Code::Unspecified );
    }

    const auto& atom = value.value();
    switch( atom->referenceType() )
    {
        case ReferenceAtom::ReferenceType::FUNCTION: // [[fallthrough]]
        case ReferenceAtom::ReferenceType::DERIVED:  // [[fallthrough]]
        case ReferenceAtom::ReferenceType::RULE:
        {
            const auto& definition
                = std::static_pointer_cast< Definition >( atom->reference() );
            m_frameStack.push( makeFrame( &node, definition.get(),
                definition->maximumNumberOfLocals() ) );
            definition->accept( *this );
            m_frameStack.pop();
            break;
        }
        case ReferenceAtom::ReferenceType::BUILTIN:
        {
            m_frameStack.push(
                makeFrame( &node, nullptr, node.arguments()->size() ) );
            invokeBuiltin( node, atom->builtinId(), node.type() );
            m_frameStack.pop();
            break;
        }
        case ReferenceAtom::ReferenceType::UNKNOWN:
        {
            assert( !"cannot call an unknown target" );
            break;
        }
    }
}

void ExecutionVisitor::visit( MethodCallExpression& node )
{
    node.expression()->accept( *this );
    reinterpret_cast< DirectCallExpression& >( node ).accept( *this );
}

void ExecutionVisitor::visit( UnaryExpression& node )
{
    node.expression()->accept( *this );
    auto& value = m_evaluationStack.top();

    try
    {
        RT::Value::execute( node.op(), node.type(), value, value );
    }
    catch( const std::exception& e )
    {
        throw RuntimeException( node.sourceLocation(),
            "unary expression has thrown an exception: "
                + std::string( e.what() ),
            m_frameStack.generateBacktrace( node.sourceLocation(), m_agentId ),
            Code::Unspecified );
    }
}

void ExecutionVisitor::visit( BinaryExpression& node )
{
    node.left()->accept( *this );
    const auto lhs = m_evaluationStack.pop();

    node.right()->accept( *this );
    auto& rhs = m_evaluationStack.top();

    try
    {
        RT::Value::execute( node.op(), node.type(), rhs, lhs, rhs );
    }
    catch( const IR::Exception& e )
    {
        throw RuntimeException( node.sourceLocation(),
            "binary expression has thrown an exception: "
                + std::string( e.what() ),
            m_frameStack.generateBacktrace( node.sourceLocation(), m_agentId ),
            Code::Unspecified );
    }
}

void ExecutionVisitor::visit( RangeExpression& node )
{
    node.left()->accept( *this );
    const auto lhs = m_evaluationStack.pop();

    node.right()->accept( *this );
    const auto rhs = m_evaluationStack.pop();

    m_evaluationStack.push( IR::RangeConstant( node.type(), lhs, rhs ) );
}

void ExecutionVisitor::visit( ListExpression& node )
{
    // TODO
}

void ExecutionVisitor::visit( LetExpression& node )
{
    node.initializer()->accept( *this );
    const auto value = m_evaluationStack.pop();

    // validate value
    const auto& variableType = node.variable()->type()->result();
    try
    {
        validateValue( value, variableType );
    }
    catch( const IR::ValidationException& e )
    {
        throw RuntimeException( { node.initializer()->sourceLocation() },
            e.what(),
            m_frameStack.generateBacktrace( node.sourceLocation(), m_agentId ),
            Code::LetAssignedValueInvalid );
    }

    auto* frame = m_frameStack.top();
    const auto variableIndex = node.variable()->localIndex();
    frame->setLocal( variableIndex, value );

    node.expression()->accept( *this );
}

void ExecutionVisitor::visit( ConditionalExpression& node )
{
    node.condition()->accept( *this );
    const auto condition = m_evaluationStack.pop< IR::BooleanConstant >();

    if( not condition.defined() )
    {
        throw RuntimeException( node.condition()->sourceLocation(),
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
    auto* frame = m_frameStack.top();
    const auto variableIndex = node.variable()->localIndex();

    node.universe()->accept( *this );
    const auto universe = m_evaluationStack.pop();

    if( not universe.defined() )
    {
        throw RuntimeException( node.universe()->sourceLocation(),
            "universe must be defined",
            m_frameStack.generateBacktrace( node.sourceLocation(), m_agentId ),
            Code::ChooseExpressionInvalidUniverse );
    }

    frame->setLocal( variableIndex, universe.choose() );
    node.expression()->accept( *this );
}

void ExecutionVisitor::visit( UniversalQuantifierExpression& node )
{
    bool result = true;
    bool defined = true;

    auto* frame = m_frameStack.top();
    const auto variableIndex = node.predicateVariable()->localIndex();

    node.universe()->accept( *this );
    const auto universe = m_evaluationStack.pop();

    if( not universe.defined() )
    {
        throw RuntimeException( node.universe()->sourceLocation(),
            "universe must be defined",
            m_frameStack.generateBacktrace( node.sourceLocation(), m_agentId ),
            Code::QuantifierExpressionInvalidUniverse );
    }

    universe.foreach( [&]( const IR::Constant& value ) {
        frame->setLocal( variableIndex, value );

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

    auto* frame = m_frameStack.top();
    const auto variableIndex = node.predicateVariable()->localIndex();

    node.universe()->accept( *this );
    const auto universe = m_evaluationStack.pop();

    if( not universe.defined() )
    {
        throw RuntimeException( node.universe()->sourceLocation(),
            "universe must be defined",
            m_frameStack.generateBacktrace( node.sourceLocation(), m_agentId ),
            Code::QuantifierExpressionInvalidUniverse );
    }

    universe.foreach( [&]( const IR::Constant& value ) {
        frame->setLocal( variableIndex, value );

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

void ExecutionVisitor::visit( ConditionalRule& node )
{
    node.condition()->accept( *this );
    const auto condition = m_evaluationStack.pop< IR::BooleanConstant >();

    if( not condition.defined() )
    {
        throw RuntimeException( node.condition()->sourceLocation(),
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
                    defaultCase == nullptr
                    && "case rule should not contain multiple default cases" );
                defaultCase = _case.get();
                break;
            }
            case Node::ID::EXPRESSION_CASE:
            {
                const auto& exprCase
                    = std::static_pointer_cast< ExpressionCase >( _case );
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
    node.expression()->accept( *this );
    const auto value = m_evaluationStack.pop();

    // validate value
    const auto& variableType = node.variable()->type()->result();
    try
    {
        validateValue( value, variableType );
    }
    catch( const IR::ValidationException& e )
    {
        throw RuntimeException( { node.expression()->sourceLocation() },
            e.what(),
            m_frameStack.generateBacktrace( node.sourceLocation(), m_agentId ),
            Code::LetAssignedValueInvalid );
    }

    auto* frame = m_frameStack.top();
    const auto variableIndex = node.variable()->localIndex();
    frame->setLocal( variableIndex, value );

    node.rule()->accept( *this );
}

void ExecutionVisitor::visit( ForallRule& node )
{
    Transaction transaction( &m_updateSetManager, Semantics::Parallel, 100UL );

    auto* frame = m_frameStack.top();
    const auto variableIndex = node.variable()->localIndex();

    node.universe()->accept( *this );
    const auto universe = m_evaluationStack.pop();

    if( not universe.defined() )
    {
        throw RuntimeException( node.universe()->sourceLocation(),
            "universe must be defined",
            m_frameStack.generateBacktrace( node.sourceLocation(), m_agentId ),
            Code::ForallRuleInvalidUniverse );
    }

    universe.foreach( [&]( const IR::Constant& value ) {
        frame->setLocal( variableIndex, value );

        // check if value satisfies the condition
        node.condition()->accept( *this );
        const auto condition = m_evaluationStack.pop< IR::BooleanConstant >();

        if( not condition.defined() )
        {
            throw RuntimeException( node.condition()->sourceLocation(),
                "condition must be true or false but was undefined for '"
                    + value.name() + "'",
                m_frameStack.generateBacktrace(
                    node.sourceLocation(), m_agentId ),
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
    auto* frame = m_frameStack.top();
    const auto variableIndex = node.variable()->localIndex();

    node.universe()->accept( *this );
    const auto universe = m_evaluationStack.pop();

    if( not universe.defined() )
    {
        throw RuntimeException( node.universe()->sourceLocation(),
            "universe must be defined",
            m_frameStack.generateBacktrace( node.sourceLocation(), m_agentId ),
            Code::ChooseRuleInvalidUniverse );
    }

    frame->setLocal( variableIndex, universe.choose() );
    node.rule()->accept( *this );
}

void ExecutionVisitor::visit( IterateRule& node )
{
    Transaction seqTrans( &m_updateSetManager, Semantics::Sequential, 100UL );

    while( true )
    {
        // uses a new parallel update set on each iteration only to check if the
        // current iteration actually produced any updates
        Transaction parTrans( &m_updateSetManager, Semantics::Parallel, 100UL );
        node.rule()->accept( *this );
        if( hasEmptyUpdateSet() )
        {
            // the current iteration hasn't produced any updates -> done
            break;
        }
        parTrans.merge(); // should not throw a merge conflict because of the
                          // surrounding sequential block, thus no conflict
                          // handling required
    }

    try
    {
        seqTrans.merge();
    }
    catch( const ExecutionUpdateSet::Conflict& conflict )
    {
        handleMergeConflict( node, conflict );
    }
}

void ExecutionVisitor::visit( BlockRule& node )
{
    Transaction transaction( &m_updateSetManager, Semantics::Parallel, 100UL );
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
    Transaction transaction(
        &m_updateSetManager, Semantics::Sequential, 100UL );
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
        validateValue( updateValue, function->type()->result() );
    }
    catch( const IR::ValidationException& e )
    {
        throw RuntimeException( { expression->sourceLocation() }, e.what(),
            m_frameStack.generateBacktrace( node.sourceLocation(), m_agentId ),
            Code::FunctionUpdateInvalidValueAtUpdate );
    }

    // evaluate function arguments
    const auto& arguments = function->arguments();
    const auto& argumentTypes = function->type()->arguments();
    std::vector< IR::Constant > argumentValues;
    argumentValues.reserve( arguments->size() );
    for( std::size_t i = 0; i < arguments->size(); ++i )
    {
        const auto& argument = arguments->at( i );
        const auto& argumentType = argumentTypes.at( i );

        argument->accept( *this );
        const auto value = m_evaluationStack.pop();

        try
        {
            validateValue(
                value, *argumentType, ValidationFlag::ValueMustBeDefined );
        }
        catch( const IR::ValidationException& e )
        {
            throw RuntimeException( { argument->sourceLocation() }, e.what(),
                m_frameStack.generateBacktrace(
                    node.sourceLocation(), m_agentId ),
                Code::FunctionArgumentInvalidValueAtUpdate );
        }

        argumentValues.emplace_back( value );
    }

    assert(
        node.function()->targetType() == CallExpression::TargetType::FUNCTION );
    const auto& functionDefintion
        = std::static_pointer_cast< FunctionDefinition >(
            node.function()->targetDefinition() );

    const auto location
        = m_locationRegistry.get( functionDefintion->uid(), argumentValues );
    const Update update{ updateValue, &node, m_agentId };

    try
    {
        m_updateSetManager.add( location, update );
    }
    catch( const ExecutionUpdateSet::Conflict& conflict )
    {
        // existing
        const auto& updateA = conflict.existingUpdate();
        const auto updateStrA = updateAsString( conflict.existingUpdate() );
        const auto& sourceLocationA = updateA.value.producer->sourceLocation();

        // conflicting
        const auto& updateB = conflict.conflictingUpdate();
        const auto updateStrB = updateAsString( updateB );
        const auto& sourceLocationB = node.sourceLocation();

        const auto info = "Conflict while adding an update in agent "
                          + m_agentId.name() + ". Update '" + updateStrA
                          + "' clashed with update '" + updateStrB + "'";
        throw RuntimeException( { sourceLocationA, sourceLocationB }, info,
            m_frameStack.generateBacktrace( node.sourceLocation(), m_agentId ),
            libcasm_fe::Code::UpdateSetClash );
    }
}

void ExecutionVisitor::visit( CallRule& node )
{
    node.call()->accept( *this );

    const auto& returnType = node.call()->type()->result();
    if( not returnType.isVoid() )
    {
        m_evaluationStack.pop(); // drop return value
    }
}

u1 ExecutionVisitor::hasEmptyUpdateSet( void ) const
{
    return m_updateSetManager.currentUpdateSet()->empty();
}

std::unique_ptr< Frame > ExecutionVisitor::makeFrame(
    CallExpression* call, Node* callee, std::size_t numberOfLocals )
{
    std::unique_ptr< Frame > frame = nullptr;

    if( call != nullptr )
    {
        assert( numberOfLocals >= call->arguments()->size() );

        std::size_t localIndex = 0;

        if( call->methodCall() )
        {
            frame = libstdhl::Memory::make_unique< Frame >(
                call, callee, numberOfLocals + 1 );

            // already evaluated in the MethodCallExpression, just pop the
            // latest value from the evaluation stack!
            const auto value = m_evaluationStack.pop();
            frame->setLocal( localIndex, value );
            ++localIndex;
        }
        else
        {
            frame = libstdhl::Memory::make_unique< Frame >(
                call, callee, numberOfLocals );
        }

        for( const auto& argument : *call->arguments() )
        {
            argument->accept( *this );
            const auto value = m_evaluationStack.pop();
            frame->setLocal( localIndex, value );
            ++localIndex;
        }
    }
    else
    {
        frame = libstdhl::Memory::make_unique< Frame >(
            call, callee, numberOfLocals );
    }

    return frame;
}

void ExecutionVisitor::invokeBuiltin(
    const Node& node, IR::Value::ID id, const IR::Type::Ptr& type )
{
    validateArguments(
        node, type->arguments(), {}, Code::BuiltinArgumentValueInvalid );

    try
    {
        const auto& arguments = m_frameStack.top()->locals();
        IR::Constant returnValue;

        RT::Value::execute(
            id, type, returnValue, arguments.data(), arguments.size() );

        const auto& returnType = type->result();
        if( not returnType.isVoid() )
        {
            m_evaluationStack.push( returnValue );
        }
    }
    catch( const std::exception& e )
    {
        throw RuntimeException( node.sourceLocation(),
            "builtin has thrown an exception: " + std::string( e.what() ),
            m_frameStack.generateBacktrace( node.sourceLocation(), m_agentId ),
            Code::AssertInvalidExpression );
    }
}

void ExecutionVisitor::validateValue( const IR::Constant& value,
    const IR::Type& type, ValidationFlags flags ) const
{
    if( flags.isSet( ValidationFlag::ValueMustBeDefined )
        and not value.defined() )
    {
        throw IR::ValidationException( "value must be defined" );
    }

    type.validate( value );
}

void ExecutionVisitor::validateArguments( const Node& node,
    const IR::Types& argumentTypes, ValidationFlags flags,
    Code errorCode ) const
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
            throw RuntimeException( { callArgument->sourceLocation() },
                e.what(),
                m_frameStack.generateBacktrace(
                    node.sourceLocation(), m_agentId ),
                errorCode );
        }
    }
}

void ExecutionVisitor::handleMergeConflict(
    const Node& node, const ExecutionUpdateSet::Conflict& conflict ) const
{
    // existing
    const auto& updateA = conflict.existingUpdate();
    const auto updateStrA = updateAsString( updateA );
    const auto& sourceLocationA = updateA.value.producer->sourceLocation();

    // conflicting
    const auto& updateB = conflict.conflictingUpdate();
    const auto updateStrB = updateAsString( updateB );
    const auto& sourceLocationB = updateB.value.producer->sourceLocation();

    const auto info = "Conflict while merging update sets in agent "
                      + m_agentId.name() + ". Update '" + updateStrA
                      + "' clashed with update '" + updateStrB + "'";
    throw RuntimeException( { sourceLocationA, sourceLocationB }, info,
        m_frameStack.generateBacktrace( node.sourceLocation(), m_agentId ),
        libcasm_fe::Code::UpdateSetMergeConflict );
}

class StateInitializationVisitor final : public EmptyVisitor
{
  public:
    StateInitializationVisitor(
        ExecutionLocationRegistry& locationRegistry, Storage& globalState );

    void visit( Specification& node );

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

    node.header()->accept( *this );
    node.definitions()->accept( *this );

    auto updateSet = m_updateSetManager.currentUpdateSet();
    m_globalState.fireUpdateSet( updateSet );
    m_updateSetManager.clear();
}

void StateInitializationVisitor::visit( FunctionDefinition& node )
{
    Transaction transaction( &m_updateSetManager, Semantics::Parallel, 100UL );
    ExecutionVisitor executionVisitor( m_locationRegistry, m_globalState,
        m_updateSetManager, ReferenceConstant() );
    node.initializers()->accept( executionVisitor );
    transaction.merge();
}

class Agent
{
  public:
    Agent( ExecutionLocationRegistry& locationRegistry,
        const Storage& globalState, const IR::Constant& agentId,
        const ReferenceConstant& rule );

    void run( void );

    ExecutionUpdateSet* updateSet( void ) const;

  private:
    const Storage& m_globalState;
    ExecutionLocationRegistry& m_locationRegistry;
    const IR::Constant& m_agentId;
    const ReferenceConstant& m_rule;
    UpdateSetManager< ExecutionUpdateSet > m_updateSetManager;
};

Agent::Agent( ExecutionLocationRegistry& locationRegistry,
    const Storage& globalState, const IR::Constant& agentId,
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
    void collectUpdates( const std::vector< Agent >& agents );
    void fireUpdates( void );

  private:
    std::unique_ptr< DispatchStrategy > m_dispatchStrategy;
    Storage& m_globalState;
    ExecutionLocationRegistry& m_locationRegistry;
    ParallelUpdateSet< UpdateSetDetails > m_collectedUpdates;
    bool m_done;
    std::size_t m_stepCounter;
};

AgentScheduler::AgentScheduler(
    ExecutionLocationRegistry& locationRegistry, Storage& globalState )
: m_dispatchStrategy(
      libstdhl::Memory::make_unique< SequentialDispatchStrategy >() )
, m_globalState( globalState )
, m_locationRegistry( locationRegistry )
, m_collectedUpdates()
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

    collectUpdates( agents );
    m_done = m_collectedUpdates.empty();
    fireUpdates();

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

        assert( IR::isa< ReferenceConstant >( value ) );
        const auto& rule = static_cast< const ReferenceConstant& >( value );

        if( rule.defined() )
        {
            agents.emplace_back(
                m_locationRegistry, m_globalState, agentId, rule );
        }
    }

    return agents;
}

void AgentScheduler::dispatch( std::vector< Agent >& agents )
{
    assert( m_dispatchStrategy );
    m_dispatchStrategy->dispatch( agents );
}

void AgentScheduler::collectUpdates( const std::vector< Agent >& agents )
{
    for( const auto& agent : agents )
    {
        try
        {
            agent.updateSet()->mergeInto( &m_collectedUpdates );
        }
        catch( const ExecutionUpdateSet::Conflict& conflict )
        {
            // existing
            const auto& updateA = conflict.existingUpdate();
            const auto updateStrA = updateAsString( updateA );
            const auto agentStrA = updateA.value.agent.name();
            const auto& sourceLocationA
                = updateA.value.producer->sourceLocation();

            // conflicting
            const auto& updateB = conflict.conflictingUpdate();
            const auto updateStrB = updateAsString( updateB );
            const auto agentStrB = updateB.value.agent.name();
            const auto& sourceLocationB
                = updateB.value.producer->sourceLocation();

            const auto info = "Conflict while collection updates from agent "
                              + agentStrB + ". Update '" + updateStrA
                              + "' produced by agent " + agentStrA
                              + " clashed with update '" + updateStrB
                              + "' produced by agent " + agentStrB;
            throw RuntimeException( { sourceLocationA, sourceLocationB }, info,
                libcasm_fe::Code::UpdateSetMergeConflict );
        }
    }
}

void AgentScheduler::fireUpdates( void )
{
    m_globalState.fireUpdateSet( &m_collectedUpdates );
    m_collectedUpdates.clear();
}

void NumericExecutionPass::usage( libpass::PassUsage& pu )
{
    pu.require< FrameSizeDeterminationPass >();
}

u1 NumericExecutionPass::run( libpass::PassResult& pr )
{
    libcasm_fe::Logger log( &id, stream() );

    const auto data = pr.result< FrameSizeDeterminationPass >();
    const auto specification = data->specification();

    ExecutionLocationRegistry locationRegistry;
    Storage globalState;

    AgentScheduler scheduler( locationRegistry, globalState );
    /*scheduler.setDispatchStrategy(
        libstdhl::Memory::make_unique< ParallelDispatchStrategy >() );*/

    try
    {
        StateInitializationVisitor stateInitializationVisitor(
            locationRegistry, globalState );
        stateInitializationVisitor.visit( *specification );

        while( not scheduler.done() )
        {
            scheduler.step();
        }

        log.info( "Finished execution after "
                  + std::to_string( scheduler.numberOfSteps() ) + " steps" );
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
