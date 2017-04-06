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

#include "AstToCasmIRPass.h"

#include "../stdhl/cpp/Default.h"

#include "../casm-ir/src/Block.h"
#include "../casm-ir/src/Builtin.h"
#include "../casm-ir/src/Constant.h"
#include "../casm-ir/src/Derived.h"
#include "../casm-ir/src/Function.h"
#include "../casm-ir/src/Instruction.h"
#include "../casm-ir/src/Specification.h"
#include "../casm-ir/src/Statement.h"
#include "../casm-ir/src/Type.h"

using namespace libcasm_fe;

char AstToCasmIRPass::id = 0;

static libpass::PassRegistration< AstToCasmIRPass > PASS( "AST to CASM IR",
    "translates the AST to the CASM intermeditate representation",
    "ast2ir",
    0 );

constexpr const char* single_execution_agent = "agent0";

libcasm_ir::Type::Ptr AstToCasmIRPass::getType( Type* type )
{
    assert( type && "not initialized type used" );

    switch( type->t )
    {
        case TypeType::RULEREF:
            return libstdhl::get< libcasm_ir::RuleReferenceType >();
        case TypeType::BOOLEAN:
            return libstdhl::get< libcasm_ir::BooleanType >();
        case TypeType::INTEGER:
            return libstdhl::get< libcasm_ir::IntegerType >();
        case TypeType::BIT:
            return libstdhl::get< libcasm_ir::BitType >( type->bitsize );
        case TypeType::STRING:
            return libstdhl::get< libcasm_ir::StringType >();
        default:
            throw std::domain_error(
                "unimplemented function atom identifier type '" + type->to_str()
                + "'" );
            return nullptr;
    }
}

libcasm_ir::Value::Ptr AstToCasmIRPass::constant(
    const value_t& value, const Type& type, libcasm_ir::Type& hint )
{
    switch( value.type )
    {
        case TypeType::UNDEF:
        {
            switch( hint.id() )
            {
                case libcasm_ir::Type::BOOLEAN:
                {
                    return libstdhl::make< libcasm_ir::BooleanConstant >();
                }
                case libcasm_ir::Type::INTEGER:
                {
                    return libstdhl::make< libcasm_ir::IntegerConstant >();
                }
                case libcasm_ir::Type::BIT:
                {
                    return libstdhl::make< libcasm_ir::BitConstant >(
                        type.bitsize );
                }
                default:
                {
                    assert( !" unimplemented 'value_t' undef constant!" );
                    return nullptr;
                }
            }
        }
        case TypeType::BOOLEAN:
        {
            return libstdhl::make< libcasm_ir::BooleanConstant >(
                value.value.boolean );
        }
        case TypeType::INTEGER:
        {
            return libstdhl::make< libcasm_ir::IntegerConstant >(
                value.value.integer );
        }
        case TypeType::BIT:
        {
            return libstdhl::make< libcasm_ir::BitConstant >(
                type.bitsize, (uint64_t)value.value.integer );
        }
        default:
        {
            assert( 0 && "unimplemented 'value_t' constant!" );
            return 0;
        }
    }
}

value_t AstToCasmIRPass::value_t_value( const libcasm_ir::Value::Ptr& value )
{
    switch( value->id() )
    {
        case libcasm_ir::Value::BOOLEAN_CONSTANT:
        {
            auto c = static_cast< const libcasm_ir::BooleanConstant* >(
                value.get() );
            return c->defined() ? value_t( c->value() ) : value_t();
        }
        default:
        {
            assert( 0 && "unimplemented 'value' to create a 'value_t'!" );
            return value_t();
        }
    }
}

void AstToCasmIRPass::usage( libpass::PassUsage& pu )
{
    pu.require< TypeCheckPass >();
    pu.provide< libcasm_ir::ConsistencyCheckPass >();
}

bool AstToCasmIRPass::run( libpass::PassResult& pr )
{
    m_specification = nullptr;

    initially_scope = 0;
    initially_update_scope = 0;
    is_initially = false;

    auto node = pr.result< TypeCheckPass >();

    AstWalker< AstToCasmIRPass, bool > walker( *this );
    walker.walk_specification( node->root() );

    auto data = libstdhl::make< Data >( m_specification );

    pr.setResult< AstToCasmIRPass >( data );
    pr.setResult< libcasm_ir::ConsistencyCheckPass >( data );

    return true;
}

libcasm_ir::Specification::Ptr AstToCasmIRPass::getSpecification( void ) const
{
    return m_specification;
}

#if 1
#define VISIT
#else
#define VISIT                                                                  \
    printf( "===--- %s:%i: %s: %p: %s\n", __FILE__, __LINE__, __FUNCTION__,    \
        node, node->to_str().c_str() )
#endif

#define FIXME                                                                  \
    printf( "+++ FIXME +++: '%s:%i' in '%s'\n", __FILE__, __LINE__,            \
        __FUNCTION__ );                                                        \
    fflush( stdout );                                                          \
    assert( 0 );

void AstToCasmIRPass::visit_root( Ast* node )
{
    VISIT;

    assert( not m_specification );

    assert( not is_initially );
    assert( not initially_scope );
    assert( not initially_update_scope );
}

void AstToCasmIRPass::visit_specification( SpecificationNode* node )
{
    VISIT;
    m_specification
        = libstdhl::make< libcasm_ir::Specification >( node->identifier );

    auto ir_initially_rule = libstdhl::make< libcasm_ir::Rule >(
        ".initially", libstdhl::get< libcasm_ir::VoidType >() );

    getSpecification()->add( ir_initially_rule );

    auto ir_initially_rule_scope = libcasm_ir::ParallelBlock::create();

    ir_initially_rule->setContext( ir_initially_rule_scope );

    auto ir_initially_rule_inner_scope = libcasm_ir::SequentialBlock::create();

    ir_initially_rule_scope->add( ir_initially_rule_inner_scope );

    initially_scope = ir_initially_rule_inner_scope;

    // single execution agent!
    auto ir_agent_init_rule
        = libstdhl::get< libcasm_ir::RuleReferenceConstant >(
            ir_initially_rule );

    std::vector< std::string > agents = { single_execution_agent };

    m_agent = libstdhl::make< libcasm_ir::Agent >( agents );

    getSpecification()->setAgent( m_agent );
}

void AstToCasmIRPass::visit_init( InitNode* node )
{
    VISIT;
}

void AstToCasmIRPass::visit_body_elements_pre( AstListNode* node )
{
    VISIT;
}

void AstToCasmIRPass::visit_body_elements_post( AstListNode* node )
{
    VISIT;
}

void AstToCasmIRPass::visit_function_def_pre( FunctionDefNode* node, bool )
{
    VISIT;

    is_initially = true;

    if( node->initializers().size() > 0 )
    {
        initially_update_scope = libcasm_ir::ParallelBlock::create();

        assert( initially_scope );
        initially_scope->add( initially_update_scope );
    }

    std::vector< libcasm_ir::Type::Ptr > ftype_args;
    for( auto argument : node->sym->arguments_ )
    {
        ftype_args.push_back( getType( argument ) );
    }

    auto ftype = libstdhl::get< libcasm_ir::RelationType >(
        getType( node->sym->return_type_ ), ftype_args );

    auto ir_function = libstdhl::make< libcasm_ir::Function >(
        node->sym->name.c_str(), ftype );

    getSpecification()->add( ir_function );

    ast2casmir[ (AstNode*)node->sym ] = ir_function;
}

void AstToCasmIRPass::visit_function_def_post( FunctionDefNode* node )
{
    VISIT;

    is_initially = false;
    initially_update_scope = 0;
}

void AstToCasmIRPass::visit_derived_def_pre( DerivedDefNode* node )
{
    VISIT;

    std::vector< libcasm_ir::Type::Ptr > ftype_args;
    for( auto argument : node->sym->arguments_ )
    {
        ftype_args.push_back( getType( argument ) );
    }

    auto ftype = libstdhl::get< libcasm_ir::RelationType >(
        getType( node->sym->return_type_ ), ftype_args );

    auto ir_derived = libstdhl::make< libcasm_ir::Derived >(
        node->sym->name.c_str(), ftype );

    current_scope.push_back( ir_derived );
}

void AstToCasmIRPass::visit_derived_def( DerivedDefNode* node, bool expr )
{
    VISIT;
    std::string x;
    for( auto& a : node->sym->arguments_ )
    {
        x.append( a->to_str() );
    }

    assert( node->sym->type == Symbol::SymbolType::DERIVED );

    auto ir_stmt = libstdhl::make< libcasm_ir::TrivialStatement >();

    auto ir_expr = lookup< libcasm_ir::Instruction >( node->sym->derived );
    ir_stmt->add( ir_expr );

    assert( libcasm_ir::isa< libcasm_ir::Derived >( current_scope.back() )
            and "invalid scope!" );

    auto ir_derived = std::static_pointer_cast< libcasm_ir::Derived >(
        current_scope.back() );

    ir_derived->setContext( ir_stmt );

    // for( auto param : ir_derived->parameters() ) // PPA: FIXME:
    // {
    //     libcasm_ir::Identifier::forgetSymbol( param->name() );
    // }

    current_scope.pop_back();

    getSpecification()->add( ir_derived );

    ast2casmir[ (AstNode*)node->sym ] = ir_derived;
}

void AstToCasmIRPass::visit_skip( AstNode* node )
{
    VISIT;

    auto ir_scope = lookupParent< libcasm_ir::ExecutionSemanticsBlock >( node );
    assert( ir_scope );

    auto ir_stmt = libstdhl::make< libcasm_ir::TrivialStatement >();
    assert( ir_stmt );
    ir_scope->add( ir_stmt );

    ast2casmir[ node ] = ir_stmt;

    auto ir_skip = libstdhl::make< libcasm_ir::SkipInstruction >();
    assert( ir_skip );

    ir_stmt->add( ir_skip );
}

void AstToCasmIRPass::visit_rule( RuleNode* node )
{
    VISIT;
    assert( node );

    if( lookup< libcasm_ir::Rule >( node ) )
    {
        return;
    }

    auto ir_rule = libstdhl::make< libcasm_ir::Rule >(
        node->name.c_str(), libstdhl::get< libcasm_ir::VoidType >() );

    ast2casmir[ node ] = ir_rule;
    ast2parent[ node->child_ ] = node;

    if( node->child_->node_type_ != NodeType::PARBLOCK )
    {
        auto ir_scope = libcasm_ir::ParallelBlock::create();

        ast2casmir[ node ] = ir_scope;

        ir_rule->setContext( ir_scope );
    }

    for( i32 i = 0; i < node->arguments.size(); i++ )
    {
        // ir_rule->addParameter( libcasm_ir::Identifier::create(  // PPA:
        // FIXME:
        //     getType( node->arguments[ i ] ), node->parameter[ i ] ) );
    }

    current_scope.push_back( ir_rule );
}

void AstToCasmIRPass::visit_rule_post( RuleNode* node )
{
    VISIT;

    assert( libcasm_ir::isa< libcasm_ir::Rule >( current_scope.back() )
            and "invalid scope!" );

    auto ir_rule
        = std::static_pointer_cast< libcasm_ir::Rule >( current_scope.back() );

    getSpecification()->add( ir_rule );

    // for( auto param : ir_rule->parameters() ) // PPA: FIXME:
    // {
    //     libcasm_ir::Identifier::forgetSymbol( param->name() );
    // }

    current_scope.pop_back();
}

void AstToCasmIRPass::visit_parblock_pre( UnaryNode* node )
{
    VISIT;
    assert( node );

    auto ir_scope = libcasm_ir::ParallelBlock::create();

    ast2casmir[ node ] = ir_scope;
    ast2parent[ node->child_ ] = node;

    auto parent = lookupParent< libcasm_ir::Value >( node );
    assert( parent );

    if( libcasm_ir::isa< libcasm_ir::Rule >( parent ) )
    {
        auto ir_rule = std::static_pointer_cast< libcasm_ir::Rule >( parent );

        ir_rule->setContext( ir_scope );
    }
    else if( libcasm_ir::isa< libcasm_ir::ExecutionSemanticsBlock >( parent ) )
    {
        auto ir_esb
            = std::static_pointer_cast< libcasm_ir::ExecutionSemanticsBlock >(
                parent );
        ir_esb->add( ir_scope );
    }
    else if( libcasm_ir::isa< libcasm_ir::Statement >( parent ) )
    {
        auto ir_stmt
            = std::static_pointer_cast< libcasm_ir::Statement >( parent );
        ir_stmt->scope()->add( ir_scope );
    }
    else
    {
        assert( 0 );
    }
}

void AstToCasmIRPass::visit_parblock_post( UnaryNode* node )
{
}

void AstToCasmIRPass::visit_seqblock_pre( UnaryNode* node )
{
    VISIT;
    assert( node );

    auto ir_scope = libcasm_ir::SequentialBlock::create();

    ast2casmir[ node ] = ir_scope;
    ast2parent[ node->child_ ] = node;

    auto parent = lookupParent< libcasm_ir::Value >( node );

    if( libcasm_ir::isa< libcasm_ir::ExecutionSemanticsBlock >( parent ) )
    {
        auto ir_esb
            = std::static_pointer_cast< libcasm_ir::ExecutionSemanticsBlock >(
                parent );
        ir_esb->add( ir_scope );
    }
    else if( libcasm_ir::isa< libcasm_ir::Statement >( parent ) )
    {
        auto ir_stmt
            = std::static_pointer_cast< libcasm_ir::Statement >( parent );
        ir_stmt->scope()->add( ir_scope );
    }
    else
    {
        assert( 0 );
    }
}

void AstToCasmIRPass::visit_seqblock_post( UnaryNode* node )
{
}

void AstToCasmIRPass::visit_statements( AstListNode* node )
{
    VISIT;
    assert( node );

    auto parent = ast2parent.find( node );
    assert( parent != ast2parent.end() );

    for( AstNode* s : node->nodes )
    {
        ast2parent[ s ] = parent->second;
    }
}

void AstToCasmIRPass::visit_forall_pre( ForallNode* node )
{
    VISIT;
    FIXME;
}

void AstToCasmIRPass::visit_forall_post( ForallNode* node )
{
    VISIT;
    FIXME;
}

void AstToCasmIRPass::visit_iterate( UnaryNode* node )
{
    VISIT;
    FIXME;
}

void AstToCasmIRPass::visit_update(
    UpdateNode* node, std::vector< bool >& args, bool expr )
{
    VISIT;
    assert( node->func );

    auto ir_ident = lookup< libcasm_ir::Value >( (AstNode*)node->func->symbol );

    auto ir_loc = libstdhl::make< libcasm_ir::LocationInstruction >( ir_ident );

    if( node->func->arguments )
    {
        for( auto a : *( node->func->arguments ) )
        {
            auto instr = lookup< libcasm_ir::Value >( a );
            ir_loc->add( instr );
        }
    }

    libcasm_ir::ExecutionSemanticsBlock::Ptr ir_scope = 0;

    if( is_initially )
    {
        ir_scope = initially_update_scope;
    }
    else
    {
        ir_scope = lookupParent< libcasm_ir::ExecutionSemanticsBlock >( node );
    }

    assert( ir_scope );

    auto ir_stmt = libstdhl::make< libcasm_ir::TrivialStatement >();
    ir_scope->add( ir_stmt );

    ast2casmir[ node ] = ir_stmt;
    ast2parent[ node->func ] = node;
    ast2parent[ node->expr_ ] = node;

    auto ir_rhs = lookup< libcasm_ir::Value >( node->expr_ );

    ir_stmt->add( ir_loc );
    ir_stmt->add(
        libstdhl::make< libcasm_ir::UpdateInstruction >( ir_loc, ir_rhs ) );
}

void AstToCasmIRPass::visit_call_pre( CallNode* node )
{
}

void AstToCasmIRPass::visit_call_pre( CallNode* node, bool expr )
{
}

void AstToCasmIRPass::visit_call( CallNode* node, std::vector< bool >& args )
{
    VISIT;

    printf( "FIXME: call: %s, %p, %p\n", node->rule_name.c_str(), node->rule,
        node->ruleref );
}

void AstToCasmIRPass::visit_call_post( CallNode* node )
{
}

void AstToCasmIRPass::visit_print( PrintNode* node, bool expr )
{
    VISIT;

    auto ir_scope = lookupParent< libcasm_ir::ExecutionSemanticsBlock >( node );

    auto ir_stmt = libstdhl::make< libcasm_ir::TrivialStatement >();
    ir_scope->add( ir_stmt );

    ast2casmir[ node ] = ir_stmt;

    assert( !" TODO! no print instr, use print builtin! " );
}

void AstToCasmIRPass::visit_diedie( DiedieNode* node, bool msg )
{
    VISIT;
    FIXME;
}

void AstToCasmIRPass::visit_impossible( AstNode* node )
{
    VISIT;
    FIXME;
}

void AstToCasmIRPass::visit_assert( UnaryNode* node, bool expr )
{
    VISIT;

    auto ir_scope = lookupParent< libcasm_ir::ExecutionSemanticsBlock >( node );

    auto ir_stmt = libstdhl::make< libcasm_ir::TrivialStatement >();
    ir_scope->add( ir_stmt );

    ast2casmir[ node ] = ir_stmt;

    auto ir_cond = lookup< libcasm_ir::Value >( node->child_ );
    assert( ir_cond );

    auto ir_instr = libstdhl::make< libcasm_ir::AssertInstruction >( ir_cond );
    ir_stmt->add( ir_instr );
}

void AstToCasmIRPass::visit_assure( UnaryNode* node, bool expr )
{
    VISIT;
    FIXME;
}

void AstToCasmIRPass::visit_let( LetNode* node, bool var )
{
    VISIT;

    ast2parent[ node->expr ] = node;
    ast2parent[ node->stmt ] = node;

    auto ir_expr = lookup< libcasm_ir::Value >( node->expr );

    auto ir_ident = libstdhl::make< libcasm_ir::Identifier >(
        node->identifier, getType( &node->type_ ) );

    auto ir_local
        = libstdhl::make< libcasm_ir::LocalInstruction >( ir_ident, ir_expr );

    libcasm_ir::ExecutionSemanticsBlock::Ptr ir_scope = 0;

    auto parent = lookupParent< libcasm_ir::Value >( node );

    if( libcasm_ir::isa< libcasm_ir::ExecutionSemanticsBlock >( parent ) )
    {
        ir_scope
            = std::static_pointer_cast< libcasm_ir::ExecutionSemanticsBlock >(
                parent );
    }
    else if( libcasm_ir::isa< libcasm_ir::Statement >( parent ) )
    {
        ir_scope
            = std::static_pointer_cast< libcasm_ir::ExecutionSemanticsBlock >(
                parent )
                  ->scope();
    }
    else
    {
        assert( 0 );
    }

    auto ir_block = libcasm_ir::SequentialBlock::create();
    ir_scope->add( ir_block );
    ir_block->setParent( ir_scope );

    auto ir_stmt = libstdhl::make< libcasm_ir::TrivialStatement >();
    ir_block->add( ir_stmt );

    ir_stmt->add( ir_local );
    ir_stmt->setParent( ir_block );

    ast2casmir[ node ] = ir_block;
}

void AstToCasmIRPass::visit_let_post( LetNode* node )
{
    VISIT;
}

void AstToCasmIRPass::visit_push( PushNode* node, bool expr, bool atom )
{
    VISIT;
    FIXME;
}

void AstToCasmIRPass::visit_pop( PopNode* node, bool atom )
{
    VISIT;
    FIXME;
}

void AstToCasmIRPass::visit_ifthenelse( IfThenElseNode* node, bool cond )
{
    VISIT;

    auto ir_scope = lookupParent< libcasm_ir::ExecutionSemanticsBlock >( node );
    assert( ir_scope );

    auto ir_stmt = libstdhl::make< libcasm_ir::BranchStatement >();
    ir_scope->add( ir_stmt );

    assert( node->condition_ );
    auto ir_cond = lookup< libcasm_ir::Value >( node->condition_ );

    assert( ( libcasm_ir::isa< libcasm_ir::Instruction >( ir_cond )
                and ir_cond->type().id() == libcasm_ir::Type::BOOLEAN )
            or libcasm_ir::isa< libcasm_ir::BooleanConstant >( ir_cond ) );

    auto ir_select = libstdhl::make< libcasm_ir::SelectInstruction >( ir_cond );

    assert( node->then_ );
    auto ir_case_true = libcasm_ir::ParallelBlock::create();

    ast2casmir[ node ] = ir_case_true;
    ast2parent[ node->then_ ] = node;

    ir_stmt->add( ir_case_true );

    const libcasm_ir::Constant::Ptr ir_true
        = libstdhl::get< libcasm_ir::BooleanConstant >( true );

    getSpecification()->add( ir_true );

    ir_select->add( ir_true );
    ir_select->add( ir_case_true );

    if( node->else_ )
    {
        auto ir_case_false = libcasm_ir::ParallelBlock::create();

        ast2casmir[ node->condition_ ] = ir_case_false;
        ast2parent[ node->condition_ ] = node;
        ast2parent[ node->else_ ] = node->condition_;

        ir_stmt->add( ir_case_false );

        const libcasm_ir::Constant::Ptr ir_false
            = libstdhl::get< libcasm_ir::BooleanConstant >( false );
        getSpecification()->add( ir_false );

        ir_select->add( ir_false );
        ir_select->add( ir_case_false );
    }

    ir_stmt->add( ir_select );
}

void AstToCasmIRPass::visit_case_pre( CaseNode* node, bool val )
{
    VISIT;

    for( auto& a : node->case_list )
    {
        auto ir_case = libcasm_ir::ParallelBlock::create();

        ast2casmir[ (AstNode*)&a ] = ir_case;
        ast2parent[ a.second ] = (AstNode*)&a;
    }
}

void AstToCasmIRPass::visit_case(
    CaseNode* node, bool val, const std::vector< bool >& case_labels )
{
    VISIT;

    auto ir_scope = lookupParent< libcasm_ir::ExecutionSemanticsBlock >( node );

    auto ir_stmt = libstdhl::make< libcasm_ir::BranchStatement >();
    ir_scope->add( ir_stmt );

    auto ir_expr = lookup< libcasm_ir::Value >( node->expr );

    assert( libcasm_ir::isa< libcasm_ir::Instruction >( ir_expr )
            or libcasm_ir::isa< libcasm_ir::Constant >( ir_expr )
            or libcasm_ir::isa< libcasm_ir::Identifier >( ir_expr ) );

    auto ir_select = libstdhl::make< libcasm_ir::SelectInstruction >( ir_expr );

    libcasm_ir::ExecutionSemanticsBlock::Ptr default_case = 0;

    for( auto& a : node->case_list )
    {
        auto ir_case
            = lookupParent< libcasm_ir::ExecutionSemanticsBlock >( a.second );
        assert( ir_case );

        if( !a.first )
        {
            default_case = ir_case;
            continue;
        }

        auto ir_label = lookup< libcasm_ir::Value >( a.first );
        assert( ir_label );

        ir_select->add( ir_label );
        ir_select->add( ir_case );

        ir_stmt->add( ir_case );
    }

    if( default_case )
    {
        ir_select->add( default_case );

        ir_stmt->add( default_case );
    }

    ir_stmt->add( ir_select );
}

bool AstToCasmIRPass::visit_expression(
    BinaryExpression* node, bool lhs, bool rhs )
{
    VISIT;

    auto ir_lhs = lookup< libcasm_ir::Value >( node->left_ );
    auto ir_rhs = lookup< libcasm_ir::Value >( node->right_ );

    using Opcode = libcasm_ir::Value::ID;

    // PPA: TODO: this section can be omitted if the IR directly uses the ID
    // value to create on the fly the Instruction instance

    libcasm_ir::Value::Ptr ir_expr = 0;

    switch( node->op )
    {
        case Opcode::ADD_INSTRUCTION:
            ir_expr = libstdhl::make< libcasm_ir::AddInstruction >(
                ir_lhs, ir_rhs );
            break;
        case Opcode::SUB_INSTRUCTION:
            ir_expr = libstdhl::make< libcasm_ir::SubInstruction >(
                ir_lhs, ir_rhs );
            break;
        case Opcode::MUL_INSTRUCTION:
            ir_expr = libstdhl::make< libcasm_ir::MulInstruction >(
                ir_lhs, ir_rhs );
            break;
        case Opcode::DIV_INSTRUCTION:
            ir_expr = libstdhl::make< libcasm_ir::DivInstruction >(
                ir_lhs, ir_rhs );
            break;
        case Opcode::MOD_INSTRUCTION:
            ir_expr = libstdhl::make< libcasm_ir::ModInstruction >(
                ir_lhs, ir_rhs );
            break;
        case Opcode::EQU_INSTRUCTION:
            ir_expr = libstdhl::make< libcasm_ir::EquInstruction >(
                ir_lhs, ir_rhs );
            break;
        case Opcode::NEQ_INSTRUCTION:
            ir_expr = libstdhl::make< libcasm_ir::NeqInstruction >(
                ir_lhs, ir_rhs );
            break;
        case Opcode::LTH_INSTRUCTION:
            ir_expr = libstdhl::make< libcasm_ir::LthInstruction >(
                ir_lhs, ir_rhs );
            break;
        case Opcode::LEQ_INSTRUCTION:
            ir_expr = libstdhl::make< libcasm_ir::LeqInstruction >(
                ir_lhs, ir_rhs );
            break;
        case Opcode::GTH_INSTRUCTION:
            ir_expr = libstdhl::make< libcasm_ir::GthInstruction >(
                ir_lhs, ir_rhs );
            break;
        case Opcode::GEQ_INSTRUCTION:
            ir_expr = libstdhl::make< libcasm_ir::GeqInstruction >(
                ir_lhs, ir_rhs );
            break;
        case Opcode::OR_INSTRUCTION:
            ir_expr
                = libstdhl::make< libcasm_ir::OrInstruction >( ir_lhs, ir_rhs );
            break;
        case Opcode::XOR_INSTRUCTION:
            ir_expr = libstdhl::make< libcasm_ir::XorInstruction >(
                ir_lhs, ir_rhs );
            break;
        case Opcode::AND_INSTRUCTION:
            ir_expr = libstdhl::make< libcasm_ir::AndInstruction >(
                ir_lhs, ir_rhs );
            break;
        default:
            assert( !"internal error" );
    }

    assert( ir_expr );
    ast2casmir[ node ] = ir_expr;
    return 0;
}

bool AstToCasmIRPass::visit_expression_single( UnaryExpression* node, bool val )
{
    VISIT;

    auto ir_lhs = lookup< libcasm_ir::Value >( node->expr_ );

    using Opcode = libcasm_ir::Value::ID;

    libcasm_ir::Value::Ptr ir_expr = 0;

    switch( node->op )
    {
        case Opcode::NOT_INSTRUCTION:
            ir_expr = libstdhl::make< libcasm_ir::NotInstruction >( ir_lhs );
            break;
        default:
            assert( !"internal error" );
    }

    assert( ir_expr );
    ast2casmir[ node ] = ir_expr;
    return 0;
}

bool AstToCasmIRPass::visit_function_atom(
    FunctionAtom* node, std::vector< bool >& args )
{
    VISIT;

    if( node->symbol_type == FunctionAtom::SymbolType::PARAMETER )
    {
        libcasm_ir::Value::Ptr scope = 0;
        if( current_scope.size() > 0 )
        {
            scope = current_scope.back();
        }

        auto ir_ident = libstdhl::make< libcasm_ir::Identifier >(
            node->name.c_str(), getType( &node->type_ ) );

        assert( ir_ident );
        ast2casmir[ node ] = ir_ident;
        return 0;
    }

    auto ir_ident = lookup< libcasm_ir::Value >( (AstNode*)node->symbol );

    auto ir_loc = libstdhl::make< libcasm_ir::LocationInstruction >( ir_ident );

    if( node->arguments )
    {
        for( auto a : *( node->arguments ) )
        {
            auto instr = lookup< libcasm_ir::Value >( a );
            ir_loc->add( instr );
        }
    }

    auto ir_lup = libstdhl::make< libcasm_ir::LookupInstruction >( ir_loc );
    ast2casmir[ node ] = ir_lup;

    return 0;
}

void AstToCasmIRPass::visit_derived_function_atom_pre(
    FunctionAtom* node, std::vector< bool >& args )
{
    VISIT;
}

bool AstToCasmIRPass::visit_derived_function_atom(
    FunctionAtom* node, bool expr )
{
    VISIT;
    std::string x;

    assert( node->symbol );
    assert( node->symbol_type == FunctionAtom::SymbolType::DERIVED );

    auto ir_derived = lookup< libcasm_ir::Value >( (AstNode*)node->symbol );

    auto ir_call = libstdhl::make< libcasm_ir::CallInstruction >( ir_derived );

    ast2casmir[ node ] = ir_call;
    if( node->arguments )
    {
        for( auto a : *( node->arguments ) )
        {
            auto arg = lookup< libcasm_ir::Value >( a );
            ir_call->add( arg );
        }
    }

    return 0;
}

bool AstToCasmIRPass::visit_undef_atom( UndefAtom* node )
{
    VISIT;
    libcasm_ir::Constant::Ptr ir_const = 0;

    switch( node->type_.t )
    {
        case TypeType::RULEREF:
        {
            ir_const = libstdhl::get< libcasm_ir::RuleReferenceConstant >();
            break;
        }
        case TypeType::BOOLEAN:
        {
            ir_const = libstdhl::get< libcasm_ir::BooleanConstant >();
            break;
        }
        case TypeType::BIT:
        {
            ir_const = libstdhl::get< libcasm_ir::BitConstant >(
                node->type_.bitsize );
            break;
        }
        case TypeType::INTEGER:
        {
            ir_const = libstdhl::get< libcasm_ir::IntegerConstant >();
            break;
        }
        case TypeType::STRING:
        {
            ir_const = libstdhl::get< libcasm_ir::StringConstant >();
            break;
        }
        default:
            assert( 0 && "unimplemented undef constant!" );
    }

    assert( ir_const );
    ast2casmir[ node ] = ir_const;

    getSpecification()->add( ir_const );
    return 0;
}

bool AstToCasmIRPass::visit_boolean_atom( BooleanAtom* node )
{
    VISIT;
    const libcasm_ir::Constant::Ptr ir_const
        = libstdhl::get< libcasm_ir::BooleanConstant >( node->value );

    assert( ir_const );
    ast2casmir[ node ] = ir_const;

    getSpecification()->add( ir_const );
    return 0;
}

bool AstToCasmIRPass::visit_int_atom( IntegerAtom* node )
{
    VISIT;
    const libcasm_ir::Constant::Ptr ir_const
        = libstdhl::get< libcasm_ir::IntegerConstant >( node->val_ );

    assert( ir_const );
    ast2casmir[ node ] = ir_const;

    getSpecification()->add( ir_const );
    return 0;
}

bool AstToCasmIRPass::visit_bit_atom( IntegerAtom* node )
{
    VISIT;
    const libcasm_ir::Constant::Ptr ir_const
        = libstdhl::get< libcasm_ir::BitConstant >(
            node->type_.bitsize, (u64)node->val_ );

    assert( ir_const );
    ast2casmir[ node ] = ir_const;

    getSpecification()->add( ir_const );
    return 0;
}

bool AstToCasmIRPass::visit_floating_atom( FloatingAtom* node )
{
    VISIT;
    FIXME;
    return 0;
}

bool AstToCasmIRPass::visit_rational_atom( RationalAtom* node )
{
    VISIT;
    FIXME;
    return 0;
}

bool AstToCasmIRPass::visit_string_atom( StringAtom* node )
{
    VISIT;
    const libcasm_ir::Constant::Ptr ir_const
        = libstdhl::get< libcasm_ir::StringConstant >( node->string );

    assert( ir_const );
    ast2casmir[ node ] = ir_const;

    getSpecification()->add( ir_const );
    return 0;
}

bool AstToCasmIRPass::visit_self_atom( SelfAtom* node )
{
    VISIT;
    const auto type
        = static_cast< const libcasm_ir::EnumerationType& >( m_agent->type() );

    const libcasm_ir::Constant::Ptr ir_const
        = libstdhl::get< libcasm_ir::EnumerationConstant >(
            type.ptr_kind(), single_execution_agent );

    assert( ir_const );
    ast2casmir[ node ] = ir_const;

    getSpecification()->add( ir_const );
    return 0;
}

bool AstToCasmIRPass::visit_rule_atom( RuleAtom* node )
{
    VISIT;
    auto rule = lookup< libcasm_ir::Rule >( node->rule );
    if( not rule )
    {
        visit_rule( node->rule );
        rule = lookup< libcasm_ir::Rule >( node->rule );
    }

    const libcasm_ir::Constant::Ptr ir_const
        = libstdhl::get< libcasm_ir::RuleReferenceConstant >( rule );

    assert( ir_const );
    ast2casmir[ node ] = ir_const;

    getSpecification()->add( ir_const );
    return 0;
}

bool AstToCasmIRPass::visit_list_atom(
    ListAtom* node, const std::vector< bool >& args )
{
    VISIT;
    FIXME;
    return 0;
}

bool AstToCasmIRPass::visit_number_range_atom(
    NumberRangeAtom* node, bool start, bool end )
{
    VISIT;
    FIXME;
    return 0;
}

bool AstToCasmIRPass::visit_builtin_atom(
    BuiltinAtom* node, std::vector< bool >& args )
{
    VISIT;

    std::vector< libcasm_ir::Type::Ptr > ty_ident_args;
    if( node->arguments )
    {
        for( auto a : *( node->arguments ) )
        {
            ty_ident_args.push_back( getType( &( a->type_ ) ) );
        }
    }

    auto ty_ident = libstdhl::make< libcasm_ir::RelationType >(
        getType( node->return_type ), ty_ident_args );

    auto ir_ident
        = libcasm_ir::Builtin::find( node->to_str().c_str(), ty_ident );

    getSpecification()->add( ir_ident );

    auto ir_call = libstdhl::make< libcasm_ir::CallInstruction >( ir_ident );

    ast2casmir[ node ] = ir_call;

    if( node->arguments )
    {
        for( auto a : *( node->arguments ) )
        {
            auto arg = lookup< libcasm_ir::Value >( a );
            ir_call->add( arg );
        }
    }

    return 0;
}

void AstToCasmIRPass::visit_statement( AstNode* node )
{
    VISIT;
}

void AstToCasmIRPass::visit_forall_iteration_pre( ForallNode* node, bool )
{
    VISIT;
}

void AstToCasmIRPass::visit_forall_iteration_post( ForallNode* node )
{
    VISIT;
}

bool AstToCasmIRPass::visit_zero_atom( ZeroAtom* node )
{
    VISIT;
    return false;
}

template < class C >
typename C::Ptr AstToCasmIRPass::lookupParent( AstNode* node )
{
    auto result = ast2parent.find( node );
    if( result != ast2parent.end() )
    {
        return lookup< C >( result->second );
    }

    return 0;
}

template < typename C >
typename C::Ptr AstToCasmIRPass::lookup( AstNode* node )
{
    auto result = ast2casmir.find( node );
    if( result != ast2casmir.end() )
    {
        if( libcasm_ir::isa< C >( result->second ) )
        {
            return std::static_pointer_cast< C >( result->second );
        }
        else
        {
            assert( 0 );
        }
    }

    return 0;
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
