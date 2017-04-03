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
//  along with this program. If not, see <http://www.gnu.org/licenses/>.
//

%skeleton "lalr1.cc"
%require "3.0"
//%debug

%defines
%define api.namespace {libcasm_fe}
%define parser_class_name {Parser}

%define api.token.constructor
%define api.value.type variant
%define api.location.type {Location}

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
        class Location;
    }

    #include "src/ast/Specification.h"

    using namespace libcasm_fe;
    using namespace Ast;

    #define YY_NULLPTR nullptr
}

%parse-param { Logger& log }
%parse-param { Lexer& lexer }
%parse-param { const std::string& filePath }
%parse-param { Specification::Ptr& result }

%code
{
    #include "src/Location.h"
    #include "src/Lexer.h"
    #include "src/Exceptions.h"
    #include "src/Logger.h"

    #include "../stdhl/cpp/Type.h"

    #undef yylex
    #define yylex lexer.nextToken

    static BasicType::Ptr createVoidType( Location& sourceLocation )
    {
        const auto type = libstdhl::get< libcasm_ir::VoidType >();
        const auto name = libcasm_fe::Ast::make< IdentifierNode >( sourceLocation, type->description() );
        const auto node = libcasm_fe::Ast::make< BasicType >( sourceLocation, name );
        node->setType( type );
        return node;
    }

    static BasicType::Ptr createRuleRefType( Location& sourceLocation )
    {
        const auto type = libstdhl::get< libcasm_ir::RuleReferenceType >();
        const auto name = libcasm_fe::Ast::make< IdentifierNode >( sourceLocation, type->description() );
        const auto node = libcasm_fe::Ast::make< BasicType >( sourceLocation, name );
        node->setType( type );
        return node;
    }

    static BasicType::Ptr createAgentType( Location& sourceLocation )
    {
        const auto name = libcasm_fe::Ast::make< IdentifierNode >( sourceLocation, "Agent" );
        const auto node = libcasm_fe::Ast::make< BasicType >( sourceLocation, name );
        return node;
    }

    static FunctionDefinition::Ptr createProgramFunction( Location& sourceLocation )
    {
        const auto agentType = createAgentType( sourceLocation );
        const auto ruleRefType = createRuleRefType( sourceLocation );

        const auto argTypes = libcasm_fe::Ast::make< Types >( sourceLocation );
        argTypes->add( agentType );

        const auto program = libcasm_fe::Ast::make< IdentifierNode >( sourceLocation, "program" );
        return libcasm_fe::Ast::make< FunctionDefinition >( sourceLocation, program, argTypes, ruleRefType );
    }

    static DirectCallExpression::Ptr createSelfBuiltinCall( Location& sourceLocation )
    {
        const auto self = libcasm_fe::Ast::make< IdentifierNode >( sourceLocation, "self" );
        const auto arguments = libcasm_fe::Ast::make< Expressions >( sourceLocation );
        return libcasm_fe::Ast::make< DirectCallExpression >( sourceLocation, self, arguments );
    }

    static Rule::Ptr wrapInBlockRule( const Rule::Ptr& rule )
    {
        if( (rule->id() == Node::ID::BLOCK_RULE )
                or (rule->id() == Node::ID::SEQUENCE_RULE ) )
        {
            return rule; // no need to wrap it
        }

        const auto& sourceLocation = rule->sourceLocation();
        const auto rules = libcasm_fe::Ast::make< Rules >( sourceLocation );
        rules->add( rule );
        return libcasm_fe::Ast::make< BlockRule >( sourceLocation, rules );
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
%token <std::string> FLOATING    "floating"
%token <std::string> STRING      "string"
%token <std::string> IDENTIFIER  "identifier"

%type <Specification::Ptr> Specification

%type <IdentifierNode::Ptr> Identifier
%type <NodeList< IdentifierNode >::Ptr> Identifiers

// definitions
%type <Definition::Ptr> Definition AttributedDefinition
%type <Definitions::Ptr> Definitions
%type <VariableDefinition::Ptr> Variable
%type <FunctionDefinition::Ptr> FunctionDefinition
%type <DerivedDefinition::Ptr> DerivedDefinition
%type <RuleDefinition::Ptr> RuleDefinition
%type <EnumerationDefinition::Ptr> EnumerationDefinition

// expressions
%type <Expression::Ptr> Expression Term Atom
%type <Expressions::Ptr> Terms
%type <ValueAtom::Ptr> Boolean String BitNumber IntegerNumber FloatingNumber RationalNumber
%type <RuleReferenceAtom::Ptr> RuleReference
%type <UndefAtom::Ptr> Undefined
%type <RangeExpression::Ptr> Range
%type <ListExpression::Ptr> List
%type <DirectCallExpression::Ptr> DirectCallExpression
%type <IndirectCallExpression::Ptr> IndirectCallExpression
%type <ConditionalExpression::Ptr> ConditionalExpression
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
%type <IterateRule::Ptr> IterateRule
%type <BlockRule::Ptr> BlockRule
%type <SequenceRule::Ptr> SequenceRule
%type <UpdateRule::Ptr> UpdateRule
%type <CallRule::Ptr> CallRule

// types
%type <Type::Ptr> Type
%type <Types::Ptr> Types
%type <BasicType::Ptr> BasicType
%type <ComposedType::Ptr> ComposedType
%type <FixedSizedType::Ptr> FixedSizedType
%type <RangedType::Ptr> RangedType

// types
%type <Attribute::Ptr> Attribute
%type <Attributes::Ptr> Attributes
%type <BasicAttribute::Ptr> BasicAttribute
%type <ExpressionAttribute::Ptr> ExpressionAttribute

// other
%type <FunctionDefinition::Ptr> ProgramFunctionDefinition
%type <Case::Ptr> CaseLabel
%type <Cases::Ptr> CaseLabels
%type <UpdateRule::Ptr> Initializer
%type <NodeList< UpdateRule >::Ptr> Initializers MaybeInitializers MaybeInitially
%type <Expression::Ptr> MaybeDefined
%type <Types::Ptr> FunctionParameters MaybeFunctionParameters
%type <Expressions::Ptr> Arguments
%type <NodeList< VariableDefinition >::Ptr> Parameters MaybeParameters


%start Specification

%precedence THEN
%precedence ELSE

%precedence UPDATE

%left IMPLIES
%left OR
%left XOR
%left AND

%left EQUAL NEQUAL
%left GREATEREQ LESSEQ GREATER LESSER

%left PLUS MINUS
%left PERCENT SLASH ASTERIX
%left CARET

%precedence UPLUS UMINUS
%precedence NOT

%precedence LPAREN
%precedence DIRECT_CALL_EXPR_NO_ARG

%precedence HOLDS WITH

%%

Specification
: CASM Definitions
  {
      const std::string& fileName = filePath.substr( filePath.find_last_of( "/\\" ) + 1 );
      const std::string& name = fileName.substr( 0, fileName.rfind( "." ) );

      const auto specificationName = make< IdentifierNode >( @$, name );
      result = libcasm_fe::Ast::make< Specification >( @$, specificationName, $2 );
  }
;


Definition
: FunctionDefinition
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
| EnumerationDefinition
  {
      $$ = $1;
  }
;


AttributedDefinition
: LSQPAREN Attributes RSQPAREN Definition
  {
      auto definition = $4;
      definition->setAttributes( $2 );
      $$ = definition;
  }
| Definition
  {
      $$ = $1;
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
      auto definitions = libcasm_fe::Ast::make< Definitions >( @$ );
      definitions->add( $1 );
      $$ = definitions;
  }
;


FunctionDefinition
: FUNCTION Identifier COLON MaybeFunctionParameters ARROW Type MaybeDefined MaybeInitially
  {
      const auto identifier = $2;

      auto function = libcasm_fe::Ast::make< FunctionDefinition >( @$, identifier, $4, $6 );
      function->setDefaultValue( $7 );

      // apply the name of the function declaration to the initializer functions
      auto initializers = $8;
      for (auto& initializer : *initializers) {
           initializer->function()->setIdentifier( identifier );
      }
      function->setInitializers( initializers );

      $$ = function;
  }
| ProgramFunctionDefinition
  {
      $$ = $1; // `init` special case
  }
;


MaybeInitially
: INITIALLY LCURPAREN MaybeInitializers RCURPAREN
  {
      $$ = $3;
  }
| %empty
  {
      $$ = libcasm_fe::Ast::make< NodeList< UpdateRule > >( @$ );
  }
;


MaybeDefined
: DEFINED LCURPAREN Term RCURPAREN
  {
      $$ = $3;
  }
| %empty
  {
      $$ = libcasm_fe::Ast::make< UndefAtom >( @$ );
  }
;


FunctionParameters
: FunctionParameters ASTERIX Type
  {
      auto types = $1;
      types->add( $3 );
      $$ = types;
  }
| Type
  {
      auto types = libcasm_fe::Ast::make< Types >( @$ );
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
      $$ = libcasm_fe::Ast::make< Types >( @$ );
  }
;


ProgramFunctionDefinition
: INIT Identifier
  {
      auto programDefinition = createProgramFunction( @$ );

      auto arguments = libcasm_fe::Ast::make< Expressions >( @$ );

      // single execution agent case, use 'self' built-in!
      const auto self = createSelfBuiltinCall( @$ );
      arguments->add( self );

      const auto program = libcasm_fe::Ast::make< DirectCallExpression >(
          @$, programDefinition->identifier(), arguments );

      const auto ruleReference = libcasm_fe::Ast::make< RuleReferenceAtom >( @$, $2 );

      auto initializers = libcasm_fe::Ast::make< NodeList< UpdateRule > >( @$ );
      initializers->add( libcasm_fe::Ast::make< UpdateRule >( @$, program, ruleReference ) );
      programDefinition->setInitializers( initializers );

      $$ = programDefinition;
  }
| INIT LCURPAREN MaybeInitializers RCURPAREN
  {
      auto programDefinition = createProgramFunction( @$ );

      // apply the name of the program declaration to the initializer functions
      auto initializers = $3;
      for (auto& initializer : *initializers) {
          initializer->function()->setIdentifier( programDefinition->identifier() );
      }
      programDefinition->setInitializers( initializers );

      $$ = programDefinition;
  }
;


Initializer
: Term
  {
      // the unknown function identifier will be replaced in FunctionDefinition
      const auto unknown = libcasm_fe::Ast::make< IdentifierNode >( @$, std::string() );
      const auto arguments = libcasm_fe::Ast::make< Expressions >( @$ );
      const auto function = libcasm_fe::Ast::make< DirectCallExpression >( @$, unknown, arguments );

      $$ = libcasm_fe::Ast::make< UpdateRule >( @$, function, $1 );
  }
| Term ARROW Term
  {
      auto arguments = libcasm_fe::Ast::make< Expressions >( @$ );
      arguments->add( $1 );

      // the unknown function identifier will be replaced in FunctionDefinition
      const auto unknown = libcasm_fe::Ast::make< IdentifierNode >( @$, std::string() );
      const auto function = libcasm_fe::Ast::make< DirectCallExpression >( @$, unknown, arguments );

      $$ = libcasm_fe::Ast::make< UpdateRule >( @$, function, $3 );
  }
| Arguments ARROW Term
  {
      // the unknown function identifier will be replaced in FunctionDefinition
      const auto unknown = libcasm_fe::Ast::make< IdentifierNode >( @$, std::string() );
      const auto function = libcasm_fe::Ast::make< DirectCallExpression >( @$, unknown, $1 );

      $$ = libcasm_fe::Ast::make< UpdateRule >( @$, function, $3 );
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
      auto initializers = libcasm_fe::Ast::make< NodeList< UpdateRule > >( @$ );
      initializers->add( $1 );
      $$ = initializers;
  }
;


MaybeInitializers
: Initializers
  {
      $$ = $1;
  }
| %empty
  {
      $$ = libcasm_fe::Ast::make< NodeList< UpdateRule > >( @$ );
  }
;


DerivedDefinition
: DERIVED Identifier MaybeParameters ARROW Type EQUAL Term
  {
      $$ = libcasm_fe::Ast::make< DerivedDefinition >( @$, $2, $3, $5, $7 );
  }
;


EnumerationDefinition
: ENUM Identifier EQUAL LCURPAREN Identifiers RCURPAREN
  {
      $$ = libcasm_fe::Ast::make< EnumerationDefinition >( @$, $2, $5 );
  }
;


Identifier
: IDENTIFIER
  {
      $$ = libcasm_fe::Ast::make< IdentifierNode >( @$, $1 );
  }
;


Identifiers
: Identifiers COMMA Identifier
  {
      auto identifiers = $1;
      identifiers->add( $3 );
      $$ = identifiers;
  }
| Identifier
  {
      auto identifiers = libcasm_fe::Ast::make< NodeList< IdentifierNode > >( @$ );
      identifiers->add( $1 );
      $$ = identifiers;
  }
;


Variable
: Identifier COLON Type
  {
      $$ = libcasm_fe::Ast::make< VariableDefinition >( @$, $1, $3 );
  }
| Identifier
  {
      const auto unresolvedType = libcasm_fe::Ast::make< UnresolvedType >( @$ );
      $$ = libcasm_fe::Ast::make< VariableDefinition >( @$, $1, unresolvedType );
  }
;


Parameters
: Parameters COMMA Variable
  {
      auto parameters = $1;
      parameters->add( $3 );
      $$ = parameters;
  }
| Variable
  {
      auto parameters = libcasm_fe::Ast::make< NodeList< VariableDefinition > >( @$ );
      parameters->add( $1 );
      $$ = parameters;
  }
;


MaybeParameters
: LPAREN Parameters RPAREN
  {
      $$ = $2;
  }
| %empty
  {
      $$ = libcasm_fe::Ast::make< NodeList< VariableDefinition > >( @$ );
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
| FixedSizedType
  {
      $$ = $1;
  }
| RangedType
  {
      $$ = $1;
  }
;


BasicType
: Identifier
  {
      $$ = libcasm_fe::Ast::make< BasicType >( @$, $1 );
  }
;


ComposedType
: Identifier LPAREN Types RPAREN
  {
      $$ = libcasm_fe::Ast::make< ComposedType >( @$, $1, $3 );
  }
;


FixedSizedType
: Identifier LESSER Term GREATER
  {
      $$ = libcasm_fe::Ast::make< FixedSizedType >( @$, $1, $3 );
  }
;


RangedType
: Identifier LESSER Term DOTDOT Term GREATER
  {
      $$ = libcasm_fe::Ast::make< RangedType >( @$, $1, $3, $5 );
  }
;


Types
: Types COMMA Type
  {
      auto types = $1;
      types->add( $3 );
      $$ = types;
  }
| Type
  {
      auto types = libcasm_fe::Ast::make< Types >( @$ );
      types->add( $1 );
      $$ = types;
  }
;


Atom
: RuleReference
  {
      $$ = $1;
  }
| BitNumber
  {
      $$ = $1;
  }
| IntegerNumber
  {
      $$ = $1;
  }
| FloatingNumber
  {
      $$ = $1;
  }
| RationalNumber
  {
      $$ = $1;
  }
| String
  {
      $$ = $1;
  }
| Undefined
  {
      $$ = $1;
  }
| Boolean
  {
      $$ = $1;
  }
;


Undefined
: UNDEF
  {
      $$ = libcasm_fe::Ast::make< UndefAtom >( @$ );
  }
;


Boolean
: TRUE
  {
      const auto value = libstdhl::get< libcasm_ir::BooleanConstant >( true );
      $$ = libcasm_fe::Ast::make< ValueAtom >( @$, value );
  }
| FALSE
  {
      const auto value = libstdhl::get< libcasm_ir::BooleanConstant >( false );
      $$ = libcasm_fe::Ast::make< ValueAtom >( @$, value );
  }
;


String
: STRING
  {
      const auto value = libstdhl::get< libcasm_ir::StringConstant >( $1 );
      $$ = libcasm_fe::Ast::make< ValueAtom >( @$, value );
  }
;


BitNumber
: BINARY
  {
      const auto value = libstdhl::get< libcasm_ir::BitConstant >( $1, libstdhl::Type::BINARY );
      $$ = libcasm_fe::Ast::make< ValueAtom >( @$, value );
  }
| HEXADECIMAL
  {
      const auto value = libstdhl::get< libcasm_ir::BitConstant >( $1, libstdhl::Type::HEXADECIMAL );
      $$ = libcasm_fe::Ast::make< ValueAtom >( @$, value );
  }
;


IntegerNumber
: INTEGER
  {
      const auto value = libstdhl::get< libcasm_ir::IntegerConstant >( $1, libstdhl::Type::DECIMAL );
      $$ = libcasm_fe::Ast::make< ValueAtom >( @$, value );
  }
;


FloatingNumber
: FLOATING
  {
      const auto value = libstdhl::get< libcasm_ir::FloatingConstant >( $1 );
      $$ = libcasm_fe::Ast::make< ValueAtom >( @$, value );
  }
;


RationalNumber
: RATIONAL
  {
      const auto value = libstdhl::get< libcasm_ir::RationalConstant >( $1 );
      $$ = libcasm_fe::Ast::make< ValueAtom >( @$, value );
  }
;


RuleReference
: AT IDENTIFIER
  {
      const auto ruleName = libcasm_fe::Ast::make< IdentifierNode >( @$, $2 );
      $$ = libcasm_fe::Ast::make< RuleReferenceAtom >( @$, ruleName );
  }
;


Term
: DirectCallExpression
  {
      $$ = $1;
  }
| IndirectCallExpression
  {
      $$ = $1;
  }
| ConditionalExpression
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
| Expression
  {
      $$ = $1;
  }
| List
  {
      $$ = $1;
  }
| Range
  {
      $$ = $1;
  }
| Atom
  {
      $$ = $1;
  }
;


Expression
: LPAREN Expression RPAREN
  {
      $$ = $2;
  }
| PLUS Term %prec UPLUS
  {
      $$ = $2;
  }
| LPAREN Term RPAREN
  {
      $$ = $2;
  }
| MINUS Term %prec UMINUS
  {
      $$ = libcasm_fe::Ast::make< UnaryExpression >( @$, $2, libcasm_ir::Value::INV_INSTRUCTION );
  }
| Term PLUS Term
  {
      $$ = libcasm_fe::Ast::make< BinaryExpression >( @$, $1, $3, libcasm_ir::Value::ADD_INSTRUCTION );
  }
| Term MINUS Term
  {
      $$ = libcasm_fe::Ast::make< BinaryExpression >( @$, $1, $3, libcasm_ir::Value::SUB_INSTRUCTION );
  }
| Term ASTERIX Term
  {
      $$ = libcasm_fe::Ast::make< BinaryExpression >( @$, $1, $3, libcasm_ir::Value::MUL_INSTRUCTION );
  }
| Term SLASH Term
  {
      $$ = libcasm_fe::Ast::make< BinaryExpression >( @$, $1, $3, libcasm_ir::Value::DIV_INSTRUCTION );
  }
| Term PERCENT Term
  {
      $$ = libcasm_fe::Ast::make< BinaryExpression >( @$, $1, $3, libcasm_ir::Value::MOD_INSTRUCTION );
  }
| Term CARET Term
  {
      // TODO call power builtin
  }
| Term NEQUAL Term
  {
      $$ = libcasm_fe::Ast::make< BinaryExpression >( @$, $1, $3, libcasm_ir::Value::NEQ_INSTRUCTION );
  }
| Term EQUAL Term
  {
      $$ = libcasm_fe::Ast::make< BinaryExpression >( @$, $1, $3, libcasm_ir::Value::EQU_INSTRUCTION );
  }
| Term LESSER Term
  {
      $$ = libcasm_fe::Ast::make< BinaryExpression >( @$, $1, $3, libcasm_ir::Value::LTH_INSTRUCTION );
  }
| Term GREATER Term
  {
      $$ = libcasm_fe::Ast::make< BinaryExpression >( @$, $1, $3, libcasm_ir::Value::GTH_INSTRUCTION );
  }
| Term LESSEQ Term
  {
      $$ = libcasm_fe::Ast::make< BinaryExpression >( @$, $1, $3, libcasm_ir::Value::LEQ_INSTRUCTION );
  }
| Term GREATEREQ Term
  {
      $$ = libcasm_fe::Ast::make< BinaryExpression >( @$, $1, $3, libcasm_ir::Value::GEQ_INSTRUCTION );
  }
| Term OR Term
  {
      $$ = libcasm_fe::Ast::make< BinaryExpression >( @$, $1, $3, libcasm_ir::Value::OR_INSTRUCTION );
  }
| Term XOR Term
  {
      $$ = libcasm_fe::Ast::make< BinaryExpression >( @$, $1, $3, libcasm_ir::Value::XOR_INSTRUCTION );
  }
| Term AND Term
  {
      $$ = libcasm_fe::Ast::make< BinaryExpression >( @$, $1, $3, libcasm_ir::Value::AND_INSTRUCTION );
  }
| Term IMPLIES Term
  {
      // TODO add implies instruction
  }
| NOT Term
  {
      $$ = libcasm_fe::Ast::make< UnaryExpression >( @$, $2, libcasm_ir::Value::NOT_INSTRUCTION );
  }
;



Range
: LSQPAREN Term DOTDOT Term RSQPAREN
  {
      $$ = libcasm_fe::Ast::make< RangeExpression >( @$, $2, $4 );
  }
;


List
: LSQPAREN RSQPAREN
  {
      const auto expressions = libcasm_fe::Ast::make< Expressions >( @$ );
      $$ = libcasm_fe::Ast::make< ListExpression >( @$, expressions );
  }
| LSQPAREN Term RSQPAREN
  {
      auto expressions = libcasm_fe::Ast::make< Expressions >( @$ );
      expressions->add( $2 );
      $$ = libcasm_fe::Ast::make< ListExpression >( @$, expressions );
  }
| LSQPAREN Terms RSQPAREN
  {
      $$ = libcasm_fe::Ast::make< ListExpression >( @$, $2 );
  }
;

Terms
: Terms COMMA Term
  {
      auto expressions = $1;
      expressions->add( $3 );
      $$ = expressions;
  }
| Term
  {
      const auto expressions = libcasm_fe::Ast::make< Expressions >( @$ );
      expressions->add( $1 );
      $$ = expressions;
  }
;


Arguments
: LPAREN Terms RPAREN
  {
      $$ = $2;
  }
| LPAREN RPAREN
  {
      const auto expressions = libcasm_fe::Ast::make< Expressions >( @$ );
      $$ = expressions;
  }
;


DirectCallExpression
: Identifier
  {
      const auto arguments = libcasm_fe::Ast::make< Expressions >( @$ );
      $$ = libcasm_fe::Ast::make< DirectCallExpression >( @$, $1, arguments );
  }
| Identifier Arguments
  {
      $$ = libcasm_fe::Ast::make< DirectCallExpression >( @$, $1, $2 );
  }
;


IndirectCallExpression
: LPAREN ASTERIX Term RPAREN Arguments
  {
      $$ = libcasm_fe::Ast::make< IndirectCallExpression >( @$, $3, $5 );
  }
;


ConditionalExpression
: IF Term THEN Term ELSE Term
  {
      $$ = libcasm_fe::Ast::make< ConditionalExpression >( @$, $2, $4, $6 );
  }
;


UniversalQuantifierExpression
: FORALL Variable IN Term HOLDS Term
  {
      $$ = libcasm_fe::Ast::make< UniversalQuantifierExpression >( @$, $2, $4, $6 );
  }
;


ExistentialQuantifierExpression
: EXISTS Variable IN Term WITH Term
  {
      $$ = libcasm_fe::Ast::make< ExistentialQuantifierExpression >( @$, $2, $4, $6 );
  }
;


RuleDefinition
: RULE Identifier MaybeParameters EQUAL Rule
  {
      $$ = libcasm_fe::Ast::make< RuleDefinition >( @$, $2, $3, createVoidType( @$ ),
                                   wrapInBlockRule( $5 ) );
  }
| RULE Identifier MaybeParameters ARROW Type EQUAL Rule
  {
      $$ = libcasm_fe::Ast::make< RuleDefinition >( @$, $2, $3, $5,
                                   wrapInBlockRule( $7 ) );
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
| ForallRule
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
      auto rules = libcasm_fe::Ast::make< Rules >( @$ );
      rules->add( $1 );
      $$ = rules;
  }
;


SkipRule
: SKIP
  {
      $$ = libcasm_fe::Ast::make< SkipRule >( @$ );
  }
;


ConditionalRule
: IF Term THEN Rule
  {
      $$ = libcasm_fe::Ast::make< ConditionalRule >( @$, $2, $4 );
  }
| IF Term THEN Rule ELSE Rule
  {
      $$ = libcasm_fe::Ast::make< ConditionalRule >( @$, $2, $4, $6 );
  }
;


CaseRule
: CASE Term OF LCURPAREN CaseLabels RCURPAREN
  {
      $$ = libcasm_fe::Ast::make< CaseRule >( @$, $2, $5 );
  }
;


CaseLabel
: DEFAULT COLON Rule
  {
      $$ = libcasm_fe::Ast::make< DefaultCase >( @$, $3 );
  }
| UNDERLINE COLON Rule
  {
      $$ = libcasm_fe::Ast::make< DefaultCase >( @$, $3 );
  }
| Term COLON Rule
  {
      $$ = libcasm_fe::Ast::make< ExpressionCase >( @$, $1, $3 );
  }
;


CaseLabels
: CaseLabel CaseLabels
  {
      auto cases = $2;
      cases->add( $1 );
      $$ = cases;
  }
| CaseLabel
  {
      auto cases = libcasm_fe::Ast::make< Cases >( @$ );
      cases->add( $1 );
      $$ = cases;
  }
;


LetRule
: LET Variable EQUAL Term IN Rule
  {
      $$ = libcasm_fe::Ast::make< LetRule >( @$, $2, $4, $6 );
  }
;


ForallRule
: FORALL Variable IN Term DO Rule
  {
      $$ = libcasm_fe::Ast::make< ForallRule >( @$, $2, $4, $6 );
  }
;


IterateRule
: ITERATE Rule
  {
      $$ = libcasm_fe::Ast::make< IterateRule >( @$, $2 );
  }
;


BlockRule
: LCURPAREN Rules RCURPAREN
  {
      $$ = libcasm_fe::Ast::make< BlockRule >( @$, $2 );
  }
| PAR Rules ENDPAR
  {
      $$ = libcasm_fe::Ast::make< BlockRule >( @$, $2 );
  }
;


SequenceRule
: SEQ_BRACKET Rules ENDSEQ_BRACKET
  {
      $$ = libcasm_fe::Ast::make< SequenceRule >( @$, $2 );
  }
| SEQ Rules ENDSEQ
  {
      $$ = libcasm_fe::Ast::make< SequenceRule >( @$, $2 );
  }
;


UpdateRule
: DirectCallExpression UPDATE Term
  {
      $$ = libcasm_fe::Ast::make< UpdateRule >( @$, $1, $3 );
  }
;


CallRule
: CALL DirectCallExpression
  {
      const std::set< CallExpression::TargetType >
          allowedCallTargetTypes{ CallExpression::TargetType::RULE };
      $$ = libcasm_fe::Ast::make< CallRule >( @$, $2, allowedCallTargetTypes );
  }
| DirectCallExpression
  {
      const std::set< CallExpression::TargetType >
          allowedCallTargetTypes{ CallExpression::TargetType::DERIVED,
                                  CallExpression::TargetType::BUILTIN };
      $$ = libcasm_fe::Ast::make< CallRule >( @$, $1, allowedCallTargetTypes );
  }
| CALL IndirectCallExpression
  {
      const std::set< CallExpression::TargetType >
          allowedCallTargetTypes{ CallExpression::TargetType::RULE };
      $$ = libcasm_fe::Ast::make< CallRule >( @$, $2, allowedCallTargetTypes );
  }
| IndirectCallExpression
  {
      const std::set< CallExpression::TargetType >
          allowedCallTargetTypes{ CallExpression::TargetType::DERIVED,
                                  CallExpression::TargetType::BUILTIN };
      $$ = libcasm_fe::Ast::make< CallRule >( @$, $1, allowedCallTargetTypes );
  }
;


Attribute
: BasicAttribute
  {
      $$ = $1;
  }
| ExpressionAttribute
  {
      $$ = $1;
  }
;


Attributes
: Attributes COMMA Attribute
  {
      auto attributes = $1;
      attributes->add( $3 );
      $$ = attributes;
  }
| Attribute
  {
      auto attributes = libcasm_fe::Ast::make< Attributes >( @$ );
      attributes->add( $1 );
      $$ = attributes;
  }
;


BasicAttribute
: Identifier
  {
      $$ = libcasm_fe::Ast::make< BasicAttribute >( @$, $1 );
  }
;


ExpressionAttribute
: Identifier Term
  {
      $$ = libcasm_fe::Ast::make< ExpressionAttribute >( @$, $1, $2 );
  }
;

%%

void Parser::error( const Location& location, const std::string& message )
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
