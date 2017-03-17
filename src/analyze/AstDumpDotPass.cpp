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

#include "AstDumpDotPass.h"

#include <vector>

#include "../ast/RecursiveVisitor.h"
#include "../ast/Specification.h"
#include "../transform/SourceToAstPass.h"

using namespace libcasm_fe;
using namespace Ast;

char AstDumpDotPass::id = 0;

static libpass::PassRegistration< AstDumpDotPass > PASS( "AST Dumping Pass",
    "generates a DOT graph of the AST and dumps it to './obj/out.dot' for now",
    "ast-dump", 0 );

class AstDumpDotVisitor final : public RecursiveVisitor
{
  private:
    class DotLink
    {
      public:
        DotLink( AstDumpDotVisitor* visitor, Node* node )
        : m_visitor( visitor )
        {
            if( not visitor->m_parentNodes.empty() )
            {
                auto parentNode = visitor->m_parentNodes.back();
                visitor->dumpLink( parentNode, node );
            }
            visitor->m_parentNodes.push_back( node );
        }

        ~DotLink()
        {
            m_visitor->m_parentNodes.pop_back();
        }

      private:
        AstDumpDotVisitor* m_visitor;
    };

  public:
    AstDumpDotVisitor( std::ostream& stream );

    void visit( IdentifierNode& node ) override;

    void visit( Specification& node ) override;

    void visit( VariableDefinition& node ) override;
    void visit( FunctionDefinition& node ) override;
    void visit( DerivedDefinition& node ) override;
    void visit( RuleDefinition& node ) override;
    void visit( EnumerationDefinition& node ) override;

    void visit( ValueAtom& node ) override;
    void visit( RuleReferenceAtom& node ) override;
    void visit( ZeroAtom& node ) override;
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

    void visit( VoidType& node ) override;
    void visit( UnresolvedType& node ) override;
    void visit( BasicType& node ) override;
    void visit( ComposedType& node ) override;
    void visit( FixedSizedType& node ) override;
    void visit( RangedType& node ) override;

  private:
    void dumpNode( const Node& node, const std::string& name );
    void dumpLink( Node* from, Node* to );

  private:
    std::ostream& m_stream;
    std::vector< Node* > m_parentNodes;
};

AstDumpDotVisitor::AstDumpDotVisitor( std::ostream& stream )
: m_stream( stream )
{
}

void AstDumpDotVisitor::visit( IdentifierNode& node )
{
    DotLink link( this, &node );
    dumpNode( node, node.identifier() );
    RecursiveVisitor::visit( node );
}

void AstDumpDotVisitor::visit( Specification& node )
{
    DotLink link( this, &node );
    dumpNode( node, "CASM\\nSpecification" );
    RecursiveVisitor::visit( node );
}

void AstDumpDotVisitor::visit( VariableDefinition& node )
{
    DotLink link( this, &node );
    dumpNode( node, "VariableDefinition" );
    RecursiveVisitor::visit( node );
}

void AstDumpDotVisitor::visit( FunctionDefinition& node )
{
    DotLink link( this, &node );
    dumpNode( node, "FunctionDefinition" );
    RecursiveVisitor::visit( node );
}

void AstDumpDotVisitor::visit( DerivedDefinition& node )
{
    DotLink link( this, &node );
    dumpNode( node, "DerivedDefinition" );
    RecursiveVisitor::visit( node );
}

void AstDumpDotVisitor::visit( RuleDefinition& node )
{
    DotLink link( this, &node );
    dumpNode( node, "RuleDefinition" );
    RecursiveVisitor::visit( node );
}

void AstDumpDotVisitor::visit( EnumerationDefinition& node )
{
    DotLink link( this, &node );
    dumpNode( node, "EnumerationDefinition" );
    RecursiveVisitor::visit( node );
}

void AstDumpDotVisitor::visit( ValueAtom& node )
{
    DotLink link( this, &node );
    dumpNode( node, "ValueAtom: " + node.value()->name() );
    RecursiveVisitor::visit( node );
}

void AstDumpDotVisitor::visit( RuleReferenceAtom& node )
{
    DotLink link( this, &node );
    dumpNode( node, "RuleReferenceAtom" );
    RecursiveVisitor::visit( node );
}

void AstDumpDotVisitor::visit( ZeroAtom& node )
{
    DotLink link( this, &node );
    dumpNode( node, "ZeroAtom" );
    RecursiveVisitor::visit( node );
}

void AstDumpDotVisitor::visit( UndefAtom& node )
{
    DotLink link( this, &node );
    dumpNode( node, "UndefAtom" );
    RecursiveVisitor::visit( node );
}

void AstDumpDotVisitor::visit( DirectCallExpression& node )
{
    DotLink link( this, &node );
    dumpNode( node, "DirectCallExpression" );
    RecursiveVisitor::visit( node );
}

void AstDumpDotVisitor::visit( IndirectCallExpression& node )
{
    DotLink link( this, &node );
    dumpNode( node, "IndirectCallExpression" );
    RecursiveVisitor::visit( node );
}

void AstDumpDotVisitor::visit( UnaryExpression& node )
{
    DotLink link( this, &node );
    dumpNode( node, "Expression" ); // TODO dump operator
    RecursiveVisitor::visit( node );
}

void AstDumpDotVisitor::visit( BinaryExpression& node )
{
    DotLink link( this, &node );
    dumpNode( node, "Expression" ); // TODO dump operator
    RecursiveVisitor::visit( node );
}

void AstDumpDotVisitor::visit( RangeExpression& node )
{
    DotLink link( this, &node );
    dumpNode( node, "RangeExpression" );
    RecursiveVisitor::visit( node );
}

void AstDumpDotVisitor::visit( ListExpression& node )
{
    DotLink link( this, &node );
    dumpNode( node, "ListExpression" );
    RecursiveVisitor::visit( node );
}

void AstDumpDotVisitor::visit( ConditionalExpression& node )
{
    DotLink link( this, &node );
    dumpNode( node, "ConditionalExpression" );
    RecursiveVisitor::visit( node );
}

void AstDumpDotVisitor::visit( UniversalQuantifierExpression& node )
{
    DotLink link( this, &node );
    dumpNode( node, "UniversalQuantifierExpression" );
    RecursiveVisitor::visit( node );
}

void AstDumpDotVisitor::visit( ExistentialQuantifierExpression& node )
{
    DotLink link( this, &node );
    dumpNode( node, "ExistentialQuantifierExpression" );
    RecursiveVisitor::visit( node );
}

void AstDumpDotVisitor::visit( SkipRule& node )
{
    DotLink link( this, &node );
    dumpNode( node, "SkipRule" );
    RecursiveVisitor::visit( node );
}

void AstDumpDotVisitor::visit( ConditionalRule& node )
{
    DotLink link( this, &node );
    dumpNode( node, "ConditionalRule" );
    RecursiveVisitor::visit( node );
}

void AstDumpDotVisitor::visit( CaseRule& node )
{
    DotLink link( this, &node );
    dumpNode( node, "CaseRule" );
    RecursiveVisitor::visit( node );
}

void AstDumpDotVisitor::visit( LetRule& node )
{
    DotLink link( this, &node );
    dumpNode( node, "LetRule" );
    RecursiveVisitor::visit( node );
}

void AstDumpDotVisitor::visit( ForallRule& node )
{
    DotLink link( this, &node );
    dumpNode( node, "ForallRule" );
    RecursiveVisitor::visit( node );
}

void AstDumpDotVisitor::visit( IterateRule& node )
{
    DotLink link( this, &node );
    dumpNode( node, "IterateRule" );
    RecursiveVisitor::visit( node );
}

void AstDumpDotVisitor::visit( BlockRule& node )
{
    DotLink link( this, &node );
    dumpNode( node, "BlockRule" );
    RecursiveVisitor::visit( node );
}

void AstDumpDotVisitor::visit( SequenceRule& node )
{
    DotLink link( this, &node );
    dumpNode( node, "SequenceRule" );
    RecursiveVisitor::visit( node );
}

void AstDumpDotVisitor::visit( UpdateRule& node )
{
    DotLink link( this, &node );
    dumpNode( node, "UpdateRule" );
    RecursiveVisitor::visit( node );
}

void AstDumpDotVisitor::visit( CallRule& node )
{
    DotLink link( this, &node );
    dumpNode( node, "CallRule" );
    RecursiveVisitor::visit( node );
}

void AstDumpDotVisitor::visit( VoidType& node )
{
    DotLink link( this, &node );
    dumpNode( node, "VoidType" );
}

void AstDumpDotVisitor::visit( UnresolvedType& node )
{
    DotLink link( this, &node );
    dumpNode( node, "UnresolvedType" );
}

void AstDumpDotVisitor::visit( BasicType& node )
{
    DotLink link( this, &node );
    dumpNode( node, "BasicType" );
    RecursiveVisitor::visit( node );
}

void AstDumpDotVisitor::visit( ComposedType& node )
{
    DotLink link( this, &node );
    dumpNode( node, "ComposedType" );
    RecursiveVisitor::visit( node );
}

void AstDumpDotVisitor::visit( FixedSizedType& node )
{
    DotLink link( this, &node );
    dumpNode( node, "FixedSizedType" );
    RecursiveVisitor::visit( node );
}

void AstDumpDotVisitor::visit( RangedType& node )
{
    DotLink link( this, &node );
    dumpNode( node, "RangedType" );
    RecursiveVisitor::visit( node );
}

void AstDumpDotVisitor::dumpNode(
    const Node& node, const std::string& name )
{
    m_stream << "\"" << &node << "\" [label=\"" << name << "\"];\n";
}

void AstDumpDotVisitor::dumpLink( Node* from, Node* to )
{
    m_stream << "\"" << from << "\" -> \"" << to << "\";\n";
}

bool AstDumpDotPass::run( libpass::PassResult& pr )
{
    const auto sourceToAstPass = pr.result< SourceToAstPass >();
    const auto specification = sourceToAstPass->specification();

    std::ofstream dotfile( "./out.dot" );

    dotfile << "digraph \"main\" {\n";

    AstDumpDotVisitor visitor{ dotfile };
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
