//
//  Copyright (C) 2014-2022 CASM Organization <https://casm-lang.org>
//  All rights reserved.
//
//  Developed by: Philipp Paulweber et al.
//                <https://github.com/casm-lang/libcasm-fe/graphs/contributors>
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

#include "CstDumpPass.h"

#include "../various/GrammarToken.h"

#include <libcasm-fe/Logger>
#include <libcasm-fe/Namespace>
#include <libcasm-fe/Specification>
#include <libcasm-fe/analyze/ConsistencyCheckPass>
#include <libcasm-fe/cst/Declaration>
#include <libcasm-fe/cst/Literal>
#include <libcasm-fe/cst/Visitor>
#include <libcasm-fe/transform/SourceToCstPass>

#include <libpass/PassRegistry>
#include <libpass/PassResult>
#include <libpass/PassUsage>

#include <libstdhl/File>

#include <fstream>
#include <iostream>
#include <stack>

using namespace libcasm_fe;
using namespace CST;

char CstDumpPass::id = 0;

static libpass::PassRegistration< CstDumpPass > PASS(
    "CstDumpPass",
    "generates DOT graph of the CST and dumps to specified output path",
    "cst-dump",
    0 );

namespace libcasm_fe
{
    namespace CST
    {
        class CSTDumpDotVisitor final : public RecursiveVisitor
        {
          private:
            /**
             * @brief RAII dot link
             */
            class DotLink
            {
              public:
                DotLink( CSTDumpDotVisitor* visitor, void* node )
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
                CSTDumpDotVisitor* m_visitor;
            };

          public:
            CSTDumpDotVisitor(
                std::ostream& stream,
                const std::string& name,
                const std::string& location,
                const u1 dumpSpan );

            void setDumpNodeLocation( u1 dumpNodeLocation );

            void visit( Root& node ) override;

            void visit( HeaderDefinition& node ) override;
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

            void visit( AbstractExpression& node ) override;
            void visit( EmbracedExpression& node ) override;
            void visit( NamedExpression& node ) override;
            void visit( MappedExpression& node ) override;
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
            void visit( WhileRule& node ) override;

            void visit( UnresolvedType& node ) override;
            void visit( BasicType& node ) override;
            void visit( TupleType& node ) override;
            void visit( RecordType& node ) override;
            void visit( TemplateType& node ) override;
            void visit( FixedSizedType& node ) override;
            void visit( MappingType& node ) override;
            void visit( VaradicType& node ) override;
            void visit( RelationType& node ) override;

            void visit( BasicAttribute& node ) override;
            void visit( SymbolAttribute& node ) override;
            void visit( ExpressionAttribute& node ) override;

            void visit( Defined& node ) override;
            void visit( Initially& node ) override;

            void visit( Identifier& node ) override;
            void visit( IdentifierPath& node ) override;
            void visit( ExpressionCase& node ) override;
            void visit( DefaultCase& node ) override;
            void visit( VariableBinding& node ) override;
            void visit( Token& node ) override;
            void visit( Span& node ) override;

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
            const u1 m_dumpSpan;
            std::stack< void* > m_parentNodes; /**< holds the parent nodes of DotLink */
            u1 m_dumpNodeLocation = false;     /**< dump node source code location */
        };
    }
}

CSTDumpDotVisitor::CSTDumpDotVisitor(
    std::ostream& stream, const std::string& name, const std::string& location, const u1 dumpSpan )
: m_stream( stream )
, m_name( name )
, m_location( location )
, m_dumpSpan( dumpSpan )
, m_parentNodes()
, m_dumpNodeLocation( false )
{
}

void CSTDumpDotVisitor::setDumpNodeLocation( u1 dumpNodeLocation )
{
    m_dumpNodeLocation = dumpNodeLocation;
}

void CSTDumpDotVisitor::visit( Root& node )
{
    m_stream << "digraph \"CST\" {\n";
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

void CSTDumpDotVisitor::visit( HeaderDefinition& node )
{
    DotLink link( this, &node );
    dumpNode( node, "HeaderDefinition" );
    RecursiveVisitor::visit( node );
}

void CSTDumpDotVisitor::visit( InitDefinition& node )
{
    DotLink link( this, &node );
    dumpNode( node, "InitDefinition" );
    RecursiveVisitor::visit( node );
}

void CSTDumpDotVisitor::visit( VariableDefinition& node )
{
    DotLink link( this, &node );
    dumpNode( node, "VariableDefinition" );
    RecursiveVisitor::visit( node );
}

void CSTDumpDotVisitor::visit( FunctionDefinition& node )
{
    DotLink link( this, &node );
    dumpNode( node, "FunctionDefinition" );
    RecursiveVisitor::visit( node );
}

void CSTDumpDotVisitor::visit( DerivedDefinition& node )
{
    DotLink link( this, &node );
    dumpNode( node, "DerivedDefinition" );
    RecursiveVisitor::visit( node );
}

void CSTDumpDotVisitor::visit( RuleDefinition& node )
{
    DotLink link( this, &node );
    dumpNode( node, "RuleDefinition" );
    RecursiveVisitor::visit( node );
}

void CSTDumpDotVisitor::visit( EnumeratorDefinition& node )
{
    DotLink link( this, &node );
    dumpNode( node, "EnumeratorDefinition" );
    RecursiveVisitor::visit( node );
}

void CSTDumpDotVisitor::visit( EnumerationDefinition& node )
{
    DotLink link( this, &node );
    dumpNode( node, "EnumerationDefinition" );
    RecursiveVisitor::visit( node );
}

void CSTDumpDotVisitor::visit( UsingDefinition& node )
{
    DotLink link( this, &node );
    dumpNode( node, "UsingDefinition" );
    RecursiveVisitor::visit( node );
}

void CSTDumpDotVisitor::visit( UsingPathDefinition& node )
{
    DotLink link( this, &node );
    dumpNode( node, "UsingPathDefinition" );
    RecursiveVisitor::visit( node );
}

void CSTDumpDotVisitor::visit( InvariantDefinition& node )
{
    DotLink link( this, &node );
    dumpNode( node, "InvariantDefinition" );
    RecursiveVisitor::visit( node );
}

void CSTDumpDotVisitor::visit( ImportDefinition& node )
{
    DotLink link( this, &node );
    dumpNode( node, "ImportDefinition" );
    RecursiveVisitor::visit( node );
}

void CSTDumpDotVisitor::visit( DomainDefinition& node )
{
    DotLink link( this, &node );
    dumpNode( node, "DomainDefinition" );
    RecursiveVisitor::visit( node );
}

void CSTDumpDotVisitor::visit( StructureDefinition& node )
{
    DotLink link( this, &node );
    dumpNode( node, "StructureDefinition" );
    RecursiveVisitor::visit( node );
}

void CSTDumpDotVisitor::visit( BehaviorDefinition& node )
{
    DotLink link( this, &node );
    dumpNode( node, "BehaviorDefinition" );
    RecursiveVisitor::visit( node );
}

void CSTDumpDotVisitor::visit( ImplementDefinition& node )
{
    DotLink link( this, &node );
    dumpNode( node, "ImplementDefinition" );
    RecursiveVisitor::visit( node );
}

void CSTDumpDotVisitor::visit( BuiltinDefinition& node )
{
    // TODO: add command-line switch
    DotLink link( this, &node );
    dumpNode( node, "BuiltinDefinition" );
    RecursiveVisitor::visit( node );
}

void CSTDumpDotVisitor::visit( Declaration& node )
{
    DotLink link( this, &node );
    dumpNode( node, "Declaration" );
    RecursiveVisitor::visit( node );
}

void CSTDumpDotVisitor::visit( UndefLiteral& node )
{
    DotLink link( this, &node );
    dumpNode( node, "UndefLiteral" );
    RecursiveVisitor::visit( node );
}

void CSTDumpDotVisitor::visit( ValueLiteral& node )
{
    DotLink link( this, &node );
    dumpNode( node, "ValueLiteral: " + node.value()->name() );
    RecursiveVisitor::visit( node );
}

void CSTDumpDotVisitor::visit( ReferenceLiteral& node )
{
    DotLink link( this, &node );
    dumpNode( node, "ReferenceLiteral" );
    RecursiveVisitor::visit( node );
}

void CSTDumpDotVisitor::visit( SetLiteral& node )
{
    DotLink link( this, &node );
    dumpNode( node, "SetLiteral" );
    RecursiveVisitor::visit( node );
}

void CSTDumpDotVisitor::visit( ListLiteral& node )
{
    DotLink link( this, &node );
    dumpNode( node, "ListLiteral" );
    RecursiveVisitor::visit( node );
}

void CSTDumpDotVisitor::visit( RangeLiteral& node )
{
    DotLink link( this, &node );
    dumpNode( node, "RangeLiteral" );
    RecursiveVisitor::visit( node );
}

void CSTDumpDotVisitor::visit( TupleLiteral& node )
{
    DotLink link( this, &node );
    dumpNode( node, "TupleLiteral" );
    RecursiveVisitor::visit( node );
}

void CSTDumpDotVisitor::visit( RecordLiteral& node )
{
    DotLink link( this, &node );
    dumpNode( node, "RecordLiteral" );
    RecursiveVisitor::visit( node );
}

void CSTDumpDotVisitor::visit( AbstractExpression& node )
{
    DotLink link( this, &node );
    dumpNode( node, "AbstractExpression" );
}

void CSTDumpDotVisitor::visit( EmbracedExpression& node )
{
    DotLink link( this, &node );
    dumpNode( node, "EmbracedExpression" );
}

void CSTDumpDotVisitor::visit( NamedExpression& node )
{
    DotLink link( this, &node );
    dumpNode( node, "NamedExpression" );
    RecursiveVisitor::visit( node );
}

void CSTDumpDotVisitor::visit( MappedExpression& node )
{
    DotLink link( this, &node );
    dumpNode( node, "MappedExpression" );
    RecursiveVisitor::visit( node );
}

void CSTDumpDotVisitor::visit( DirectCallExpression& node )
{
    DotLink link( this, &node );
    dumpNode( node, "DirectCallExpression" );
    RecursiveVisitor::visit( node );
}

void CSTDumpDotVisitor::visit( MethodCallExpression& node )
{
    DotLink link( this, &node );
    dumpNode( node, "MethodCallExpression" );
    RecursiveVisitor::visit( node );
}

void CSTDumpDotVisitor::visit( LiteralCallExpression& node )
{
    DotLink link( this, &node );
    dumpNode( node, "LiteralCallExpression" );
    RecursiveVisitor::visit( node );
}

void CSTDumpDotVisitor::visit( IndirectCallExpression& node )
{
    DotLink link( this, &node );
    dumpNode( node, "IndirectCallExpression" );
    RecursiveVisitor::visit( node );
}

void CSTDumpDotVisitor::visit( TypeCastingExpression& node )
{
    DotLink link( this, &node );
    dumpNode( node, "TypeCastingExpression" );
    RecursiveVisitor::visit( node );
}

void CSTDumpDotVisitor::visit( UnaryExpression& node )
{
    DotLink link( this, &node );
    dumpNode( node, "UnaryExpression '" + node.operationToken()->tokenString() + "'" );
    RecursiveVisitor::visit( node );
}

void CSTDumpDotVisitor::visit( BinaryExpression& node )
{
    DotLink link( this, &node );
    dumpNode( node, "BinaryExpression '" + node.operationToken()->tokenString() + "'" );
    RecursiveVisitor::visit( node );
}

void CSTDumpDotVisitor::visit( LetExpression& node )
{
    DotLink link( this, &node );
    dumpNode( node, "LetExpression" );
    RecursiveVisitor::visit( node );
}

void CSTDumpDotVisitor::visit( ConditionalExpression& node )
{
    DotLink link( this, &node );
    dumpNode( node, "ConditionalExpression" );
    RecursiveVisitor::visit( node );
}

void CSTDumpDotVisitor::visit( ChooseExpression& node )
{
    DotLink link( this, &node );
    dumpNode( node, "ChooseExpression" );
    RecursiveVisitor::visit( node );
}

void CSTDumpDotVisitor::visit( UniversalQuantifierExpression& node )
{
    DotLink link( this, &node );
    dumpNode( node, "UniversalQuantifierExpression" );
    RecursiveVisitor::visit( node );
}

void CSTDumpDotVisitor::visit( ExistentialQuantifierExpression& node )
{
    DotLink link( this, &node );
    dumpNode( node, "ExistentialQuantifierExpression" );
    RecursiveVisitor::visit( node );
}

void CSTDumpDotVisitor::visit( CardinalityExpression& node )
{
    DotLink link( this, &node );
    dumpNode( node, "CardinalityExpression" );
    RecursiveVisitor::visit( node );
}

void CSTDumpDotVisitor::visit( SkipRule& node )
{
    DotLink link( this, &node );
    dumpNode( node, "SkipRule" );
    RecursiveVisitor::visit( node );
}

void CSTDumpDotVisitor::visit( ConditionalRule& node )
{
    DotLink link( this, &node );
    dumpNode( node, "ConditionalRule" );
    RecursiveVisitor::visit( node );
}

void CSTDumpDotVisitor::visit( CaseRule& node )
{
    DotLink link( this, &node );
    dumpNode( node, "CaseRule" );
    RecursiveVisitor::visit( node );
}

void CSTDumpDotVisitor::visit( LetRule& node )
{
    DotLink link( this, &node );
    dumpNode( node, "LetRule" );
    RecursiveVisitor::visit( node );
}

void CSTDumpDotVisitor::visit( LocalRule& node )
{
    DotLink link( this, &node );
    dumpNode( node, "LocalRule" );
    RecursiveVisitor::visit( node );
}

void CSTDumpDotVisitor::visit( ForallRule& node )
{
    DotLink link( this, &node );
    dumpNode( node, "ForallRule" );
    RecursiveVisitor::visit( node );
}

void CSTDumpDotVisitor::visit( ChooseRule& node )
{
    DotLink link( this, &node );
    dumpNode( node, "ChooseRule" );
    RecursiveVisitor::visit( node );
}

void CSTDumpDotVisitor::visit( IterateRule& node )
{
    DotLink link( this, &node );
    dumpNode( node, "IterateRule" );
    RecursiveVisitor::visit( node );
}

void CSTDumpDotVisitor::visit( BlockRule& node )
{
    DotLink link( this, &node );
    dumpNode( node, "BlockRule" );
    RecursiveVisitor::visit( node );
}

void CSTDumpDotVisitor::visit( SequenceRule& node )
{
    DotLink link( this, &node );
    dumpNode( node, "SequenceRule" );
    RecursiveVisitor::visit( node );
}

void CSTDumpDotVisitor::visit( UpdateRule& node )
{
    DotLink link( this, &node );
    dumpNode( node, "UpdateRule" );
    RecursiveVisitor::visit( node );
}

void CSTDumpDotVisitor::visit( CallRule& node )
{
    DotLink link( this, &node );
    dumpNode( node, "CallRule" );
    RecursiveVisitor::visit( node );
}

void CSTDumpDotVisitor::visit( WhileRule& node )
{
    DotLink link( this, &node );
    dumpNode( node, "WhileRule" );
    RecursiveVisitor::visit( node );
}

void CSTDumpDotVisitor::visit( UnresolvedType& node )
{
    DotLink link( this, &node );
    dumpNode( node, "UnresolvedType" );
    // omit recursive visiting of node
}

void CSTDumpDotVisitor::visit( BasicType& node )
{
    DotLink link( this, &node );
    dumpNode( node, "BasicType" );
    RecursiveVisitor::visit( node );
}

void CSTDumpDotVisitor::visit( TupleType& node )
{
    DotLink link( this, &node );
    dumpNode( node, "TupleType" );
    RecursiveVisitor::visit( node );
}

void CSTDumpDotVisitor::visit( RecordType& node )
{
    DotLink link( this, &node );
    dumpNode( node, "RecordType" );
    RecursiveVisitor::visit( node );
}

void CSTDumpDotVisitor::visit( TemplateType& node )
{
    DotLink link( this, &node );
    dumpNode( node, "TemplateType" );
    RecursiveVisitor::visit( node );
}

void CSTDumpDotVisitor::visit( FixedSizedType& node )
{
    DotLink link( this, &node );
    dumpNode( node, "FixedSizedType" );
    RecursiveVisitor::visit( node );
}

void CSTDumpDotVisitor::visit( MappingType& node )
{
    DotLink link( this, &node );
    dumpNode( node, "MappingType" );
    RecursiveVisitor::visit( node );
}

void CSTDumpDotVisitor::visit( VaradicType& node )
{
    DotLink link( this, &node );
    dumpNode( node, "VaradicType" );
    RecursiveVisitor::visit( node );
}

void CSTDumpDotVisitor::visit( RelationType& node )
{
    DotLink link( this, &node );
    dumpNode( node, "RelationType" );
    RecursiveVisitor::visit( node );
}

void CSTDumpDotVisitor::visit( BasicAttribute& node )
{
    DotLink link( this, &node );
    dumpNode( node, "BasicAttribute" );
    RecursiveVisitor::visit( node );
}

void CSTDumpDotVisitor::visit( SymbolAttribute& node )
{
    DotLink link( this, &node );
    dumpNode( node, "SymbolAttribute" );
    RecursiveVisitor::visit( node );
}

void CSTDumpDotVisitor::visit( ExpressionAttribute& node )
{
    DotLink link( this, &node );
    dumpNode( node, "ExpressionAttribute" );
    RecursiveVisitor::visit( node );
}

void CSTDumpDotVisitor::visit( Defined& node )
{
    DotLink link( this, &node );
    dumpNode( node, "Defined" );
    RecursiveVisitor::visit( node );
}

void CSTDumpDotVisitor::visit( Initially& node )
{
    DotLink link( this, &node );
    dumpNode( node, "Initially" );
    RecursiveVisitor::visit( node );
}

void CSTDumpDotVisitor::visit( Identifier& node )
{
    DotLink link( this, &node );
    dumpNode( node, node.name() );
    RecursiveVisitor::visit( node );
}

void CSTDumpDotVisitor::visit( IdentifierPath& node )
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
    name += "\nIdentifierPath";

    dumpNode( node, name );
    RecursiveVisitor::visit( node );
}

void CSTDumpDotVisitor::visit( ExpressionCase& node )
{
    DotLink link( this, &node );
    dumpNode( node, "ExpressionCase" );
    RecursiveVisitor::visit( node );
}

void CSTDumpDotVisitor::visit( DefaultCase& node )
{
    DotLink link( this, &node );
    dumpNode( node, "DefaultCase" );
    RecursiveVisitor::visit( node );
}

void CSTDumpDotVisitor::visit( VariableBinding& node )
{
    DotLink link( this, &node );
    dumpNode( node, "VariableBinding" );
    RecursiveVisitor::visit( node );
}

void CSTDumpDotVisitor::visit( Token& node )
{
    if( node.token() != Grammar::Token::UNRESOLVED )
    {
        DotLink link( this, &node );
        dumpNode( node, "Token\n" + node.tokenString() );
        RecursiveVisitor::visit( node );
    }
}

void CSTDumpDotVisitor::visit( Span& node )
{
    if( m_dumpSpan )
    {
        DotLink link( this, &node );
        dumpNode( node, "Span\n" + node.kindName() + " " + std::to_string( node.length() ) );
        RecursiveVisitor::visit( node );
    }
}

void CSTDumpDotVisitor::dumpNode( const Node& node, const std::string& name )
{
    m_stream << "\"" << &node << "\" [label=\"" << name;

    dumpLabel( node );

    m_stream << "\"";

    if( node.id() == Node::ID::TOKEN )
    {
        m_stream << " shape=box";
    }

    m_stream << "];\n";
}

void CSTDumpDotVisitor::dumpNode( const TypedNode& node, const std::string& name )
{
    m_stream << "\"" << &node << "\" [label=\"" << name;

    dumpLabel( node );

    m_stream << "\"];\n";
}

void CSTDumpDotVisitor::dumpNode( const TypedPropertyNode& node, const std::string& name )
{
    m_stream << "\"" << &node << "\" [label=\"" << name;

    dumpLabel( node );

    m_stream << "\"];\n";
}

void CSTDumpDotVisitor::dumpNode( const TargetCallExpression& node, const std::string& name )
{
    m_stream << "\"" << &node << "\" [label=\"" << name;

    dumpLabel( node );

    m_stream << "\"];\n";
}

void CSTDumpDotVisitor::dumpLabel( const Node& node )
{
    if( m_dumpNodeLocation )
    {
        m_stream << "\n" << node.sourceLocation();
    }
}

void CSTDumpDotVisitor::dumpLabel( const TypedNode& node )
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

void CSTDumpDotVisitor::dumpLabel( const TypedPropertyNode& node )
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

void CSTDumpDotVisitor::dumpLabel( const TargetCallExpression& node )
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

void CSTDumpDotVisitor::dumpLink( void* from, void* to )
{
    m_stream << "\"" << from << "\" -> \"" << to << "\";\n";
}

void CstDumpPass::usage( libpass::PassUsage& pu )
{
    pu.require< SourceToCstPass >();
}

u1 CstDumpPass::run( libpass::PassResult& pr )
{
    Logger log( &id, stream() );

    const auto& data = pr.output< SourceToCstPass >();
    const auto& specification = data->specification();

    const u1 dumpNodeLocation = true;  // TODO: add command-line switch

    const auto printDotGraph = [ & ]( std::ostream& out ) {
        CSTDumpDotVisitor visitor{
            out, specification->name(), specification->location()->toString(), dumpSpan()
        };
        visitor.setDumpNodeLocation( dumpNodeLocation );
        specification->cst()->accept( visitor );
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

void CstDumpPass::setOutputPath( const std::string& outputPath )
{
    m_outputPath = outputPath;
}

const std::string& CstDumpPass::outputPath( void ) const
{
    return m_outputPath;
}

void CstDumpPass::setDumpSpan( const u1 enable )
{
    m_dumpSpan = enable;
}

u1 CstDumpPass::dumpSpan( void ) const
{
    return m_dumpSpan;
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
