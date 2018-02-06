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

#include "PropertyRevisePass.h"

#include <libcasm-fe/Logger>
#include <libcasm-fe/Namespace>
#include <libcasm-fe/Specification>
#include <libcasm-fe/ast/RecursiveVisitor>

#include <libcasm-fe/analyze/PropertyResolverPass>
#include <libcasm-fe/transform/SourceToAstPass>

#include <libcasm-ir/Annotation>

#include <libpass/PassRegistry>
#include <libpass/PassResult>
#include <libpass/PassUsage>

using namespace libcasm_fe;
using namespace Ast;

char PropertyRevisePass::id = 0;

static libpass::PassRegistration< PropertyRevisePass > PASS(
    "ASTPropertyRevisePass",
    "property revise (checking) of AST representation",
    "ast-prop-rev",
    0 );

class PropertyReviseVisitor final : public RecursiveVisitor
{
  public:
    PropertyReviseVisitor( libcasm_fe::Logger& log );

    void visit( DerivedDefinition& node ) override;

    void visit( BasicType& node ) override;
    void visit( ComposedType& node ) override;
    void visit( TemplateType& node ) override;
    void visit( FixedSizedType& node ) override;
    void visit( RelationType& node ) override;

  private:
    void revise( Ast::Type& node );

  private:
    libcasm_fe::Logger& m_log;
};

//
//
// PropertyReviseVisitor
//

PropertyReviseVisitor::PropertyReviseVisitor( libcasm_fe::Logger& log )
: m_log( log )
{
}

void PropertyReviseVisitor::visit( DerivedDefinition& node )
{
    RecursiveVisitor::visit( node );

    const auto& expressionProperties = node.expression()->properties();

    node.properties().foreach( [&]( const libcasm_ir::Property property ) -> u1 {
        if( not expressionProperties.isSet( property ) )
        {
            m_log.error(
                { node.sourceLocation() },
                "expression of " + node.description() + " '" + node.identifier()->name() +
                    "' violates '" + libcasm_ir::PropertyInfo::toString( property ) + "' property",
                Code::TypeInvalidProperty );
        }
        return true;
    } );
}

void PropertyReviseVisitor::visit( BasicType& node )
{
    RecursiveVisitor::visit( node );
}
void PropertyReviseVisitor::visit( ComposedType& node )
{
    RecursiveVisitor::visit( node );
}
void PropertyReviseVisitor::visit( TemplateType& node )
{
    RecursiveVisitor::visit( node );
}
void PropertyReviseVisitor::visit( FixedSizedType& node )
{
    RecursiveVisitor::visit( node );
}
void PropertyReviseVisitor::visit( RelationType& node )
{
    RecursiveVisitor::visit( node );
}

void PropertyReviseVisitor::revise( Ast::Type& node )
{
    const auto properties = libcasm_ir::Properties{ libcasm_ir::Property::SIDE_EFFECT_FREE,
                                                    libcasm_ir::Property::PURE };

    properties.foreach( [&]( const libcasm_ir::Property property ) -> u1 {
        if( not node.properties().isSet( property ) )
        {
            m_log.error(
                { node.sourceLocation() },
                "type violates '" + libcasm_ir::PropertyInfo::toString( property ) + "' property",
                Code::TypeInvalidProperty );
        }
        return true;
    } );
}

//
//
// PropertyRevisePass
//

void PropertyRevisePass::usage( libpass::PassUsage& pu )
{
    pu.require< SourceToAstPass >();
    pu.scheduleAfter< PropertyResolverPass >();
}

u1 PropertyRevisePass::run( libpass::PassResult& pr )
{
    libcasm_fe::Logger log( &id, stream() );

    const auto data = pr.output< SourceToAstPass >();
    const auto specification = data->specification();

    PropertyReviseVisitor visitor( log );
    specification->definitions()->accept( visitor );

    const auto errors = log.errors();
    if( errors > 0 )
    {
        log.debug( "found %lu error(s) during property resolving", errors );
        return false;
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
