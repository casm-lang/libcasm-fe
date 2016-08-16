//  
//  Copyright (c) 2014-2016 CASM Organization
//  All rights reserved.
//  
//  Developed by: Florian Hahn
//                Philipp Paulweber
//                Emmanuel Pescosta
//                https://github.com/ppaulweber/libcasm-fe
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
%define parser_class_name {casmi_parser}

%define api.token.constructor
%define api.value.type variant
%define parse.assert


%code requires
{
    #include <cstdint>
    #include <string>
    #include <utility>

    #include "src/Ast.h"
    #include "src/Types.h"
    #include "src/Codes.h"
    class Driver;
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

%code {
    #include "src/Driver.h"
    #include "src/Codes.h"

    std::pair<bool, bool> parse_function_attributes
    ( Driver& driver
    , const yy::location& loc
    , const std::vector<std::string>& attribute_names
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
		
        return std::pair<bool, bool>(is_static, is_symbolic);
    }
}

%token AND OR XOR NOT ASSERT ASSURE DIEDIE IMPOSSIBLE SKIP SEQ ENDSEQ
%token PAR ENDPAR LET IN IF THEN ELSE PRINT DEBUG DUMPS PUSH INTO
%token POP FROM FORALL ITERATE DO CALL CASE DEFAULT OF ENDCASE INITIALLY FUNCTION
%token DERIVED ENUM RULE PROVIDER INIT OPTION SELF UNDEF TRUE FALSE CASM SYMBOL
%token INTERN RATIONAL_DIV OBJDUMP

%token DOTDOT ARROW UPDATE NEQUAL LESSEQ GREATEREQ SEQ_BRACKET ENDSEQ_BRACKET

%token
    END  0  "end of file"
    PLUS    "+"
    MINUS   "-"
    EQ      "="
    LPAREN  "("
    RPAREN  ")"
    LSQPAREN  "["
    RSQPAREN  "]"
    LCURPAREN  "{"
    RCURPAREN  "}"
    DOT "."
    COLON ":"
    AT "@"
    COMMA ","
    LESSER "<"
    GREATER ">"
    STAR    "*"
    SLASH   "/"
    PERCENT "%"
    ;
%token FLOATINGCONST INTEGERCONST RATIONALCONST STRCONST
%token <std::string> IDENTIFIER "identifier"

%type <Ast*> SPECIFICATION
%type <SpecificationNode*> HEADER
%type <InitNode*> INIT_SYNTAX
%type <AstNode*> BODY_ELEMENT RULE_SYNTAX STATEMENT IMPOSSIBLE_SYNTAX RULE_STMT SIMPLE_STMT
%type <UnaryNode*> PAR_SYNTAX SEQ_SYNTAX ASSERT_SYNTAX ASSURE_SYNTAX ITERATE_SYNTAX
%type <AstListNode*> BODY_ELEMENTS STATEMENTS
%type <AtomNode*> NUMBER VALUE NUMBER_RANGE
%type <IntegerAtom*> INTEGER_NUMBER 
%type <std::pair<ExpressionBase*, ExpressionBase*>> INITIALIZER
%type <std::vector<std::pair<ExpressionBase*, ExpressionBase*>>*> INITIALIZER_LIST INITIALIZERS
%type <ExpressionBase*> EXPRESSION BRACKET_EXPRESSION ATOM
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
%type <std::vector<ExpressionBase*>> DEBUG_ATOM_LIST
%type <PrintNode*> PRINT_SYNTAX DEBUG_SYNTAX
%type <LetNode*> LET_SYNTAX
%type<std::vector<Type*>> TYPE_SYNTAX_LIST
%type <PushNode*> PUSH_SYNTAX
%type <PopNode*> POP_SYNTAX
%type <std::pair<AtomNode*, AstNode*>> CASE_LABEL_STRING CASE_LABEL_NUMBER CASE_LABEL_DEFAULT CASE_LABEL_IDENT CASE_LABEL
%type <std::vector<std::pair<AtomNode*, AstNode*>>> CASE_LABEL_LIST
%type <CaseNode*> CASE_SYNTAX
%type <ForallNode*> FORALL_SYNTAX
%type <std::vector<std::string>> IDENTIFIER_LIST IDENTIFIER_LIST_NO_COMMA
%type <Enum*> ENUM_SYNTAX;
%type <std::vector<std::pair<std::string, std::vector<std::string>>>> DUMPSPEC_LIST
%type <std::pair<std::string, std::vector<std::string>>> DUMPSPEC
%type <DiedieNode*> DIEDIE_SYNTAX


%start SPECIFICATION

%right UMINUS
%right UPLUS
%left XIF

%precedence THEN ELSE

%precedence UPDATE PRINT ASSURE ASSERT DIEDIE NOT

%nonassoc ","
%nonassoc FLOATINGCONST INTEGERCONST STRCONST RATIONALCONST IDENTIFIER
%nonassoc AND OR
%nonassoc "=" "<" ">"  NEQUAL LESSEQ GREATEREQ
%left "-" "+" XOR
%left RATIONAL_DIV "*" "/" "%"

%%

     
SPECIFICATION
: HEADER BODY_ELEMENTS
{
    driver.result = new Ast( @$, $1, $2 );
}
;


HEADER
: CASM IDENTIFIER
{
    $$ = new SpecificationNode( @$, $2 );
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


BODY_ELEMENT: PROVIDER_SYNTAX { $$ = new AstNode(NodeType::PROVIDER); }
           | OPTION_SYNTAX { $$ = new AstNode(NodeType::OPTION); }
           | ENUM_SYNTAX { $$ = new EnumDefNode(@$, $1); }
           | FUNCTION_DEFINITION {
                $$ = new FunctionDefNode(@$, $1);
                if ($1->is_builtin()) {
                    driver.error(@$, "cannot use `"+$1->name+"` as function identifier because it is a builtin name");
                }
                try {
                    driver.add($1);
                } catch (const IdentifierAlreadyUsed& e) {
                    driver.error(@$, e.what());
                    // if another symbol with same name exists we need to delete
                    // the symbol here, because it is not inserted in the symbol table
                    delete $1;
                }
            }
           | DERIVED_SYNTAX {
                $1->binding_offsets = std::move(driver.binding_offsets);
                driver.binding_offsets.clear();
                $$ = new FunctionDefNode(@$, $1);
                try {
                    driver.add($1);
                } catch (const IdentifierAlreadyUsed& e) {
                    driver.error(@$, e.what());
                    // if another symbol with same name exists we need to delete
                    // the symbol here, because it is not inserted in the symbol table
                    delete $1;
                }
            }
           | INIT_SYNTAX { $$ = $1; }
           | RULE_SYNTAX {
                $$ = $1;
                // TODO check, we trust bison to pass only RuleNodes up
                try {
                    driver.add(reinterpret_cast<RuleNode*>($1));
                } catch (const IdentifierAlreadyUsed& e) {
                    driver.error(@$, e.what());
                    // we do not need to delete $1 here, because it's already in
                    // the AST, so it will be deleted later
                }
           }
           ;

INIT_SYNTAX
: INIT IDENTIFIER
{
    $$ = new InitNode( @$, $2 );
}
;


PROVIDER_SYNTAX: PROVIDER IDENTIFIER // TODO: PPA: REMOVE THIS, BECAUSE THIS IS AN OLD SYNTAX ELEMENT!!! 
;


OPTION_SYNTAX: OPTION IDENTIFIER "." IDENTIFIER IDENTIFIER;


ENUM_SYNTAX: ENUM IDENTIFIER "=" "{" IDENTIFIER_LIST "}" {
                $$ = new Enum($2, @$);
                try {
                    driver.function_table.add($$);
                } catch (const SymbolAlreadyExists& e) {
                    driver.error(@$, e.what());
                }
                for (const std::string& name : $5) {
                    if ($$->add_enum_element(name)) {
                        try {
                            driver.function_table.add_enum_element(name, $$);
                        } catch (const SymbolAlreadyExists& e) {
                            driver.error(@$, e.what());
                        }
                    } else {
                        driver.error(@$, "name `"+name+"` already used in enum");
                    }
                }
           }
           ;

DERIVED_SYNTAX: DERIVED IDENTIFIER "(" PARAM_LIST ")" "=" EXPRESSION {
                  // TODO: 2nd argument should be a reference
                  $$ = new Function($2, @$, $4, $7, new Type(TypeType::UNKNOWN));
                }
              | DERIVED IDENTIFIER "=" EXPRESSION {
                  $$ = new Function($2, @$, $4, new Type(TypeType::UNKNOWN));
                }
              | DERIVED IDENTIFIER "(" ")" "=" EXPRESSION {
                  $$ = new Function($2, @$, $6, new Type(TypeType::UNKNOWN));
                }
              /* again with type syntax */
              | DERIVED IDENTIFIER "(" PARAM_LIST ")" ":" TYPE_SYNTAX "=" EXPRESSION {
                  $$ = new Function($2, @$, $4, $9, $7);
                }
              | DERIVED IDENTIFIER ":" TYPE_SYNTAX "=" EXPRESSION {
                  $$ = new Function($2, @$, $6, $4);
                }
              | DERIVED IDENTIFIER "(" ")" ":" TYPE_SYNTAX "=" EXPRESSION {
                  $$ = new Function($2, @$, $8, $6);
                }
              ;

FUNCTION_DEFINITION: FUNCTION "(" IDENTIFIER_LIST ")" IDENTIFIER FUNCTION_SIGNATURE INITIALIZERS {
                      auto attrs = parse_function_attributes(driver, @$, $3);
                      $$ = new Function(attrs.first, attrs.second, $5, @$, $6.first, $6.second, $7);
                   }
                   | FUNCTION "(" IDENTIFIER_LIST ")" IDENTIFIER FUNCTION_SIGNATURE {
                      auto attrs = parse_function_attributes(driver, @$, $3);
                      $$ = new Function(attrs.first, attrs.second, $5, @$, $6.first, $6.second, nullptr);
                   }
                   | FUNCTION IDENTIFIER FUNCTION_SIGNATURE INITIALIZERS {
                      $$ = new Function($2, @$, $3.first, $3.second, $4);
                   }
                   | FUNCTION IDENTIFIER FUNCTION_SIGNATURE
                   { $$ = new Function($2, @$, $3.first, $3.second, nullptr); }
                   ;

IDENTIFIER_LIST: IDENTIFIER_LIST_NO_COMMA "," { $$ = std::move($1); }
               | IDENTIFIER_LIST_NO_COMMA { $$ = std::move($1); }
               ;

IDENTIFIER_LIST_NO_COMMA: IDENTIFIER_LIST_NO_COMMA "," IDENTIFIER {
                            $$ = std::move($1);
                            $$.push_back($3);
                        }
                        | IDENTIFIER {
                            $$ = std::vector<std::string>();
                            $$.push_back($1);
                        }
                        ;

FUNCTION_SIGNATURE: ":" ARROW TYPE_SYNTAX {
                    /* this constructor is implementation dependant! */
                    std::vector<Type*> foo;
                    $$ = std::pair<std::vector<Type*>, Type*>(foo, $3);
                  }
                  | ":" TYPE_IDENTIFIER_STARLIST ARROW TYPE_SYNTAX
                  { $$ = std::pair<std::vector<Type*>, Type*>($2, $4); }
                  ;

PARAM: IDENTIFIER ":" TYPE_SYNTAX {
        size_t size = driver.binding_offsets.size();
        driver.binding_offsets[$1] = size;
        $$ = $3;
     }
     | IDENTIFIER {
        size_t size = driver.binding_offsets.size();
        driver.binding_offsets[$1] = size;
        // TODO: fail for rules without types and print warnings
        $$ = new Type(TypeType::INTEGER);
     }
     ;


PARAM_LIST: PARAM_LIST_NO_COMMA { $$ = std::move($1); }
          | PARAM_LIST_NO_COMMA "," { $$ = std::move($1); }

PARAM_LIST_NO_COMMA: PARAM_LIST_NO_COMMA "," PARAM {
                        $$ = std::move($1);
                        $$.push_back($3);
                   }
                   | PARAM { $$.push_back($1); }
                   ;


TYPE_IDENTIFIER_STARLIST: TYPE_SYNTAX "*" TYPE_IDENTIFIER_STARLIST {
                            $3.insert($3.begin(), $1);
                            $$ = std::move($3);
                        }
                        | TYPE_SYNTAX "*" {
                          // TODO: limit memory size
                            $$.push_back($1);
                        }
                        | TYPE_SYNTAX {
                            $$.push_back($1);
                        }
                        ;

TYPE_SYNTAX
: IDENTIFIER
  {
	  $$ = new Type($1);
	  
	  // TODO: FUTURE: integrate the IR-based type-list here to perform checks!,
	  //               or maybe we should check everything in the typecheckpass?
	  if( $1.compare( "Bit" ) == 0 )
	  {
		  driver.error( @$, "missing bit-size for Bit type", libcasm_fe::Codes::BitTypeSyntaxError );
	  }
  }
| IDENTIFIER "(" INTEGER_NUMBER ")"
  {
	  $$ = new Type( $1 );
	  $$->bitsize = $3->val_;
	  if( $$->bitsize <= 0 || $$->bitsize > 256 )
	  {
		  driver.error(@$, "invalid bit-size for Bit type, must between 1 <= x <= 256", libcasm_fe::Codes::BitTypeSizeIsInvalid );
	  }
  }
| IDENTIFIER "(" TYPE_SYNTAX_LIST ")"
  {
	  $$ = new Type($1, $3);
  }
| IDENTIFIER "(" INTEGER_NUMBER DOTDOT INTEGER_NUMBER ")"
  {
	  $$ = new Type($1);
	  $$->subrange_start = $3->val_;
	  $$->subrange_end = $5->val_;
	  if ($$->subrange_start >= $$->subrange_end)
	  {
		  driver.error(@$, "start of subrange must be smaller than the end");
	  }
  }
;


TYPE_SYNTAX_LIST: TYPE_SYNTAX "," TYPE_SYNTAX_LIST {
                      $3.push_back($1);
                      $$ = std::move($3);
                    }
                    | TYPE_SYNTAX "," { $$.push_back($1); }
                    | TYPE_SYNTAX { $$.push_back($1); }
                    ;

INITIALIZERS: INITIALLY "{" INITIALIZER_LIST "}" { $$ = $3; }
            | INITIALLY "{" "}" { $$ = nullptr; }
            ;

INITIALIZER_LIST: INITIALIZER_LIST "," INITIALIZER { $$ = $1; $1->push_back($3); }
                | INITIALIZER_LIST "," { $$ = $1; }
                | INITIALIZER {
                    $$ = new std::vector<std::pair<ExpressionBase*, ExpressionBase*>>();
                    $$->push_back($1);
                }
                ;


INITIALIZER: ATOM { $$ = std::pair<ExpressionBase*, ExpressionBase*>(nullptr, $1); }
           | ATOM ARROW ATOM { $$ = std::pair<ExpressionBase*, ExpressionBase*>($1, $3); }
           ;

ATOM: FUNCTION_SYNTAX { $$ = $1; }
    | VALUE { $$ = $1; }
    | BRACKET_EXPRESSION { $$ = $1; }
    ;

VALUE: RULEREF { $$ = new RuleAtom(@$, std::move($1)); }
     | NUMBER { $$ = $1; }
     | STRCONST { $$ = new StringAtom(@$, std::move($1)); }
     | LISTCONST { $$ = new ListAtom(@$, $1); }
     | NUMBER_RANGE { $$ = $1; }
     | SYMBOL { $$ = new IntegerAtom(@$, 0); }
     | SELF { $$ = new SelfAtom(@$); }
     | UNDEF { $$ = new UndefAtom(@$); }
     | TRUE { $$ = new BooleanAtom(@$, true); }
     | FALSE { $$ = new BooleanAtom(@$, false); }
     ;

INTEGER_NUMBER: "+" INTEGERCONST %prec UPLUS { $$ = new IntegerAtom(@$, $2); }
          | "-" INTEGERCONST %prec UMINUS { $$ = new IntegerAtom(@$, (-1) * $2); }
          | INTEGERCONST { $$ = new IntegerAtom(@$, $1); }
NUMBER: INTEGER_NUMBER { $$ = $1; }
      | "+" FLOATINGCONST %prec UPLUS { $$ = new FloatingAtom(@$, $2); }
      | "-" FLOATINGCONST %prec UMINUS { $$ = new FloatingAtom(@$, (-1) * $2); }
      | FLOATINGCONST { $$ = new FloatingAtom(@$, $1); }
      | "+" RATIONALCONST %prec UPLUS { $$ = new RationalAtom(@$, $2); }
      | "-" RATIONALCONST %prec UMINUS {
          $2.numerator *= -1;
          $$ = new RationalAtom(@$, $2);
        }
      | RATIONALCONST { $$ = new RationalAtom(@$, $1); }
      ;

RULEREF: "@" IDENTIFIER { $$ = $2; }
       ;

NUMBER_RANGE: "[" NUMBER DOTDOT NUMBER "]" {
              if ($2->node_type_ == NodeType::INTEGER_ATOM && $4->node_type_ == NodeType::INTEGER_ATOM) {
                $$ = new NumberRangeAtom(@$, reinterpret_cast<IntegerAtom*>($2), reinterpret_cast<IntegerAtom*>($4));
              } else {
                driver.error(@$, "numbers in range expression must be Integer");
                $$ = nullptr;
              }
            }
            /*| "[" IDENTIFIER DOTDOT IDENTIFIER "]" */
            ;

LISTCONST: "[" EXPRESSION_LIST "]" { $$ = $2; }
         | "[" "]" { $$ = new std::vector<ExpressionBase*>(); }
         ;


EXPRESSION_LIST: EXPRESSION_LIST_NO_COMMA { $$ = $1; }
               | EXPRESSION_LIST_NO_COMMA "," { $$ = $1; }

EXPRESSION_LIST_NO_COMMA: EXPRESSION_LIST_NO_COMMA"," EXPRESSION {
                          $$ = $1;
                          $$->push_back($3);
                        }
                        | EXPRESSION {
                          $$ = new std::vector<ExpressionBase*>;
                          $$->push_back($1);
                        }
                        ;


EXPRESSION: EXPRESSION "+" EXPRESSION
            { $$ = new Expression(@$, $1, $3, ExpressionOperation::ADD); }
          | EXPRESSION "-" EXPRESSION
            { $$ = new Expression(@$, $1, $3, ExpressionOperation::SUB); }
          | EXPRESSION "*" EXPRESSION
            { $$ = new Expression(@$, $1, $3, ExpressionOperation::MUL); }
          | EXPRESSION "/" EXPRESSION
            { $$ = new Expression(@$, $1, $3, ExpressionOperation::DIV); }
          | EXPRESSION "%" EXPRESSION
            { $$ = new Expression(@$, $1, $3, ExpressionOperation::MOD); }
          | EXPRESSION RATIONAL_DIV EXPRESSION
            { $$ = new Expression(@$, $1, $3, ExpressionOperation::RAT_DIV); }
          | EXPRESSION NEQUAL EXPRESSION
            { $$ = new Expression(@$, $1, $3, ExpressionOperation::NEQ); }
          | EXPRESSION "=" EXPRESSION
            { $$ = new Expression(@$, $1, $3, ExpressionOperation::EQ); }
          | EXPRESSION "<" EXPRESSION
            { $$ = new Expression(@$, $1, $3, ExpressionOperation::LESSER); }
          | EXPRESSION ">" EXPRESSION
            { $$ = new Expression(@$, $1, $3, ExpressionOperation::GREATER); }
          | EXPRESSION LESSEQ EXPRESSION
            { $$ = new Expression(@$, $1, $3, ExpressionOperation::LESSEREQ); }
          | EXPRESSION GREATEREQ EXPRESSION
            { $$ = new Expression(@$, $1, $3, ExpressionOperation::GREATEREQ); }
          | EXPRESSION OR EXPRESSION
            { $$ = new Expression(@$, $1, $3, ExpressionOperation::OR); }
          | EXPRESSION XOR EXPRESSION
            { $$ = new Expression(@$, $1, $3, ExpressionOperation::XOR); }
          | EXPRESSION AND EXPRESSION
            { $$ = new Expression(@$, $1, $3, ExpressionOperation::AND); }
          | NOT EXPRESSION
            { $$ = new Expression(@$, $2, nullptr, ExpressionOperation::NOT);}
          | ATOM  { $$ = $1; }
          ;

BRACKET_EXPRESSION: "(" EXPRESSION ")"  { $$ = $2; }
                  ;

FUNCTION_SYNTAX: IDENTIFIER { $$ = new FunctionAtom(@$, $1); }
               | IDENTIFIER "(" ")" { $$ = new FunctionAtom(@$, $1); }
               | IDENTIFIER "(" EXPRESSION_LIST ")"
               {
                   if( Builtin::isBuiltin( $1 ) )
                   {
                       $$ = new BuiltinAtom(@$, $1, $3);
                   }
                   else
                   {
                       $$ = new FunctionAtom(@$, $1, $3);
                   }
               }
               ;

RULE_STMT: SEQ_SYNTAX { $$ = $1; }
         | PAR_SYNTAX { $$ = $1; }
         | SIMPLE_STMT {
              auto stmts = new AstListNode(@$, NodeType::STATEMENTS);
              stmts->add($1);
              $$ = new UnaryNode(@$, NodeType::PARBLOCK, stmts);
          }
         ;

RULE_SYNTAX: RULE IDENTIFIER "=" RULE_STMT { $$ = new RuleNode(@$, $4, $2); }
           | RULE IDENTIFIER "(" ")" "=" RULE_STMT {
                $$ = new RuleNode(@$, $6, $2);
           }
           | RULE IDENTIFIER "(" PARAM_LIST ")" "=" RULE_STMT {
                $$ = new RuleNode(@$, $7, $2, $4);
           }
/* again, with dump specification */
           | RULE IDENTIFIER DUMPS DUMPSPEC_LIST "=" RULE_STMT {
                std::vector<Type*> tmp;
                $$ = new RuleNode(@$, $6, $2, tmp, $4);
           }
           | RULE IDENTIFIER "(" ")" DUMPS DUMPSPEC_LIST "=" RULE_STMT {
                std::vector<Type*> tmp;
                $$ = new RuleNode(@$, $8, $2, tmp, $6);
           }
           | RULE IDENTIFIER "(" PARAM_LIST ")" DUMPS DUMPSPEC_LIST "=" RULE_STMT {
                std::vector<Type*> tmp;
                $$ = new RuleNode(@$, $9, $2, tmp, $7);
           }
           ;

DUMPSPEC_LIST: DUMPSPEC_LIST "," DUMPSPEC { $$ = std::move($1); $$.push_back($3); }
             | DUMPSPEC {
                $$ = std::vector<std::pair<std::string,std::vector<std::string>>>();
                $$.push_back(std::move($1));
             }
             ;

DUMPSPEC: "(" IDENTIFIER_LIST ")" ARROW IDENTIFIER {
            $$ = std::pair<std::string, std::vector<std::string>>($5, $2);
        }
        ;

SIMPLE_STMT: ASSERT_SYNTAX { $$ = $1; }
           | ASSURE_SYNTAX { $$ = $1; }
           | DIEDIE_SYNTAX { $$ = $1; }
           | IMPOSSIBLE_SYNTAX { $$ = $1; }
           | DEBUG_SYNTAX { $$ = $1; }
           | PRINT_SYNTAX { $$ = $1; }
           | UPDATE_SYNTAX { $$ = $1; }
           | CASE_SYNTAX { $$ = $1; }
           | CALL_SYNTAX { $$ = $1; }
           | IFTHENELSE { $$ = $1; }
           | LET_SYNTAX { $$ = $1; }
           | PUSH_SYNTAX { $$ = $1; }
           | POP_SYNTAX { $$ = $1; }
           | FORALL_SYNTAX { $$ = $1; }
           | ITERATE_SYNTAX { $$ = $1; }
           | SKIP  { $$ = new AstNode(NodeType::SKIP); }
           | IDENTIFIER  { driver.error(@$, "this call syntax is obsolete, use `call "+$1+"`"); }
           | INTERN EXPRESSION_LIST  { $$ = new AstNode(NodeType::STATEMENT); }
           | OBJDUMP "(" IDENTIFIER ")"   { $$ = new AstNode(NodeType::STATEMENT);}
           ;

STATEMENT: SIMPLE_STMT { $$ = $1; }
         | SEQ_SYNTAX { $$ = $1; }
         | PAR_SYNTAX { $$ = $1; }
         ;

ASSERT_SYNTAX: ASSERT EXPRESSION { $$ = new UnaryNode(@$, NodeType::ASSERT, $2); }
             ;
ASSURE_SYNTAX: ASSURE EXPRESSION { $$ = new UnaryNode(@$, NodeType::ASSURE, $2); }
             ;

DIEDIE_SYNTAX: DIEDIE EXPRESSION { $$ = new DiedieNode(@$, $2); }
             | DIEDIE { $$ = new DiedieNode(@$, nullptr); }
             ;

/* when symbolic execution:
    * abort trace
    * do not write it
    * no error
  in concrete mode:
    * an error like diedie
*/
IMPOSSIBLE_SYNTAX: IMPOSSIBLE { $$ = new AstNode(@$, NodeType::IMPOSSIBLE); }
         ;

DEBUG_SYNTAX: DEBUG IDENTIFIER DEBUG_ATOM_LIST { $$ = new PrintNode(@$, $2, $3); }
                ;

DEBUG_ATOM_LIST: DEBUG_ATOM_LIST "+" ATOM { $$ = std::move($1); $$.push_back($3); }
               | ATOM { $$.push_back($1); }

PRINT_SYNTAX: PRINT DEBUG_ATOM_LIST { $$ = new PrintNode(@$, $2); }
            ;

UPDATE_SYNTAX: FUNCTION_SYNTAX UPDATE EXPRESSION {
                  if ($1->node_type_ == NodeType::FUNCTION_ATOM) {
                    $$ = new UpdateNode(@$, reinterpret_cast<FunctionAtom*>($1), $3);
                  } else {
                    driver.error(@$, "can only use functions for updates but `"+
                                     $1->to_str()+"` is a `"+type_to_str($1->node_type_));
                  }
                }
             ;

CASE_SYNTAX: CASE EXPRESSION OF CASE_LABEL_LIST ENDCASE {
                $$ = new CaseNode(@$, $2, $4);
           }
           ;

CASE_LABEL_LIST: CASE_LABEL_LIST CASE_LABEL {
                    $$ = std::move($1);
                    $$.push_back($2);
               }
               | CASE_LABEL {
                    $$ = std::move(std::vector<std::pair<AtomNode*, AstNode*>>());
                    $$.push_back($1);
               }
               ;

CASE_LABEL: CASE_LABEL_DEFAULT { $$ =$1; }
          | CASE_LABEL_NUMBER { $$ = $1; }
          | CASE_LABEL_IDENT  { $$ = $1; }
          | CASE_LABEL_STRING { $$ = $1; }
          ;

CASE_LABEL_DEFAULT: DEFAULT ":" STATEMENT {
                    $$ = std::pair<AtomNode*, AstNode*>(nullptr, $3);
                  }
                  ;

CASE_LABEL_NUMBER: NUMBER ":" STATEMENT {
                    $$ = std::pair<AtomNode*, AstNode*>($1, $3);
                 }
                 ;

CASE_LABEL_IDENT: FUNCTION_SYNTAX ":" STATEMENT {
                    $$ = std::pair<AtomNode*, AstNode*>($1, $3);
                }
                ;

CASE_LABEL_STRING: STRCONST ":" STATEMENT {
                    $$ = std::pair<AtomNode*, AstNode*>(new StringAtom(@$, std::move($1)), $3);
                 }
                 ;

CALL_SYNTAX: CALL "(" EXPRESSION ")" "(" EXPRESSION_LIST ")" { $$ = new CallNode(@$, "", $3, $6); }
           | CALL "(" EXPRESSION ")" { $$ = new CallNode(@$, "", $3); }
           | CALL IDENTIFIER "(" EXPRESSION_LIST ")" { $$ = new CallNode(@$, $2, nullptr, $4); }
           | CALL IDENTIFIER { $$ = new CallNode(@$, $2, nullptr); }
           ;

SEQ_SYNTAX: SEQ_BRACKET STATEMENTS ENDSEQ_BRACKET {
                $$ = new UnaryNode(@$, NodeType::SEQBLOCK, $2);
          }
          | SEQ STATEMENTS ENDSEQ {
                $$ = new UnaryNode(@$, NodeType::SEQBLOCK, $2);
          }
          ;

PAR_SYNTAX: "{" STATEMENTS "}" {
                $$ = new UnaryNode(@$, NodeType::PARBLOCK, $2);
          }
          | PAR STATEMENTS ENDPAR {
                $$ = new UnaryNode(@$, NodeType::PARBLOCK, $2);
          }
          ;

STATEMENTS: STATEMENTS STATEMENT { $1->add($2); $$ = $1; }
          | STATEMENT { $$ = new AstListNode(@$, NodeType::STATEMENTS); $$->add($1); }
          ;

IFTHENELSE: IF EXPRESSION THEN STATEMENT %prec XIF {
                $$ = new IfThenElseNode(@$, $2, $4, nullptr);
          }
          | IF EXPRESSION THEN STATEMENT ELSE STATEMENT {
                $$ = new IfThenElseNode(@$, $2, $4, $6);
          }
          ;

LET_SYNTAX: LET IDENTIFIER "=" 
            {
                auto var = Symbol($2, @$, Symbol::SymbolType::LET);
                try {
                    driver.function_table.add(&var);
                } catch (const SymbolAlreadyExists& e) {
                    driver.error(@$, e.what());
                }
            }
            EXPRESSION IN STATEMENT {
              driver.function_table.remove($2);
              $$ = new LetNode(@$, Type(TypeType::UNKNOWN), $2, $5, $7);
          }
          | LET IDENTIFIER ":" TYPE_SYNTAX "="
            {
                auto var = Symbol($2, @$, Symbol::SymbolType::LET);
                try {
                    driver.function_table.add(&var);
                } catch (const SymbolAlreadyExists& e) {
                    driver.error(@$, e.what());
                }
            }
          EXPRESSION IN STATEMENT {
              driver.function_table.remove($2);
              $$ = new LetNode(@$, $4, $2, $7, $9);
          }
          ;

PUSH_SYNTAX: PUSH EXPRESSION INTO FUNCTION_SYNTAX {
                if ($4->node_type_ == NodeType::BUILTIN_ATOM) {
                  driver.error(@$, "cannot push to builtin `"+$4->to_str()+"`");
                } else {
                    $$ = new PushNode(@$, $2, reinterpret_cast<FunctionAtom*>($4));
                }
          }

           ;

POP_SYNTAX: POP FUNCTION_SYNTAX FROM FUNCTION_SYNTAX {
                if ($2->node_type_ == NodeType::BUILTIN_ATOM) {
                  driver.error(@$, "cannot pop to builtin `"+$2->to_str()+"`");
                } else if ($4->node_type_ == NodeType::BUILTIN_ATOM) {
                  driver.error(@$, "cannot pop from builtin `"+$4->to_str()+"`");
                } else {
                    $$ = new PopNode(@$, reinterpret_cast<FunctionAtom*>($2), reinterpret_cast<FunctionAtom*>($4));
                }
          }
          ;

FORALL_SYNTAX: FORALL IDENTIFIER IN EXPRESSION DO STATEMENT {
                $$ = new ForallNode(@$, $2, $4, $6);
             }
             ;

ITERATE_SYNTAX: ITERATE STATEMENT { $$ = new UnaryNode(@$, NodeType::ITERATE, $2); }
              ;


%%

void yy::casmi_parser::error
( const location_type& l
, const std::string& m
)
{
    driver.error (l, m, libcasm_fe::Codes::SyntaxError );
}


//  
//  Local variables:
//  mode: c++
//  indent-tabs-mode: t
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//  
