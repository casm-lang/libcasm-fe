#
#   Copyright (C) 2014-2024 CASM Organization <https://casm-lang.org>
#   All rights reserved.
#
#   Developed by: Philipp Paulweber et al.
#   <https://github.com/casm-lang/libcasm-fe/graphs/contributors>
#
#   This file is part of libcasm-fe.
#
#   libcasm-fe is free software: you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation, either version 3 of the License, or
#   (at your option) any later version.
#
#   libcasm-fe is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
#   GNU General Public License for more details.
#
#   You should have received a copy of the GNU General Public License
#   along with libcasm-fe. If not, see <http://www.gnu.org/licenses/>.
#
#   Additional permission under GNU GPL version 3 section 7
#
#   libcasm-fe is distributed under the terms of the GNU General Public License
#   with the following clarification and special exception: Linking libcasm-fe
#   statically or dynamically with other modules is making a combined work
#   based on libcasm-fe. Thus, the terms and conditions of the GNU General
#   Public License cover the whole combination. As a special exception,
#   the copyright holders of libcasm-fe give you permission to link libcasm-fe
#   with independent modules to produce an executable, regardless of the
#   license terms of these independent modules, and to copy and distribute
#   the resulting executable under terms of your choice, provided that you
#   also meet, for each linked independent module, the terms and conditions
#   of the license of that module. An independent module is a module which
#   is not derived from or based on libcasm-fe. If you modify libcasm-fe, you
#   may extend this exception to your version of the library, but you are
#   not obliged to do so. If you do not wish to do so, delete this exception
#   statement from your version.
#

# LIBCASM_FE_FOUND        - system has found the package
# LIBCASM_FE_INCLUDE_DIR  - the package include directory
# LIBCASM_FE_LIBRARY      - the package library

include( LibPackage )

libfind_pkg_check_modules( LIBCASM_FE_PKGCONF libcasm-fe )

find_path( LIBCASM_FE_INCLUDE_DIR
  NAMES libcasm-fe/libcasm-fe.h
  PATHS ${LIBCASM_FE_PKGCONF_INCLUDE_DIRS}
)

find_library( LIBCASM_FE_LIBRARY
  NAMES libcasm-fe.so libcasm-fe.dylib libcasm-fe.dll
  PATHS ${LIBCASM_FE_PKGCONF_LIBRARY_DIRS}
)

find_library( LIBCASM_FE_ARCHIVE
  NAMES libcasm-fe.a
  PATHS ${LIBCASM_FE_PKGCONF_LIBRARY_DIRS}
)

set( LIBCASM_FE_PROCESS_INCLUDES LIBCASM_FE_INCLUDE_DIR )
set( LIBCASM_FE_PROCESS_LIBS     LIBCASM_FE_LIBRARY LIBCASM_FE_ARCHIVE )

libfind_process( LIBCASM_FE )

if( EXISTS "${LIBCASM_FE_LIBRARY}" AND ${LIBCASM_FE_LIBRARY} AND
    EXISTS "${LIBCASM_FE_ARCHIVE}" AND ${LIBCASM_FE_ARCHIVE} )
  set( LIBCASM_FE_FOUND TRUE PARENT_SCOPE )
else()
  set( LIBCASM_FE_FOUND FALSE PARENT_SCOPE )
endif()
