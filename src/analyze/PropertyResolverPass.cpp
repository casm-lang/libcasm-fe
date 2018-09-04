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

#include "PropertyResolverPass.h"

#include <libcasm-fe/Logger>
#include <libcasm-fe/Namespace>
#include <libcasm-fe/Specification>
#include <libcasm-fe/ast/RecursiveVisitor>

#include <libcasm-fe/analyze/TypeInferencePass>
#include <libcasm-fe/transform/SourceToAstPass>

#include <libcasm-ir/Annotation>

#include <libpass/PassRegistry>
#include <libpass/PassResult>
#include <libpass/PassUsage>

using namespace libcasm_fe;
using namespace Ast;

char PropertyResolverPass::id = 0;

static libpass::PassRegistration< PropertyResolverPass > PASS(
    "ASTPropertyResolverPass", "property resolving of AST representation", "ast-prop-res", 0 );

class PropertyResolverVisitor final : public RecursiveVisitor
{
  public:
    PropertyResolverVisitor( libcasm_fe::Logger& log );

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

  private:
    libcasm_fe::Logger& m_log;
};

//
//
// PropertyResolverVisitor
//

PropertyResolverVisitor::PropertyResolverVisitor( libcasm_fe::Logger& log )
: m_log( log )
{
}

template < class T >
static libcasm_ir::Properties intersectPropertiesOf( const T& expressions )
{
    libcasm_ir::Properties properties;

    u1 first = true;
    for( auto const& expression : expressions )
    {
        if( first )
        {
            properties = expression->properties();
            first = false;
            continue;
        }
        properties = properties * expression->properties();
    }

    return properties;
}

void PropertyResolverVisitor::visit( ListLiteral& node )
{
    RecursiveVisitor::visit( node );

    const auto properties = intersectPropertiesOf< Expressions >( *node.expressions() );
    node.setProperties( properties );
}

void PropertyResolverVisitor::visit( RangeLiteral& node )
{
    RecursiveVisitor::visit( node );

    node.setProperties( node.left()->properties() * node.right()->properties() );
}

void PropertyResolverVisitor::visit( TupleLiteral& node )
{
    RecursiveVisitor::visit( node );

    const auto properties = intersectPropertiesOf< Expressions >( *node.expressions() );
    node.setProperties( properties );
}

void PropertyResolverVisitor::visit( RecordLiteral& node )
{
    RecursiveVisitor::visit( node );

    const auto properties = intersectPropertiesOf< NamedExpressions >( *node.namedExpressions() );
    node.setProperties( properties );
}

void PropertyResolverVisitor::visit( EmbracedExpression& node )
{
    RecursiveVisitor::visit( node );

    node.setProperties( node.expression()->properties() );
}

void PropertyResolverVisitor::visit( NamedExpression& node )
{
    RecursiveVisitor::visit( node );

    node.setProperties( node.expression()->properties() );
}

void PropertyResolverVisitor::visit( DirectCallExpression& node )
{
    RecursiveVisitor::visit( node );

    libcasm_ir::Properties callProperties;
    switch( node.targetType() )
    {
        case DirectCallExpression::TargetType::BUILTIN:
        {
            const auto& annotation = libcasm_ir::Annotation::find( node.targetBuiltinId() );
            callProperties = annotation.properties();
            break;
        }
        case DirectCallExpression::TargetType::VARIABLE:  // [[fallthrough]]
        case DirectCallExpression::TargetType::FUNCTION:  // [[fallthrough]]
        case DirectCallExpression::TargetType::DERIVED:   // [[fallthrough]]
        case DirectCallExpression::TargetType::RULE:      // [[fallthrough]]
        case DirectCallExpression::TargetType::CONSTANT:
        {
            const auto& definition = node.targetDefinition();
            assert( definition.get() != nullptr );
            callProperties = definition->properties();
            break;
        }
        case DirectCallExpression::TargetType::TYPE_DOMAIN:
        {
            callProperties.set( libcasm_ir::Property::SIDE_EFFECT_FREE );
            callProperties.set( libcasm_ir::Property::PURE );
            break;
        }
        case DirectCallExpression::TargetType::SELF:
        {
            callProperties.set( libcasm_ir::Property::SIDE_EFFECT_FREE );
            break;
        }
        case DirectCallExpression::TargetType::UNKNOWN:
        {
            assert( !" direct call cannot have UNKNOWN target type at this pass! " );
            break;
        }
    }

    if( node.arguments()->size() > 0 )
    {
        const auto argumentProperties = intersectPropertiesOf< Expressions >( *node.arguments() );
        node.setProperties( callProperties * argumentProperties );
    }
    else
    {
        node.setProperties( callProperties );
    }
}

void PropertyResolverVisitor::visit( MethodCallExpression& node )
{
    RecursiveVisitor::visit( node );

    libcasm_ir::Properties callProperties;
    if( node.methodType() == MethodCallExpression::MethodType::BUILTIN )
    {
        const auto& annotation = libcasm_ir::Annotation::find( node.targetBuiltinId() );
        callProperties = annotation.properties();
    }
    else
    {
        m_log.error(
            { node.sourceLocation() },
            "method type '" + node.methodTypeName() + "' is not implemented!" );
        return;
    }

    if( node.arguments()->size() > 0 )
    {
        const auto argumentProperties = intersectPropertiesOf< Expressions >( *node.arguments() );
        node.setProperties( callProperties * argumentProperties );
    }
    else
    {
        node.setProperties( callProperties );
    }
}

void PropertyResolverVisitor::visit( LiteralCallExpression& node )
{
    RecursiveVisitor::visit( node );

    node.setProperties( node.object()->properties() * node.literal()->properties() );
}

void PropertyResolverVisitor::visit( IndirectCallExpression& node )
{
    RecursiveVisitor::visit( node );

    libcasm_ir::Properties callProperties;
    if( node.isFunctionCall() )
    {
        callProperties.set( libcasm_ir::Property::SIDE_EFFECT_FREE );
    }

    if( node.arguments()->size() > 0 )
    {
        const auto argumentProperties = intersectPropertiesOf< Expressions >( *node.arguments() );
        node.setProperties( callProperties * argumentProperties );
    }
    else
    {
        node.setProperties( callProperties );
    }
}

void PropertyResolverVisitor::visit( TypeCastingExpression& node )
{
    RecursiveVisitor::visit( node );

    // propagate the fromExpression properties
    node.setProperties( node.fromExpression()->properties() );
}

void PropertyResolverVisitor::visit( UnaryExpression& node )
{
    RecursiveVisitor::visit( node );

    const auto& annotation = libcasm_ir::Annotation::find( node.op() );
    node.setProperties( annotation.properties() * node.expression()->properties() );
}

void PropertyResolverVisitor::visit( BinaryExpression& node )
{
    RecursiveVisitor::visit( node );

    const auto& annotation = libcasm_ir::Annotation::find( node.op() );
    node.setProperties(
        annotation.properties() * node.left()->properties() * node.right()->properties() );
}

void PropertyResolverVisitor::visit( LetExpression& node )
{
    RecursiveVisitor::visit( node );

    auto properties = node.expression()->properties();
    for( auto const& variableBinding : *node.variableBindings() )
    {
        properties = properties * variableBinding->expression()->properties();
    }
    node.setProperties( properties );
}

void PropertyResolverVisitor::visit( ConditionalExpression& node )
{
    RecursiveVisitor::visit( node );

    node.setProperties(
        node.condition()->properties() * node.thenExpression()->properties() *
        node.elseExpression()->properties() );
}

void PropertyResolverVisitor::visit( ChooseExpression& node )
{
    RecursiveVisitor::visit( node );

    auto properties = node.universe()->properties() * node.expression()->properties();
    properties.unset( libcasm_ir::Property::PURE );  // randomness is in-pure
    node.setProperties( properties );
}

void PropertyResolverVisitor::visit( UniversalQuantifierExpression& node )
{
    RecursiveVisitor::visit( node );

    node.setProperties( node.universe()->properties() * node.proposition()->properties() );
}

void PropertyResolverVisitor::visit( ExistentialQuantifierExpression& node )
{
    RecursiveVisitor::visit( node );

    node.setProperties( node.universe()->properties() * node.proposition()->properties() );
}

void PropertyResolverVisitor::visit( CardinalityExpression& node )
{
    RecursiveVisitor::visit( node );

    const auto& annotation = libcasm_ir::Annotation::find( node.targetBuiltinId() );
    node.setProperties( annotation.properties() * node.expression()->properties() );
}

//
//
// PropertyResolverPass
//

void PropertyResolverPass::usage( libpass::PassUsage& pu )
{
    pu.require< SourceToAstPass >();
    pu.scheduleAfter< TypeInferencePass >();
}

u1 PropertyResolverPass::run( libpass::PassResult& pr )
{
    libcasm_fe::Logger log( &id, stream() );

    const auto data = pr.output< SourceToAstPass >();
    const auto specification = data->specification();

    PropertyResolverVisitor visitor( log );
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
