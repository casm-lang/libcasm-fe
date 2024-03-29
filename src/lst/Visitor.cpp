//
//  Copyright (C) 2014-2024 CASM Organization <https://casm-lang.org>
//  All rights reserved.
//
//  Developed by: Philipp Paulweber et al.
//  <https://github.com/casm-lang/libcasm-fe/graphs/contributors>
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

#include "Visitor.h"

#include <libcasm-fe/lst/Definition>
#include <libcasm-fe/lst/Expression>
#include <libcasm-fe/lst/Literal>
#include <libcasm-fe/lst/Root>
#include <libcasm-fe/lst/Rule>

using namespace libcasm_fe;
using namespace LST;

//
//
// RecursiveVisitor
//

void RecursiveVisitor::visit( Root& node )
{
    node.definitions()->accept( *this );
}

void RecursiveVisitor::visit( VariableDefinition& node )
{
    node.identifier()->accept( *this );
}

void RecursiveVisitor::visit( FunctionDefinition& node )
{
    node.identifier()->accept( *this );
    node.defined()->accept( *this );
    node.initially()->accept( *this );
}

void RecursiveVisitor::visit( DerivedDefinition& node )
{
    node.identifier()->accept( *this );
    node.arguments()->accept( *this );
    node.expression()->accept( *this );
}

void RecursiveVisitor::visit( RuleDefinition& node )
{
    node.identifier()->accept( *this );
    node.arguments()->accept( *this );
    node.rule()->accept( *this );
}

void RecursiveVisitor::visit( EnumeratorDefinition& node )
{
    node.identifier()->accept( *this );
}

void RecursiveVisitor::visit( EnumerationDefinition& node )
{
    node.enumerators()->accept( *this );
}

void RecursiveVisitor::visit( InvariantDefinition& node )
{
    node.identifier()->accept( *this );
    node.expression()->accept( *this );
}

void RecursiveVisitor::visit( DomainDefinition& node )
{
}

void RecursiveVisitor::visit( BuiltinDefinition& node )
{
}

void RecursiveVisitor::visit( ValueLiteral& node )
{
}

void RecursiveVisitor::visit( ReferenceLiteral& node )
{
    node.identifier()->accept( *this );
}

void RecursiveVisitor::visit( SetLiteral& node )
{
    node.expressions()->accept( *this );
}

void RecursiveVisitor::visit( ListLiteral& node )
{
    node.expressions()->accept( *this );
}

void RecursiveVisitor::visit( RangeLiteral& node )
{
    node.left()->accept( *this );
    node.right()->accept( *this );
}

void RecursiveVisitor::visit( TupleLiteral& node )
{
    node.expressions()->accept( *this );
}

void RecursiveVisitor::visit( RecordLiteral& node )
{
    node.namedExpressions()->accept( *this );
}

void RecursiveVisitor::visit( NamedExpression& node )
{
    node.identifier()->accept( *this );
    node.expression()->accept( *this );
}

void RecursiveVisitor::visit( DirectCallExpression& node )
{
    node.arguments()->accept( *this );
}

void RecursiveVisitor::visit( IndirectCallExpression& node )
{
    node.expression()->accept( *this );
    node.arguments()->accept( *this );
}

void RecursiveVisitor::visit( LetExpression& node )
{
    node.variableBindings()->accept( *this );
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
    node.condition()->accept( *this );
    node.expression()->accept( *this );
}

void RecursiveVisitor::visit( UniversalQuantifierExpression& node )
{
    node.predicateVariables()->accept( *this );
    node.universe()->accept( *this );
    node.proposition()->accept( *this );
}

void RecursiveVisitor::visit( ExistentialQuantifierExpression& node )
{
    node.predicateVariables()->accept( *this );
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

void RecursiveVisitor::visit( DefaultCase& node )
{
    node.rule()->accept( *this );
}

void RecursiveVisitor::visit( ExpressionCase& node )
{
    node.expression()->accept( *this );
    node.rule()->accept( *this );
}

void RecursiveVisitor::visit( CaseRule& node )
{
    node.expression()->accept( *this );
    node.cases()->accept( *this );
}

void RecursiveVisitor::visit( LetRule& node )
{
    node.variableBindings()->accept( *this );
    node.rule()->accept( *this );
}

void RecursiveVisitor::visit( LocalRule& node )
{
    node.localFunctions()->accept( *this );
    node.rule()->accept( *this );
}

void RecursiveVisitor::visit( ForallRule& node )
{
    node.variables()->accept( *this );
    node.universe()->accept( *this );
    node.condition()->accept( *this );
    node.rule()->accept( *this );
}

void RecursiveVisitor::visit( ChooseRule& node )
{
    node.variable()->accept( *this );
    node.universe()->accept( *this );
    node.condition()->accept( *this );
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

void RecursiveVisitor::visit( Identifier& node )
{
}

void RecursiveVisitor::visit( IdentifierPath& node )
{
    node.identifiers()->accept( *this );
}

void RecursiveVisitor::visit( VariableBinding& node )
{
    node.variable()->accept( *this );
    node.expression()->accept( *this );
}

//
//
// EmptyVisitor
//

void EmptyVisitor::visit( Root& )
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

void EmptyVisitor::visit( InvariantDefinition& )
{
}

void EmptyVisitor::visit( DomainDefinition& )
{
}

void EmptyVisitor::visit( BuiltinDefinition& )
{
}

void EmptyVisitor::visit( ValueLiteral& )
{
}

void EmptyVisitor::visit( ReferenceLiteral& )
{
}

void EmptyVisitor::visit( SetLiteral& )
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

void EmptyVisitor::visit( NamedExpression& )
{
}

void EmptyVisitor::visit( DirectCallExpression& )
{
}

void EmptyVisitor::visit( IndirectCallExpression& )
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

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
