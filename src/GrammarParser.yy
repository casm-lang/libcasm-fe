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

%skeleton "lalr1.cc"
%require "3.0"
//%debug

%defines
%define api.namespace {libcasm_fe}
%define parser_class_name {Parser}

%define api.token.constructor
%define api.value.type variant
%define api.location.type {SourceLocation}

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
        class SourceLocation;
    }

    #include "Specification.h"
    #include "ast/Definition.h"
    #include "ast/Expression.h"
    #include "ast/Rule.h"

    using namespace libcasm_fe;
    using namespace Ast;

    #define YY_NULLPTR nullptr
}

%parse-param { Logger& log }
%parse-param { Lexer& lexer }
%parse-param { Specification& specification }

%code
{
    #include "SourceLocation.h"
    #include "Lexer.h"
    #include "Exception.h"
    #include "Logger.h"

    #include <libstdhl/Type>

    #undef yylex
    #define yylex lexer.nextToken

    static BasicType::Ptr createVoidType( SourceLocation& sourceLocation )
    {
        const auto type = libstdhl::Memory::get< libcasm_ir::VoidType >();
        const auto name = Ast::make< Identifier >( sourceLocation, type->description() );
        const auto path = Ast::make< IdentifierPath >( sourceLocation, name );
        const auto node = Ast::make< BasicType >( sourceLocation, path );
        node->setType( type );
        return node;
    }

    static BasicType::Ptr createRuleRefType( SourceLocation& sourceLocation )
    {
        const auto type = libstdhl::Memory::get< libcasm_ir::RuleReferenceType >();
        const auto name = Ast::make< Identifier >( sourceLocation, type->description() );
        const auto path = Ast::make< IdentifierPath >( sourceLocation, name );
        const auto node = Ast::make< BasicType >( sourceLocation, path );
        node->setType( type );
        return node;
    }

    static BasicType::Ptr createAgentType( SourceLocation& sourceLocation )
    {
        const auto name = Ast::make< Identifier >( sourceLocation, "Agent" );
        const auto path = Ast::make< IdentifierPath >( sourceLocation, name );
        const auto node = Ast::make< BasicType >( sourceLocation, path );
        return node;
    }

    static FunctionDefinition::Ptr createProgramFunction( SourceLocation& sourceLocation )
    {
        const auto agentType = createAgentType( sourceLocation );
        const auto ruleRefType = createRuleRefType( sourceLocation );

        const auto argTypes = Ast::make< Types >( sourceLocation );
        argTypes->add( agentType );

        const auto program = Ast::make< Identifier >( sourceLocation, "program" );
        return Ast::make< FunctionDefinition >( sourceLocation, program, argTypes, ruleRefType );
    }

    static IdentifierPath::Ptr asIdentifierPath( const Identifier::Ptr& identifier )
    {
        const auto& location = identifier->sourceLocation();
        return Ast::make< IdentifierPath >( location, identifier );
    }

    static Rule::Ptr wrapInBlockRule( const Rule::Ptr& rule )
    {
        if( rule == nullptr )
        {
            // this can happen while recovering from a syntax error
            return nullptr;
        }

        if( (rule->id() == Node::ID::BLOCK_RULE )
                or (rule->id() == Node::ID::SEQUENCE_RULE ) )
        {
            return rule; // no need to wrap it
        }

        const auto& sourceLocation = rule->sourceLocation();
        const auto rules = Ast::make< Rules >( sourceLocation );
        rules->add( rule );
        return Ast::make< BlockRule >( sourceLocation, rules );
    }
}


%token
END       0 "end of file"
{{grammartoken}}
;

%token <std::string> BINARY      "binary"
%token <std::string> HEXADECIMAL "hexadecimal"
%token <std::string> INTEGER     "integer"
%token <std::string> RATIONAL    "rational"
%token <std::string> DECIMAL     "decimal"
%token <std::string> STRING      "string"
%token <std::string> IDENTIFIER  "identifier"

%type <Specification::Ptr> Specification

%type <Identifier::Ptr> Identifier
%type <Identifiers::Ptr> DotSeparatedIdentifiers
%type <IdentifierPath::Ptr> IdentifierPath

// definitions
%type <Definition::Ptr> Definition AttributedDefinition
%type <Definitions::Ptr> Definitions
%type <HeaderDefinition::Ptr> Header
%type <VariableDefinition::Ptr> Variable TypedVariable AttributedVariable TypedAttributedVariable
%type <VariableDefinitions::Ptr> TypedVariables
%type <FunctionDefinition::Ptr> FunctionDefinition
%type <DerivedDefinition::Ptr> DerivedDefinition
%type <RuleDefinition::Ptr> RuleDefinition
%type <EnumeratorDefinition::Ptr> EnumeratorDefinition
%type <Enumerators::Ptr> Enumerators
%type <EnumerationDefinition::Ptr> EnumerationDefinition
%type <UsingDefinition::Ptr> UsingDefinition

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

// rules
%type <Rule::Ptr> Rule
%type <Rules::Ptr> Rules
%type <SkipRule::Ptr> SkipRule
%type <ConditionalRule::Ptr> ConditionalRule
%type <CaseRule::Ptr> CaseRule
%type <LetRule::Ptr> LetRule
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
%type <ComposedType::Ptr> ComposedType TupleType RecordType
%type <TemplateType::Ptr> TemplateType
%type <RelationType::Ptr> RelationType
%type <FixedSizedType::Ptr> FixedSizedType

// attributes
%type <Attribute::Ptr> Attribute
%type <Attributes::Ptr> Attributes
%type <BasicAttribute::Ptr> BasicAttribute
%type <ExpressionAttribute::Ptr> ExpressionAttribute

// other
%type <FunctionDefinition::Ptr> ProgramFunctionDefinition
%type <Case::Ptr> CaseLabel
%type <Cases::Ptr> CaseLabels
%type <UpdateRule::Ptr> Initializer
%type <UpdateRules::Ptr> Initializers MaybeInitializers MaybeInitially
%type <Expression::Ptr> MaybeDefined
%type <Types::Ptr> FunctionParameters MaybeFunctionParameters
%type <Expressions::Ptr> Arguments
%type <VariableDefinitions::Ptr> Parameters MaybeParameters AttributedVariables
%type <VariableBinding::Ptr> VariableBinding
%type <VariableBindings::Ptr> VariableBindings


%start Specification

// prefer absolute over relative paths
%precedence ABSOLUTE_PATH
%precedence DOUBLECOLON

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
      specification.setHeader( $1 );
      specification.setDefinitions( $2 );
  }
;


Header
: Attributes CASM
  {
      auto definition = Ast::make< HeaderDefinition >( @$, @$ );
      definition->setAttributes( $1 );
      $$ = definition;
  }
| CASM
  {
      $$ = Ast::make< HeaderDefinition >( @$, @$ );
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
: EnumerationDefinition
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
;


EnumerationDefinition
: ENUMERATION Identifier EQUAL LCURPAREN Enumerators RCURPAREN
  {
      $$ = Ast::make< EnumerationDefinition >( @$, $2, $5 );
  }
;


DerivedDefinition
: DERIVED Identifier MaybeParameters MAPS Type EQUAL Term
  {
      $$ = Ast::make< DerivedDefinition >( @$, $2, $3, $5, $7 );
  }
;


RuleDefinition
: RULE Identifier MaybeParameters EQUAL Rule
  {
      $$ = Ast::make< RuleDefinition >( @$, $2, $3, createVoidType( @$ ),
                                   wrapInBlockRule( $5 ) );
  }
| RULE Identifier MaybeParameters MAPS Type EQUAL Rule
  {
      $$ = Ast::make< RuleDefinition >( @$, $2, $3, $5,
                                   wrapInBlockRule( $7 ) );
  }
;


FunctionDefinition
: FUNCTION Identifier COLON MaybeFunctionParameters MAPS Type MaybeDefined MaybeInitially
  {
      const auto identifier = $2;

      auto function = Ast::make< FunctionDefinition >( @$, identifier, $4, $6 );
      function->setDefaultValue( $7 );

      // apply the name of the function declaration to the initializer functions
      auto initializers = $8;
      for (auto& initializer : *initializers) {
          initializer->function()->setIdentifier( asIdentifierPath( identifier ) );
      }
      function->setInitializers( initializers );

      $$ = function;
  }
| ProgramFunctionDefinition
  {
      $$ = $1; // `init` special case
  }
;


ProgramFunctionDefinition
: INIT IdentifierPath
  {
      const auto singleAgentIdentifier = Ast::make< Identifier >( @$, "$" );
      auto singleAgentArguments = libcasm_fe::Ast::make< Expressions >( @$ );
      const auto singleAgent = libcasm_fe::Ast::make< DirectCallExpression >(
          @$, asIdentifierPath( singleAgentIdentifier ), singleAgentArguments );
      singleAgent->setTargetType( DirectCallExpression::TargetType::CONSTANT );

      auto programDefinition = createProgramFunction( @$ );
      auto programArguments = libcasm_fe::Ast::make< Expressions >( @$ );
      programArguments->add( singleAgent );
      const auto program = libcasm_fe::Ast::make< DirectCallExpression >(
          @$, asIdentifierPath( programDefinition->identifier() ), programArguments );

      const auto ruleReference = Ast::make< ReferenceLiteral >( @$, $2 );

      auto initializers = Ast::make< UpdateRules >( @$ );
      initializers->add( Ast::make< UpdateRule >( @$, program, ruleReference ) );
      programDefinition->setInitializers( initializers );

      $$ = programDefinition;
  }
| INIT LCURPAREN MaybeInitializers RCURPAREN
  {
      auto programDefinition = createProgramFunction( @$ );

      // apply the name of the program declaration to the initializer functions
      auto initializers = $3;
      for (auto& initializer : *initializers) {
          initializer->function()->setIdentifier(
              asIdentifierPath( programDefinition->identifier() ) );
      }
      programDefinition->setInitializers( initializers );

      $$ = programDefinition;
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
      $$ = Ast::make< UsingDefinition >( @$, $2, $4 );
  }
;


//
// Rules
//

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


SkipRule
: SKIP
  {
      $$ = Ast::make< SkipRule >( @$ );
  }
;


ConditionalRule
: IF Term THEN Rule
  {
      $$ = Ast::make< ConditionalRule >( @$, $2, $4 );
  }
| IF Term THEN Rule ELSE Rule
  {
      $$ = Ast::make< ConditionalRule >( @$, $2, $4, $6 );
  }
;


CaseRule
: CASE Term OF LCURPAREN CaseLabels RCURPAREN
  {
      $$ = Ast::make< CaseRule >( @$, $2, $5 );
  }
| CASE Term OF LCURPAREN error RCURPAREN // error recovery
  {
      $$ = nullptr;
  }
;


CaseLabel
: DEFAULT COLON Rule
  {
      $$ = Ast::make< DefaultCase >( @$, $3 );
  }
| UNDERLINE COLON Rule
  {
      $$ = Ast::make< DefaultCase >( @$, $3 );
  }
| Term COLON Rule
  {
      $$ = Ast::make< ExpressionCase >( @$, $1, $3 );
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


LetRule
: LET VariableBindings IN Rule
  {
      $$ = Ast::make< LetRule >( @$, $2, $4 );
  }
;


ForallRule
: FORALL AttributedVariables IN Term DO Rule
  {
      $$ = Ast::make< ForallRule >( @$, $2, $4, $6 );
  }
| FORALL AttributedVariables IN Term WITH Term DO Rule
  {
      $$ = Ast::make< ForallRule >( @$, $2, $4, $6, $8 );
  }
;


ChooseRule
: CHOOSE AttributedVariables IN Term DO Rule
  {
      $$ = Ast::make< ChooseRule >( @$, $2, $4, $6 );
  }
;


IterateRule
: ITERATE Rule
  {
      $$ = Ast::make< IterateRule >( @$, $2 );
  }
;


BlockRule
: LCURPAREN Rules RCURPAREN
  {
      $$ = Ast::make< BlockRule >( @$, $2 );
  }
| PAR Rules ENDPAR
  {
      $$ = Ast::make< BlockRule >( @$, $2 );
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
      $$ = Ast::make< SequenceRule >( @$, $2 );
  }
| SEQ Rules ENDSEQ
  {
      $$ = Ast::make< SequenceRule >( @$, $2 );
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
      $$ = Ast::make< UpdateRule >( @$, $1, $3 );
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
      $$ = Ast::make< WhileRule >( @$, $2, $4 );
  }
;


//
// Terms
//

Terms
: Terms COMMA Term
  {
      auto expressions = $1;
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
;


SimpleOrClaspedTerm
: LPAREN Term RPAREN
  {
      $$ = $2;
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
      $$ = $2;
  }
| MINUS SimpleOrClaspedTerm %prec UMINUS
  {
      $$ = Ast::make< UnaryExpression >( @$, $2, libcasm_ir::Value::INV_INSTRUCTION );
  }
;


//
// Operator Expression
//

OperatorExpression
: Term PLUS Term
  {
      $$ = Ast::make< BinaryExpression >( @$, $1, $3, libcasm_ir::Value::ADD_INSTRUCTION );
  }
| Term MINUS Term
  {
      $$ = Ast::make< BinaryExpression >( @$, $1, $3, libcasm_ir::Value::SUB_INSTRUCTION );
  }
| Term ASTERIX Term
  {
      $$ = Ast::make< BinaryExpression >( @$, $1, $3, libcasm_ir::Value::MUL_INSTRUCTION );
  }
| Term SLASH Term
  {
      $$ = Ast::make< BinaryExpression >( @$, $1, $3, libcasm_ir::Value::DIV_INSTRUCTION );
  }
| Term PERCENT Term
  {
      $$ = Ast::make< BinaryExpression >( @$, $1, $3, libcasm_ir::Value::MOD_INSTRUCTION );
  }
| Term CARET Term
  {
      $$ = Ast::make< BinaryExpression >( @$, $1, $3, libcasm_ir::Value::POW_INSTRUCTION );
  }
| Term NEQUAL Term
  {
      $$ = Ast::make< BinaryExpression >( @$, $1, $3, libcasm_ir::Value::NEQ_INSTRUCTION );
  }
| Term EQUAL Term
  {
      $$ = Ast::make< BinaryExpression >( @$, $1, $3, libcasm_ir::Value::EQU_INSTRUCTION );
  }
| Term LESSER Term
  {
      $$ = Ast::make< BinaryExpression >( @$, $1, $3, libcasm_ir::Value::LTH_INSTRUCTION );
  }
| Term GREATER Term
  {
      $$ = Ast::make< BinaryExpression >( @$, $1, $3, libcasm_ir::Value::GTH_INSTRUCTION );
  }
| Term LESSEQ Term
  {
      $$ = Ast::make< BinaryExpression >( @$, $1, $3, libcasm_ir::Value::LEQ_INSTRUCTION );
  }
| Term GREATEREQ Term
  {
      $$ = Ast::make< BinaryExpression >( @$, $1, $3, libcasm_ir::Value::GEQ_INSTRUCTION );
  }
| Term OR Term
  {
      $$ = Ast::make< BinaryExpression >( @$, $1, $3, libcasm_ir::Value::OR_INSTRUCTION );
  }
| Term XOR Term
  {
      $$ = Ast::make< BinaryExpression >( @$, $1, $3, libcasm_ir::Value::XOR_INSTRUCTION );
  }
| Term AND Term
  {
      $$ = Ast::make< BinaryExpression >( @$, $1, $3, libcasm_ir::Value::AND_INSTRUCTION );
  }
| Term ARROW Term
  {
      $$ = Ast::make< BinaryExpression >( @$, $1, $3, libcasm_ir::Value::IMP_INSTRUCTION );
  }
| Term IMPLIES Term
  {
      $$ = Ast::make< BinaryExpression >( @$, $1, $3, libcasm_ir::Value::IMP_INSTRUCTION );
  }
| NOT Term
  {
      $$ = Ast::make< UnaryExpression >( @$, $2, libcasm_ir::Value::NOT_INSTRUCTION );
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
| IdentifierPath Arguments
  {
      $$ = Ast::make< DirectCallExpression >( @$, $1, $2 );
  }
;


MethodCallExpression
: SimpleOrClaspedTerm DOT Identifier %prec CALL_WITHOUT_ARGS
  {
      const auto arguments = Ast::make< Expressions >( @$ );
      $$ = Ast::make< MethodCallExpression >( @$, $1, $3, arguments );
  }
| SimpleOrClaspedTerm DOT Identifier Arguments
  {
      $$ = Ast::make< MethodCallExpression >( @$, $1, $3, $4 );
  }
;


LiteralCallExpression
: SimpleOrClaspedTerm DOT IntegerLiteral
  {
      $$ = Ast::make< LiteralCallExpression >( @$, $1, $3 );
  }
;


IndirectCallExpression
: CallExpression Arguments
  {
      $$ = Ast::make< IndirectCallExpression >( @$, $1, $2 );
  }
;


TypeCastingExpression
: SimpleOrClaspedTerm AS Type
  {
      $$ = Ast::make< TypeCastingExpression >( @$, $1, $3 );
  }
;


LetExpression
: LET VariableBindings IN Term
  {
      $$ = Ast::make< LetExpression >( @$, $2, $4 );
  }
;


ConditionalExpression
: IF Term THEN Term ELSE Term
  {
      $$ = Ast::make< ConditionalExpression >( @$, $2, $4, $6 );
  }
;


ChooseExpression
: CHOOSE AttributedVariables IN Term DO Term
  {
      $$ = Ast::make< ChooseExpression >( @$, $2, $4, $6 );
  }
;


UniversalQuantifierExpression
: FORALL AttributedVariables IN Term HOLDS Term
  {
      $$ = Ast::make< UniversalQuantifierExpression >( @$, $2, $4, $6 );
  }
;


ExistentialQuantifierExpression
: EXISTS AttributedVariables IN Term WITH Term
  {
      $$ = Ast::make< ExistentialQuantifierExpression >( @$, $2, $4, $6 );
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
  }
;


BooleanLiteral
: TRUE
  {
      const auto value = libstdhl::Memory::get< libcasm_ir::BooleanConstant >( true );
      $$ = Ast::make< ValueLiteral >( @$, value );
  }
| FALSE
  {
      const auto value = libstdhl::Memory::get< libcasm_ir::BooleanConstant >( false );
      $$ = Ast::make< ValueLiteral >( @$, value );
  }
;


IntegerLiteral
: INTEGER
  {
      try
      {
          const auto value = libstdhl::Memory::get< libcasm_ir::IntegerConstant >( $1, libstdhl::Type::DECIMAL );
          $$ = Ast::make< ValueLiteral >( @$, value );
      }
      catch( const std::domain_error& e )
      {
          throw syntax_error( @$, e.what() );
      }
  }
;


RationalLiteral
: RATIONAL
  {
      try
      {
          const auto value = libstdhl::Memory::get< libcasm_ir::RationalConstant >( $1 );
          $$ = Ast::make< ValueLiteral >( @$, value );
      }
      catch( const std::domain_error& e )
      {
          throw syntax_error( @$, e.what() );
      }
  }
;


DecimalLiteral
: DECIMAL
  {
      try
      {
          const auto value = libstdhl::Memory::get< libcasm_ir::DecimalConstant >( $1 );
          $$ = Ast::make< ValueLiteral >( @$, value );
      }
      catch( const std::domain_error& e )
      {
          throw syntax_error( @$, e.what() );
      }
  }
;


BinaryLiteral
: BINARY
  {
      try
      {
          const auto value = libstdhl::Memory::get< libcasm_ir::BinaryConstant >( $1, libstdhl::Type::BINARY );
          $$ = Ast::make< ValueLiteral >( @$, value );
      }
      catch( const std::domain_error& e )
      {
          throw syntax_error( @$, e.what() );
      }
  }
| HEXADECIMAL
  {
      try
      {
          const auto value = libstdhl::Memory::get< libcasm_ir::BinaryConstant >( $1, libstdhl::Type::HEXADECIMAL );
          $$ = Ast::make< ValueLiteral >( @$, value );
      }
      catch( const std::domain_error& e )
      {
          throw syntax_error( @$, e.what() );
      }
  }
;


StringLiteral
: STRING
  {
      try
      {
          const auto value = libstdhl::Memory::get< libcasm_ir::StringConstant >( $1 );
          $$ = Ast::make< ValueLiteral >( @$, value );
      }
      catch( const std::domain_error& e )
      {
          throw syntax_error( @$, e.what() );
      }
  }
;


ReferenceLiteral
: AT IdentifierPath
  {
      $$ = Ast::make< ReferenceLiteral >( @$, $2 );
  }
;


ListLiteral
: LSQPAREN RSQPAREN
  {
      const auto expressions = Ast::make< Expressions >( @$ );
      $$ = Ast::make< ListLiteral >( @$, expressions );
  }
| LSQPAREN Terms RSQPAREN
  {
      $$ = Ast::make< ListLiteral >( @$, $2 );
  }
| LSQPAREN error RSQPAREN // error recovery
  {
      $$ = nullptr;
  }
;


RangeLiteral
: LSQPAREN Term DOTDOT Term RSQPAREN
  {
      $$ = Ast::make< RangeLiteral >( @$, $2, $4 );
  }
;

TupleLiteral
: LPAREN Terms COMMA Term RPAREN
  {
      const auto expressions = $2;
      expressions->add( $4 );
      $$ = Ast::make< TupleLiteral >( @$, expressions );
  }

RecordLiteral
: LPAREN Assignments RPAREN
  {
      $$ = Ast::make< RecordLiteral >( @$, $2 );
  }
;

Assignments
: Assignments COMMA Assignment
  {
      auto assignments = $1;
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
      $$ = Ast::make< NamedExpression >( @$, $1, $3 );
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
| ComposedType
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
: IdentifierPath %prec ABSOLUTE_PATH
  {
      $$ = Ast::make< BasicType >( @$, $1 );
  }
;


ComposedType
: TupleType
  {
      $$ = $1;
  }
| RecordType
  {
      $$ = $1;
  }
;

TupleType
: LPAREN Types COMMA Type RPAREN
  {
      const auto identifier = Ast::make< Identifier >( @$, "Tuple" );
      auto subTypes = $2;
      subTypes->add( $4 );
      $$ = Ast::make< ComposedType >( @$, asIdentifierPath( identifier ), subTypes );
  }
;

RecordType
: LPAREN TypedVariables COMMA TypedVariable RPAREN
  {
      const auto identifier = Ast::make< Identifier >( @$, "Record" );
      auto namedSubTypes = $2;
      namedSubTypes->add( $4 );

      auto identifiers = Ast::make< Identifiers >( @$ );
      auto subTypes = Ast::make< Types >( @$ );
      for( const auto& namedSubType : *namedSubTypes )
      {
          identifiers->add( namedSubType->identifier() );
          subTypes->add( namedSubType->variableType() );
      }

      $$ = Ast::make< ComposedType >( @$, asIdentifierPath( identifier ), subTypes, identifiers );
  }
;


TemplateType
: IdentifierPath LESSER Types GREATER
  {
      $$ = Ast::make< TemplateType >( @$, $1, $3 );
  }
;


RelationType
: IdentifierPath LESSER MaybeFunctionParameters MAPS Type GREATER
  {
      $$ = Ast::make< RelationType >( @$, $1, $3, $5 );
  }
;


FixedSizedType
: IdentifierPath MARK Term
  {
      $$ = Ast::make< FixedSizedType >( @$, $1, $3 );
  }
;


//
// Arguments
//

Arguments
: LPAREN Terms RPAREN
  {
      $$ = $2;
  }
| LPAREN error RPAREN // error recovery
  {
      $$ = nullptr;
  }
| LPAREN RPAREN
  {
      const auto expressions = Ast::make< Expressions >( @$ );
      $$ = expressions;
  }
;



//
// FunctionParameters (Relation) and Parameters
//

FunctionParameters
: FunctionParameters ASTERIX Type
  {
      auto types = $1;
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


MaybeParameters
: LPAREN Parameters RPAREN
  {
      $$ = $2;
  }
| LPAREN error RPAREN // error recovery
  {
      $$ = nullptr;
  }
| %empty
  {
      $$ = Ast::make< NodeList< VariableDefinition > >( @$ );
  }
;


//
// Defined, Initially and Initializers
//

MaybeDefined
: DEFINED LCURPAREN Term RCURPAREN
  {
      $$ = $3;
  }
| %empty
  {
      $$ = Ast::make< UndefLiteral >( @$ );
  }
;


MaybeInitially
: INITIALLY LCURPAREN MaybeInitializers RCURPAREN
  {
      $$ = $3;
  }
| %empty
  {
      $$ = Ast::make< UpdateRules >( @$ );
  }
;


Initializers
: Initializers COMMA Initializer
  {
      auto initializers = $1;
      initializers->add( $3 );
      $$ = initializers;
  }
| Initializer
  {
      auto initializers = Ast::make< UpdateRules >( @$ );
      initializers->add( $1 );
      $$ = initializers;
  }
;


Initializer
: Term
  {
      // the unknown function identifier will be replaced in FunctionDefinition
      const auto arguments = Ast::make< Expressions >( @$ );
      const auto function = Ast::make< DirectCallExpression >( @$, nullptr, arguments );
      $$ = Ast::make< UpdateRule >( @$, function, $1 );
  }
| LPAREN Term RPAREN MAPS Term
  {
      auto arguments = Ast::make< Expressions >( @$ );
      arguments->add( $2 );

      // the unknown function identifier will be replaced in FunctionDefinition
      const auto function = Ast::make< DirectCallExpression >( @$, nullptr, arguments );
      $$ = Ast::make< UpdateRule >( @$, function, $5 );
  }
| TupleLiteral MAPS Term
  {
      // the unknown function identifier will be replaced in FunctionDefinition
      const auto function = Ast::make< DirectCallExpression >( @$, nullptr, $1->expressions() );
      $$ = Ast::make< UpdateRule >( @$, function, $3 );
  }
;


MaybeInitializers
: Initializers
  {
      $$ = $1;
  }
| %empty
  {
      $$ = Ast::make< UpdateRules >( @$ );
  }
;


//
// Identifiers
//

Identifier
: IDENTIFIER
  {
      $$ = Ast::make< Identifier >( @$, $1 );
  }
| IN // allow in keyword as identifier
  {
      $$ = Ast::make< Identifier >( @$, "in" );
  }
;


IdentifierPath
: DotSeparatedIdentifiers %prec ABSOLUTE_PATH
  {
      $$ = Ast::make< IdentifierPath >( @$, $1, IdentifierPath::Type::ABSOLUTE );
  }
| DOUBLECOLON Identifier
  {
      auto identifiers = Ast::make< Identifiers >( @$ );
      identifiers->add( $2 );
      $$ = Ast::make< IdentifierPath >( @$, identifiers, IdentifierPath::Type::RELATIVE );
  }
;


DotSeparatedIdentifiers
: DotSeparatedIdentifiers DOUBLECOLON Identifier
  {
      auto identifiers = $1;
      identifiers->add( $3 );
      $$ = identifiers;
  }
| Identifier
  {
      auto identifiers = Ast::make< Identifiers >( @$ );
      identifiers->add( $1 );
      $$ = identifiers;
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
      $$ = Ast::make< VariableDefinition >( @$, $1, unresolvedType );
  }
;


AttributedVariables
: AttributedVariables COMMA AttributedVariable
  {
      auto variables = $1;
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
      $$ = Ast::make< VariableDefinition >( @$, $1, $3 );
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


VariableBinding
: AttributedVariable EQUAL Term
  {
      $$ = Ast::make< VariableBinding >( @$, $1, $3 );
  }
;


VariableBindings
: VariableBindings COMMA VariableBinding
  {
      auto variableBindings = $1;
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
      $$ = $2;
  }
| LSQPAREN ExpressionAttribute RSQPAREN
  {
      $$ = $2;
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

void Parser::error( const SourceLocation& location, const std::string& message )
{
    log.error( {location}, message, Code::SyntaxError );
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
