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

#include "PropertyResolverPass.h"

#include "../Logger.h"
#include "../ast/RecursiveVisitor.h"

#include <libcasm-ir/Annotation>

#include <libpass/PassRegistry>
#include <libpass/PassResult>
#include <libpass/PassUsage>

using namespace libcasm_fe;
using namespace Ast;

char PropertyResolverPass::id = 0;

static libpass::PassRegistration< PropertyResolverPass > PASS(
    "ASTPropertyResolverPass",
    "property resolving and checking of AST representation",
    "ast-prop-res",
    0 );

class PropertyResolverVisitor final : public RecursiveVisitor
{
  public:
    PropertyResolverVisitor( libcasm_fe::Logger& log );

    void visit( VariableDefinition& node ) override;
    void visit( FunctionDefinition& node ) override;
    void visit( DerivedDefinition& node ) override;
    void visit( RuleDefinition& node ) override;
    void visit( EnumeratorDefinition& node ) override;
    void visit( EnumerationDefinition& node ) override;

    void visit( ValueAtom& node ) override;
    void visit( ReferenceAtom& node ) override;
    void visit( UndefAtom& node ) override;
    void visit( DirectCallExpression& node ) override;
    void visit( MethodCallExpression& node ) override;
    void visit( TypeCastingExpression& node ) override;
    void visit( IndirectCallExpression& node ) override;
    void visit( UnaryExpression& node ) override;
    void visit( BinaryExpression& node ) override;
    void visit( RangeExpression& node ) override;
    void visit( ListExpression& node ) override;
    void visit( LetExpression& node ) override;
    void visit( ConditionalExpression& node ) override;
    void visit( ChooseExpression& node ) override;
    void visit( UniversalQuantifierExpression& node ) override;
    void visit( ExistentialQuantifierExpression& node ) override;

    void visit( SkipRule& node ) override;
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

    void visit( UnresolvedType& node ) override;
    void visit( BasicType& node ) override;
    void visit( ComposedType& node ) override;
    void visit( FixedSizedType& node ) override;
    void visit( RelationType& node ) override;

    void visit( BasicAttribute& node ) override;
    void visit( ExpressionAttribute& node ) override;

    void visit( Identifier& node ) override;
    void visit( IdentifierPath& node ) override;
    void visit( ExpressionCase& node ) override;
    void visit( DefaultCase& node ) override;

  private:
    libcasm_fe::Logger& m_log;
};

PropertyResolverVisitor::PropertyResolverVisitor( libcasm_fe::Logger& log )
: m_log( log )
{
}

void PropertyResolverVisitor::visit( VariableDefinition& node )
{
    node.setProperty( libcasm_ir::Property::CONSTANT );
    node.setProperty( libcasm_ir::Property::PURE );

    RecursiveVisitor::visit( node );
}

void PropertyResolverVisitor::visit( FunctionDefinition& node )
{
    switch( node.classification() )
    {
        case FunctionDefinition::Classification::UNKNOWN:
        {
            m_log.error( { node.sourceLocation() }, "function classification 'UNKNOWN' found!" );
            break;
        }
        case FunctionDefinition::Classification::IN:
        {
            node.setProperty( libcasm_ir::Property::CONSTANT );
            break;
        }
        case FunctionDefinition::Classification::CONTROLLED:  // [fallthrough]
        case FunctionDefinition::Classification::SHARED:
        {
            node.setProperty( libcasm_ir::Property::ALTERABLE );
            node.setProperty( libcasm_ir::Property::CONSTANT );
            break;
        }
        case FunctionDefinition::Classification::OUT:
        {
            node.setProperty( libcasm_ir::Property::ALTERABLE );
            break;
        }
        case FunctionDefinition::Classification::STATIC:
        {
            node.setProperty( libcasm_ir::Property::CONSTANT );
            node.setProperty( libcasm_ir::Property::PURE );
            break;
        }
    }

    RecursiveVisitor::visit( node );
}

void PropertyResolverVisitor::visit( DerivedDefinition& node )
{
    node.setProperty( libcasm_ir::Property::CONSTANT );

    RecursiveVisitor::visit( node );

    const auto& expressionProperties = node.expression()->properties();

    if( not expressionProperties.isSet( libcasm_ir::Property::CONSTANT ) )
    {
        m_log.error(
            { node.expression()->sourceLocation() },
            "expression of " + node.description() + " '" + node.identifier()->name() +
                "' violates 'constant' property",
            Code::DerivedDefinitionExpressionIsNotConstant );
    }
}

void PropertyResolverVisitor::visit( RuleDefinition& node )
{
    RecursiveVisitor::visit( node );
}

void PropertyResolverVisitor::visit( EnumeratorDefinition& node )
{
    node.setProperty( libcasm_ir::Property::CONSTANT );
    node.setProperty( libcasm_ir::Property::PURE );

    RecursiveVisitor::visit( node );
}

void PropertyResolverVisitor::visit( EnumerationDefinition& node )
{
    node.setProperty( libcasm_ir::Property::CONSTANT );
    node.setProperty( libcasm_ir::Property::PURE );

    RecursiveVisitor::visit( node );
}

void PropertyResolverVisitor::visit( ValueAtom& node )
{
    node.setProperty( libcasm_ir::Property::CONSTANT );
    node.setProperty( libcasm_ir::Property::PURE );

    RecursiveVisitor::visit( node );
}

void PropertyResolverVisitor::visit( ReferenceAtom& node )
{
    node.setProperty( libcasm_ir::Property::CONSTANT );
    node.setProperty( libcasm_ir::Property::PURE );

    RecursiveVisitor::visit( node );
}

void PropertyResolverVisitor::visit( UndefAtom& node )
{
    node.setProperty( libcasm_ir::Property::CONSTANT );
    node.setProperty( libcasm_ir::Property::PURE );

    RecursiveVisitor::visit( node );
}

void PropertyResolverVisitor::visit( DirectCallExpression& node )
{
    RecursiveVisitor::visit( node );

    switch( node.targetType() )
    {
        case CallExpression::TargetType::BUILTIN:
        {
            const auto& annotation = libcasm_ir::Annotation::find( node.targetBuiltinId() );
            node.setProperties( annotation.properties() );
            break;
        }
        case CallExpression::TargetType::VARIABLE:  // [[fallthrough]]
        case CallExpression::TargetType::FUNCTION:  // [[fallthrough]]
        case CallExpression::TargetType::DERIVED:   // [[fallthrough]]
        case CallExpression::TargetType::RULE:
        {
            const auto& definition = node.targetDefinition();
            assert( definition.get() != nullptr );
            node.setProperties( definition->properties() );
            break;
        }
        case CallExpression::TargetType::SELF:         // [[fallthrough]]
        case CallExpression::TargetType::TYPE_DOMAIN:  // [[fallthrough]]
        case CallExpression::TargetType::CONSTANT:
        {
            node.setProperty( libcasm_ir::Property::CONSTANT );
            node.setProperty( libcasm_ir::Property::PURE );
            break;
        }
        case CallExpression::TargetType::UNKNOWN:
        {
            assert( !" direct call cannot have UNKNOWN target type at this pass! " );
            break;
        }
    }
}

void PropertyResolverVisitor::visit( MethodCallExpression& node )
{
    RecursiveVisitor::visit( node );

    if( node.methodType() == MethodCallExpression::MethodType::BUILTIN )
    {
        const auto& annotation = libcasm_ir::Annotation::find( node.targetBuiltinId() );
        node.setProperties( annotation.properties() );
    }
    else
    {
        m_log.error(
            { node.sourceLocation() }, "method type '" + node.methodTypeName() + "' is invalid!" );
    }
}

void PropertyResolverVisitor::visit( TypeCastingExpression& node )
{
    RecursiveVisitor::visit( node );

    // propagate the fromExpression properties
    node.setProperties( node.fromExpression()->properties() );
}

void PropertyResolverVisitor::visit( IndirectCallExpression& node )
{
    RecursiveVisitor::visit( node );

    switch( node.targetType() )
    {
        case CallExpression::TargetType::FUNCTION:
        {
            node.setProperty( libcasm_ir::Property::CONSTANT );
            break;
        }
        case CallExpression::TargetType::RULE:
        {
            node.setProperty( libcasm_ir::Property::ALTERABLE );
            node.setProperty( libcasm_ir::Property::CONSTANT );
            break;
        }
        case CallExpression::TargetType::BUILTIN:      // [[fallthrough]]
        case CallExpression::TargetType::VARIABLE:     // [[fallthrough]]
        case CallExpression::TargetType::DERIVED:      // [[fallthrough]]
        case CallExpression::TargetType::SELF:         // [[fallthrough]]
        case CallExpression::TargetType::TYPE_DOMAIN:  // [[fallthrough]]
        case CallExpression::TargetType::CONSTANT:
        {
            m_log.error(
                { node.sourceLocation() },
                "target type '" + node.targetTypeName() + "' is invalid!" );
            break;
        }
        case CallExpression::TargetType::UNKNOWN:
        {
            m_log.error( { node.sourceLocation() }, "target type 'UNKNOWN' found!" );
            break;
        }
    }
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

void PropertyResolverVisitor::visit( RangeExpression& node )
{
    RecursiveVisitor::visit( node );
}

void PropertyResolverVisitor::visit( ListExpression& node )
{
    RecursiveVisitor::visit( node );
}

void PropertyResolverVisitor::visit( LetExpression& node )
{
    RecursiveVisitor::visit( node );

    node.setProperties( node.expression()->properties() );
}

void PropertyResolverVisitor::visit( ConditionalExpression& node )
{
    RecursiveVisitor::visit( node );

    node.setProperties( node.thenExpression()->properties() * node.elseExpression()->properties() );
}

void PropertyResolverVisitor::visit( ChooseExpression& node )
{
    RecursiveVisitor::visit( node );

    node.setProperties( node.expression()->properties() );
}

void PropertyResolverVisitor::visit( UniversalQuantifierExpression& node )
{
    RecursiveVisitor::visit( node );
}

void PropertyResolverVisitor::visit( ExistentialQuantifierExpression& node )
{
    RecursiveVisitor::visit( node );
}

void PropertyResolverVisitor::visit( SkipRule& node )
{
    RecursiveVisitor::visit( node );
}

void PropertyResolverVisitor::visit( ConditionalRule& node )
{
    RecursiveVisitor::visit( node );
}

void PropertyResolverVisitor::visit( CaseRule& node )
{
    RecursiveVisitor::visit( node );
}

void PropertyResolverVisitor::visit( LetRule& node )
{
    RecursiveVisitor::visit( node );
}

void PropertyResolverVisitor::visit( ForallRule& node )
{
    RecursiveVisitor::visit( node );
}

void PropertyResolverVisitor::visit( ChooseRule& node )
{
    RecursiveVisitor::visit( node );
}

void PropertyResolverVisitor::visit( IterateRule& node )
{
    RecursiveVisitor::visit( node );
}

void PropertyResolverVisitor::visit( BlockRule& node )
{
    RecursiveVisitor::visit( node );
}

void PropertyResolverVisitor::visit( SequenceRule& node )
{
    RecursiveVisitor::visit( node );
}

void PropertyResolverVisitor::visit( UpdateRule& node )
{
    RecursiveVisitor::visit( node );
}

void PropertyResolverVisitor::visit( CallRule& node )
{
    RecursiveVisitor::visit( node );
}

void PropertyResolverVisitor::visit( UnresolvedType& node )
{
    RecursiveVisitor::visit( node );
}

void PropertyResolverVisitor::visit( BasicType& node )
{
    RecursiveVisitor::visit( node );
}

void PropertyResolverVisitor::visit( ComposedType& node )
{
    RecursiveVisitor::visit( node );
}

void PropertyResolverVisitor::visit( FixedSizedType& node )
{
    RecursiveVisitor::visit( node );
}

void PropertyResolverVisitor::visit( RelationType& node )
{
    RecursiveVisitor::visit( node );
}

void PropertyResolverVisitor::visit( BasicAttribute& node )
{
    RecursiveVisitor::visit( node );
}

void PropertyResolverVisitor::visit( ExpressionAttribute& node )
{
    RecursiveVisitor::visit( node );
}

void PropertyResolverVisitor::visit( Identifier& node )
{
    RecursiveVisitor::visit( node );
}

void PropertyResolverVisitor::visit( IdentifierPath& node )
{
    RecursiveVisitor::visit( node );
}

void PropertyResolverVisitor::visit( ExpressionCase& node )
{
    RecursiveVisitor::visit( node );
}

void PropertyResolverVisitor::visit( DefaultCase& node )
{
    RecursiveVisitor::visit( node );
}

void PropertyResolverPass::usage( libpass::PassUsage& pu )
{
    pu.require< TypeInferencePass >();
}

u1 PropertyResolverPass::run( libpass::PassResult& pr )
{
    libcasm_fe::Logger log( &id, stream() );

    const auto data = pr.result< TypeInferencePass >();
    const auto specification = data->specification();

    PropertyResolverVisitor visitor( log );
    specification->definitions()->accept( visitor );

    const auto errors = log.errors();
    if( errors > 0 )
    {
        log.debug( "found %lu error(s) during property resolving", errors );
        return false;
    }

    pr.setResult< PropertyResolverPass >( data );
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
