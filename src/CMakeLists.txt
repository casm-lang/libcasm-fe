#
#   Copyright (C) 2014-2018 CASM Organization <https://casm-lang.org>
#   All rights reserved.
#
#   Developed by: Philipp Paulweber
#                 Emmanuel Pescosta
#                 Florian Hahn
#                 <https://github.com/casm-lang/libcasm-fe>
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

include_directories(
  ${LIBSTDHL_INCLUDE_DIR}
  ${LIBPASS_INCLUDE_DIR}
  ${LIBCASM_IR_INCLUDE_DIR}
  ${LIBCASM_RT_INCLUDE_DIR}
)

add_library( ${PROJECT}-cpp OBJECT
  Exception.cpp
  Logger.cpp
  Namespace.cpp
  Specification.cpp
  TypeInfo.cpp

  ast/Attribute.cpp
  ast/Definition.cpp
  ast/Expression.cpp
  ast/Literal.cpp
  ast/Node.cpp
  ast/Rule.cpp
  ast/Type.cpp
  ast/RecursiveVisitor.cpp
  ast/EmptyVisitor.cpp

  analyze/ConsistencyCheckPass.cpp
  analyze/TypeCheckPass.cpp
  analyze/TypeInferencePass.cpp
  analyze/AttributionPass.cpp
  analyze/SymbolRegistrationPass.cpp
  analyze/SymbolResolverPass.cpp
  analyze/FrameSizeDeterminationPass.cpp
  analyze/PropertyResolverPass.cpp

  execute/NumericExecutionPass.cpp
  execute/HashMapBase.cpp
  execute/ReferenceConstant.cpp
  execute/Frame.cpp

  transform/AstDumpDotPass.cpp
  transform/AstDumpSourcePass.cpp
  transform/AstToCasmIRPass.cpp
  transform/SourceToAstPass.cpp

  various/GrammarParser.cpp
  various/GrammarLexer.cpp
  )


configure_file(
  Version.in.h
  ${PROJECT}/Version.h
  )
configure_file(
  Version.in
  ${PROJECT}/Version
  )
install(
  FILES
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT}/Version.h
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT}/Version
  DESTINATION
    "include/${PROJECT}"
  )


ecm_generate_headers( ${PROJECT}_HEADERS_CPP
  ORIGINAL
    CAMELCASE
  HEADER_NAMES
    libcasm-fe
    CasmFE
    Codes
    Exception
    Logger
    Namespace
    SourceLocation
    Specification
    TypeInfo
  PREFIX
    ${PROJECT}
  REQUIRED_HEADERS
    ${PROJECT}_HEADERS
  )
install(
  FILES
    ${${PROJECT}_HEADERS}
    ${${PROJECT}_HEADERS_CPP}
  DESTINATION
    "include/${PROJECT}"
  )


ecm_generate_headers( ${PROJECT}_ANALYZE_HEADERS_CPP
  ORIGINAL
    CAMELCASE
  HEADER_NAMES
    AttributionPass
    ConsistencyCheckPass
    SymbolRegistrationPass
    SymbolResolverPass
    TypeCheckPass
    TypeInferencePass
    FrameSizeDeterminationPass
    PropertyResolverPass
  PREFIX
    ${PROJECT}/analyze
  RELATIVE
    analyze
  REQUIRED_HEADERS
    ${PROJECT}_ANALYZE_HEADERS
  )
install(
  FILES
    ${${PROJECT}_ANALYZE_HEADERS}
    ${${PROJECT}_ANALYZE_HEADERS_CPP}
  DESTINATION
    "include/${PROJECT}/analyze"
  )


ecm_generate_headers( ${PROJECT}_EXECUTE_HEADERS_CPP
  ORIGINAL
    CAMELCASE
  HEADER_NAMES
    ChainedHashMap
    Frame
    FunctionState
    HashMapBase
    LocationRegistry
    NumericExecutionPass
    ProbingHashMap
    ReferenceConstant
    RobinHoodHashMap
    Stack
    UpdateSet
  PREFIX
    ${PROJECT}/execute
  RELATIVE
    execute
  REQUIRED_HEADERS
    ${PROJECT}_EXECUTE_HEADERS
  )
install(
  FILES
    ${${PROJECT}_EXECUTE_HEADERS}
    ${${PROJECT}_EXECUTE_HEADERS_CPP}
  DESTINATION
    "include/${PROJECT}/execute"
  )


ecm_generate_headers( ${PROJECT}_TRANSFORM_HEADERS_CPP
  ORIGINAL
    CAMELCASE
  HEADER_NAMES
    AstDumpDotPass
    AstDumpSourcePass
    AstToCasmIRPass
    SourceToAstPass
  PREFIX
    ${PROJECT}/transform
  RELATIVE
    transform
  REQUIRED_HEADERS
    ${PROJECT}_TRANSFORM_HEADERS
  )
install(
  FILES
    ${${PROJECT}_TRANSFORM_HEADERS}
    ${${PROJECT}_TRANSFORM_HEADERS_CPP}
  DESTINATION
    "include/${PROJECT}/transform"
  )


ecm_generate_headers( ${PROJECT}_ALLOCATOR_HEADERS_CPP
  ORIGINAL
    CAMELCASE
  HEADER_NAMES
    BlockAllocator
    MemoryPool
  PREFIX
    ${PROJECT}/allocator
  RELATIVE
    allocator
  REQUIRED_HEADERS
    ${PROJECT}_ALLOCATOR_HEADERS
  )
install(
  FILES
    ${${PROJECT}_ALLOCATOR_HEADERS}
    ${${PROJECT}_ALLOCATOR_HEADERS_CPP}
  DESTINATION
    "include/${PROJECT}/allocator"
  )


ecm_generate_headers( ${PROJECT}_AST_HEADERS_CPP
  ORIGINAL
    CAMELCASE
  HEADER_NAMES
    Attribute
    Definition
    EmptyVisitor
    Expression
    Literal
    Node
    RecursiveVisitor
    Rule
    Type
    Visitor
  PREFIX
    ${PROJECT}/ast
  RELATIVE
    ast
  REQUIRED_HEADERS
    ${PROJECT}_AST_HEADERS
  )
install(
  FILES
    ${${PROJECT}_AST_HEADERS}
    ${${PROJECT}_AST_HEADERS_CPP}
  DESTINATION
    "include/${PROJECT}/ast"
  )
