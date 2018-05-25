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

#include "AttributionPass.h"

#include <libcasm-fe/Logger>
#include <libcasm-fe/Namespace>
#include <libcasm-fe/Specification>
#include <libcasm-fe/ast/RecursiveVisitor>

#include <libcasm-fe/transform/SourceToAstPass>

#include <libpass/PassRegistry>
#include <libpass/PassResult>
#include <libpass/PassUsage>

using namespace libcasm_fe;
using namespace Ast;

char AttributionPass::id = 0;

static libpass::PassRegistration< AttributionPass > PASS(
    "AstAttributionPass",
    "applies the definition attributes to the AST and performs various "
    "attribution checks",
    "ast-attr",
    0 );

// attribute names (case sensitive)
static const std::string DEPRECATED_ATTRIBUTE = "deprecated";
static const std::string IN_ATTRIBUTE = "in";
static const std::string MONITORED_ATTRIBUTE = "monitored";
static const std::string EXTERNAL_ATTRIBUTE = "external";
static const std::string CONTROLLED_ATTRIBUTE = "controlled";
static const std::string INTERNAL_ATTRIBUTE = "internal";
static const std::string SHARED_ATTRIBUTE = "shared";
static const std::string OUT_ATTRIBUTE = "out";
static const std::string STATIC_ATTRIBUTE = "static";
static const std::string VARIANT_ATTRIBUTE = "variant";
static const std::string SYMBOLIC_ATTRIBUTE = "symbolic";
static const std::string DUMPS_ATTRIBUTE = "dumps";
static const std::string PURE_ATTRIBUTE = "pure";
static const std::string SYNCHRONOUS_ATTRIBUTE = "synchronous";
static const std::string ASYNCHRONOUS_ATTRIBUTE = "asynchronous";

// list of allowed basic attribute names
static const std::unordered_set< std::string > VALID_BASIC_ATTRIBUTES = {
    DEPRECATED_ATTRIBUTE,  IN_ATTRIBUTE,       MONITORED_ATTRIBUTE, EXTERNAL_ATTRIBUTE,
    CONTROLLED_ATTRIBUTE,  INTERNAL_ATTRIBUTE, SHARED_ATTRIBUTE,    OUT_ATTRIBUTE,
    STATIC_ATTRIBUTE,      SYMBOLIC_ATTRIBUTE, PURE_ATTRIBUTE,      SYNCHRONOUS_ATTRIBUTE,
    ASYNCHRONOUS_ATTRIBUTE
};

// list of allowed expression attribute names
static const std::unordered_set< std::string > VALID_EXPRESSION_ATTRIBUTES = {
    VARIANT_ATTRIBUTE,
    DUMPS_ATTRIBUTE,
};

class DefinitionAttributionVisitor final : public RecursiveVisitor
{
  public:
    DefinitionAttributionVisitor( libcasm_fe::Logger& log, Definition& definition );

    const std::unordered_set< std::string >& attributeNames() const;

    void visit( BasicAttribute& node ) override;
    void visit( ExpressionAttribute& node ) override;

  private:
    libcasm_fe::Logger& m_log;
    Definition& m_definition;
    std::unordered_set< std::string > m_attributeNames;
};

DefinitionAttributionVisitor::DefinitionAttributionVisitor(
    libcasm_fe::Logger& log, Definition& definition )
: m_log( log )
, m_definition( definition )
, m_attributeNames()
{
}

const std::unordered_set< std::string >& DefinitionAttributionVisitor::attributeNames() const
{
    return m_attributeNames;
}

void DefinitionAttributionVisitor::visit( BasicAttribute& node )
{
    const auto& name = node.identifier()->name();

    // allow only basic attributes
    if( VALID_BASIC_ATTRIBUTES.count( name ) == 0 )
    {
        m_log.error(
            { node.sourceLocation() },
            "'" + name + "' is a unknown basic attribute",
            Code::AttributionBasicAttributeUnknown );
        return;
    }

    // each attribute should only be used once
    if( m_attributeNames.count( name ) != 0 )
    {
        m_log.error(
            { node.sourceLocation() },
            "basic attribute '" + name + "' has already been used",
            Code::AttributionBasicAttributeAlreadyUsed );
        return;
    }
    m_attributeNames.insert( node.identifier()->name() );

    if( name == DEPRECATED_ATTRIBUTE )
    {
        // definition has been deprecated
        m_log.info(
            { m_definition.sourceLocation() },
            m_definition.description() + " `" + m_definition.identifier()->name() +
                "` has been marked as deprecated" );
    }
}

void DefinitionAttributionVisitor::visit( ExpressionAttribute& node )
{
    const auto& name = node.identifier()->name();

    // allow only expression attributes
    if( VALID_EXPRESSION_ATTRIBUTES.count( name ) == 0 )
    {
        m_log.error(
            { node.sourceLocation() },
            "'" + name + "' is a unknown expression attribute",
            Code::AttributionExpressionAttributeUnknown );
        return;
    }

    // each attribute should only be used once
    if( m_attributeNames.count( name ) != 0 )
    {
        m_log.error(
            { node.sourceLocation() },
            "expression attribute '" + name + "' has already been used",
            Code::AttributionExpressionAttributeAlreadyUsed );
        return;
    }
    m_attributeNames.insert( node.identifier()->name() );
}

class DefinitionVisitor final : public RecursiveVisitor
{
  public:
    DefinitionVisitor( libcasm_fe::Logger& log );

    void visit( VariableDefinition& node ) override;
    void visit( FunctionDefinition& node ) override;
    void visit( DerivedDefinition& node ) override;
    void visit( RuleDefinition& node ) override;
    void visit( EnumeratorDefinition& node ) override;
    void visit( EnumerationDefinition& node ) override;
    void visit( UsingDefinition& node ) override;

  private:
    libcasm_fe::Logger& m_log;
};

DefinitionVisitor::DefinitionVisitor( libcasm_fe::Logger& log )
: m_log( log )
{
}

void DefinitionVisitor::visit( VariableDefinition& node )
{
    RecursiveVisitor::visit( node );

    DefinitionAttributionVisitor visitor{ m_log, node };
    node.attributes()->accept( visitor );
}

void DefinitionVisitor::visit( FunctionDefinition& node )
{
    RecursiveVisitor::visit( node );

    DefinitionAttributionVisitor visitor{ m_log, node };
    node.attributes()->accept( visitor );
    const auto& attributeNames = visitor.attributeNames();

    using Classification = FunctionDefinition::Classification;

    for( const auto& name : attributeNames )
    {
        Classification classification = Classification::UNKNOWN;

        if( name == SYMBOLIC_ATTRIBUTE )
        {
            node.setSymbolic( true );
        }
        else if( name == IN_ATTRIBUTE or name == MONITORED_ATTRIBUTE or name == EXTERNAL_ATTRIBUTE )
        {
            classification = Classification::IN;
        }
        else if( name == CONTROLLED_ATTRIBUTE or name == INTERNAL_ATTRIBUTE )
        {
            classification = Classification::CONTROLLED;
        }
        else if( name == SHARED_ATTRIBUTE )
        {
            classification = Classification::SHARED;
        }
        else if( name == OUT_ATTRIBUTE )
        {
            classification = Classification::OUT;
        }
        else if( name == STATIC_ATTRIBUTE )
        {
            classification = Classification::STATIC;
        }

        if( classification != Classification::UNKNOWN )
        {
            if( node.classification() != Classification::UNKNOWN )
            {
                m_log.error(
                    { node.attributes()->sourceLocation() },
                    "function '" + node.identifier()->name() + "' classified as '" +
                        node.classificationName() + "' cannot be re-classified as '" +
                        FunctionDefinition::toString( classification ) + "'",
                    Code::FunctionDefinitionReClassification );
            }
            else
            {
                node.setClassification( classification );
            }
        }
    }

    // ensure controlled classification if classification is unknown!
    if( node.classification() == Classification::UNKNOWN )
    {
        // if function classification is provided, all ASM functions are controlled by default
        node.setClassification( Classification::CONTROLLED );
    }

    // set classification specific properties
    if( node.classification() == FunctionDefinition::Classification::STATIC )
    {
        node.setProperty( libcasm_ir::Property::PURE );
    }
}

void DefinitionVisitor::visit( DerivedDefinition& node )
{
    RecursiveVisitor::visit( node );

    DefinitionAttributionVisitor visitor( m_log, node );
    node.attributes()->accept( visitor );
    const auto& attributeNames = visitor.attributeNames();

    for( const auto& name : attributeNames )
    {
        if( name == PURE_ATTRIBUTE )
        {
            node.setProperty( libcasm_ir::Property::PURE );
        }
    }
}

void DefinitionVisitor::visit( RuleDefinition& node )
{
    RecursiveVisitor::visit( node );

    DefinitionAttributionVisitor visitor( m_log, node );
    node.attributes()->accept( visitor );
}

void DefinitionVisitor::visit( EnumeratorDefinition& node )
{
    RecursiveVisitor::visit( node );

    DefinitionAttributionVisitor visitor( m_log, node );
    node.attributes()->accept( visitor );
}

void DefinitionVisitor::visit( EnumerationDefinition& node )
{
    RecursiveVisitor::visit( node );

    DefinitionAttributionVisitor visitor( m_log, node );
    node.attributes()->accept( visitor );
}

void DefinitionVisitor::visit( UsingDefinition& node )
{
    RecursiveVisitor::visit( node );

    DefinitionAttributionVisitor visitor( m_log, node );
    node.attributes()->accept( visitor );
}

class HeaderVisitor final : public RecursiveVisitor
{
  public:
    HeaderVisitor( libcasm_fe::Logger& log, Specification& specification );

    void visit( HeaderDefinition& node ) override;

  private:
    libcasm_fe::Logger& m_log;
    Specification& m_specification;
};

HeaderVisitor::HeaderVisitor( libcasm_fe::Logger& log, Specification& specification )
: m_log( log )
, m_specification( specification )
{
}

void HeaderVisitor::visit( HeaderDefinition& node )
{
    RecursiveVisitor::visit( node );

    DefinitionAttributionVisitor visitor{ m_log, node };
    node.attributes()->accept( visitor );
    const auto& attributeNames = visitor.attributeNames();

    for( const auto& name : attributeNames )
    {
        if( name == SYNCHRONOUS_ATTRIBUTE )
        {
            m_specification.setAsmType( Specification::AsmType::SYNCHRONOUS );
        }
        else if( name == ASYNCHRONOUS_ATTRIBUTE )
        {
            m_specification.setAsmType( Specification::AsmType::ASYNCHRONOUS );
        }
    }
}

void AttributionPass::usage( libpass::PassUsage& pu )
{
    pu.require< SourceToAstPass >();
}

u1 AttributionPass::run( libpass::PassResult& pr )
{
    libcasm_fe::Logger log( &id, stream() );

    const auto data = pr.output< SourceToAstPass >();
    const auto specification = data->specification();

    DefinitionVisitor definitionVisitor( log );
    specification->definitions()->accept( definitionVisitor );

    HeaderVisitor headerVisitor( log, *specification );
    specification->header()->accept( headerVisitor );

    const auto errors = log.errors();
    if( errors > 0 )
    {
        log.debug( "found %lu error(s) during attribution", errors );
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
