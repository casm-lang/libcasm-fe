//  
//  Copyright (c) 2014-2017 CASM Organization
//  All rights reserved.
//  
//  Developed by: Florian Hahn
//                Philipp Paulweber
//                Emmanuel Pescosta
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
    
    #include "src/Ast.h"
    #include "src/Types.h"
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
        
    void parse_function_attributes
    ( Driver& driver
    , const yy::location& loc
    , const std::vector<std::string>& attribute_names
    , Function* function
    )
    {
        bool is_static = false;
        bool is_symbolic = false;
        bool is_controlled = false;
        
        for( const auto& attribute_name : attribute_names )
        {
            if( attribute_name == "static" )
            {
                if( is_static )
                {
                    driver.error
                    ( loc
                    , "`static` attribute can only be used once per function"
                    , libcasm_fe::Codes::FunctionAttributeMultipleUseOfStatic
                    );
                    break;
                }
                else
                {
                    is_static = true;
                }
            }
            else if( attribute_name == "symbolic" )
            {
                if( is_symbolic )
                {
                    driver.error
                    ( loc
                    , "`symbolic` attribute can only be used once per function"
                    , libcasm_fe::Codes::FunctionAttributeMultipleUseOfSymbolic
                    );
                    break;
                }
                else
                {
                    is_symbolic = true;
                }
            }
            else if( attribute_name == "controlled" )
            {
                if( is_controlled )
                {
                    driver.error
                    ( loc
                    , "`controlled` attribute can only be used once per function"
                      , libcasm_fe::Codes::FunctionAttributeMultipleUseOfControlled
                    );
                    break;
                }
                else
                {
                    is_controlled = true;
                }
            }
            else
            {
                driver.error
                ( loc
                , "`"+attribute_name+"` is no valid function attribute, only static, symbolic and controlled are allowed"
                , libcasm_fe::Codes::FunctionAttributeIsInvalid
                );
            }
        }
        if( is_static && is_controlled )
        {
            driver.error
            ( loc
            , "attributes `controlled` and `static` are mutually exclusive"
            , libcasm_fe::Codes::FunctionAttributeControlledAndStaticIsInvalid
            );
        }
        
        function->is_static = is_static;
        function->is_symbolic = is_symbolic;
    }
}


%token
END       0 "end of file"
{{grammartoken}}
;

%token FLOATINGCONST "floating"
%token INTEGERCONST  "integer"
%token RATIONALCONST "rational"
%token STRCONST      "string"
%token <std::string> IDENTIFIER "identifier"


%type <Ast*> SPECIFICATION
%type <SpecificationNode*> HEADER
%type <InitNode*> INIT_SYNTAX
%type <AstNode*> BODY_ELEMENT RULE_SYNTAX STATEMENT IMPOSSIBLE_SYNTAX RULE_STMT SIMPLE_STMT SCOPE
%type <UnaryNode*> PAR_SYNTAX SEQ_SYNTAX ASSERT_SYNTAX ASSURE_SYNTAX ITERATE_SYNTAX
%type <AstListNode*> BODY_ELEMENTS STATEMENTS
%type <AtomNode*> UNDEFINED BOOLEAN NUMBER VALUE NUMBER_RANGE
%type <IntegerAtom*> INTEGER_NUMBER 
%type <FloatingAtom*> FLOATING_NUMBER 
%type <RationalAtom*> RATIONAL_NUMBER 
%type <std::pair<ExpressionBase*, ExpressionBase*>> INITIALIZER
%type <std::vector<std::pair<ExpressionBase*, ExpressionBase*>>*> INITIALIZER_LIST INITIALIZERS
%type <ExpressionBase*> EXPRESSION ATOM
%type <std::vector<ExpressionBase*>*> EXPRESSION_LIST EXPRESSION_LIST_NO_COMMA LISTCONST
%type <UpdateNode*> UPDATE_SYNTAX
%type <INTEGER_T> INTEGERCONST
%type <FLOATING_T> FLOATINGCONST
%type <std::string> STRCONST
%type <rational_t> RATIONALCONST
%type <Function*> FUNCTION_DEFINITION DERIVED_SYNTAX
%type <BaseFunctionAtom*> FUNCTION_SYNTAX
%type <std::pair<std::vector<Type*>, Type*>> FUNCTION_SIGNATURE
%type <Type*> TYPE_SYNTAX
%type <Type*> PARAM
%type <std::vector<Type*>> PARAM_LIST_NO_COMMA PARAM_LIST
%type <std::vector<Type*>> TYPE_IDENTIFIER_STARLIST
%type <std::string> RULEREF
%type <IfThenElseNode*> IFTHENELSE
%type <CallNode*> CALL_SYNTAX
%type <PrintNode*> PRINT_SYNTAX DEBUG_SYNTAX
%type <LetNode*> LET_SYNTAX
%type<std::vector<Type*>> TYPE_SYNTAX_LIST
%type <PushNode*> PUSH_SYNTAX
%type <PopNode*> POP_SYNTAX
%type <AtomNode*> CASE_VALUE
%type <std::pair<AtomNode*, AstNode*>> CASE_LABEL
%type <std::vector<std::pair<AtomNode*, AstNode*>>> CASE_LABEL_LIST
%type <CaseNode*> CASE_SYNTAX
%type <ForallNode*> FORALL_SYNTAX
%type <std::vector<std::string>> IDENTIFIER_LIST IDENTIFIER_LIST_NO_COMMA
%type <Enum*> ENUM_SYNTAX;
%type <std::vector<std::pair<std::string, std::vector<std::string>>>> DUMPSPEC_LIST
%type <std::pair<std::string, std::vector<std::string>>> DUMPSPEC
%type <DiedieNode*> DIEDIE_SYNTAX


%start SPECIFICATION
     
%precedence THEN
%precedence ELSE

//%precedence UPDATE ASSERT ASSURE DIEDIE
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

     
SPECIFICATION
: HEADER BODY_ELEMENTS
  {
      driver.result = new Ast( @$, $1, $2 );
  }
;


HEADER
: CASM
  {
      const std::string& filepath = driver.get_filename();
      
      const std::string& filename
          = filepath.substr( filepath.find_last_of( "/\\" ) + 1 );
      
      const std::string& filename_without_extension
          = filename.substr( 0, filename.rfind( "." ) );
      
      $$ = new SpecificationNode( @$, filename_without_extension );
  }
;

BODY_ELEMENTS
: BODY_ELEMENTS BODY_ELEMENT
  {
      $1->add($2);
      $$ = $1;
  }
| BODY_ELEMENT
  {
      $$ = new AstListNode(@$, NodeType::BODY_ELEMENTS);
      $$->add($1);
  }
;


BODY_ELEMENT
: OPTION_SYNTAX
  {
      $$ = new AstNode( NodeType::OPTION );
  }
| ENUM_SYNTAX
  {
      $$ = new EnumDefNode( @$, $1 );
  }
| FUNCTION_DEFINITION
  {
      $$ = new FunctionDefNode( @$, $1 );
      
      if( $1->is_builtin() )
      {
          driver.error
          ( @$
          , "cannot use builtin name '"
            + $1->name
            + "' as function identifier"
          , libcasm_fe::Codes::FunctionIdentifierIsBuiltinName
          );
      }
      
      try
      {
          driver.add( $1 );
      }
      catch( const Exception& e )
      {
          driver.error
          ( e.getLocations()
          , e.what()
          , e.getErrorCode()
          );
          
          // if another symbol with same name exists we need to delete
          // the symbol here, because it is not inserted in the symbol table
          delete $1;
      }
  }
| DERIVED_SYNTAX
  {
      $1->binding_offsets = std::move( driver.binding_offsets );
      driver.binding_offsets.clear();
      
      $$ = new FunctionDefNode( @$, $1 );
      try
      {
          driver.add( $1 );
      }
      catch( const Exception& e )
      {
          driver.error
          ( e.getLocations()
          , e.what()
          , e.getErrorCode()
          );
          
          // if another symbol with same name exists we need to delete
          // the symbol here, because it is not inserted in the symbol table
          delete $1;
      }
  }
| INIT_SYNTAX
  {
      $$ = $1;
  }
| RULE_SYNTAX
  {
      $$ = $1;
      // TODO: check, we trust bison to pass only RuleNodes up
      
      try
      {
          driver.add( reinterpret_cast< RuleNode* >( $1 ) );
      }
      catch( const Exception& e )
      {
          driver.error
          ( e.getLocations()
          , e.what()
          , e.getErrorCode()
          );
          
          // we do not need to delete $1 here, because it's already in
          // the AST, so it will be deleted later
      }
  }
;


INIT_SYNTAX
: INIT IDENTIFIER
  {
      static InitNode* init_node = 0;

      if( not init_node )
      {
          init_node = new InitNode( @$, $2 );
      }
      else
      {
          static u1 flag = true;
          
          if( flag )
          {
              flag = false;
              
              driver.error
              ( init_node->location
              , "multiple definition of 'init' node"
              , libcasm_fe::Codes::AgentInitRuleMultipleDefinitions
              );
          }
          
          driver.error
          ( @$
          , "multiple definition of 'init' node"
          , libcasm_fe::Codes::AgentInitRuleMultipleDefinitions
          );
      }
      
      $$ = init_node;
  }
;


OPTION_SYNTAX
: OPTION IDENTIFIER DOT IDENTIFIER IDENTIFIER
;


ENUM_SYNTAX
: ENUM IDENTIFIER EQUAL LCURPAREN IDENTIFIER_LIST RCURPAREN
  {
      $$ = new Enum($2, @$);
      try
      {
          driver.function_table.add($$);
      }
      catch( const Exception& e )
      {
          driver.error
          ( e.getLocations()
          , e.what()
          , e.getErrorCode()
          );
      }
      for( const std::string& name : $5 )
      {
          if( $$->add_enum_element(name) )
          {
              try
              {
                  driver.function_table.add_enum_element( name, $$ );
              }
              catch( const Exception& e )
              {
                  driver.error
                  ( e.getLocations()
                  , e.what()
                  , e.getErrorCode()
                  );
              }
          }
          else
          {
              driver.error
              ( @$
              , "name '"
                + name
                + "' already used in enum"
              );
          }
      }
  }
;


DERIVED_SYNTAX
: DERIVED IDENTIFIER LPAREN PARAM_LIST RPAREN EQUAL EXPRESSION
  {
      // TODO: 2nd argument should be a reference
      $$ = new Function($2, @$, $4, $7, new Type(TypeType::UNKNOWN));
  }
| DERIVED IDENTIFIER EQUAL EXPRESSION
  {
      $$ = new Function($2, @$, $4, new Type(TypeType::UNKNOWN));
  }
| DERIVED IDENTIFIER LPAREN RPAREN EQUAL EXPRESSION
  {
      $$ = new Function($2, @$, $6, new Type(TypeType::UNKNOWN));
  }
| DERIVED IDENTIFIER LPAREN PARAM_LIST RPAREN COLON TYPE_SYNTAX EQUAL EXPRESSION
  {
      $$ = new Function($2, @$, $4, $9, $7);
  }
| DERIVED IDENTIFIER COLON TYPE_SYNTAX EQUAL EXPRESSION
  {
      $$ = new Function($2, @$, $6, $4);
  }
| DERIVED IDENTIFIER LPAREN RPAREN COLON TYPE_SYNTAX EQUAL EXPRESSION
  {
      $$ = new Function($2, @$, $8, $6);
  }
;


FUNCTION_DEFINITION
: FUNCTION LPAREN IDENTIFIER_LIST RPAREN IDENTIFIER FUNCTION_SIGNATURE INITIALIZERS
  {
      auto function = new Function($5, @$, $6.first, $6.second, $7);
      parse_function_attributes(driver, @$, $3, function);
      $$ = function;
  }
| FUNCTION LPAREN IDENTIFIER_LIST RPAREN IDENTIFIER FUNCTION_SIGNATURE
  {
      auto function = new Function($5, @$, $6.first, $6.second, nullptr);
      parse_function_attributes(driver, @$, $3, function);
      $$ = function;
  }
| FUNCTION IDENTIFIER FUNCTION_SIGNATURE INITIALIZERS
  {
      $$ = new Function($2, @$, $3.first, $3.second, $4);
  }
| FUNCTION IDENTIFIER FUNCTION_SIGNATURE
  {
      $$ = new Function($2, @$, $3.first, $3.second, nullptr);
  }
;

IDENTIFIER_LIST
: IDENTIFIER_LIST_NO_COMMA COMMA
  {
      $$ = std::move($1);
  }
| IDENTIFIER_LIST_NO_COMMA
  {
      $$ = std::move($1);
  }
;


IDENTIFIER_LIST_NO_COMMA
: IDENTIFIER_LIST_NO_COMMA COMMA IDENTIFIER
  {
      $$ = std::move( $1 );
      $$.push_back( $3 );
  }
| IDENTIFIER
  {
      $$ = std::vector<std::string>();
      $$.push_back($1);
  }
;


FUNCTION_SIGNATURE
: COLON ARROW TYPE_SYNTAX
  {
      /* this constructor is implementation dependant! */
      std::vector<Type*> foo;
      $$ = std::pair<std::vector<Type*>, Type*>(foo, $3);
  }
| COLON TYPE_IDENTIFIER_STARLIST ARROW TYPE_SYNTAX
  {
      $$ = std::pair<std::vector<Type*>, Type*>($2, $4);
  }
;


PARAM
: IDENTIFIER COLON TYPE_SYNTAX
  {
      size_t size = driver.binding_offsets.size();
      driver.binding_offsets[$1] = size;
      $$ = $3;
  }
| IDENTIFIER
  {
      size_t size = driver.binding_offsets.size();
      driver.binding_offsets[$1] = size;
      // TODO: fail for rules without types and print warnings
      $$ = new Type(TypeType::INTEGER);
  }
;


PARAM_LIST
: PARAM_LIST_NO_COMMA
  {
      $$ = std::move($1);
  }
| PARAM_LIST_NO_COMMA COMMA
  {
      $$ = std::move($1);
  }
;


PARAM_LIST_NO_COMMA
: PARAM_LIST_NO_COMMA COMMA PARAM
  {
      $$ = std::move($1);
      $$.push_back($3);
  }
| PARAM
  {
      $$.push_back($1);
  }
;


TYPE_IDENTIFIER_STARLIST
: TYPE_SYNTAX STAR TYPE_IDENTIFIER_STARLIST
  {
      $3.insert($3.begin(), $1);
      $$ = std::move($3);
  }
| TYPE_SYNTAX STAR
  {
      // TODO: limit memory size
      $$.push_back($1);
  }
| TYPE_SYNTAX
  {
      $$.push_back($1);
  }
;


TYPE_SYNTAX
: IDENTIFIER
  {
      $$ = new Type( $1 );
      
      // TODO: FUTURE: integrate the IR-based type-list here to perform checks!,
      //               or maybe we should check everything in the typecheckpass?
      if( $1.compare( "Bit" ) == 0 )
      {
          driver.error
          ( @$
          , "missing bit-size for Bit type 'Bit(<bitsize>)'"
          , libcasm_fe::Codes::TypeBitSyntaxError
          );
      }
      else if( $1.compare( "List" ) == 0 )
      {
          driver.error
          ( @$
          , "unsupported type '" + $1 + "'"
          , libcasm_fe::Codes::TypeUnsupported
          );
      }      
  }
| IDENTIFIER LPAREN INTEGER_NUMBER RPAREN
  {
      $$ = new Type( $1 );
      $$->bitsize = $3->val_;
      if( $$->bitsize <= 0 || $$->bitsize > 256 )
      {
          driver.error
          ( @$
          , "invalid bit-size for Bit type, must between 1 <= x <= 256"
          , libcasm_fe::Codes::TypeBitSizeIsInvalid
          );
      }
  }
| IDENTIFIER LPAREN TYPE_SYNTAX_LIST RPAREN
  {
      $$ = new Type( $1, $3 );

      if( $1.compare( "List" ) == 0 )
      {
          driver.error
          ( @$
          , "unsupported type '" + $1 + "'"
          , libcasm_fe::Codes::TypeUnsupported
          );
      }
      // TODO: FUTURE: PPA: better and generic type checking in the type check pass
      else if( $1.compare( "Tuple" ) != 0 )
      {
          driver.error
          ( @$
          , "unknown type '" + $1 + "'"
          , libcasm_fe::Codes::TypeUnknown
          );
      }      
  }
| IDENTIFIER LPAREN INTEGER_NUMBER DOTDOT INTEGER_NUMBER RPAREN
  {
      $$ = new Type( $1 );
      $$->subrange_start = $3->val_;
      $$->subrange_end = $5->val_;
      if( $$->subrange_start >= $$->subrange_end )
      {
          driver.error
          ( @$
          , "start of subrange must be smaller than the end"
          , libcasm_fe::Codes::TypeIntegerRangedInvalidInterval
          );
      }
  }
;


TYPE_SYNTAX_LIST
: TYPE_SYNTAX COMMA TYPE_SYNTAX_LIST
  {
      $3.push_back( $1 );
      $$ = std::move( $3 );
  }
| TYPE_SYNTAX COMMA
  {
      $$.push_back( $1 );
  }
| TYPE_SYNTAX
  {
      $$.push_back( $1 );
  }
;


INITIALIZERS
: INITIALLY LCURPAREN INITIALIZER_LIST RCURPAREN
  {
      $$ = $3;
  }
| INITIALLY LCURPAREN RCURPAREN
  {
      $$ = nullptr;
  }
;


INITIALIZER_LIST
: INITIALIZER_LIST COMMA INITIALIZER
  {
      $$ = $1; $1->push_back( $3 );
  }
| INITIALIZER_LIST COMMA
  {
      $$ = $1;
  }
| INITIALIZER
  {
      $$ = new std::vector< std::pair<ExpressionBase*, ExpressionBase* > >();
      $$->push_back( $1 );
  }
;


INITIALIZER
: ATOM
  {
      $$ = std::pair<ExpressionBase*, ExpressionBase*>(nullptr, $1);
  }
| ATOM ARROW ATOM
  {
      $$ = std::pair<ExpressionBase*, ExpressionBase*>($1, $3);
  }
;


ATOM
: FUNCTION_SYNTAX
  {
      $$ = $1;
  }
| VALUE
  {
      $$ = $1;
  }
| LPAREN EXPRESSION RPAREN
  {
      $$ = $2;
  }
| PLUS LPAREN EXPRESSION RPAREN %prec UPLUS
  {
      $$ = $3;
  }
| MINUS LPAREN EXPRESSION RPAREN %prec UMINUS
  {
      $$ = new BinaryExpression( @$, new ZeroAtom( @$, $3 ), $3,
                                 libcasm_ir::Value::SUB_INSTRUCTION );
  }
;


VALUE
: RULEREF
  {
      $$ = new RuleAtom( @$, std::move( $1 ) );
  }
| NUMBER
  {
      $$ = $1;
  }
| STRCONST
  {
      $$ = new StringAtom( @$, std::move( $1 ) );
  }
| LISTCONST
  {
      $$ = new ListAtom( @$, $1 );
  }
| NUMBER_RANGE
  {
      $$ = $1;
  }
| SELF
  {
      $$ = new SelfAtom( @$ );
  }
| UNDEFINED
  {
      $$ = $1; 
  }
| BOOLEAN
  {
      $$ = $1;
  }
;


UNDEFINED
: UNDEF
  {
      $$ = new UndefAtom( @$ );
  }
;


BOOLEAN
: TRUE
  {
      $$ = new BooleanAtom( @$, true );
  }
| FALSE
  {
      $$ = new BooleanAtom( @$, false );
  }
; 


NUMBER
: INTEGER_NUMBER
  {
      $$ = $1;
  }
| FLOATING_NUMBER
  {
      $$ = $1;
  }
| RATIONAL_NUMBER
  {
      $$ = $1;
  }
;


INTEGER_NUMBER
: INTEGERCONST
  {
      $$ = new IntegerAtom( @$, $1 );
  }
| PLUS INTEGER_NUMBER %prec UPLUS
  {
      $$ = $2;
  }
| MINUS INTEGER_NUMBER %prec UMINUS
  {
      $$ = $2;
      $2->val_ *= (-1);
  }
;


FLOATING_NUMBER
: FLOATINGCONST
  {
      $$ = new FloatingAtom( @$, $1 );
  }
| PLUS FLOATING_NUMBER %prec UPLUS
  {
      $$ = $2;
  }
| MINUS FLOATING_NUMBER %prec UMINUS
  {
      $$ = $2;
      $2->val_ *= (-1);
  }
;


RATIONAL_NUMBER
: RATIONALCONST
  {
      $$ = new RationalAtom( @$, $1 );
  }
| PLUS RATIONAL_NUMBER %prec UPLUS
  {
      $$ = $2;
  }
| MINUS RATIONALCONST %prec UMINUS
  {
      $2.numerator *= -1;
      $$ = new RationalAtom( @$, $2 );
  }
;


RULEREF
: AT IDENTIFIER
  {
      $$ = $2;
  }
;


NUMBER_RANGE
: LSQPAREN EXPRESSION DOTDOT EXPRESSION RSQPAREN
  {
      $$ = new NumberRangeAtom( @$, $2, $4 );
  }
;


LISTCONST
: LSQPAREN EXPRESSION_LIST RSQPAREN
  {
      $$ = $2;
  }
| LSQPAREN RSQPAREN
  {
      $$ = new std::vector< ExpressionBase* >();
  }
;


EXPRESSION_LIST
: EXPRESSION_LIST_NO_COMMA
  {
      $$ = $1;
  }
| EXPRESSION_LIST_NO_COMMA COMMA
  {
      $$ = $1;
  }
;


EXPRESSION_LIST_NO_COMMA
: EXPRESSION_LIST_NO_COMMA COMMA EXPRESSION
  {
      $$ = $1;
      $$->push_back( $3 );
  }
| EXPRESSION
  {
      $$ = new std::vector< ExpressionBase* >;
      $$->push_back( $1 );
  }
;


EXPRESSION
: EXPRESSION PLUS EXPRESSION
  {
      $$ = new BinaryExpression( @$, $1, $3, libcasm_ir::Value::ADD_INSTRUCTION );
  }
| EXPRESSION MINUS EXPRESSION
  {
      $$ = new BinaryExpression( @$, $1, $3, libcasm_ir::Value::SUB_INSTRUCTION );
  }
| EXPRESSION STAR EXPRESSION
  {
      $$ = new BinaryExpression( @$, $1, $3, libcasm_ir::Value::MUL_INSTRUCTION );
  }
| EXPRESSION SLASH EXPRESSION
  {
      $$ = new BinaryExpression( @$, $1, $3, libcasm_ir::Value::DIV_INSTRUCTION );
  }
| EXPRESSION PERCENT EXPRESSION
  {
      $$ = new BinaryExpression( @$, $1, $3, libcasm_ir::Value::MOD_INSTRUCTION );
  }
| EXPRESSION NEQUAL EXPRESSION
  {
      $$ = new BinaryExpression( @$, $1, $3, libcasm_ir::Value::NEQ_INSTRUCTION );
  }
| EXPRESSION EQUAL EXPRESSION
  {
      $$ = new BinaryExpression( @$, $1, $3, libcasm_ir::Value::EQU_INSTRUCTION );
  }
| EXPRESSION LESSER EXPRESSION
  {
      $$ = new BinaryExpression( @$, $1, $3, libcasm_ir::Value::LTH_INSTRUCTION );
  }
| EXPRESSION GREATER EXPRESSION
  {
      $$ = new BinaryExpression( @$, $1, $3, libcasm_ir::Value::GTH_INSTRUCTION );
  }
| EXPRESSION LESSEQ EXPRESSION
  {
      $$ = new BinaryExpression( @$, $1, $3, libcasm_ir::Value::LEQ_INSTRUCTION );
  }
| EXPRESSION GREATEREQ EXPRESSION
  {
      $$ = new BinaryExpression( @$, $1, $3, libcasm_ir::Value::GEQ_INSTRUCTION );
  }
| EXPRESSION OR EXPRESSION
  {
      $$ = new BinaryExpression( @$, $1, $3, libcasm_ir::Value::OR_INSTRUCTION );
  }
| EXPRESSION XOR EXPRESSION
  {
      $$ = new BinaryExpression( @$, $1, $3, libcasm_ir::Value::XOR_INSTRUCTION );
  }
| EXPRESSION AND EXPRESSION
  {
      $$ = new BinaryExpression( @$, $1, $3, libcasm_ir::Value::AND_INSTRUCTION );
  }
| NOT EXPRESSION
  {
      $$ = new UnaryExpression( @$, $2, libcasm_ir::Value::NOT_INSTRUCTION );
  }
| ATOM
  {
      $$ = $1;
  }
;


FUNCTION_SYNTAX
: IDENTIFIER
  {
      $$ = new FunctionAtom( @$, $1 );
  }
| IDENTIFIER LPAREN RPAREN
  {
      $$ = new FunctionAtom( @$, $1 );
  }
| IDENTIFIER LPAREN EXPRESSION_LIST RPAREN
  {
      if( Builtin::isBuiltin( $1 ) )
      {
          $$ = new BuiltinAtom( @$, $1, $3 );
      }
      else
      {
          $$ = new FunctionAtom( @$, $1, $3 );
      }
  }
;


SCOPE
: SEQ_SYNTAX
  {
      $$ = $1;
  }
| PAR_SYNTAX
  {
      $$ = $1;
  }
; 


RULE_STMT
: SCOPE
  {
      $$ = $1;
  }
| SIMPLE_STMT
  {
      auto stmts = new AstListNode( @$, NodeType::STATEMENTS );
      stmts->add( $1 );
      $$ = new UnaryNode( @$, NodeType::PARBLOCK, stmts );
  }
;


RULE_SYNTAX
: RULE IDENTIFIER EQUAL RULE_STMT
  {
      $$ = new RuleNode( @$, $4, $2 );
  }
| RULE IDENTIFIER LPAREN RPAREN EQUAL RULE_STMT
  {
      $$ = new RuleNode( @$, $6, $2 );
  }
| RULE IDENTIFIER LPAREN PARAM_LIST RPAREN EQUAL RULE_STMT
  {
      $$ = new RuleNode( @$, $7, $2, $4 );
  }
| RULE IDENTIFIER DUMPS DUMPSPEC_LIST EQUAL RULE_STMT
  {
      std::vector< Type* > tmp;
      $$ = new RuleNode( @$, $6, $2, tmp, $4 );
  }
| RULE IDENTIFIER LPAREN RPAREN DUMPS DUMPSPEC_LIST EQUAL RULE_STMT
  {
      std::vector< Type* > tmp;
      $$ = new RuleNode( @$, $8, $2, tmp, $6 );
  }
| RULE IDENTIFIER LPAREN PARAM_LIST RPAREN DUMPS DUMPSPEC_LIST EQUAL RULE_STMT
  {
      std::vector< Type* > tmp;
      $$ = new RuleNode( @$, $9, $2, tmp, $7 );
  }
;


DUMPSPEC_LIST
: DUMPSPEC_LIST COMMA DUMPSPEC
  {
      $$ = std::move( $1 );
      $$.push_back( $3 );
  }
| DUMPSPEC
  {
      $$ = std::vector< std::pair< std::string, std::vector<std::string> > >();
      $$.push_back( std::move( $1 ) );
  }
;


DUMPSPEC
: LPAREN IDENTIFIER_LIST RPAREN ARROW IDENTIFIER
  {
      $$ = std::pair< std::string, std::vector< std::string > >( $5, $2 );
  }
;


SIMPLE_STMT
: ASSERT_SYNTAX
  {
      $$ = $1;
  }
| ASSURE_SYNTAX
  {
      $$ = $1;
  }
| DIEDIE_SYNTAX
  {
      $$ = $1;
  }
| IMPOSSIBLE_SYNTAX
  {
      $$ = $1;
  }
| DEBUG_SYNTAX
  {
      $$ = $1;
  }
| PRINT_SYNTAX
  {
      $$ = $1;
  }
| UPDATE_SYNTAX
  {
      $$ = $1;
  }
| CASE_SYNTAX
  {
      $$ = $1;
  }
| CALL_SYNTAX
  {
      $$ = $1;
  }
| IFTHENELSE
  {
      $$ = $1;
  }
| LET_SYNTAX
  {
      $$ = $1;
  }
| PUSH_SYNTAX
  {
      $$ = $1;
  }
| POP_SYNTAX
  {
      $$ = $1;
  }
| FORALL_SYNTAX
  {
      $$ = $1;
  }
| ITERATE_SYNTAX
  {
      $$ = $1;
  }
| SKIP
  {
      $$ = new AstNode( NodeType::SKIP );
  }
| IDENTIFIER
  {
      driver.error
      ( @$
      , "invalid statement '" + $1 + "' found"
      , libcasm_fe::Codes::SyntaxErrorInvalidStatement
      );
  }
//   INTERN EXPRESSION_LIST
//   {
//       $$ = new AstNode( NodeType::STATEMENT );
//   }
//   OBJDUMP "(" IDENTIFIER ")"
//   {
//       $$ = new AstNode( NodeType::STATEMENT );
//   }
;


STATEMENT
: SCOPE
  {
      $$ = $1;
  }
| SIMPLE_STMT
  {
      $$ = $1;
  }
;


ASSERT_SYNTAX
: ASSERT EXPRESSION
  {
      $$ = new UnaryNode( @$, NodeType::ASSERT, $2 );
  }
;


ASSURE_SYNTAX
: ASSURE EXPRESSION
  {
      $$ = new UnaryNode( @$, NodeType::ASSURE, $2 );
  }
;


DIEDIE_SYNTAX
: DIEDIE EXPRESSION
  {
      $$ = new DiedieNode( @$, $2 );
  }
| DIEDIE
  {
      $$ = new DiedieNode( @$, nullptr );
  }
;


/* when symbolic execution:
    * abort trace
    * do not write it
    * no error
  in concrete mode:
    * an error like diedie
*/

IMPOSSIBLE_SYNTAX
: IMPOSSIBLE
  {
      $$ = new AstNode( @$, NodeType::IMPOSSIBLE );
  }
;


PRINT_SYNTAX
: PRINT EXPRESSION
  {
      $$ = new PrintNode( @$, $2 );
  }
;


DEBUG_SYNTAX
: DEBUG IDENTIFIER EXPRESSION
  {
      $$ = new PrintNode( @$, $3, $2 );
  }
;


UPDATE_SYNTAX
: FUNCTION_SYNTAX UPDATE EXPRESSION
  {
      if( $1->node_type_ == NodeType::FUNCTION_ATOM )
      {
          $$ = new UpdateNode( @$, reinterpret_cast< FunctionAtom* >( $1 ), $3 );
      }
      else
      {
          driver.error
          ( @$
          , "can only use functions for updates but '"
            + $1->to_str()
            + "` is a '"
            + type_to_str( $1->node_type_ )
          );
      }
  }
;


CASE_SYNTAX
: CASE EXPRESSION OF LCURPAREN CASE_LABEL_LIST RCURPAREN
  {
      $$ = new CaseNode( @$, $2, $5 );
  }
;


CASE_LABEL_LIST
: CASE_LABEL CASE_LABEL_LIST
  {
      $$ = std::move( $2 );
      $$.push_back( $1 );
  }
| CASE_LABEL
  {
      $$ = std::vector< std::pair< AtomNode*, AstNode* > >();
      $$.push_back( $1 );
  }
;


CASE_LABEL
: CASE_VALUE COLON STATEMENT
  {
      $$ = std::pair< AtomNode*, AstNode* >( $1, $3 );
  }
;


CASE_VALUE
: DEFAULT
  {
      $$ = nullptr;
  }
| UNDERLINE
  {
      // equivalent to 'default' 
      $$ = nullptr;
  }
| UNDEFINED
  {
      $$ = $1;
  }
| BOOLEAN
  {
      $$ = $1;
  }
| NUMBER
  {
      $$ = $1;
  }
| STRCONST
  {
      $$ = new StringAtom( @$, std::move( $1 ) );
  }
| FUNCTION_SYNTAX
  {
      $$ = $1;
  }
;


CALL_SYNTAX
: CALL LPAREN EXPRESSION RPAREN LPAREN EXPRESSION_LIST RPAREN
  {
      $$ = new CallNode( @$, "", $3, $6 );
  }
| CALL LPAREN EXPRESSION RPAREN
  {
      $$ = new CallNode( @$, "", $3 );
  }
| CALL IDENTIFIER LPAREN EXPRESSION_LIST RPAREN
  {
      $$ = new CallNode( @$, $2, nullptr, $4 );
  }
| CALL IDENTIFIER
  {
      $$ = new CallNode( @$, $2, nullptr );
  }
;


SEQ_SYNTAX
: SEQ_BRACKET STATEMENTS ENDSEQ_BRACKET
  {
      $$ = new UnaryNode( @$, NodeType::SEQBLOCK, $2 );
  }
| SEQ STATEMENTS ENDSEQ
  {
      $$ = new UnaryNode( @$, NodeType::SEQBLOCK, $2 );
  }
;


PAR_SYNTAX
: LCURPAREN STATEMENTS RCURPAREN
  {
      $$ = new UnaryNode( @$, NodeType::PARBLOCK, $2 );
  }
| PAR STATEMENTS ENDPAR
  {
      $$ = new UnaryNode( @$, NodeType::PARBLOCK, $2 );
  }
;


STATEMENTS
: STATEMENTS STATEMENT
  {
      $1->add( $2 );
      $$ = $1;
  }
| STATEMENT
  {
      $$ = new AstListNode( @$, NodeType::STATEMENTS );
      $$->add( $1 );
  }
;


IFTHENELSE
: IF EXPRESSION THEN STATEMENT
  {
      $$ = new IfThenElseNode( @$, $2, $4, nullptr );
  }
| IF EXPRESSION THEN STATEMENT ELSE STATEMENT
  {
      $$ = new IfThenElseNode( @$, $2, $4, $6 );
  }
;



LET_SYNTAX
: LET IDENTIFIER EQUAL
  {
      auto var = Symbol( $2, @$, Symbol::SymbolType::LET );
      try
      {
          driver.function_table.add( &var );      
      }
      catch( const Exception& e)
      {
          driver.error( @$, e.what() );
      }
  }
  EXPRESSION IN STATEMENT
  {
      driver.function_table.remove( $2 );
      $$ = new LetNode( @$, Type( TypeType::UNKNOWN ), $2, $5, $7 );
  }
| LET IDENTIFIER COLON TYPE_SYNTAX EQUAL
  {
      auto var = Symbol( $2, @$, Symbol::SymbolType::LET );
      try
      {
          driver.function_table.add( &var );
      }
      catch( const Exception& e)
      {
          driver.error( @$, e.what() );
      }
  }
  EXPRESSION IN STATEMENT
  {
      driver.function_table.remove( $2 );
      $$ = new LetNode( @$, $4, $2, $7, $9 );
  }
;


PUSH_SYNTAX
: PUSH EXPRESSION INTO FUNCTION_SYNTAX
  {
      if( $4->node_type_ == NodeType::BUILTIN_ATOM )
      {
          driver.error( @$, "cannot push to builtin '" + $4->to_str() + "'" );
      }
      else
      {
          $$ = new PushNode( @$, $2, reinterpret_cast< FunctionAtom* >( $4 ) );
      }
  }
;


POP_SYNTAX
: POP FUNCTION_SYNTAX FROM FUNCTION_SYNTAX
  {
      if( $2->node_type_ == NodeType::BUILTIN_ATOM )
      {
          driver.error( @$, "cannot pop to builtin '" + $2->to_str() + "'" );
      }
      else if( $4->node_type_ == NodeType::BUILTIN_ATOM )
      {
          driver.error( @$, "cannot pop from builtin '" + $4->to_str() + "'" );
      }
      else
      {
          $$ = new PopNode
          ( @$
          , reinterpret_cast< FunctionAtom* >( $2 )
          , reinterpret_cast< FunctionAtom* >( $4 )
          );
      }
  }
;


FORALL_SYNTAX
: FORALL IDENTIFIER IN EXPRESSION DO STATEMENT
  {
      $$ = new ForallNode( @$, $2, $4, $6 );
  }
;




ITERATE_SYNTAX
: ITERATE STATEMENT
  {
      $$ = new UnaryNode( @$, NodeType::ITERATE, $2 );
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
