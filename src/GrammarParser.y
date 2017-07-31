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
    #include <libcasm-fe/ast/Definition>
    #include <libcasm-fe/ast/Expression>
    #include <libcasm-fe/ast/Rule>
    #include <libcasm-fe/ast/Token>
    #include <libcasm-fe/Exception>
    #include <libcasm-fe/Logger>

    #include <libstdhl/SourceLocation>

    using namespace libcasm_fe;
    using namespace Ast;

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
        const auto type = libstdhl::Memory::get< libcasm_ir::VoidType >();
        const auto name = Ast::make< Identifier >( sourceLocation, type->description() );
        const auto path = Ast::make< IdentifierPath >( sourceLocation, name );
        const auto node = Ast::make< BasicType >( sourceLocation, path );
        node->setType( type );
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
%token <Identifier::Ptr>  IDENTIFIER  "identifier"

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
%type <FunctionDefinition::Ptr> FunctionDefinition
%type <FunctionDefinitions::Ptr> FunctionDefinitions
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
%type <FunctionDefinition::Ptr> StructureDefinitionElement
%type <FunctionDefinitions::Ptr> StructureDefinitionList
%type <FeatureDefinition::Ptr> FeatureDefinition
%type <Definition::Ptr> FeatureDefinitionElement
%type <Definitions::Ptr> FeatureDefinitionList
%type <ImplementationDefinition::Ptr> ImplementationDefinition
%type <Definition::Ptr> ImplementationDefinitionDefinition
%type <Definitions::Ptr> ImplementationDefinitionDefinitions
%type <DeclarationDefinition::Ptr> DeclarationDefinition

// literals
%type <Literal::Ptr> Literal
%type <UndefLiteral::Ptr> UndefinedLiteral
%type <ValueLiteral::Ptr> BooleanLiteral StringLiteral BinaryLiteral IntegerLiteral DecimalLiteral RationalLiteral
%type <ReferenceLiteral::Ptr> ReferenceLiteral
%type <ListLiteral::Ptr> ListLiteral
%type <RangeLiteral::Ptr> RangeLiteral
%type <TupleLiteral::Ptr> TupleLiteral
%type <RecordLiteral::Ptr> RecordLiteral

// expressions
%type <Expression::Ptr> Term SimpleOrClaspedTerm OperatorExpression
%type <Expressions::Ptr> Terms
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

// assignments
%type <NamedExpression::Ptr> Assignment
%type <NamedExpressions::Ptr> Assignments

// types
%type <libcasm_fe::Ast::Type::Ptr> Type
%type <Types::Ptr> Types
%type <BasicType::Ptr> BasicType
%type <TupleType::Ptr> TupleType
%type <RecordType::Ptr> RecordType
%type <TemplateType::Ptr> TemplateType
%type <RelationType::Ptr> RelationType
%type <FixedSizedType::Ptr> FixedSizedType

// attributes
%type <Attribute::Ptr> Attribute
%type <Attributes::Ptr> Attributes
%type <BasicAttribute::Ptr> BasicAttribute
%type <ExpressionAttribute::Ptr> ExpressionAttribute

// other
%type <Case::Ptr> CaseLabel
%type <Cases::Ptr> CaseLabels
%type <Initially::Ptr> MaybeInitially
%type <Initializer::Ptr> Initializer
%type <Initializers::Ptr> Initializers
%type <Defined::Ptr> MaybeDefined
%type <Types::Ptr> FunctionParameters MaybeFunctionParameters
%type <VariableDefinitions::Ptr> Parameters AttributedVariables
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
      m_specification.setHeader( $1 );
      m_specification.setDefinitions( $2 );
      m_specification.setSpans( m_lexer.fetchSpansAndReset() );
  }
;


Header
: Attributes CASM
  {
      auto definition = Ast::make< HeaderDefinition >( @$, $2 );
      definition->setAttributes( $1 );
      $$ = definition;
  }
| CASM
  {
      $$ = Ast::make< HeaderDefinition >( @$, $1 );
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
      auto definitions = Ast::make< Definitions >( @$ );
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
| FeatureDefinition
  {
      $$ = $1;
  }
| ImplementationDefinition
  {
      $$ = $1;
  }
;


InitDefinition
: INIT IdentifierPath
  {
      $$ = Ast::make< InitDefinition >( @$, $1, $2 );
  }
| INIT LCURPAREN Initializers RCURPAREN
  {
      $$ = Ast::make< InitDefinition >( @$, $1, $2, $3, $4 );
  }
;


EnumerationDefinition
: ENUMERATION Identifier EQUAL LCURPAREN Enumerators RCURPAREN
  {
      $$ = Ast::make< EnumerationDefinition >( @$, $1, $2, $3, $4, $5, $6 );
  }
;


DerivedDefinition
: DERIVED Identifier MAPS Type EQUAL Term
  {
      const auto params = Ast::make< NodeList< VariableDefinition > >( @$ );
      $$ = Ast::make< DerivedDefinition >( @$, $1, $2, params, $3, $4, $5, $6 );
  }
| DERIVED Identifier LPAREN Parameters RPAREN MAPS Type EQUAL Term
  {
      $$ = Ast::make< DerivedDefinition >( @$, $1, $2, $4, $6, $7, $8, $9 );
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
      const auto params = Ast::make< NodeList< VariableDefinition > >( @$ );
      const auto vType = createVoidType( @$ );
      $$ = Ast::make< RuleDefinition >( @$, $1, $2, params, Token::unresolved(), vType, $3, $4 );
  }
| RULE Identifier MAPS Type EQUAL Rule
  {
      const auto params = Ast::make< NodeList< VariableDefinition > >( @$ );
      $$ = Ast::make< RuleDefinition >( @$, $1, $2, params, $3, $4, $5, $6 );
  }
| RULE Identifier LPAREN Parameters RPAREN EQUAL Rule
  {
      const auto vType = createVoidType( @$ );
      $$ = Ast::make< RuleDefinition >( @$, $1, $2, $4, Token::unresolved(), vType, $6, $7 );
      $$->setLeftBracketToken( $3 );
      $$->setRightBracketToken( $5 );
  }
| RULE Identifier LPAREN Parameters RPAREN MAPS Type EQUAL Rule
  {
      $$ = Ast::make< RuleDefinition >( @$, $1, $2, $4, $6, $7, $8, $9 );
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


FunctionDefinitions
: FunctionDefinitions FunctionDefinition
  {
      auto functions = $1;
      functions->add( $2 );
      $$ = functions;
  }
| FunctionDefinition
  {
      auto functions = Ast::make< FunctionDefinitions >( @$ );
      functions->add( $1 );
      $$ = functions;
  }
;


FunctionDefinition
: FUNCTION Identifier COLON MaybeFunctionParameters MAPS Type MaybeDefined MaybeInitially
  {
      $$ = Ast::make< FunctionDefinition >( @$, $1, $2, $3, $4, $5, $6, $7, $8 );

      // apply the name of the function declaration to the initializer functions
      const auto initially = $$->initially();
      for( auto& initializer : *initially->initializers() )
      {
          initializer->setFunction( $$ );
      }
  }
;


EnumeratorDefinition
: Identifier
  {
      $$ = Ast::make< EnumeratorDefinition >( @$, $1 );
  }
| Attributes Identifier
  {
      auto enumerator = Ast::make< EnumeratorDefinition >( @$, $2 );
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
      auto enumerators = Ast::make< Enumerators >( @$ );
      enumerators->add( $1 );
      $$ = enumerators;
  }
;


UsingDefinition
: USING Identifier EQUAL Type
  {
      $$ = Ast::make< UsingDefinition >( @$, $1, $2, $3, $4 );
  }
;


UsingPathDefinition
: USING IdentifierPath
  {
      $$ = Ast::make< UsingPathDefinition >( @$, $1, $2 );
  }
| USING IdentifierPath DOUBLECOLON ASTERIX
  {
      $$ = Ast::make< UsingPathDefinition >( @$, $1, $2, $3, $4 );
  }
;


InvariantDefinition
: INVARIANT Identifier EQUAL Term
  {
      $$ = Ast::make< InvariantDefinition >( @$, $1, $2, $3, $4 );
  }
;

//
//
// StructureDefinition
//

ImportDefinition
: IMPORT IdentifierPath
  {
      $$ = Ast::make< ImportDefinition >( @$, $1, $2 );
  }
| IMPORT IdentifierPath AS Identifier
  {
      $$ = Ast::make< ImportDefinition >( @$, $1, $2, $3, $4 );
  }
;


StructureDefinition
: STRUCTURE Identifier EQUAL LCURPAREN StructureDefinitionList RCURPAREN
  {
      // TODO: FIXME: @ppaulweber: handle AST keyword tokens $1, $3, $4, and $6
      // $$ = Ast::make< StructureDefinition >( @$, $2, $5 );
  }
;


StructureDefinitionElement
: LSQPAREN Attributes RSQPAREN FunctionDefinition
  {
      auto definition = $4;
      definition->setAttributes( $2 );
      $$ = definition;
  }
| FunctionDefinition
  {
      $$ = $1;
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
      auto functions = Ast::make< FunctionDefinitions >( @$ );
      functions->add( $1 );
      $$ = functions;
  }
;

//
//
// FeatureDefinition
//

FeatureDefinition
: FEATURE Identifier EQUAL LCURPAREN FeatureDefinitionList RCURPAREN
  {
      // TODO: FIXME: @ppaulweber: handle AST keyword tokens $1, $3, $4, and $6
      $$ = Ast::make< FeatureDefinition >( @$, $2, $5 );
  }
;


FeatureDefinitionElement
: LSQPAREN Attributes RSQPAREN DeclarationDefinition
  {
      auto definition = $4;
      definition->setAttributes( $2 );
      $$ = definition;
  }
| DeclarationDefinition
  {
      $$ = $1;
  }
| LSQPAREN Attributes RSQPAREN DerivedDefinition
  {
      auto definition = $4;
      definition->setAttributes( $2 );
      $$ = definition;
  }
| DerivedDefinition
  {
      $$ = $1;
  }
| LSQPAREN Attributes RSQPAREN RuleDefinition
  {
      auto definition = $4;
      definition->setAttributes( $2 );
      $$ = definition;
  }
| RuleDefinition
  {
      $$ = $1;
  }
;


FeatureDefinitionList
: FeatureDefinitionList FeatureDefinitionElement
  {
      auto definitions = $1;
      definitions->add( $2 );
      $$ = definitions;
  }
| FeatureDefinitionElement
  {
      auto definitions = Ast::make< Definitions >( @$ );
      definitions->add( $1 );
      $$ = definitions;
  }
;

//
//
// ImplementationDefinition
//

ImplementationDefinition
: IMPLEMENTS IdentifierPath FOR Type EQUAL LCURPAREN ImplementationDefinitionDefinitions RCURPAREN
  {
      $$ = Ast::make< ImplementationDefinition >( @$, $2, $4, $7 );
  }
| IMPLEMENTS Type EQUAL LCURPAREN ImplementationDefinitionDefinitions RCURPAREN
  {
      const auto name = Ast::make< Identifier >( @$, "" );
      const auto path = asIdentifierPath( name );
      $$ = Ast::make< ImplementationDefinition >( @$, path, $2, $5 );
  }
;


ImplementationDefinitionDefinition
: DerivedDefinition
  {
      $$ = $1;
  }
| RuleDefinition
  {
      $$ = $1;
  }
;


ImplementationDefinitionDefinitions
: ImplementationDefinitionDefinition ImplementationDefinitionDefinitions
  {
      auto definitions = $2;
      definitions->add( $1 );
      $$ = definitions;
  }
| ImplementationDefinitionDefinition
  {
      auto definitions = Ast::make< Definitions >( @$ );
      definitions->add( $1 );
      $$ = definitions;
  }
;

//
//
// DeclarationDefinition
//

DeclarationDefinition
: DERIVED Identifier COLON MaybeFunctionParameters MAPS Type
  {
      // TODO: FIXME: @ppaulweber: handle AST keyword tokens $1, $3, and $5
      auto declaration = Ast::make< DeclarationDefinition >( @$, $2, $4, $6 );
      declaration->setKind( DeclarationDefinition::Kind::DERIVED );
      $$ = declaration;
  }
| RULE Identifier COLON MaybeFunctionParameters MAPS Type
  {
      // TODO: FIXME: @ppaulweber: handle AST keyword tokens $1, $3, and $5
      auto declaration = Ast::make< DeclarationDefinition >( @$, $2, $4, $6 );
      declaration->setKind( DeclarationDefinition::Kind::RULE );
      $$ = declaration;
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
      auto rules = Ast::make< Rules >( @$ );
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
      $$ = Ast::make< SkipRule >( @$, $1 );
  }
;


ConditionalRule
: IF Term THEN Rule
  {
      $$ = Ast::make< ConditionalRule >( @$, $1, $2, $3, $4 );
  }
| IF Term THEN Rule ELSE Rule
  {
      $$ = Ast::make< ConditionalRule >( @$, $1, $2, $3, $4, $5, $6 );
  }
;


CaseRule
: CASE Term OF LCURPAREN CaseLabels RCURPAREN
  {
      $$ = Ast::make< CaseRule >( @$, $1, $2, $3, $4, $5, $6 );
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
      auto cases = Ast::make< Cases >( @$ );
      cases->add( $1 );
      $$ = cases;
  }
;


CaseLabel
: DEFAULT COLON Rule
  {
      $$ = Ast::make< DefaultCase >( @$, $1, $2, $3 );
  }
| UNDERLINE COLON Rule
  {
      $$ = Ast::make< DefaultCase >( @$, $1, $2, $3 );
  }
| Term COLON Rule
  {
      $$ = Ast::make< ExpressionCase >( @$, $1, $2, $3 );
  }
;


LetRule
: LET VariableBindings IN Rule
  {
      $$ = Ast::make< LetRule >( @$, $1, $2, $3, $4 );
  }
;


LocalRule
: LOCAL LocalFunctionDefinitions IN Rule
  {
      $$ = Ast::make< LocalRule >( @$, $1, $2, $3, $4 );
  }
;


ForallRule
: FORALL AttributedVariables IN Term DO Rule
  {
      $$ = Ast::make< ForallRule >( @$, $1, $2, $3, $4, $5, $6 );
  }
| FORALL AttributedVariables IN Term WITH Term DO Rule
  {
      $$ = Ast::make< ForallRule >( @$, $1, $2, $3, $4, $5, $6, $7, $8 );
  }
;


ChooseRule
: CHOOSE AttributedVariables IN Term DO Rule
  {
      $$ = Ast::make< ChooseRule >( @$, $1, $2, $3, $4, $5, $6 );
  }
;


IterateRule
: ITERATE Rule
  {
      $$ = Ast::make< IterateRule >( @$, $1, $2 );
  }
;


BlockRule
: LCURPAREN Rules RCURPAREN
  {
      $$ = Ast::make< BlockRule >( @$, $1, $2, $3 );
  }
| PAR Rules ENDPAR
  {
      $$ = Ast::make< BlockRule >( @$, $1, $2, $3 );
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
      $$ = Ast::make< SequenceRule >( @$, $1, $2, $3 );
  }
| SEQ Rules ENDSEQ
  {
      $$ = Ast::make< SequenceRule >( @$, $1, $2, $3 );
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
      $$ = Ast::make< UpdateRule >( @$, $1, $2, $3 );
  }
;


CallRule
: CallExpression %prec CALL
  {
      $$ = Ast::make< CallRule >( @$, $1 );
  }
;


WhileRule
: WHILE Term DO Rule
  {
      $$ = Ast::make< WhileRule >( @$, $1, $2, $3, $4 );
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
      const auto expressions = Ast::make< Expressions >( @$ );
      expressions->add( $1 );
      $$ = expressions;
  }
;


Term
: SimpleOrClaspedTerm
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


SimpleOrClaspedTerm
: LPAREN Term RPAREN
  {
      $$ = Ast::make< Ast::EmbracedExpression >( @$, $1, $2, $3 );
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
| PLUS SimpleOrClaspedTerm %prec UPLUS
  {
      $$ = Ast::make< UnaryExpression >( @$, $1, $2, libcasm_ir::Value::ADD_INSTRUCTION );
  }
| MINUS SimpleOrClaspedTerm %prec UMINUS
  {
      $$ = Ast::make< UnaryExpression >( @$, $1, $2, libcasm_ir::Value::INV_INSTRUCTION );
  }
;


//
// Operator Expression
//

OperatorExpression
: Term PLUS Term
  {
      $$ = Ast::make< BinaryExpression >( @$, $1, $2, $3, libcasm_ir::Value::ADD_INSTRUCTION );
  }
| Term MINUS Term
  {
      $$ = Ast::make< BinaryExpression >( @$, $1, $2, $3, libcasm_ir::Value::SUB_INSTRUCTION );
  }
| Term ASTERIX Term
  {
      $$ = Ast::make< BinaryExpression >( @$, $1, $2, $3, libcasm_ir::Value::MUL_INSTRUCTION );
  }
| Term SLASH Term
  {
      $$ = Ast::make< BinaryExpression >( @$, $1, $2, $3, libcasm_ir::Value::DIV_INSTRUCTION );
  }
| Term PERCENT Term
  {
      $$ = Ast::make< BinaryExpression >( @$, $1, $2, $3, libcasm_ir::Value::MOD_INSTRUCTION );
  }
| Term CARET Term
  {
      $$ = Ast::make< BinaryExpression >( @$, $1, $2, $3, libcasm_ir::Value::POW_INSTRUCTION );
  }
| Term NEQUAL Term
  {
      $$ = Ast::make< BinaryExpression >( @$, $1, $2, $3, libcasm_ir::Value::NEQ_INSTRUCTION );
  }
| Term EQUAL Term
  {
      $$ = Ast::make< BinaryExpression >( @$, $1, $2, $3, libcasm_ir::Value::EQU_INSTRUCTION );
  }
| Term LESSER Term
  {
      $$ = Ast::make< BinaryExpression >( @$, $1, $2, $3, libcasm_ir::Value::LTH_INSTRUCTION );
  }
| Term GREATER Term
  {
      $$ = Ast::make< BinaryExpression >( @$, $1, $2, $3, libcasm_ir::Value::GTH_INSTRUCTION );
  }
| Term LESSEQ Term
  {
      $$ = Ast::make< BinaryExpression >( @$, $1, $2, $3, libcasm_ir::Value::LEQ_INSTRUCTION );
  }
| Term GREATEREQ Term
  {
      $$ = Ast::make< BinaryExpression >( @$, $1, $2, $3, libcasm_ir::Value::GEQ_INSTRUCTION );
  }
| Term OR Term
  {
      $$ = Ast::make< BinaryExpression >( @$, $1, $2, $3, libcasm_ir::Value::OR_INSTRUCTION );
  }
| Term XOR Term
  {
      $$ = Ast::make< BinaryExpression >( @$, $1, $2, $3, libcasm_ir::Value::XOR_INSTRUCTION );
  }
| Term AND Term
  {
      $$ = Ast::make< BinaryExpression >( @$, $1, $2, $3, libcasm_ir::Value::AND_INSTRUCTION );
  }
| Term ARROW Term
  {
      $$ = Ast::make< BinaryExpression >( @$, $1, $2, $3, libcasm_ir::Value::IMP_INSTRUCTION );
  }
| Term IMPLIES Term
  {
      $$ = Ast::make< BinaryExpression >( @$, $1, $2, $3, libcasm_ir::Value::IMP_INSTRUCTION );
  }
| NOT Term
  {
      $$ = Ast::make< UnaryExpression >( @$, $1, $2, libcasm_ir::Value::NOT_INSTRUCTION );
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
: IdentifierPath %prec CALL_WITHOUT_ARGS
  {
      const auto arguments = Ast::make< Expressions >( @$ );
      $$ = Ast::make< DirectCallExpression >( @$, $1, arguments );
  }
| IdentifierPath LPAREN RPAREN
  {
      const auto arguments = Ast::make< Expressions >( @$ );
      $$ = Ast::make< DirectCallExpression >( @$, $1, arguments );
      $$->setLeftBracketToken( $2 );
      $$->setRightBracketToken( $3 );
  }
| IdentifierPath LPAREN Terms RPAREN
  {
      $$ = Ast::make< DirectCallExpression >( @$, $1, $3 );
      $$->setLeftBracketToken( $2 );
      $$->setRightBracketToken( $4 );
  }
| IdentifierPath LPAREN error RPAREN // error recovery
  {
      $$ = nullptr;
  }
;


MethodCallExpression
: SimpleOrClaspedTerm DOT Identifier %prec CALL_WITHOUT_ARGS
  {
      const auto arguments = Ast::make< Expressions >( @$ );
      $$ = Ast::make< MethodCallExpression >( @$, $1, $2, $3, arguments );
  }
| SimpleOrClaspedTerm DOT Identifier LPAREN RPAREN
  {
      const auto arguments = Ast::make< Expressions >( @$ );
      $$ = Ast::make< MethodCallExpression >( @$, $1, $2, $3, arguments );
      $$->setLeftBracketToken( $4 );
      $$->setRightBracketToken( $5 );
  }
| SimpleOrClaspedTerm DOT Identifier LPAREN Terms RPAREN
  {
      $$ = Ast::make< MethodCallExpression >( @$, $1, $2, $3, $5 );
      $$->setLeftBracketToken( $4 );
      $$->setRightBracketToken( $6 );
  }
| SimpleOrClaspedTerm DOT Identifier LPAREN error RPAREN // error recovery
  {
      $$ = nullptr;
  }
;


LiteralCallExpression
: SimpleOrClaspedTerm DOT IntegerLiteral
  {
      $$ = Ast::make< LiteralCallExpression >( @$, $1, $2, $3 );
  }
;


IndirectCallExpression
: CallExpression LPAREN RPAREN
  {
      const auto arguments = Ast::make< Expressions >( @$ );
      $$ = Ast::make< IndirectCallExpression >( @$, $1, arguments );
      $$->setLeftBracketToken( $2 );
      $$->setRightBracketToken( $3 );
  }
| CallExpression LPAREN Terms RPAREN
  {
      $$ = Ast::make< IndirectCallExpression >( @$, $1, $3 );
      $$->setLeftBracketToken( $2 );
      $$->setRightBracketToken( $4 );
  }
| CallExpression LPAREN error RPAREN // error recovery
  {
      $$ = nullptr;
  }
;


TypeCastingExpression
: SimpleOrClaspedTerm AS Type
  {
      $$ = Ast::make< TypeCastingExpression >( @$, $1, $2, $3 );
  }
;


LetExpression
: LET VariableBindings IN Term
  {
      $$ = Ast::make< LetExpression >( @$, $1, $2, $3, $4 );
  }
;


ConditionalExpression
: IF Term THEN Term ELSE Term
  {
      $$ = Ast::make< ConditionalExpression >( @$, $1, $2, $3, $4, $5, $6 );
  }
;


ChooseExpression
: CHOOSE AttributedVariables IN Term DO Term
  {
      $$ = Ast::make< ChooseExpression >( @$, $1, $2, $3, $4, $5, $6 );
  }
;


UniversalQuantifierExpression
: FORALL AttributedVariables IN Term HOLDS Term
  {
      $$ = Ast::make< UniversalQuantifierExpression >( @$, $1, $2, $3, $4, $5, $6 );
  }
;


ExistentialQuantifierExpression
: EXISTS AttributedVariables IN Term WITH Term
  {
      $$ = Ast::make< ExistentialQuantifierExpression >( @$, $1, $2, $3, $4, $5, $6 );
  }
;


CardinalityExpression
: VERTICAL_BAR SimpleOrClaspedTerm VERTICAL_BAR
  {
      $$ = Ast::make< CardinalityExpression >( @$, $1, $2, $3 );
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
      $$ = Ast::make< UndefLiteral >( @$ );
      $$->setSpans( $1->spans() );
  }
;


BooleanLiteral
: TRUE
  {
      const auto value = libstdhl::Memory::get< libcasm_ir::BooleanConstant >( true );
      $$ = Ast::make< ValueLiteral >( @$, value );
      $$->setSpans( $1->spans() );
  }
| FALSE
  {
      const auto value = libstdhl::Memory::get< libcasm_ir::BooleanConstant >( false );
      $$ = Ast::make< ValueLiteral >( @$, value );
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
      $$ = Ast::make< ReferenceLiteral >( @$, $1, $2 );
  }
;


ListLiteral
: LSQPAREN RSQPAREN
  {
      const auto expressions = Ast::make< Expressions >( @$ );
      $$ = Ast::make< ListLiteral >( @$, expressions );
      $$->setLeftBracket( $1 );
      $$->setRightBracket( $2 );
  }
| LSQPAREN Terms RSQPAREN
  {
      $$ = Ast::make< ListLiteral >( @$, $2 );
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
      $$ = Ast::make< RangeLiteral >( @$, $2, $3, $4 );
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
      $$ = Ast::make< TupleLiteral >( @$, expressions );
      $$->setLeftBracket( $1 );
      $$->setRightBracket( $5 );
  }

RecordLiteral
: LPAREN Assignments RPAREN
  {
      $$ = Ast::make< RecordLiteral >( @$, $2 );
      $$->setLeftBracket( $1 );
      $$->setRightBracket( $3 );
  }
;

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
      auto assignments = Ast::make< NamedExpressions >( @$ );
      assignments->add( $1 );
      $$ = assignments;
  }
;

Assignment
: Identifier COLON Term
  {
      $$ = Ast::make< NamedExpression >( @$, $1, $2, $3 );
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
      auto types = Ast::make< Types >( @$ );
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
;


BasicType
: IdentifierPath %prec BASIC_TYPE
  {
      $$ = Ast::make< BasicType >( @$, $1 );
  }
;


TupleType
: LPAREN Types COMMA Type RPAREN
  {
      auto subTypes = $2;
      $4->setDelimiterToken( $3 );
      subTypes->add( $4 );
      $$ = Ast::make< TupleType >( @$, $1, subTypes, $5 );
  }
;


RecordType
: LPAREN TypedVariables COMMA TypedVariable RPAREN
  {
      auto namedSubTypes = $2;
      $4->setDelimiterToken( $3 );
      namedSubTypes->add( $4 );
      $$ = Ast::make< RecordType >( @$, $1, namedSubTypes, $5 );
  }
;


TemplateType
: IdentifierPath LESSER Types GREATER
  {
      $$ = Ast::make< TemplateType >( @$, $1, $2, $3, $4 );
  }
;


RelationType
: IdentifierPath LESSER MaybeFunctionParameters MAPS Type GREATER
  {
      $$ = Ast::make< RelationType >( @$, $1, $2, $3, $4, $5, $6 );
  }
;


FixedSizedType
: IdentifierPath MARK Term
  {
      $$ = Ast::make< FixedSizedType >( @$, $1, $2, $3 );
  }
;


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
      auto types = Ast::make< Types >( @$ );
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
      $$ = Ast::make< Types >( @$ );
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
      auto parameters = Ast::make< NodeList< VariableDefinition > >( @$ );
      parameters->add( $1 );
      $$ = parameters;
  }
;


//
// Defined, Initially and Initializers
//

MaybeDefined
: DEFINED LCURPAREN Term RCURPAREN
  {
      $$ = Ast::make< Defined >( @$, $1, $2, $3, $4 );
  }
| %empty
  {
      $$ = Ast::make< Defined >( @$, Token::unresolved(), Token::unresolved(), Ast::make< UndefLiteral >( @$ ), Token::unresolved() );
  }
;


MaybeInitially
: EQUAL LCURPAREN Initializers RCURPAREN
  {
      $$ = Ast::make< Initially >( @$, $1, $2, $3, $4 );
  }
| %empty
  {
      const auto initializers = Ast::make< Initializers >( @$ );
      $$ = Ast::make< Initially >( @$, Token::unresolved(), Token::unresolved(), initializers, Token::unresolved() );
  }
;


Initializers
: Initializers COMMA Initializer
  {
      auto initializers = $1;
      $3->setDelimiterToken( $2 );
      initializers->add( $3 );
      $$ = initializers;
  }
| Initializer
  {
      auto initializers = Ast::make< Initializers >( @$ );
      initializers->add( $1 );
      $$ = initializers;
  }
;


Initializer
: Term
  {
      const auto arguments = Ast::make< Expressions >( @$ );
      $$ = Ast::make< Initializer >( @$, Token::unresolved(), arguments, Token::unresolved(), Token::unresolved(), $1 );
  }
| LPAREN Term RPAREN MAPS Term
  {
      auto arguments = Ast::make< Expressions >( @$ );
      arguments->add( $2 );
      $$ = Ast::make< Initializer >( @$, $1, arguments, $3, $4, $5 );
  }
| TupleLiteral MAPS Term
  {
      const auto arguments = $1->expressions();
      const auto lbToken = $1->leftBracket();
      const auto rbToken = $1->rightBracket();
      $$ = Ast::make< Initializer >( @$, lbToken, arguments, rbToken, $2, $3 );
  }
;


//
// Identifiers
//

Identifier
: IDENTIFIER
  {
      $$ = $1;
  }
| IN // allow in keyword as identifier
  {
      $$ = Ast::make< Identifier >( @$, "in" );
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
      $$ = Ast::make< IdentifierPath >( @$, $1 );
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
      const auto unresolvedType = Ast::make< UnresolvedType >( @$ );
      $$ = Ast::make< VariableDefinition >( @$, $1, Token::unresolved(), unresolvedType );
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
      auto variables = Ast::make< VariableDefinitions >( @$ );
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
      auto typedVariables = Ast::make< VariableDefinitions >( @$ );
      typedVariables->add( $1 );
      $$ = typedVariables;
  }
;


TypedVariable
: Identifier COLON Type
  {
      auto variable = Ast::make< VariableDefinition >( @$, $1, $2, $3 );
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
      auto variableBindings = Ast::make< VariableBindings >( @$ );
      variableBindings->add( $1 );
      $$ = variableBindings;
  }
;

VariableBinding
: AttributedVariable EQUAL Term
  {
      $$ = Ast::make< VariableBinding >( @$, $1, $2, $3 );
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
      auto definitions = Ast::make< FunctionDefinitions >( @$ );
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
      $$ = Ast::make< FunctionDefinition >( @$, Token::unresolved(), $1, $2, $3, $4, $5, $6, $7 );
      $$->setClassification( FunctionDefinition::Classification::LOCAL );

      // apply the name of the function declaration to the initializer functions
      const auto initially = $$->initially();
      for( auto& initializer : *initially->initializers() )
      {
          initializer->setFunction( $$ );
      }
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
      auto attributes = Ast::make< Attributes >( @$ );
      attributes->add( $1 );
      $$ = attributes;
  }
;

Attribute
: LSQPAREN BasicAttribute RSQPAREN
  {
      auto attribute = $2;
      $2->setLeftBrace( $1 );
      $2->setRightBrace( $3 );
      $$ = attribute;
  }
| LSQPAREN ExpressionAttribute RSQPAREN
  {
      auto attribute = $2;
      $2->setLeftBrace( $1 );
      $2->setRightBrace( $3 );
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
      $$ = Ast::make< BasicAttribute >( @$, $1 );
  }
;

ExpressionAttribute
: Identifier Term
  {
      $$ = Ast::make< ExpressionAttribute >( @$, $1, $2 );
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
