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

#include "CstEmitPass.h"

#include "../various/GrammarToken.h"

#include <libcasm-fe/Logger>
#include <libcasm-fe/Namespace>
#include <libcasm-fe/Specification>
#include <libcasm-fe/analyze/ConsistencyCheckPass>
#include <libcasm-fe/cst/Literal>
#include <libcasm-fe/cst/Visitor>
#include <libcasm-fe/transform/SourceToCstPass>

#include <libpass/PassRegistry>
#include <libpass/PassResult>
#include <libpass/PassUsage>

#include <iostream>

using namespace libcasm_fe;
using namespace CST;

char CstEmitPass::id = 0;

static libpass::PassRegistration< CstEmitPass > PASS(
    "CstEmitPass",
    "emits the CASM specification based on the parsed CST and writes it to a specified output path",
    "cst-emit",
    0 );

namespace libcasm_fe
{
    namespace CST
    {
        class CSTDumpSourceVisitor final : public RecursiveVisitor
        {
          public:
            explicit CSTDumpSourceVisitor( std::ostream& stream );

            void visit( BuiltinDefinition& node ) override;
            void visit( DomainDefinition& node ) override;
            void visit( ImportDefinition& node ) override;
            void visit( UsingPathDefinition& node ) override;
            void visit( InitDefinition& node ) override;
            void visit( RuleDefinition& node ) override;

            void visit( EmbracedExpression& node ) override;

            void visit( UndefLiteral& node ) override;
            void visit( ValueLiteral& node ) override;

            void visit( UnresolvedType& node ) override;
            void visit( Identifier& node ) override;
            void visit( Token& node ) override;
            void visit( Span& node ) override;
            void visit( Defined& node ) override;
            void visit( Initially& node ) override;

          private:
            std::ostream& m_stream;
        };
    }
}

CSTDumpSourceVisitor::CSTDumpSourceVisitor( std::ostream& stream )
: m_stream( stream )
{
}

void CSTDumpSourceVisitor::visit( DomainDefinition& node )
{
    // omit domain information
}

void CSTDumpSourceVisitor::visit( BuiltinDefinition& node )
{
    // omit builtin information
}

void CSTDumpSourceVisitor::visit( UsingPathDefinition& node )
{
    if( node.usingToken()->token() == Grammar::Token::UNRESOLVED )
    {
        return;
    }
    RecursiveVisitor::visit( node );
}

void CSTDumpSourceVisitor::visit( ImportDefinition& node )
{
    if( node.importToken()->token() == Grammar::Token::UNRESOLVED )
    {
        return;
    }
    RecursiveVisitor::visit( node );
}

void CSTDumpSourceVisitor::visit( InitDefinition& node )
{
    node.attributes()->accept( *this );
    node.initToken()->accept( *this );
    if( node.isSingleAgent() )
    {
        node.initPath()->accept( *this );
    }
    else
    {
        node.leftBraceToken()->accept( *this );
        node.initializers()->accept( *this );
        node.rightBraceToken()->accept( *this );
    }
}

void CSTDumpSourceVisitor::visit( RuleDefinition& node )
{
    node.attributes()->accept( *this );
    node.ruleToken()->accept( *this );
    node.identifier()->accept( *this );
    node.leftBracketToken()->accept( *this );
    node.arguments()->accept( *this );
    node.rightBracketToken()->accept( *this );
    node.mapsToken()->accept( *this );
    if( node.mapsToken()->token() != Grammar::Token::UNRESOLVED )
    {
        node.returnType()->accept( *this );
    }
    node.assignmentToken()->accept( *this );
    node.rule()->accept( *this );
}

void CSTDumpSourceVisitor::visit( EmbracedExpression& node )
{
    if( node.leftBraceToken()->token() == Grammar::Token::UNRESOLVED )
    {
        return;
    }
    RecursiveVisitor::visit( node );
}

void CSTDumpSourceVisitor::visit( UndefLiteral& node )
{
    RecursiveVisitor::visit( node );
    m_stream << "undef";
}

void CSTDumpSourceVisitor::visit( ValueLiteral& node )
{
    RecursiveVisitor::visit( node );
    m_stream << node.toString();
}

void CSTDumpSourceVisitor::visit( UnresolvedType& node )
{
}

void CSTDumpSourceVisitor::visit( Identifier& node )
{
    RecursiveVisitor::visit( node );
    m_stream << node.name();
}

void CSTDumpSourceVisitor::visit( Token& node )
{
    if( node.token() == Grammar::Token::UNRESOLVED )
    {
        return;
    }
    RecursiveVisitor::visit( node );
    m_stream << node.tokenString();
}

void CSTDumpSourceVisitor::visit( Span& node )
{
    RecursiveVisitor::visit( node );
    m_stream << node.toString();
}

void CSTDumpSourceVisitor::visit( Defined& node )
{
    if( node.definedToken()->token() == Grammar::Token::UNRESOLVED )
    {
        return;
    }
    RecursiveVisitor::visit( node );
}

void CSTDumpSourceVisitor::visit( Initially& node )
{
    if( node.equalToken()->token() == Grammar::Token::UNRESOLVED )
    {
        return;
    }
    RecursiveVisitor::visit( node );
}

//
//
// CstEmitPass
//

void CstEmitPass::usage( libpass::PassUsage& pu )
{
    pu.require< SourceToCstPass >();
    pu.scheduleAfter< ConsistencyCheckPass >();
}

u1 CstEmitPass::run( libpass::PassResult& pr )
{
    Logger log( &id, stream() );

    const auto& data = pr.output< SourceToCstPass >();
    const auto& specification = data->specification();

    auto& outputStream = std::cout;

    CSTDumpSourceVisitor visitor{ outputStream };
    specification->cst()->accept( visitor );

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
