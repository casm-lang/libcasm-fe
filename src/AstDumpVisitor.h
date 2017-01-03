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
//  along with libcasm-fe. If not, see <http://www.gnu.org/licenses/>.
//

#ifndef CASMI_LIBINTERPRETER_AST_DUMP_VISITOR
#define CASMI_LIBINTERPRETER_AST_DUMP_VISITOR

#include <sstream>
#include <string>
#include <utility>

#include "Ast.h"
#include "Visitor.h"

class AstDumpVisitor : public BaseVisitor< bool, bool >
{
  private:
    std::stringstream dump_stream_;

    void dump_node( uint64_t key, const std::string& name );
    void dump_node( AstNode* n, const std::string& name );
    void dump_link( uint64_t from, uint64_t to );
    void dump_link( AstNode* from, AstNode* to );

  public:
    AstDumpVisitor();
    std::string get_dump();

    void visit_init( InitNode* init ) override;
    void visit_body_elements( AstListNode* body_elements ) override;
    void visit_function_def( FunctionDefNode* def,
        const std::vector< std::pair< bool, bool > >& ) override;
    void visit_derived_def( FunctionDefNode* def, bool ) override;
    void visit_rule( RuleNode* rule ) override;
    void visit_statements( AstListNode* stmts ) override;
    void visit_statement( AstNode* stmt ) override;
    void visit_ifthenelse( IfThenElseNode* node, bool ) override;
    void visit_assert( UnaryNode* assert, bool ) override;
    void visit_seqblock_pre( UnaryNode* seqblock ) override;
    void visit_parblock_pre( UnaryNode* parblock ) override;
    void visit_update(
        UpdateNode* update, const std::vector< bool >&, bool ) override;
    void visit_call_pre( CallNode* call ) override;
    void visit_call_pre( CallNode* call, bool ) override;
    void visit_print( PrintNode* node, bool argument ) override;

    void visit_let( LetNode*, bool ) override;
    void visit_pop( PopNode*, bool ) override;
    void visit_push( PushNode*, bool, bool ) override;
    void visit_case(
        CaseNode* node, bool flag, const std::vector< bool >& result ) override;

    void visit_forall_post( ForallNode* node ) override;
    void visit_iterate( UnaryNode* node ) override;

    bool visit_expression( BinaryExpression* expr, bool, bool ) override;
    bool visit_expression_single( UnaryExpression* expr, bool ) override;
    bool visit_zero_atom( ZeroAtom* atom ) override;
    bool visit_int_atom( IntegerAtom* atom ) override;
    bool visit_bit_atom( IntegerAtom* atom ) override;
    bool visit_floating_atom( FloatingAtom* atom ) override;
    bool visit_undef_atom( UndefAtom* ) override;
    bool visit_function_atom(
        FunctionAtom* atom, std::vector< bool >& ) override;
    bool visit_builtin_atom( BuiltinAtom*, std::vector< bool >& ) override;
    bool visit_derived_function_atom( FunctionAtom*, bool ) override;
    bool visit_self_atom( SelfAtom* atom ) override;
    bool visit_rule_atom( RuleAtom* atom ) override;
    bool visit_boolean_atom( BooleanAtom* atom ) override;
    bool visit_string_atom( StringAtom* atom ) override;
    bool visit_list_atom( ListAtom*, const std::vector< bool >& ) override;
    bool visit_number_range_atom( NumberRangeAtom*, bool, bool ) override;
};

#endif // CASMI_LIBINTERPRETER_EXEC_VISITOR
