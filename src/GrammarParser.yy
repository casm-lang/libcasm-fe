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

%define parse.assert
%define parse.trace
%define parse.error verbose

%locations

%code requires
{
    namespace libcasm_fe
    {
        class Lexer;
    }

    #include "src/ast/Specification.h"

    using namespace libcasm_fe;
    using namespace Ast;
}

%parse-param { Lexer& lexer }
%parse-param { const std::string& specificationName }
%parse-param { Specification::Ptr& result }

%initial-action
{
  // Initialize the initial location.
  // Error messages are printed in Driver, I guess location does not
  // need to know about the filename
  // @$.begin.filename = @$.end.filename = driver.get_filename_ptr();
};

%code
{
    #include "src/Lexer.h"
    #include "src/Exceptions.h"

    #include "../stdhl/cpp/Type.h"

    #undef yylex
    #define yylex lexer.nextToken

    std::pair< FunctionDefinition::Classification, bool > parseFunctionAttributes(
        const NodeList< IdentifierNode >::Ptr& attributes )
    {
        using Classification = FunctionDefinition::Classification;

        auto functionClass = Classification::CONTROLLED;
        bool symbolicFunction = false;

        bool classAttributeAlreadyUsed = false;
        IdentifierNode::Ptr classAttribute;

        bool symbolicAttributeAlreadyUsed = false;
        IdentifierNode::Ptr symbolicAttribute;

        for( const auto& attribute : *attributes )
        {
            const auto& name = attribute->identifier();

            if( name == "symbolic" )
            {
                symbolicFunction = true;

                if( symbolicAttributeAlreadyUsed )
                {
                    /*driver.error
                    ( { symbolicAttribute->location(), attribute->location() }
                    , "`symbolic` attribute can only be used once per function"
                    , libcasm_fe::Codes::FunctionAttributeMultipleUseOfSymbolic
                    ); TODO */
                }
                else
                {
                    symbolicAttributeAlreadyUsed = true;
                    symbolicAttribute = attribute;
                }

                continue;
            }

            if( name == "in" or name == "monitored" )
            {
                functionClass = Classification::IN;
            }
            else if( name == "controlled" )
            {
                functionClass = Classification::CONTROLLED;
            }
            else if( name == "shared" )
            {
                functionClass = Classification::SHARED;
            }
            else if( name == "out" )
            {
                functionClass = Classification::OUT;
            }
            else if( name == "static" )
            {
                functionClass = Classification::STATIC;
            }
            else
            {
                /*driver.error
                ( attribute->location()
                , "`" + name + "` is no valid function attribute, only in, monitored, "
                + "controlled, shared, out, static and symbolic are allowed"
                , libcasm_fe::Codes::FunctionAttributeIsInvalid
                ); TODO */
            }

            if( classAttributeAlreadyUsed )
            {
                /*driver.error
                ( { classAttribute->location(), attribute->location() }
                , "a function classifier attribute can only be used once per function"
                , libcasm_fe::Codes::FunctionAttributeMultipleUseOfFunctionClassifier
                ); TODO */
            }
            else
            {
                classAttributeAlreadyUsed = true;
                classAttribute = attribute;
            }
        }

        return { functionClass, symbolicFunction };
    }

    static FunctionDefinition::Ptr createProgramFunction( location& sourceLocation )
    {
        const auto agentTypeName = make< IdentifierNode >( sourceLocation, "Agent" );
        const auto agentType = make< BasicType >( sourceLocation, agentTypeName );

        const auto ruleRefTypeName = make< IdentifierNode >( sourceLocation, "RuleReference" );
        const auto ruleRefType = make< BasicType >( sourceLocation, ruleRefTypeName );

        const auto argTypes = make< Types >( sourceLocation );
        argTypes->add( agentType );

        const auto program = make< IdentifierNode >( sourceLocation, "program" );
        return make< FunctionDefinition >( sourceLocation, program, argTypes, ruleRefType );
    }

    static Rule::Ptr wrapInBlockRule( const Rule::Ptr& rule )
    {
        if( (rule->id() == Node::ID::BLOCK_RULE )
                or (rule->id() == Node::ID::SEQUENCE_RULE ) )
        {
            return rule; // no need to wrap it
        }

        const auto& sourceLocation = rule->sourceLocation();
        const auto rules = make< Rules >( sourceLocation );
        rules->add( rule );
        return make< BlockRule >( sourceLocation, rules );
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
%type <NodeList< IdentifierNode >::Ptr> Identifiers MaybeIdentifiers

// definitions
%type <Definition::Ptr> Definition
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

// other
%type <FunctionDefinition::Ptr> ProgramFunctionDefinition
%type <CaseRule::Case> CaseLabel
%type <std::vector< CaseRule::Case >> CaseLabels
%type <UpdateRule::Ptr> Initializer
%type <NodeList< UpdateRule >::Ptr> Initializers MaybeInitializers MaybeInitially
%type <NodeList< IdentifierNode >::Ptr> MaybeFunctionAttributes
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
      const auto name = make< IdentifierNode >( @$, specificationName );
      result = make< Specification >( @$, name, $2 );
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


Definitions
: Definitions Definition
  {
      auto definitions = $1;
      definitions->add( $2 );
      $$ = definitions;
  }
| Definition
  {
      auto definitions = make< Definitions >( @$ );
      definitions->add( $1 );
      $$ = definitions;
  }
;


FunctionDefinition
: FUNCTION MaybeFunctionAttributes Identifier COLON MaybeFunctionParameters ARROW Type MaybeDefined MaybeInitially
  {
      const auto identifier = $3;

      auto function = make< FunctionDefinition >( @$, identifier, $5, $7 );

      const auto attributes = parseFunctionAttributes( $2 );
      function->setClassification( attributes.first );
      function->setSymbolic( attributes.second );

      function->setDefaultValue( $8 );

      // apply the name of the function declaration to the initializer functions
      auto initializers = $9;
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
      $$ = make< NodeList< UpdateRule > >( @$ );
  }
;


MaybeDefined
: DEFINED LCURPAREN Term RCURPAREN
  {
      $$ = $3;
  }
| %empty
  {
      $$ = make< UndefAtom >( @$ );
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
      auto types = make< Types >( @$ );
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
      $$ = make< Types >( @$ );
  }
;


MaybeFunctionAttributes
: LPAREN MaybeIdentifiers RPAREN
  {
      $$ = $2;
  }
| %empty
  {
      $$ = make< NodeList< IdentifierNode > >( @$ );
  }
;


ProgramFunctionDefinition
: INIT Identifier
  {
      auto programDefinition = createProgramFunction( @$ );

      auto arguments = make< Expressions >( @$ );
      // TODO add `default` agent to arguments
      const auto program = make< DirectCallExpression >(
          @$, programDefinition->identifier(), arguments );

      const auto ruleReference = make< RuleReferenceAtom >( @$, $2 );

      auto initializers = make< NodeList< UpdateRule > >( @$ );
      initializers->add( make< UpdateRule >( @$, program, ruleReference ) );
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
      const auto unknown = make< IdentifierNode >( @$, std::string() );
      const auto arguments = make< Expressions >( @$ );
      const auto function = make< DirectCallExpression >( @$, unknown, arguments );

      $$ = make< UpdateRule >( @$, function, $1 );
  }
| Term ARROW Term
  {
      auto arguments = make< Expressions >( @$ );
      arguments->add( $1 );

      // the unknown function identifier will be replaced in FunctionDefinition
      const auto unknown = make< IdentifierNode >( @$, std::string() );
      const auto function = make< DirectCallExpression >( @$, unknown, arguments );

      $$ = make< UpdateRule >( @$, function, $3 );
  }
| Arguments ARROW Term
  {
      // the unknown function identifier will be replaced in FunctionDefinition
      const auto unknown = make< IdentifierNode >( @$, std::string() );
      const auto function = make< DirectCallExpression >( @$, unknown, $1 );

      $$ = make< UpdateRule >( @$, function, $3 );
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
      auto initializers = make< NodeList< UpdateRule > >( @$ );
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
      $$ = make< NodeList< UpdateRule > >( @$ );
  }
;


DerivedDefinition
: DERIVED Identifier MaybeParameters ARROW Type EQUAL Term
  {
      $$ = make< DerivedDefinition >( @$, $2, $3, $5, $7 );
  }
;


EnumerationDefinition
: ENUM Identifier EQUAL LCURPAREN Identifiers RCURPAREN
  {
      $$ = make< EnumerationDefinition >( @$, $2, $5 );
  }
;


Identifier
: IDENTIFIER
  {
      $$ = make< IdentifierNode >( @$, $1 );
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
      auto identifiers = make< NodeList< IdentifierNode > >( @$ );
      identifiers->add( $1 );
      $$ = identifiers;
  }
;


MaybeIdentifiers
: Identifiers
  {
      $$ = $1;
  }
| %empty
  {
      $$ = make< NodeList< IdentifierNode > >( @$ );
  }
;


Variable
: Identifier COLON Type
  {
      $$ = make< VariableDefinition >( @$, $1, $3 );
  }
| Identifier
  {
      const auto voidType = make< VoidType >( @$ );
      $$ = make< VariableDefinition >( @$, $1, voidType );
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
      auto parameters = make< NodeList< VariableDefinition > >( @$ );
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
      $$ = make< NodeList< VariableDefinition > >( @$ );
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
      $$ = make< BasicType >( @$, $1 );
  }
;


ComposedType
: Identifier LPAREN Types RPAREN
  {
      $$ = make< ComposedType >( @$, $1, $3 );
  }
;


FixedSizedType
: Identifier LESSER Term GREATER
  {
      $$ = make< FixedSizedType >( @$, $1, $3 );
  }
;


RangedType
: Identifier LESSER Term DOTDOT Term GREATER
  {
      $$ = make< RangedType >( @$, $1, $3, $5 );
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
      auto types = make< Types >( @$ );
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
      $$ = make< UndefAtom >( @$ );
  }
;


Boolean
: TRUE
  {
      const auto value = libstdhl::get< libcasm_ir::BooleanConstant >( true );
      $$ = make< ValueAtom >( @$, value );
  }
| FALSE
  {
      const auto value = libstdhl::get< libcasm_ir::BooleanConstant >( false );
      $$ = make< ValueAtom >( @$, value );
  }
;


String
: STRING
  {
      const auto value = libstdhl::get< libcasm_ir::StringConstant >( $1 );
      $$ = make< ValueAtom >( @$, value );
  }
;


BitNumber
: BINARY
  {
      const auto value = libstdhl::get< libcasm_ir::BitConstant >( $1, libstdhl::Type::BINARY );
      $$ = make< ValueAtom >( @$, value );
  }
| HEXADECIMAL
  {
      const auto value = libstdhl::get< libcasm_ir::BitConstant >( $1, libstdhl::Type::HEXADECIMAL );
      $$ = make< ValueAtom >( @$, value );
  }
;


IntegerNumber
: INTEGER
  {
      const auto value = libstdhl::get< libcasm_ir::IntegerConstant >( $1, libstdhl::Type::DECIMAL );
      $$ = make< ValueAtom >( @$, value );
  }
;


FloatingNumber
: FLOATING
  {
      const auto value = libstdhl::get< libcasm_ir::FloatingConstant >( $1 );
      $$ = make< ValueAtom >( @$, value );
  }
;


RationalNumber
: RATIONAL
  {
      const auto value = libstdhl::get< libcasm_ir::RationalConstant >( $1 );
      $$ = make< ValueAtom >( @$, value );
  }
;


RuleReference
: AT IDENTIFIER
  {
      const auto ruleName = make< IdentifierNode >( @$, $2 );
      $$ = make< RuleReferenceAtom >( @$, ruleName );
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
      const auto zero = make< ZeroAtom >( @$ );
      $$ = make< BinaryExpression >( @$, zero, $2, libcasm_ir::Value::SUB_INSTRUCTION );
  }
| Term PLUS Term
  {
      $$ = make< BinaryExpression >( @$, $1, $3, libcasm_ir::Value::ADD_INSTRUCTION );
  }
| Term MINUS Term
  {
      $$ = make< BinaryExpression >( @$, $1, $3, libcasm_ir::Value::SUB_INSTRUCTION );
  }
| Term ASTERIX Term
  {
      $$ = make< BinaryExpression >( @$, $1, $3, libcasm_ir::Value::MUL_INSTRUCTION );
  }
| Term SLASH Term
  {
      $$ = make< BinaryExpression >( @$, $1, $3, libcasm_ir::Value::DIV_INSTRUCTION );
  }
| Term PERCENT Term
  {
      $$ = make< BinaryExpression >( @$, $1, $3, libcasm_ir::Value::MOD_INSTRUCTION );
  }
| Term CARET Term
  {
      // TODO call power builtin
  }
| Term NEQUAL Term
  {
      $$ = make< BinaryExpression >( @$, $1, $3, libcasm_ir::Value::NEQ_INSTRUCTION );
  }
| Term EQUAL Term
  {
      $$ = make< BinaryExpression >( @$, $1, $3, libcasm_ir::Value::EQU_INSTRUCTION );
  }
| Term LESSER Term
  {
      $$ = make< BinaryExpression >( @$, $1, $3, libcasm_ir::Value::LTH_INSTRUCTION );
  }
| Term GREATER Term
  {
      $$ = make< BinaryExpression >( @$, $1, $3, libcasm_ir::Value::GTH_INSTRUCTION );
  }
| Term LESSEQ Term
  {
      $$ = make< BinaryExpression >( @$, $1, $3, libcasm_ir::Value::LEQ_INSTRUCTION );
  }
| Term GREATEREQ Term
  {
      $$ = make< BinaryExpression >( @$, $1, $3, libcasm_ir::Value::GEQ_INSTRUCTION );
  }
| Term OR Term
  {
      $$ = make< BinaryExpression >( @$, $1, $3, libcasm_ir::Value::OR_INSTRUCTION );
  }
| Term XOR Term
  {
      $$ = make< BinaryExpression >( @$, $1, $3, libcasm_ir::Value::XOR_INSTRUCTION );
  }
| Term AND Term
  {
      $$ = make< BinaryExpression >( @$, $1, $3, libcasm_ir::Value::AND_INSTRUCTION );
  }
| Term IMPLIES Term
  {
      // TODO add implies instruction
  }
| NOT Term
  {
      $$ = make< UnaryExpression >( @$, $2, libcasm_ir::Value::NOT_INSTRUCTION );
  }
;



Range
: LSQPAREN Term DOTDOT Term RSQPAREN
  {
      $$ = make< RangeExpression >( @$, $2, $4 );
  }
;


List
: LSQPAREN RSQPAREN
  {
      const auto expressions = make< Expressions >( @$ );
      $$ = make< ListExpression >( @$, expressions );
  }
| LSQPAREN Term RSQPAREN
  {
      auto expressions = make< Expressions >( @$ );
      expressions->add( $2 );
      $$ = make< ListExpression >( @$, expressions );
  }
| LSQPAREN Terms RSQPAREN
  {
      $$ = make< ListExpression >( @$, $2 );
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
      const auto expressions = make< Expressions >( @$ );
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
      const auto expressions = make< Expressions >( @$ );
      $$ = expressions;
  }
;


DirectCallExpression
: Identifier
  {
      const auto arguments = make< Expressions >( @$ );
      $$ = make< DirectCallExpression >( @$, $1, arguments );
  }
| Identifier Arguments
  {
      $$ = make< DirectCallExpression >( @$, $1, $2 );
  }
;


IndirectCallExpression
: LPAREN ASTERIX Term RPAREN Arguments
  {
      $$ = make< IndirectCallExpression >( @$, $3, $5 );
  }
;


ConditionalExpression
: IF Term THEN Term ELSE Term
  {
      $$ = make< ConditionalExpression >( @$, $2, $4, $6 );
  }
;


UniversalQuantifierExpression
: FORALL Variable IN Term HOLDS Term
  {
      $$ = make< UniversalQuantifierExpression >( @$, $2, $4, $6 );
  }
;


ExistentialQuantifierExpression
: EXISTS Variable IN Term WITH Term
  {
      $$ = make< ExistentialQuantifierExpression >( @$, $2, $4, $6 );
  }
;


RuleDefinition
: RULE Identifier MaybeParameters EQUAL Rule
  {
      $$ = make< RuleDefinition >( @$, $2, $3, make< VoidType >( @$ ),
                                   wrapInBlockRule( $5 ) );
  }
| RULE Identifier MaybeParameters ARROW Type EQUAL Rule
  {
      $$ = make< RuleDefinition >( @$, $2, $3, $5,
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
      auto rules = make< Rules >( @$ );
      rules->add( $1 );
      $$ = rules;
  }
;


SkipRule
: SKIP
  {
      $$ = make< SkipRule >( @$ );
  }
;


ConditionalRule
: IF Term THEN Rule
  {
      $$ = make< ConditionalRule >( @$, $2, $4 );
  }
| IF Term THEN Rule ELSE Rule
  {
      $$ = make< ConditionalRule >( @$, $2, $4, $6 );
  }
;


CaseRule
: CASE Term OF LCURPAREN CaseLabels RCURPAREN
  {
      $$ = make< CaseRule >( @$, $2, $5 );
  }
;


CaseLabel
: DEFAULT COLON Rule
  {
      // default case
      $$ = CaseRule::Case( nullptr, $3 );
  }
| UNDERLINE COLON Rule
  {
      // default case
      $$ = CaseRule::Case( nullptr, $3 );
  }
| Term COLON Rule
  {
      $$ = CaseRule::Case( $1, $3 );
  }
;


CaseLabels
: CaseLabel CaseLabels
  {
      $$ = std::move( $2 );
      $$.push_back( $1 );
  }
| CaseLabel
  {
      $$ = { $1 };
  }
;


LetRule
: LET Variable EQUAL Term IN Rule
  {
      $$ = make< LetRule >( @$, $2, $4, $6 );
  }
;


ForallRule
: FORALL Variable IN Term DO Rule
  {
      $$ = make< ForallRule >( @$, $2, $4, $6 );
  }
;


IterateRule
: ITERATE Rule
  {
      $$ = make< IterateRule >( @$, $2 );
  }
;


BlockRule
: LCURPAREN Rules RCURPAREN
  {
      $$ = make< BlockRule >( @$, $2 );
  }
| PAR Rules ENDPAR
  {
      $$ = make< BlockRule >( @$, $2 );
  }
;


SequenceRule
: SEQ_BRACKET Rules ENDSEQ_BRACKET
  {
      $$ = make< SequenceRule >( @$, $2 );
  }
| SEQ Rules ENDSEQ
  {
      $$ = make< SequenceRule >( @$, $2 );
  }
;


UpdateRule
: DirectCallExpression UPDATE Term
  {
      $$ = make< UpdateRule >( @$, $1, $3 );
  }
;


CallRule
: CALL DirectCallExpression
  {
      const std::set< CallExpression::TargetType >
          allowedCallTargetTypes{ CallExpression::TargetType::RULE };
      $$ = make< CallRule >( @$, $2, allowedCallTargetTypes );
  }
| DirectCallExpression
  {
      const std::set< CallExpression::TargetType >
          allowedCallTargetTypes{ CallExpression::TargetType::DERIVED,
                                  CallExpression::TargetType::BUILTIN };
      $$ = make< CallRule >( @$, $1, allowedCallTargetTypes );
  }
| CALL IndirectCallExpression
  {
      const std::set< CallExpression::TargetType >
          allowedCallTargetTypes{ CallExpression::TargetType::RULE };
      $$ = make< CallRule >( @$, $2, allowedCallTargetTypes );
  }
| IndirectCallExpression
  {
      const std::set< CallExpression::TargetType >
          allowedCallTargetTypes{ CallExpression::TargetType::DERIVED,
                                  CallExpression::TargetType::BUILTIN };
      $$ = make< CallRule >( @$, $1, allowedCallTargetTypes );
  }
;

%%

void Parser::error( const location_type& l, const std::string& m )
{
    if( m.compare( "syntax error, unexpected end of file, expecting CASM" ) == 0 )
    {
        i32 pos = (l.begin.line - 1);
        pos = ( pos > 0 ? pos : 1 );

        /*driver.error
        ( location( position( 0, pos, 1 ) )
        , m
        , libcasm_fe::Codes::SyntaxError
        ); TODO */
    }
    else
    {
        //driver.error( l, m, libcasm_fe::Codes::SyntaxError ); TODO
    }

    std::cerr << l << ": " << m << std::endl;
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
