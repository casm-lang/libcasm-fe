//
//  Copyright (c) 2014-2017 CASM Organization
//  All rights reserved.
//
//  Developed by: Philipp Paulweber
//                Emmanuel Pescosta
//                Florian Hahn
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

#include "../ast/RecursiveVisitor.h"

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
using namespace Ast;

char AstToCasmIRPass::id = 0;

static libpass::PassRegistration< AstToCasmIRPass > PASS( "AstToIRPass",
    "translates the AST to the Intermediate Representation",
    "ast2ir",
    0 );

class AstToCasmIRVisitor final : public RecursiveVisitor
{
  public:
    AstToCasmIRVisitor( void );

    void visit( Specification& node ) override;

    void visit( VariableDefinition& node ) override;
    void visit( FunctionDefinition& node ) override;
    void visit( DerivedDefinition& node ) override;
    void visit( RuleDefinition& node ) override;
    void visit( EnumerationDefinition& node ) override;

    void visit( ValueAtom& node ) override;
    void visit( RuleReferenceAtom& node ) override;
    void visit( UndefAtom& node ) override;
    void visit( DirectCallExpression& node ) override;
    void visit( IndirectCallExpression& node ) override;
    void visit( UnaryExpression& node ) override;
    void visit( BinaryExpression& node ) override;
    void visit( RangeExpression& node ) override;
    void visit( ListExpression& node ) override;
    void visit( ConditionalExpression& node ) override;
    void visit( UniversalQuantifierExpression& node ) override;
    void visit( ExistentialQuantifierExpression& node ) override;

    void visit( SkipRule& node ) override;
    void visit( ConditionalRule& node ) override;
    void visit( CaseRule& node ) override;
    void visit( LetRule& node ) override;
    void visit( ForallRule& node ) override;
    void visit( IterateRule& node ) override;
    void visit( BlockRule& node ) override;
    void visit( SequenceRule& node ) override;
    void visit( UpdateRule& node ) override;
    void visit( CallRule& node ) override;

    void visit( UnresolvedType& node ) override;
    void visit( BasicType& node ) override;
    void visit( ComposedType& node ) override;
    void visit( FixedSizedType& node ) override;
    void visit( RangedType& node ) override;

    void visit( BasicAttribute& node ) override;
    void visit( ExpressionAttribute& node ) override;

    void visit( IdentifierNode& node ) override;
    void visit( ExpressionCase& node ) override;
    void visit( DefaultCase& node ) override;

    libcasm_ir::Specification::Ptr specification( void ) const;

  private:
    libcasm_ir::Specification::Ptr m_specification;
};

AstToCasmIRVisitor::AstToCasmIRVisitor( void )
{
}

void AstToCasmIRVisitor::visit( Specification& node )
{
    // TODO
    RecursiveVisitor::visit( node );
}

void AstToCasmIRVisitor::visit( VariableDefinition& node )
{
    // TODO
    RecursiveVisitor::visit( node );
}

void AstToCasmIRVisitor::visit( FunctionDefinition& node )
{
    // TODO
    RecursiveVisitor::visit( node );
}

void AstToCasmIRVisitor::visit( DerivedDefinition& node )
{
    // TODO
    RecursiveVisitor::visit( node );
}

void AstToCasmIRVisitor::visit( RuleDefinition& node )
{
    // TODO
    RecursiveVisitor::visit( node );
}

void AstToCasmIRVisitor::visit( EnumerationDefinition& node )
{
    // TODO
    RecursiveVisitor::visit( node );
}

void AstToCasmIRVisitor::visit( ValueAtom& node )
{
    // TODO
    RecursiveVisitor::visit( node );
}

void AstToCasmIRVisitor::visit( RuleReferenceAtom& node )
{
    // TODO
    RecursiveVisitor::visit( node );
}

void AstToCasmIRVisitor::visit( UndefAtom& node )
{
    // TODO
    RecursiveVisitor::visit( node );
}

void AstToCasmIRVisitor::visit( DirectCallExpression& node )
{
    // TODO
    RecursiveVisitor::visit( node );
}

void AstToCasmIRVisitor::visit( IndirectCallExpression& node )
{
    // TODO
    RecursiveVisitor::visit( node );
}

void AstToCasmIRVisitor::visit( UnaryExpression& node )
{
    // TODO
    RecursiveVisitor::visit( node );
}

void AstToCasmIRVisitor::visit( BinaryExpression& node )
{
    // TODO
    RecursiveVisitor::visit( node );
}

void AstToCasmIRVisitor::visit( RangeExpression& node )
{
    // TODO
    RecursiveVisitor::visit( node );
}

void AstToCasmIRVisitor::visit( ListExpression& node )
{
    // TODO
    RecursiveVisitor::visit( node );
}

void AstToCasmIRVisitor::visit( ConditionalExpression& node )
{
    // TODO
    RecursiveVisitor::visit( node );
}

void AstToCasmIRVisitor::visit( UniversalQuantifierExpression& node )
{
    // TODO
    RecursiveVisitor::visit( node );
}

void AstToCasmIRVisitor::visit( ExistentialQuantifierExpression& node )
{
    // TODO
    RecursiveVisitor::visit( node );
}

void AstToCasmIRVisitor::visit( SkipRule& node )
{
    // TODO
    RecursiveVisitor::visit( node );
}

void AstToCasmIRVisitor::visit( ConditionalRule& node )
{
    // TODO
    RecursiveVisitor::visit( node );
}

void AstToCasmIRVisitor::visit( CaseRule& node )
{
    // TODO
    RecursiveVisitor::visit( node );
}

void AstToCasmIRVisitor::visit( LetRule& node )
{
    // TODO
    RecursiveVisitor::visit( node );
}

void AstToCasmIRVisitor::visit( ForallRule& node )
{
    // TODO
    RecursiveVisitor::visit( node );
}

void AstToCasmIRVisitor::visit( IterateRule& node )
{
    // TODO
    RecursiveVisitor::visit( node );
}

void AstToCasmIRVisitor::visit( BlockRule& node )
{
    // TODO
    RecursiveVisitor::visit( node );
}

void AstToCasmIRVisitor::visit( SequenceRule& node )
{
    // TODO
    RecursiveVisitor::visit( node );
}

void AstToCasmIRVisitor::visit( UpdateRule& node )
{
    // TODO
    RecursiveVisitor::visit( node );
}

void AstToCasmIRVisitor::visit( CallRule& node )
{
    // TODO
    RecursiveVisitor::visit( node );
}

void AstToCasmIRVisitor::visit( UnresolvedType& node )
{
    // TODO
}

void AstToCasmIRVisitor::visit( BasicType& node )
{
    // TODO
    RecursiveVisitor::visit( node );
}

void AstToCasmIRVisitor::visit( ComposedType& node )
{
    // TODO
    RecursiveVisitor::visit( node );
}

void AstToCasmIRVisitor::visit( FixedSizedType& node )
{
    // TODO
    RecursiveVisitor::visit( node );
}

void AstToCasmIRVisitor::visit( RangedType& node )
{
    // TODO
    RecursiveVisitor::visit( node );
}

void AstToCasmIRVisitor::visit( BasicAttribute& node )
{
    // TODO
    RecursiveVisitor::visit( node );
}

void AstToCasmIRVisitor::visit( ExpressionAttribute& node )
{
    // TODO
    RecursiveVisitor::visit( node );
}

void AstToCasmIRVisitor::visit( IdentifierNode& node )
{
    // TODO
    RecursiveVisitor::visit( node );
}

void AstToCasmIRVisitor::visit( ExpressionCase& node )
{
    // TODO
    RecursiveVisitor::visit( node );
}

void AstToCasmIRVisitor::visit( DefaultCase& node )
{
    // TODO
    RecursiveVisitor::visit( node );
}

libcasm_ir::Specification::Ptr AstToCasmIRVisitor::specification( void ) const
{
    return m_specification;
}

void AstToCasmIRPass::usage( libpass::PassUsage& pu )
{
    pu.require< TypeCheckPass >();
    pu.provide< libcasm_ir::ConsistencyCheckPass >();
}

bool AstToCasmIRPass::run( libpass::PassResult& pr )
{
    libpass::PassLogger log( &id, stream() );

    // m_specification = nullptr;

    // initially_scope = 0;
    // initially_update_scope = 0;
    // is_initially = false;

    auto data = pr.result< TypeCheckPass >();
    auto specification = data->specification();

    log.debug( "transforming AST specification '"
               + specification->name()->identifier()
               + "'" );

    AstToCasmIRVisitor visitor;
    specification->accept( visitor );

    if( not visitor.specification() )
    {
        log.error( "inconsistent AST to IR transformation" );
        return false;
    }

    pr.setResult< libcasm_ir::ConsistencyCheckPass >(
        libstdhl::make< libcasm_ir::ConsistencyCheckPass::Data >(
            visitor.specification() ) );

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
