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

#ifndef CASMI_LIBPARSE_VISITOR_H
#define CASMI_LIBPARSE_VISITOR_H

#include "Exceptions.h"
#include "Ast.h"

class AstNode;

template<class T, class V> class AstWalker {
  public:
    T& visitor;
    bool suppress_calls;
    
    AstWalker(T& v)
    : visitor(v)
    , suppress_calls(false)
    {
    }
    
    void walk_specification( Ast* spec )
    {
        assert( spec->node_type_ == NodeType::SPECIFICATION );
        visitor.visit_specification( spec->getSpecification() );
        walk_body_elements( spec->getElements() );
    }
    
    
    void walk_body_elements(AstListNode *body_elements) {
      for (auto e : body_elements->nodes) {
        switch(e->node_type_) {
          case NodeType::PROVIDER: {break;} // TODO implement
          case NodeType::OPTION: {break;} // TODO implement
          case NodeType::ENUM: {break;} // TODO implement
          case NodeType::FUNCTION: {
            walk_function_def(reinterpret_cast<FunctionDefNode*>(e));
            break;
          }
          case NodeType::DERIVED: {break;} // TODO implement
          case NodeType::RULE: {
            walk_rule(reinterpret_cast<RuleNode*>(e));
            break; 
          } 
          case NodeType::INIT: {
            visitor.visit_init(reinterpret_cast<InitNode*>(e));
            break;
          }
          default: {
            throw RuntimeException(
              std::string("Invalid node type: ")+
              type_to_str(e->node_type_)+
              std::string(" at ")+
              e->location_str());
          }
        }
      }
      visitor.visit_body_elements(body_elements);
    }

    void walk_function_def(FunctionDefNode *def) {
      if (def->sym->type == Symbol::SymbolType::FUNCTION) {
        std::vector<std::pair<V, V>> initializer_results;
        if (def->sym->intitializers_) {
          for (std::pair<ExpressionBase*, ExpressionBase*> p : *def->sym->intitializers_) {
            V first;
            if (p.first) {
              first = walk_expression_base(p.first);
            } else {
              UndefAtom foo = {p.second->location};
              first = walk_atom(&foo);
            }
            initializer_results.push_back(
                std::pair<V, V>(first, walk_expression_base(p.second))
            );
          }
        }

        visitor.visit_function_def(def, initializer_results);
      } else {
        visitor.visit_derived_def_pre(def);
        V v = walk_expression_base(def->sym->derived);
        visitor.visit_derived_def(def, v);
      }
    }

    void walk_rule(RuleNode *rule) {
      visitor.visit_rule(rule);
      walk_statement(rule->child_);
      visitor.visit_rule_post(rule);
    }

    void walk_skip(AstNode* node)
    {
        visitor.visit_skip(node);
    }
    
    void walk_statement(AstNode *stmt) {
      switch(stmt->node_type_) {
        case NodeType::SEQBLOCK:
          walk_seqblock(reinterpret_cast<UnaryNode*>(stmt));
          break;
        case NodeType::PARBLOCK:
          walk_parblock(reinterpret_cast<UnaryNode*>(stmt));
          break;
        case NodeType::UPDATE:
          walk_update(reinterpret_cast<UpdateNode*>(stmt));
          break;
        case NodeType::ASSERT: {
          UnaryNode *assert = reinterpret_cast<UnaryNode*>(stmt);
          V v = walk_expression_base(reinterpret_cast<ExpressionBase*>(assert->child_));
          visitor.visit_assert(assert, v);
          break;
        }
        case NodeType::ASSURE: {
          UnaryNode *assure = reinterpret_cast<UnaryNode*>(stmt);
          V v = walk_expression_base(reinterpret_cast<ExpressionBase*>(assure->child_));
          visitor.visit_assure(assure, v);
          break;
        }
        case NodeType::SKIP:
        {
            // skip does nothing, but in the IR we need this "trivial" information for processing!
            walk_skip(stmt);
            break; 
        }
        case NodeType::IFTHENELSE: {
          walk_ifthenelse(reinterpret_cast<IfThenElseNode*>(stmt));
          break;
        }
        case NodeType::CALL: {
          walk_call(reinterpret_cast<CallNode*>(stmt));
          break;
        }
        case NodeType::PRINT: {
          walk_print(reinterpret_cast<PrintNode*>(stmt));
          break;
        }
        case NodeType::LET: {
          walk_let(reinterpret_cast<LetNode*>(stmt));
          break;
        }
        case NodeType::POP: {
          walk_pop(reinterpret_cast<PopNode*>(stmt));
          break;
        }
        case NodeType::PUSH: {
          walk_push(reinterpret_cast<PushNode*>(stmt));
          break;
        }
        case NodeType::FORALL: {
          walk_forall(reinterpret_cast<ForallNode*>(stmt));
          break;
        }
        case NodeType::ITERATE: {
          walk_iterate(reinterpret_cast<UnaryNode*>(stmt));
          break;
        }
        case NodeType::CASE: {
          walk_case(reinterpret_cast<CaseNode*>(stmt));
          break;
        }
        case NodeType::UPDATE_DUMPS:
          walk_update_dumps(reinterpret_cast<UpdateNode*>(stmt));
          break;
        case NodeType::DIEDIE: {
            DiedieNode *node = reinterpret_cast<DiedieNode*>(stmt);
            if (node->msg) {
              visitor.visit_diedie(node, walk_expression_base(node->msg));
            } else {
              visitor.visit_diedie(node, V());
            }
          }
          break;
        case NodeType::IMPOSSIBLE:
            visitor.visit_impossible(stmt);
          break;

        default:
            throw RuntimeException(
              std::string("Invalid node type: ")+
              type_to_str(stmt->node_type_)+
              std::string(" at ")+
              stmt->location_str());
      }
    }

    void walk_seqblock(UnaryNode *parblock) {
      visitor.visit_seqblock(parblock);
      walk_statements(reinterpret_cast<AstListNode*>(parblock->child_));
    }

    void walk_parblock(UnaryNode *parblock) {
      visitor.visit_parblock(parblock);
      walk_statements(reinterpret_cast<AstListNode*>(parblock->child_));
    }

    void walk_statements(AstListNode *stmts) {
      visitor.visit_statements(stmts);
      for (auto stmt: stmts->nodes) {
        walk_statement(stmt);
      }
    }

    void walk_update(UpdateNode *update) {
      V expr_t = walk_expression_base(update->expr_);

      // we must walk the expression before walking update->func because it 
      // sets the list of arguments and we do not want the update->expr_ to
      // overwrite the value_list
      V func_t = walk_function_atom(update->func);
      visitor.visit_update(update, func_t, expr_t);
    }


    void walk_update_dumps(UpdateNode *update) {
      V expr_t = walk_expression_base(update->expr_);

      // we must walk the expression before walking update->func because it 
      // sets the list of arguments and we do not want the update->expr_ to
      // overwrite the value_list
      V func_t = walk_function_atom(update->func);
      visitor.visit_update_dumps(update, func_t, expr_t);
    }


    void walk_call(CallNode *call) {
      if (call->ruleref == nullptr) {
        visitor.visit_call_pre(call);
      } else {
        V v = walk_expression_base(call->ruleref);
        visitor.visit_call_pre(call, v);
      }
      
      // we must evaluate all arguments, to set correct offset for bindings
      std::vector<V> argument_results;
      if (call->arguments != nullptr) {
        for (ExpressionBase *e: *call->arguments) {
          argument_results.push_back(walk_expression_base(e));
        }
      }
      if (call->rule != nullptr) {
        visitor.visit_call(call, argument_results);

        if( !suppress_calls )
        {
            walk_rule(call->rule);
        }
        
        visitor.visit_call_post(call);
      } else {
        DEBUG("rule not set!");
      }
    }

    void walk_print( PrintNode* node )
    {
        visitor.visit_print
        ( node
        , walk_expression_base( node->getAtom() )
        );
    }
    
    void walk_let(LetNode *node) {
      V v = walk_expression_base(node->expr);
      visitor.visit_let(node, v);
      walk_statement(node->stmt);
      visitor.visit_let_post(node);
    }

    void walk_pop(PopNode *node) {
      walk_function_atom(node->from);
      visitor.visit_pop(node);
    }

    void walk_push(PushNode *node) {
      V expr = walk_expression_base(node->expr);
      V atom = walk_function_atom(node->to);
      visitor.visit_push(node, expr, atom);
    }

    void walk_forall(ForallNode *node) {
      walk_expression_base(node->in_expr);
      visitor.visit_forall_pre(node);
      walk_statement(node->statement);
      visitor.visit_forall_post(node);
    }

    void walk_iterate(UnaryNode* node) {
      visitor.visit_iterate(node);
      walk_statement(node->child_);
    }

    void walk_case(CaseNode *node) {
        V web = walk_expression_base(node->expr);
        visitor.visit_case_pre(node, web );
        std::vector<V> case_labels;
        for (auto& pair : node->case_list) {
            // pair.first == nullptr for default:
            if( pair.first )
            {
                case_labels.push_back(walk_atom(pair.first));
            }
            walk_statement(pair.second);
        }
        visitor.visit_case(node, web, case_labels);
    }
    
    V walk_expression_base( ExpressionBase *expr )
    {
        if( expr->node_type_ == NodeType::EXPRESSION )
        {
            Expression *e = reinterpret_cast< Expression* >( expr );

            V lhs{};
            V rhs{};
            
            if( e->left_ and e->right_ )
            {
                if( e->left_->node_type_ == NodeType::ZERO_ATOM )
                {
                    // IMPORTANT: right hand side has to be evaluated first to assign the
                    // correct typed zero value to the left hand side
                    rhs = walk_expression_base( e->right_ );
                    lhs = walk_expression_base( e->left_ );                     
                }
                else
                {
                    lhs = walk_expression_base( e->left_ );
                    rhs = walk_expression_base( e->right_ );
                }
                return visitor.visit_expression( e, lhs, rhs );
            }
            else
            {
                lhs = walk_expression_base( e->left_ );
                return visitor.visit_expression_single( e, lhs );
            }
        }
        else
        {
            return walk_atom( reinterpret_cast< AtomNode* >( expr ) );
        }
        
        throw RuntimeException("Invalid expression structure");
    }

    void walk_ifthenelse(IfThenElseNode *n) {
      V cond = walk_expression_base(n->condition_);
      visitor.visit_ifthenelse(n, cond);
      walk_statement(n->then_);
      if (n->else_) {
        walk_statement(n->else_);
      }
    }

    V walk_function_atom(BaseFunctionAtom *func) {
      V arguments[10];

      uint16_t i = 0;
      if (func->arguments) {
        for (; i < func->arguments->size(); i++) {
          arguments[i] = walk_expression_base(func->arguments->at(i));
        }
      } 
      if (func->node_type_ == NodeType::BUILTIN_ATOM) {
         return visitor.visit_builtin_atom(reinterpret_cast<BuiltinAtom*>(func), arguments, i);
      } else {
        FunctionAtom *func_a = reinterpret_cast<FunctionAtom*>(func);
        if (func_a->symbol_type == FunctionAtom::SymbolType::DERIVED) {
          visitor.visit_derived_function_atom_pre(func_a, arguments, i);
          V expr = walk_expression_base(func_a->symbol->derived);
          return visitor.visit_derived_function_atom(func_a, expr);
        } else {
          return visitor.visit_function_atom(func_a, arguments, i);
        }
      }
    }

    V walk_list_atom(ListAtom *atom) {
      std::vector<V> expr_results;
      if (atom->expr_list) {
        for (ExpressionBase* e : *atom->expr_list) {
          expr_results.push_back(walk_expression_base(e));
        }
      }
      return visitor.visit_list_atom(atom, expr_results);
    }

    V walk_atom( AtomNode* atom )
    {
        switch( atom->node_type_ )
        {
            case NodeType::ZERO_ATOM:
            {
                return visitor.visit_zero_atom( reinterpret_cast< ZeroAtom* >( atom ) );
            }
            case NodeType::INTEGER_ATOM:
            {
                IntegerAtom* ia = reinterpret_cast< IntegerAtom* >( atom );
                
                if( ia->type_.t == TypeType::BIT )
                {
                    return visitor.visit_bit_atom( ia );
                }
                
                return visitor.visit_int_atom( ia );
            }
            case NodeType::FLOATING_ATOM:
            {
                return visitor.visit_floating_atom( reinterpret_cast< FloatingAtom* >( atom ) );
            }
            case NodeType::RATIONAL_ATOM:
            {
                return visitor.visit_rational_atom( reinterpret_cast< RationalAtom* >( atom ) );
            }
            case NodeType::UNDEF_ATOM:
            {
                return visitor.visit_undef_atom( reinterpret_cast< UndefAtom* >( atom ) );
            }
            case NodeType::BUILTIN_ATOM: // fall-through
            case NodeType::FUNCTION_ATOM:
            {
                return walk_function_atom( reinterpret_cast< BaseFunctionAtom* >( atom ) );
            }
            case NodeType::SELF_ATOM:
            {
                return visitor.visit_self_atom( reinterpret_cast< SelfAtom* >( atom ) );
            }
            case NodeType::RULE_ATOM:
            {
                return visitor.visit_rule_atom( reinterpret_cast< RuleAtom* >( atom ) );
            }
            case NodeType::BOOLEAN_ATOM:
            {
                return visitor.visit_boolean_atom( reinterpret_cast< BooleanAtom* >( atom ) );
            }
            case NodeType::STRING_ATOM:
            {
                return visitor.visit_string_atom( reinterpret_cast< StringAtom* >( atom ) );
            }
            case NodeType::LIST_ATOM:
            {
                return walk_list_atom(reinterpret_cast< ListAtom* >( atom ) );
            }
            case NodeType::NUMBER_RANGE_ATOM:
            {
                return visitor.visit_number_range_atom( reinterpret_cast< NumberRangeAtom* >( atom ) );
            }
            default:
            {
                throw RuntimeException
                ( "Invalid atom type:"
                  + type_to_str( atom->node_type_ )
                  + std::to_string( atom->node_type_ )
                );
            }
        }
    }
};


template<class T> class BaseVisitor {
  public:
    void visit_specification(SpecificationNode*) {}
    void visit_init(InitNode*) {}
    void visit_body_elements(AstListNode*) {}
    void visit_function_def(FunctionDefNode*, const std::vector<std::pair<T,T>>&) {}
    void visit_derived_def_pre(FunctionDefNode*) {}
    void visit_derived_def(FunctionDefNode*, T) {}
    void visit_rule(RuleNode*) {}
    void visit_rule_post(RuleNode*) {}
    void visit_statements(AstListNode*) {}
    void visit_statement(AstNode*) {}
    void visit_ifthenelse(IfThenElseNode*, T) {}
    void visit_assert(UnaryNode*, T) {}
    void visit_assure(UnaryNode*, T) {}
    void visit_seqblock(UnaryNode*) {}
    void visit_parblock(UnaryNode*) {}
    T visit_update(UpdateNode*, T, T) { return T(); }
    T visit_update_dumps(UpdateNode *u, T v1, T v2) { return visit_update(u, v1, v2); }
    T visit_call_pre(CallNode*) { return T(); }
    T visit_call_pre(CallNode*, T) { return T(); }
    T visit_call(CallNode*, std::vector<T>&) { return T(); }
    void visit_call_post(CallNode*) {}
    T visit_print(PrintNode*, T) { return T(); }
    void visit_diedie(DiedieNode*, const T&) {}
    void visit_impossible(AstNode*) {}

    void visit_let(LetNode*, T) {}
    void visit_let_post(LetNode*) {}
    void visit_pop(PopNode*) { }
    void visit_push(PushNode*, T , T)  { }
    void visit_case_pre(CaseNode*, const T ) { }
    void visit_case(CaseNode*, const T, const std::vector<T>&) { }
    void visit_skip( AstNode* node ) {}
    
    void visit_forall_pre(ForallNode*) { }
    void visit_forall_post(ForallNode*) { }

    void visit_iterate(UnaryNode*) { }

    T visit_expression(Expression*, T, T) { return T(); }
    T visit_expression_single(Expression*, T) { return T(); }
    T visit_zero_atom( ZeroAtom* ) { return T(); }
    T visit_int_atom(IntegerAtom*) { return T(); }
    T visit_bit_atom(IntegerAtom*) { return T(); }
    T visit_floating_atom(FloatingAtom*) { return T(); }
    T visit_rational_atom(RationalAtom*) { return T(); }
    T visit_undef_atom(UndefAtom*) { return T(); }
    T visit_function_atom(FunctionAtom *, const std::vector<T> &) { return T(); }
    T visit_builtin_atom(BuiltinAtom*, T[], uint16_t) { return T(); }
    void visit_derived_function_atom_pre(FunctionAtom*, T[], uint16_t) {}
    T visit_derived_function_atom(FunctionAtom*, T) { return T(); }
    T visit_self_atom(SelfAtom*) { return T(); }
    T visit_rule_atom(RuleAtom*) { return T(); }
    T visit_boolean_atom(BooleanAtom*) { return T(); }
    T visit_string_atom(StringAtom*) { return T(); }
    T visit_list_atom(ListAtom*, std::vector<T> &) { return T(); }
    T visit_number_range_atom(NumberRangeAtom*) { return T(); }
};

#endif

//  
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
