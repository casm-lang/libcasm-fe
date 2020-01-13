
//
//  Copyright (C) 2014-2020 CASM Organization <https://casm-lang.org>
//  All rights reserved.
//
//  Developed by: Philipp Paulweber
//                Emmanuel Pescosta
//                Florian Hahn
//                Ioan Molnar
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

#include "AstDumpPass.h"

#include <libcasm-fe/Logger>
#include <libcasm-fe/Namespace>
#include <libcasm-fe/Specification>
#include <libcasm-fe/analyze/ConsistencyCheckPass>
#include <libcasm-fe/ast/Declaration>
#include <libcasm-fe/ast/Literal>
#include <libcasm-fe/ast/Visitor>
#include <libcasm-fe/transform/CstToAstPass>

#include <libpass/PassRegistry>
#include <libpass/PassResult>
#include <libpass/PassUsage>

#include <libstdhl/File>

#include <fstream>
#include <iostream>
#include <stack>

using namespace libcasm_fe;
using namespace AST;

char AstDumpPass::id = 0;

static libpass::PassRegistration< AstDumpPass > PASS(
    "AstDumpPass",
    "generates DOT graph of the AST and dumps to specified output path",
    "ast-dump",
    0 );

namespace libcasm_fe
{
    namespace AST
    {
        class ASTDumpVisitor final : public RecursiveVisitor
        {
          private:
            /**
             * @brief RAII dot link
             */
            class DotLink
            {
              public:
                DotLink( ASTDumpVisitor* visitor, void* node )
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
                ASTDumpVisitor* m_visitor;
            };

          public:
            ASTDumpVisitor(
                std::ostream& stream, const std::string& name, const std::string& location );

            void setDumpNodeLocation( u1 dumpNodeLocation );

            void visit( Root& node ) override;

            void visit( InitDefinition& node ) override;
            void visit( VariableDefinition& node ) override;
            void visit( FunctionDefinition& node ) override;
            void visit( DerivedDefinition& node ) override;
            void visit( RuleDefinition& node ) override;
            void visit( EnumeratorDefinition& node ) override;
            void visit( EnumerationDefinition& node ) override;
            void visit( UsingDefinition& node ) override;
            void visit( UsingPathDefinition& node ) override;
            void visit( InvariantDefinition& node ) override;
            void visit( ImportDefinition& node ) override;
            void visit( DomainDefinition& node ) override;
            void visit( StructureDefinition& node ) override;
            void visit( BehaviorDefinition& node ) override;
            void visit( ImplementDefinition& node ) override;
            void visit( BuiltinDefinition& node ) override;
            void visit( Declaration& node ) override;

            void visit( ValueLiteral& node ) override;
            void visit( ReferenceLiteral& node ) override;
            void visit( UndefLiteral& node ) override;
            void visit( SetLiteral& node ) override;
            void visit( ListLiteral& node ) override;
            void visit( RangeLiteral& node ) override;
            void visit( TupleLiteral& node ) override;
            void visit( RecordLiteral& node ) override;

            void visit( EmbracedExpression& node ) override;
            void visit( NamedExpression& node ) override;
            void visit( DirectCallExpression& node ) override;
            void visit( MethodCallExpression& node ) override;
            void visit( LiteralCallExpression& node ) override;
            void visit( IndirectCallExpression& node ) override;
            void visit( TypeCastingExpression& node ) override;
            void visit( UnaryExpression& node ) override;
            void visit( BinaryExpression& node ) override;
            void visit( LetExpression& node ) override;
            void visit( ConditionalExpression& node ) override;
            void visit( ChooseExpression& node ) override;
            void visit( UniversalQuantifierExpression& node ) override;
            void visit( ExistentialQuantifierExpression& node ) override;
            void visit( CardinalityExpression& node ) override;

            void visit( SkipRule& node ) override;
            void visit( ConditionalRule& node ) override;
            void visit( CaseRule& node ) override;
            void visit( LetRule& node ) override;
            void visit( LocalRule& node ) override;
            void visit( ForallRule& node ) override;
            void visit( ChooseRule& node ) override;
            void visit( IterateRule& node ) override;
            void visit( BlockRule& node ) override;
            void visit( SequenceRule& node ) override;
            void visit( UpdateRule& node ) override;
            void visit( CallRule& node ) override;

            void visit( UnresolvedType& node ) override;
            void visit( BasicType& node ) override;
            void visit( TupleType& node ) override;
            void visit( RecordType& node ) override;
            void visit( TemplateType& node ) override;
            void visit( FixedSizedType& node ) override;
            void visit( RelationType& node ) override;

            void visit( Identifier& node ) override;
            void visit( IdentifierPath& node ) override;
            void visit( ExpressionCase& node ) override;
            void visit( DefaultCase& node ) override;
            void visit( VariableBinding& node ) override;

          private:
            void dumpNode( const Node& node, const std::string& name );
            void dumpNode( const TypedNode& node, const std::string& name );
            void dumpNode( const TypedPropertyNode& node, const std::string& name );
            void dumpNode( const TargetCallExpression& node, const std::string& name );
            void dumpLabel( const Node& node );
            void dumpLabel( const TypedNode& node );
            void dumpLabel( const TypedPropertyNode& node );
            void dumpLabel( const TargetCallExpression& node );
            void dumpLink( void* from, void* to );

          private:
            std::ostream& m_stream;
            const std::string m_name;
            const std::string m_location;
            std::stack< void* > m_parentNodes; /**< holds the parent nodes of DotLink */
            u1 m_dumpNodeLocation = false;     /**< dump node source code location */
        };
    }
}

ASTDumpVisitor::ASTDumpVisitor(
    std::ostream& stream, const std::string& name, const std::string& location )
: m_stream( stream )
, m_name( name )
, m_location( location )
, m_parentNodes()
, m_dumpNodeLocation( false )
{
}

void ASTDumpVisitor::setDumpNodeLocation( u1 dumpNodeLocation )
{
    m_dumpNodeLocation = dumpNodeLocation;
}

void ASTDumpVisitor::visit( Root& node )
{
    m_stream << "digraph \"AST\" {\n";
    m_stream << "subgraph \"" << m_name << "\" {\n"
             << "\"" << &node << "\" [label=\"Specification\n"
             << m_name << "\n"
             << m_location << "\"];\n";

    {
        DotLink link( this, &node );
        RecursiveVisitor::visit( node );
    }

    m_stream << "}\n";
    m_stream << "}\n";
}

void ASTDumpVisitor::visit( InitDefinition& node )
{
    DotLink link( this, &node );
    dumpNode( node, "InitDefinition" );
    RecursiveVisitor::visit( node );
}

void ASTDumpVisitor::visit( VariableDefinition& node )
{
    DotLink link( this, &node );
    dumpNode( node, "VariableDefinition" );
    RecursiveVisitor::visit( node );
}

void ASTDumpVisitor::visit( FunctionDefinition& node )
{
    DotLink link( this, &node );
    dumpNode( node, "FunctionDefinition" );
    RecursiveVisitor::visit( node );
}

void ASTDumpVisitor::visit( DerivedDefinition& node )
{
    DotLink link( this, &node );
    dumpNode( node, "DerivedDefinition" );
    RecursiveVisitor::visit( node );
}

void ASTDumpVisitor::visit( RuleDefinition& node )
{
    DotLink link( this, &node );
    dumpNode( node, "RuleDefinition" );
    RecursiveVisitor::visit( node );
}

void ASTDumpVisitor::visit( EnumeratorDefinition& node )
{
    DotLink link( this, &node );
    dumpNode( node, "EnumeratorDefinition" );
    RecursiveVisitor::visit( node );
}

void ASTDumpVisitor::visit( EnumerationDefinition& node )
{
    DotLink link( this, &node );
    dumpNode( node, "EnumerationDefinition" );
    RecursiveVisitor::visit( node );
}

void ASTDumpVisitor::visit( UsingDefinition& node )
{
    DotLink link( this, &node );
    dumpNode( node, "UsingDefinition" );
    RecursiveVisitor::visit( node );
}

void ASTDumpVisitor::visit( UsingPathDefinition& node )
{
    DotLink link( this, &node );
    dumpNode( node, "UsingPathDefinition" );
    RecursiveVisitor::visit( node );
}

void ASTDumpVisitor::visit( InvariantDefinition& node )
{
    DotLink link( this, &node );
    dumpNode( node, "InvariantDefinition" );
    RecursiveVisitor::visit( node );
}

void ASTDumpVisitor::visit( ImportDefinition& node )
{
    DotLink link( this, &node );
    dumpNode( node, "ImportDefinition" );
    RecursiveVisitor::visit( node );
}

void ASTDumpVisitor::visit( DomainDefinition& node )
{
    DotLink link( this, &node );
    dumpNode( node, "DomainDefinition" );
    RecursiveVisitor::visit( node );
}

void ASTDumpVisitor::visit( StructureDefinition& node )
{
    DotLink link( this, &node );
    dumpNode( node, "StructureDefinition" );
    RecursiveVisitor::visit( node );
}

void ASTDumpVisitor::visit( BehaviorDefinition& node )
{
    DotLink link( this, &node );
    dumpNode( node, "BehaviorDefinition" );
    RecursiveVisitor::visit( node );
}

void ASTDumpVisitor::visit( ImplementDefinition& node )
{
    DotLink link( this, &node );
    dumpNode( node, "ImplementDefinition" );
    RecursiveVisitor::visit( node );
}

void ASTDumpVisitor::visit( BuiltinDefinition& node )
{
    DotLink link( this, &node );
    dumpNode( node, "BuiltinDefinition" );
    RecursiveVisitor::visit( node );
}

void ASTDumpVisitor::visit( Declaration& node )
{
    DotLink link( this, &node );
    dumpNode( node, "Declaration" );
    RecursiveVisitor::visit( node );
}

void ASTDumpVisitor::visit( UndefLiteral& node )
{
    DotLink link( this, &node );
    dumpNode( node, "UndefLiteral" );
    RecursiveVisitor::visit( node );
}

void ASTDumpVisitor::visit( ValueLiteral& node )
{
    DotLink link( this, &node );
    dumpNode( node, "ValueLiteral: " + node.value()->name() );
    RecursiveVisitor::visit( node );
}

void ASTDumpVisitor::visit( ReferenceLiteral& node )
{
    DotLink link( this, &node );
    dumpNode( node, "ReferenceLiteral" );
    RecursiveVisitor::visit( node );
}

void ASTDumpVisitor::visit( SetLiteral& node )
{
    DotLink link( this, &node );
    dumpNode( node, "ListLiteral" );
    RecursiveVisitor::visit( node );
}

void ASTDumpVisitor::visit( ListLiteral& node )
{
    DotLink link( this, &node );
    dumpNode( node, "ListLiteral" );
    RecursiveVisitor::visit( node );
}

void ASTDumpVisitor::visit( RangeLiteral& node )
{
    DotLink link( this, &node );
    dumpNode( node, "RangeLiteral" );
    RecursiveVisitor::visit( node );
}

void ASTDumpVisitor::visit( TupleLiteral& node )
{
    DotLink link( this, &node );
    dumpNode( node, "TupleLiteral" );
    RecursiveVisitor::visit( node );
}

void ASTDumpVisitor::visit( RecordLiteral& node )
{
    DotLink link( this, &node );
    dumpNode( node, "RecordLiteral" );
    RecursiveVisitor::visit( node );
}

void ASTDumpVisitor::visit( EmbracedExpression& node )
{
    DotLink link( this, &node );
    dumpNode( node, "EmbracedExpression" );
}

void ASTDumpVisitor::visit( NamedExpression& node )
{
    DotLink link( this, &node );
    dumpNode( node, "NamedExpression" );
    RecursiveVisitor::visit( node );
}

void ASTDumpVisitor::visit( DirectCallExpression& node )
{
    DotLink link( this, &node );
    dumpNode( node, "DirectCallExpression" );
    RecursiveVisitor::visit( node );
}

void ASTDumpVisitor::visit( MethodCallExpression& node )
{
    DotLink link( this, &node );
    dumpNode( node, "MethodCallExpression" );
    RecursiveVisitor::visit( node );
}

void ASTDumpVisitor::visit( LiteralCallExpression& node )
{
    DotLink link( this, &node );
    dumpNode( node, "LiteralCallExpression" );
    RecursiveVisitor::visit( node );
}

void ASTDumpVisitor::visit( IndirectCallExpression& node )
{
    DotLink link( this, &node );
    dumpNode( node, "IndirectCallExpression" );
    RecursiveVisitor::visit( node );
}

void ASTDumpVisitor::visit( TypeCastingExpression& node )
{
    DotLink link( this, &node );
    dumpNode( node, "TypeCastingExpression" );
    RecursiveVisitor::visit( node );
}

void ASTDumpVisitor::visit( UnaryExpression& node )
{
    DotLink link( this, &node );
    dumpNode( node, "UnaryExpression '" + node.operationTokenString() + "'" );
    RecursiveVisitor::visit( node );
}

void ASTDumpVisitor::visit( BinaryExpression& node )
{
    DotLink link( this, &node );
    dumpNode( node, "BinaryExpression '" + node.operationTokenString() + "'" );
    RecursiveVisitor::visit( node );
}

void ASTDumpVisitor::visit( LetExpression& node )
{
    DotLink link( this, &node );
    dumpNode( node, "LetExpression" );
    RecursiveVisitor::visit( node );
}

void ASTDumpVisitor::visit( ConditionalExpression& node )
{
    DotLink link( this, &node );
    dumpNode( node, "ConditionalExpression" );
    RecursiveVisitor::visit( node );
}

void ASTDumpVisitor::visit( ChooseExpression& node )
{
    DotLink link( this, &node );
    dumpNode( node, "ChooseExpression" );
    RecursiveVisitor::visit( node );
}

void ASTDumpVisitor::visit( UniversalQuantifierExpression& node )
{
    DotLink link( this, &node );
    dumpNode( node, "UniversalQuantifierExpression" );
    RecursiveVisitor::visit( node );
}

void ASTDumpVisitor::visit( ExistentialQuantifierExpression& node )
{
    DotLink link( this, &node );
    dumpNode( node, "ExistentialQuantifierExpression" );
    RecursiveVisitor::visit( node );
}

void ASTDumpVisitor::visit( CardinalityExpression& node )
{
    DotLink link( this, &node );
    dumpNode( node, "CardinalityExpression" );
    RecursiveVisitor::visit( node );
}

void ASTDumpVisitor::visit( SkipRule& node )
{
    DotLink link( this, &node );
    dumpNode( node, "SkipRule" );
    RecursiveVisitor::visit( node );
}

void ASTDumpVisitor::visit( ConditionalRule& node )
{
    DotLink link( this, &node );
    dumpNode( node, "ConditionalRule" );
    RecursiveVisitor::visit( node );
}

void ASTDumpVisitor::visit( CaseRule& node )
{
    DotLink link( this, &node );
    dumpNode( node, "CaseRule" );
    RecursiveVisitor::visit( node );
}

void ASTDumpVisitor::visit( LetRule& node )
{
    DotLink link( this, &node );
    dumpNode( node, "LetRule" );
    RecursiveVisitor::visit( node );
}

void ASTDumpVisitor::visit( LocalRule& node )
{
    DotLink link( this, &node );
    dumpNode( node, "LocalRule" );
    RecursiveVisitor::visit( node );
}

void ASTDumpVisitor::visit( ForallRule& node )
{
    DotLink link( this, &node );
    dumpNode( node, "ForallRule" );
    RecursiveVisitor::visit( node );
}

void ASTDumpVisitor::visit( ChooseRule& node )
{
    DotLink link( this, &node );
    dumpNode( node, "ChooseRule" );
    RecursiveVisitor::visit( node );
}

void ASTDumpVisitor::visit( IterateRule& node )
{
    DotLink link( this, &node );
    dumpNode( node, "IterateRule" );
    RecursiveVisitor::visit( node );
}

void ASTDumpVisitor::visit( BlockRule& node )
{
    DotLink link( this, &node );
    dumpNode( node, "BlockRule" );
    RecursiveVisitor::visit( node );
}

void ASTDumpVisitor::visit( SequenceRule& node )
{
    DotLink link( this, &node );
    dumpNode( node, "SequenceRule" );
    RecursiveVisitor::visit( node );
}

void ASTDumpVisitor::visit( UpdateRule& node )
{
    DotLink link( this, &node );
    dumpNode( node, "UpdateRule" );
    RecursiveVisitor::visit( node );
}

void ASTDumpVisitor::visit( CallRule& node )
{
    DotLink link( this, &node );
    dumpNode( node, "CallRule" );
    RecursiveVisitor::visit( node );
}

void ASTDumpVisitor::visit( UnresolvedType& node )
{
    DotLink link( this, &node );
    dumpNode( node, "UnresolvedType" );
    // omit recursive visiting of node
}

void ASTDumpVisitor::visit( BasicType& node )
{
    DotLink link( this, &node );
    dumpNode( node, "BasicType" );
    RecursiveVisitor::visit( node );
}

void ASTDumpVisitor::visit( TupleType& node )
{
    DotLink link( this, &node );
    dumpNode( node, "TupleType" );
    RecursiveVisitor::visit( node );
}

void ASTDumpVisitor::visit( RecordType& node )
{
    DotLink link( this, &node );
    dumpNode( node, "RecordType" );
    RecursiveVisitor::visit( node );
}

void ASTDumpVisitor::visit( TemplateType& node )
{
    DotLink link( this, &node );
    dumpNode( node, "TemplateType" );
    RecursiveVisitor::visit( node );
}

void ASTDumpVisitor::visit( FixedSizedType& node )
{
    DotLink link( this, &node );
    dumpNode( node, "FixedSizedType" );
    RecursiveVisitor::visit( node );
}

void ASTDumpVisitor::visit( RelationType& node )
{
    DotLink link( this, &node );
    dumpNode( node, "RelationType" );
    RecursiveVisitor::visit( node );
}

void ASTDumpVisitor::visit( Identifier& node )
{
    DotLink link( this, &node );
    dumpNode( node, node.name() );
    RecursiveVisitor::visit( node );
}

void ASTDumpVisitor::visit( IdentifierPath& node )
{
    DotLink link( this, &node );
    dumpNode( node, "IdentifierPath\n" );
    RecursiveVisitor::visit( node );
}

void ASTDumpVisitor::visit( ExpressionCase& node )
{
    DotLink link( this, &node );
    dumpNode( node, "ExpressionCase" );
    RecursiveVisitor::visit( node );
}

void ASTDumpVisitor::visit( DefaultCase& node )
{
    DotLink link( this, &node );
    dumpNode( node, "DefaultCase" );
    RecursiveVisitor::visit( node );
}

void ASTDumpVisitor::visit( VariableBinding& node )
{
    DotLink link( this, &node );
    dumpNode( node, "VariableBinding" );
    RecursiveVisitor::visit( node );
}

void ASTDumpVisitor::dumpNode( const Node& node, const std::string& name )
{
    m_stream << "\"" << &node << "\" [label=\"" << name;

    dumpLabel( node );

    m_stream << "\"];\n";
}

void ASTDumpVisitor::dumpNode( const TypedNode& node, const std::string& name )
{
    m_stream << "\"" << &node << "\" [label=\"" << name;

    dumpLabel( node );

    m_stream << "\"];\n";
}

void ASTDumpVisitor::dumpNode( const TypedPropertyNode& node, const std::string& name )
{
    m_stream << "\"" << &node << "\" [label=\"" << name;

    dumpLabel( node );

    m_stream << "\"];\n";
}

void ASTDumpVisitor::dumpNode( const TargetCallExpression& node, const std::string& name )
{
    m_stream << "\"" << &node << "\" [label=\"" << name;

    dumpLabel( node );

    m_stream << "\"];\n";
}

void ASTDumpVisitor::dumpLabel( const Node& node )
{
    if( m_dumpNodeLocation )
    {
        m_stream << "\n" << node.sourceLocation();
    }
}

void ASTDumpVisitor::dumpLabel( const TypedNode& node )
{
    dumpLabel( static_cast< const Node& >( node ) );

    if( true )  // m_dumpType
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

void ASTDumpVisitor::dumpLabel( const TypedPropertyNode& node )
{
    dumpLabel( static_cast< const TypedNode& >( node ) );

    if( true )  // m_dumpProperties
    {
        m_stream << " { ";

        if( node.properties().isSet( libcasm_ir::Property::SIDE_EFFECT_FREE ) )
        {
            m_stream << "S ";
        }
        if( node.properties().isSet( libcasm_ir::Property::PURE ) )
        {
            m_stream << "P ";
        }

        m_stream << "}";
    }
}

void ASTDumpVisitor::dumpLabel( const TargetCallExpression& node )
{
    m_stream << "\n";

    if( node.hasTargetDefinition() )
    {
        const auto& targetDefinition = node.targetDefinition();
        m_stream << "[" << targetDefinition->description() << "] "
                 << targetDefinition->identifier()->name() << ": ";

        if( targetDefinition->type() )
        {
            m_stream << targetDefinition->type()->description();
        }
        else
        {
            m_stream << "UNRESOLVED";
        }
    }
    else
    {
        m_stream << "[ UNRESOLVED ] UNRESOLVED: UNRESOLVED";
    }

    dumpLabel( static_cast< const TypedPropertyNode& >( node ) );
}

void ASTDumpVisitor::dumpLink( void* from, void* to )
{
    m_stream << "\"" << from << "\" -> \"" << to << "\";\n";
}

void AstDumpPass::usage( libpass::PassUsage& pu )
{
    pu.require< CstToAstPass >();
    pu.repeatUntil< ConsistencyCheckPass >();
}

u1 AstDumpPass::run( libpass::PassResult& pr )
{
    Logger log( &id, stream() );

    const auto& data = pr.output< CstToAstPass >();
    const auto& specification = data->specification();

    const u1 dumpNodeLocation = true;  // TODO: add command-line switch

    const auto printDotGraph = [&]( std::ostream& out ) {
        ASTDumpVisitor visitor{ out, specification->name(), specification->location()->toString() };
        visitor.setDumpNodeLocation( dumpNodeLocation );
        specification->ast()->accept( visitor );
    };

    if( outputPath() == "" )
    {
        log.debug( "writing dot graph to 'stdout'" );
        printDotGraph( std::cout );
    }
    else
    {
        const auto previousPass = libpass::PassRegistry::passInfo( pr.previousPass() );
        const std::string outputFile = specification->name() + "." + previousPass.name() + ".dot";

        if( not libstdhl::File::Path::exists( outputPath() ) )
        {
            try
            {
                libstdhl::File::Path::create( outputPath() );
            }
            catch( const std::domain_error& e )
            {
                log.error( e.what() );
            }
        }

        const auto outputFilePath = outputPath() + "/" + outputFile;

        std::ofstream dotFile( outputFilePath );
        if( not dotFile.is_open() )
        {
            log.error( "could not open '" + outputFilePath + "'" );
            return false;
        }

        log.debug( "writing dot graph to '" + outputFilePath + "'" );
        printDotGraph( dotFile );
    }

    return true;
}

void AstDumpPass::setOutputPath( const std::string& outputPath )
{
    m_outputPath = outputPath;
}

const std::string& AstDumpPass::outputPath( void ) const
{
    return m_outputPath;
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
