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

#include "ConsistencyCheckPass.h"

#include <libcasm-fe/Logger>
#include <libcasm-fe/Namespace>
#include <libcasm-fe/Specification>
#include <libcasm-fe/ast/RecursiveVisitor>

#include <libcasm-fe/analyze/PropertyRevisePass>
#include <libcasm-fe/transform/SourceToAstPass>

#include <libcasm-ir/Builtin>

#include <libpass/PassRegistry>
#include <libpass/PassResult>
#include <libpass/PassUsage>

#include <algorithm>

using namespace libcasm_fe;
using namespace Ast;

char ConsistencyCheckPass::id = 0;

static libpass::PassRegistration< ConsistencyCheckPass > PASS(
    "ASTConsistencyCheckPass", "checks the consistency of the AST representation", "ast-check", 0 );

//
// ConsistencyCheckVisitor
//

class ConsistencyCheckVisitor final : public RecursiveVisitor
{
  public:
    ConsistencyCheckVisitor( libcasm_fe::Logger& m_log );

    void visit( Specification& node );

    void visit( VariableDefinition& node ) override;
    void visit( FunctionDefinition& node ) override;

    void visit( UndefLiteral& node ) override;
    void visit( ValueLiteral& node ) override;
    void visit( ReferenceLiteral& node ) override;
    void visit( ListLiteral& node ) override;
    void visit( RangeLiteral& node ) override;
    void visit( TupleLiteral& node ) override;
    void visit( RecordLiteral& node ) override;

    void visit( DirectCallExpression& node ) override;

    void visit( CaseRule& node ) override;
    void visit( UpdateRule& node ) override;

    void visit( BasicType& node ) override;
    void visit( ComposedType& node ) override;
    void visit( TemplateType& node ) override;
    void visit( FixedSizedType& node ) override;
    void visit( RelationType& node ) override;

    void verify( const TypedNode& node );

  private:
    libcasm_fe::Logger& m_log;
    u1 m_functionInitially;
    u1 m_initDefinitionFound;
};

ConsistencyCheckVisitor::ConsistencyCheckVisitor( libcasm_fe::Logger& log )
: m_log( log )
, m_functionInitially( false )
, m_initDefinitionFound( false )
{
}

void ConsistencyCheckVisitor::visit( Specification& node )
{
    node.header()->accept( *this );
    node.definitions()->accept( *this );

    if( not m_initDefinitionFound )
    {
        m_log.error(
            { node.header()->sourceLocation() },
            "no init definition found in this specification",
            Code::AgentInitRuleNotDefined );
    }
}

void ConsistencyCheckVisitor::visit( VariableDefinition& node )
{
    RecursiveVisitor::visit( node );
    verify( node );
}

void ConsistencyCheckVisitor::visit( FunctionDefinition& node )
{
    m_functionInitially = true;
    node.initializers()->accept( *this );
    m_functionInitially = false;

    node.identifier()->accept( *this );
    node.argumentTypes()->accept( *this );
    node.returnType()->accept( *this );
    node.defaultValue()->accept( *this );
    node.attributes()->accept( *this );

    if( node.uid() == FunctionDefinition::UID::PROGRAM )
    {
        m_initDefinitionFound = true;
    }
}

void ConsistencyCheckVisitor::visit( UndefLiteral& node )
{
    RecursiveVisitor::visit( node );
    verify( node );
}

void ConsistencyCheckVisitor::visit( ValueLiteral& node )
{
    RecursiveVisitor::visit( node );
    verify( node );
}

void ConsistencyCheckVisitor::visit( ReferenceLiteral& node )
{
    RecursiveVisitor::visit( node );
    verify( node );
}

void ConsistencyCheckVisitor::visit( ListLiteral& node )
{
    RecursiveVisitor::visit( node );
    verify( node );
    assert( node.type()->isList() );
}

void ConsistencyCheckVisitor::visit( RangeLiteral& node )
{
    RecursiveVisitor::visit( node );
    verify( node );
    assert( node.type()->isRange() );
}

void ConsistencyCheckVisitor::visit( TupleLiteral& node )
{
    RecursiveVisitor::visit( node );
    verify( node );
    assert( node.type()->isTuple() );
}

void ConsistencyCheckVisitor::visit( RecordLiteral& node )
{
    RecursiveVisitor::visit( node );
    verify( node );
    assert( node.type()->isRecord() );
}

void ConsistencyCheckVisitor::visit( CaseRule& node )
{
    RecursiveVisitor::visit( node );

    const auto numberOfDefaultCases =
        std::count_if( node.cases()->begin(), node.cases()->end(), []( const auto& _case ) {
            return _case->id() == Node::ID::DEFAULT_CASE;
        } );

    if( numberOfDefaultCases > 1 )
    {
        for( const auto& _case : *node.cases() )
        {
            if( _case->id() == Node::ID::DEFAULT_CASE )
            {
                m_log.error(
                    { _case->sourceLocation() },
                    "case rule contains multiple default cases",
                    Code::CaseRuleMultipleDefaultCases );
            }
        }
    }
}

void ConsistencyCheckVisitor::visit( DirectCallExpression& node )
{
    assert( node.targetType() != DirectCallExpression::TargetType::UNKNOWN );

    RecursiveVisitor::visit( node );

    if( node.targetType() == DirectCallExpression::TargetType::FUNCTION )
    {
        const auto& function = node.targetDefinition()->ptr< FunctionDefinition >();
        if( function->classification() == FunctionDefinition::Classification::OUT )
        {
            // calling an out function isn't allowed (write-only)
            m_log.error(
                { node.sourceLocation() },
                "calling function '" + node.identifier()->path() +
                    "' is not allowed, it is classified as '" + function->classificationName() +
                    "' ",
                Code::DirectCallExpressionInvalidClassifier );

            m_log.info(
                { function->sourceLocation() },
                "function '" + node.identifier()->path() + "' is classified as '" +
                    function->classificationName() + "', incorrect usage in line " +
                    std::to_string( node.sourceLocation().begin.line ) );
        }
    }
}

void ConsistencyCheckVisitor::visit( UpdateRule& node )
{
    // don't visit the function directly, as it would be treated like a function call

    node.expression()->accept( *this );

    const auto& func = node.function();
    if( func->targetType() != DirectCallExpression::TargetType::FUNCTION )
    {
        m_log.error(
            { func->sourceLocation() },
            "updating " + func->targetTypeName() + " '" + func->identifier()->path() +
                "' is not allowed, only function symbols are allowed",
            Code::UpdateRuleFunctionSymbolIsInvalid );
        return;
    }

    func->arguments()->accept( *this );

    const auto& def = func->targetDefinition()->ptr< FunctionDefinition >();

    bool updatesAllowed;
    switch( def->classification() )
    {
        case FunctionDefinition::Classification::IN:
        {
            updatesAllowed = false;
            break;
        }
        case FunctionDefinition::Classification::STATIC:
        {
            // static function updates are only allowed during initialisation
            updatesAllowed = m_functionInitially;
            break;
        }
        default:
        {
            updatesAllowed = true;
        }
    }

    if( not updatesAllowed )
    {
        m_log.error(
            { func->sourceLocation() },
            "updating function '" + func->identifier()->path() +
                "' is not allowed, it is classified as '" + def->classificationName() + "' ",
            Code::UpdateRuleInvalidClassifier );

        m_log.info(
            { def->sourceLocation() },
            "function '" + func->identifier()->path() + "' is classified as '" +
                def->classificationName() + "', incorrect usage in line " +
                std::to_string( func->sourceLocation().begin.line ) );
    }
}

void ConsistencyCheckVisitor::visit( BasicType& node )
{
    RecursiveVisitor::visit( node );
    verify( node );
}

void ConsistencyCheckVisitor::visit( ComposedType& node )
{
    RecursiveVisitor::visit( node );
    verify( node );
}

void ConsistencyCheckVisitor::visit( TemplateType& node )
{
    RecursiveVisitor::visit( node );
    verify( node );
}

void ConsistencyCheckVisitor::visit( FixedSizedType& node )
{
    RecursiveVisitor::visit( node );
    verify( node );
}

void ConsistencyCheckVisitor::visit( RelationType& node )
{
    RecursiveVisitor::visit( node );
    verify( node );
}

void ConsistencyCheckVisitor::verify( const TypedNode& node )
{
    if( not node.type() )
    {
        m_log.error(
            { node.sourceLocation() },
            "unable to infer type",
            Code::TypeInferenceUnableToInferType );
    }
}

//
// ConsistencyCheckPass
//

void ConsistencyCheckPass::usage( libpass::PassUsage& pu )
{
    pu.require< SourceToAstPass >();
    pu.scheduleAfter< PropertyRevisePass >();
}

u1 ConsistencyCheckPass::run( libpass::PassResult& pr )
{
    libcasm_fe::Logger log( &id, stream() );

    const auto data = pr.output< SourceToAstPass >();
    const auto specification = data->specification();

    ConsistencyCheckVisitor visitor( log );
    visitor.visit( *specification );

    const auto errors = log.errors();
    if( errors > 0 )
    {
        log.debug( "found %lu error(s) during consistency checking", errors );
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
