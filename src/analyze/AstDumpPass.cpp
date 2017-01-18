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

#include "AstDumpPass.h"

#include "TypeCheckPass.h"

using namespace libcasm_fe;

char AstDumpPass::id = 0;

static libpass::PassRegistration< AstDumpPass > PASS( "AST Dumping Pass",
    "generates a DOT graph of the AST and dumps it to './obj/out.dot' for now",
    "ast-dump", 0 );

bool AstDumpPass::run( libpass::PassResult& pr )
{
    Ast* node = (Ast*)pr.getResult< TypeCheckPass >();

    AstWalker< AstDumpPass, bool > dump_walker( *this );
    dump_walker.walk_specification( node );

    // std::cout << this->get_dump() << std::endl;

    std::ofstream dotfile( "./obj/out.dot" );
    dotfile << this->get_dump() << "\n";
    dotfile.close();

    return true;
}

std::string AstDumpPass::get_dump()
{
    return std::string( "digraph \"main\" {\n" ) + dump_stream_.str()
           + std::string( "}" );
}

void AstDumpPass::dump_node( uint64_t key, const std::string& name )
{
    dump_stream_ << "    " << key << " [label=\"" << name << "\"];"
                 << std::endl;
}

void AstDumpPass::dump_node( AstNode* n, const std::string& name )
{
    dump_node( (uint64_t)n, name );
}

void AstDumpPass::dump_link( uint64_t from, uint64_t to )
{
    dump_stream_ << "    " << from << " -> " << to << ";" << std::endl;
}

void AstDumpPass::dump_link( AstNode* from, AstNode* to )
{
    dump_link( (uint64_t)from, (uint64_t)to );
}

void AstDumpPass::dump_arguments(
    AstNode* from, std::vector< ExpressionBase* >* arguments )
{
    if( arguments )
    {
        for( auto arg : *arguments )
        {
            dump_link( from, arg );
        }
    }
}

void AstDumpPass::visit_root( Ast* node )
{
    dump_node( node, "CASM" );
    dump_link( node, node->getSpecification() );
    dump_link( node, node->getElements() );
}

void AstDumpPass::visit_specification( SpecificationNode* node )
{
    dump_node( node, "Specification\\n'" + node->identifier + "'" );
}

void AstDumpPass::visit_body_elements_pre( AstListNode* body_elements )
{
    dump_node( body_elements, "BodyElements" );
}

void AstDumpPass::visit_body_elements_post( AstListNode* body_elements )
{
    for( auto s : body_elements->nodes )
    {
        dump_link( body_elements, s );
    }
}

void AstDumpPass::visit_function_def_pre( FunctionDefNode* def )
{
    dump_node( def, "Function Definition: '" + def->sym->name + "'\\n"
                        + def->sym->to_str() );
}

void AstDumpPass::visit_function_def_post( FunctionDefNode* def )
{
    for( auto initializer : def->initializers() )
    {
        dump_link( def, initializer );
    }
}

void AstDumpPass::visit_derived_def_pre( DerivedDefNode* def )
{
    dump_node( def,
        "Derived Definition: " + def->sym->name + " " + def->sym->to_str() );
}

void AstDumpPass::visit_derived_def( DerivedDefNode* def, bool )
{
    dump_link( def, def->sym->derived );
}

bool AstDumpPass::visit_derived_function_atom( FunctionAtom* atom, bool )
{
    dump_node( atom, "Derived: '" + atom->name + "'" );
    dump_arguments( atom, atom->arguments );
    return true;
}

void AstDumpPass::visit_init( InitNode* init )
{
    dump_node( init, "Init" );
    dump_link( init, init->progamDef );
}

void AstDumpPass::visit_rule_post( RuleNode* rule )
{
    dump_node( rule, "Rule: '" + rule->name + "'" );
}

void AstDumpPass::visit_rule( RuleNode* rule )
{
    dump_link( rule, rule->child_ );
}

void AstDumpPass::visit_statements( AstListNode* stmts )
{
    dump_node( stmts, "Statements" );

    for( auto s : stmts->nodes )
    {
        dump_link( stmts, s );
    }
}

void AstDumpPass::visit_statement( AstNode* stmt )
{
    dump_node( stmt, "Statement" );
    // dump_link((uint64_t) rule, (uint64_t) rule->child_);
}

void AstDumpPass::visit_ifthenelse( IfThenElseNode* node, bool )
{
    dump_node( node, "IfThenElse" );
    dump_link( node, node->condition_ );
    dump_link( node, node->then_ );
    if( node->else_ )
    {
        dump_link( node, node->else_ );
    }
}

void AstDumpPass::visit_assert( UnaryNode* assert, bool )
{
    dump_node( assert, "Assert" );
    dump_link( assert, assert->child_ );
}

void AstDumpPass::visit_assure( UnaryNode* assure, bool )
{
    dump_node( assure, "Assure" );
    dump_link( assure, assure->child_ );
}

void AstDumpPass::visit_seqblock_pre( UnaryNode* seqblock )
{
    dump_node( seqblock, "Seqblock" );
}

void AstDumpPass::visit_seqblock_post( UnaryNode* seqblock )
{
    dump_link( seqblock, seqblock->child_ );
}

void AstDumpPass::visit_parblock_pre( UnaryNode* parblock )
{
    dump_node( parblock, "Parblock" );
}

void AstDumpPass::visit_parblock_post( UnaryNode* parblock )
{
    dump_link( parblock, parblock->child_ );
}

void AstDumpPass::visit_update(
    UpdateNode* update, std::vector< bool >& args, bool )
{
    dump_node( update, "Update" );
    visit_function_atom( update->func, args );
    dump_link( update, update->func );
    dump_link( update, update->expr_ );
}

void AstDumpPass::visit_call_pre( CallNode* call )
{
    dump_node( call, "Direct Call: '" + call->rule_name + "'" );
    dump_arguments( call, call->arguments );
}

void AstDumpPass::visit_call_pre( CallNode* call, bool )
{
    dump_node( call, "Indirect Call" );
    dump_link( call, call->ruleref );
    dump_arguments( call, call->arguments );
}

void AstDumpPass::visit_case( CaseNode* node, bool, const std::vector< bool >& )
{
    dump_node( node, "Case" );
    dump_link( node, node->expr );

    for( const auto& a : node->case_list )
    {
        dump_link( node, a.first );
        dump_link( a.first, a.second );
    }
}

void AstDumpPass::visit_forall_pre( ForallNode* node )
{
    dump_node( node, "Forall" );
}

void AstDumpPass::visit_forall_post( ForallNode* node )
{
    dump_link( node, node->in_expr );
    dump_link( node, node->statement );
}

void AstDumpPass::visit_iterate( UnaryNode* node )
{
    dump_node( node, "Iterate" );
    dump_link( node, node->child_ );
}

void AstDumpPass::visit_print( PrintNode* node, bool )
{
    dump_node( node, "Print" );
    dump_link( node, node->getAtom() );
}

void AstDumpPass::visit_let( LetNode* node, bool )
{
    dump_node( node, "Let " + node->identifier );
}

void AstDumpPass::visit_let_post( LetNode* node )
{
    dump_link( node, node->expr );
    dump_link( node, node->stmt );
}

void AstDumpPass::visit_pop( PopNode* node, bool )
{
    dump_node( node, "Pop" );
    dump_link( node, node->to );
    dump_link( node, node->from );
}

void AstDumpPass::visit_push( PushNode* node, bool, bool )
{
    dump_node( node, "Push" );
    dump_link( node, node->expr );
    dump_link( node, node->to );
}

bool AstDumpPass::visit_expression( BinaryExpression* expr, bool, bool )
{
    dump_node( expr, "Expression: " + operator_to_str( expr->op ) );
    dump_link( expr, expr->left_ );
    dump_link( expr, expr->right_ );
    return true;
}

bool AstDumpPass::visit_expression_single( UnaryExpression* expr, bool )
{
    dump_node( expr, "Expression: " + operator_to_str( expr->op ) );
    dump_link( expr, expr->expr_ );
    return true;
}

bool AstDumpPass::visit_zero_atom( ZeroAtom* atom )
{
    dump_node( atom, "ZeroAtom: 0" );
    return true;
}

bool AstDumpPass::visit_int_atom( IntegerAtom* atom )
{
    dump_node( atom, "Integer: " + std::to_string( atom->val_ ) );
    return true;
}

bool AstDumpPass::visit_bit_atom( IntegerAtom* atom )
{
    dump_node( atom, "Bit(" + std::to_string( atom->type_.bitsize ) + "): "
                         + std::to_string( atom->val_ ) );

    return true;
}

bool AstDumpPass::visit_floating_atom( FloatingAtom* atom )
{
    dump_node( atom, "Floating: " + std::to_string( atom->val_ ) );
    return true;
}

bool AstDumpPass::visit_undef_atom( UndefAtom* atom )
{
    dump_node( atom, "'undef'" );
    return true;
}

bool AstDumpPass::visit_function_atom(
    FunctionAtom* atom, std::vector< bool >& )
{
    dump_node( atom, "Function: '" + atom->name + "'" );
    dump_arguments( atom, atom->arguments );
    return true;
}

bool AstDumpPass::visit_builtin_atom( BuiltinAtom* atom, std::vector< bool >& )
{
    dump_node( atom, "Builtin: '" + atom->to_str() + "'" );
    dump_arguments( atom, atom->arguments );
    return true;
}

bool AstDumpPass::visit_self_atom( SelfAtom* atom )
{
    dump_node( atom, "Agent: 'self'" );
    return true;
}

bool AstDumpPass::visit_rule_atom( RuleAtom* atom )
{
    dump_node( atom, "RuleRef: '@" + atom->name + "'" );
    return true;
}

bool AstDumpPass::visit_boolean_atom( BooleanAtom* atom )
{
    dump_node(
        atom, "Boolean: " + std::string( atom->value ? "true" : "false" ) );
    return true;
}

bool AstDumpPass::visit_string_atom( StringAtom* atom )
{
    dump_node( atom, "String: \\\"" + atom->string + "\\\"" );
    return true;
}

bool AstDumpPass::visit_list_atom( ListAtom* atom, const std::vector< bool >& )
{
    dump_node( atom, "List: " );

    for( auto a : *( atom->expr_list ) )
    {
        dump_link( atom, a );
    }

    return true;
}

bool AstDumpPass::visit_number_range_atom( NumberRangeAtom* atom, bool, bool )
{
    dump_node( atom, "NumberRange" );
    dump_link( atom, atom->left );
    dump_link( atom, atom->right );
    return true;
}

void AstDumpPass::visit_call(
    CallNode*, std::vector< bool, std::allocator< bool > >& )
{
}

void AstDumpPass::visit_call_post( CallNode* )
{
}

void AstDumpPass::visit_diedie( DiedieNode*, bool )
{
}

void AstDumpPass::visit_impossible( AstNode* )
{
}

void AstDumpPass::visit_case_pre( CaseNode*, bool )
{
}

void AstDumpPass::visit_skip( AstNode* )
{
}

void AstDumpPass::visit_forall_iteration_pre( ForallNode*, bool )
{
}

void AstDumpPass::visit_forall_iteration_post( ForallNode* )
{
}

bool AstDumpPass::visit_rational_atom( RationalAtom* )
{
    return false;
}

void AstDumpPass::visit_derived_function_atom_pre(
    FunctionAtom*, std::vector< bool, std::allocator< bool > >& )
{
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
