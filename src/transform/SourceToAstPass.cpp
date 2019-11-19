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

#include <libcasm-ir/Instruction>

#include <libpass/PassRegistry>

#include "../Lexer.h"
#include "../various/GrammarParser.tab.h"
#include "../various/GrammarToken.h"

using namespace libcasm_fe;

namespace IR = libcasm_ir;

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
    // Domain Types via IR::Types
    //

    const auto domainBasicType = [&specification, &srcLoc]( const std::string& name ) {
        const auto domain = Ast::make< DomainDefinition >(
            srcLoc,
            Ast::make< BasicType >(
                srcLoc,
                IdentifierPath::fromIdentifier( Ast::make< Identifier >( srcLoc, name ) ) ) );
        const auto domainProperties = { IR::Property::SIDE_EFFECT_FREE, IR::Property::PURE };
        domain->setProperties( domainProperties );
        domain->setExported( true );
        specification->definitions()->add( domain );
    };

    const auto domainTemplateType = [&specification, &srcLoc]( const std::string& name ) {
        const auto domainTypes = Ast::make< Types >( srcLoc );
        domainTypes->add( Ast::make< UnresolvedType >( srcLoc ) );
        const auto domain = Ast::make< DomainDefinition >(
            srcLoc,
            Ast::make< TemplateType >(
                srcLoc,
                IdentifierPath::fromIdentifier( Ast::make< Identifier >( srcLoc, name ) ),
                Token::unresolved(),
                domainTypes,
                Token::unresolved() ) );
        const auto domainProperties = { IR::Property::SIDE_EFFECT_FREE, IR::Property::PURE };
        domain->setProperties( domainProperties );
        domain->setExported( true );
        specification->definitions()->add( domain );
    };

    domainBasicType( TypeInfo::TYPE_NAME_VOID );
    domainBasicType( TypeInfo::TYPE_NAME_OBJECT );
    domainBasicType( TypeInfo::TYPE_NAME_ENUMERATION );
    domainBasicType( TypeInfo::TYPE_NAME_BOOLEAN );
    domainBasicType( TypeInfo::TYPE_NAME_INTEGER );
    domainBasicType( TypeInfo::TYPE_NAME_STRING );
    domainBasicType( TypeInfo::TYPE_NAME_RATIONAL );
    domainBasicType( TypeInfo::TYPE_NAME_DECIMAL );

    domainTemplateType( TypeInfo::TYPE_NAME_RANGE );
    domainTemplateType( TypeInfo::TYPE_NAME_LIST );
    // domainTemplateType( TypeInfo::TYPE_NAME_SET );  // TODO: FIXME: @ppaulweber: feature/set
    domainTemplateType( TypeInfo::TYPE_NAME_PORT );
    domainTemplateType( TypeInfo::TYPE_NAME_FILE );

    //
    //
    // Builtin Definitions via IR::Instructions
    //

    const auto& VOID = std::make_shared< IR::VoidType >();
    const auto& BOOLEAN = TypeInfo::instance().getType( TypeInfo::TYPE_NAME_BOOLEAN );
    const auto& INTEGER = TypeInfo::instance().getType( TypeInfo::TYPE_NAME_INTEGER );
    const auto& STRING = TypeInfo::instance().getType( TypeInfo::TYPE_NAME_STRING );
    const auto& OBJECT = TypeInfo::instance().getType( TypeInfo::TYPE_NAME_OBJECT );

    const auto builtin = [&specification, &srcLoc](
                             const std::string& name,
                             const IR::Value::ID id,
                             const IR::Type::Ptr& returnType,
                             const std::vector< IR::Type::Ptr >& argumentTypes ) {
        const auto definition = Ast::make< BuiltinDefinition >(
            srcLoc,
            Ast::make< Identifier >( srcLoc, name ),
            id,
            std::make_shared< IR::RelationType >( returnType, argumentTypes ) );
        const auto definitionProperties = { IR::Property::SIDE_EFFECT_FREE, IR::Property::PURE };
        definition->setProperties( definitionProperties );
        definition->setExported( true );
        specification->definitions()->add( definition );
    };

    builtin( "AbortInstruction", IR::AbortBuiltin::classid(), VOID, {} );
    builtin( "AssertInstruction", IR::AssertBuiltin::classid(), VOID, { BOOLEAN } );
    builtin( "AssureInstruction", IR::AssureBuiltin::classid(), VOID, { BOOLEAN } );
    builtin( "PrintInstruction", IR::PrintBuiltin::classid(), VOID, { STRING } );
    builtin( "NotInstruction", IR::NotInstruction::classid(), BOOLEAN, { BOOLEAN } );
    builtin( "OrInstruction", IR::OrInstruction::classid(), BOOLEAN, { BOOLEAN, BOOLEAN } );
    // builtin( "XorInstruction", IR::XorInstruction::classid(), BOOLEAN, {
    // BOOLEAN, BOOLEAN, } );
    // builtin( "AndInstruction", IR::AndInstruction::classid(), BOOLEAN, {
    // BOOLEAN, BOOLEAN, } );
    // builtin( "ImpInstruction", IR::ImpInstruction::classid(), BOOLEAN, {
    // BOOLEAN, BOOLEAN, } );
    builtin( "ConcatInstruction", IR::AddInstruction::classid(), STRING, { STRING, STRING } );
    builtin( "AddInstruction", IR::AddInstruction::classid(), INTEGER, { INTEGER, INTEGER } );
    builtin( "SubInstruction", IR::SubInstruction::classid(), INTEGER, { INTEGER, INTEGER } );
    builtin( "SizeInstruction", IR::SizeBuiltin::classid(), INTEGER, { OBJECT } );
    builtin( "EquInstruction", IR::EquInstruction::classid(), BOOLEAN, { OBJECT, OBJECT } );
    builtin( "LthInstruction", IR::LthInstruction::classid(), BOOLEAN, { OBJECT, OBJECT } );
    builtin( "GthInstruction", IR::GthInstruction::classid(), BOOLEAN, { OBJECT, OBJECT } );
    builtin( "AsStringInstruction", IR::AsStringBuiltin::classid(), STRING, { OBJECT } );
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
