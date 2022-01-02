#
#   Copyright (C) 2014-2022 CASM Organization <https://casm-lang.org>
#   All rights reserved.
#
#   Developed by: Philipp Paulweber et al.
#                 <https://github.com/casm-lang/libcasm-fe/graphs/contributors>
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
  ${PROJECT_BINARY_DIR}/src
  ${LIBSTDHL_INCLUDE_DIR}
  ${LIBPASS_INCLUDE_DIR}
  ${LIBTPTP_INCLUDE_DIR}
  ${LIBCASM_IR_INCLUDE_DIR}
)

add_library( ${PROJECT}-cpp OBJECT
  Configuration.cpp
  Exception.cpp
  Lexer.cpp
  Logger.cpp
  Namespace.cpp
  Project.cpp
  Specification.cpp
  TypeInfo.cpp

  cst/Attribute.cpp
  cst/Declaration.cpp
  cst/Definition.cpp
  cst/Expression.cpp
  cst/Helper.cpp
  cst/Identifier.cpp
  cst/Literal.cpp
  cst/Node.cpp
  cst/Rule.cpp
  cst/Root.cpp
  cst/Span.cpp
  cst/Token.cpp
  cst/Type.cpp
  cst/Visitor.cpp

  ast/Declaration.cpp
  ast/Definition.cpp
  ast/Expression.cpp
  ast/Identifier.cpp
  ast/Literal.cpp
  ast/Node.cpp
  ast/Rule.cpp
  ast/Root.cpp
  ast/Type.cpp
  ast/Visitor.cpp

  lst/Definition.cpp
  lst/Expression.cpp
  lst/Identifier.cpp
  lst/Literal.cpp
  lst/Node.cpp
  lst/Rule.cpp
  lst/Root.cpp
  lst/Visitor.cpp

  analyze/ConsistencyCheckPass.cpp
  analyze/TemplatingPass.cpp
  analyze/TypeCheckPass.cpp
  analyze/TypeInferencePass.cpp
  analyze/AttributionPass.cpp
  analyze/SymbolRegistrationPass.cpp
  analyze/SymbolResolverPass.cpp
  analyze/FrameSizeDeterminationPass.cpp
  analyze/ProjectResolverPass.cpp
  analyze/PropertyResolverPass.cpp
  analyze/PropertyRevisePass.cpp

  import/FileLoadingStrategy.cpp
  import/PathLoadingStrategy.cpp
  import/SpecificationLoader.cpp
  import/SpecificationRepository.cpp
  import/ImportError.cpp
  import/LibraryLoaderPass.cpp
  import/SpecificationMergerPass.cpp

  transform/AstDumpPass.cpp
  transform/AstToLstPass.cpp
  transform/CstDumpPass.cpp
  transform/CstEmitPass.cpp
  transform/CstToAstPass.cpp
  transform/LstDumpPass.cpp
  transform/LstToIrPass.cpp
  transform/SourceToCstPass.cpp

  various/GrammarParser.cpp

  execute/Agent.cpp
  execute/ExecutionVisitor.cpp
  execute/NumericExecutionPass.cpp
  execute/HashMapBase.cpp
  execute/ReferenceConstant.cpp
  execute/SymbolicExecutionPass.cpp
  execute/SymbolicConsistencyPass.cpp
  execute/SymbolicConsistencyVisitor.cpp
  execute/Frame.cpp
  execute/RuntimeException.cpp
  execute/UpdateException.cpp
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
    Configuration
    Exception
    Logger
    Namespace
    Project
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
    TemplatingPass
    TypeCheckPass
    TypeInferencePass
    FrameSizeDeterminationPass
    ProjectResolverPass
    PropertyResolverPass
    PropertyRevisePass
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
    Agent
    ChainedHashMap
    ExecutionVisitor
    Frame
    FunctionState
    HashMapBase
    LocationRegistry
    NumericExecutionPass
    ProbingHashMap
    ReferenceConstant
    RobinHoodHashMap
    Stack
    SymbolicConsistencyPass
    SymbolicConsistencyVisitor
    SymbolicExecutionPass
    UpdateSet
    RuntimeException
    UpdateException
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


ecm_generate_headers( ${PROJECT}_IMPORT_HEADERS_CPP
  ORIGINAL
    CAMELCASE
  HEADER_NAMES
    FileLoadingStrategy
    PathLoadingStrategy
    LoadingStrategy
    SpecificationRepository
    ImportError
    SpecificationLoader
    LibraryLoaderPass
    SpecificationMergerPass
  PREFIX
    ${PROJECT}/import
  RELATIVE
    import
  REQUIRED_HEADERS
    ${PROJECT}_IMPORT_HEADERS
  )
install(
  FILES
    ${${PROJECT}_IMPORT_HEADERS}
    ${${PROJECT}_IMPORT_HEADERS_CPP}
  DESTINATION
    "include/${PROJECT}/import"
  )


ecm_generate_headers( ${PROJECT}_TRANSFORM_HEADERS_CPP
  ORIGINAL
    CAMELCASE
  HEADER_NAMES
    AstDumpPass
    AstToLstPass
    CstDumpPass
    CstEmitPass
    CstToAstPass
    LstDumpPass
    LstToIrPass
    SourceToCstPass
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


ecm_generate_headers( ${PROJECT}_CST_HEADERS_CPP
  ORIGINAL
    CAMELCASE
  HEADER_NAMES
    Attribute
    Declaration
    Definition
    Expression
    Helper
    Identifier
    Literal
    Node
    Rule
    Root
    Span
    Token
    Type
    Visitor
  PREFIX
    ${PROJECT}/cst
  RELATIVE
    cst
  REQUIRED_HEADERS
    ${PROJECT}_CST_HEADERS
  )
install(
  FILES
    ${${PROJECT}_CST_HEADERS}
    ${${PROJECT}_CST_HEADERS_CPP}
  DESTINATION
    "include/${PROJECT}/cst"
  )


ecm_generate_headers( ${PROJECT}_AST_HEADERS_CPP
  ORIGINAL
    CAMELCASE
  HEADER_NAMES
    Declaration
    Definition
    Expression
    Identifier
    Literal
    Node
    Rule
    Root
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


ecm_generate_headers( ${PROJECT}_LST_HEADERS_CPP
  ORIGINAL
    CAMELCASE
  HEADER_NAMES
    Definition
    Expression
    Identifier
    Literal
    Node
    Rule
    Root
    Visitor
  PREFIX
    ${PROJECT}/lst
  RELATIVE
    lst
  REQUIRED_HEADERS
    ${PROJECT}_LST_HEADERS
  )
install(
  FILES
    ${${PROJECT}_LST_HEADERS}
    ${${PROJECT}_LST_HEADERS_CPP}
  DESTINATION
    "include/${PROJECT}/lst"
  )
