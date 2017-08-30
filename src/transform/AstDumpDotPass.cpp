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

#include "../pass/src/PassLogger.h"
#include "../pass/src/PassRegistry.h"
#include "../pass/src/PassResult.h"
#include "../pass/src/PassUsage.h"

#include "../Logger.h"
#include "../analyze/TypeInferencePass.h"
#include "../ast/RecursiveVisitor.h"
#include "../ast/Specification.h"

using namespace libcasm_fe;
using namespace Ast;

char AstDumpDotPass::id = 0;

static libpass::PassRegistration< AstDumpDotPass > PASS( "AstDumpDotPass",
    "generates a DOT graph of the AST and dumps it to './out.dot' for now",
    "ast-dump-dot", 0 );

class AstDumpDotVisitor final : public RecursiveVisitor
{
  private:
    /**
     * @brief RAII dot link
     */
    class DotLink
    {
      public:
        DotLink( AstDumpDotVisitor* visitor, Node* node )
        : m_visitor( visitor )
        {
            if( not visitor->m_parentNodes.empty() )
            {
                auto parentNode = visitor->m_parentNodes.top();
                visitor->dumpLink( parentNode, node );
            }
            visitor->m_parentNodes.push( node );
        }

        ~DotLink()
        {
            m_visitor->m_parentNodes.pop();
        }

      private:
        AstDumpDotVisitor* m_visitor;
    };

  public:
    AstDumpDotVisitor( std::ostream& stream );

    void setDumpNodeLocation( u1 dumpNodeLocation );

    void visit( Specification& node ) override;

    void visit( VariableDefinition& node ) override;
    void visit( FunctionDefinition& node ) override;
    void visit( DerivedDefinition& node ) override;
    void visit( RuleDefinition& node ) override;
    void visit( EnumerationDefinition& node ) override;

    void visit( ValueAtom& node ) override;
    void visit( ReferenceAtom& node ) override;
    void visit( UndefAtom& node ) override;
    void visit( DirectCallExpression& node ) override;
    void visit( IndirectCallExpression& node ) override;
    void visit( UnaryExpression& node ) override;
    void visit( BinaryExpression& node ) override;
    void visit( RangeExpression& node ) override;
    void visit( ListExpression& node ) override;
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

    void visit( UnresolvedType& node ) override;
    void visit( BasicType& node ) override;
    void visit( ComposedType& node ) override;
    void visit( FixedSizedType& node ) override;
    void visit( RelationType& node ) override;

    void visit( BasicAttribute& node ) override;
    void visit( ExpressionAttribute& node ) override;

    void visit( Identifier& node ) override;
    void visit( IdentifierPath& node ) override;
    void visit( ExpressionCase& node ) override;
    void visit( DefaultCase& node ) override;

  private:
    void dumpNode( const Node& node, const std::string& name );
    void dumpNode( const TypedNode& node, const std::string& name );
    void dumpLabel( const Node& node );
    void dumpLabel( const TypedNode& node );
    void dumpLink( Node* from, Node* to );

  private:
    std::ostream& m_stream;
    std::stack< Node* > m_parentNodes; /**< holds the parent nodes of DotLink */
    u1 m_dumpNodeLocation = false;     /**< dump node source code location */
};

AstDumpDotVisitor::AstDumpDotVisitor( std::ostream& stream )
: m_stream( stream )
, m_parentNodes()
, m_dumpNodeLocation( false )
{
}

void AstDumpDotVisitor::setDumpNodeLocation( u1 dumpNodeLocation )
{
    m_dumpNodeLocation = dumpNodeLocation;
}

void AstDumpDotVisitor::visit( Specification& node )
{
    m_stream << "subgraph \"" << node.name()->name() << "\" {\n";

    { // scope for DotLink object
        DotLink link( this, &node );

        dumpNode( node, "CASM\\nSpecification" );
        RecursiveVisitor::visit( node );
    }

    m_stream << "}\n";
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

void AstDumpDotVisitor::visit( ReferenceAtom& node )
{
    DotLink link( this, &node );
    dumpNode( node, "ReferenceAtom" );
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
    dumpNode(
        node, "DirectCallExpression\nTarget type: " + node.targetTypeName() );
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
    dumpNode(
        node, "UnaryExpression\n" + libcasm_ir::Value::token( node.op() ) );
    RecursiveVisitor::visit( node );
}

void AstDumpDotVisitor::visit( BinaryExpression& node )
{
    DotLink link( this, &node );
    dumpNode(
        node, "BinaryExpression\n" + libcasm_ir::Value::token( node.op() ) );
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

void AstDumpDotVisitor::visit( LetExpression& node )
{
    DotLink link( this, &node );
    dumpNode( node, "LetExpression" );
    RecursiveVisitor::visit( node );
}

void AstDumpDotVisitor::visit( ConditionalExpression& node )
{
    DotLink link( this, &node );
    dumpNode( node, "ConditionalExpression" );
    RecursiveVisitor::visit( node );
}

void AstDumpDotVisitor::visit( ChooseExpression& node )
{
    DotLink link( this, &node );
    dumpNode( node, "ChooseExpression" );
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

void AstDumpDotVisitor::visit( ChooseRule& node )
{
    DotLink link( this, &node );
    dumpNode( node, "ChooseRule" );
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

void AstDumpDotVisitor::visit( RelationType& node )
{
    DotLink link( this, &node );
    dumpNode( node, "RelationType" );
    RecursiveVisitor::visit( node );
}

void AstDumpDotVisitor::visit( BasicAttribute& node )
{
    DotLink link( this, &node );
    dumpNode( node, "BasicAttribute" );
    RecursiveVisitor::visit( node );
}

void AstDumpDotVisitor::visit( ExpressionAttribute& node )
{
    DotLink link( this, &node );
    dumpNode( node, "ExpressionAttribute" );
    RecursiveVisitor::visit( node );
}

void AstDumpDotVisitor::visit( Identifier& node )
{
    DotLink link( this, &node );
    dumpNode( node, node.name() );
    RecursiveVisitor::visit( node );
}

void AstDumpDotVisitor::visit( IdentifierPath& node )
{
    DotLink link( this, &node );

    std::string name;
    switch( node.type() )
    {
        case IdentifierPath::Type::ABSOLUTE:
            name = "Absolute";
            break;
        case IdentifierPath::Type::RELATIVE:
            name = "Relative";
            break;
    }
    name += " IdentifierPath";

    dumpNode( node, name );
    RecursiveVisitor::visit( node );
}

void AstDumpDotVisitor::visit( ExpressionCase& node )
{
    DotLink link( this, &node );
    dumpNode( node, "ExpressionCase" );
    RecursiveVisitor::visit( node );
}

void AstDumpDotVisitor::visit( DefaultCase& node )
{
    DotLink link( this, &node );
    dumpNode( node, "DefaultCase" );
    RecursiveVisitor::visit( node );
}

void AstDumpDotVisitor::dumpNode( const Node& node, const std::string& name )
{
    m_stream << "\"" << &node << "\" [label=\"" << name;

    dumpLabel( node );

    m_stream << "\"];\n";
}

void AstDumpDotVisitor::dumpNode(
    const TypedNode& node, const std::string& name )
{
    m_stream << "\"" << &node << "\" [label=\"" << name;

    dumpLabel( node );

    m_stream << "\"];\n";
}

void AstDumpDotVisitor::dumpLabel( const Node& node )
{
    if( m_dumpNodeLocation )
    {
        m_stream << "\n" << node.sourceLocation();
    }
}

void AstDumpDotVisitor::dumpLabel( const TypedNode& node )
{
    dumpLabel( static_cast< const Node& >( node ) );

    if( true ) // m_dumpType
    {
        m_stream << "\n";

        if( node.type() )
        {
            m_stream << node.type()->description();
        }
        else
        {
            m_stream << "UNRESOLVED";
        }
    }
}

void AstDumpDotVisitor::dumpLink( Node* from, Node* to )
{
    m_stream << "\"" << from << "\" -> \"" << to << "\";\n";
}

void AstDumpDotPass::usage( libpass::PassUsage& pu )
{
    pu.require< TypeInferencePass >();
}

u1 AstDumpDotPass::run( libpass::PassResult& pr )
{
    Logger log( &id, stream() );

    const auto& data = pr.result< TypeInferencePass >();
    const auto& specification = data->specification();

    const std::string outputFilePath
        = "./obj/out.dot";            // TODO: add command-line switch
    const u1 dumpNodeLocation = true; // TODO: add command-line switch

    const auto printDotGraph = [&]( std::ostream& out ) {
        out << "digraph \"main\" {\n";

        AstDumpDotVisitor visitor{ out };
        visitor.setDumpNodeLocation( dumpNodeLocation );

        specification->accept( visitor );

        out << "}\n";
    };

    if( outputFilePath == "stdout" )
    {
        printDotGraph( std::cout );
    }
    else
    {
        log.debug( "writing dot graph to '" + outputFilePath + "'" );

        std::ofstream dotFile( outputFilePath );
        if( not dotFile.is_open() )
        {
            log.error( "could not open '" + outputFilePath + "'" );
            return false;
        }

        printDotGraph( dotFile );
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
