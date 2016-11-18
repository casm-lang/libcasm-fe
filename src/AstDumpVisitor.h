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

#ifndef CASMI_LIBINTERPRETER_AST_DUMP_VISITOR
#define CASMI_LIBINTERPRETER_AST_DUMP_VISITOR

#include <sstream>
#include <string>
#include <utility>

#include "Ast.h"
#include "Visitor.h"

class AstDumpVisitor : public BaseVisitor< bool >
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

    void visit_init( AstNode* init );
    void visit_body_elements( AstListNode* body_elements );
    void visit_function_def(
        FunctionDefNode* def, const std::vector< std::pair< bool, bool > >& );
    void visit_derived_def( FunctionDefNode* def, bool );
    void visit_rule( RuleNode* rule );
    void visit_statements( AstListNode* stmts );
    void visit_statement( AstNode* stmt );
    void visit_ifthenelse( IfThenElseNode* node, bool );
    bool visit_assert( UnaryNode* assert, bool );
    void visit_seqblock( UnaryNode* seqblock );
    void visit_parblock( UnaryNode* parblock );
    bool visit_update( UpdateNode* update, bool, bool );
    bool visit_update_dumps( UpdateNode* update, bool v1, bool v2 );
    bool visit_call_pre( CallNode* call );
    bool visit_call_pre( CallNode* call, bool );
    bool visit_call( CallNode* call, std::vector< bool >& );
    void visit_call_post( CallNode* call )
    {
        UNUSED( call );
    }
    bool visit_print( PrintNode* node, bool argument );

    void visit_let( LetNode*, bool );
    void visit_pop( PopNode* );
    void visit_push( PushNode*, bool, bool );
    void visit_case(
        CaseNode* node, const bool flag, const std::vector< bool >& result );

    void visit_forall_post( ForallNode* node );
    void visit_iterate( UnaryNode* node );

    bool visit_expression( BinaryExpression* expr, bool, bool );
    bool visit_expression_single( UnaryExpression* expr, bool );
    bool visit_zero_atom( ZeroAtom* atom );
    bool visit_int_atom( IntegerAtom* atom );
    bool visit_bit_atom( IntegerAtom* atom );
    bool visit_floating_atom( FloatingAtom* atom );
    bool visit_undef_atom( UndefAtom* );
    bool visit_function_atom( FunctionAtom* atom, std::vector< bool >& );
    bool visit_builtin_atom( BuiltinAtom*, std::vector< bool >& );
    bool visit_derived_function_atom( FunctionAtom*, bool );
    bool visit_self_atom( SelfAtom* atom );
    bool visit_rule_atom( RuleAtom* atom );
    bool visit_boolean_atom( BooleanAtom* atom );
    bool visit_string_atom( StringAtom* atom );
    bool visit_list_atom( ListAtom*, std::vector< bool >& );
    bool visit_number_range_atom( NumberRangeAtom*, bool, bool );
};

#endif // CASMI_LIBINTERPRETER_EXEC_VISITOR
