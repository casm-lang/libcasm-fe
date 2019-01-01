//
//  Copyright (C) 2014-2019 CASM Organization <https://casm-lang.org>
//  All rights reserved.
//
//  Developed by: Philipp Paulweber
//                Emmanuel Pescosta
//                Florian Hahn
//                <https://github.com/casm-lang/libcasm-fe>
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
//  Additional permission under GNU GPL version 3 section 7
//
//  libcasm-fe is distributed under the terms of the GNU General Public License
//  with the following clarification and special exception: Linking libcasm-fe
//  statically or dynamically with other modules is making a combined work
//  based on libcasm-fe. Thus, the terms and conditions of the GNU General
//  Public License cover the whole combination. As a special exception,
//  the copyright holders of libcasm-fe give you permission to link libcasm-fe
//  with independent modules to produce an executable, regardless of the
//  license terms of these independent modules, and to copy and distribute
//  the resulting executable under terms of your choice, provided that you
//  also meet, for each linked independent module, the terms and conditions
//  of the license of that module. An independent module is a module which
//  is not derived from or based on libcasm-fe. If you modify libcasm-fe, you
//  may extend this exception to your version of the library, but you are
//  not obliged to do so. If you do not wish to do so, delete this exception
//  statement from your version.
//

#include "AstToCasmIRPass.h"

#include <libcasm-fe/Logger>
#include <libcasm-fe/Namespace>
#include <libcasm-fe/Specification>
#include <libcasm-fe/ast/RecursiveVisitor>

#include <libcasm-fe/analyze/ConsistencyCheckPass>
#include <libcasm-fe/transform/SourceToAstPass>

#include <libcasm-ir/Specification>
#include <libcasm-ir/analyze/ConsistencyCheckPass>

#include <libpass/PassRegistry>
#include <libpass/PassResult>
#include <libpass/PassUsage>

using namespace libcasm_fe;
using namespace Ast;

char AstToCasmIRPass::id = 0;

static libpass::PassRegistration< AstToCasmIRPass > PASS(
    "AstToIRPass", "translates the AST to the Intermediate Representation", "ast2ir", 0 );

class AstToCasmIRVisitor final : public RecursiveVisitor
{
  public:
    AstToCasmIRVisitor( libcasm_fe::Logger& log );

    void visit( Specification& node );

    void visit( VariableDefinition& node ) override;
    void visit( FunctionDefinition& node ) override;
    void visit( DerivedDefinition& node ) override;
    void visit( RuleDefinition& node ) override;
    void visit( EnumeratorDefinition& node ) override;
    void visit( EnumerationDefinition& node ) override;
    void visit( InvariantDefinition& node ) override;

    void visit( UndefLiteral& node ) override;
    void visit( ValueLiteral& node ) override;
    void visit( ReferenceLiteral& node ) override;
    void visit( ListLiteral& node ) override;
    void visit( RangeLiteral& node ) override;

    void visit( DirectCallExpression& node ) override;
    void visit( MethodCallExpression& node ) override;
    void visit( IndirectCallExpression& node ) override;
    void visit( UnaryExpression& node ) override;
    void visit( BinaryExpression& node ) override;
    void visit( LetExpression& node ) override;
    void visit( ConditionalExpression& node ) override;
    void visit( ChooseExpression& node ) override;
    void visit( UniversalQuantifierExpression& node ) override;
    void visit( ExistentialQuantifierExpression& node ) override;

    void visit( SkipRule& node ) override;
    void visit( ConditionalRule& node ) override;
    void visit( CaseRule& node ) override;
    void visit( LetRule& node ) override;
    void visit( ForallRule& node ) override;
    void visit( ChooseRule& node ) override;
    void visit( IterateRule& node ) override;
    void visit( BlockRule& node ) override;
    void visit( SequenceRule& node ) override;
    void visit( UpdateRule& node ) override;
    void visit( CallRule& node ) override;
    void visit( WhileRule& node ) override;

    void visit( UnresolvedType& node ) override;
    void visit( BasicType& node ) override;
    void visit( TupleType& node ) override;
    void visit( RecordType& node ) override;
    void visit( TemplateType& node ) override;
    void visit( FixedSizedType& node ) override;
    void visit( RelationType& node ) override;

    void visit( BasicAttribute& node ) override;
    void visit( ExpressionAttribute& node ) override;

    void visit( Identifier& node ) override;
    void visit( IdentifierPath& node ) override;
    void visit( ExpressionCase& node ) override;
    void visit( DefaultCase& node ) override;

    libcasm_ir::Specification::Ptr specification( void ) const;

  private:
    libcasm_fe::Logger& m_log;

    libcasm_ir::Specification::Ptr m_specification;
    u1 m_declaration;
    u1 m_init_flag;
    libcasm_ir::SequentialBlock::Ptr m_init_block;
    libcasm_ir::Statement::Ptr m_statement;
    u1 m_update_flag;
    std::vector< libcasm_ir::ExecutionSemanticsBlock::Ptr > m_blocks;
    std::unordered_map< RuleDefinition*, libcasm_ir::Rule::Ptr > m_def2rule;
    std::unordered_map< FunctionDefinition*, libcasm_ir::Function::Ptr > m_def2func;
    std::unordered_map< Node*, libcasm_ir::Value::Ptr > m_ast2ir;
};

AstToCasmIRVisitor::AstToCasmIRVisitor( libcasm_fe::Logger& log )
: m_log( log )
, m_specification( nullptr )
, m_declaration( false )
, m_init_flag( false )
, m_init_block( nullptr )
, m_statement( nullptr )
, m_update_flag( false )
, m_blocks()
, m_def2rule()
, m_def2func()
, m_ast2ir()
{
}

static const auto VOID = libstdhl::Memory::get< libcasm_ir::VoidType >();

void AstToCasmIRVisitor::visit( Specification& node )
{
    m_specification = libstdhl::Memory::make< libcasm_ir::Specification >( node.name() );

    const auto rule_init_type = libstdhl::Memory::make< libcasm_ir::RelationType >( VOID );
    auto rule_init = libstdhl::Memory::make< libcasm_ir::Rule >( ".init", rule_init_type );
    m_specification->add( rule_init );

    auto rule_init_block = libcasm_ir::ParallelBlock::create();
    rule_init->setContext( rule_init_block );
    auto rule_init_inner_block = libcasm_ir::SequentialBlock::create();
    rule_init_block->add( rule_init_inner_block );
    m_init_block = rule_init_inner_block;

    node.header()->accept( *this );

    // declaration phase
    m_declaration = true;
    node.definitions()->accept( *this );
    m_declaration = false;

    // definition phase
    node.definitions()->accept( *this );
}

void AstToCasmIRVisitor::visit( VariableDefinition& node )
{
    m_log.info( "%s:%i: TODO %s", __FILE__, __LINE__, node.description().c_str() );
}

void AstToCasmIRVisitor::visit( FunctionDefinition& node )
{
    const auto& name = node.identifier()->name();
    const auto& type = node.type();

    if( m_declaration )
    {
        if( name.compare( "program" ) == 0 )
        {
            m_specification->set< libcasm_ir::Agent >( node.type()->arguments().front() );
        }

        auto func = libstdhl::Memory::make< libcasm_ir::Function >( name, type );

        auto result = m_def2func.emplace( &node, func );
        assert( result.second and " multiple declaration " );

        m_specification->add( func );

        m_log.debug(
            { node.sourceLocation() }, "declared " + node.description() + " '" + name + "'" );
    }
    else
    {
        auto result = m_def2func.find( &node );
        assert( result != m_def2func.end() and " undeclared function found " );

        auto& func = result->second;
        assert( func->type() == *node.type() and " inconsistent declared function found " );

        // node.defaultValue()->accept( *this ); // TODO
        // node.attributes()->accept( *this ); // TODO

        m_init_flag = true;
        node.initializers()->accept( *this );
        m_init_flag = false;
    }
}

void AstToCasmIRVisitor::visit( DerivedDefinition& node )
{
    m_log.info( "%s:%i: TODO %s", __FILE__, __LINE__, node.description().c_str() );
}

void AstToCasmIRVisitor::visit( RuleDefinition& node )
{
    const auto& name = node.identifier()->name();
    const auto& type = node.type();

    if( m_declaration )
    {
        auto rule = libstdhl::Memory::make< libcasm_ir::Rule >( name, type );

        auto result = m_def2rule.emplace( &node, rule );
        assert( result.second and " multiple declaration " );

        m_specification->add( rule );

        m_log.debug(
            { node.sourceLocation() }, "declared " + node.description() + " '" + name + "'" );
    }
    else
    {
        auto result = m_def2rule.find( &node );
        assert( result != m_def2rule.end() and " undeclared rule found " );

        auto& rule = result->second;
        assert( rule->type() == *node.type() and " inconsistent declared rule found " );

        // node.arguments()->accept( *this ); // TODO
        // node.attributes()->accept( *this ); // TODO

        auto rule_block = libcasm_ir::ParallelBlock::create();
        rule->setContext( rule_block );

        m_blocks.push_back( rule_block );

        node.rule()->accept( *this );

        assert( m_blocks.back().get() == rule_block.get() );
        m_blocks.pop_back();

        assert( m_blocks.size() == 0 );
    }
}

void AstToCasmIRVisitor::visit( EnumeratorDefinition& node )
{
    m_log.info( "%s:%i: TODO %s", __FILE__, __LINE__, node.description().c_str() );
}

void AstToCasmIRVisitor::visit( EnumerationDefinition& node )
{
    m_log.info( "%s:%i: TODO %s", __FILE__, __LINE__, node.description().c_str() );
}

void AstToCasmIRVisitor::visit( InvariantDefinition& node )
{
    m_log.info( "%s:%i: TODO %s", __FILE__, __LINE__, node.description().c_str() );
}

void AstToCasmIRVisitor::visit( UndefLiteral& node )
{
    assert( node.type() );

    const libcasm_ir::Constant::Ptr& constant = libstdhl::Memory::make< libcasm_ir::Constant >(
        libcasm_ir::Constant::undef( node.type() ) );

    auto result = m_ast2ir.emplace( &node, constant );
    assert( result.second and " reference already exists " );
    m_specification->add( constant );
}

void AstToCasmIRVisitor::visit( ValueLiteral& node )
{
    assert( node.type() );
    assert( node.value() );

    const libcasm_ir::Constant::Ptr& constant = node.value();

    auto result = m_ast2ir.emplace( &node, constant );
    assert( result.second and " reference already exists " );
    m_specification->add( constant );
}

void AstToCasmIRVisitor::visit( ReferenceLiteral& node )
{
    libcasm_ir::Constant::Ptr constant = nullptr;

    switch( node.referenceType() )
    {
        case ReferenceLiteral::ReferenceType::FUNCTION:
        {
            m_log.error( { node.sourceLocation() }, "TODO" );
            break;
        }
        case ReferenceLiteral::ReferenceType::DERIVED:
        {
            m_log.error( { node.sourceLocation() }, "TODO" );
            break;
        }
        case ReferenceLiteral::ReferenceType::BUILTIN:
        {
            m_log.error( { node.sourceLocation() }, "TODO" );
            break;
        }
        case ReferenceLiteral::ReferenceType::RULE:
        {
            assert( node.reference() );
            const auto def = static_cast< RuleDefinition* >( node.reference().get() );

            auto result = m_def2rule.find( def );
            assert( result != m_def2rule.end() and " non-registered rule found " );

            const auto& rule = result->second;
            assert( rule->type() == *def->type() and " inconsistent registered typed rule " );

            constant = libstdhl::Memory::make< libcasm_ir::RuleReferenceConstant >( rule );
            break;
        }
        case ReferenceLiteral::ReferenceType::UNKNOWN:
        {
            m_log.error( { node.sourceLocation() }, "TODO" );
            break;
        }
    }

    assert( constant and " unimplemented reference literal " );
    m_specification->add( constant );
    auto result = m_ast2ir.emplace( &node, constant );
    assert( result.second and " reference already exists " );
}

void AstToCasmIRVisitor::visit( ListLiteral& node )
{
    m_log.info( "%s:%i: TODO %s", __FILE__, __LINE__, node.description().c_str() );
}

void AstToCasmIRVisitor::visit( RangeLiteral& node )
{
    m_log.info( "%s:%i: TODO %s", __FILE__, __LINE__, node.description().c_str() );
}

void AstToCasmIRVisitor::visit( DirectCallExpression& node )
{
    assert( m_statement and " target statement not set " );
    assert( node.identifier() );
    const auto& identifier = node.identifier();
    const auto& identifierName = identifier->path();
    const auto& type = node.type();

    std::vector< libcasm_ir::Value::Ptr > args;
    for( auto argument : *node.arguments() )
    {
        const auto size = m_statement->instructions().size();
        argument->accept( *this );

        if( size == m_statement->instructions().size() )
        {
            // argument is a constant
            args.emplace_back( m_ast2ir.at( argument.get() ) );
        }
        else
        {
            // argument is a register/instruction
            args.emplace_back( m_statement->instructions().back() );
        }
    }

    switch( node.targetType() )
    {
        case DirectCallExpression::TargetType::FUNCTION:
        {
            const auto def = static_cast< FunctionDefinition* >( node.targetDefinition().get() );

            auto result = m_def2func.find( def );
            assert( result != m_def2func.end() );

            const auto& func = result->second;
            const auto loc = m_statement->add< libcasm_ir::LocationInstruction >( func, args );

            if( not m_update_flag )
            {
                m_statement->add< libcasm_ir::LookupInstruction >( loc );
            }
            break;
        }
        case DirectCallExpression::TargetType::DERIVED:
        {
            assert( not" unimplemented direct expr call " );
            break;
        }
        case DirectCallExpression::TargetType::BUILTIN:
        {
            const auto id = node.targetBuiltinId();
            const auto builtin = libcasm_ir::Builtin::create( id, type );
            m_statement->add< libcasm_ir::CallInstruction >( builtin, args );
            m_specification->add( builtin );
            break;
        }
        case DirectCallExpression::TargetType::RULE:
        {
            assert( not" unimplemented direct expr call " );
            break;
        }
        case DirectCallExpression::TargetType::TYPE_DOMAIN:
        {
            assert( not" unimplemented direct expr call " );
            break;
        }
        case DirectCallExpression::TargetType::CONSTANT:
        {
            assert( node.type()->isEnumeration() );

            const auto& type =
                std::static_pointer_cast< libcasm_ir::EnumerationType >( node.type() );

            m_specification->add( type );

            const libcasm_ir::Constant::Ptr constant =
                libstdhl::Memory::make< libcasm_ir::EnumerationConstant >( type, identifierName );

            m_specification->add( constant );
            m_ast2ir.emplace( &node, constant );
            break;
        }
        case DirectCallExpression::TargetType::VARIABLE:
        {
            assert( not" unimplemented direct expr call " );
            break;
        }
        case DirectCallExpression::TargetType::SELF:
        {
            const auto& type = std::static_pointer_cast< libcasm_ir::EnumerationType >(
                m_specification->agent()->type().ptr_type() );

            const libcasm_ir::Constant::Ptr constant =
                libstdhl::Memory::make< libcasm_ir::EnumerationConstant >( type, "$" );

            m_specification->add( constant );
            m_ast2ir.emplace( &node, constant );
            break;
        }
        case DirectCallExpression::TargetType::UNKNOWN:
        {
            assert( not" unimplemented direct expr call " );
            break;
        }
    }
}

void AstToCasmIRVisitor::visit( MethodCallExpression& node )
{
    m_log.info( "%s:%i: TODO %s", __FILE__, __LINE__, node.description().c_str() );
}

void AstToCasmIRVisitor::visit( IndirectCallExpression& node )
{
    m_log.info( "%s:%i: TODO %s", __FILE__, __LINE__, node.description().c_str() );
}

void AstToCasmIRVisitor::visit( UnaryExpression& node )
{
    m_log.info( "%s:%i: TODO %s", __FILE__, __LINE__, node.description().c_str() );
}

void AstToCasmIRVisitor::visit( BinaryExpression& node )
{
    m_log.info( "%s:%i: TODO %s", __FILE__, __LINE__, node.description().c_str() );
}

void AstToCasmIRVisitor::visit( LetExpression& node )
{
    m_log.info( "%s:%i: TODO %s", __FILE__, __LINE__, node.description().c_str() );
}

void AstToCasmIRVisitor::visit( ConditionalExpression& node )
{
    m_log.info( "%s:%i: TODO %s", __FILE__, __LINE__, node.description().c_str() );
}

void AstToCasmIRVisitor::visit( ChooseExpression& node )
{
    m_log.info( "%s:%i: TODO %s", __FILE__, __LINE__, node.description().c_str() );
}

void AstToCasmIRVisitor::visit( UniversalQuantifierExpression& node )
{
    m_log.info( "%s:%i: TODO %s", __FILE__, __LINE__, node.description().c_str() );
}

void AstToCasmIRVisitor::visit( ExistentialQuantifierExpression& node )
{
    m_log.info( "%s:%i: TODO %s", __FILE__, __LINE__, node.description().c_str() );
}

void AstToCasmIRVisitor::visit( SkipRule& node )
{
    assert( m_blocks.size() > 0 );
    auto& block = m_blocks.back();

    auto stmt = libstdhl::Memory::make< libcasm_ir::TrivialStatement >();
    block->add( stmt );
    stmt->add< libcasm_ir::SkipInstruction >();
}

void AstToCasmIRVisitor::visit( ConditionalRule& node )
{
    m_log.info( "%s:%i: TODO %s", __FILE__, __LINE__, node.description().c_str() );
}

void AstToCasmIRVisitor::visit( CaseRule& node )
{
    m_log.info( "%s:%i: TODO %s", __FILE__, __LINE__, node.description().c_str() );
}

void AstToCasmIRVisitor::visit( LetRule& node )
{
    m_log.info( "%s:%i: TODO %s", __FILE__, __LINE__, node.description().c_str() );
}

void AstToCasmIRVisitor::visit( ForallRule& node )
{
    m_log.info( "%s:%i: TODO %s", __FILE__, __LINE__, node.description().c_str() );
}

void AstToCasmIRVisitor::visit( ChooseRule& node )
{
    m_log.info( "%s:%i: TODO %s", __FILE__, __LINE__, node.description().c_str() );
}

void AstToCasmIRVisitor::visit( IterateRule& node )
{
    m_log.info( "%s:%i: TODO %s", __FILE__, __LINE__, node.description().c_str() );
}

void AstToCasmIRVisitor::visit( BlockRule& node )
{
    assert( m_blocks.size() > 0 );
    auto& parent = m_blocks.back();

    if( parent->parallel() )
    {
        m_log.debug( "omitting redundant parallel block" );

        node.rules()->accept( *this );
    }
    else
    {
        auto block = libcasm_ir::ParallelBlock::create();
        parent->add( block );
        m_blocks.push_back( block );

        node.rules()->accept( *this );

        assert( m_blocks.back().get() == block.get() );
        m_blocks.pop_back();
    }
}

void AstToCasmIRVisitor::visit( SequenceRule& node )
{
    assert( m_blocks.size() > 0 );
    auto& parent = m_blocks.back();

    if( not parent->parallel() )
    {
        m_log.debug( "omitting redundant sequential block" );

        node.rules()->accept( *this );
    }
    else
    {
        auto block = libcasm_ir::SequentialBlock::create();
        parent->add( block );
        m_blocks.push_back( block );

        node.rules()->accept( *this );

        assert( m_blocks.back().get() == block.get() );
        m_blocks.pop_back();
    }
}

void AstToCasmIRVisitor::visit( UpdateRule& node )
{
    libcasm_ir::ExecutionSemanticsBlock::Ptr block = nullptr;
    if( m_init_flag )
    {
        block = m_init_block;
    }
    else
    {
        block = m_blocks.back();
    }
    assert( block and " unable to determine the surrounding block for this update " );

    auto stmt = libstdhl::Memory::make< libcasm_ir::TrivialStatement >();
    block->add( stmt );

    m_statement = stmt;

    node.expression()->accept( *this );
    const auto& value =
        ( stmt->instructions().size() == 0 ? m_ast2ir.at( node.expression().get() )
                                           : stmt->instructions().back() );

    m_update_flag = true;
    node.function()->accept( *this );
    m_update_flag = false;

    const auto& location = stmt->instructions().back();
    stmt->add< libcasm_ir::UpdateInstruction >( location, value );

    m_statement = nullptr;
}

void AstToCasmIRVisitor::visit( CallRule& node )
{
    assert( m_blocks.size() > 0 );
    auto& block = m_blocks.back();

    auto stmt = libstdhl::Memory::make< libcasm_ir::TrivialStatement >();
    block->add( stmt );
    m_statement = stmt;

    node.call()->accept( *this );

    m_statement = nullptr;
}

void AstToCasmIRVisitor::visit( WhileRule& node )
{
    m_log.info( "%s:%i: TODO %s", __FILE__, __LINE__, node.description().c_str() );
}

void AstToCasmIRVisitor::visit( UnresolvedType& node )
{
    m_log.info( "%s:%i: TODO %s", __FILE__, __LINE__, node.description().c_str() );
}

void AstToCasmIRVisitor::visit( BasicType& node )
{
    m_log.info( "%s:%i: TODO %s", __FILE__, __LINE__, node.description().c_str() );
}

void AstToCasmIRVisitor::visit( TupleType& node )
{
    m_log.info( "%s:%i: TODO %s", __FILE__, __LINE__, node.description().c_str() );
}

void AstToCasmIRVisitor::visit( RecordType& node )
{
    m_log.info( "%s:%i: TODO %s", __FILE__, __LINE__, node.description().c_str() );
}

void AstToCasmIRVisitor::visit( TemplateType& node )
{
    m_log.info( "%s:%i: TODO %s", __FILE__, __LINE__, node.description().c_str() );
}

void AstToCasmIRVisitor::visit( FixedSizedType& node )
{
    m_log.info( "%s:%i: TODO %s", __FILE__, __LINE__, node.description().c_str() );
}

void AstToCasmIRVisitor::visit( RelationType& node )
{
    m_log.info( "%s:%i: TODO %s", __FILE__, __LINE__, node.description().c_str() );
}

void AstToCasmIRVisitor::visit( BasicAttribute& node )
{
    m_log.info( "%s:%i: TODO %s", __FILE__, __LINE__, node.description().c_str() );
}

void AstToCasmIRVisitor::visit( ExpressionAttribute& node )
{
    m_log.info( "%s:%i: TODO %s", __FILE__, __LINE__, node.description().c_str() );
}

void AstToCasmIRVisitor::visit( Identifier& node )
{
    m_log.info( "%s:%i: TODO %s", __FILE__, __LINE__, node.description().c_str() );
}

void AstToCasmIRVisitor::visit( IdentifierPath& node )
{
    m_log.info( "%s:%i: TODO %s", __FILE__, __LINE__, node.description().c_str() );
}

void AstToCasmIRVisitor::visit( ExpressionCase& node )
{
    m_log.info( "%s:%i: TODO %s", __FILE__, __LINE__, node.description().c_str() );
}

void AstToCasmIRVisitor::visit( DefaultCase& node )
{
    m_log.info( "%s:%i: TODO %s", __FILE__, __LINE__, node.description().c_str() );
}

libcasm_ir::Specification::Ptr AstToCasmIRVisitor::specification( void ) const
{
    return m_specification;
}

void AstToCasmIRPass::usage( libpass::PassUsage& pu )
{
    pu.require< SourceToAstPass >();
    pu.scheduleAfter< ConsistencyCheckPass >();

    pu.provide< libcasm_ir::ConsistencyCheckPass >();
}

bool AstToCasmIRPass::run( libpass::PassResult& pr )
{
    libcasm_fe::Logger log( &id, stream() );

    const auto& data = pr.output< SourceToAstPass >();
    const auto& specification = data->specification();

    AstToCasmIRVisitor visitor{ log };
    visitor.visit( *specification );

    if( not visitor.specification() )
    {
        log.error( "inconsistent AST to IR transformation" );
        return false;
    }

    pr.setInput< libcasm_ir::ConsistencyCheckPass >( visitor.specification() );
    return true;
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
