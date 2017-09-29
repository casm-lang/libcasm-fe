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

    #include "../stdhl/cpp/Type.h"

    #undef yylex
    #define yylex lexer.nextToken

    static BasicType::Ptr createVoidType( SourceLocation& sourceLocation )
    {
        const auto type = libstdhl::get< libcasm_ir::VoidType >();
        const auto name = Ast::make< Identifier >( sourceLocation, type->description() );
        const auto path = Ast::make< IdentifierPath >( sourceLocation, name );
        const auto node = Ast::make< BasicType >( sourceLocation, path );
        node->setType( type );
        return node;
    }

    static BasicType::Ptr createRuleRefType( SourceLocation& sourceLocation )
    {
        const auto type = libstdhl::get< libcasm_ir::RuleReferenceType >();
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
%token <std::string> FLOATING    "floating"
%token <std::string> STRING      "string"
%token <std::string> IDENTIFIER  "identifier"

%type <Specification::Ptr> Specification

%type <Identifier::Ptr> Identifier
%type <Identifiers::Ptr> Identifiers DotSeparatedIdentifiers
%type <IdentifierPath::Ptr> IdentifierPath

// definitions
%type <Definition::Ptr> Definition AttributedDefinition
%type <Definitions::Ptr> Definitions
%type <VariableDefinition::Ptr> Variable AttributedVariable
%type <FunctionDefinition::Ptr> FunctionDefinition
%type <DerivedDefinition::Ptr> DerivedDefinition
%type <RuleDefinition::Ptr> RuleDefinition
%type <EnumerationDefinition::Ptr> EnumerationDefinition

// expressions
%type <Expression::Ptr> Expression Term Atom
%type <Expressions::Ptr> Terms
%type <ValueAtom::Ptr> Boolean String BitNumber IntegerNumber FloatingNumber RationalNumber
%type <ReferenceAtom::Ptr> Reference
%type <UndefAtom::Ptr> Undefined
%type <RangeExpression::Ptr> Range
%type <ListExpression::Ptr> List
%type <DirectCallExpression::Ptr> DirectCallExpression
%type <IndirectCallExpression::Ptr> IndirectCallExpression
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

// types
%type <Type::Ptr> Type
%type <Types::Ptr> Types
%type <BasicType::Ptr> BasicType
%type <ComposedType::Ptr> ComposedType
%type <RelationType::Ptr> RelationType
%type <FixedSizedType::Ptr> FixedSizedType

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
%type <Expressions::Ptr> Arguments TwoOrMoreArguments
%type <NodeList< VariableDefinition >::Ptr> Parameters MaybeParameters


%start Specification

// prefer absolute over relative paths
%precedence ABSOLUTE_PATH

%precedence IN
%precedence DO

%precedence THEN
%precedence ELSE

%precedence HOLDS WITH

%precedence UPDATE

%left DOT
%left IMPLIES ARROW
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

// prefer calls with args (starts with LPAREN) over calls without args
%precedence CALL_WITHOUT_ARGS
%precedence LPAREN

// prefer fixed sized types over composed types (start with LESSER) over basic types
%precedence MARK

%%

Specification
: CASM Definitions
  {
      specification.setDefinitions( $2 );
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
| error // error recovery
  {
      $$ = nullptr;
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
      auto definitions = Ast::make< Definitions >( @$ );
      definitions->add( $1 );
      $$ = definitions;
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


MaybeInitially
: INITIALLY LCURPAREN MaybeInitializers RCURPAREN
  {
      $$ = $3;
  }
| %empty
  {
      $$ = Ast::make< NodeList< UpdateRule > >( @$ );
  }
;


MaybeDefined
: DEFINED LCURPAREN Term RCURPAREN
  {
      $$ = $3;
  }
| %empty
  {
      $$ = Ast::make< UndefAtom >( @$ );
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


ProgramFunctionDefinition
: INIT IdentifierPath
  {
      const auto singleAgentIdentifier = Ast::make< Identifier >( @$, "$" );
      auto singleAgentArguments = libcasm_fe::Ast::make< Expressions >( @$ );
      const auto singleAgent = libcasm_fe::Ast::make< DirectCallExpression >(
          @$, asIdentifierPath( singleAgentIdentifier ), singleAgentArguments );
      singleAgent->setTargetType( CallExpression::TargetType::CONSTANT );

      auto programDefinition = createProgramFunction( @$ );
      auto programArguments = libcasm_fe::Ast::make< Expressions >( @$ );
      programArguments->add( singleAgent );
      const auto program = libcasm_fe::Ast::make< DirectCallExpression >(
          @$, asIdentifierPath( programDefinition->identifier() ), programArguments );
      program->setTargetType( CallExpression::TargetType::FUNCTION );

      const auto ruleReference = Ast::make< ReferenceAtom >( @$, $2 );

      auto initializers = Ast::make< NodeList< UpdateRule > >( @$ );
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


Initializer
: Term
  {
      // the unknown function identifier will be replaced in FunctionDefinition
      const auto arguments = Ast::make< Expressions >( @$ );
      const auto function = Ast::make< DirectCallExpression >( @$, nullptr, arguments );
      function->setTargetType( CallExpression::TargetType::FUNCTION );
      $$ = Ast::make< UpdateRule >( @$, function, $1 );
  }
| Term MAPS Term
  {
      auto arguments = Ast::make< Expressions >( @$ );
      arguments->add( $1 );

      // the unknown function identifier will be replaced in FunctionDefinition
      const auto function = Ast::make< DirectCallExpression >( @$, nullptr, arguments );
      function->setTargetType( CallExpression::TargetType::FUNCTION );
      $$ = Ast::make< UpdateRule >( @$, function, $3 );
  }
| TwoOrMoreArguments MAPS Term // the rule above can be (arg)->... so force >=2 args here to avoid a shift/reduce conflict
  {
      // the unknown function identifier will be replaced in FunctionDefinition
      const auto function = Ast::make< DirectCallExpression >( @$, nullptr, $1 );
      function->setTargetType( CallExpression::TargetType::FUNCTION );
      $$ = Ast::make< UpdateRule >( @$, function, $3 );
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
      auto initializers = Ast::make< NodeList< UpdateRule > >( @$ );
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
      $$ = Ast::make< NodeList< UpdateRule > >( @$ );
  }
;


DerivedDefinition
: DERIVED Identifier MaybeParameters MAPS Type EQUAL Term
  {
      $$ = Ast::make< DerivedDefinition >( @$, $2, $3, $5, $7 );
  }
;


EnumerationDefinition
: ENUM Identifier EQUAL LCURPAREN Identifiers RCURPAREN
  {
      $$ = Ast::make< EnumerationDefinition >( @$, $2, $5 );
  }
;


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


Identifiers
: Identifiers COMMA Identifier
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


DotSeparatedIdentifiers
: DotSeparatedIdentifiers DOT Identifier
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


IdentifierPath
: DotSeparatedIdentifiers %prec ABSOLUTE_PATH
  {
      $$ = Ast::make< IdentifierPath >( @$, $1, IdentifierPath::Type::ABSOLUTE );
  }
| DOT DotSeparatedIdentifiers
  {
      $$ = Ast::make< IdentifierPath >( @$, $2, IdentifierPath::Type::RELATIVE );
  }
;


Variable
: Identifier COLON Type
  {
      $$ = Ast::make< VariableDefinition >( @$, $1, $3 );
  }
| Identifier
  {
      const auto unresolvedType = Ast::make< UnresolvedType >( @$ );
      $$ = Ast::make< VariableDefinition >( @$, $1, unresolvedType );
  }
;


AttributedVariable
: LSQPAREN Attributes RSQPAREN Variable
  {
      auto variable = $4;
      variable->setAttributes( $2 );
      $$ = variable;
  }
| Variable
  {
      $$ = $1;
  }
;


Parameters
: Parameters COMMA AttributedVariable
  {
      auto parameters = $1;
      parameters->add( $3 );
      $$ = parameters;
  }
| AttributedVariable
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


Type
: BasicType
  {
      $$ = $1;
  }
| ComposedType
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
: IdentifierPath
  {
      $$ = Ast::make< BasicType >( @$, $1 );
  }
;


ComposedType
: IdentifierPath LESSER Types GREATER
  {
      $$ = Ast::make< ComposedType >( @$, $1, $3 );
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


Atom
: Reference
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
      $$ = Ast::make< UndefAtom >( @$ );
  }
;


Boolean
: TRUE
  {
      const auto value = libstdhl::get< libcasm_ir::BooleanConstant >( true );
      $$ = Ast::make< ValueAtom >( @$, value );
  }
| FALSE
  {
      const auto value = libstdhl::get< libcasm_ir::BooleanConstant >( false );
      $$ = Ast::make< ValueAtom >( @$, value );
  }
;


String
: STRING
  {
      try
      {
          const auto value = libstdhl::get< libcasm_ir::StringConstant >( $1 );
          $$ = Ast::make< ValueAtom >( @$, value );
      }
      catch( const std::domain_error& e )
      {
          throw syntax_error( @$, e.what() );
      }
  }
;


BitNumber
: BINARY
  {
      try
      {
          const auto value = libstdhl::get< libcasm_ir::BitConstant >( $1, libstdhl::Type::BINARY );
          $$ = Ast::make< ValueAtom >( @$, value );
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
          const auto value = libstdhl::get< libcasm_ir::BitConstant >( $1, libstdhl::Type::HEXADECIMAL );
          $$ = Ast::make< ValueAtom >( @$, value );
      }
      catch( const std::domain_error& e )
      {
          throw syntax_error( @$, e.what() );
      }
  }
;


IntegerNumber
: INTEGER
  {
      try
      {
          const auto value = libstdhl::get< libcasm_ir::IntegerConstant >( $1, libstdhl::Type::DECIMAL );
          $$ = Ast::make< ValueAtom >( @$, value );
      }
      catch( const std::domain_error& e )
      {
          throw syntax_error( @$, e.what() );
      }
  }
;


FloatingNumber
: FLOATING
  {
      try
      {
          const auto value = libstdhl::get< libcasm_ir::FloatingConstant >( $1 );
          $$ = Ast::make< ValueAtom >( @$, value );
      }
      catch( const std::domain_error& e )
      {
          throw syntax_error( @$, e.what() );
      }
  }
;


RationalNumber
: RATIONAL
  {
      try
      {
          const auto value = libstdhl::get< libcasm_ir::RationalConstant >( $1 );
          $$ = Ast::make< ValueAtom >( @$, value );
      }
      catch( const std::domain_error& e )
      {
          throw syntax_error( @$, e.what() );
      }
  }
;


Reference
: AT IdentifierPath
  {
      $$ = Ast::make< ReferenceAtom >( @$, $2 );
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
: LPAREN Term RPAREN
  {
      $$ = $2;
  }
| LPAREN error RPAREN // error recovery
  {
      $$ = nullptr;
  }
| PLUS Term %prec UPLUS
  {
      $$ = $2;
  }
| MINUS Term %prec UMINUS
  {
      $$ = Ast::make< UnaryExpression >( @$, $2, libcasm_ir::Value::INV_INSTRUCTION );
  }
| Term PLUS Term
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


Range
: LSQPAREN Term DOTDOT Term RSQPAREN
  {
      $$ = Ast::make< RangeExpression >( @$, $2, $4 );
  }
;


List
: LSQPAREN RSQPAREN
  {
      const auto expressions = Ast::make< Expressions >( @$ );
      $$ = Ast::make< ListExpression >( @$, expressions );
  }
| LSQPAREN Terms RSQPAREN
  {
      $$ = Ast::make< ListExpression >( @$, $2 );
  }
| LSQPAREN error RSQPAREN // error recovery
  {
      $$ = nullptr;
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
      const auto expressions = Ast::make< Expressions >( @$ );
      expressions->add( $1 );
      $$ = expressions;
  }
;


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


TwoOrMoreArguments
: LPAREN Terms COMMA Term RPAREN
  {
      const auto expressions = $2;
      expressions->add( $4 );
      $$ = expressions;
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


IndirectCallExpression
: LPAREN ASTERIX Term RPAREN Arguments
  {
      $$ = Ast::make< IndirectCallExpression >( @$, $3, $5 );
  }
;


LetExpression
: LET AttributedVariable EQUAL Term IN Term
  {
      $$ = Ast::make< LetExpression >( @$, $2, $4, $6 );
  }
;


ConditionalExpression
: IF Term THEN Term ELSE Term
  {
      $$ = Ast::make< ConditionalExpression >( @$, $2, $4, $6 );
  }
;


ChooseExpression
: CHOOSE AttributedVariable IN Term DO Term
  {
      $$ = Ast::make< ChooseExpression >( @$, $2, $4, $6 );
  }
;


UniversalQuantifierExpression
: FORALL AttributedVariable IN Term HOLDS Term
  {
      $$ = Ast::make< UniversalQuantifierExpression >( @$, $2, $4, $6 );
  }
;


ExistentialQuantifierExpression
: EXISTS AttributedVariable IN Term WITH Term
  {
      $$ = Ast::make< ExistentialQuantifierExpression >( @$, $2, $4, $6 );
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
: CaseLabel CaseLabels
  {
      auto cases = $2;
      cases->add( $1 );
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
: LET AttributedVariable EQUAL Term IN Rule
  {
      $$ = Ast::make< LetRule >( @$, $2, $4, $6 );
  }
;


ForallRule
: FORALL AttributedVariable IN Term DO Rule
  {
      $$ = Ast::make< ForallRule >( @$, $2, $4, $6 );
  }
;


ChooseRule
: CHOOSE AttributedVariable IN Term DO Rule
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
      const auto function = $1;
      function->setTargetType( CallExpression::TargetType::FUNCTION );
      $$ = Ast::make< UpdateRule >( @$, function, $3 );
  }
;


CallRule
: CALL DirectCallExpression
  {
      const std::set< CallExpression::TargetType >
          allowedCallTargetTypes{ CallExpression::TargetType::RULE };
      $$ = Ast::make< CallRule >( @$, $2, allowedCallTargetTypes );
  }
| DirectCallExpression
  {
      const std::set< CallExpression::TargetType >
          allowedCallTargetTypes{ CallExpression::TargetType::DERIVED,
                                  CallExpression::TargetType::BUILTIN };
      $$ = Ast::make< CallRule >( @$, $1, allowedCallTargetTypes );
  }
| CALL IndirectCallExpression
  {
      const std::set< CallExpression::TargetType >
          allowedCallTargetTypes{ CallExpression::TargetType::RULE };
      $$ = Ast::make< CallRule >( @$, $2, allowedCallTargetTypes );
  }
| IndirectCallExpression
  {
      const std::set< CallExpression::TargetType >
          allowedCallTargetTypes{ CallExpression::TargetType::DERIVED,
                                  CallExpression::TargetType::BUILTIN };
      $$ = Ast::make< CallRule >( @$, $1, allowedCallTargetTypes );
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
      auto attributes = Ast::make< Attributes >( @$ );
      attributes->add( $1 );
      $$ = attributes;
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
