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

%skeleton "lalr1.cc"
%require "3.2"
//%debug

%defines
%define api.namespace {libcasm_fe}
%define api.parser.class {Parser}
%define api.token.constructor
%define api.value.type variant
%define api.location.type {libstdhl::SourceLocation}

%define parse.assert
%define parse.trace
%define parse.error verbose

%locations

%code requires
{
    namespace libcasm_fe
    {
        class Lexer;
        class Logger;
    }

    #include <libcasm-fe/Specification>
    #include <libcasm-fe/cst/Definition>
    #include <libcasm-fe/cst/Declaration>
    #include <libcasm-fe/cst/Literal>
    #include <libcasm-fe/Exception>
    #include <libcasm-fe/TypeInfo>
    #include <libcasm-fe/Logger>

    #include <libstdhl/SourceLocation>

    using namespace libcasm_fe;
    using namespace CST;

    #define YY_NULLPTR nullptr
}

%parse-param { Logger& m_log }
%parse-param { Lexer& m_lexer }
%parse-param { Specification& m_specification }

%code
{
    #include "../../src/Lexer.h"

    #include <libstdhl/Type>

    #undef yylex
    #define yylex m_lexer.nextToken

    static BasicType::Ptr createVoidType( libstdhl::SourceLocation& sourceLocation )
    {
        const auto name = CST::make< Identifier >( sourceLocation, TypeInfo::TYPE_NAME_VOID );
        const auto path = CST::make< IdentifierPath >( sourceLocation, name );
        const auto node = CST::make< BasicType >( sourceLocation, path );
        return node;
    }
}


%token
END       0 "end of file"
{{grammartoken}}

%token <ValueLiteral::Ptr> BINARY      "binary"
%token <ValueLiteral::Ptr> HEXADECIMAL "hexadecimal"
%token <ValueLiteral::Ptr> INTEGER     "integer"
%token <ValueLiteral::Ptr> RATIONAL    "rational"
%token <ValueLiteral::Ptr> DECIMAL     "decimal"
%token <ValueLiteral::Ptr> STRING      "string"
%token <Identifier::Ptr>   IDENTIFIER  "identifier"

%type <Specification::Ptr> Specification

%type <Identifier::Ptr> Identifier
%type <IdentifierPath::Ptr> IdentifierPath

// definitions
%type <Definition::Ptr> Definition AttributedDefinition
%type <Definitions::Ptr> Definitions
%type <HeaderDefinition::Ptr> Header
%type <InitDefinition::Ptr> InitDefinition
%type <VariableDefinition::Ptr> Variable TypedVariable AttributedVariable TypedAttributedVariable
%type <VariableDefinitions::Ptr> TypedVariables
%type <DomainDefinition::Ptr> DomainDefinition
%type <BuiltinDefinition::Ptr> BuiltinDefinition
%type <FunctionDefinition::Ptr> FunctionDefinition
%type <DerivedDefinition::Ptr> DerivedDefinition
%type <RuleDefinition::Ptr> RuleDefinition
%type <EnumeratorDefinition::Ptr> EnumeratorDefinition
%type <Enumerators::Ptr> Enumerators
%type <EnumerationDefinition::Ptr> EnumerationDefinition
%type <UsingDefinition::Ptr> UsingDefinition
%type <UsingPathDefinition::Ptr> UsingPathDefinition
%type <InvariantDefinition::Ptr> InvariantDefinition
%type <ImportDefinition::Ptr> ImportDefinition
%type <StructureDefinition::Ptr> StructureDefinition
%type <FunctionDefinitions::Ptr> StructureDefinitionList
%type <FunctionDefinition::Ptr> StructureDefinitionElement
%type <BehaviorDefinition::Ptr> BehaviorDefinition
%type <Definitions::Ptr> BehaviorDefinitionList
%type <Definition::Ptr> BehaviorDefinitionElement
%type <ImplementDefinition::Ptr> ImplementDefinition
%type <Definitions::Ptr> ImplementDefinitionList
%type <Definition::Ptr> ImplementDefinitionElement ImplementDefinitionAttributedElement
%type <Declaration::Ptr> Declaration

// literals
%type <Literal::Ptr> Literal
%type <UndefLiteral::Ptr> UndefinedLiteral
%type <ValueLiteral::Ptr> BooleanLiteral StringLiteral BinaryLiteral IntegerLiteral DecimalLiteral RationalLiteral
%type <ReferenceLiteral::Ptr> ReferenceLiteral
// %type <SetLiteral::Ptr> SetLiteral
%type <ListLiteral::Ptr> ListLiteral
%type <RangeLiteral::Ptr> RangeLiteral
%type <TupleLiteral::Ptr> TupleLiteral
%type <RecordLiteral::Ptr> RecordLiteral

// expressions
%type <Expression::Ptr> Term Expression OperatorExpression
%type <Expressions::Ptr> Terms
%type <NamedExpression::Ptr> Assignment
%type <NamedExpressions::Ptr> Assignments
%type <MappedExpression::Ptr> MappedExpression
%type <MappedExpressions::Ptr> MappedExpressions
%type <CallExpression::Ptr> CallExpression
%type <DirectCallExpression::Ptr> DirectCallExpression
%type <MethodCallExpression::Ptr> MethodCallExpression
%type <LiteralCallExpression::Ptr> LiteralCallExpression
%type <IndirectCallExpression::Ptr> IndirectCallExpression
%type <TypeCastingExpression::Ptr> TypeCastingExpression
%type <LetExpression::Ptr> LetExpression
%type <ConditionalExpression::Ptr> ConditionalExpression
%type <ChooseExpression::Ptr> ChooseExpression
%type <UniversalQuantifierExpression::Ptr> UniversalQuantifierExpression
%type <ExistentialQuantifierExpression::Ptr> ExistentialQuantifierExpression
%type <CardinalityExpression::Ptr> CardinalityExpression

// rules
%type <Rule::Ptr> Rule
%type <Rules::Ptr> Rules
%type <SkipRule::Ptr> SkipRule
%type <ConditionalRule::Ptr> ConditionalRule
%type <CaseRule::Ptr> CaseRule
%type <LetRule::Ptr> LetRule
%type <LocalRule::Ptr> LocalRule
%type <ForallRule::Ptr> ForallRule
%type <ChooseRule::Ptr> ChooseRule
%type <IterateRule::Ptr> IterateRule
%type <BlockRule::Ptr> BlockRule
%type <SequenceRule::Ptr> SequenceRule
%type <UpdateRule::Ptr> UpdateRule
%type <CallRule::Ptr> CallRule
%type <WhileRule::Ptr> WhileRule

// types
%type <libcasm_fe::CST::Type::Ptr> Type
%type <Types::Ptr> Types
%type <BasicType::Ptr> BasicType
%type <TupleType::Ptr> TupleType
%type <RecordType::Ptr> RecordType
%type <TemplateType::Ptr> TemplateType
%type <RelationType::Ptr> RelationType
%type <FixedSizedType::Ptr> FixedSizedType
%type <MappingType::Ptr> MappingType
%type <VaradicType::Ptr> VaradicType

// attributes
%type <Attribute::Ptr> Attribute
%type <Attributes::Ptr> Attributes
%type <BasicAttribute::Ptr> BasicAttribute
%type <SymbolAttribute::Ptr> SymbolAttribute
%type <ExpressionAttribute::Ptr> ExpressionAttribute

// other
%type <Case::Ptr> CaseLabel
%type <Cases::Ptr> CaseLabels
%type <Initially::Ptr> MaybeInitially
%type <Defined::Ptr> MaybeDefined
%type <Types::Ptr> FunctionParameters MaybeFunctionParameters
%type <VariableDefinitions::Ptr> Parameters AttributedVariables
%type <VariableDefinitions::Ptr> MethodParameters
%type <VariableBinding::Ptr> VariableBinding
%type <VariableBindings::Ptr> VariableBindings
%type <FunctionDefinition::Ptr> LocalFunctionDefinition AttributedLocalFunctionDefinition
%type <FunctionDefinitions::Ptr> LocalFunctionDefinitions


%start Specification

// prefer basic types over the other types
%precedence BASIC_TYPE

%precedence IN
%precedence DO

%precedence THEN
%precedence ELSE

%precedence HOLDS WITH

%precedence CALL
%precedence UPDATE

%left IMPLIES ARROW
%left OR
%left XOR
%left AND

%left EQUAL NEQUAL
%left GREATEREQ LESSEQ GREATER LESSER

%left PLUS MINUS
%left PERCENT SLASH ASTERIX
%left CARET

%precedence DOT
%precedence UPLUS UMINUS
%precedence NOT

// prefer calls with args (starts with LPAREN) over calls without args
%precedence CALL_WITHOUT_ARGS
%precedence LPAREN

// prefer fixed sized types over composed types (start with LESSER) over basic types
%precedence MARK

%%


Specification
: Header Definitions
  {
      const auto& cst = CST::make< CST::Root >(
          @$, $1, $2, m_lexer.fetchSpansAndReset() );
      m_specification.setCst( cst );
  }
;


Header
: Attributes CASM
  {
      auto definition = CST::make< HeaderDefinition >( @$, $2 );
      definition->setAttributes( $1 );
      $$ = definition;
  }
| CASM
  {
      $$ = CST::make< HeaderDefinition >( @$, $1 );
  }
;


Definitions
: Definitions AttributedDefinition
  {
      auto definitions = $1;
      definitions->add( $2 );
      $$ = definitions;
  }
| AttributedDefinition
  {
      auto definitions = CST::make< Definitions >( @$ );
      definitions->add( $1 );
      $$ = definitions;
  }
;


AttributedDefinition
: Attributes Definition
  {
      auto definition = $2;
      definition->setAttributes( $1 );
      $$ = definition;
  }
| Definition
  {
      $$ = $1;
  }
| error // error recovery
  {
      $$ = nullptr;
  }
;


Definition
: InitDefinition
  {
      $$ = $1;
  }
| EnumerationDefinition
  {
      $$ = $1;
  }
| DerivedDefinition
  {
      $$ = $1;
  }
| RuleDefinition
  {
      $$ = $1;
  }
| FunctionDefinition
  {
      $$ = $1;
  }
| UsingDefinition
  {
      $$ = $1;
  }
| UsingPathDefinition
  {
      $$ = $1;
  }
| InvariantDefinition
  {
      $$ = $1;
  }
| ImportDefinition
  {
      $$ = $1;
  }
| StructureDefinition
  {
      $$ = $1;
  }
| BehaviorDefinition
  {
      $$ = $1;
  }
| ImplementDefinition
  {
      $$ = $1;
  }
| DomainDefinition
  {
      $$ = $1;
  }
| BuiltinDefinition
  {
      $$ = $1;
  }
;


InitDefinition
: INIT IdentifierPath
  {
      $$ = CST::make< InitDefinition >( @$, $1, $2 );
  }
| INIT LCURPAREN MappedExpressions RCURPAREN
  {
      $$ = CST::make< InitDefinition >( @$, $1, $2, $3, $4 );
  }
;


EnumerationDefinition
: ENUMERATION Identifier EQUAL LCURPAREN Enumerators RCURPAREN
  {
      $$ = CST::make< EnumerationDefinition >( @$, $1, $2, $3, $4, $5, $6 );
  }
;


DerivedDefinition
: DERIVED Identifier MAPS Type EQUAL Term
  {
      const auto params = CST::make< NodeList< VariableDefinition > >( @$ );
      $$ = CST::make< DerivedDefinition >( @$, $1, $2, params, $3, $4, $5, $6 );
  }
| DERIVED Identifier LPAREN Parameters RPAREN MAPS Type EQUAL Term
  {
      $$ = CST::make< DerivedDefinition >( @$, $1, $2, $4, $6, $7, $8, $9 );
      $$->setLeftBracketToken( $3 );
      $$->setRightBracketToken( $5 );
  }
| DERIVED Identifier LPAREN MethodParameters RPAREN MAPS Type EQUAL Term
  {
      $$ = CST::make< DerivedDefinition >( @$, $1, $2, $4, $6, $7, $8, $9 );
      $$->setLeftBracketToken( $3 );
      $$->setRightBracketToken( $5 );
  }
| DERIVED Identifier LPAREN error RPAREN MAPS Type EQUAL Term // error recovery
  {
      $$ = nullptr;
  }
;


RuleDefinition
: RULE Identifier EQUAL Rule
  {
      const auto params = CST::make< NodeList< VariableDefinition > >( @$ );
      const auto vType = createVoidType( @$ );
      $$ = CST::make< RuleDefinition >( @$, $1, $2, params, Token::unresolved(), vType, $3, $4 );
  }
| RULE Identifier MAPS Type EQUAL Rule
  {
      const auto params = CST::make< NodeList< VariableDefinition > >( @$ );
      $$ = CST::make< RuleDefinition >( @$, $1, $2, params, $3, $4, $5, $6 );
  }
| RULE Identifier LPAREN Parameters RPAREN EQUAL Rule
  {
      const auto vType = createVoidType( @$ );
      $$ = CST::make< RuleDefinition >( @$, $1, $2, $4, Token::unresolved(), vType, $6, $7 );
      $$->setLeftBracketToken( $3 );
      $$->setRightBracketToken( $5 );
  }
| RULE Identifier LPAREN Parameters RPAREN MAPS Type EQUAL Rule
  {
      $$ = CST::make< RuleDefinition >( @$, $1, $2, $4, $6, $7, $8, $9 );
      $$->setLeftBracketToken( $3 );
      $$->setRightBracketToken( $5 );
  }
| RULE Identifier LPAREN MethodParameters RPAREN EQUAL Rule
  {
      const auto vType = createVoidType( @$ );
      $$ = CST::make< RuleDefinition >( @$, $1, $2, $4, Token::unresolved(), vType, $6, $7 );
      $$->setLeftBracketToken( $3 );
      $$->setRightBracketToken( $5 );
  }
| RULE Identifier LPAREN MethodParameters RPAREN MAPS Type EQUAL Rule
  {
      $$ = CST::make< RuleDefinition >( @$, $1, $2, $4, $6, $7, $8, $9 );
      $$->setLeftBracketToken( $3 );
      $$->setRightBracketToken( $5 );
  }
| RULE Identifier LPAREN error RPAREN EQUAL Rule // error recovery
  {
      $$ = nullptr;
  }
| RULE Identifier LPAREN error RPAREN MAPS Type EQUAL Rule // error recovery
  {
      $$ = nullptr;
  }
;


FunctionDefinition
: FUNCTION Identifier COLON MaybeFunctionParameters MAPS Type MaybeDefined MaybeInitially
  {
      $$ = CST::make< FunctionDefinition >( @$, $1, $2, $3, $4, $5, $6, $7, $8 );
  }
;


EnumeratorDefinition
: Identifier
  {
      $$ = CST::make< EnumeratorDefinition >( @$, $1 );
  }
| Attributes Identifier
  {
      auto enumerator = CST::make< EnumeratorDefinition >( @$, $2 );
      enumerator->setAttributes( $1 );
      $$ = enumerator;
  }
| error // error recovery
  {
      $$ = nullptr;
  }
;


Enumerators
: Enumerators COMMA EnumeratorDefinition
  {
      auto enumerators = $1;
      $3->setDelimiterToken( $2 );
      enumerators->add( $3 );
      $$ = enumerators;
  }
| EnumeratorDefinition
  {
      auto enumerators = CST::make< Enumerators >( @$ );
      enumerators->add( $1 );
      $$ = enumerators;
  }
;


UsingDefinition
: USING Identifier EQUAL Type
  {
      $$ = CST::make< UsingDefinition >( @$, $1, $2, $3, $4 );
  }
;


UsingPathDefinition
: USING IdentifierPath
  {
      $$ = CST::make< UsingPathDefinition >( @$, $1, $2 );
  }
| USING IdentifierPath DOUBLECOLON ASTERIX
  {
      $$ = CST::make< UsingPathDefinition >( @$, $1, $2, $3, $4 );
  }
;


InvariantDefinition
: INVARIANT Identifier EQUAL Term
  {
      $$ = CST::make< InvariantDefinition >( @$, $1, $2, $3, $4 );
  }
;


ImportDefinition
: IMPORT IdentifierPath
  {
      $$ = CST::make< ImportDefinition >( @$, $1, $2 );
  }
| IMPORT IdentifierPath AS Identifier
  {
      $$ = CST::make< ImportDefinition >( @$, $1, $2, $3, $4 );
  }
;

//
//
// StructureDefinition
//

StructureDefinition
: STRUCTURE Identifier EQUAL LCURPAREN StructureDefinitionList RCURPAREN
  {
      $$ = CST::make< StructureDefinition >( @$, $1, $2, $3, $4, $5, $6 );
  }
;

StructureDefinitionList
: StructureDefinitionList StructureDefinitionElement
  {
      auto functions = $1;
      functions->add( $2 );
      $$ = functions;
  }
| StructureDefinitionElement
  {
      auto functions = CST::make< FunctionDefinitions >( @$ );
      functions->add( $1 );
      $$ = functions;
  }
;

StructureDefinitionElement
: Attributes FunctionDefinition
  {
      auto definition = $2;
      definition->setAttributes( $1 );
      $$ = definition;
  }
| FunctionDefinition
  {
      $$ = $1;
  }
;

//
//
// BehaviorDefinition
//

BehaviorDefinition
: BEHAVIOR Type EQUAL LCURPAREN BehaviorDefinitionList RCURPAREN
  {
      $$ = CST::make< BehaviorDefinition >( @$, $1, $2, $3, $4, $5, $6 );
  }
;


BehaviorDefinitionElement
: Attributes Declaration
  {
      auto definition = $2;
      definition->setAttributes( $1 );
      $$ = definition;
  }
| Declaration
  {
      $$ = $1;
  }
| Attributes DerivedDefinition
  {
      auto definition = $2;
      definition->setAttributes( $1 );
      $$ = definition;
  }
| DerivedDefinition
  {
      $$ = $1;
  }
| Attributes RuleDefinition
  {
      auto definition = $2;
      definition->setAttributes( $1 );
      $$ = definition;
  }
| RuleDefinition
  {
      $$ = $1;
  }
;

BehaviorDefinitionList
: BehaviorDefinitionList BehaviorDefinitionElement
  {
      auto definitions = $1;
      definitions->add( $2 );
      $$ = definitions;
  }
| BehaviorDefinitionElement
  {
      auto definitions = CST::make< Definitions >( @$ );
      definitions->add( $1 );
      $$ = definitions;
  }
;

//
//
// ImplementDefinition
//

ImplementDefinition
: IMPLEMENT Type EQUAL LCURPAREN ImplementDefinitionList RCURPAREN
  {
      $$ = CST::make< ImplementDefinition >( @$, $1, $2, $3, $4, $5, $6 );
  }
| IMPLEMENT Type FOR Type EQUAL LCURPAREN ImplementDefinitionList RCURPAREN
  {
      $$ = CST::make< ImplementDefinition >( @$, $1, $2, $3, $4, $5, $6, $7, $8 );
  }
;

ImplementDefinitionList
: ImplementDefinitionList ImplementDefinitionElement
  {
      auto definitions = $1;
      definitions->add( $2 );
      $$ = definitions;
  }
| ImplementDefinitionElement
  {
      auto definitions = CST::make< Definitions >( @$ );
      definitions->add( $1 );
      $$ = definitions;
  }
;

ImplementDefinitionElement
: Attributes ImplementDefinitionAttributedElement
  {
      const auto& definition = $2;
      definition->setAttributes( $1 );
      $$ = definition;
  }
| ImplementDefinitionAttributedElement
  {
      $$ = $1;
  }
;

ImplementDefinitionAttributedElement
: DerivedDefinition
  {
      $$ = $1;
  }
| RuleDefinition
  {
      $$ = $1;
  }
;

//
//
// DomainDefinition
//

DomainDefinition
: DOMAIN Type
  {
      $$ = CST::make< DomainDefinition >( @$, $1, $2 );
  }
;

//
//
// BuiltinDefinition
//

BuiltinDefinition
: BUILTIN RelationType
  {
      $$ = CST::make< BuiltinDefinition >( @$, $1, $2 );
  }
;

//
//
// Declaration
//

Declaration
: DERIVED Identifier COLON MaybeFunctionParameters MAPS Type
  {
      $$ = CST::make< Declaration >( @$, $1, $2, $3, $4, $5, $6 );
  }
| RULE Identifier COLON MaybeFunctionParameters MAPS Type
  {
      $$ = CST::make< Declaration >( @$, $1, $2, $3, $4, $5, $6 );
  }
;

//
//
// Rules
//

Rules
: Rules Rule
  {
      auto rules = $1;
      rules->add( $2 );
      $$ = rules;
  }
| Rule
  {
      auto rules = CST::make< Rules >( @$ );
      rules->add( $1 );
      $$ = rules;
  }
;


Rule
: SkipRule
  {
      $$ = $1;
  }
| ConditionalRule
  {
      $$ = $1;
  }
| CaseRule
  {
      $$ = $1;
  }
| LetRule
  {
      $$ = $1;
  }
| LocalRule
  {
      $$ = $1;
  }
| ForallRule
  {
      $$ = $1;
  }
| ChooseRule
  {
      $$ = $1;
  }
| IterateRule
  {
      $$ = $1;
  }
| BlockRule
  {
      $$ = $1;
  }
| SequenceRule
  {
      $$ = $1;
  }
| UpdateRule
  {
      $$ = $1;
  }
| CallRule
  {
      $$ = $1;
  }
| WhileRule
  {
      $$ = $1;
  }
;


SkipRule
: SKIP
  {
      $$ = CST::make< SkipRule >( @$, $1 );
  }
;


ConditionalRule
: IF Term THEN Rule
  {
      $$ = CST::make< ConditionalRule >( @$, $1, $2, $3, $4 );
  }
| IF Term THEN Rule ELSE Rule
  {
      $$ = CST::make< ConditionalRule >( @$, $1, $2, $3, $4, $5, $6 );
  }
;


CaseRule
: CASE Term OF LCURPAREN CaseLabels RCURPAREN
  {
      $$ = CST::make< CaseRule >( @$, $1, $2, $3, $4, $5, $6 );
  }
| CASE Term OF LCURPAREN error RCURPAREN // error recovery
  {
      $$ = nullptr;
  }
;


CaseLabels
: CaseLabels CaseLabel
  {
      auto cases = $1;
      cases->add( $2 );
      $$ = cases;
  }
| CaseLabel
  {
      auto cases = CST::make< Cases >( @$ );
      cases->add( $1 );
      $$ = cases;
  }
;


CaseLabel
: DEFAULT COLON Rule
  {
      $$ = CST::make< DefaultCase >( @$, $1, $2, $3 );
  }
| UNDERLINE COLON Rule
  {
      $$ = CST::make< DefaultCase >( @$, $1, $2, $3 );
  }
| Term COLON Rule
  {
      $$ = CST::make< ExpressionCase >( @$, $1, $2, $3 );
  }
;


LetRule
: LET VariableBindings IN Rule
  {
      $$ = CST::make< LetRule >( @$, $1, $2, $3, $4 );
  }
;


LocalRule
: LOCAL LocalFunctionDefinitions IN Rule
  {
      $$ = CST::make< LocalRule >( @$, $1, $2, $3, $4 );
  }
;


ForallRule
: FORALL AttributedVariables IN Term DO Rule
  {
      $$ = CST::make< ForallRule >( @$, $1, $2, $3, $4, $5, $6 );
  }
| FORALL AttributedVariables IN Term WITH Term DO Rule
  {
      $$ = CST::make< ForallRule >( @$, $1, $2, $3, $4, $5, $6, $7, $8 );
  }
;


ChooseRule
: CHOOSE AttributedVariables IN Term DO Rule
  {
      $$ = CST::make< ChooseRule >( @$, $1, $2, $3, $4, $5, $6 );
  }
;


IterateRule
: ITERATE Rule
  {
      $$ = CST::make< IterateRule >( @$, $1, $2 );
  }
;


BlockRule
: LCURPAREN Rules RCURPAREN
  {
      $$ = CST::make< BlockRule >( @$, $1, $2, $3 );
  }
| PAR Rules ENDPAR
  {
      $$ = CST::make< BlockRule >( @$, $1, $2, $3 );
  }
| LCURPAREN error RCURPAREN // error recovery
  {
      $$ = nullptr;
      yyerrok;
  }
| PAR error ENDPAR // error recovery
  {
      $$ = nullptr;
      yyerrok;
  }
;


SequenceRule
: SEQ_BRACKET Rules ENDSEQ_BRACKET
  {
      $$ = CST::make< SequenceRule >( @$, $1, $2, $3 );
  }
| SEQ Rules ENDSEQ
  {
      $$ = CST::make< SequenceRule >( @$, $1, $2, $3 );
  }
| SEQ_BRACKET error ENDSEQ_BRACKET // error recovery
  {
      $$ = nullptr;
      yyerrok;
  }
| SEQ error ENDSEQ // error recovery
  {
      $$ = nullptr;
      yyerrok;
  }
;


UpdateRule
: DirectCallExpression UPDATE Term
  {
      $$ = CST::make< UpdateRule >( @$, $1, $2, $3 );
  }
| MethodCallExpression UPDATE Term
  {
      $$ = CST::make< UpdateRule >( @$, $1, $2, $3 );
  }
;


CallRule
: CallExpression %prec CALL
  {
      $$ = CST::make< CallRule >( @$, $1 );
  }
;


WhileRule
: WHILE Term DO Rule
  {
      $$ = CST::make< WhileRule >( @$, $1, $2, $3, $4 );
  }
;


//
// Terms
//

Terms
: Terms COMMA Term
  {
      auto expressions = $1;
      $3->setDelimiterToken( $2 );
      expressions->add( $3 );
      $$ = expressions;
  }
| Term
  {
      const auto expressions = CST::make< Expressions >( @$ );
      expressions->add( $1 );
      $$ = expressions;
  }
;


Term
: Expression
  {
     $$ = $1;
  }
| TypeCastingExpression
  {
      $$ = $1;
  }
| OperatorExpression
  {
      $$ = $1;
  }
| LetExpression
  {
      $$ = $1;
  }
| ConditionalExpression
  {
      $$ = $1;
  }
| ChooseExpression
  {
      $$ = $1;
  }
| UniversalQuantifierExpression
  {
      $$ = $1;
  }
| ExistentialQuantifierExpression
  {
      $$ = $1;
  }
| CardinalityExpression
  {
      $$ = $1;
  }
;


Expression
: LPAREN Term RPAREN
  {
      $$ = CST::make< CST::EmbracedExpression >( @$, $1, $2, $3 );
  }
| LPAREN error RPAREN // error recovery
  {
      $$ = nullptr;
  }
| CallExpression %prec CALL
  {
      $$ = $1;
  }
| LiteralCallExpression
  {
      $$ = $1;
  }
| Literal
  {
      $$ = $1;
  }
| PLUS Expression %prec UPLUS
  {
      $$ = CST::make< UnaryExpression >( @$, $1, $2 );
  }
| MINUS Expression %prec UMINUS
  {
      $$ = CST::make< UnaryExpression >( @$, $1, $2 );
  }
;


//
// Operator Expression
//

OperatorExpression
: Term PLUS Term
  {
      $$ = CST::make< BinaryExpression >( @$, $1, $2, $3 );
  }
| Term MINUS Term
  {
      $$ = CST::make< BinaryExpression >( @$, $1, $2, $3 );
  }
| Term ASTERIX Term
  {
      $$ = CST::make< BinaryExpression >( @$, $1, $2, $3 );
  }
| Term SLASH Term
  {
      $$ = CST::make< BinaryExpression >( @$, $1, $2, $3 );
  }
| Term PERCENT Term
  {
      $$ = CST::make< BinaryExpression >( @$, $1, $2, $3 );
  }
| Term CARET Term
  {
      $$ = CST::make< BinaryExpression >( @$, $1, $2, $3 );
  }
| Term NEQUAL Term
  {
      $$ = CST::make< BinaryExpression >( @$, $1, $2, $3 );
  }
| Term EQUAL Term
  {
      $$ = CST::make< BinaryExpression >( @$, $1, $2, $3 );
  }
| Term LESSER Term
  {
      $$ = CST::make< BinaryExpression >( @$, $1, $2, $3 );
  }
| Term GREATER Term
  {
      $$ = CST::make< BinaryExpression >( @$, $1, $2, $3 );
  }
| Term LESSEQ Term
  {
      $$ = CST::make< BinaryExpression >( @$, $1, $2, $3 );
  }
| Term GREATEREQ Term
  {
      $$ = CST::make< BinaryExpression >( @$, $1, $2, $3 );
  }
| Term OR Term
  {
      $$ = CST::make< BinaryExpression >( @$, $1, $2, $3 );
  }
| Term XOR Term
  {
      $$ = CST::make< BinaryExpression >( @$, $1, $2, $3 );
  }
| Term AND Term
  {
      $$ = CST::make< BinaryExpression >( @$, $1, $2, $3 );
  }
| Term ARROW Term
  {
      $$ = CST::make< BinaryExpression >( @$, $1, $2, $3 );
  }
| Term IMPLIES Term
  {
      $$ = CST::make< BinaryExpression >( @$, $1, $2, $3 );
  }
| NOT Term
  {
      $$ = CST::make< UnaryExpression >( @$, $1, $2 );
  }
;


CallExpression
: DirectCallExpression
  {
      $$ = $1;
  }
| MethodCallExpression
  {
      $$ = $1;
  }
| IndirectCallExpression
  {
      $$ = $1;
  }
;


DirectCallExpression
: THIS %prec CALL_WITHOUT_ARGS
  {
      const auto identifier = CST::make< Identifier >( @1, $1->tokenString() );
      const auto identifierPath = IdentifierPath::fromIdentifier( identifier );
      $$ = CST::make< DirectCallExpression >( @$, identifierPath );
  }
| IdentifierPath %prec CALL_WITHOUT_ARGS
  {
      $$ = CST::make< DirectCallExpression >( @$, $1 );
  }
| IdentifierPath LPAREN RPAREN
  {
      const auto arguments = CST::make< Expressions >( @$ );
      $$ = CST::make< DirectCallExpression >( @$, $1, $2, arguments, $3 );
  }
| IdentifierPath LPAREN Terms RPAREN
  {
      $$ = CST::make< DirectCallExpression >( @$, $1, $2, $3, $4 );
  }
| IdentifierPath LPAREN error RPAREN // error recovery
  {
      $$ = nullptr;
  }
;


MethodCallExpression
: Expression DOT Identifier %prec CALL_WITHOUT_ARGS
  {
      const auto arguments = CST::make< Expressions >( @$ );
      $$ = CST::make< MethodCallExpression >( @$, $1, $2, $3, arguments );
  }
| Expression DOT Identifier LPAREN RPAREN
  {
      const auto arguments = CST::make< Expressions >( @$ );
      $$ = CST::make< MethodCallExpression >( @$, $1, $2, $3, arguments );
      $$->setLeftBracketToken( $4 );
      $$->setRightBracketToken( $5 );
  }
| Expression DOT Identifier LPAREN Terms RPAREN
  {
      $$ = CST::make< MethodCallExpression >( @$, $1, $2, $3, $5 );
      $$->setLeftBracketToken( $4 );
      $$->setRightBracketToken( $6 );
  }
| Expression DOT Identifier LPAREN error RPAREN // error recovery
  {
      $$ = nullptr;
  }
;


LiteralCallExpression
: Expression DOT IntegerLiteral
  {
      $$ = CST::make< LiteralCallExpression >( @$, $1, $2, $3 );
  }
;


IndirectCallExpression
: CallExpression LPAREN RPAREN
  {
      const auto arguments = CST::make< Expressions >( @$ );
      $$ = CST::make< IndirectCallExpression >( @$, $1, arguments );
      $$->setLeftBracketToken( $2 );
      $$->setRightBracketToken( $3 );
  }
| CallExpression LPAREN Terms RPAREN
  {
      $$ = CST::make< IndirectCallExpression >( @$, $1, $3 );
      $$->setLeftBracketToken( $2 );
      $$->setRightBracketToken( $4 );
  }
| CallExpression LPAREN error RPAREN // error recovery
  {
      $$ = nullptr;
  }
;


TypeCastingExpression
: Expression AS Type
  {
      $$ = CST::make< TypeCastingExpression >( @$, $1, $2, $3 );
  }
;


LetExpression
: LET VariableBindings IN Term
  {
      $$ = CST::make< LetExpression >( @$, $1, $2, $3, $4 );
  }
;


ConditionalExpression
: IF Term THEN Term ELSE Term
  {
      $$ = CST::make< ConditionalExpression >( @$, $1, $2, $3, $4, $5, $6 );
  }
;


ChooseExpression
: CHOOSE AttributedVariables IN Term DO Term
  {
      $$ = CST::make< ChooseExpression >( @$, $1, $2, $3, $4, $5, $6 );
  }
;


UniversalQuantifierExpression
: FORALL AttributedVariables IN Term HOLDS Term
  {
      $$ = CST::make< UniversalQuantifierExpression >( @$, $1, $2, $3, $4, $5, $6 );
  }
;


ExistentialQuantifierExpression
: EXISTS AttributedVariables IN Term WITH Term
  {
      $$ = CST::make< ExistentialQuantifierExpression >( @$, $1, $2, $3, $4, $5, $6 );
  }
;


CardinalityExpression
: VERTICAL_BAR Expression VERTICAL_BAR
  {
      $$ = CST::make< CardinalityExpression >( @$, $1, $2, $3 );
  }
;

//
//
// Literals
//

Literal
: UndefinedLiteral
  {
      $$ = $1;
  }
| BooleanLiteral
  {
      $$ = $1;
  }
| IntegerLiteral
  {
      $$ = $1;
  }
| RationalLiteral
  {
      $$ = $1;
  }
| DecimalLiteral
  {
      $$ = $1;
  }
| BinaryLiteral
  {
      $$ = $1;
  }
| StringLiteral
  {
      $$ = $1;
  }
| ReferenceLiteral
  {
      $$ = $1;
  }
// | SetLiteral
//   {
//       $$ = $1;
//   }
| ListLiteral
  {
      $$ = $1;
  }
| RangeLiteral
  {
      $$ = $1;
  }
| TupleLiteral
  {
      $$ = $1;
  }
| RecordLiteral
  {
      $$ = $1;
  }
;


UndefinedLiteral
: UNDEF
  {
      $$ = CST::make< UndefLiteral >( @$ );
      $$->setSpans( $1->spans() );
  }
;


BooleanLiteral
: TRUE
  {
      const auto value = libstdhl::Memory::get< libcasm_ir::BooleanConstant >( true );
      $$ = CST::make< ValueLiteral >( @$, value );
      $$->setSpans( $1->spans() );
  }
| FALSE
  {
      const auto value = libstdhl::Memory::get< libcasm_ir::BooleanConstant >( false );
      $$ = CST::make< ValueLiteral >( @$, value );
      $$->setSpans( $1->spans() );
  }
;


IntegerLiteral
: INTEGER
  {
      $$ = $1;
  }
;


RationalLiteral
: RATIONAL
  {
      $$ = $1;
  }
;


DecimalLiteral
: DECIMAL
  {
      $$ = $1;
  }
;


BinaryLiteral
: BINARY
  {
      $$ = $1;
  }
| HEXADECIMAL
  {
      $$ = $1;
  }
;


StringLiteral
: STRING
  {
      $$ = $1;
  }
;


ReferenceLiteral
: AT IdentifierPath
  {
      $$ = CST::make< ReferenceLiteral >( @$, $1, $2 );
  }
;


// SetLiteral
// : LCURPAREN RCURPAREN
//   {
//       const auto& expressions = CST::make< Expressions >( @$ );
//       $$ = CST::make< SetLiteral >( @$, expressions );
//       $$->setLeftBracket( $1 );
//       $$->setRightBracket( $2 );
//   }
// | LCURPAREN Terms LCURPAREN
//   {
//       $$ = CST::make< SetLiteral >( @$, $2 );
//       $$->setLeftBracket( $1 );
//       $$->setRightBracket( $3 );
//   }
// | LCURPAREN error LCURPAREN // error recovery
//   {
//       $$ = nullptr;
//   }
// ;


ListLiteral
: LSQPAREN RSQPAREN
  {
      const auto& expressions = CST::make< Expressions >( @$ );
      $$ = CST::make< ListLiteral >( @$, expressions );
      $$->setLeftBracket( $1 );
      $$->setRightBracket( $2 );
  }
| LSQPAREN Terms RSQPAREN
  {
      $$ = CST::make< ListLiteral >( @$, $2 );
      $$->setLeftBracket( $1 );
      $$->setRightBracket( $3 );
  }
| LSQPAREN error RSQPAREN // error recovery
  {
      $$ = nullptr;
  }
;


RangeLiteral
: LSQPAREN Term DOTDOT Term RSQPAREN
  {
      $$ = CST::make< RangeLiteral >( @$, $2, $3, $4 );
      $$->setLeftBracket( $1 );
      $$->setRightBracket( $5 );
  }
;


TupleLiteral
: LPAREN Terms COMMA Term RPAREN
  {
      const auto expressions = $2;
      $4->setDelimiterToken( $3 );
      expressions->add( $4 );
      $$ = CST::make< TupleLiteral >( @$, expressions );
      $$->setLeftBracket( $1 );
      $$->setRightBracket( $5 );
  }
;


RecordLiteral
: LCURPAREN Assignments RCURPAREN
  {
      $$ = CST::make< RecordLiteral >( @$, $2 );
      $$->setLeftBracket( $1 );
      $$->setRightBracket( $3 );
  }
;

//
//
// Assignments
//

Assignments
: Assignments COMMA Assignment
  {
      auto assignments = $1;
      $3->setDelimiterToken( $2 );
      assignments->add( $3 );
      $$ = assignments;
  }
| Assignment
  {
      auto assignments = CST::make< NamedExpressions >( @$ );
      assignments->add( $1 );
      $$ = assignments;
  }
;

Assignment
: Identifier COLON Term
  {
      $$ = CST::make< NamedExpression >( @$, $1, $2, $3 );
  }
;

MappedExpressions
: MappedExpressions COMMA MappedExpression
  {
      const auto& mappedExpressions = $1;
      $3->setDelimiterToken( $2 );
      mappedExpressions->add( $3 );
      $$ = mappedExpressions;
  }
| MappedExpression
  {
      auto mappedExpressions = CST::make< MappedExpressions >( @$ );
      mappedExpressions->add( $1 );
      $$ = mappedExpressions;
  }
;

MappedExpression
: MAPS Term
  {
      const auto& arguments = CST::make< Expressions >( @$ );
      $$ = CST::make< MappedExpression >( @$, Token::unresolved(), arguments, Token::unresolved(), $1, $2 );
  }
| LPAREN Term RPAREN MAPS Term
  {
      const auto& arguments = CST::make< Expressions >( @$ );
      arguments->add( $2 );
      $$ = CST::make< MappedExpression >( @$, $1, arguments, $3, $4, $5 );
  }
| TupleLiteral MAPS Term
  {
      const auto& arguments = $1->expressions();
      const auto& leftBracket = $1->leftBracket();
      const auto& rightBracket = $1->rightBracket();
      $$ = CST::make< MappedExpression >( @$, Token::unresolved(), arguments, Token::unresolved(), $2, $3 );
  }
;


//
//
// Types
//

Types
: Types COMMA Type
  {
      auto types = $1;
      $3->setDelimiterToken( $2 );
      types->add( $3 );
      $$ = types;
  }
| Type
  {
      auto types = CST::make< Types >( @$ );
      types->add( $1 );
      $$ = types;
  }
;

Type
: BasicType
  {
      $$ = $1;
  }
| TupleType
  {
      $$ = $1;
  }
| RecordType
  {
      $$ = $1;
  }
| TemplateType
  {
      $$ = $1;
  }
| RelationType
  {
      $$ = $1;
  }
| FixedSizedType
  {
      $$ = $1;
  }
| MappingType
  {
      $$ = $1;
  }
| VaradicType
  {
      $$ = $1;
  }
;


BasicType
: IdentifierPath %prec BASIC_TYPE
  {
      $$ = CST::make< BasicType >( @$, $1 );
  }
;


TupleType
: LPAREN Types COMMA Type RPAREN
  {
      auto subTypes = $2;
      $4->setDelimiterToken( $3 );
      subTypes->add( $4 );
      $$ = CST::make< TupleType >( @$, $1, subTypes, $5 );
  }
;


RecordType
: LCURPAREN TypedVariables COMMA TypedVariable RCURPAREN
  {
      auto namedSubTypes = $2;
      $4->setDelimiterToken( $3 );
      namedSubTypes->add( $4 );
      $$ = CST::make< RecordType >( @$, $1, namedSubTypes, $5 );
  }
;


TemplateType
: IdentifierPath LESSER Types GREATER
  {
      $$ = CST::make< TemplateType >( @$, $1, $2, $3, $4 );
  }
;


RelationType
: IdentifierPath LESSER MaybeFunctionParameters MAPS Type GREATER
  {
      $$ = CST::make< RelationType >( @$, $1, $2, $3, $4, $5, $6 );
  }
;


FixedSizedType
: IdentifierPath MARK Term
  {
      $$ = CST::make< FixedSizedType >( @$, $1, $2, $3 );
  }
;


MappingType
: LESSER FunctionParameters MAPS Type GREATER
  {
      $$ = CST::make< MappingType >( @$, $1, $2, $3, $4, $5 );      
  }
;


VaradicType
: Identifier DOTDOTDOT
  {
      $$ = CST::make< VaradicType >( @$, $1, $2 );
  }
;

//
//
// FunctionParameters (Relation) and Parameters
//

FunctionParameters
: FunctionParameters ASTERIX Type
  {
      auto types = $1;
      $3->setDelimiterToken( $2 );
      types->add( $3 );
      $$ = types;
  }
| Type
  {
      auto types = CST::make< Types >( @$ );
      types->add( $1 );
      $$ = types;
  }
;


MaybeFunctionParameters
: FunctionParameters
  {
      $$ = $1;
  }
| %empty
  {
      $$ = CST::make< Types >( @$ );
  }
;


MethodParameters
: MethodParameters COMMA TypedAttributedVariable
  {
      auto parameters = $1;
      $3->setDelimiterToken( $2 );
      parameters->add( $3 );
      $$ = parameters;
  }
| THIS
  {
      auto parameters = CST::make< NodeList< VariableDefinition > >( @$ );
      const auto identifier = CST::make< Identifier >( @1, $1->tokenString() );
      const auto unresolvedType = CST::make< UnresolvedType >( @$ );
      auto variable = CST::make< VariableDefinition >( @$, identifier, Token::unresolved(), unresolvedType );
      parameters->add( variable );
      $$ = parameters;
  }
;


Parameters
: Parameters COMMA TypedAttributedVariable
  {
      auto parameters = $1;
      $3->setDelimiterToken( $2 );
      parameters->add( $3 );
      $$ = parameters;
  }
| TypedAttributedVariable
  {
      auto parameters = CST::make< NodeList< VariableDefinition > >( @$ );
      parameters->add( $1 );
      $$ = parameters;
  }
;


//
// Defined and Initially
//

MaybeDefined
: DEFINED LCURPAREN Term RCURPAREN
  {
      $$ = CST::make< Defined >( @$, $1, $2, $3, $4 );
  }
| %empty
  {
      $$ = CST::make< Defined >( @$, Token::unresolved(), Token::unresolved(), CST::make< UndefLiteral >( @$ ), Token::unresolved() );
  }
;


MaybeInitially
: EQUAL LCURPAREN Expression RCURPAREN
  {
      // TODO: FIXME: @ppaulweber: drop braces and replace this rule with ::= Expression
      const auto& embracedExpression = CST::make< EmbracedExpression >( @3, $2, $3, $4 );
      $$ = CST::make< Initially >( @$, $1, embracedExpression );
  }
| EQUAL LCURPAREN MappedExpressions RCURPAREN
  {
      // TODO: FIXME: @ppaulweber: replace this rule with ::= EQUAL SetLiteral
      const auto& expressions = CST::make< Expressions >( @3 );
      for( auto const& expression : *$3 )
      {
          expressions->add( expression );
      }
      const auto& setLiteral = CST::make< SetLiteral >( @3, expressions );
      setLiteral->setLeftBracket( $2 );
      setLiteral->setRightBracket( $4 );
      $$ = CST::make< Initially >( @$, $1, setLiteral );
  }
| %empty
  {
      const auto& expression = CST::make< CST::AbstractExpression >( @$, Token::unresolved() );
      $$ = CST::make< Initially >( @$, Token::unresolved(), expression );
  }
;

//
//
// Identifiers
//

Identifier
: IDENTIFIER
  {
      $$ = $1;
  }
| IN
  {
      $$ = CST::make< Identifier >( @$, $1->tokenString() );
      $$->setSpans( m_lexer.fetchSpansAndReset() );
  }
| CASM
  {
      $$ = CST::make< Identifier >( @$, $1->tokenString() );
      $$->setSpans( m_lexer.fetchSpansAndReset() );
  }
| SELF
  {
      $$ = CST::make< Identifier >( @$, $1->tokenString() );
      $$->setSpans( m_lexer.fetchSpansAndReset() );
  }
| ENUMERATION
  {
      $$ = CST::make< Identifier >( @$, $1->tokenString() );
      $$->setSpans( m_lexer.fetchSpansAndReset() );
  }
| STRUCTURE
  {
      $$ = CST::make< Identifier >( @$, $1->tokenString() );
      $$->setSpans( m_lexer.fetchSpansAndReset() );
  }
;


IdentifierPath
: IdentifierPath DOUBLECOLON Identifier
  {
      auto path = $1;
      $3->setDoubleColon( $2 );
      path->addIdentifier( $3 );
      $$ = path;
  }
| Identifier
  {
      $$ = CST::make< IdentifierPath >( @$, $1 );
  }
;


//
// Variables
//

Variable
: TypedVariable
  {
      $$ = $1;
  }
| Identifier
  {
      const auto unresolvedType = CST::make< UnresolvedType >( @$ );
      $$ = CST::make< VariableDefinition >( @$, $1, Token::unresolved(), unresolvedType );
  }
;


AttributedVariables
: AttributedVariables COMMA AttributedVariable
  {
      auto variables = $1;
      $3->setDelimiterToken( $2 );
      variables->add( $3 );
      $$ = variables;
  }
| AttributedVariable
  {
      auto variables = CST::make< VariableDefinitions >( @$ );
      variables->add( $1 );
      $$ = variables;
  }
;


TypedVariables
: TypedVariables COMMA TypedVariable
  {
      auto typedVariables = $1;
      $3->setDelimiterToken( $2 );
      typedVariables->add( $3 );
      $$ = typedVariables;
  }
| TypedVariable
  {
      auto typedVariables = CST::make< VariableDefinitions >( @$ );
      typedVariables->add( $1 );
      $$ = typedVariables;
  }
;


TypedVariable
: Identifier COLON Type
  {
      auto variable = CST::make< VariableDefinition >( @$, $1, $2, $3 );
      $$ = variable;
  }
;


AttributedVariable
: Attributes Variable
  {
      auto variable = $2;
      variable->setAttributes( $1 );
      $$ = variable;
  }
| Variable
  {
      $$ = $1;
  }
;


TypedAttributedVariable
: Attributes TypedVariable
  {
      auto variable = $2;
      variable->setAttributes( $1 );
      $$ = variable;
  }
| TypedVariable
  {
      $$ = $1;
  }
;

//
//
// VariableBindings
//

VariableBindings
: VariableBindings COMMA VariableBinding
  {
      auto variableBindings = $1;
      $3->setDelimiterToken( $2 );
      variableBindings->add( $3 );
      $$ = variableBindings;
  }
| VariableBinding
  {
      auto variableBindings = CST::make< VariableBindings >( @$ );
      variableBindings->add( $1 );
      $$ = variableBindings;
  }
;

VariableBinding
: AttributedVariable EQUAL Term
  {
      $$ = CST::make< VariableBinding >( @$, $1, $2, $3 );
  }
;

//
//
// LocalFunctionDefinitions
//

LocalFunctionDefinitions
: LocalFunctionDefinitions COMMA AttributedLocalFunctionDefinition
  {
      auto definitions = $1;
      $3->setDelimiterToken( $2 );
      definitions->add( $3 );
      $$ = definitions;
  }
| AttributedLocalFunctionDefinition
  {
      auto definitions = CST::make< FunctionDefinitions >( @$ );
      definitions->add( $1 );
      $$ = definitions;
  }
;

AttributedLocalFunctionDefinition
: Attributes LocalFunctionDefinition
  {
      auto definition = $2;
      definition->setAttributes( $1 );
      $$ = definition;
  }
| LocalFunctionDefinition
  {
      $$ = $1;
  }
| error // error recovery
  {
      $$ = nullptr;
  }
;

LocalFunctionDefinition
: Identifier COLON MaybeFunctionParameters MAPS Type MaybeDefined MaybeInitially
  {
      $$ = CST::make< FunctionDefinition >( @$, Token::unresolved(), $1, $2, $3, $4, $5, $6, $7 );
      $$->setClassification( FunctionDefinition::Classification::LOCAL );
  }
;

//
//
// Attributes
//

Attributes
: Attributes Attribute
  {
      auto attributes = $1;
      attributes->add( $2 );
      $$ = attributes;
  }
| Attribute
  {
      auto attributes = CST::make< Attributes >( @$ );
      attributes->add( $1 );
      $$ = attributes;
  }
;

Attribute
: LSQPAREN BasicAttribute RSQPAREN
  {
      const auto& attribute = $2;
      attribute->setLeftBrace( $1 );
      attribute->setRightBrace( $3 );
      $$ = attribute;
  }
| LSQPAREN SymbolAttribute RSQPAREN
  {
      const auto& attribute = $2;
      attribute->setLeftBrace( $1 );
      attribute->setRightBrace( $3 );
      $$ = attribute;
  }
| LSQPAREN ExpressionAttribute RSQPAREN
  {
      const auto& attribute = $2;
      attribute->setLeftBrace( $1 );
      attribute->setRightBrace( $3 );
      $$ = attribute;
  }
| LSQPAREN error RSQPAREN // error recovery
  {
      $$ = nullptr;
  }
;

BasicAttribute
: Identifier
  {
      $$ = CST::make< BasicAttribute >( @$, $1 );
  }
;

SymbolAttribute
: Identifier TypedVariable
  {
      $$ = CST::make< SymbolAttribute >( @$, $1, $2 );
  }
;

ExpressionAttribute
: Identifier Term
  {
      $$ = CST::make< ExpressionAttribute >( @$, $1, $2 );
  }
;

%%

void Parser::error( const libstdhl::SourceLocation& location, const std::string& message )
{
    m_log.error( {location}, message, Code::SyntaxError );
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
