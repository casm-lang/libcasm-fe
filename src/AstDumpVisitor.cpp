//  
//  Copyright (c) 2014-2016 CASM Organization
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
//  along with libcasm-fe. If not, see <http://www.gnu.org/licenses/>.
//  

#include "AstDumpVisitor.h"

AstDumpVisitor::AstDumpVisitor() { }

std::string AstDumpVisitor::get_dump() {
  return std::string("digraph \"main\" {\n") + dump_stream_.str() + std::string("}");
}

void AstDumpVisitor::dump_node(uint64_t key, const std::string& name) {
  dump_stream_ << "    " << key << " [label=\"" << name << "\"];" << std::endl;
}

void AstDumpVisitor::dump_node(AstNode *n, const std::string& name) {
  dump_node((uint64_t) n, name);
}


void AstDumpVisitor::dump_link(uint64_t from, uint64_t to) {
  dump_stream_ << "    " << from << " -> " << to << ";" << std::endl;
}

void AstDumpVisitor::dump_link(AstNode *from, AstNode *to) {
  dump_link((uint64_t) from, (uint64_t) to);
}

void AstDumpVisitor::visit_body_elements(AstListNode *body_elements) {
  dump_node(body_elements, "Body Elements");

  for (AstNode *s : body_elements->nodes) {
    dump_link(body_elements, s);
  }
}

void AstDumpVisitor::visit_function_def(FunctionDefNode *def, const std::vector<std::pair<bool, bool>>&) {
  dump_node(def, "Function Definition: " + def->sym->name + " " + def->sym->to_str());
  DEBUG("TODO: implement initializers");
}

void AstDumpVisitor::visit_derived_def(FunctionDefNode *def, bool) {
    dump_node(def, "Derived Definition: " + def->sym->name + " " + def->sym->to_str());
  dump_link(def, def->sym->derived);
}

bool AstDumpVisitor::visit_derived_function_atom( FunctionAtom* node, bool )
{
    dump_node( node, node->name );
    return 0;
}


void AstDumpVisitor::visit_init(AstNode *init) {
  dump_node(init, "Init");
}

void AstDumpVisitor::visit_rule(RuleNode *rule) {
  dump_node(rule, "Rule "+rule->name);
  dump_link(rule, rule->child_);
}

void AstDumpVisitor::visit_statements(AstListNode *stmts) {
  dump_node(stmts, "Statements");

  for (AstNode *s : stmts->nodes) {
    dump_link(stmts, s);
  }
}

void AstDumpVisitor::visit_statement(AstNode *stmt) {
  dump_node(stmt, "Statement");
  //dump_link((uint64_t) rule, (uint64_t) rule->child_);
}

void AstDumpVisitor::visit_ifthenelse(IfThenElseNode *node, bool) {
  dump_node(node, "IfThenElse");
  dump_link(node, node->condition_);
  dump_link(node, node->then_);
  if (node->else_) {
    dump_link(node, node->else_);
  }
}

bool AstDumpVisitor::visit_assert(UnaryNode *assert, bool) {
  dump_node(assert, "Assert");

  dump_link((uint64_t) assert, (uint64_t) assert->child_);
  return true;
}

void AstDumpVisitor::visit_seqblock(UnaryNode *seqblock) {
  dump_node(seqblock, "Seqblock");
  dump_link(seqblock, seqblock->child_);
}

void AstDumpVisitor::visit_parblock(UnaryNode *parblock) {
  dump_node(parblock, "Parblock");
  dump_link(parblock, parblock->child_);
}

bool AstDumpVisitor::visit_update(UpdateNode *update, bool, bool) {
  dump_node(update, "Update");

  dump_link((uint64_t) update, (uint64_t) update->func);
  dump_link(update, update->expr_);
  return true;
}

bool AstDumpVisitor::visit_update_dumps(UpdateNode *update, bool v1, bool v2) {
  return visit_update(update, v1, v2);
}

bool AstDumpVisitor::visit_call_pre(CallNode *call)
{
    dump_node(call, "Direct Call: " + call->rule_name);

    if( call->arguments )
    {
        for( ExpressionBase* a : *(call->arguments) )
        {
            dump_link(call, a);
        }
    }
    
    return 0;
}

bool AstDumpVisitor::visit_call_pre(CallNode *call, bool)
{
    dump_node(call, "Indirect Call");

    dump_link(call, call->ruleref);
    
    if( call->arguments )
    {
        for( ExpressionBase* a : *(call->arguments) )
        {
            dump_link(call, a);
        }
    }
    
    return 0;
}


bool AstDumpVisitor::visit_call(CallNode *call, std::vector<bool>& argument_results)
{
    UNUSED(call);
    UNUSED(argument_results);
    return true;
}

void AstDumpVisitor::visit_case(CaseNode* node, const bool flag, const std::vector<bool>& result)
{
    dump_node(node, "Case");
    dump_link(node, node->expr);
 
    for( auto& a : node->case_list )
    {
        dump_link(node, a.first);
        dump_link(a.first, a.second);
    }
}


bool AstDumpVisitor::visit_print( PrintNode *node, bool argument )
{
    UNUSED( argument );
    dump_node(node, "Print");
    dump_link(node, node->getAtom() );
    return true;
}


void AstDumpVisitor::visit_let(LetNode *node, bool) {
  dump_node(node, "Let "+node->identifier);
  dump_link(node, node->expr);
  dump_link(node, node->stmt);
}

void AstDumpVisitor::visit_pop(PopNode *node) {
  dump_node(node, "Pop");
  dump_link(node, node->to);
  dump_link(node, node->from);
}

void AstDumpVisitor::visit_push(PushNode *node, bool, bool) {
  dump_node(node, "Push");
  dump_link(node, node->expr);
  dump_link(node, node->to);
}

bool AstDumpVisitor::visit_expression(Expression *expr, bool, bool) {
  dump_node(expr, "Expression:"+operator_to_str(expr->op));
  if (expr->left_ != nullptr) {
    dump_link(expr, expr->left_);
  }
  if (expr->right_ != nullptr) {
    dump_link(expr, expr->right_);
  }

  return true;
}

bool AstDumpVisitor::visit_expression_single(Expression *expr, bool) {
  visit_expression(expr, true, true);
  return true;
}

bool AstDumpVisitor::visit_zero_atom( ZeroAtom *atom )
{
    dump_node( atom, std::string( "ZeroAtom: 0") );
    return true;
}

bool AstDumpVisitor::visit_int_atom(IntegerAtom *atom) {
  dump_node(atom, std::string("IntegerAtom: ")+std::to_string(atom->val_));
  return true;
}

bool AstDumpVisitor::visit_bit_atom( IntegerAtom *atom )
{
    dump_node
    ( atom
    , std::string("Bit(")
    + std::to_string( atom->type_.bitsize )
    + std::string("): ")
    + std::to_string( atom->val_ )
    );
    
    return true;
}

bool AstDumpVisitor::visit_floating_atom(FloatingAtom *atom) {
  dump_node(atom, std::string("FloatingAtom: ")+std::to_string(atom->val_));
  return true;
}

bool AstDumpVisitor::visit_undef_atom(UndefAtom *atom) {
  dump_node(atom, std::string("UndefAtom"));
  return true;
}


bool AstDumpVisitor::visit_function_atom(FunctionAtom *atom, bool[], uint16_t) {
  dump_node(atom, std::string("FunctionAtom:"+atom->name));

  if( atom->arguments )
  {
      for( auto arg : *(atom->arguments) )
      {
          dump_link( atom, arg );
      }
  }
  
  return true;
}

bool AstDumpVisitor::visit_builtin_atom(BuiltinAtom *atom, bool[], uint16_t) {
  dump_node(atom, std::string("BuiltinAtom:"+atom->to_str()));

  if( atom->arguments )
  {
      for( auto arg : *(atom->arguments) )
      {
          dump_link( atom, arg );
      }
  }
  
  return true;
}

bool AstDumpVisitor::visit_self_atom(SelfAtom *atom) {
  dump_node(atom, std::string("SelfAtom"));
  return true;
}

bool AstDumpVisitor::visit_rule_atom(RuleAtom *atom) {
  dump_node(atom, std::string("RuleAtom: "+atom->name));
  return true;
}

bool AstDumpVisitor::visit_boolean_atom(BooleanAtom *atom) {
  dump_node(atom, std::string("BooleanAtom: "+std::to_string(atom->value)));
  return true;
}

bool AstDumpVisitor::visit_string_atom(StringAtom *atom) {
  dump_node(atom, std::string("StringAtom: "+atom->string));
  return true;
}

bool AstDumpVisitor::visit_list_atom(ListAtom* atom, std::vector<bool>&) {
  dump_node(atom, std::string("ListAtom"));
  
  for (ExpressionBase* a : *(atom->expr_list)) {
    dump_link(atom, a);
  }

  return true;
}
