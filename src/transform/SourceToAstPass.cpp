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

#include "SourceToAstPass.h"

#include <fstream>
#include <iostream>

#include "../Lexer.h"
#include "../various/GrammarParser.tab.h"

using namespace libcasm_fe;

char SourceToAstPass::id = 0;

static libpass::PassRegistration< SourceToAstPass > PASS( "SourceToAstPass",
    "parse the source code and generate an AST", "ast-parse", 0 );

void SourceToAstPass::usage( libpass::PassUsage& pu )
{
    pu.require< libpass::LoadFilePass >();
}

u1 SourceToAstPass::run( libpass::PassResult& pr )
{
    const auto loadFilePass = pr.result< libpass::LoadFilePass >();
    const auto filePath = std::string(
        loadFilePass->filename() ); // TODO char* -> string in load pass

    std::ifstream sourceFile( filePath );
    if( not sourceFile.is_open() )
    {
        std::cerr << "error: could not open `" << filePath << "´" << std::endl;
        return false;
    }

    const std::string& fileName
        = filePath.substr( filePath.find_last_of( "/\\" ) + 1 );
    const std::string& specificationName
        = fileName.substr( 0, fileName.rfind( "." ) );

    Ast::Specification::Ptr specification;

    Lexer lexer( sourceFile, std::cout );
    Parser parser( lexer, specificationName, specification );
    parser.set_debug_level( false ); // TODO add flag

    try
    {
        if( ( parser.parse() != 0 ) or not specification )
        {
            std::cerr << "Error parsing file" << std::endl;
            return false;
        }
    }
    catch( const std::exception& e )
    {
        std::cerr << "error: got exception: " << e.what() << std::endl;
        return false;
    }

    pr.setResult< SourceToAstPass >( libstdhl::make< Data >( specification ) );

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
