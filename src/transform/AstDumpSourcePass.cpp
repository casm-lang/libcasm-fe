//
//  Copyright (C) 2014-2018 CASM Organization <https://casm-lang.org>
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

#include "AstDumpSourcePass.h"

#include "../various/GrammarToken.h"

#include <libcasm-fe/Logger>
#include <libcasm-fe/Namespace>
#include <libcasm-fe/Specification>
#include <libcasm-fe/ast/RecursiveVisitor>

#include <libcasm-fe/analyze/ConsistencyCheckPass>
#include <libcasm-fe/transform/SourceToAstPass>

#include <libpass/PassRegistry>
#include <libpass/PassResult>
#include <libpass/PassUsage>

#include <iostream>

using namespace libcasm_fe;
using namespace Ast;

namespace ir = libcasm_ir;

char AstDumpSourcePass::id = 0;

static libpass::PassRegistration< AstDumpSourcePass > PASS(
    "AstDumpSourcePass",
    "outputs the parsed AST as a CASM input specification to stdout",
    "ast-dump",
    0 );

class AstDumpSourceVisitor final : public RecursiveVisitor
{
  public:
    explicit AstDumpSourceVisitor( std::ostream& stream );

    void visit( InitDefinition& node ) override;
    void visit( UndefLiteral& node ) override;
    void visit( ValueLiteral& node ) override;
    void visit( UnresolvedType& node ) override;
    void visit( Identifier& node ) override;
    void visit( Token& node ) override;

  private:
    std::ostream& m_stream;
};

AstDumpSourceVisitor::AstDumpSourceVisitor( std::ostream& stream )
: m_stream( stream )
{
}

void AstDumpSourceVisitor::visit( InitDefinition& node )
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

void AstDumpSourceVisitor::visit( UndefLiteral& node )
{
    m_stream << "undef";
}

void AstDumpSourceVisitor::visit( ValueLiteral& node )
{
    const auto value_is_string = node.value()->type().isString();

    if( value_is_string )
    {
        m_stream << "\"";
    }
    m_stream << node.value()->name();

    if( value_is_string )
    {
        m_stream << "\"";
    }
    m_stream << " ";  // TODO: FIXME: @ppaulweber: remove this when spans (space etc.) are ready
}

void AstDumpSourceVisitor::visit( UnresolvedType& node )
{
}

void AstDumpSourceVisitor::visit( Identifier& node )
{
    node.doubleColon()->accept( *this );
    m_stream << node.name();
    m_stream << " ";  // TODO: FIXME: @ppaulweber: remove this when spans (space etc.) are ready
}

void AstDumpSourceVisitor::visit( Token& node )
{
    if( node.token() == Grammar::Token::UNRESOLVED )
    {
        return;
    }
    m_stream << node.tokenString();
    m_stream << " ";  // TODO: FIXME: @ppaulweber: remove this when spans (space etc.) are ready
}

void AstDumpSourcePass::usage( libpass::PassUsage& pu )
{
    pu.require< SourceToAstPass >();
    pu.scheduleAfter< ConsistencyCheckPass >();
}

u1 AstDumpSourcePass::run( libpass::PassResult& pr )
{
    Logger log( &id, stream() );

    const auto& data = pr.output< SourceToAstPass >();
    const auto& specification = data->specification();

    auto& outputStream = std::cout;

    AstDumpSourceVisitor visitor{ outputStream };

    specification->header()->accept( visitor );
    specification->definitions()->accept( visitor );
    outputStream << "\n";  // TODO: FIXME: @ppaulweber: remove this when spans (space etc.) are ready

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
