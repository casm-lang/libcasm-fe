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

#ifndef CASMI_LIBPARSE_TYPECHECK_VISITOR
#define CASMI_LIBPARSE_TYPECHECK_VISITOR

#include <utility>

#include "Ast.h"
#include "Driver.h"
#include "Types.h"
#include "Visitor.h"

class TypecheckVisitor : public BaseVisitor< Type*, Type* >
{
  private:
    void check_type_valid( const yy::location& location, const Type& type );

  public:
    Driver& driver_;
    void check_numeric_operator(
        const yy::location& loc, Type* type, const libcasm_ir::Value::ID op );

    std::vector< std::vector< Type* >* > rule_binding_types;
    std::vector< std::map< std::string, size_t >* > rule_binding_offsets;

    bool forall_head;

    TypecheckVisitor( Driver& driver );

    void visit_function_def( FunctionDefNode* def,
        const std::vector< std::pair< Type*, Type* > >& initializers ) override;
    void visit_derived_def_pre( FunctionDefNode* def ) override;
    void visit_derived_def( FunctionDefNode* def, Type* expr ) override;

    void visit_rule( RuleNode* rule ) override;
    void visit_ifthenelse( IfThenElseNode* node, Type* cond ) override;
    void visit_assert( UnaryNode* assert, Type* t ) override;
    void visit_update( UpdateNode* update,
        const std::vector< Type* >& args,
        Type* expr ) override;
    void visit_call_pre( CallNode* call ) override;
    void visit_call_pre( CallNode* call, Type* expr ) override;
    void visit_call( CallNode* call, std::vector< Type* >& arguments ) override;
    void visit_print( PrintNode* node, Type* type ) override;
    void visit_diedie( DiedieNode* node, Type* msg ) override;

    void visit_let( LetNode* node, Type* v ) override;
    void visit_let_post( LetNode* node ) override;
    void visit_push( PushNode* node, Type* expr, Type* atom ) override;
    void visit_pop( PopNode* node, Type* atom ) override;
    void visit_case( CaseNode* node,
        Type* val,
        const std::vector< Type* >& case_labels ) override;

    Type* visit_expression(
        BinaryExpression* expr, Type* left_val, Type* right_val ) override;
    Type* visit_expression_single( UnaryExpression* expr, Type* val ) override;

    Type* visit_zero_atom( ZeroAtom* atom ) override
    {
        return &atom->type_;
    }

    Type* visit_int_atom( IntegerAtom* atom ) override
    {
        return &atom->type_;
    }

    Type* visit_floating_atom( FloatingAtom* atom ) override
    {
        return &atom->type_;
    }

    Type* visit_rational_atom( RationalAtom* atom ) override
    {
        return &atom->type_;
    }

    Type* visit_undef_atom( UndefAtom* atom ) override
    {
        return &atom->type_;
    }

    Type* visit_self_atom( SelfAtom* atom ) override
    {
        return &atom->type_;
    }

    Type* visit_boolean_atom( BooleanAtom* atom ) override
    {
        return &atom->type_;
    }

    Type* visit_string_atom( StringAtom* atom ) override
    {
        return &atom->type_;
    }

    Type* visit_function_atom(
        FunctionAtom* atom, std::vector< Type* >& arguments ) override;
    Type* visit_builtin_atom(
        BuiltinAtom* atom, std::vector< Type* >& arguments ) override;

    void visit_derived_function_atom_pre(
        FunctionAtom* atom, std::vector< Type* >& arguments ) override;
    Type* visit_derived_function_atom(
        FunctionAtom* atom, Type* expr ) override;
    Type* visit_rule_atom( RuleAtom* atom ) override;
    Type* visit_list_atom(
        ListAtom* atom, const std::vector< Type* >& vals ) override;
    Type* visit_number_range_atom(
        NumberRangeAtom* atom, Type* left, Type* right ) override;
};

template <>
void AstWalker< TypecheckVisitor, Type* >::walk_forall( ForallNode* node );

#endif // CASMI_LIBINTERPRETER_EXEC_VISITOR
