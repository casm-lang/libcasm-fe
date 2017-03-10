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

#include "Visitor.h"

#include "libcasm-fe.h"

using namespace libcasm_fe;

#define CASE_VALUE( VID, CLASS )                                               \
    case Value::ID::VID:                                                       \
        visit( static_cast< CLASS& >( value ), cxt );                          \
        break

void Visitor::dispatch( Stage stage, Value& value, Context& cxt )
{
    switch( value.id() )
    {
        CASE_VALUE( NODE_CLASS, NodeClass );
        CASE_VALUE( NODE_CLASS_2, NodeClass_2 );

        default:
        {
            fprintf( stderr,
                "%s:%i: error: unimplemented value name '%s' with id '%i' to "
                "dispatch\n",
                __FILE__, __LINE__, value.name(), value.id() );
            assert( 0 );
            break;
        }
    }
}


// use Node for Value

void Value::iterate( Traversal order,
    Visitor* visitor,
    Context* context,
    std::function< void( Value&, Context& ) >
        action )
{
    static Context default_context = Context();

    Context* cxt = context ? context : &default_context;

    Value& value = static_cast< Value& >( *this );

    // if( order == Traversal::PREORDER )
    // {
    //     action( /*order, */ value, *cxt );
    // }

    // if( visitor )
    // {
    //     visitor->dispatch( Visitor::Stage::PROLOG, value, *cxt );
    // }

    // if is specific node ... call iterate of node etc.
}

void Value::iterate(
    Traversal order, std::function< void( Value&, Context& ) > action )
{
    iterate( order, nullptr, nullptr, action );
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
