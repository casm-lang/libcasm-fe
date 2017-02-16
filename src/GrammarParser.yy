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

%skeleton "lalr1.cc" /* -*- C++ -*- */
%defines
%define parser_class_name {Parser}

%define api.token.constructor
%define api.value.type variant
%define parse.assert


%code requires
{
    #include "cpp/Type.h"

    #include "src/Ast/Specification.h"
    #include "src/Driver.h"
    #include "src/Codes.h"

    #include "../casm-ir/src/Value.h"

    using namespace libcasm_fe;
}

// The parsing context.
%parse-param { Driver& driver }
%lex-param   { Driver& driver }

%locations
%initial-action
{
  // Initialize the initial location.
  // Error messages are printed in Driver, I guess location does not
  // need to know about the filename
  // @$.begin.filename = @$.end.filename = driver.get_filename_ptr();
};

%define parse.trace
%define parse.error verbose


%code
{
    yy::Parser::symbol_type yylex( libcasm_fe::Driver& driver );

    std::pair< Ast::FunctionDefinition::Classification, bool > parseFunctionAttributes(
        Driver& driver, const Ast::NodeList< Ast::IdentifierNode >& attributes )
    {
        using Classification = Ast::FunctionDefinition::Classification;

        auto functionClass = Classification::Controlled;
        bool symbolicFunction = false;

        bool classAttributeAlreadyUsed = false;
        Ast::IdentifierNode classAttribute;

        bool symbolicAttributeAlreadyUsed = false;
        Ast::IdentifierNode symbolicAttribute;

        for( auto attribute : *attributes )
        {
            const auto& name = attribute->identifier();

            if( name == "symbolic" )
            {
                symbolicFunction = true;

                if( symbolicAttributeAlreadyUsed )
                {
                    driver.error
                    ( { symbolicAttribute->location(), attribute->location() }
                    , "`symbolic` attribute can only be used once per function"
                    , libcasm_fe::Codes::FunctionAttributeMultipleUseOfSymbolic
                    );
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
                functionClass = Classification::In;
            }
            else if( name == "controlled" )
            {
                functionClass = Classification::Controlled;
            }
            else if( name == "shared" )
            {
                functionClass = Classification::Shared;
            }
            else if( name == "out" )
            {
                functionClass = Classification::Out;
            }
            else if( name == "static" )
            {
                functionClass = Classification::Static;
            }
            else
            {
                driver.error
                ( attribute->location(),
                , "`" + name + "` is no valid function attribute, only in, monitored, "
                + "controlled, shared, out, static and symbolic are allowed"
                , libcasm_fe::Codes::FunctionAttributeIsInvalid
                );
            }

            if( classAttributeAlreadyUsed )
            {
                driver.error
                ( { classAttribute->location(), attribute->location() }
                , "a function classifier attribute can only be used once per function"
                , libcasm_fe::Codes::FunctionAttributeMultipleUseOfFunctionClassifier
                );
            }
            else
            {
                classAttributeAlreadyUsed = true;
                classAttribute = attribute;
            }
        }

        return { functionClass, symbolicFunction };
    }

    static Ast::FunctionDefinition::Ptr createProgramFunction( yy::location& location )
    {
        //auto argTypes = { new Type( TypeType::AGENT ) }; // TODO add args and return type
        //auto retType = new Type( TypeType::RuleReference );

        const auto program = Ast::make< Ast::IdentifierNode >( location, "program" );
        return Ast::make< Ast::FunctionDefinition >( location, program, nullptr, nullptr );
    }

    static Ast::Rule::Ptr wrapInBlockRule( const Ast::Rule::Ptr& rule )
    {
        if ( (rule->type() == Ast::Node::Type::BlockRule)
                or (rule->type() == Ast::Node::Type::SequenceRule) )
        {
            return rule; // no need to wrap it
        }

        return Ast::make< Ast::BlockRule >( rule );
    }
}


%token
END       0 "end of file"
{{grammartoken}}
;

%token <FLOATING_T> FLOATINGCONST "floating"
%token <INTEGER_T> INTEGERCONST  "integer"
%token <rational_t> RATIONALCONST "rational"
%token <std::string> STRCONST      "string"
%token <std::string> IDENTIFIER "identifier"

%type <Ast::Specification::Ptr> Specification
%type <Ast::IdentifierNode::Ptr> Identifier
%type <Ast::NodeList< Ast::IdentifierNode >::Ptr> Identifiers MaybeIdentifiers

// definitions
%type <Ast::Definition::Ptr> Definition
%type <Ast::Definitions::Ptr> Definitions
%type <Ast::VariableDefinition::Ptr> Variable
%type <Ast::FunctionDefinition::Ptr> FunctionDefinition
%type <Ast::DerivedDefinition::Ptr> DerivedDefinition
%type <Ast::RuleDefinition::Ptr> RuleDefinition
%type <Ast::EnumerationDefinition::Ptr> EnumerationDefinition

// expressions
%type <Ast::Expression::Ptr> Expression Atom
%type <Ast::Expressions::Ptr> Expressions MaybeExpressions
%type <Ast::ValueAtom::Ptr> Boolean String IntegerNumber FloatingNumber RationalNumber RuleReference
%type <Ast::UndefAtom::Ptr> Undefined
%type <Ast::RangeExpression::Ptr> Range
%type <Ast::ListExpression::Ptr> List
%type <Ast::DirectCallExpression::Ptr> DirectCallExpression
%type <Ast::IndirectCallExpression::Ptr> IndirectCallExpression

// rules
%type <Ast::Rule::Ptr> Rule
%type <Ast::Rules::Ptr> Rules
%type <Ast::SkipRule::Ptr> SkipRule
%type <Ast::ConditionalRule::Ptr> ConditionalRule
%type <Ast::CaseRule::Ptr> CaseRule
%type <Ast::LetRule::Ptr> LetRule
%type <Ast::ForallRule::Ptr> ForallRule
%type <Ast::IterateRule::Ptr> IterateRule
%type <Ast::BlockRule::Ptr> BlockRule
%type <Ast::SequenceRule::Ptr> SequenceRule
%type <Ast::UpdateRule::Ptr> UpdateRule
%type <Ast::CallRule::Ptr> CallRule

// types
%type <Ast::Type::Ptr> Type
%type <Ast::Types::Ptr> Types
%type <Ast::BasicType::Ptr> BasicType
%type <Ast::ComposedType::Ptr> ComposedType
%type <Ast::StaticallySizedType::Ptr> StaticallySizedType
%type <Ast::RangedType::Ptr> RangedType

// other
%type <Ast::FunctionDefinition::Ptr> ProgramFunctionDefinition
%type <Ast::CaseRule::Case> CaseLabel
%type <std::vector< Ast::CaseRule::Case >> CaseLabels
%type <Ast::UpdateRule::Ptr> Initializer
%type <Ast::NodeList< Ast::UpdateRule >::Ptr> Initializers MaybeInitializers MaybeInitially
%type <Ast::NodeList< Ast::IdentifierNode >::Ptr> MaybeFunctionAttributes
%type <Ast::Expression::Ptr> MaybeDefined
%type <Ast::Types::Ptr> FunctionParameters MaybeFunctionParameters
%type <Ast::Expressions::Ptr> Arguments MaybeArguments
%type <Ast::NodeList< Ast::VariableDefinition >::Ptr> Parameters MaybeParameters


%start Specification

%precedence THEN
%precedence ELSE

//%precedence UPDATE ASSERT ASSURE ABORT
// %precedence IDENTIFIER
//%precedence INTEGERCONST STRCONST FLOATINGCONST RATIONALCONST
// %precedence UNDEF
// %precedence TRUE
// %precedence FALSE

%left AND
%left XOR
%left OR

%left EQUAL
%left NEQUAL

%left GREATEREQ
%left LESSEQ

%left GREATER
%left LESSER

%left PLUS
%left MINUS
%left PERCENT
%left SLASH
%left STAR

%precedence NOT

%nonassoc UPLUS
%nonassoc UMINUS

%%

Specification
: CASM Definitions
  {
      const std::string& filepath = driver.get_filename();
      const std::string& filename
          = filepath.substr( filepath.find_last_of( "/\\" ) + 1 );
      const std::string& filenameWithoutExtension
          = filename.substr( 0, filename.rfind( "." ) );

      const auto name = Ast::make< Ast::IdentifierNode >( filenameWithoutExtension );
      const auto specification = Ast::make< Ast::Specification >( @$, name, $2 );

      //driver.result = specification; TODO
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
      auto definitions = Ast::make< Ast::Definitions >( @$ );
      definitions->add( $1 );
      $$ = definitions;
  }
;


FunctionDefinition
: FUNCTION MaybeFunctionAttributes Identifier COLON MaybeFunctionParameters ARROW Type MaybeDefined MaybeInitially
  {
      auto function = Ast::make< Ast::FunctionDefinition >( @$, $3, $5, $7 );

      const auto attributes = parseFunctionAttributes( driver, $2 );
      function->setClassification( attributes.first );
      function->setSymbolic( attributes.second );

      function->setDefaultValue( $8 );

      // apply the name of the function declaration to the initializer functions
      auto initializers = $9;
      for (auto initializer : *initializers) {
           initializer->function()->setIdentifier( functionDefinition->identifier() );
      }
      function->setInitializers( initializers );

      $$ = function;
  }
| ProgramFunctionDefinition // `init` special case
  {
      $$ = $1;
  }
;


MaybeInitially
: INITIALLY LCURPAREN MaybeInitializers RCURPAREN
  {
      $$ = $3;
  }
| %empty
  {
      $$ = Ast::make< Ast::NodeList< Ast::UpdateRule > >( @$ );
  }
;


MaybeDefined
: DEFINED LCURPAREN Atom RCURPAREN
  {
      $$ = $3;
  }
| %empty
  {
      $$ = Ast::make< Ast::UndefAtom >( @$ );
  }
;


FunctionParameters
: FunctionParameters STAR Type
  {
      auto types = $1;
      types->add( $3 );
      $$ = types;
  }
| Type
  {
      auto types = Ast::make< Ast::Types >( @$ );
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
      $$ = Ast::make< Ast::Types >( @$ );
  }
;


MaybeFunctionAttributes
: LPAREN MaybeIdentifiers RPAREN
  {
      $$ = $2;
  }
| %empty
  {
      $$ = Ast::make< Ast::NodeList< Ast::IdentifierNode > >( @$ );
  }
;


ProgramFunctionDefinition
: INIT RuleReference
  {
      auto programDefinition = createProgramFunction();

      auto arguments = Ast::make< Ast::Expressions >( @$ );
      // TODO add `default` agent to arguments
      const auto program = Ast::make< Ast::DirectCallExpression >(
          @$, programDefinition->identifier(), arguments );

      auto initializers = Ast::make< Ast::NodeList< Ast::UpdateRule > >( @$ );
      initializers->add( Ast::make< Ast::UpdateRule >( @$, program, $2 ) );
      programDefinition->setInitializers( initializers );

      $$ = programDefinition;
  }
| INIT LCURPAREN MaybeInitializers RCURPAREN
  {
      auto programDefinition = createProgramFunction();

      // apply the name of the program declaration to the initializer functions
      auto initializers = $3;
      for (auto initializer : *initializers) {
          initializer->function()->setIdentifier( programDefinition->identifier() );
      }
      programDefinition->setInitializers( initializers );

      $$ = programDefinition;
  }
;


Initializer
: Atom
  {
      // the unknown function identifier will be replaced in FunctionDefinition
      const auto unknown = Ast::make< Ast::IdentifierNode >( @$, std::string() );
      const auto arguments = Ast::make< Ast::Expressions >( @$ );
      const auto function = Ast::make< Ast::DirectCallExpression >( @$, unknown, arguments );

      $$ = Ast::make< Ast::UpdateRule >( @$, function, $1 );
  }
| MaybeArguments ARROW Atom
  {
      // the unknown function identifier will be replaced in FunctionDefinition
      const auto unknown = Ast::make< Ast::IdentifierNode >( @$, std::string() );
      const auto function = Ast::make< Ast::DirectCallExpression >( @$, unknown, $1 );

      $$ = Ast::make< Ast::UpdateRule >( @$, function, $3 );
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
      auto initializers = Ast::make< Ast::NodeList< Ast::UpdateRule > >( @$ );
      initializers->add( $1 );
      $$ = initializers;
  }
;


MaybeInitializers
: Initializers
  {
      $$ = $1;
  }
| Initializers COMMA
  {
      $$ = $1;
  }
| %empty
  {
      $$ = Ast::make< Ast::NodeList< Ast::UpdateRule > >( @$ );
  }
;


DerivedDefinition
: DERIVED Identifier MaybeParameters COLON Type EQUAL Expression
  {
      $$ = Ast::make< Ast::DerivedDefinition >( @$, $2, $3, $5, $7 );
  }
;


EnumerationDefinition
: ENUM Identifier EQUAL LCURPAREN MaybeIdentifiers RCURPAREN
  {
      $$ = Ast::make< Ast::EnumerationDefinition >( @$, $2, $5 );
  }
;


Identifier
: IDENTIFIER
  {
      $$ = Ast::make< Ast::IdentifierNode >( @$, $1 );
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
      auto identifiers = Ast::make< Ast::NodeList< Ast::Identifier > >( @$ );
      identifiers->add( $1 );
      $$ = identifiers;
  }
;


MaybeIdentifiers
: Identifiers
  {
      $$ = $1;
  }
| Identifiers COMMA
  {
      $$ = $1;
  }
| %empty
  {
      $$ = Ast::make< Ast::NodeList< Ast::Identifier > >( @$ );
  }
;


Variable
: Identifier COLON Type
  {
      $$ = Ast::make< Ast::VariableDefinition >( @$, $1, $3 );
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
      auto parameters = Ast::make< Ast::NodeList< Ast::VariableDefinition > >( @$ );
      parameters->add( $1 );
      $$ = parameters;
  }
;


MaybeParameters
: LPAREN Parameters RPAREN
  {
      $$ = $2;
  }
| LPAREN RPAREN
  {
      $$ = Ast::make< Ast::NodeList< Ast::VariableDefinition > >( @$ );
  }
| %empty
  {
      $$ = Ast::make< Ast::NodeList< Ast::VariableDefinition > >( @$ );
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
| StaticallySizedType
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
      $$ = Ast::make< Ast::BasicType >( @$, $1 );
  }
;


ComposedType
: Identifier LPAREN Types RPAREN
  {
      $$ = Ast::make< Ast::ComposedType >( @$, $1, $3 );
  }
;


StaticallySizedType
: Identifier LPAREN Atom RPAREN
  {
      $$ = Ast::make< Ast::StaticallySizedType >( @$, $1, $3 );
  }
;


RangedType
: Identifier LPAREN Atom DOTDOT Atom RPAREN
  {
      $$ = Ast::make< Ast::RangedType >( @$, $1, $3, $5 );
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
      auto types = Ast::make< Ast::Types >( @$ );
      types->add( $1 );
      $$ = types;
  }
;


Atom
: DirectCallExpression
  {
      $$ = $1;
  }
| IndirectCallExpression
  {
      $$ = $1;
  }
| LPAREN Expression RPAREN
  {
      $$ = $2;
  }
| PLUS LPAREN Expression RPAREN %prec UPLUS
  {
      $$ = $3;
  }
| MINUS LPAREN Expression RPAREN %prec UMINUS
  {
      const auto zero = Ast::make< Ast::ZeroAtom >( @$ );
      $$ = Ast::make< Ast::BinaryExpression >( @$, zero, $3,
                                               libcasm_ir::Value::SUB_INSTRUCTION );
  }
| RuleReference
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
| List
  {
      $$ = $1;
  }
| Range
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
      $$ = Ast::make< Ast::UndefAtom >( @$ );
  }
;


Boolean
: TRUE
  {
      const auto value = libstdhl::get< libcasm_ir::BooleanConstant >( true );
      $$ = Ast::make< Ast::ValueAtom >( @$, value );
  }
| FALSE
  {
      const auto value = libstdhl::get< libcasm_ir::BooleanConstant >( false );
      $$ = Ast::make< Ast::ValueAtom >( @$, value );
  }
;


String
: STRCONST
  {
      const auto value = libstdhl::get< libcasm_ir::StringConstant >( $1 );
      $$ = Ast::make< Ast::ValueAtom >( @$, value );
  }
;


IntegerNumber
: INTEGERCONST
  {
      const auto value = libstdhl::get< libcasm_ir::IntegerConstant >( $1 );
      $$ = Ast::make< Ast::ValueAtom >( @$, value );
  }
;


FloatingNumber
: FLOATINGCONST
  {
      const auto value = libstdhl::get< libcasm_ir::FloatingConstant >( $1 );
      $$ = Ast::make< Ast::ValueAtom >( @$, value );
  }
;


RationalNumber
: RATIONALCONST
  {
      // TODO
  }
;


RuleReference
: AT IDENTIFIER
  {
      const auto value = libstdhl::get< libcasm_ir::RuleReferenceConstant >( $2 );
      $$ = Ast::make< Ast::ValueAtom >( @$, value );
  }
;


Range
: LSQPAREN Atom DOTDOT Atom RSQPAREN
  {
      $$ = Ast::make< Ast::RangeExpression >( @$, $2, $4 );
  }
;


List
: LSQPAREN MaybeExpressions RSQPAREN
  {
      $$ = Ast::make< Ast::ListExpression >( @$, $2 );
  }
;


Expression
: Expression PLUS Expression
  {
      $$ = Ast::make< Ast::BinaryExpression >( @$, $1, $3, libcasm_ir::Value::ADD_INSTRUCTION );
  }
| Expression MINUS Expression
  {
      $$ = Ast::make< Ast::BinaryExpression >( @$, $1, $3, libcasm_ir::Value::SUB_INSTRUCTION );
  }
| Expression STAR Expression
  {
      $$ = Ast::make< Ast::BinaryExpression >( @$, $1, $3, libcasm_ir::Value::MUL_INSTRUCTION );
  }
| Expression SLASH Expression
  {
      $$ = Ast::make< Ast::BinaryExpression >( @$, $1, $3, libcasm_ir::Value::DIV_INSTRUCTION );
  }
| Expression PERCENT Expression
  {
      $$ = Ast::make< Ast::BinaryExpression >( @$, $1, $3, libcasm_ir::Value::MOD_INSTRUCTION );
  }
| Expression NEQUAL Expression
  {
      $$ = Ast::make< Ast::BinaryExpression >( @$, $1, $3, libcasm_ir::Value::NEQ_INSTRUCTION );
  }
| Expression EQUAL Expression
  {
      $$ = Ast::make< Ast::BinaryExpression >( @$, $1, $3, libcasm_ir::Value::EQU_INSTRUCTION );
  }
| Expression LESSER Expression
  {
      $$ = Ast::make< Ast::BinaryExpression >( @$, $1, $3, libcasm_ir::Value::LTH_INSTRUCTION );
  }
| Expression GREATER Expression
  {
      $$ = Ast::make< Ast::BinaryExpression >( @$, $1, $3, libcasm_ir::Value::GTH_INSTRUCTION );
  }
| Expression LESSEQ Expression
  {
      $$ = Ast::make< Ast::BinaryExpression >( @$, $1, $3, libcasm_ir::Value::LEQ_INSTRUCTION );
  }
| Expression GREATEREQ Expression
  {
      $$ = Ast::make< Ast::BinaryExpression >( @$, $1, $3, libcasm_ir::Value::GEQ_INSTRUCTION );
  }
| Expression OR Expression
  {
      $$ = Ast::make< Ast::BinaryExpression >( @$, $1, $3, libcasm_ir::Value::OR_INSTRUCTION );
  }
| Expression XOR Expression
  {
      $$ = Ast::make< Ast::BinaryExpression >( @$, $1, $3, libcasm_ir::Value::XOR_INSTRUCTION );
  }
| Expression AND Expression
  {
      $$ = Ast::make< Ast::BinaryExpression >( @$, $1, $3, libcasm_ir::Value::AND_INSTRUCTION );
  }
| NOT Expression
  {
      $$ = Ast::make< Ast::UnaryExpression >( @$, $2, libcasm_ir::Value::NOT_INSTRUCTION );
  }
| Atom
  {
      $$ = $1;
  }
;


Expressions
: Expressions COMMA Expression
  {
      auto expressions = $1;
      expressions->add( $3 );
      $$ = expressions;
  }
| Expression
  {
      auto expressions = Ast::make< Ast::Expressions >( @$ );
      expressions->add( $1 );
      $$ = expressions;
  }
;


MaybeExpressions
: Expressions
  {
      $$ = $1;
  }
| Expressions COMMA
  {
      $$ = $1;
  }
| %empty
  {
      $$ = Ast::make< Ast::Expressions >( @$ );
  }
;


Arguments
: LPAREN Expressions RPAREN
  {
      $$ = $2;
  }
| LPAREN RPAREN
  {
      $$ = Ast::make< Ast::Expressions >( @$ );
  }
;


MaybeArguments
: Arguments
  {
      $$ = $1;
  }
| Expression
  {
      auto expressions = Ast::make< Ast::Expressions >( @$ );
      expressions->add( $1 );
      $$ = expressions;
  }
| %empty
  {
      $$ = Ast::make< Ast::Expressions >( @$ );
  }
;


DirectCallExpression
: Identifier MaybeArguments
  {
      $$ = Ast::make< Ast::DirectCallExpression >( @$, $1, $2 );
  }
;


IndirectCallExpression
: LPAREN Expression RPAREN Arguments
  {
      $$ = Ast::make< Ast::IndirectCallExpression >( @$, $2, $4 );
  }
;


RuleDefinition
: RULE Identifier MaybeParameters EQUAL Rule
  {
      $$ = Ast::make< Ast::RuleDefinition >( @$, $2, $3, nullptr,
                                             wrapInBlockRule( $5 ) ); // TODO nullptr -> void
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
      auto rules = Ast::make< Ast::Rules >( @$ );
      rules->add( $1 );
      $$ = rules;
  }
;


SkipRule
: SKIP
  {
      $$ = Ast::make< Ast::SkipRule >( @$ );
  }
;


ConditionalRule
: IF Expression THEN Rule
  {
      $$ = Ast::make< Ast::ConditionalRule >( @$, $2, $4 );
  }
| IF Expression THEN Rule ELSE Rule
  {
      $$ = Ast::make< Ast::ConditionalRule >( @$, $2, $4, $6 );
  }
;


CaseRule
: CASE Expression OF LCURPAREN CaseLabels RCURPAREN
  {
      $$ = Ast::make< Ast::CaseRule >( @$, $2, $5 );
  }
;


CaseLabel
: DEFAULT COLON Rule
  {
      // default case
      $$ = Ast::CaseRule::Case( nullptr, $3 );
  }
| UNDERLINE COLON Rule
  {
      // default case
      $$ = Ast::CaseRule::Case( nullptr, $3 );
  }
| Atom COLON Rule
  {
      $$ = Ast::CaseRule::Case( $1, $3 );
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
: LET Variable EQUAL Expression IN Rule
  {
      $$ = Ast::make< Ast::LetRule >( @$, $2, $4, $6 );
  }
;


ForallRule
: FORALL Variable IN Expression DO Rule
  {
      $$ = Ast::make< Ast::ForallRule >( @$, $2, $4, $6 );
  }
;


IterateRule
: ITERATE Rule
  {
      $$ = Ast::make< Ast::IterateRule >( @$, $2 );
  }
;


BlockRule
: LCURPAREN Rules RCURPAREN
  {
      $$ = Ast::make< Ast::BlockRule >( @$, $2 );
  }
| PAR Rules ENDPAR
  {
      $$ = Ast::make< Ast::BlockRule >( @$, $2 );
  }
;


SequenceRule
: SEQ_BRACKET Rules ENDSEQ_BRACKET
  {
      $$ = Ast::make< Ast::SequenceRule >( @$, $2 );
  }
| SEQ Rules ENDSEQ
  {
      $$ = Ast::make< Ast::SequenceRule >( @$, $2 );
  }
;


UpdateRule
: DirectCallExpression UPDATE Expression
  {
      $$ = Ast::make< Ast::UpdateRule >( @$, $1, $3 );
  }
;


CallRule
: CALL DirectCallExpression
  {
      using CallTargetType = Ast::CallExpression::TargetType;
      $$ = Ast::make< Ast::CallRule >( @$, $2, { CallTargetType::Rule } );
  }
| DirectCallExpression
  {
      using CallTargetType = Ast::CallExpression::TargetType;
      $$ = Ast::make< Ast::CallRule >( @$, $1, { CallTargetType::Derived, CallTargetType::Builtin } );
  }
| CALL IndirectCallExpression
  {
      using CallTargetType = Ast::CallExpression::TargetType;
      $$ = Ast::make< Ast::CallRule >( @$, $2, { CallTargetType::Rule } );
  }
| IndirectCallExpression
  {
      using CallTargetType = Ast::CallExpression::TargetType;
      $$ = Ast::make< Ast::CallRule >( @$, $1, { CallTargetType::Derived, CallTargetType::Builtin } );
  }
;

%%

void yy::Parser::error
( const location_type& l
, const std::string& m
)
{
    if( m.compare( "syntax error, unexpected end of file, expecting CASM" ) == 0 )
    {
        i32 pos = (l.begin.line - 1);
        pos = ( pos > 0 ? pos : 1 );

        driver.error
        ( yy::location( yy::position( 0, pos, 1 ) )
        , m
        , libcasm_fe::Codes::SyntaxError
        );
    }
    else
    {
        driver.error( l, m, libcasm_fe::Codes::SyntaxError );
    }
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
