//
//  Copyright (C) 2014-2021 CASM Organization <https://casm-lang.org>
//  All rights reserved.
//
//  Developed by: Philipp Paulweber
//                Emmanuel Pescosta
//                Jakob Moosbrugger
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

#include "SourceToAstPass.h"

#include <libcasm-fe/Logger>
#include <libcasm-fe/Namespace>
#include <libcasm-fe/Specification>
#include <libcasm-fe/TypeInfo>
#include <libcasm-fe/analyze/ProjectResolverPass>
#include <libcasm-fe/transform/SourceToAstPass>

#include <libpass/PassRegistry>

#include "../Lexer.h"
#include "../various/GrammarParser.tab.h"
#include "../various/GrammarToken.h"

using namespace libcasm_fe;

char SourceToAstPass::id = 0;

static libpass::PassRegistration< SourceToAstPass > PASS(
    "SourceToAstPass", "parse the source code and generate an AST", "ast-parse", 0 );

static void loadBuiltinDefinitions( const Specification::Ptr& specification );

void SourceToAstPass::usage( libpass::PassUsage& pu )
{
    pu.require< ProjectResolverPass >();
}

u1 SourceToAstPass::run( libpass::PassResult& pr )
{
    libcasm_fe::Logger log( &id, stream() );

    const auto data = pr.output< ProjectResolverPass >();
    const auto project = data->project();
    const auto specificationFile = project->specification();
    const auto specificationFileName = specificationFile->filename();
    auto& specificationFileStream = specificationFile->stream();

    Lexer lexer( log, specificationFileStream, std::cout );
    lexer.setFileName( specificationFileName );

    const auto specification = std::make_shared< Specification >();
    specification->setLocation( std::make_shared< libstdhl::Standard::RFC3986::URI >(
        "file", "/", specificationFileName, "", "" ) );

    Parser parser( log, lexer, *specification );
    parser.set_debug_level( m_debug );

    if( ( parser.parse() != 0 ) or not specification or ( log.errors() > 0 ) )
    {
        log.error( "could not parse '" + specification->location()->toString() + "'" );
        return false;
    }

    if( specification->name() == "CASM" )
    {
        log.debug( "module 'CASM': adding built-ins!" );
        loadBuiltinDefinitions( specification );
    }
    else
    {
        const auto& sourceLocation = specification->header()->sourceLocation();
        const auto casmImport = Ast::make< ImportDefinition >(
            sourceLocation,
            Token::unresolved(),
            IdentifierPath::fromIdentifier( Ast::make< Identifier >( sourceLocation, "CASM" ) ) );
        specification->definitions()->add( casmImport );

        const auto casmUsing = Ast::make< UsingPathDefinition >(
            sourceLocation,
            Token::unresolved(),
            IdentifierPath::fromIdentifier( Ast::make< Identifier >( sourceLocation, "CASM" ) ),
            std::make_shared< Token >( Grammar::Token::DOUBLECOLON ),
            std::make_shared< Token >( Grammar::Token::ASTERIX ) );
        specification->definitions()->add( casmUsing );
    }

    pr.setOutput< SourceToAstPass >( specification );
    return true;
}

void SourceToAstPass::setDebug( u1 enable )
{
    m_debug = enable;
}

static void loadBuiltinDefinitions( const Specification::Ptr& specification )
{
    const auto& srcLoc = specification->header()->sourceLocation();

    //
    //
    // Types
    //

    const auto domainVoid = Ast::make< DomainDefinition >(
        srcLoc,
        Ast::make< BasicType >(
            srcLoc,
            IdentifierPath::fromIdentifier(
                Ast::make< Identifier >( srcLoc, TypeInfo::TYPE_NAME_VOID ) ) ) );
    const auto domainVoidProperties = { libcasm_ir::Property::SIDE_EFFECT_FREE,
                                        libcasm_ir::Property::PURE };
    domainVoid->setProperties( domainVoidProperties );
    domainVoid->setExported( true );
    specification->definitions()->add( domainVoid );

    const auto domainObject = Ast::make< DomainDefinition >(
        srcLoc,
        Ast::make< BasicType >(
            srcLoc,
            IdentifierPath::fromIdentifier(
                Ast::make< Identifier >( srcLoc, TypeInfo::TYPE_NAME_OBJECT ) ) ) );
    const auto domainObjectProperties = { libcasm_ir::Property::SIDE_EFFECT_FREE,
                                          libcasm_ir::Property::PURE };
    domainObject->setProperties( domainObjectProperties );
    domainObject->setExported( true );
    specification->definitions()->add( domainObject );

    const auto domainBoolean = Ast::make< DomainDefinition >(
        srcLoc,
        Ast::make< BasicType >(
            srcLoc,
            IdentifierPath::fromIdentifier(
                Ast::make< Identifier >( srcLoc, TypeInfo::TYPE_NAME_BOOLEAN ) ) ) );
    const auto domainBooleanProperties = { libcasm_ir::Property::SIDE_EFFECT_FREE,
                                           libcasm_ir::Property::PURE };
    domainBoolean->setProperties( domainBooleanProperties );
    domainBoolean->setExported( true );
    specification->definitions()->add( domainBoolean );

    const auto domainInteger = Ast::make< DomainDefinition >(
        srcLoc,
        Ast::make< BasicType >(
            srcLoc,
            IdentifierPath::fromIdentifier(
                Ast::make< Identifier >( srcLoc, TypeInfo::TYPE_NAME_INTEGER ) ) ) );
    const auto domainIntegerProperties = { libcasm_ir::Property::SIDE_EFFECT_FREE,
                                           libcasm_ir::Property::PURE };
    domainInteger->setProperties( domainIntegerProperties );
    domainInteger->setExported( true );
    specification->definitions()->add( domainInteger );

    const auto domainString = Ast::make< DomainDefinition >(
        srcLoc,
        Ast::make< BasicType >(
            srcLoc,
            IdentifierPath::fromIdentifier(
                Ast::make< Identifier >( srcLoc, TypeInfo::TYPE_NAME_STRING ) ) ) );
    const auto domainStringProperties = { libcasm_ir::Property::SIDE_EFFECT_FREE,
                                          libcasm_ir::Property::PURE };
    domainString->setProperties( domainStringProperties );
    domainString->setExported( true );
    specification->definitions()->add( domainString );

    const auto domainRational = Ast::make< DomainDefinition >(
        srcLoc,
        Ast::make< BasicType >(
            srcLoc,
            IdentifierPath::fromIdentifier(
                Ast::make< Identifier >( srcLoc, TypeInfo::TYPE_NAME_RATIONAL ) ) ) );
    const auto domainRationalProperties = { libcasm_ir::Property::SIDE_EFFECT_FREE,
                                            libcasm_ir::Property::PURE };
    domainRational->setProperties( domainRationalProperties );
    domainRational->setExported( true );
    specification->definitions()->add( domainRational );

    const auto domainDecimal = Ast::make< DomainDefinition >(
        srcLoc,
        Ast::make< BasicType >(
            srcLoc,
            IdentifierPath::fromIdentifier(
                Ast::make< Identifier >( srcLoc, TypeInfo::TYPE_NAME_DECIMAL ) ) ) );
    const auto domainDecimalProperties = { libcasm_ir::Property::SIDE_EFFECT_FREE,
                                           libcasm_ir::Property::PURE };
    domainDecimal->setProperties( domainDecimalProperties );
    domainDecimal->setExported( true );
    specification->definitions()->add( domainDecimal );

    const auto domainRangeTypes = Ast::make< Types >( srcLoc );
    domainRangeTypes->add( Ast::make< UnresolvedType >( srcLoc ) );
    const auto domainRange = Ast::make< DomainDefinition >(
        srcLoc,
        Ast::make< TemplateType >(
            srcLoc,
            IdentifierPath::fromIdentifier(
                Ast::make< Identifier >( srcLoc, TypeInfo::TYPE_NAME_RANGE ) ),
            Token::unresolved(),
            domainRangeTypes,
            Token::unresolved() ) );
    const auto domainRangeProperties = { libcasm_ir::Property::SIDE_EFFECT_FREE,
                                         libcasm_ir::Property::PURE };
    domainRange->setProperties( domainRangeProperties );
    domainRange->setExported( true );
    specification->definitions()->add( domainRange );

    const auto domainListTypes = Ast::make< Types >( srcLoc );
    domainListTypes->add( Ast::make< UnresolvedType >( srcLoc ) );
    const auto domainList = Ast::make< DomainDefinition >(
        srcLoc,
        Ast::make< TemplateType >(
            srcLoc,
            IdentifierPath::fromIdentifier(
                Ast::make< Identifier >( srcLoc, TypeInfo::TYPE_NAME_LIST ) ),
            Token::unresolved(),
            domainListTypes,
            Token::unresolved() ) );
    const auto domainListProperties = { libcasm_ir::Property::SIDE_EFFECT_FREE,
                                        libcasm_ir::Property::PURE };
    domainList->setProperties( domainListProperties );
    domainList->setExported( true );
    specification->definitions()->add( domainList );

    // TODO: FIXME: @ppaulweber: feature/set
    // const auto domainSetTypes = Ast::make< Types >( srcLoc );
    // domainSetTypes->add( Ast::make< UnresolvedType >( srcLoc ) );
    // const auto domainSet = Ast::make< DomainDefinition >(
    //     srcLoc,
    //     Ast::make< TemplateType >(
    //         srcLoc,
    //         IdentifierPath::fromIdentifier(
    //             Ast::make< Identifier >( srcLoc, TypeInfo::TYPE_NAME_SET ) ),
    //         Token::unresolved(),
    //         domainSetTypes,
    //         Token::unresolved() ) );
    // const auto domainSetProperties = { libcasm_ir::Property::SIDE_EFFECT_FREE,
    //                                libcasm_ir::Property::PURE };
    // domainSet->setProperties( domainSetProperties );
    // domainSet->setExported( true );
    // specification->definitions()->add( domainSet );

    const auto domainPortTypes = Ast::make< Types >( srcLoc );
    domainPortTypes->add( Ast::make< UnresolvedType >( srcLoc ) );
    const auto domainPort = Ast::make< DomainDefinition >(
        srcLoc,
        Ast::make< TemplateType >(
            srcLoc,
            IdentifierPath::fromIdentifier(
                Ast::make< Identifier >( srcLoc, TypeInfo::TYPE_NAME_PORT ) ),
            Token::unresolved(),
            domainPortTypes,
            Token::unresolved() ) );
    const auto domainPortProperties = { libcasm_ir::Property::SIDE_EFFECT_FREE,
                                        libcasm_ir::Property::PURE };
    domainPort->setProperties( domainPortProperties );
    domainPort->setExported( true );
    specification->definitions()->add( domainPort );

    const auto domainFileTypes = Ast::make< Types >( srcLoc );
    domainFileTypes->add( Ast::make< UnresolvedType >( srcLoc ) );
    const auto domainFile = Ast::make< DomainDefinition >(
        srcLoc,
        Ast::make< TemplateType >(
            srcLoc,
            IdentifierPath::fromIdentifier(
                Ast::make< Identifier >( srcLoc, TypeInfo::TYPE_NAME_FILE ) ),
            Token::unresolved(),
            domainFileTypes,
            Token::unresolved() ) );
    const auto domainFileProperties = { libcasm_ir::Property::SIDE_EFFECT_FREE,
                                        libcasm_ir::Property::PURE };
    domainFile->setProperties( domainFileProperties );
    domainFile->setExported( true );
    specification->definitions()->add( domainFile );

    //
    //
    // Instructions
    //

    const auto print = std::make_shared< BuiltinDefinition >(
        std::make_shared< Identifier >( "PrintInstruction" ),
        libcasm_ir::PrintBuiltin::classid(),
        std::make_shared< libcasm_ir::RelationType >(
            std::make_shared< libcasm_ir::VoidType >(),
            std::vector< libcasm_ir::Type::Ptr >{
                std::make_shared< libcasm_ir::StringType >() } ) );
    const auto printProperties = { libcasm_ir::Property::SIDE_EFFECT_FREE,
                                   libcasm_ir::Property::PURE };
    print->setProperties( printProperties );
    print->setExported( true );
    specification->definitions()->add( print );

    const auto assert = std::make_shared< BuiltinDefinition >(
        std::make_shared< Identifier >( "AssertInstruction" ),
        libcasm_ir::AssertBuiltin::classid(),
        std::make_shared< libcasm_ir::RelationType >(
            std::make_shared< libcasm_ir::VoidType >(),
            std::vector< libcasm_ir::Type::Ptr >{
                std::make_shared< libcasm_ir::BooleanType >() } ) );
    const auto assertProperties = { libcasm_ir::Property::SIDE_EFFECT_FREE,
                                    libcasm_ir::Property::PURE };
    assert->setProperties( assertProperties );
    assert->setExported( true );
    specification->definitions()->add( assert );

    const auto asString = std::make_shared< BuiltinDefinition >(
        std::make_shared< Identifier >( "AsStringInstruction" ),
        libcasm_ir::AsStringBuiltin::classid(),
        std::make_shared< libcasm_ir::RelationType >(
            std::make_shared< libcasm_ir::StringType >(),
            std::vector< libcasm_ir::Type::Ptr >{
                TypeInfo::instance().getType( TypeInfo::TYPE_NAME_OBJECT ) } ) );
    const auto asStringProperties = { libcasm_ir::Property::SIDE_EFFECT_FREE,
                                      libcasm_ir::Property::PURE };
    asString->setProperties( asStringProperties );
    asString->setExported( true );
    specification->definitions()->add( asString );
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
