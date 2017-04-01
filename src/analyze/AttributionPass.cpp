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

#include "AttributionPass.h"

#include <unordered_set>

#include "../Logger.h"
#include "../ast/RecursiveVisitor.h"
#include "../ast/Specification.h"

using namespace libcasm_fe;
using namespace Ast;

char AttributionPass::id = 0;

static libpass::PassRegistration< AttributionPass > PASS( "AstAttributionPass",
    "applies the definition attributes to the AST and performs various "
    "attribution checks",
    "ast-attr", 0 );

// attribute names (case sensitive)
static const std::string DEPRECATED_ATTRIBUTE = "deprecated";
static const std::string IN_ATTRIBUTE = "in";
static const std::string MONITORED_ATTRIBUTE = "monitored";
static const std::string CONTROLLED_ATTRIBUTE = "controlled";
static const std::string SHARED_ATTRIBUTE = "shared";
static const std::string OUT_ATTRIBUTE = "out";
static const std::string STATIC_ATTRIBUTE = "static";
static const std::string VARIANT_ATTRIBUTE = "variant";
static const std::string SYMBOLIC_ATTRIBUTE = "symbolic";

// list of allowed basic attribute names
static const std::unordered_set< std::string > VALID_BASIC_ATTRIBUTES = {
    DEPRECATED_ATTRIBUTE,
    IN_ATTRIBUTE,
    MONITORED_ATTRIBUTE,
    CONTROLLED_ATTRIBUTE,
    SHARED_ATTRIBUTE,
    OUT_ATTRIBUTE,
    STATIC_ATTRIBUTE,
    SYMBOLIC_ATTRIBUTE,
};

// list of allowed expression attribute names
static const std::unordered_set< std::string > VALID_EXPRESSION_ATTRIBUTES = {
    VARIANT_ATTRIBUTE,
};

class DefinitionAttributionVisitor final : public RecursiveVisitor
{
  public:
    DefinitionAttributionVisitor( Logger& log, Definition& definition );

    const std::unordered_set< std::string >& attributeNames() const;

    void visit( BasicAttribute& node ) override;
    void visit( ExpressionAttribute& node ) override;

  private:
    Logger& log;
    Definition& m_definition;
    std::unordered_set< std::string > m_attributeNames;
};

DefinitionAttributionVisitor::DefinitionAttributionVisitor(
    Logger& log, Definition& definition )
: log( log )
, m_definition( definition )
, m_attributeNames()
{
}

const std::unordered_set< std::string >&
DefinitionAttributionVisitor::attributeNames() const
{
    return m_attributeNames;
}

void DefinitionAttributionVisitor::visit( BasicAttribute& node )
{
    const auto& name = node.identifier()->identifier();

    // allow only basic attributes
    if( VALID_BASIC_ATTRIBUTES.count( name ) == 0 )
    {
        log.error( {node.sourceLocation()}, "`" + name +
            "` is a unknown basic attribute" );
        return;
    }

    // each attribute should only be used once
    if( m_attributeNames.count( name ) != 0 )
    {
        log.error( {node.sourceLocation()}, "attribute `" + name +
            "` has already been used" );
        return;
    }
    m_attributeNames.insert( node.identifier()->identifier() );

    if( name == DEPRECATED_ATTRIBUTE )
    {
        // definition has been deprecated
        log.info( {m_definition.sourceLocation()}, m_definition.name() + " `" +
            m_definition.identifier()->identifier() +
            "` has been marked as deprecated" );
    }
}

void DefinitionAttributionVisitor::visit( ExpressionAttribute& node )
{
    const auto& name = node.identifier()->identifier();

    // allow only expression attributes
    if( VALID_EXPRESSION_ATTRIBUTES.count( name ) == 0 )
    {
        log.error( {node.sourceLocation()}, "`" + name +
            "` is a unknown expression attribute" );
        return;
    }

    // each attribute should only be used once
    if( m_attributeNames.count( name ) != 0 )
    {
        log.error( {node.sourceLocation()}, "attribute `" + name +
            "` has already been used" );
        return;
    }
    m_attributeNames.insert( node.identifier()->identifier() );
}

class DefinitionVisitor final : public RecursiveVisitor
{
  public:
    DefinitionVisitor( Logger& log );

    void visit( VariableDefinition& node ) override;
    void visit( FunctionDefinition& node ) override;
    void visit( DerivedDefinition& node ) override;
    void visit( RuleDefinition& node ) override;
    void visit( EnumerationDefinition& node ) override;

  private:
    Logger& log;
};

DefinitionVisitor::DefinitionVisitor( Logger& log )
: log( log )
{
}

void DefinitionVisitor::visit( VariableDefinition& node )
{
    DefinitionAttributionVisitor visitor{ log, node };
    node.attributes()->accept( visitor );
}

void DefinitionVisitor::visit( FunctionDefinition& node )
{
    DefinitionAttributionVisitor visitor{ log, node };
    node.attributes()->accept( visitor );

    const auto& attributeNames = visitor.attributeNames();

    for( const auto& name : attributeNames )
    {
        using Classification = FunctionDefinition::Classification;

        if( name == SYMBOLIC_ATTRIBUTE )
        {
            node.setSymbolic( true );
        }
        else if( name == IN_ATTRIBUTE or name == MONITORED_ATTRIBUTE )
        {
            node.setClassification( Classification::IN );
        }
        else if( name == CONTROLLED_ATTRIBUTE )
        {
            node.setClassification( Classification::CONTROLLED );
        }
        else if( name == SHARED_ATTRIBUTE )
        {
            node.setClassification( Classification::SHARED );
        }
        else if( name == OUT_ATTRIBUTE )
        {
            node.setClassification( Classification::OUT );
        }
        else if( name == STATIC_ATTRIBUTE )
        {
            node.setClassification( Classification::STATIC );
        }
    }
}

void DefinitionVisitor::visit( DerivedDefinition& node )
{
    DefinitionAttributionVisitor visitor{ log, node };
    node.attributes()->accept( visitor );
}

void DefinitionVisitor::visit( RuleDefinition& node )
{
    DefinitionAttributionVisitor visitor{ log, node };
    node.attributes()->accept( visitor );
}

void DefinitionVisitor::visit( EnumerationDefinition& node )
{
    DefinitionAttributionVisitor visitor{ log, node };
    node.attributes()->accept( visitor );
}

void AttributionPass::usage( libpass::PassUsage& pu )
{
    pu.require< SourceToAstPass >();
}

u1 AttributionPass::run( libpass::PassResult& pr )
{
    Logger log( &id, stream() );

    const auto sourceToAstPass = pr.result< SourceToAstPass >();
    const auto specification = sourceToAstPass->specification();

    DefinitionVisitor visitor{ log };
    specification->accept( visitor );

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
