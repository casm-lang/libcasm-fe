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

class ConstantStack
{
  public:
    void push( const ir::Constant& value )
    {
        m_values.push_back( value );
    }

    ir::Constant pop()
    {
        const auto& value = m_values.back();
        m_values.pop_back();
        return value;
    }

    template < typename T >
    T pop()
    {
        const auto& value = pop();
        assert( ir::isa< T >( value ) );
        return static_cast< const T& >( value );
    }

  private:
    std::vector< ir::Constant > m_values;
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

class ExecutionVisitor final : public RecursiveVisitor
{
    using ExecutionUpdateSet = UpdateSet< UpdateSetDetails >;
    using ForkGuard = UpdateSetForkGuard< ExecutionUpdateSet >;
    using Semantics = ExecutionUpdateSet::Semantics;

  public:
    ExecutionVisitor();

    void visit( VariableDefinition& node ) override;
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

  private:
    u1 hasEmptyUpdateSet( void ) const;

  private:
    UpdateSetManager< ExecutionUpdateSet > m_updateSetManager;

    ConstantStack m_evaluationStack;
};

ExecutionVisitor::ExecutionVisitor()
{
}

void ExecutionVisitor::visit( VariableDefinition& node )
{
    RecursiveVisitor::visit( node );
}

void ExecutionVisitor::visit( FunctionDefinition& node )
{
    RecursiveVisitor::visit( node );
}

void ExecutionVisitor::visit( DerivedDefinition& node )
{
    RecursiveVisitor::visit( node );
}

void ExecutionVisitor::visit( RuleDefinition& node )
{
    RecursiveVisitor::visit( node );
}

void ExecutionVisitor::visit( EnumerationDefinition& node )
{
    RecursiveVisitor::visit( node );
}

void ExecutionVisitor::visit( ValueAtom& node )
{
    // m_evaluationStack.push( node.value() );
}

void ExecutionVisitor::visit( RuleReferenceAtom& node )
{
    RecursiveVisitor::visit( node );
}

void ExecutionVisitor::visit( UndefAtom& node )
{
    RecursiveVisitor::visit( node );
}

void ExecutionVisitor::visit( DirectCallExpression& node )
{
    RecursiveVisitor::visit( node );
}

void ExecutionVisitor::visit( IndirectCallExpression& node )
{
    RecursiveVisitor::visit( node );
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
        throw RuntimeException( node.sourceLocation(),
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

    while( false /* TODO iterate over universe */ )
    {
        node.proposition()->accept( *this );
        const auto& prop = m_evaluationStack.pop< ir::BooleanConstant >();

        if( prop.value() == false )
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

    while( false /* TODO iterate over universe */ )
    {
        node.proposition()->accept( *this );
        const auto& prop = m_evaluationStack.pop< ir::BooleanConstant >();

        if( prop.value() == true )
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
        throw RuntimeException( node.sourceLocation(),
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

    // TODO
}

void ExecutionVisitor::visit( LetRule& node )
{
    node.expression()->accept( *this );
    const auto& value = m_evaluationStack.pop();

    // TODO

    node.rule()->accept( *this );
}

void ExecutionVisitor::visit( ForallRule& node )
{
    ForkGuard parGuard( &m_updateSetManager, Semantics::Parallel, 100UL );

    RecursiveVisitor::visit( node );
}

void ExecutionVisitor::visit( ChooseRule& node )
{
    RecursiveVisitor::visit( node );
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
}

u1 ExecutionVisitor::hasEmptyUpdateSet( void ) const
{
    return m_updateSetManager.currentUpdateSet()->empty();
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
        ExecutionVisitor visitor;
        specification->accept( visitor );
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
