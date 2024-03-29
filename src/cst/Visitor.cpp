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

#include "../various/GrammarToken.h"

#include <libcasm-fe/cst/Declaration>
#include <libcasm-fe/cst/Definition>
#include <libcasm-fe/cst/Expression>
#include <libcasm-fe/cst/Literal>
#include <libcasm-fe/cst/Root>
#include <libcasm-fe/cst/Rule>

using namespace libcasm_fe;
using namespace CST;

//
//
// RecursiveVisitor
//

void RecursiveVisitor::visit( Root& node )
{
    node.header()->accept( *this );
    node.definitions()->accept( *this );
    node.spans()->accept( *this );
}

void RecursiveVisitor::visit( HeaderDefinition& node )
{
    node.attributes()->accept( *this );
    node.headerToken()->accept( *this );
}

void RecursiveVisitor::visit( InitDefinition& node )
{
    node.attributes()->accept( *this );
    node.initToken()->accept( *this );
    if( node.initPath() )
    {
        node.initPath()->accept( *this );
    }
    node.leftBraceToken()->accept( *this );
    node.initializers()->accept( *this );
    node.rightBraceToken()->accept( *this );
}

void RecursiveVisitor::visit( VariableDefinition& node )
{
    node.delimiterToken()->accept( *this );
    node.attributes()->accept( *this );
    node.identifier()->accept( *this );
    node.colonToken()->accept( *this );
    node.variableType()->accept( *this );
}

void RecursiveVisitor::visit( FunctionDefinition& node )
{
    node.delimiterToken()->accept( *this );
    node.attributes()->accept( *this );
    node.functionToken()->accept( *this );
    node.identifier()->accept( *this );
    node.colonToken()->accept( *this );
    node.argumentTypes()->accept( *this );
    node.mapsToken()->accept( *this );
    node.returnType()->accept( *this );
    node.defined()->accept( *this );
    node.initially()->accept( *this );
}

void RecursiveVisitor::visit( DerivedDefinition& node )
{
    node.attributes()->accept( *this );
    node.derivedToken()->accept( *this );
    node.identifier()->accept( *this );
    node.leftBracketToken()->accept( *this );
    node.arguments()->accept( *this );
    node.rightBracketToken()->accept( *this );
    node.mapsToken()->accept( *this );
    node.returnType()->accept( *this );
    node.assignmentToken()->accept( *this );
    node.expression()->accept( *this );
}

void RecursiveVisitor::visit( RuleDefinition& node )
{
    node.attributes()->accept( *this );
    node.ruleToken()->accept( *this );
    node.identifier()->accept( *this );
    node.leftBracketToken()->accept( *this );
    node.arguments()->accept( *this );
    node.rightBracketToken()->accept( *this );
    node.mapsToken()->accept( *this );
    node.returnType()->accept( *this );
    node.assignmentToken()->accept( *this );
    node.rule()->accept( *this );
}

void RecursiveVisitor::visit( EnumeratorDefinition& node )
{
    node.delimiterToken()->accept( *this );
    node.attributes()->accept( *this );
    node.identifier()->accept( *this );
}

void RecursiveVisitor::visit( EnumerationDefinition& node )
{
    node.attributes()->accept( *this );
    node.enumerationToken()->accept( *this );
    node.domainType()->accept( *this );
    node.assignmentToken()->accept( *this );
    node.leftBraceToken()->accept( *this );
    node.enumerators()->accept( *this );
    node.rightBraceToken()->accept( *this );
}

void RecursiveVisitor::visit( UsingDefinition& node )
{
    node.attributes()->accept( *this );
    node.usingToken()->accept( *this );
    node.identifier()->accept( *this );
    node.assignmentToken()->accept( *this );
    node.aliasType()->accept( *this );
}

void RecursiveVisitor::visit( UsingPathDefinition& node )
{
    node.attributes()->accept( *this );
    node.usingToken()->accept( *this );
    node.path()->accept( *this );
    node.doubleColonToken()->accept( *this );
    node.asterixToken()->accept( *this );
}

void RecursiveVisitor::visit( InvariantDefinition& node )
{
    node.attributes()->accept( *this );
    node.invariantToken()->accept( *this );
    node.identifier()->accept( *this );
    node.assignmentToken()->accept( *this );
    node.expression()->accept( *this );
}

void RecursiveVisitor::visit( ImportDefinition& node )
{
    node.attributes()->accept( *this );
    node.importToken()->accept( *this );
    node.path()->accept( *this );
    if( node.asToken()->token() != Grammar::Token::UNRESOLVED )
    {
        node.asToken()->accept( *this );
        node.identifier()->accept( *this );
    }
}

void RecursiveVisitor::visit( DomainDefinition& node )
{
    node.attributes()->accept( *this );
    node.domainToken()->accept( *this );
    node.domainType()->accept( *this );
}

void RecursiveVisitor::visit( StructureDefinition& node )
{
    node.attributes()->accept( *this );
    node.structureToken()->accept( *this );
    node.domainType()->accept( *this );
    node.assignmentToken()->accept( *this );
    node.leftBraceToken()->accept( *this );
    node.functions()->accept( *this );
    node.rightBraceToken()->accept( *this );
}

void RecursiveVisitor::visit( BehaviorDefinition& node )
{
    node.attributes()->accept( *this );
    node.behaviorToken()->accept( *this );
    node.domainType()->accept( *this );
    node.assignmentToken()->accept( *this );
    node.leftBraceToken()->accept( *this );
    node.definitions()->accept( *this );
    node.rightBraceToken()->accept( *this );
}

void RecursiveVisitor::visit( ImplementDefinition& node )
{
    node.attributes()->accept( *this );
    node.implementToken()->accept( *this );
    node.behaviorType()->accept( *this );
    node.forToken()->accept( *this );
    node.domainType()->accept( *this );
    node.assignmentToken()->accept( *this );
    node.leftBraceToken()->accept( *this );
    node.definitions()->accept( *this );
    node.rightBraceToken()->accept( *this );
}

void RecursiveVisitor::visit( BuiltinDefinition& node )
{
    node.attributes()->accept( *this );
    node.builtinToken()->accept( *this );
    node.domainType()->accept( *this );
}

void RecursiveVisitor::visit( Declaration& node )
{
    node.attributes()->accept( *this );
    node.kindToken()->accept( *this );
    node.identifier()->accept( *this );
    node.colonToken()->accept( *this );
    node.argumentTypes()->accept( *this );
    node.mapsToken()->accept( *this );
    node.returnType()->accept( *this );
}

void RecursiveVisitor::visit( UndefLiteral& node )
{
    node.delimiterToken()->accept( *this );
    node.spans()->accept( *this );
}

void RecursiveVisitor::visit( ValueLiteral& node )
{
    node.delimiterToken()->accept( *this );
    node.spans()->accept( *this );
}

void RecursiveVisitor::visit( ReferenceLiteral& node )
{
    node.delimiterToken()->accept( *this );
    node.at()->accept( *this );
    node.identifier()->accept( *this );
}

void RecursiveVisitor::visit( SetLiteral& node )
{
    node.delimiterToken()->accept( *this );
    node.leftBracket()->accept( *this );
    node.expressions()->accept( *this );
    node.rightBracket()->accept( *this );
}

void RecursiveVisitor::visit( ListLiteral& node )
{
    node.delimiterToken()->accept( *this );
    node.leftBracket()->accept( *this );
    node.expressions()->accept( *this );
    node.rightBracket()->accept( *this );
}

void RecursiveVisitor::visit( RangeLiteral& node )
{
    node.delimiterToken()->accept( *this );
    node.leftBracket()->accept( *this );
    node.left()->accept( *this );
    node.dotdot()->accept( *this );
    node.right()->accept( *this );
    node.rightBracket()->accept( *this );
}

void RecursiveVisitor::visit( TupleLiteral& node )
{
    node.delimiterToken()->accept( *this );
    node.leftBracket()->accept( *this );
    node.expressions()->accept( *this );
    node.rightBracket()->accept( *this );
}

void RecursiveVisitor::visit( RecordLiteral& node )
{
    node.delimiterToken()->accept( *this );
    node.leftBracket()->accept( *this );
    node.namedExpressions()->accept( *this );
    node.rightBracket()->accept( *this );
}

void RecursiveVisitor::visit( AbstractExpression& node )
{
    node.delimiterToken()->accept( *this );
}

void RecursiveVisitor::visit( EmbracedExpression& node )
{
    node.delimiterToken()->accept( *this );
    node.leftBraceToken()->accept( *this );
    node.expression()->accept( *this );
    node.rightBraceToken()->accept( *this );
}

void RecursiveVisitor::visit( NamedExpression& node )
{
    node.delimiterToken()->accept( *this );
    node.identifier()->accept( *this );
    node.colonToken()->accept( *this );
    node.expression()->accept( *this );
}

void RecursiveVisitor::visit( MappedExpression& node )
{
    node.delimiterToken()->accept( *this );
    node.leftBracketToken()->accept( *this );
    node.arguments()->accept( *this );
    node.rightBracketToken()->accept( *this );
    node.mapsToken()->accept( *this );
    node.value()->accept( *this );
}

void RecursiveVisitor::visit( DirectCallExpression& node )
{
    node.delimiterToken()->accept( *this );
    node.identifier()->accept( *this );
    node.leftBracketToken()->accept( *this );
    node.arguments()->accept( *this );
    node.rightBracketToken()->accept( *this );
}

void RecursiveVisitor::visit( MethodCallExpression& node )
{
    node.delimiterToken()->accept( *this );
    node.object()->accept( *this );
    node.dotToken()->accept( *this );
    node.methodName()->accept( *this );
    node.leftBracketToken()->accept( *this );
    node.arguments()->accept( *this );
    node.rightBracketToken()->accept( *this );
}

void RecursiveVisitor::visit( LiteralCallExpression& node )
{
    node.delimiterToken()->accept( *this );
    node.object()->accept( *this );
    node.dotToken()->accept( *this );
    node.literal()->accept( *this );
}

void RecursiveVisitor::visit( IndirectCallExpression& node )
{
    node.delimiterToken()->accept( *this );
    node.expression()->accept( *this );
    node.leftBracketToken()->accept( *this );
    node.arguments()->accept( *this );
    node.rightBracketToken()->accept( *this );
}

void RecursiveVisitor::visit( TypeCastingExpression& node )
{
    node.delimiterToken()->accept( *this );
    node.fromExpression()->accept( *this );
    node.asToken()->accept( *this );
    node.asType()->accept( *this );
}

void RecursiveVisitor::visit( UnaryExpression& node )
{
    node.delimiterToken()->accept( *this );
    node.operationToken()->accept( *this );
    node.expression()->accept( *this );
}

void RecursiveVisitor::visit( BinaryExpression& node )
{
    node.delimiterToken()->accept( *this );
    node.left()->accept( *this );
    node.operationToken()->accept( *this );
    node.right()->accept( *this );
}

void RecursiveVisitor::visit( LetExpression& node )
{
    node.delimiterToken()->accept( *this );
    node.letToken()->accept( *this );
    node.variableBindings()->accept( *this );
    node.inToken()->accept( *this );
    node.expression()->accept( *this );
}

void RecursiveVisitor::visit( ConditionalExpression& node )
{
    node.delimiterToken()->accept( *this );
    node.ifToken()->accept( *this );
    node.condition()->accept( *this );
    node.thenToken()->accept( *this );
    node.thenExpression()->accept( *this );
    node.elseToken()->accept( *this );
    node.elseExpression()->accept( *this );
}

void RecursiveVisitor::visit( ChooseExpression& node )
{
    node.delimiterToken()->accept( *this );
    node.chooseToken()->accept( *this );
    node.variableSelections()->accept( *this );
    node.doToken()->accept( *this );
    node.expression()->accept( *this );
}

void RecursiveVisitor::visit( UniversalQuantifierExpression& node )
{
    node.delimiterToken()->accept( *this );
    node.quantifierToken()->accept( *this );
    node.predicateVariables()->accept( *this );
    node.inToken()->accept( *this );
    node.universe()->accept( *this );
    node.doToken()->accept( *this );
    node.proposition()->accept( *this );
}

void RecursiveVisitor::visit( ExistentialQuantifierExpression& node )
{
    node.delimiterToken()->accept( *this );
    node.quantifierToken()->accept( *this );
    node.predicateVariables()->accept( *this );
    node.inToken()->accept( *this );
    node.universe()->accept( *this );
    node.doToken()->accept( *this );
    node.proposition()->accept( *this );
}

void RecursiveVisitor::visit( CardinalityExpression& node )
{
    node.delimiterToken()->accept( *this );
    node.leftVerticalBarToken()->accept( *this );
    node.expression()->accept( *this );
    node.rightVerticalBarToken()->accept( *this );
}

void RecursiveVisitor::visit( MatchExpression& node )
{
    node.matchToken()->accept( *this );
    node.scrutinee()->accept( *this );
    node.withToken()->accept( *this );
    node.leftBraceToken()->accept( *this );
    node.matchArms()->accept( *this );
    node.rightBraceToken()->accept( *this );
}

void RecursiveVisitor::visit( MatchArm& node )
{
    node.delimiterToken()->accept( *this );
    node.pattern()->accept( *this );
    node.arrowToken()->accept( *this );
    node.expression()->accept( *this );
}

void RecursiveVisitor::visit( SkipRule& node )
{
    node.skipToken()->accept( *this );
}

void RecursiveVisitor::visit( ConditionalRule& node )
{
    node.ifToken()->accept( *this );
    node.condition()->accept( *this );
    node.thenToken()->accept( *this );
    node.thenRule()->accept( *this );
    node.elseToken()->accept( *this );
    node.elseRule()->accept( *this );
}

void RecursiveVisitor::visit( DefaultCase& node )
{
    node.labelToken()->accept( *this );
    node.colonToken()->accept( *this );
    node.rule()->accept( *this );
}

void RecursiveVisitor::visit( ExpressionCase& node )
{
    node.expression()->accept( *this );
    node.colonToken()->accept( *this );
    node.rule()->accept( *this );
}

void RecursiveVisitor::visit( CaseRule& node )
{
    node.caseToken()->accept( *this );
    node.expression()->accept( *this );
    node.ofToken()->accept( *this );
    node.leftBraceToken()->accept( *this );
    node.cases()->accept( *this );
    node.rightBraceToken()->accept( *this );
}

void RecursiveVisitor::visit( LetRule& node )
{
    node.letToken()->accept( *this );
    node.variableBindings()->accept( *this );
    node.inToken()->accept( *this );
    node.rule()->accept( *this );
}

void RecursiveVisitor::visit( LocalRule& node )
{
    node.localToken()->accept( *this );
    node.localFunctions()->accept( *this );
    node.inToken()->accept( *this );
    node.rule()->accept( *this );
}

void RecursiveVisitor::visit( ForallRule& node )
{
    node.forallToken()->accept( *this );
    node.variables()->accept( *this );
    node.inToken()->accept( *this );
    node.universe()->accept( *this );
    if( node.withToken()->token() != Grammar::Token::UNRESOLVED )
    {
        node.withToken()->accept( *this );
        node.condition()->accept( *this );
    }
    node.doToken()->accept( *this );
    node.rule()->accept( *this );
}

void RecursiveVisitor::visit( ChooseRule& node )
{
    node.chooseToken()->accept( *this );
    node.variableSelections()->accept( *this );
    node.doToken()->accept( *this );
    node.rule()->accept( *this );
}

void RecursiveVisitor::visit( IterateRule& node )
{
    node.iterateToken()->accept( *this );
    node.rule()->accept( *this );
}

void RecursiveVisitor::visit( BlockRule& node )
{
    node.leftBraceToken()->accept( *this );
    node.rules()->accept( *this );
    node.rightBraceToken()->accept( *this );
}

void RecursiveVisitor::visit( SequenceRule& node )
{
    node.leftBraceToken()->accept( *this );
    node.rules()->accept( *this );
    node.rightBraceToken()->accept( *this );
}

void RecursiveVisitor::visit( UpdateRule& node )
{
    node.function()->accept( *this );
    node.updateToken()->accept( *this );
    node.expression()->accept( *this );
}

void RecursiveVisitor::visit( CallRule& node )
{
    node.call()->accept( *this );
}

void RecursiveVisitor::visit( WhileRule& node )
{
    node.whileToken()->accept( *this );
    node.condition()->accept( *this );
    node.doToken()->accept( *this );
    node.rule()->accept( *this );
}

void RecursiveVisitor::visit( UnresolvedType& node )
{
    node.delimiterToken()->accept( *this );
    node.name()->accept( *this );
}

void RecursiveVisitor::visit( BasicType& node )
{
    node.delimiterToken()->accept( *this );
    node.name()->accept( *this );
}

void RecursiveVisitor::visit( TupleType& node )
{
    node.delimiterToken()->accept( *this );
    node.leftBraceToken()->accept( *this );
    node.subTypes()->accept( *this );
    node.rightBraceToken()->accept( *this );
}

void RecursiveVisitor::visit( RecordType& node )
{
    node.delimiterToken()->accept( *this );
    node.leftBraceToken()->accept( *this );
    node.namedSubTypes()->accept( *this );
    node.rightBraceToken()->accept( *this );
}

void RecursiveVisitor::visit( TemplateType& node )
{
    node.delimiterToken()->accept( *this );
    node.name()->accept( *this );
    node.leftBraceToken()->accept( *this );
    node.subTypes()->accept( *this );
    node.rightBraceToken()->accept( *this );
}

void RecursiveVisitor::visit( RelationType& node )
{
    node.delimiterToken()->accept( *this );
    node.name()->accept( *this );
    node.leftBraceToken()->accept( *this );
    node.argumentTypes()->accept( *this );
    node.mapsToken()->accept( *this );
    node.returnType()->accept( *this );
    node.rightBraceToken()->accept( *this );
}

void RecursiveVisitor::visit( FixedSizedType& node )
{
    node.delimiterToken()->accept( *this );
    node.name()->accept( *this );
    node.markToken()->accept( *this );
    node.size()->accept( *this );
}

void RecursiveVisitor::visit( MappingType& node )
{
    node.delimiterToken()->accept( *this );
    node.argumentTypes()->accept( *this );
    node.mapsToken()->accept( *this );
    node.returnType()->accept( *this );
}

void RecursiveVisitor::visit( VaradicType& node )
{
    node.delimiterToken()->accept( *this );
    node.dotdotdotToken()->accept( *this );
    node.name()->accept( *this );
}

void RecursiveVisitor::visit( BasicAttribute& node )
{
    node.leftBrace()->accept( *this );
    node.identifier()->accept( *this );
    node.rightBrace()->accept( *this );
}

void RecursiveVisitor::visit( SymbolAttribute& node )
{
    node.leftBrace()->accept( *this );
    node.identifier()->accept( *this );
    node.symbol()->accept( *this );
    node.rightBrace()->accept( *this );
}

void RecursiveVisitor::visit( ExpressionAttribute& node )
{
    node.leftBrace()->accept( *this );
    node.identifier()->accept( *this );
    node.expression()->accept( *this );
    node.rightBrace()->accept( *this );
}

void RecursiveVisitor::visit( Defined& node )
{
    node.definedToken()->accept( *this );
    node.leftBraceToken()->accept( *this );
    node.expression()->accept( *this );
    node.rightBraceToken()->accept( *this );
}

void RecursiveVisitor::visit( Initially& node )
{
    if( node.expression() )
    {
        node.equalToken()->accept( *this );
        node.expression()->accept( *this );
    }
}

void RecursiveVisitor::visit( Identifier& node )
{
    node.doubleColon()->accept( *this );
    node.spans()->accept( *this );
}

void RecursiveVisitor::visit( IdentifierPath& node )
{
    node.identifiers()->accept( *this );
}

void RecursiveVisitor::visit( VariableBinding& node )
{
    node.delimiterToken()->accept( *this );
    node.variable()->accept( *this );
    node.equalToken()->accept( *this );
    node.expression()->accept( *this );
}

void RecursiveVisitor::visit( VariableSelection& node )
{
    node.delimiterToken()->accept( *this );
    node.variable()->accept( *this );
    node.inToken()->accept( *this );
    node.universe()->accept( *this );
    node.withToken()->accept( *this );
    node.condition()->accept( *this );
}

void RecursiveVisitor::visit( Token& node )
{
    node.spans()->accept( *this );
}

void RecursiveVisitor::visit( Span& node )
{
}

//
//
// EmptyVisitor
//

void EmptyVisitor::visit( Root& )
{
}

void EmptyVisitor::visit( HeaderDefinition& )
{
}

void EmptyVisitor::visit( InitDefinition& )
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

void EmptyVisitor::visit( AbstractExpression& )
{
}

void EmptyVisitor::visit( EmbracedExpression& )
{
}

void EmptyVisitor::visit( NamedExpression& )
{
}

void EmptyVisitor::visit( MappedExpression& )
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

void EmptyVisitor::visit( MatchExpression& )
{
}

void EmptyVisitor::visit( MatchArm& )
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

void EmptyVisitor::visit( MappingType& )
{
}

void EmptyVisitor::visit( VaradicType& )
{
}

void EmptyVisitor::visit( RelationType& )
{
}

void EmptyVisitor::visit( BasicAttribute& )
{
}

void EmptyVisitor::visit( SymbolAttribute& )
{
}

void EmptyVisitor::visit( ExpressionAttribute& )
{
}

void EmptyVisitor::visit( Defined& )
{
}

void EmptyVisitor::visit( Initially& )
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

void EmptyVisitor::visit( VariableSelection& )
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
