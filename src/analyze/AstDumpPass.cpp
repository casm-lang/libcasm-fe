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
#include "../transform/SourceToAstPass.h"

using namespace libcasm_fe;
using namespace Ast;

char AstDumpPass::id = 0;

static libpass::PassRegistration< AstDumpPass > PASS( "AST Dumping Pass",
    "generates a DOT graph of the AST and dumps it to './obj/out.dot' for now",
    "ast-dump", 0 );

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

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
