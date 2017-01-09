#
#   Copyright (c) 2014-2017 CASM Organization
#   All rights reserved.
#
#   Developed by: Florian Hahn
#                 Philipp Paulweber
#                 Emmanuel Pescosta
#                 https://github.com/casm-lang/libcasm-fe
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

cmake_minimum_required( VERSION 3.1 )

if( EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/../gtest" )
  set( LIBS .. )
else()
  set( LIBS lib )
endif()

foreach( DEPENDENCY
    stdhl
    pass
    casm-ir
    )
  if( NOT TARGET ${DEPENDENCY} )
    add_subdirectory( ${LIBS}/${DEPENDENCY} lib/${DEPENDENCY} )
  endif()  
endforeach()


file( GLOB_RECURSE CXX_SRC_FILES "src/*.cpp" )
file( GLOB_RECURSE CXX_UTS_FILES "uts/*.cpp" )


set( TARGET casm-fe )
project( ${TARGET} )


include_directories(
  .
  src
  ${LIBS}/gtest/googletest
  ${LIBS}/gtest/googletest/include
  ${LIBS}/hayai/src
  ${LIBS}/stdhl
  ${LIBS}/pass
  ${LIBS}/casm-ir
)


set( CMAKE_CXX_FLAGS          "${CMAKE_CXX_FLAGS}          -std=c++11 -Wall" )

set( CMAKE_CXX_FLAGS_DEBUG    "${CMAKE_CXX_FLAGS_DEBUG}    -O0" )
set( CMAKE_CXX_FLAGS_RELEASE  "${CMAKE_CXX_FLAGS_RELEASE}  -O3" )
set( CMAKE_CXX_FLAGS_SANITIZE "${CMAKE_CXX_FLAGS_SANITIZE} -O1 -Wextra -g -fno-omit-frame-pointer -fno-optimize-sibling-calls -fsanitize=undefined -fsanitize=address" )


string( LENGTH "${CMAKE_CURRENT_SOURCE_DIR}/" CWD_LENGTH )


set( DEF_GRAMMAR "${CMAKE_CURRENT_SOURCE_DIR}/src/GrammarParser.yy;${CMAKE_CURRENT_SOURCE_DIR}/src/GrammarToken.hpp" )
set( ORG_GRAMMAR "${CMAKE_CURRENT_BINARY_DIR}/src/various/Grammar.org" )
set( GRAMMAR     "obj/src/various/Grammar.org" )

add_custom_command(
  OUTPUT  ${ORG_GRAMMAR}
  COMMAND make -C ${CMAKE_CURRENT_SOURCE_DIR} ${GRAMMAR}
  DEPENDS ${DEF_GRAMMAR}
  COMMENT ""
)

set( DEF_GRAMMAR_PARSER "${CMAKE_CURRENT_SOURCE_DIR}/src/GrammarParser.yy;${CMAKE_CURRENT_SOURCE_DIR}/src/GrammarToken.hpp" )
set( CXX_GRAMMAR_PARSER "${CMAKE_CURRENT_BINARY_DIR}/src/various/GrammarParser.cpp" )
set(     GRAMMAR_PARSER "obj/src/various/GrammarParser.cpp" )

add_custom_command(
  OUTPUT  ${CXX_GRAMMAR_PARSER}
  COMMAND make -C ${CMAKE_CURRENT_SOURCE_DIR} ${GRAMMAR_PARSER}
  DEPENDS ${DEF_GRAMMAR_PARSER}
  COMMENT ""
)


set( DEF_GRAMMAR_LEXER "${CMAKE_CURRENT_SOURCE_DIR}/src/GrammarLexer.l;${CMAKE_CURRENT_SOURCE_DIR}/src/GrammarToken.hpp" )
set( CXX_GRAMMAR_LEXER "${CMAKE_CURRENT_BINARY_DIR}/src/various/GrammarLexer.cpp" )
set(     GRAMMAR_LEXER "src/various/GrammarLexer.cpp" )

add_custom_command(
  OUTPUT  ${CXX_GRAMMAR_LEXER}
  COMMAND make -C ${CMAKE_CURRENT_SOURCE_DIR} ${GRAMMAR_LEXER}
  DEPENDS ${DEF_GRAMMAR_LEXER}
  COMMENT ""
)


add_library( ${TARGET} STATIC
  ${CXX_SRC_FILES}
)

add_custom_target( ${TARGET}-grammar ALL
  DEPENDS ${ORG_GRAMMAR} ${CXX_GRAMMAR_PARSER} ${CXX_GRAMMAR_LEXER}
  )

add_dependencies( ${TARGET} ${TARGET}-grammar )

add_library( ${TARGET}-test OBJECT
  ${CXX_UTS_FILES}
)

add_executable( ${TARGET}-check
  ${LIBS}/gtest/googletest/src/gtest_main.cc
  ${LIBS}/gtest/googletest/src/gtest-all.cc  
  $<TARGET_OBJECTS:${TARGET}-test>
)

target_link_libraries( ${TARGET}-check
  ${TARGET}
  pass
  stdhl
  casm-ir
  pthread
)


add_library( ${TARGET}-benchmark OBJECT
  ${LIBS}/hayai/src/hayai_posix_main.cpp
)
  
add_executable( ${TARGET}-run
  $<TARGET_OBJECTS:${TARGET}-benchmark>
)

target_link_libraries( ${TARGET}-run
  pthread
)


if( NOT CMAKE_BUILD_TYPE )
  set( CMAKE_BUILD_TYPE Debug
    CACHE STRING "Choose the type of build : debug sanitize release."
    FORCE
  )
endif( NOT CMAKE_BUILD_TYPE )


message( "* ${CMAKE_BUILD_TYPE} : ${TARGET} : ${LIBS}" )
