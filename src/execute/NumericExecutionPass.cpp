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

#include "../stdhl/cpp/Default.h"

#include "../pass/src/PassRegistry.h"
#include "../pass/src/PassResult.h"
#include "../pass/src/PassUsage.h"

#include "../casm-ir/src/Instruction.h"
#include "../casm-ir/src/Value.h"

#include "../Exceptions.h"
#include "../Logger.h"

#include "../ast/RecursiveVisitor.h"
#include "../ast/Specification.h"

#include "../analyze/TypeInferencePass.h"

#include "UpdateSet.h"

using namespace libcasm_fe;
using namespace Ast;

namespace ir = libcasm_ir;

char NumericExecutionPass::id = 0;

static libpass::PassRegistration< NumericExecutionPass > PASS(
    "NumericExecutionPass",
    "execute numerically over the AST input specification", "ast-exec-num", 0 );

template < typename T >
class Stack
{
  public:
    Stack()
    : m_values()
    {
    }

    void push( const T& value )
    {
        m_values.push_back( value );
    }

    T pop()
    {
        assert( not m_values.empty() );

        const auto& value = m_values.back();
        m_values.pop_back();
        return value;
    }

    T& top()
    {
        assert( not m_values.empty() );

        return m_values.back();
    }

    void clear()
    {
        m_values.clear();
    }

  private:
    std::vector< T > m_values;
};

class ConstantStack : public Stack< ir::Constant >
{
  public:
    using Stack::Stack;

    using Stack::pop;

    template < typename T >
    T pop()
    {
        const auto& value = Stack::pop();
        assert( ir::isa< T >( value ) );
        return static_cast< const T& >( value );
    }
};

class Frame
{
  public:
    Frame( const Definition::Ptr& definition )
    : m_definition( definition )
    , m_locals()
    {
    }

    Definition::Ptr definition( void ) const
    {
        return m_definition;
    }

    void setLocal( std::size_t index, const ir::Constant& local )
    {
        m_locals[ index ] = local;
    }

    ir::Constant local( std::size_t index ) const
    {
        return m_locals.at( index );
    }

  private:
    Definition::Ptr m_definition;
    std::vector< ir::Constant > m_locals;
};

class FrameStack
{
  public:
    FrameStack()
    : m_frames()
    {
    }

    void push( std::unique_ptr< Frame > frame )
    {
        m_frames.emplace_back( std::move( frame ) );
    }

    std::unique_ptr< Frame > pop()
    {
        assert( not m_frames.empty() );

        auto frame = std::move( m_frames.back() );
        m_frames.pop_back();
        return frame;
    }

    Frame* top() const
    {
        assert( not m_frames.empty() );

        return m_frames.back().get();
    }

  private:
    std::vector< std::unique_ptr< Frame > > m_frames;
};

struct LocationHash
{
    /**
     * Directly using a libcasm_fe::value_t pointer as hash value has the
     * problem that the first 4 bits of the hash value are always 0, because the
     * size of libcasm_fe::value_t is 16 bytes. Some bit shifting avoids this
     * problem.
     *
     * Forumla is from LLVM's DenseMapInfo<T*>
     */
    std::size_t operator()( const ir::Constant* location ) const
    {
        return ( reinterpret_cast< std::uintptr_t >( location ) >> 4 )
               ^ ( reinterpret_cast< std::uintptr_t >( location ) >> 9 );
    }
};

/**
 * @brief Represents an update
 */
struct Update
{
    ir::Constant value; /**< The value of the update */
    const std::vector< ir::Constant >*
        args; /**< The function arguments of the update */
    const Location*
        location; /**< The source-code location of the update producer */
};

struct UpdateEquals : public std::binary_function< Update*, Update*, bool >
{
    bool operator()( Update* lhs, Update* rhs ) const
    {
        return lhs->value == rhs->value;
    }
};

struct UpdateSetDetails
{
    using Location = const ir::Constant*;
    using Value = Update*;
    using LocationHash = LocationHash;
    using LocationEquals = std::equal_to< Location >;
    using ValueEquals = UpdateEquals;
};

using ExecutionUpdateSet = UpdateSet< UpdateSetDetails >;
using ForkGuard = UpdateSetForkGuard< ExecutionUpdateSet >;
using Semantics = ExecutionUpdateSet::Semantics;

class ExecutionVisitor final : public RecursiveVisitor
{
    /** Use the list index of rules, functions, deriveds, ... to refer to them
     */
    using ReferenceConstant = ir::IntegerConstant;

  public:
    ExecutionVisitor(
        UpdateSetManager< ExecutionUpdateSet >& updateSetManager );

    void visit( FunctionDefinition& node ) override;
    void visit( DerivedDefinition& node ) override;
    void visit( RuleDefinition& node ) override;
    void visit( EnumerationDefinition& node ) override;

    void visit( ValueAtom& node ) override;
    void visit( RuleReferenceAtom& node ) override;
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

    std::unique_ptr< Frame > makeFrame( const CallExpression& call );

  private:
    UpdateSetManager< ExecutionUpdateSet >& m_updateSetManager;

    ConstantStack m_evaluationStack;
    FrameStack m_frameStack;
};

ExecutionVisitor::ExecutionVisitor(
    UpdateSetManager< ExecutionUpdateSet >& updateSetManager )
: m_updateSetManager( updateSetManager )
, m_evaluationStack()
, m_frameStack()
{
}

void ExecutionVisitor::visit( FunctionDefinition& node )
{
    auto* frame = m_frameStack.top();

    // TODO hash arguments of frame and perform a lookup

    if( false /* TODO update exists or function exists in state */ )
    {
        // m_evaluationStack.push( value );
    }
    else
    {
        node.defaultValue()->accept( *this ); // return value already on stack
    }
}

void ExecutionVisitor::visit( DerivedDefinition& node )
{
    node.expression()->accept( *this ); // return value already on stack
}

void ExecutionVisitor::visit( RuleDefinition& node )
{
    node.rule()->accept( *this );

    const auto& returnType = node.relationType()->ptr_result();
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
    RecursiveVisitor::visit( node );
}

void ExecutionVisitor::visit( ValueAtom& node )
{
    m_evaluationStack.push( *node.value() );
}

void ExecutionVisitor::visit( RuleReferenceAtom& node )
{
    // m_evaluationStack.push( ReferenceConstant( node.targetId() ) ); TODO
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
        case CallExpression::TargetType::DERIVED:  // [[fallthrough]]
        case CallExpression::TargetType::BUILTIN:  // [[fallthrough]]
        case CallExpression::TargetType::RULE:
        {
            m_frameStack.push( makeFrame( node ) );

            // TODO invoke derived/function/rule/builtin (by node.targetId())

            m_frameStack.pop();
            break;
        }
        case CallExpression::TargetType::ENUMERATION:
        {
            break;
        }
        case CallExpression::TargetType::CONSTANT:
        {
            break;
        }
        case CallExpression::TargetType::VARIABLE:
        {
            const auto localIndex = node.targetId(); // calc. by SymbolResolver
            const auto* frame = m_frameStack.top();
            m_evaluationStack.push( frame->local( localIndex ) );
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
    switch( node.targetType() )
    {
        case CallExpression::TargetType::FUNCTION: // [[fallthrough]]
        case CallExpression::TargetType::DERIVED:  // [[fallthrough]]
        case CallExpression::TargetType::BUILTIN:  // [[fallthrough]]
        case CallExpression::TargetType::RULE:
        {
            node.expression()->accept( *this );
            const auto& targetId = m_evaluationStack.pop< ReferenceConstant >();
            if( not targetId.defined() )
            {
                throw RuntimeException( node.expression()->sourceLocation(),
                    "cannot call an undefined " + node.targetTypeName(),
                    Code::Unspecified );
            }

            m_frameStack.push( makeFrame( node ) );

            // TODO invoke derived/function/rule/builtin (by targetId)

            m_frameStack.pop();
            break;
        }
        case CallExpression::TargetType::ENUMERATION: // [[fallthrough]]
        case CallExpression::TargetType::CONSTANT:    // [[fallthrough]]
        case CallExpression::TargetType::VARIABLE:
        {
            assert( !"target not allowed in indirect call" );
            break;
        }
        case CallExpression::TargetType::UNKNOWN:
        {
            assert( !"cannot call an unknown target" );
            break;
        }
    }
}

void ExecutionVisitor::visit( UnaryExpression& node )
{
    node.expression()->accept( *this );
    const auto& expr = m_evaluationStack.pop();

    // TODO dispatch instruction node.op()
    // m_evaluationStack.push( result );
}

void ExecutionVisitor::visit( BinaryExpression& node )
{
    node.left()->accept( *this );
    const auto& lhs = m_evaluationStack.pop();

    node.right()->accept( *this );
    const auto& rhs = m_evaluationStack.pop();

    // TODO dispatch instruction node.op()
    // m_evaluationStack.push( result );
}

void ExecutionVisitor::visit( RangeExpression& node )
{
    RecursiveVisitor::visit( node );
}

void ExecutionVisitor::visit( ListExpression& node )
{
    RecursiveVisitor::visit( node );
}

void ExecutionVisitor::visit( ConditionalExpression& node )
{
    node.condition()->accept( *this );
    const auto& condition = m_evaluationStack.pop< ir::BooleanConstant >();

    if( not condition.defined() )
    {
        throw RuntimeException( node.condition()->sourceLocation(),
            "condition must be true or false but was undef",
            Code::Unspecified );
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

    auto* frame = m_frameStack.top();
    const auto variableIndex = node.predicateVariable()->localIndex();

    while( false /* TODO iterate over universe */ )
    {
        // frame->setLocal( variableIndex, ... ); // TODO assign value

        node.proposition()->accept( *this );
        const auto& prop = m_evaluationStack.pop< ir::BooleanConstant >();

        if( not prop.defined() )
        {
            throw RuntimeException( node.proposition()->sourceLocation(),
                "proposition must be true or false but was undef",
                Code::Unspecified );
        }
        else if( prop.value() == false )
        {
            result = false;
            break;
        }
    }

    m_evaluationStack.push( ir::BooleanConstant( result ) );
}

void ExecutionVisitor::visit( ExistentialQuantifierExpression& node )
{
    bool result = false;

    auto* frame = m_frameStack.top();
    const auto variableIndex = node.predicateVariable()->localIndex();

    while( false /* TODO iterate over universe */ )
    {
        // frame->setLocal( variableIndex, ... ); // TODO assign value

        node.proposition()->accept( *this );
        const auto& prop = m_evaluationStack.pop< ir::BooleanConstant >();

        if( not prop.defined() )
        {
            throw RuntimeException( node.proposition()->sourceLocation(),
                "proposition must be true or false but was undef",
                Code::Unspecified );
        }
        else if( prop.value() == true )
        {
            result = true;
            break;
        }
    }

    m_evaluationStack.push( ir::BooleanConstant( result ) );
}

void ExecutionVisitor::visit( ConditionalRule& node )
{
    node.condition()->accept( *this );
    const auto& condition = m_evaluationStack.pop< ir::BooleanConstant >();

    if( not condition.defined() )
    {
        throw RuntimeException( node.condition()->sourceLocation(),
            "condition must be true or false but was undef",
            Code::Unspecified );
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

    while( false /* TODO iterate over universe */ )
    {
        // frame->setLocal( variableIndex, ... ); // TODO assign value
        node.rule()->accept( *this );
    }
}

void ExecutionVisitor::visit( ChooseRule& node )
{
    // TODO choose one value of the universe

    auto* frame = m_frameStack.top();
    const auto variableIndex = node.variable()->localIndex();
    // frame->setLocal( variableIndex, ... ); // TODO assign value

    node.rule()->accept( *this );
}

void ExecutionVisitor::visit( IterateRule& node )
{
    ForkGuard seqGuard( &m_updateSetManager, Semantics::Sequential, 100UL );

    while( true )
    {
        ForkGuard parGuard( &m_updateSetManager, Semantics::Parallel, 100UL );
        RecursiveVisitor::visit( node );
        if( hasEmptyUpdateSet() )
        {
            break;
        }
    }
}

void ExecutionVisitor::visit( BlockRule& node )
{
    ForkGuard parGuard( &m_updateSetManager, Semantics::Parallel, 100UL );
    RecursiveVisitor::visit( node );
}

void ExecutionVisitor::visit( SequenceRule& node )
{
    ForkGuard seqGuard( &m_updateSetManager, Semantics::Sequential, 100UL );
    RecursiveVisitor::visit( node );
}

void ExecutionVisitor::visit( UpdateRule& node )
{
    node.expression()->accept( *this );
    const auto& expr = m_evaluationStack.pop();

    // TODO
}

void ExecutionVisitor::visit( CallRule& node )
{
    RecursiveVisitor::visit( node );
    m_evaluationStack.clear(); // call may returned a value, ignore it
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
    const CallExpression& call )
{
    auto frame
        = libstdhl::make_unique< Frame >( nullptr ); // TODO fetch definition

    std::size_t localIndex = 0;
    for( const auto& argument : *call.arguments() )
    {
        argument->accept( *this );
        const auto& value = m_evaluationStack.pop();
        frame->setLocal( localIndex, value );
        ++localIndex;
    }

    return frame;
}

class StateInitializationVisitor final : public RecursiveVisitor
{
  public:
    StateInitializationVisitor( /* FunctionState& */ );

    void visit( Specification& node ) override;

    void visit( VariableDefinition& node ) override;
    void visit( FunctionDefinition& node ) override;
    void visit( DerivedDefinition& node ) override;
    void visit( RuleDefinition& node ) override;
    void visit( EnumerationDefinition& node ) override;

  private:
    UpdateSetManager< ExecutionUpdateSet > m_updateSetManager;
};

StateInitializationVisitor::StateInitializationVisitor( /* FunctionState& */ )
: m_updateSetManager()
{
}

void StateInitializationVisitor::visit( Specification& node )
{
    ForkGuard seqGuard( &m_updateSetManager, Semantics::Sequential, 100UL );
    node.definitions()->accept( *this );
    // TODO fire updates
}

void StateInitializationVisitor::visit( VariableDefinition& node )
{
    // nothing to do
}

void StateInitializationVisitor::visit( FunctionDefinition& node )
{
    ForkGuard parGuard( &m_updateSetManager, Semantics::Parallel, 100UL );
    ExecutionVisitor executionVisitor( m_updateSetManager );
    node.initializers()->accept( executionVisitor );
}

void StateInitializationVisitor::visit( DerivedDefinition& node )
{
    // nothing to do
}

void StateInitializationVisitor::visit( RuleDefinition& node )
{
    // nothing to do
}

void StateInitializationVisitor::visit( EnumerationDefinition& node )
{
    // nothing to do
}

void NumericExecutionPass::usage( libpass::PassUsage& pu )
{
    pu.require< TypeInferencePass >();
}

u1 NumericExecutionPass::run( libpass::PassResult& pr )
{
    Logger log( &id, stream() );

    const auto data = pr.result< TypeInferencePass >();
    const auto specification = data->specification();

    try
    {
        StateInitializationVisitor stateInitializationVisitor;
        specification->accept( stateInitializationVisitor );

        // foreach agent: program->accept( ExecutionVisitor )
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
