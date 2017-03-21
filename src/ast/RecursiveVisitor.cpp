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

#include "RecursiveVisitor.h"

#include "Specification.h"

using namespace libcasm_fe;
using namespace Ast;

void RecursiveVisitor::visit( Specification& node )
{
    node.name()->accept( *this );
    node.definitions()->accept( *this );
}

void RecursiveVisitor::visit( VariableDefinition& node )
{
    node.identifier()->accept( *this );
    node.variableType()->accept( *this );
}

void RecursiveVisitor::visit( FunctionDefinition& node )
{
    node.identifier()->accept( *this );
    node.argumentTypes()->accept( *this );
    node.returnType()->accept( *this );
    node.initializers()->accept( *this );
    node.defaultValue()->accept( *this );
}

void RecursiveVisitor::visit( DerivedDefinition& node )
{
    node.identifier()->accept( *this );
    node.arguments()->accept( *this );
    node.returnType()->accept( *this );
    node.expression()->accept( *this );
}

void RecursiveVisitor::visit( RuleDefinition& node )
{
    node.identifier()->accept( *this );
    node.arguments()->accept( *this );
    node.returnType()->accept( *this );
    node.rule()->accept( *this );
}

void RecursiveVisitor::visit( EnumerationDefinition& node )
{
    node.identifier()->accept( *this );
    node.enumerators()->accept( *this );
}

void RecursiveVisitor::visit( ValueAtom& node )
{
}

void RecursiveVisitor::visit( RuleReferenceAtom& node )
{
    node.identifier()->accept( *this );
}

void RecursiveVisitor::visit( ZeroAtom& node )
{
}

void RecursiveVisitor::visit( UndefAtom& node )
{
}

void RecursiveVisitor::visit( DirectCallExpression& node )
{
    node.identifier()->accept( *this );
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

void RecursiveVisitor::visit( ConditionalExpression& node )
{
    node.condition()->accept( *this );
    node.thenExpression()->accept( *this );
    node.elseExpression()->accept( *this );
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

void RecursiveVisitor::visit( RangedType& node )
{
    node.name()->accept( *this );
    node.lowerBound()->accept( *this );
    node.upperBound()->accept( *this );
}

void RecursiveVisitor::visit( IdentifierNode& node )
{
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