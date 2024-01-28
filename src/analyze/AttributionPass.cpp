//
//  Copyright (C) 2014-2024 CASM Organization <https://casm-lang.org>
//  All rights reserved.
//
//  Developed by: Philipp Paulweber et al.
//  <https://github.com/casm-lang/libcasm-fe/graphs/contributors>
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

#include "../various/GrammarToken.h"

#include <libcasm-fe/Logger>
#include <libcasm-fe/Namespace>
#include <libcasm-fe/Specification>
#include <libcasm-fe/cst/Declaration>
#include <libcasm-fe/cst/Literal>
#include <libcasm-fe/cst/Visitor>
#include <libcasm-fe/transform/SourceToCstPass>

#include <libpass/PassRegistry>
#include <libpass/PassResult>
#include <libpass/PassUsage>

using namespace libcasm_fe;
using namespace CST;

char AttributionPass::id = 0;

static libpass::PassRegistration< AttributionPass > PASS(
    "Attribution Pass",
    "applies the definition attributes to the CST and performs various attribution checks",
    "cst-attr",
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
static const std::string EXPORT_ATTRIBUTE = "export";
static const std::string ABSTRACT_ATTRIBUTE = "abstract";
static const std::string TEMPLATE_ATTRIBUTE = "template";
static const std::string OPERATOR_ATTRIBUTE = "operator";

// list of allowed basic attribute names
static const std::unordered_set< std::string > VALID_BASIC_ATTRIBUTES = {
    DEPRECATED_ATTRIBUTE,   IN_ATTRIBUTE,       MONITORED_ATTRIBUTE, EXTERNAL_ATTRIBUTE,
    CONTROLLED_ATTRIBUTE,   INTERNAL_ATTRIBUTE, SHARED_ATTRIBUTE,    OUT_ATTRIBUTE,
    STATIC_ATTRIBUTE,       SYMBOLIC_ATTRIBUTE, PURE_ATTRIBUTE,      SYNCHRONOUS_ATTRIBUTE,
    ASYNCHRONOUS_ATTRIBUTE, EXPORT_ATTRIBUTE,   ABSTRACT_ATTRIBUTE,
};

// list of allowed symbol attribute names
static const std::unordered_set< std::string > VALID_SYMBOL_ATTRIBUTES = {
    TEMPLATE_ATTRIBUTE,
};

// list of allowed expression attribute names
static const std::unordered_set< std::string > VALID_EXPRESSION_ATTRIBUTES = {
    OPERATOR_ATTRIBUTE,
    VARIANT_ATTRIBUTE,
    DUMPS_ATTRIBUTE,
};

namespace libcasm_fe
{
    namespace CST
    {
        class DefinitionAttributionVisitor final : public RecursiveVisitor
        {
          public:
            DefinitionAttributionVisitor( libcasm_fe::Logger& log, Definition& definition );

            const std::unordered_set< std::string >& attributeNames( void ) const;
            Grammar::Token operation( void ) const;

            void visit( BasicAttribute& node ) override;
            void visit( SymbolAttribute& node ) override;
            void visit( ExpressionAttribute& node ) override;

          private:
            libcasm_fe::Logger& m_log;
            Definition& m_definition;
            std::unordered_set< std::string > m_attributeNames;
            Grammar::Token m_operation;
        };
    }
}

DefinitionAttributionVisitor::DefinitionAttributionVisitor(
    libcasm_fe::Logger& log, Definition& definition )
: m_log( log )
, m_definition( definition )
, m_attributeNames()
, m_operation( Grammar::Token::UNRESOLVED )
{
}

const std::unordered_set< std::string >& DefinitionAttributionVisitor::attributeNames( void ) const
{
    return m_attributeNames;
}

Grammar::Token DefinitionAttributionVisitor::operation( void ) const
{
    return m_operation;
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

void DefinitionAttributionVisitor::visit( SymbolAttribute& node )
{
    const auto& name = node.identifier()->name();

    // allow only symbol attributes
    if( VALID_SYMBOL_ATTRIBUTES.count( name ) == 0 )
    {
        m_log.error(
            { node.sourceLocation() },
            "'" + name + "' is a unknown " + node.description(),
            Code::AttributionSymbolAttributeUnknown );
        return;
    }

    // template can be used multiple times
    if( name == TEMPLATE_ATTRIBUTE )
    {
        m_definition.templateSymbols()->add( node.symbol() );
        return;
    }

    // each attribute should only be used once
    if( m_attributeNames.count( name ) != 0 )
    {
        m_log.error(
            { node.sourceLocation() },
            node.description() + " " + name + "' has already been used",
            Code::AttributionExpressionAttributeAlreadyUsed );
        return;
    }
    m_attributeNames.insert( node.identifier()->name() );
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

    if( name == OPERATOR_ATTRIBUTE )
    {
        static const std::unordered_map< std::string, Grammar::Token > operationStringToToken = {
            { Grammar::tokenAsString( Grammar::Token::PLUS ), Grammar::Token::PLUS },
            { Grammar::tokenAsString( Grammar::Token::MINUS ), Grammar::Token::MINUS },
            { Grammar::tokenAsString( Grammar::Token::ASTERIX ), Grammar::Token::ASTERIX },
            { Grammar::tokenAsString( Grammar::Token::SLASH ), Grammar::Token::SLASH },
            { Grammar::tokenAsString( Grammar::Token::PERCENT ), Grammar::Token::PERCENT },
            { Grammar::tokenAsString( Grammar::Token::CARET ), Grammar::Token::CARET },
            { Grammar::tokenAsString( Grammar::Token::EQUAL ), Grammar::Token::EQUAL },
            { Grammar::tokenAsString( Grammar::Token::NEQUAL ), Grammar::Token::NEQUAL },
            { Grammar::tokenAsString( Grammar::Token::LESSER ), Grammar::Token::LESSER },
            { Grammar::tokenAsString( Grammar::Token::GREATER ), Grammar::Token::GREATER },
            { Grammar::tokenAsString( Grammar::Token::LESSEQ ), Grammar::Token::LESSEQ },
            { Grammar::tokenAsString( Grammar::Token::GREATEREQ ), Grammar::Token::GREATEREQ },
            { Grammar::tokenAsString( Grammar::Token::OR ), Grammar::Token::OR },
            { Grammar::tokenAsString( Grammar::Token::XOR ), Grammar::Token::XOR },
            { Grammar::tokenAsString( Grammar::Token::AND ), Grammar::Token::AND },
            { Grammar::tokenAsString( Grammar::Token::ARROW ), Grammar::Token::ARROW },
            { Grammar::tokenAsString( Grammar::Token::IMPLIES ), Grammar::Token::IMPLIES },
            { Grammar::tokenAsString( Grammar::Token::NOT ), Grammar::Token::NOT },
        };

        if( node.expression()->id() != Node::ID::VALUE_LITERAL or
            not node.expression()->ptr< ValueLiteral >()->value()->type().isString() )
        {
            m_log.error(
                { node.sourceLocation() },
                "expression attribute '" + name + "' needs a string literal",
                Code::Unspecified );
            return;
        }

        const auto& operationValue = node.expression()->ptr< ValueLiteral >()->toString();
        const auto& operationString = operationValue.substr( 1, operationValue.size() - 2 );
        const auto operation = operationStringToToken.find( operationString );
        if( operation == operationStringToToken.end() )
        {
            m_log.error(
                { node.sourceLocation() },
                "unsupported " + name + " '" + operationString + "' found",
                Code::Unspecified );
            return;
        }

        m_operation = operation->second;
    }
}

namespace libcasm_fe
{
    namespace CST
    {
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
            void visit( ImportDefinition& node ) override;
            void visit( DomainDefinition& node ) override;
            void visit( BuiltinDefinition& node ) override;
            void visit( StructureDefinition& node ) override;
            void visit( BehaviorDefinition& node ) override;
            void visit( ImplementDefinition& node ) override;
            void visit( Declaration& node ) override;

          private:
            libcasm_fe::Logger& m_log;
        };
    }
}

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

    using Classification = FunctionDefinition::Classification;

    const auto& attributeNames = visitor.attributeNames();
    for( const auto& name : attributeNames )
    {
        Classification classification = Classification::UNKNOWN;

        if( name == EXPORT_ATTRIBUTE )
        {
            node.setExported( true );
        }
        else if( name == SYMBOLIC_ATTRIBUTE )
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
        if( name == EXPORT_ATTRIBUTE )
        {
            node.setExported( true );
        }
        else if( name == PURE_ATTRIBUTE )
        {
            node.setProperty( libcasm_ir::Property::PURE );
        }
        else if( name == OPERATOR_ATTRIBUTE )
        {
            node.setOperation( visitor.operation() );
        }
        else
        {
            m_log.error(
                { node.attributes()->sourceLocation() },
                "unsupported " + node.description() + " attribute '" + name + "' found",
                Code::Unspecified );
        }
    }
}

void DefinitionVisitor::visit( RuleDefinition& node )
{
    RecursiveVisitor::visit( node );

    DefinitionAttributionVisitor visitor( m_log, node );
    node.attributes()->accept( visitor );

    const auto& attributeNames = visitor.attributeNames();
    for( const auto& name : attributeNames )
    {
        if( name == EXPORT_ATTRIBUTE )
        {
            node.setExported( true );
        }
        else
        {
            m_log.error(
                { node.attributes()->sourceLocation() },
                "unsupported " + node.description() + " attribute '" + name + "' found",
                Code::Unspecified );
        }
    }
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

    const auto& attributeNames = visitor.attributeNames();
    for( const auto& name : attributeNames )
    {
        if( name == EXPORT_ATTRIBUTE )
        {
            node.setExported( true );

            // pass exported flag to enumerators
            for( const auto& enumerator : *node.enumerators() )
            {
                enumerator->setExported( true );
            }
        }
        else
        {
            m_log.error(
                { node.attributes()->sourceLocation() },
                "unsupported " + node.description() + " attribute '" + name + "' found",
                Code::Unspecified );
        }
    }
}

void DefinitionVisitor::visit( UsingDefinition& node )
{
    RecursiveVisitor::visit( node );

    DefinitionAttributionVisitor visitor( m_log, node );
    node.attributes()->accept( visitor );

    const auto& attributeNames = visitor.attributeNames();
    for( const auto& name : attributeNames )
    {
        if( name == EXPORT_ATTRIBUTE )
        {
            node.setExported( true );
        }
        else
        {
            m_log.error(
                { node.attributes()->sourceLocation() },
                "unsupported " + node.description() + " attribute '" + name + "' found",
                Code::Unspecified );
        }
    }
}

void DefinitionVisitor::visit( ImportDefinition& node )
{
    RecursiveVisitor::visit( node );

    DefinitionAttributionVisitor visitor( m_log, node );
    node.attributes()->accept( visitor );

    const auto& attributeNames = visitor.attributeNames();
    for( const auto& name : attributeNames )
    {
        if( name == EXPORT_ATTRIBUTE )
        {
            node.setExported( true );
        }
        else
        {
            m_log.error(
                { node.attributes()->sourceLocation() },
                "unsupported " + node.description() + " attribute '" + name + "' found",
                Code::Unspecified );
        }
    }
}

void DefinitionVisitor::visit( DomainDefinition& node )
{
    RecursiveVisitor::visit( node );

    DefinitionAttributionVisitor visitor( m_log, node );
    node.attributes()->accept( visitor );

    const auto& attributeNames = visitor.attributeNames();
    for( const auto& name : attributeNames )
    {
        if( name == ABSTRACT_ATTRIBUTE )
        {
            node.setAbstract( true );
        }
        else if( name == EXPORT_ATTRIBUTE )
        {
            node.setExported( true );
        }
        else
        {
            m_log.error(
                { node.attributes()->sourceLocation() },
                "unsupported " + node.description() + " attribute '" + name + "' found",
                Code::Unspecified );
        }
    }
}

void DefinitionVisitor::visit( BuiltinDefinition& node )
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
        else if( name == EXPORT_ATTRIBUTE )
        {
            node.setExported( true );
        }
        else
        {
            m_log.error(
                { node.attributes()->sourceLocation() },
                "unsupported " + node.description() + " attribute '" + name + "' found",
                Code::Unspecified );
        }
    }
}

void DefinitionVisitor::visit( StructureDefinition& node )
{
    RecursiveVisitor::visit( node );

    DefinitionAttributionVisitor visitor( m_log, node );
    node.attributes()->accept( visitor );

    const auto& attributeNames = visitor.attributeNames();
    for( const auto& name : attributeNames )
    {
        if( name == EXPORT_ATTRIBUTE )
        {
            node.setExported( true );
        }
        else
        {
            m_log.error(
                { node.attributes()->sourceLocation() },
                "unsupported " + node.description() + " attribute '" + name + "' found",
                Code::Unspecified );
        }
    }
}

void DefinitionVisitor::visit( BehaviorDefinition& node )
{
    RecursiveVisitor::visit( node );

    DefinitionAttributionVisitor visitor( m_log, node );
    node.attributes()->accept( visitor );

    const auto& attributeNames = visitor.attributeNames();
    for( const auto& name : attributeNames )
    {
        if( name == EXPORT_ATTRIBUTE )
        {
            node.setExported( true );
        }
        else
        {
            m_log.error(
                { node.attributes()->sourceLocation() },
                "unsupported " + node.description() + " attribute '" + name + "' found",
                Code::Unspecified );
        }
    }
}

void DefinitionVisitor::visit( ImplementDefinition& node )
{
    RecursiveVisitor::visit( node );

    DefinitionAttributionVisitor visitor( m_log, node );
    node.attributes()->accept( visitor );

    const auto& attributeNames = visitor.attributeNames();
    for( const auto& name : attributeNames )
    {
        m_log.error(
            { node.attributes()->sourceLocation() },
            "unsupported " + node.description() + " attribute '" + name + "' found",
            Code::Unspecified );
    }
}

void DefinitionVisitor::visit( Declaration& node )
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
        else if( name == OPERATOR_ATTRIBUTE )
        {
            node.setOperation( visitor.operation() );
        }
        else
        {
            m_log.error(
                { node.attributes()->sourceLocation() },
                "unsupported " + node.description() + " attribute '" + name + "' found",
                Code::Unspecified );
        }
    }
}

namespace libcasm_fe
{
    namespace CST
    {
        class HeaderVisitor final : public RecursiveVisitor
        {
          public:
            HeaderVisitor( libcasm_fe::Logger& log, libcasm_fe::Specification& specification );

            void visit( HeaderDefinition& node ) override;

          private:
            libcasm_fe::Logger& m_log;
            libcasm_fe::Specification& m_specification;
        };
    }
}

HeaderVisitor::HeaderVisitor( libcasm_fe::Logger& log, libcasm_fe::Specification& specification )
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
            m_specification.setAsmType( libcasm_fe::Specification::AsmType::SYNCHRONOUS );
        }
        else if( name == ASYNCHRONOUS_ATTRIBUTE )
        {
            m_specification.setAsmType( libcasm_fe::Specification::AsmType::ASYNCHRONOUS );
        }
    }
}

void AttributionPass::usage( libpass::PassUsage& pu )
{
    pu.require< SourceToCstPass >();
}

u1 AttributionPass::run( libpass::PassResult& pr )
{
    libcasm_fe::Logger log( &id, stream() );

    const auto data = pr.output< SourceToCstPass >();
    const auto specification = data->specification();

    DefinitionVisitor definitionVisitor( log );
    specification->cst()->definitions()->accept( definitionVisitor );

    HeaderVisitor headerVisitor( log, *specification );
    specification->cst()->header()->accept( headerVisitor );

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
