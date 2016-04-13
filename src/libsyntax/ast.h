//  
//  Copyright (c) 2014-2016, Florian Hahn, Philipp Paulweber
//  All rights reserved.
//  
//  Developed by: Florian Hahn
//                Philipp Paulweber
//                https://github.com/ppaulweber/libcasm-fe
//  
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//  
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//  
//  You should have received a copy of the GNU General Public License
//  along with this program. If not, see <http://www.gnu.org/licenses/>.
//  

#ifndef CASMI_AST_H
#define CASMI_AST_H

#include <string>
#include <vector>
#include <unordered_map>

#include "macros.h"

#include "libsyntax/types.h"
#include "libsyntax/symbols.h"
#include "libsyntax/value.h"
#include "libsyntax/location.hh" // reuse bison's location class

class value_t;

enum NodeType {
  ASSERT,
  UNDEF_ATOM,
  INTEGER_ATOM,
  FLOAT_ATOM,
  RATIONAL_ATOM,
  SELF_ATOM,
  STRING_ATOM,
  RULE_ATOM,
  DUMMY_ATOM,
  BOOLEAN_ATOM,
  INIT,
  IFTHENELSE,
  BODY_ELEMENTS,
  PROVIDER,
  OPTION,
  ENUM,
  FUNCTION,
  DERIVED,
  RULE,
  SPECIFICATION,
  EXPRESSION,
  UPDATE,
  UPDATE_SUBRANGE,
  UPDATE_DUMPS,
  STATEMENT,
  STATEMENTS,
  SKIP,
  PARBLOCK,
  SEQBLOCK,
  FUNCTION_ATOM,
  FUNCTION_ATOM_SUBRANGE,
  CALL,
  PRINT,
  LET,
  LIST_ATOM,
  BUILTIN_ATOM,
  NUMBER_RANGE_ATOM,
  POP,
  PUSH,
  CASE,
  FORALL,
  ITERATE,
  DIEDIE,
  IMPOSSIBLE,
  ASSURE,
};

const std::string& type_to_str(NodeType t);

class AstVisitor;

// Forward declarations for libsyntax/symbols.h
class Function;
class Enum;
class Binding;

class List;
class TempList;
class BottomList;

// Forward delclarations for this file
class Expression;
class ExpressionBase;
class AtomNode;

class AstNode {
    public:
        yy::location location;
        NodeType node_type_;

        Type type_;

        AstNode(NodeType node_type);
        AstNode(yy::location& loc, NodeType node_type);
        AstNode(yy::location& loc, NodeType node_type, Type type);
        virtual ~AstNode();
        virtual std::string to_str();
        virtual bool equals(AstNode *other);
        std::string location_str() const;
};

class AstListNode: public AstNode {
    public:
        std::vector<AstNode*> nodes;

        AstListNode(yy::location& loc, NodeType node_type);
        virtual ~AstListNode();
        void add(AstNode* n);
        virtual bool equals(AstNode *other);
};


class UnaryNode: public AstNode {
  public:
    AstNode *child_;

    UnaryNode(yy::location& loc, NodeType node_type, AstNode *child);
    virtual ~UnaryNode();
    virtual bool equals(AstNode *other);
};


class RuleNode: public UnaryNode {
  public:
    const std::string name;
    std::vector<Type*> arguments;
    std::map<std::string, size_t> binding_offsets;
    std::vector< const char* > parameter;
    
    const std::vector<std::pair<std::string, std::vector<std::string>>> dump_list;

    RuleNode(yy::location& loc, AstNode *child, const std::string &name);
    RuleNode(yy::location& loc, AstNode *child, const std::string &name,
        std::vector<Type*>& args);
    RuleNode(yy::location& loc, AstNode *child, const std::string &name,
        std::vector<Type*>& args,
        const std::vector<std::pair<std::string, std::vector<std::string>>>& dump_list);

};


class FunctionDefNode: public AstNode {
  public:
    Function *sym;
    FunctionDefNode(yy::location& loc, Function *sym);
    ~FunctionDefNode();
};

class EnumDefNode: public AstNode {
  public:
    Enum *enum_;
    EnumDefNode(yy::location& loc, Enum *enum_);
    ~EnumDefNode();
};

class IfThenElseNode : public AstNode {
  public:
    ExpressionBase *condition_;
    AstNode *then_; // should always be a statement
    AstNode *else_; // should always be a statement

    IfThenElseNode(yy::location& loc, ExpressionBase *condition, AstNode *then,
                   AstNode *els);
};

class ExpressionBase : public AstNode {
  public:
    ExpressionBase(yy::location& loc, NodeType node_type, Type type) : AstNode(loc, node_type, type) {}

};

class AtomNode: public ExpressionBase {
  public:
    AtomNode(yy::location& loc, NodeType node_type, Type type) : ExpressionBase(loc, node_type, type) {}
};

class IntegerAtom : public AtomNode {
  public:
    INTEGER_T val_;

    IntegerAtom(yy::location& loc, INTEGER_T val);
    virtual ~IntegerAtom();
    bool equals(AstNode *other);
};

class FloatAtom : public AtomNode {
  public:
    FLOAT_T val_;

    FloatAtom(yy::location& loc, FLOAT_T val);
    virtual ~FloatAtom();
    bool equals(AstNode *other);
};

class RationalAtom : public AtomNode {
  public:
    const rational_t val_;

    RationalAtom(yy::location& loc, const rational_t& rat);
};


class UndefAtom : public AtomNode {
  public:
    UndefAtom(yy::location& loc);
    bool equals(AstNode *other);
};


class SelfAtom : public AtomNode {
  public:
    SelfAtom(yy::location& loc);
    bool equals(AstNode *other);
};


class BooleanAtom : public AtomNode {
  public:
    bool value;
    BooleanAtom(yy::location& loc, bool value);
    bool equals(AstNode *other);
};


class BaseFunctionAtom: public AtomNode {
  public:
    const std::string name;
    std::vector<ExpressionBase*> *arguments;

    BaseFunctionAtom(yy::location& loc, NodeType t, const std::string name,
                 std::vector<ExpressionBase*> *args);
    
    
};

class FunctionAtom : public BaseFunctionAtom {
  public:
    enum class SymbolType {
      FUNCTION,
      DERIVED,
      PARAMETER,
      UNSET,
      PUSH_POP,
      ENUM,
    };

    SymbolType symbol_type;
    bool initialized;

    union {
      Function *symbol;
      size_t offset;
      Enum *enum_;
    };

    FunctionAtom(yy::location& loc, const std::string name);
    FunctionAtom(yy::location& loc, const std::string name,
                 std::vector<ExpressionBase*> *args);
 
    virtual ~FunctionAtom();
    bool equals(AstNode *other);
};

class BuiltinAtom: public BaseFunctionAtom {
  public:
    Builtin::Id id;
    
    std::vector<Type*> types;
    Type* return_type;

    BuiltinAtom(yy::location& loc, const std::string name,
                 std::vector<ExpressionBase*> *args);
 
    virtual ~BuiltinAtom();
    bool equals(AstNode *other);
    std::string to_string();
};



class RuleAtom : public AtomNode {
  public:
    RuleNode *rule;
    const std::string name;

    RuleAtom(yy::location& loc, const std::string&& name);
 
    virtual ~RuleAtom();
    bool equals(AstNode *other);
};


class StringAtom : public AtomNode {
  public:
    std::string string;

    StringAtom(yy::location& loc, std::string&& name);
 
    virtual ~StringAtom();
    bool equals(AstNode *other);
};

class ListAtom : public AtomNode {
  public:
    std::vector<ExpressionBase*>* expr_list;

    ListAtom(yy::location& loc, std::vector<ExpressionBase*> *exprs);
};

class NumberRangeAtom : public AtomNode {
  public:
    BottomList *list;

    NumberRangeAtom(yy::location& loc, IntegerAtom *start, IntegerAtom *end);
};

enum class ExpressionOperation {
  ADD = 0,
  SUB,
  MUL,
  DIV,
  MOD,
  RAT_DIV,
  EQ,
  NEQ,
  LESSER,
  GREATER,
  LESSEREQ,
  GREATEREQ,
  OR,
  XOR,
  AND,
  NOT
};

class Expression : public ExpressionBase {
  public:

    ExpressionBase *left_;
    ExpressionBase *right_;

    ExpressionOperation op;

    Expression(yy::location& loc, ExpressionBase *left, ExpressionBase *right, ExpressionOperation op);
    virtual ~Expression();
    virtual bool equals(AstNode *other);
};

std::string operator_to_str(const ExpressionOperation op);

class UpdateNode: public AstNode {
  public:
    FunctionAtom *func;
    ExpressionBase *expr_;

    UpdateNode(yy::location& loc, FunctionAtom *func, ExpressionBase *expr);
    virtual ~UpdateNode();
    virtual bool equals(AstNode *other);
};

class PushNode: public AstNode {
  public:
    ExpressionBase *expr;
    FunctionAtom *to;

    PushNode(yy::location& loc, ExpressionBase *expr, FunctionAtom *to);
    virtual ~PushNode();
    virtual bool equals(AstNode *other);
};

class PopNode: public AstNode {
  public:
    FunctionAtom *to;
    FunctionAtom *from;

    Type from_type;

    PopNode(yy::location& loc, FunctionAtom *to, FunctionAtom *from);
    virtual ~PopNode();
    virtual bool equals(AstNode *other);
};

class ForallNode: public AstNode {
  public:
    const std::string identifier;
    ExpressionBase *in_expr;
    AstNode *statement;

    ForallNode(yy::location& loc, const std::string& ident, ExpressionBase *expr, AstNode *stmt);
    virtual ~ForallNode();
};


class CaseNode: public AstNode {
  public:
    ExpressionBase *expr;

    std::vector<std::pair<AtomNode*, AstNode*>> case_list;
    //std::unordered_map<value_t, AstNode*> label_map;

    bool map_fixed;

    CaseNode(yy::location& loc, ExpressionBase *expr,
             std::vector<std::pair<AtomNode*, AstNode*>>& case_list);
    virtual ~CaseNode();
    virtual bool equals(AstNode *other);
};


class CallNode: public AstNode {
  public:
    const std::string rule_name;
    RuleNode *rule;
    std::vector<ExpressionBase*> *arguments;
    ExpressionBase *ruleref;
    
    CallNode(yy::location& loc, const std::string& rule_name, ExpressionBase *ruleref);
    CallNode(yy::location& loc, const std::string& rule_name, ExpressionBase *ruleref,
             std::vector<ExpressionBase*> *args);
};

class PrintNode: public AstNode {
  public:
    std::vector<ExpressionBase*> atoms;
    std::string filter;

    PrintNode(yy::location& loc, const std::vector<ExpressionBase*> &atoms);
    PrintNode(yy::location& loc, const std::string& filter, const std::vector<ExpressionBase*> &atoms);
};

class LetNode: public AstNode {
  public:
    const std::string identifier;
    ExpressionBase *expr;
    AstNode *stmt;

    LetNode(yy::location& loc, Type type, const std::string& identifier,
            ExpressionBase *expr, AstNode *stmt);
};

class DiedieNode : public AstNode {
  public:
    ExpressionBase *msg;

    DiedieNode(yy::location& loc, ExpressionBase *msg);
};


#endif
