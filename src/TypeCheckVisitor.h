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
//  along with libcasm-fe. If not, see <http://www.gnu.org/licenses/>.
//  

#ifndef CASMI_LIBPARSE_TYPECHECK_VISITOR
#define CASMI_LIBPARSE_TYPECHECK_VISITOR

#include <utility>

#include "Ast.h"
#include "Visitor.h"
#include "Types.h"
#include "Driver.h"

class TypecheckVisitor : public BaseVisitor<Type*> {
  private:
    void check_type_valid(const yy::location& location, const Type& type);

  public:
    Driver& driver_;
    void check_numeric_operator(const yy::location& loc,  Type *type,
                                const ExpressionOperation op);

    std::vector<std::vector<Type*> *> rule_binding_types;
    std::vector<std::map<std::string, size_t> *> rule_binding_offsets;

    bool forall_head;

    Type *arguments[10];
    uint32_t num_arguments;

    TypecheckVisitor(Driver& driver);

    void visit_init(AstNode *init) { UNUSED(init); }
    void visit_function_def(FunctionDefNode *def,
                            const std::vector<std::pair<Type*, Type*>>& initializers);
    void visit_derived_def_pre(FunctionDefNode *def);
    void visit_derived_def(FunctionDefNode *def, Type* expr);

    void visit_rule(RuleNode *rule);
    void visit_ifthenelse(IfThenElseNode *node, Type* cond);
    void visit_assert(UnaryNode *assert, Type* t);
    void visit_update(UpdateNode *update, Type* func, Type* expr);
    void visit_call_pre(CallNode *call);
    void visit_call_pre(CallNode *call, Type* expr);
    void visit_call(CallNode *call, std::vector<Type*>& argument_results);
    void visit_call_post(CallNode *call);
    void visit_print( PrintNode* node, Type* type );
    void visit_diedie(DiedieNode *node, Type* msg);

    void visit_let(LetNode *node, Type* v);
    void visit_let_post(LetNode *node);
    void visit_push(PushNode *node, Type *expr, Type *atom);
    void visit_pop(PopNode *node);
    void visit_case(CaseNode *node, Type *val, const std::vector<Type*>& case_labels);

    Type* visit_expression(Expression *expr, Type* left_val, Type* right_val);
    Type* visit_expression_single(Expression *expr, Type* val);
    Type* visit_zero_atom(ZeroAtom *atom)   { return &atom->type_; }
    Type* visit_int_atom(IntegerAtom *atom) { return &atom->type_; }
    Type* visit_floating_atom(FloatingAtom *atom) {  return &atom->type_; }
    Type* visit_rational_atom(RationalAtom *atom) { return &atom->type_; }
    Type* visit_undef_atom(UndefAtom *atom) { return &atom->type_; }
    Type* visit_function_atom(FunctionAtom *atom, Type* arguments[], uint16_t num_arguments);
    Type* visit_builtin_atom(BuiltinAtom *atom, Type *arguments[], uint16_t num_arguments);

    void visit_derived_function_atom_pre(FunctionAtom *atom, Type* arguments[], uint16_t num_arguments);
    Type* visit_derived_function_atom(FunctionAtom *atom, Type *expr);
    Type* visit_self_atom(SelfAtom *atom) { return &atom->type_;  }
    Type* visit_rule_atom(RuleAtom *atom);
    Type* visit_boolean_atom(BooleanAtom *atom) { return &atom->type_; }
    Type* visit_string_atom(StringAtom *atom) { return &atom->type_; }
    Type* visit_list_atom(ListAtom *atom, std::vector<Type*> &vals);
    Type* visit_number_range_atom(NumberRangeAtom *atom) { return &atom->type_; }
};

template <>
void AstWalker<TypecheckVisitor, Type*>::walk_forall(ForallNode *node);

template <>
void AstWalker<TypecheckVisitor, Type*>::walk_call(CallNode *call);


#endif //CASMI_LIBINTERPRETER_EXEC_VISITOR
