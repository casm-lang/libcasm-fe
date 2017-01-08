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

#include "FunctionCycleVisitor.h"

bool InitCycleVisitor::visit_function_atom(
    FunctionAtom* atom, std::vector< bool >& )
{
    dependency_names.insert( atom->name );
    return true;
}

bool InitCycleVisitor::visit_zero_atom( ZeroAtom* )
{
    return false;
}

bool InitCycleVisitor::visit_bit_atom( IntegerAtom* )
{
    return false;
}

bool InitCycleVisitor::visit_int_atom( IntegerAtom* )
{
    return false;
}

bool InitCycleVisitor::visit_floating_atom( FloatingAtom* )
{
    return false;
}

bool InitCycleVisitor::visit_rational_atom( RationalAtom* )
{
    return false;
}

bool InitCycleVisitor::visit_undef_atom( UndefAtom* )
{
    return false;
}

bool InitCycleVisitor::visit_self_atom( SelfAtom* )
{
    return false;
}

bool InitCycleVisitor::visit_rule_atom( RuleAtom* )
{
    return false;
}

bool InitCycleVisitor::visit_boolean_atom( BooleanAtom* )
{
    return false;
}

bool InitCycleVisitor::visit_string_atom( StringAtom* )
{
    return false;
}

bool InitCycleVisitor::visit_builtin_atom(
    BuiltinAtom*, std::vector< bool, std::allocator< bool > >& )
{
    return false;
}

void InitCycleVisitor::visit_derived_function_atom_pre(
    FunctionAtom*, std::vector< bool, std::allocator< bool > >& )
{
}

bool InitCycleVisitor::visit_derived_function_atom( FunctionAtom*, bool )
{
    return false;
}

bool InitCycleVisitor::visit_list_atom(
    ListAtom*, std::vector< bool, std::allocator< bool > > const& )
{
    return false;
}

bool InitCycleVisitor::visit_number_range_atom( NumberRangeAtom*, bool, bool )
{
    return false;
}

bool InitCycleVisitor::visit_expression( BinaryExpression*, bool, bool )
{
    return false;
}

bool InitCycleVisitor::visit_expression_single( UnaryExpression*, bool )
{
    return false;
}

void InitCycleVisitor::visit_specification( SpecificationNode* )
{
}

void InitCycleVisitor::visit_init( InitNode* )
{
}

void InitCycleVisitor::visit_body_elements( AstListNode* )
{
}

void InitCycleVisitor::visit_rule_post( RuleNode* )
{
}

void InitCycleVisitor::visit_seqblock_pre( UnaryNode* )
{
}

void InitCycleVisitor::visit_seqblock_post( UnaryNode* )
{
}

void InitCycleVisitor::visit_parblock_pre( UnaryNode* )
{
}

void InitCycleVisitor::visit_parblock_post( UnaryNode* )
{
}

void InitCycleVisitor::visit_assure( UnaryNode*, bool )
{
}

void InitCycleVisitor::visit_skip( AstNode* )
{
}

void InitCycleVisitor::visit_call_post( CallNode* )
{
}

void InitCycleVisitor::visit_iterate( UnaryNode* )
{
}

void InitCycleVisitor::visit_case_pre( CaseNode*, bool )
{
}

void InitCycleVisitor::visit_impossible( AstNode* )
{
}

void InitCycleVisitor::visit_statements( AstListNode* )
{
}

void InitCycleVisitor::visit_function_def(
    FunctionDefNode*, std::vector< std::pair< bool, bool >,
                          std::allocator< std::pair< bool, bool > > > const& )
{
}

void InitCycleVisitor::visit_derived_def_pre( FunctionDefNode* )
{
}
void InitCycleVisitor::visit_derived_def( FunctionDefNode*, bool )
{
}

void InitCycleVisitor::visit_rule( RuleNode* )
{
}
void InitCycleVisitor::visit_statement( AstNode* )
{
}
void InitCycleVisitor::visit_ifthenelse( IfThenElseNode*, bool )
{
}
void InitCycleVisitor::visit_assert( UnaryNode*, bool )
{
}
void InitCycleVisitor::visit_update(
    UpdateNode*, std::vector< bool, std::allocator< bool > >&, bool )
{
}
void InitCycleVisitor::visit_call_pre( CallNode* )
{
}
void InitCycleVisitor::visit_call_pre( CallNode*, bool )
{
}
void InitCycleVisitor::visit_call(
    CallNode*, std::vector< bool, std::allocator< bool > >& )
{
}
void InitCycleVisitor::visit_print( PrintNode*, bool )
{
}
void InitCycleVisitor::visit_diedie( DiedieNode*, bool )
{
}
void InitCycleVisitor::visit_let( LetNode*, bool )
{
}
void InitCycleVisitor::visit_let_post( LetNode* )
{
}
void InitCycleVisitor::visit_pop( PopNode*, bool )
{
}
void InitCycleVisitor::visit_push( PushNode*, bool, bool )
{
}
void InitCycleVisitor::visit_case(
    CaseNode*, bool, std::vector< bool, std::allocator< bool > > const& )
{
}
void InitCycleVisitor::visit_forall_pre( ForallNode* )
{
}
void InitCycleVisitor::visit_forall_post( ForallNode* )
{
}
void InitCycleVisitor::visit_forall_iteration_pre( ForallNode*, bool )
{
}
void InitCycleVisitor::visit_forall_iteration_post( ForallNode* )
{
}
