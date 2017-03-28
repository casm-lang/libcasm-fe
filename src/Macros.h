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

#ifndef CASMI_MACROS_H
#define CASMI_MACROS_H

#include <iostream>

#if defined( CASMI_DEBUG )
#define DEBUG( x )                                                             \
    do                                                                         \
    {                                                                          \
        std::cerr << "DEBUG: " << x << std::endl;                              \
    } while( 0 )
#else
#define DEBUG( x )                                                             \
    do                                                                         \
    {                                                                          \
    } while( 0 )
#endif

#define UNUSED( expr )                                                         \
    do                                                                         \
    {                                                                          \
        (void)( expr );                                                        \
    } while( 0 )

#ifdef __clang__
#define IGNORE_VARIADIC_WARNINGS                                               \
    _Pragma( "GCC diagnostic ignored \"-Wvariadic-macros\"" ) _Pragma(         \
        "GCC diagnostic ignored \"-Wgnu-zero-variadic-macro-arguments\"" )
#else
#define IGNORE_VARIADIC_WARNINGS                                               \
    _Pragma( "GCC diagnostic ignored \"-Wvariadic-macros\"" )
#endif

#ifdef __clang__
#define REENABLE_VARIADIC_WARNINGS                                             \
    _Pragma( "GCC diagnostic warning \"-Wvariadic-macros\"" ) _Pragma(         \
        "GCC diagnostic warning \"-Wgnu-zero-variadic-macro-arguments\"" )
#else
#define REENABLE_VARIADIC_WARNINGS                                             \
    _Pragma( "GCC diagnostic warning \"-Wvariadic-macros\"" )

#endif

#define FAILURE()                                                              \
    do                                                                         \
    {                                                                          \
        std::cerr << __FILE__ << ":" << __LINE__                               \
                  << ": this line shouldn't be reached!" << std::endl;         \
        exit( 4 );                                                             \
    } while( 0 )

#endif
