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

#include "EmptyVisitor.h"

#include "Specification.h"

using namespace libcasm_fe;
using namespace Ast;

void EmptyVisitor::visit( Specification& )
{
}

void EmptyVisitor::visit( VariableDefinition& )
{
}

void EmptyVisitor::visit( FunctionDefinition& )
{
}

void EmptyVisitor::visit( DerivedDefinition& )
{
}

void EmptyVisitor::visit( RuleDefinition& )
{
}

void EmptyVisitor::visit( EnumerationDefinition& )
{
}

void EmptyVisitor::visit( ValueAtom& )
{
}

void EmptyVisitor::visit( ReferenceAtom& )
{
}

void EmptyVisitor::visit( UndefAtom& )
{
}

void EmptyVisitor::visit( DirectCallExpression& )
{
}

void EmptyVisitor::visit( IndirectCallExpression& )
{
}

void EmptyVisitor::visit( UnaryExpression& )
{
}

void EmptyVisitor::visit( BinaryExpression& )
{
}

void EmptyVisitor::visit( RangeExpression& )
{
}

void EmptyVisitor::visit( ListExpression& )
{
}

void EmptyVisitor::visit( ConditionalExpression& )
{
}

void EmptyVisitor::visit( ChooseExpression& )
{
}

void EmptyVisitor::visit( UniversalQuantifierExpression& )
{
}

void EmptyVisitor::visit( ExistentialQuantifierExpression& )
{
}

void EmptyVisitor::visit( SkipRule& )
{
}

void EmptyVisitor::visit( ConditionalRule& )
{
}

void EmptyVisitor::visit( CaseRule& )
{
}

void EmptyVisitor::visit( LetRule& )
{
}

void EmptyVisitor::visit( ForallRule& )
{
}

void EmptyVisitor::visit( ChooseRule& )
{
}

void EmptyVisitor::visit( IterateRule& )
{
}

void EmptyVisitor::visit( BlockRule& )
{
}

void EmptyVisitor::visit( SequenceRule& )
{
}

void EmptyVisitor::visit( UpdateRule& )
{
}

void EmptyVisitor::visit( CallRule& )
{
}

void EmptyVisitor::visit( UnresolvedType& )
{
}

void EmptyVisitor::visit( BasicType& )
{
}

void EmptyVisitor::visit( ComposedType& )
{
}

void EmptyVisitor::visit( FixedSizedType& )
{
}

void EmptyVisitor::visit( RelationType& )
{
}

void EmptyVisitor::visit( BasicAttribute& )
{
}

void EmptyVisitor::visit( ExpressionAttribute& )
{
}

void EmptyVisitor::visit( Identifier& )
{
}

void EmptyVisitor::visit( IdentifierPath& )
{
}

void EmptyVisitor::visit( ExpressionCase& )
{
}

void EmptyVisitor::visit( DefaultCase& )
{
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
