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

#include "AstDumpPass.h"

#include "../ast/Specification.h"
#include "../ast/RecursiveVisitor.h"
#include "../transform/SourceToAstPass.h"

using namespace libcasm_fe;
using namespace Ast;

char AstDumpPass::id = 0;

static libpass::PassRegistration< AstDumpPass > PASS( "AST Dumping Pass",
    "generates a DOT graph of the AST and dumps it to './obj/out.dot' for now",
    "ast-dump", 0 );

class AstDumpVisitor final : public Ast::RecursiveVisitor
{
public:
    AstDumpVisitor( std::ostream& stream );

    void visit( Ast::IdentifierNode& node ) override;

    void visit( Ast::Specification& node ) override;

    void visit( Ast::VariableDefinition& node ) override;
    void visit( Ast::FunctionDefinition& node ) override;
    void visit( Ast::DerivedDefinition& node ) override;
    void visit( Ast::RuleDefinition& node ) override;
    void visit( Ast::EnumerationDefinition& node ) override;

    void visit( Ast::ValueAtom& node ) override;
    void visit( Ast::RuleReferenceAtom& node ) override;
    void visit( Ast::ZeroAtom& node ) override;
    void visit( Ast::UndefAtom& node ) override;
    void visit( Ast::DirectCallExpression& node ) override;
    void visit( Ast::IndirectCallExpression& node ) override;
    void visit( Ast::UnaryExpression& node ) override;
    void visit( Ast::BinaryExpression& node ) override;
    void visit( Ast::RangeExpression& node ) override;
    void visit( Ast::ListExpression& node ) override;
    void visit( Ast::ConditionalExpression& node ) override;
    void visit( Ast::UniversalQuantifierExpression& node ) override;
    void visit( Ast::ExistentialQuantifierExpression& node ) override;

    void visit( Ast::SkipRule& node ) override;
    void visit( Ast::ConditionalRule& node ) override;
    void visit( Ast::CaseRule& node ) override;
    void visit( Ast::LetRule& node ) override;
    void visit( Ast::ForallRule& node ) override;
    void visit( Ast::IterateRule& node ) override;
    void visit( Ast::BlockRule& node ) override;
    void visit( Ast::SequenceRule& node ) override;
    void visit( Ast::UpdateRule& node ) override;
    void visit( Ast::CallRule& node ) override;

    void visit( Ast::BasicType& node ) override;
    void visit( Ast::ComposedType& node ) override;
    void visit( Ast::FixedSizedType& node ) override;
    void visit( Ast::RangedType& node ) override;

private:
    void dumpNode( const Ast::Node& node, const std::string& name );
    void dumpLink( const Ast::Node& from, const Ast::Node& to );

private:
    std::ostream& m_stream;
};

AstDumpVisitor::AstDumpVisitor( std::ostream& stream )
: m_stream( stream )
{
}

void AstDumpVisitor::visit( IdentifierNode& node )
{
    dumpNode( node, node.identifier() );
    RecursiveVisitor::visit( node );
}

void AstDumpVisitor::visit( Specification& node )
{
    dumpNode( node, "CASM\\nSpecification" );
    RecursiveVisitor::visit( node );
}

void AstDumpVisitor::visit( VariableDefinition& node )
{
    dumpNode( node, "VariableDefinition" );
    RecursiveVisitor::visit( node );
}

void AstDumpVisitor::visit( FunctionDefinition& node )
{
    dumpNode( node, "FunctionDefinition" );
    RecursiveVisitor::visit( node );
}

void AstDumpVisitor::visit( DerivedDefinition& node )
{
    dumpNode( node, "DerivedDefinition" );
    RecursiveVisitor::visit( node );
}

void AstDumpVisitor::visit( RuleDefinition& node )
{
    dumpNode( node, "RuleDefinition" );
    RecursiveVisitor::visit( node );
}

void AstDumpVisitor::visit( EnumerationDefinition& node )
{
    dumpNode( node, "EnumerationDefinition" );
    RecursiveVisitor::visit( node );
}

void AstDumpVisitor::visit( ValueAtom& node )
{
    dumpNode( node, "ValueAtom" ); // TODO dump value
    RecursiveVisitor::visit( node );
}

void AstDumpVisitor::visit( RuleReferenceAtom& node )
{
    dumpNode( node, "RuleReferenceAtom" );
    RecursiveVisitor::visit( node );
}

void AstDumpVisitor::visit( ZeroAtom& node )
{
    dumpNode( node, "ZeroAtom" );
    RecursiveVisitor::visit( node );
}

void AstDumpVisitor::visit( UndefAtom& node )
{
    dumpNode( node, "UndefAtom" );
    RecursiveVisitor::visit( node );
}

void AstDumpVisitor::visit( DirectCallExpression& node )
{
    dumpNode( node, "DirectCallExpression" );
    RecursiveVisitor::visit( node );
}

void AstDumpVisitor::visit( IndirectCallExpression& node )
{
    dumpNode( node, "IndirectCallExpression" );
    RecursiveVisitor::visit( node );
}

void AstDumpVisitor::visit( UnaryExpression& node )
{
    dumpNode( node, "Expression" ); // TODO dump operator
    RecursiveVisitor::visit( node );
}

void AstDumpVisitor::visit( BinaryExpression& node )
{
    dumpNode( node, "Expression" ); // TODO dump operator
    RecursiveVisitor::visit( node );
}

void AstDumpVisitor::visit( RangeExpression& node )
{
    dumpNode( node, "RangeExpression" );
    RecursiveVisitor::visit( node );
}

void AstDumpVisitor::visit( ListExpression& node )
{
    dumpNode( node, "ListExpression" );
    RecursiveVisitor::visit( node );
}

void AstDumpVisitor::visit( ConditionalExpression& node )
{
    dumpNode( node, "ConditionalExpression" );
    RecursiveVisitor::visit( node );
}

void AstDumpVisitor::visit( UniversalQuantifierExpression& node )
{
    dumpNode( node, "UniversalQuantifierExpression" );
    RecursiveVisitor::visit( node );
}

void AstDumpVisitor::visit( ExistentialQuantifierExpression& node )
{
    dumpNode( node, "ExistentialQuantifierExpression" );
    RecursiveVisitor::visit( node );
}

void AstDumpVisitor::visit( SkipRule& node )
{
    dumpNode( node, "SkipRule" );
    RecursiveVisitor::visit( node );
}

void AstDumpVisitor::visit( ConditionalRule& node )
{
    dumpNode( node, "ConditionalRule" );
    RecursiveVisitor::visit( node );
}

void AstDumpVisitor::visit( CaseRule& node )
{
    dumpNode( node, "CaseRule" );
    RecursiveVisitor::visit( node );
}

void AstDumpVisitor::visit( LetRule& node )
{
    dumpNode( node, "LetRule" );
    RecursiveVisitor::visit( node );
}

void AstDumpVisitor::visit( ForallRule& node )
{
    dumpNode( node, "ForallRule" );
    RecursiveVisitor::visit( node );
}

void AstDumpVisitor::visit( IterateRule& node )
{
    dumpNode( node, "IterateRule" );
    RecursiveVisitor::visit( node );
}

void AstDumpVisitor::visit( BlockRule& node )
{
    dumpNode( node, "BlockRule" );
    RecursiveVisitor::visit( node );
}

void AstDumpVisitor::visit( SequenceRule& node )
{
    dumpNode( node, "SequenceRule" );
    RecursiveVisitor::visit( node );
}

void AstDumpVisitor::visit( UpdateRule& node )
{
    dumpNode( node, "UpdateRule" );
    RecursiveVisitor::visit( node );
}

void AstDumpVisitor::visit( CallRule& node )
{
    dumpNode( node, "CallRule" );
    RecursiveVisitor::visit( node );
}

void AstDumpVisitor::visit( BasicType& node )
{
    dumpNode( node, "BasicType" );
    RecursiveVisitor::visit( node );
}

void AstDumpVisitor::visit( ComposedType& node )
{
    dumpNode( node, "ComposedType" );
    RecursiveVisitor::visit( node );
}

void AstDumpVisitor::visit( FixedSizedType& node )
{
    dumpNode( node, "FixedSizedType" );
    RecursiveVisitor::visit( node );
}

void AstDumpVisitor::visit( RangedType& node )
{
    dumpNode( node, "RangedType" );
    RecursiveVisitor::visit( node );
}

void AstDumpVisitor::dumpNode( const Ast::Node& node, const std::string& name )
{
    m_stream << "    " << &node << " [label=\"" << name << "\"];\n";
}

void AstDumpVisitor::dumpLink( const Ast::Node& from, const Ast::Node& to )
{
    m_stream << "    " << &from << " -> " << &to << ";\n";
}

bool AstDumpPass::run( libpass::PassResult& pr )
{
    const auto sourceToAstPass = pr.result< SourceToAstPass >();
    const auto specification = sourceToAstPass->specification();

    std::ofstream dotfile( "./obj/out.dot" );
    dotfile << "digraph \"main\" {\n";

    AstDumpVisitor visitor{ dotfile };
    specification->accept( visitor );

    dotfile << "}\n";
    dotfile.close();

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
