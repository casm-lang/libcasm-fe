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

#include "RecursiveVisitor.h"

#include "Definition.h"
#include "Expression.h"
#include "Literal.h"
#include "Rule.h"

using namespace libcasm_fe;
using namespace Ast;

//
//
// Definitions
//

void RecursiveVisitor::visit( HeaderDefinition& node )
{
    node.attributes()->accept( *this );
    node.identifier()->accept( *this );
}

void RecursiveVisitor::visit( VariableDefinition& node )
{
    node.delimiter()->accept( *this );
    node.attributes()->accept( *this );
    node.identifier()->accept( *this );
    node.colon()->accept( *this );
    node.variableType()->accept( *this );
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

void RecursiveVisitor::visit( UsingDefinition& node )
{
    node.identifier()->accept( *this );
    node.type()->accept( *this );
    node.attributes()->accept( *this );
}

void RecursiveVisitor::visit( InvariantDefinition& node )
{
    node.identifier()->accept( *this );
    node.expression()->accept( *this );
    node.attributes()->accept( *this );
}

//
//
// Literals
//

void RecursiveVisitor::visit( UndefLiteral& node )
{
}

void RecursiveVisitor::visit( ValueLiteral& node )
{
}

void RecursiveVisitor::visit( ReferenceLiteral& node )
{
    node.identifier()->accept( *this );
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

//
//
// Expressions
//

void RecursiveVisitor::visit( NamedExpression& node )
{
    node.delimiter()->accept( *this );
    node.leftBrace()->accept( *this );

    node.identifier()->accept( *this );
    node.colon()->accept( *this );
    node.expression()->accept( *this );

    node.rightBrace()->accept( *this );
}

void RecursiveVisitor::visit( DirectCallExpression& node )
{
    node.delimiter()->accept( *this );
    node.leftBrace()->accept( *this );

    node.identifier()->accept( *this );
    node.arguments()->accept( *this );

    node.rightBrace()->accept( *this );
}

void RecursiveVisitor::visit( MethodCallExpression& node )
{
    node.delimiter()->accept( *this );
    node.leftBrace()->accept( *this );

    node.object()->accept( *this );
    node.methodName()->accept( *this );
    node.arguments()->accept( *this );

    node.rightBrace()->accept( *this );
}

void RecursiveVisitor::visit( LiteralCallExpression& node )
{
    node.delimiter()->accept( *this );
    node.leftBrace()->accept( *this );

    node.object()->accept( *this );
    node.dot()->accept( *this );
    node.literal()->accept( *this );

    node.rightBrace()->accept( *this );
}

void RecursiveVisitor::visit( IndirectCallExpression& node )
{
    node.delimiter()->accept( *this );
    node.leftBrace()->accept( *this );

    node.expression()->accept( *this );
    node.arguments()->accept( *this );

    node.rightBrace()->accept( *this );
}

void RecursiveVisitor::visit( TypeCastingExpression& node )
{
    node.delimiter()->accept( *this );
    node.leftBrace()->accept( *this );

    node.fromExpression()->accept( *this );
    node.as()->accept( *this );
    node.asType()->accept( *this );

    node.rightBrace()->accept( *this );
}

void RecursiveVisitor::visit( UnaryExpression& node )
{
    node.delimiter()->accept( *this );
    node.leftBrace()->accept( *this );

    node.operation()->accept( *this );
    node.expression()->accept( *this );

    node.rightBrace()->accept( *this );
}

void RecursiveVisitor::visit( BinaryExpression& node )
{
    node.delimiter()->accept( *this );
    node.leftBrace()->accept( *this );

    node.left()->accept( *this );
    node.operation()->accept( *this );
    node.right()->accept( *this );

    node.rightBrace()->accept( *this );
}

void RecursiveVisitor::visit( LetExpression& node )
{
    node.delimiter()->accept( *this );
    node.leftBrace()->accept( *this );

    node.let()->accept( *this );
    node.variableBindings()->accept( *this );
    node.in()->accept( *this );
    node.expression()->accept( *this );

    node.rightBrace()->accept( *this );
}

void RecursiveVisitor::visit( ConditionalExpression& node )
{
    node.delimiter()->accept( *this );
    node.leftBrace()->accept( *this );

    node.ifToken()->accept( *this );
    node.condition()->accept( *this );
    node.thenToken()->accept( *this );
    node.thenExpression()->accept( *this );
    node.elseToken()->accept( *this );
    node.elseExpression()->accept( *this );

    node.rightBrace()->accept( *this );
}

void RecursiveVisitor::visit( ChooseExpression& node )
{
    node.delimiter()->accept( *this );
    node.leftBrace()->accept( *this );

    node.chooseToken()->accept( *this );
    node.variables()->accept( *this );
    node.inToken()->accept( *this );
    node.universe()->accept( *this );
    node.doToken()->accept( *this );
    node.expression()->accept( *this );

    node.rightBrace()->accept( *this );
}

void RecursiveVisitor::visit( UniversalQuantifierExpression& node )
{
    node.delimiter()->accept( *this );
    node.leftBrace()->accept( *this );

    node.quantifierToken()->accept( *this );
    node.predicateVariables()->accept( *this );
    node.inToken()->accept( *this );
    node.universe()->accept( *this );
    node.doToken()->accept( *this );
    node.proposition()->accept( *this );

    node.rightBrace()->accept( *this );
}

void RecursiveVisitor::visit( ExistentialQuantifierExpression& node )
{
    node.delimiter()->accept( *this );
    node.leftBrace()->accept( *this );

    node.quantifierToken()->accept( *this );
    node.predicateVariables()->accept( *this );
    node.inToken()->accept( *this );
    node.universe()->accept( *this );
    node.doToken()->accept( *this );
    node.proposition()->accept( *this );

    node.rightBrace()->accept( *this );
}

void RecursiveVisitor::visit( CardinalityExpression& node )
{
    node.delimiter()->accept( *this );
    node.leftBrace()->accept( *this );

    node.leftVerticalBar()->accept( *this );
    node.expression()->accept( *this );
    node.rightVerticalBar()->accept( *this );

    node.rightBrace()->accept( *this );
}

//
//
// Rules
//

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
    node.variableBindings()->accept( *this );
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
    node.variables()->accept( *this );
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

void RecursiveVisitor::visit( WhileRule& node )
{
    node.condition()->accept( *this );
    node.rule()->accept( *this );
}

//
//
// Types
//

void RecursiveVisitor::visit( UnresolvedType& node )
{
    node.delimiter()->accept( *this );
    node.name()->accept( *this );
}

void RecursiveVisitor::visit( BasicType& node )
{
    node.delimiter()->accept( *this );
    node.name()->accept( *this );
}

void RecursiveVisitor::visit( ComposedType& node )
{
    node.delimiter()->accept( *this );
    node.leftBrace()->accept( *this );
    node.name()->accept( *this );
    if( not node.isNamed() )
    {
        node.subTypes()->accept( *this );
    }
    else
    {
        node.subTypeIdentifiers()->accept( *this );
    }
    node.rightBrace()->accept( *this );
}

void RecursiveVisitor::visit( TemplateType& node )
{
    node.delimiter()->accept( *this );
    node.name()->accept( *this );
    node.leftBrace()->accept( *this );
    node.subTypes()->accept( *this );
    node.rightBrace()->accept( *this );
}

void RecursiveVisitor::visit( RelationType& node )
{
    node.delimiter()->accept( *this );
    node.name()->accept( *this );
    node.leftBrace()->accept( *this );
    node.argumentTypes()->accept( *this );
    node.maps()->accept( *this );
    node.returnType()->accept( *this );
    node.rightBrace()->accept( *this );
}

void RecursiveVisitor::visit( FixedSizedType& node )
{
    node.delimiter()->accept( *this );
    node.name()->accept( *this );
    node.mark()->accept( *this );
    node.size()->accept( *this );
}

//
//
// Attributes
//

void RecursiveVisitor::visit( BasicAttribute& node )
{
    node.leftBrace()->accept( *this );
    node.identifier()->accept( *this );
    node.rightBrace()->accept( *this );
}

void RecursiveVisitor::visit( ExpressionAttribute& node )
{
    node.leftBrace()->accept( *this );
    node.identifier()->accept( *this );
    node.expression()->accept( *this );
    node.rightBrace()->accept( *this );
}

//
//
// Others
//

void RecursiveVisitor::visit( Identifier& node )
{
    node.doubleColon()->accept( *this );
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

void RecursiveVisitor::visit( VariableBinding& node )
{
    node.delimiter()->accept( *this );
    node.variable()->accept( *this );
    node.equal()->accept( *this );
    node.expression()->accept( *this );
}

void RecursiveVisitor::visit( Token& node )
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
