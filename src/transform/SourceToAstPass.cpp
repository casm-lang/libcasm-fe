//
//  Copyright (c) 2014-2017 CASM Organization
//  All rights reserved.
//
//  Developed by: Florian Hahn
//                Philipp Paulweber
//                Emmanuel Pescosta
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

#include "../Driver.h"

using namespace libcasm_fe;

extern Driver* global_driver;

char SourceToAstPass::id = 0;

static libpass::PassRegistration< SourceToAstPass > PASS( "Source To AST Pass",
    "parse the source code and generate an AST", "ast-parse", 0 );

// PPA: TODO: dependency INPUT FILE

bool SourceToAstPass::run( libpass::PassResult& pr )
{
    auto load_file_pass = pr.result< libpass::LoadFilePass >();

    global_driver = new Driver;

    Ast* node = global_driver->parse( load_file_pass->filename() );

    if( !node )
    {
        // TODO: FIXME: PPA: better error messages,
        // can be improved with the new libstdhl Verbose support

        std::cerr << "Error parsing file" << std::endl;

        return false;
    }

    pr.setResult< SourceToAstPass >( libstdhl::make< Data >( node ) );

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
