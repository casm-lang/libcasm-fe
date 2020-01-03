//
//  Copyright (C) 2014-2021 CASM Organization <https://casm-lang.org>
//  All rights reserved.
//
//  Developed by: Philipp Paulweber
//                Emmanuel Pescosta
//                Jakob Moosbrugger
//                Florian Hahn
//                Ioan Molnar
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

#include "EmptyVisitor.h"

#include "Definition.h"
#include "Expression.h"
#include "Rule.h"

using namespace libcasm_fe;
using namespace Ast;

void EmptyVisitor::visit( HeaderDefinition& )
{
}

void EmptyVisitor::visit( InitDefinition& )
{
}

void EmptyVisitor::visit( Initially& )
{
}

void EmptyVisitor::visit( Initializer& )
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

void EmptyVisitor::visit( EnumeratorDefinition& )
{
}

void EmptyVisitor::visit( EnumerationDefinition& )
{
}

void EmptyVisitor::visit( UsingDefinition& )
{
}

void EmptyVisitor::visit( UsingPathDefinition& )
{
}

void EmptyVisitor::visit( InvariantDefinition& )
{
}

void EmptyVisitor::visit( ImportDefinition& )
{
}

void EmptyVisitor::visit( DomainDefinition& )
{
}

void EmptyVisitor::visit( StructureDefinition& )
{
}

void EmptyVisitor::visit( BehaviorDefinition& )
{
}

void EmptyVisitor::visit( ImplementDefinition& )
{
}

void EmptyVisitor::visit( BuiltinDefinition& )
{
}

void EmptyVisitor::visit( Declaration& )
{
}

void EmptyVisitor::visit( UndefLiteral& )
{
}

void EmptyVisitor::visit( ValueLiteral& )
{
}

void EmptyVisitor::visit( ReferenceLiteral& )
{
}

void EmptyVisitor::visit( ListLiteral& )
{
}

void EmptyVisitor::visit( RangeLiteral& )
{
}

void EmptyVisitor::visit( TupleLiteral& )
{
}

void EmptyVisitor::visit( RecordLiteral& )
{
}

void EmptyVisitor::visit( EmbracedExpression& )
{
}

void EmptyVisitor::visit( NamedExpression& )
{
}

void EmptyVisitor::visit( DirectCallExpression& )
{
}

void EmptyVisitor::visit( MethodCallExpression& )
{
}

void EmptyVisitor::visit( LiteralCallExpression& )
{
}

void EmptyVisitor::visit( IndirectCallExpression& )
{
}

void EmptyVisitor::visit( TypeCastingExpression& )
{
}

void EmptyVisitor::visit( UnaryExpression& )
{
}

void EmptyVisitor::visit( BinaryExpression& )
{
}

void EmptyVisitor::visit( LetExpression& )
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

void EmptyVisitor::visit( CardinalityExpression& )
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

void EmptyVisitor::visit( LocalRule& )
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

void EmptyVisitor::visit( WhileRule& )
{
}

void EmptyVisitor::visit( UnresolvedType& )
{
}

void EmptyVisitor::visit( BasicType& )
{
}

void EmptyVisitor::visit( TupleType& )
{
}

void EmptyVisitor::visit( RecordType& )
{
}

void EmptyVisitor::visit( TemplateType& )
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

void EmptyVisitor::visit( Defined& )
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

void EmptyVisitor::visit( VariableBinding& )
{
}

void EmptyVisitor::visit( Token& )
{
}

void EmptyVisitor::visit( Span& )
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
