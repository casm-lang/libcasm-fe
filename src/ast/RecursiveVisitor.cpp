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

#include "RecursiveVisitor.h"

#include "Definition.h"
#include "Expression.h"
#include "Rule.h"

using namespace libcasm_fe;
using namespace Ast;

void RecursiveVisitor::visit( HeaderDefinition& node )
{
    node.identifier()->accept( *this );
    node.attributes()->accept( *this );
}

void RecursiveVisitor::visit( VariableDefinition& node )
{
    node.identifier()->accept( *this );
    node.variableType()->accept( *this );
    node.attributes()->accept( *this );
}

void RecursiveVisitor::visit( FunctionDefinition& node )
{
    node.identifier()->accept( *this );
    node.argumentTypes()->accept( *this );
    node.returnType()->accept( *this );
    node.initializers()->accept( *this );
    node.defaultValue()->accept( *this );
    node.attributes()->accept( *this );
}

void RecursiveVisitor::visit( DerivedDefinition& node )
{
    node.identifier()->accept( *this );
    node.arguments()->accept( *this );
    node.returnType()->accept( *this );
    node.expression()->accept( *this );
    node.attributes()->accept( *this );
}

void RecursiveVisitor::visit( RuleDefinition& node )
{
    node.identifier()->accept( *this );
    node.arguments()->accept( *this );
    node.returnType()->accept( *this );
    node.rule()->accept( *this );
    node.attributes()->accept( *this );
}

void RecursiveVisitor::visit( EnumeratorDefinition& node )
{
    node.identifier()->accept( *this );
    node.attributes()->accept( *this );
}

void RecursiveVisitor::visit( EnumerationDefinition& node )
{
    node.identifier()->accept( *this );
    node.enumerators()->accept( *this );
    node.attributes()->accept( *this );
}

void RecursiveVisitor::visit( TypeCastingExpression& node )
{
    node.fromExpression()->accept( *this );
    node.asType()->accept( *this );
}

void RecursiveVisitor::visit( ValueAtom& node )
{
}

void RecursiveVisitor::visit( ReferenceAtom& node )
{
    node.identifier()->accept( *this );
}

void RecursiveVisitor::visit( UndefAtom& node )
{
}

void RecursiveVisitor::visit( DirectCallExpression& node )
{
    node.identifier()->accept( *this );
    node.arguments()->accept( *this );
}

void RecursiveVisitor::visit( MethodCallExpression& node )
{
    node.object()->accept( *this );
    node.methodName()->accept( *this );
    node.arguments()->accept( *this );
}

void RecursiveVisitor::visit( IndirectCallExpression& node )
{
    node.expression()->accept( *this );
    node.arguments()->accept( *this );
}

void RecursiveVisitor::visit( UnaryExpression& node )
{
    node.expression()->accept( *this );
}

void RecursiveVisitor::visit( BinaryExpression& node )
{
    node.left()->accept( *this );
    node.right()->accept( *this );
}

void RecursiveVisitor::visit( RangeExpression& node )
{
    node.left()->accept( *this );
    node.right()->accept( *this );
}

void RecursiveVisitor::visit( ListExpression& node )
{
    node.expressions()->accept( *this );
}

void RecursiveVisitor::visit( LetExpression& node )
{
    node.variable()->accept( *this );
    node.initializer()->accept( *this );
    node.expression()->accept( *this );
}

void RecursiveVisitor::visit( ConditionalExpression& node )
{
    node.condition()->accept( *this );
    node.thenExpression()->accept( *this );
    node.elseExpression()->accept( *this );
}

void RecursiveVisitor::visit( ChooseExpression& node )
{
    node.variable()->accept( *this );
    node.universe()->accept( *this );
    node.expression()->accept( *this );
}

void RecursiveVisitor::visit( UniversalQuantifierExpression& node )
{
    node.predicateVariable()->accept( *this );
    node.universe()->accept( *this );
    node.proposition()->accept( *this );
}

void RecursiveVisitor::visit( ExistentialQuantifierExpression& node )
{
    node.predicateVariable()->accept( *this );
    node.universe()->accept( *this );
    node.proposition()->accept( *this );
}

void RecursiveVisitor::visit( SkipRule& node )
{
}

void RecursiveVisitor::visit( ConditionalRule& node )
{
    node.condition()->accept( *this );
    node.thenRule()->accept( *this );
    node.elseRule()->accept( *this );
}

void RecursiveVisitor::visit( CaseRule& node )
{
    node.expression()->accept( *this );
    node.cases()->accept( *this );
}

void RecursiveVisitor::visit( LetRule& node )
{
    node.variable()->accept( *this );
    node.expression()->accept( *this );
    node.rule()->accept( *this );
}

void RecursiveVisitor::visit( ForallRule& node )
{
    node.variable()->accept( *this );
    node.universe()->accept( *this );
    node.condition()->accept( *this );
    node.rule()->accept( *this );
}

void RecursiveVisitor::visit( ChooseRule& node )
{
    node.variable()->accept( *this );
    node.universe()->accept( *this );
    node.rule()->accept( *this );
}

void RecursiveVisitor::visit( IterateRule& node )
{
    node.rule()->accept( *this );
}

void RecursiveVisitor::visit( BlockRule& node )
{
    node.rules()->accept( *this );
}

void RecursiveVisitor::visit( SequenceRule& node )
{
    node.rules()->accept( *this );
}

void RecursiveVisitor::visit( UpdateRule& node )
{
    node.function()->accept( *this );
    node.expression()->accept( *this );
}

void RecursiveVisitor::visit( CallRule& node )
{
    node.call()->accept( *this );
}

void RecursiveVisitor::visit( UnresolvedType& node )
{
    node.name()->accept( *this );
}

void RecursiveVisitor::visit( BasicType& node )
{
    node.name()->accept( *this );
}

void RecursiveVisitor::visit( ComposedType& node )
{
    node.name()->accept( *this );
    node.subTypes()->accept( *this );
}

void RecursiveVisitor::visit( FixedSizedType& node )
{
    node.name()->accept( *this );
    node.size()->accept( *this );
}

void RecursiveVisitor::visit( RelationType& node )
{
    node.name()->accept( *this );
    node.argumentTypes()->accept( *this );
    node.returnType()->accept( *this );
}

void RecursiveVisitor::visit( BasicAttribute& node )
{
    node.identifier()->accept( *this );
}

void RecursiveVisitor::visit( ExpressionAttribute& node )
{
    node.identifier()->accept( *this );
    node.expression()->accept( *this );
}

void RecursiveVisitor::visit( Identifier& node )
{
}

void RecursiveVisitor::visit( IdentifierPath& node )
{
    node.identifiers()->accept( *this );
}

void RecursiveVisitor::visit( ExpressionCase& node )
{
    node.expression()->accept( *this );
    node.rule()->accept( *this );
}

void RecursiveVisitor::visit( DefaultCase& node )
{
    node.rule()->accept( *this );
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
