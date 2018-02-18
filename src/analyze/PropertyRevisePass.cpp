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

#include "PropertyRevisePass.h"

#include <libcasm-fe/Logger>
#include <libcasm-fe/Namespace>
#include <libcasm-fe/Specification>
#include <libcasm-fe/ast/RecursiveVisitor>

#include <libcasm-fe/analyze/PropertyResolverPass>
#include <libcasm-fe/transform/SourceToAstPass>

#include <libcasm-ir/Annotation>

#include <libpass/PassRegistry>
#include <libpass/PassResult>
#include <libpass/PassUsage>

using namespace libcasm_fe;
using namespace Ast;

char PropertyRevisePass::id = 0;

static libpass::PassRegistration< PropertyRevisePass > PASS(
    "ASTPropertyRevisePass",
    "property revise (checking) of AST representation",
    "ast-prop-rev",
    0 );

class PropertyReviseVisitor final : public RecursiveVisitor
{
  public:
    PropertyReviseVisitor( libcasm_fe::Logger& log );

    void visit( FunctionDefinition& node ) override;
    void visit( DerivedDefinition& node ) override;

    void visit( ConditionalRule& node ) override;
    void visit( CaseRule& node ) override;
    void visit( ForallRule& node ) override;
    void visit( ChooseRule& node ) override;
    void visit( UpdateRule& node ) override;
    void visit( CallRule& node ) override;

    void visit( FixedSizedType& node ) override;

  private:
    void revise( Ast::Type& node );

    void checkIfPropertiesHold(
        const TypedPropertyNode& node,
        const libcasm_ir::Properties& requiredProperties,
        const std::string& errorDescription,
        const Code errorCode ) const;

  private:
    libcasm_fe::Logger& m_log;
};

//
//
// PropertyReviseVisitor
//

using Property = libcasm_ir::Property;

PropertyReviseVisitor::PropertyReviseVisitor( libcasm_fe::Logger& log )
: m_log( log )
{
}

void PropertyReviseVisitor::visit( FunctionDefinition& node )
{
    RecursiveVisitor::visit( node );

    checkIfPropertiesHold(
        *node.defaultValue(),
        { Property::SIDE_EFFECT_FREE, Property::PURE },
        "default value of " + node.description() + " '" + node.identifier()->name() + "'",
        Code::FunctionDefinitionDefaultValueInvalidProperty );
}

void PropertyReviseVisitor::visit( DerivedDefinition& node )
{
    RecursiveVisitor::visit( node );

    checkIfPropertiesHold(
        *node.expression(),
        node.properties(),
        "expression of " + node.description() + " '" + node.identifier()->name() + "'",
        Code::DerivedDefinitionExpressionInvalidProperty );
}

void PropertyReviseVisitor::visit( ConditionalRule& node )
{
    RecursiveVisitor::visit( node );

    checkIfPropertiesHold(
        *node.condition(),
        { Property::SIDE_EFFECT_FREE },
        "condition",
        Code::ConditionalRuleConditionInvalidProperty );
}

void PropertyReviseVisitor::visit( CaseRule& node )
{
    RecursiveVisitor::visit( node );

    checkIfPropertiesHold(
        *node.expression(),
        { Property::SIDE_EFFECT_FREE },
        "case expression",
        Code::CaseRuleExpressionInvalidProperty );
}

void PropertyReviseVisitor::visit( ForallRule& node )
{
    RecursiveVisitor::visit( node );

    checkIfPropertiesHold(
        *node.universe(),
        { Property::SIDE_EFFECT_FREE },
        "universe",
        Code::ForallRuleUniverseInvalidProperty );

    checkIfPropertiesHold(
        *node.condition(),
        { Property::SIDE_EFFECT_FREE },
        "condition",
        Code::ForallRuleConditionInvalidProperty );
}

void PropertyReviseVisitor::visit( ChooseRule& node )
{
    RecursiveVisitor::visit( node );

    checkIfPropertiesHold(
        *node.universe(),
        { Property::SIDE_EFFECT_FREE },
        "universe",
        Code::ChooseRuleConditionInvalidProperty );
}

void PropertyReviseVisitor::visit( UpdateRule& node )
{
    RecursiveVisitor::visit( node );

    for( const auto& argument : *node.function()->arguments() )
    {
        checkIfPropertiesHold(
            *argument,
            { Property::SIDE_EFFECT_FREE },
            "function argument",
            Code::UpdateRuleFunctionArgumentInvalidProperty );
    }

    checkIfPropertiesHold(
        *node.expression(),
        { Property::SIDE_EFFECT_FREE },
        "update expression",
        Code::UpdateRuleUpdateExpressionInvalidProperty );
}

void PropertyReviseVisitor::visit( CallRule& node )
{
    RecursiveVisitor::visit( node );

    for( const auto& argument : *node.call()->arguments() )
    {
        checkIfPropertiesHold(
            *argument,
            { Property::SIDE_EFFECT_FREE },
            "argument",
            Code::CallRuleArgumentInvalidProperty );
    }
}

void PropertyReviseVisitor::visit( FixedSizedType& node )
{
    checkIfPropertiesHold(
        *node.size(),
        { Property::SIDE_EFFECT_FREE, Property::PURE },
        "type",
        Code::TypeInvalidProperty );
}

void PropertyReviseVisitor::checkIfPropertiesHold(
    const TypedPropertyNode& node,
    const libcasm_ir::Properties& requiredProperties,
    const std::string& errorDescription,
    const Code errorCode ) const
{
    requiredProperties.foreach( [&]( const libcasm_ir::Property property ) -> u1 {
        if( not node.properties().isSet( property ) )
        {
            m_log.error(
                { node.sourceLocation() },
                errorDescription + " violates '" + libcasm_ir::PropertyInfo::toString( property ) +
                    "' property",
                errorCode );
        }
        return true;
    } );
}

//
//
// PropertyRevisePass
//

void PropertyRevisePass::usage( libpass::PassUsage& pu )
{
    pu.require< SourceToAstPass >();
    pu.scheduleAfter< PropertyResolverPass >();
}

u1 PropertyRevisePass::run( libpass::PassResult& pr )
{
    libcasm_fe::Logger log( &id, stream() );

    const auto data = pr.output< SourceToAstPass >();
    const auto specification = data->specification();

    PropertyReviseVisitor visitor( log );
    specification->definitions()->accept( visitor );

    const auto errors = log.errors();
    if( errors > 0 )
    {
        log.debug( "found %lu error(s) during property resolving", errors );
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
