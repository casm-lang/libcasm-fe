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

#include "AstDumpSourcePass.h"

#include "../ast/RecursiveVisitor.h"
#include "../ast/Specification.h"
#include "../transform/SourceToAstPass.h"

using namespace libcasm_fe;
using namespace Ast;

char AstDumpSourcePass::id = 0;

static libpass::PassRegistration< AstDumpSourcePass > PASS( "AstDumpSourcePass",
    "outputs the parsed AST as a CASM input specification to stdout",
    "ast-dump", 0 );

class AstDumpSourceVisitor final : public RecursiveVisitor
{
  public:
    AstDumpSourceVisitor( std::ostream& stream );

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

  private:
    std::ostream& m_stream;
};

AstDumpSourceVisitor::AstDumpSourceVisitor( std::ostream& stream )
: m_stream( stream )
{
}

void AstDumpSourceVisitor::visit( Specification& node )
{
    m_stream << "CASM\n"
                "\n";

    RecursiveVisitor::visit( node );

    m_stream << "\n";
}

void AstDumpSourceVisitor::visit( VariableDefinition& node )
{
    // TODO
    RecursiveVisitor::visit( node );
}

void AstDumpSourceVisitor::visit( FunctionDefinition& node )
{
    // TODO
    RecursiveVisitor::visit( node );
}

void AstDumpSourceVisitor::visit( DerivedDefinition& node )
{
    // TODO
    RecursiveVisitor::visit( node );
}

void AstDumpSourceVisitor::visit( RuleDefinition& node )
{
    // TODO
    RecursiveVisitor::visit( node );
}

void AstDumpSourceVisitor::visit( EnumerationDefinition& node )
{
    // TODO
    RecursiveVisitor::visit( node );
}

void AstDumpSourceVisitor::visit( ValueAtom& node )
{
    // TODO
    RecursiveVisitor::visit( node );
}

void AstDumpSourceVisitor::visit( RuleReferenceAtom& node )
{
    // TODO
    RecursiveVisitor::visit( node );
}

void AstDumpSourceVisitor::visit( UndefAtom& node )
{
    // TODO
    RecursiveVisitor::visit( node );
}

void AstDumpSourceVisitor::visit( DirectCallExpression& node )
{
    // TODO
    RecursiveVisitor::visit( node );
}

void AstDumpSourceVisitor::visit( IndirectCallExpression& node )
{
    // TODO
    RecursiveVisitor::visit( node );
}

void AstDumpSourceVisitor::visit( UnaryExpression& node )
{
    // TODO
    RecursiveVisitor::visit( node );
}

void AstDumpSourceVisitor::visit( BinaryExpression& node )
{
    // TODO
    RecursiveVisitor::visit( node );
}

void AstDumpSourceVisitor::visit( RangeExpression& node )
{
    // TODO
    RecursiveVisitor::visit( node );
}

void AstDumpSourceVisitor::visit( ListExpression& node )
{
    // TODO
    RecursiveVisitor::visit( node );
}

void AstDumpSourceVisitor::visit( ConditionalExpression& node )
{
    // TODO
    RecursiveVisitor::visit( node );
}

void AstDumpSourceVisitor::visit( UniversalQuantifierExpression& node )
{
    // TODO
    RecursiveVisitor::visit( node );
}

void AstDumpSourceVisitor::visit( ExistentialQuantifierExpression& node )
{
    // TODO
    RecursiveVisitor::visit( node );
}

void AstDumpSourceVisitor::visit( SkipRule& node )
{
    // TODO
    RecursiveVisitor::visit( node );
}

void AstDumpSourceVisitor::visit( ConditionalRule& node )
{
    // TODO
    RecursiveVisitor::visit( node );
}

void AstDumpSourceVisitor::visit( CaseRule& node )
{
    // TODO
    RecursiveVisitor::visit( node );
}

void AstDumpSourceVisitor::visit( LetRule& node )
{
    // TODO
    RecursiveVisitor::visit( node );
}

void AstDumpSourceVisitor::visit( ForallRule& node )
{
    // TODO
    RecursiveVisitor::visit( node );
}

void AstDumpSourceVisitor::visit( IterateRule& node )
{
    // TODO
    RecursiveVisitor::visit( node );
}

void AstDumpSourceVisitor::visit( BlockRule& node )
{
    // TODO
    RecursiveVisitor::visit( node );
}

void AstDumpSourceVisitor::visit( SequenceRule& node )
{
    // TODO
    RecursiveVisitor::visit( node );
}

void AstDumpSourceVisitor::visit( UpdateRule& node )
{
    // TODO
    RecursiveVisitor::visit( node );
}

void AstDumpSourceVisitor::visit( CallRule& node )
{
    // TODO
    RecursiveVisitor::visit( node );
}

void AstDumpSourceVisitor::visit( UnresolvedType& node )
{
    // TODO
}

void AstDumpSourceVisitor::visit( BasicType& node )
{
    // TODO
    RecursiveVisitor::visit( node );
}

void AstDumpSourceVisitor::visit( ComposedType& node )
{
    // TODO
    RecursiveVisitor::visit( node );
}

void AstDumpSourceVisitor::visit( FixedSizedType& node )
{
    // TODO
    RecursiveVisitor::visit( node );
}

void AstDumpSourceVisitor::visit( RangedType& node )
{
    // TODO
    RecursiveVisitor::visit( node );
}

void AstDumpSourceVisitor::visit( BasicAttribute& node )
{
    // TODO
    RecursiveVisitor::visit( node );
}

void AstDumpSourceVisitor::visit( ExpressionAttribute& node )
{
    // TODO
    RecursiveVisitor::visit( node );
}

void AstDumpSourceVisitor::visit( IdentifierNode& node )
{
    // TODO
    RecursiveVisitor::visit( node );
}

void AstDumpSourceVisitor::visit( ExpressionCase& node )
{
    // TODO
    RecursiveVisitor::visit( node );
}

void AstDumpSourceVisitor::visit( DefaultCase& node )
{
    // TODO
    RecursiveVisitor::visit( node );
}

u1 AstDumpSourcePass::run( libpass::PassResult& pr )
{
    libpass::PassLogger log( &id, stream() );

    try
    {
        const auto sourceToAstPass = pr.result< SourceToAstPass >();
        const auto specification = sourceToAstPass->specification();

        AstDumpSourceVisitor visitor{ std::cout };
        specification->accept( visitor );
    }
    catch( ... )
    {
        log.error( "unable to dump CASM specification" );
    }

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
