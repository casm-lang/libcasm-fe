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

#include "SymbolicConsistencyPass.h"

#include <libcasm-fe/Logger>
#include <libcasm-fe/execute/ExecutionVisitor>

#include <libcasm-fe/Exception.h>
#include <libcasm-fe/execute/Agent>
#include <libcasm-fe/execute/SymbolicConsistencyVisitor>
#include <libcasm-fe/import/SpecificationMergerPass>
#include <libcasm-fe/transform/AstToLstPass>

#include <libpass/PassRegistry>
#include <libpass/PassResult>
#include <libpass/PassUsage>

#include <libstdhl/Enum>
#include <libstdhl/Hash>
#include <libstdhl/Random>
#include <libstdhl/Stack>

#include <libtptp/Node>

#include <libtptp/transform/AstDumpDotPass>
#include <libtptp/transform/DumpSourcePass>

#include <mutex>

using namespace libcasm_fe;
using namespace LST;

namespace IR = libcasm_ir;

char SymbolicConsistencyPass::id = 0;

static libpass::PassRegistration< SymbolicConsistencyPass > PASS(
    "SymbolicConsistencyPass",
    "check consistency of symbolic updates on functions",
    "ast-symbolic-consistency",
    0 );

void SymbolicConsistencyPass::usage( libpass::PassUsage& pu )
{
    pu.require< SpecificationMergerPass >();
    pu.scheduleAfter< AstToLstPass >();
}

u1 SymbolicConsistencyPass::run( libpass::PassResult& pr )
{
    libcasm_fe::Logger log( &id, stream() );

    const auto data = pr.output< SpecificationMergerPass >();
    const auto specification = data->specification();

    while( true )
    {
        try
        {
            SymbolicConsistencyVisitor consistencyVisitor( log );
            consistencyVisitor.visit( *specification );
            break;
        }
        catch( SymbolicConsistencyVisitor::Conflict& e )
        {
            auto function = e.conflictingFunction();
            if( function->program() )
            {
                std::stringstream err;
                err << "Cannot promote 'program' function to symbolic." << std::endl << e.what();
                log.error( e.locations(), err.str() );
                return false;
            }
            log.info( e.locations(), e.what() );
            function->setSymbolic( true );
        }
        catch( const RuntimeException& e )
        {
            log.error( e );
            return false;
        }
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
