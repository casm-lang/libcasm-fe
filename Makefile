#   
#   Copyright (c) 2014-2016 CASM Organization
#   All rights reserved.
#   
#   Developed by: Florian Hahn
#                 Philipp Paulweber
#                 Emmanuel Pescosta
#                 https://github.com/ppaulweber/libcasm-fe
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

AR=ar

CC=clang
CCFLAG += -std=c11
CCFLAG += -g -O0
CCFLAG += -Wall

CPP=clang
CPPFLAG += -std=c++11
CPPFLAG += -g -O0
CPPFLAG += -Wall
#CPPFLAG += -Wextra

LEX=flex
YAC=bison

TARGET = libcasm-fe.a

CPPOBJECTS += src/various/GrammarParser.cpp
CPPOBJECTS += src/various/GrammarLexer.cpp
CPPOBJECTS += obj/GrammarParser.o
CPPOBJECTS += obj/GrammarLexer.o

CPPOBJECTS += obj/Ast.o
CPPOBJECTS += obj/AstDumpVisitor.o
CPPOBJECTS += obj/Driver.o
CPPOBJECTS += obj/Exceptions.o
CPPOBJECTS += obj/Frontend.o
CPPOBJECTS += obj/FunctionCycleVisitor.o
CPPOBJECTS += obj/LexerHelpers.o
CPPOBJECTS += obj/Symbols.o
CPPOBJECTS += obj/TypeCheckVisitor.o
CPPOBJECTS += obj/Types.o
CPPOBJECTS += obj/Value.o

CPPOBJECTS += obj/AstDumpPass.o
CPPOBJECTS += obj/TypeCheckPass.o
CPPOBJECTS += obj/SourceToAstPass.o
CPPOBJECTS += obj/NumericExecutionPass.o
CPPOBJECTS += obj/SymbolicExecutionPass.o

CPPOBJECTS += obj/Builtins.o
CPPOBJECTS += obj/ExecutionContext.o
CPPOBJECTS += obj/ExecutionVisitor.o
CPPOBJECTS += obj/Operators.o
CPPOBJECTS += obj/Symbolic.o
CPPOBJECTS += obj/UpdateSet.o

INCLUDE += -I ./
INCLUDE += -I ./src
INCLUDE += -I ./src/analyze
INCLUDE += -I ./src/transform
INCLUDE += -I ./src/execute
INCLUDE += -I ./src/various

INCLUDE += -I ../
INCLUDE += -I ../pass

default: $(LIBRARY) obj $(TARGET)

obj:
	mkdir -p obj

src/various/GrammarParser.cpp: src/GrammarParser.yy
	@echo "YAC " $<
	@cd src/various && $(YAC) -b src/various/ --output GrammarParser.cpp --defines=GrammarParser.tab.h ../../$^

src/various/GrammarLexer.cpp: src/GrammarLexer.l
	@echo "LEX " $<
	@$(LEX) $(LFLAGS) -o $@ $^

obj/%.o: src/%.cpp
	@echo "CPP " $<
	@$(CPP) $(CPPFLAG) $(INCLUDE) -c $< -o $@

obj/%.o: src/analyze/%.cpp
	@echo "CPP " $<
	@$(CPP) $(CPPFLAG) $(INCLUDE) -c $< -o $@

obj/%.o: src/transform/%.cpp
	@echo "CPP " $<
	@$(CPP) $(CPPFLAG) $(INCLUDE) -c $< -o $@

obj/%.o: src/execute/%.cpp
	@echo "CPP " $<
	@$(CPP) $(CPPFLAG) $(INCLUDE) -c $< -o $@

obj/%.o: src/various/%.cpp
	@echo "CPP " $<
	@$(CPP) $(CPPFLAG) $(INCLUDE) -c $< -o $@

$(TARGET): $(CPPOBJECTS) $(LIBRARY)
	@echo "AR  " $@
	@$(AR) rsc $@ $(filter %.o,$^)
	@ranlib $@

clean:
	@echo "RM  " obj
	@rm -rf obj
	@echo "RM  " $(TARGET)
	@rm -f $(TARGET)
	@rm -f test


TEST_FILES   = $(shell find uts -name '*.cpp' | cut -d'.' -f1)
TEST_OBJECTS = $(TEST_FILES:%=obj/%.o)

TEST_INCLUDE  = -I ../gtest/googletest/include
TEST_INCLUDE += -I ../gtest/googletest

TEST_LIBRARY  = -lstdc++
TEST_LIBRARY += -lpthread

obj/uts/%.o: uts/%.cpp
	@mkdir -p `dirname $@`
	@echo "CPP " $<
	@$(CPP) $(CPPFLAG) $(TEST_INCLUDE) $(INCLUDE) -c $< -o $@

test: default obj/uts $(TEST_OBJECTS)
	@rm -f $@
	@echo "LD  " $@
	@$(CPP) $(CPPFLAG) $(TEST_INCLUDE) $(INCLUDE) $(TEST_LIBRARY) -o $@ $(filter %.o,$^) ../gtest/googletest/src/gtest-all.cc ../gtest/googletest/src/gtest_main.cc
	@echo "RUN " $@
	@./$@


# LEX = flex
# CXX = clang
# CFLAGS = -Isrc -Iobj/src -std=c++11 -O0 -g
# # -stdlib=libstdc++
# OBJ_DIR = obj
# AR = /usr/bin/ar

# SRC = $(shell find src -name '*.cpp' | cut -d'.' -f1)

# OBJS = $(SRC:%=obj/%.o)

# .PHONY: all clean
# # test

# all: lib

# clean:
# 	rm -rf obj

# # test: obj/test_parse obj/test_typecheck
# #	python tests/integration/test_runner.py

# $(OBJ_DIR):
# 	mkdir -p $@/src/libsyntax
# 	mkdir -p $@/src/libutil
# 	mkdir -p $@/src/libmiddle
# 	mkdir -p $@/src/execute

# obj/libfrontend.a: obj/src/libsyntax/parser.o obj/src/libsyntax/lexer.o $(OBJS)
# 	@echo "AR  " $@
# 	@$(AR) rsc obj/libfrontend.a $(OBJS) obj/src/libsyntax/lexer.o obj/src/libsyntax/parser.o
# 	@ranlib obj/libfrontend.a

# lib: $(OBJ_DIR) obj/libfrontend.a

# obj/src/libsyntax/parser.cpp: src/libsyntax/grammer.yy
# 	@echo "YAC " $<
# 	@cd obj/src/libsyntax && bison --output parser.cpp --defines=parser.tab.h ../../../src/libsyntax/grammer.yy

# $(OBJ_DIR)/src/libsyntax/lexer.cpp: src/libsyntax/lexer.l
# 	@echo "LEX " $<
# 	@$(LEX) $(LFLAGS) -o $(OBJ_DIR)/src/libsyntax/lexer.cpp src/libsyntax/lexer.l

# $(OBJ_DIR)/src/libsyntax/%.o: obj/src/libsyntax/%.cpp
# 	@echo "CPP " $<
# 	@$(CXX) $(CFLAGS) -c $< -o $@

# $(OBJ_DIR)/src/libutil/%.o: src/libutil/%.cpp
# 	@echo "CPP " $<
# 	@$(CXX) $(CFLAGS) -c $< -o $@

# $(OBJ_DIR)/src/libsyntax/%.o: src/libsyntax/%.cpp
# 	@echo "CPP " $<
# 	@$(CXX) $(CFLAGS) -c $< -o $@

# $(obj_dir)/src/libmiddle/%.o: src/libmiddle/%.cpp
# 	@echo "CPP " $<
# 	@$(cxx) $(cflags) -c $< -o $@

# $(OBJ_DIR)/src/%.o: src/%.cpp
# 	@echo "CPP " $<
# 	@$(CXX) $(CFLAGS) -c $< -o $@

# $(obj_dir)/src/execute/%.o: src/execute/%.cpp
# 	@echo "CPP " $<
# 	@$(cxx) $(cflags) -c $< -o $@


# # obj/test_parse: $(OBJ_DIR) obj/libfrontend.a tests/integration/test_parse.cpp
# # 	@echo "CPP " $<
# # 	@$(CXX) $(CFLAGS) -o $@ tests/integration/test_parse.cpp obj/libfrontend.a -lstdc++ -lm
# # 
# # obj/test_typecheck: $(OBJ_DIR) obj/libfrontend.a tests/integration/test_typecheck.cpp
# # 	@echo "CPP " $<
# # 	@$(CXX) $(CFLAGS) -o $@ tests/integration/test_typecheck.cpp obj/libfrontend.a -lstdc++ -lm
# # 
# # obj/test_dump: $(OBJ_DIR) obj/libfrontend.a tests/integration/test_dump.cpp
# # 	@echo "CPP " $<
# # 	@$(CXX) $(CFLAGS) -o $@ tests/integration/test_dump.cpp obj/libfrontend.a -lstdc++ -lm

