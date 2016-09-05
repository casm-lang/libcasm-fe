#   
#   Copyright (c) 2014-2016 CASM Organization
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

AR=ar

CC=clang
CCFLAG += -std=c11
debug: CCFLAG += -g -O0
release: CCFLAG += -O3 -DNDEBUG
CCFLAG += -Wall

CPP=clang
CPPFLAG += -std=c++11
debug: CPPFLAG += -g -O0
release: CPPFLAG += -O3 -DNDEBUG
CPPFLAG += -Wall
#CPPFLAG += -Wextra

LEX=flex
YAC=bison
YAC_FLAG = -Wall

TARGET = libcasm-fe.a

CPPOBJECTS += src/various/GrammarParser.cpp
CPPOBJECTS += src/various/GrammarLexer.cpp
CPPOBJECTS += src/various/Grammar.org
CPPOBJECTS += obj/GrammarParser.o
CPPOBJECTS += obj/GrammarLexer.o

CPPOBJECTS += obj/Ast.o
CPPOBJECTS += obj/AstDumpVisitor.o
CPPOBJECTS += obj/Driver.o
CPPOBJECTS += obj/Exceptions.o
CPPOBJECTS += obj/FunctionCycleVisitor.o
CPPOBJECTS += obj/LexerHelpers.o
CPPOBJECTS += obj/Symbols.o
CPPOBJECTS += obj/TypeCheckVisitor.o
CPPOBJECTS += obj/Types.o
CPPOBJECTS += obj/Value.o

CPPOBJECTS += obj/AstDumpPass.o
CPPOBJECTS += obj/TypeCheckPass.o
CPPOBJECTS += obj/SourceToAstPass.o
CPPOBJECTS += obj/ExecutionPassBase.o
CPPOBJECTS += obj/NumericExecutionPass.o
CPPOBJECTS += obj/SymbolicExecutionPass.o
CPPOBJECTS += obj/UpdateSet.o

INCLUDE += -I ./
INCLUDE += -I ./src
INCLUDE += -I ./src/analyze
INCLUDE += -I ./src/transform
INCLUDE += -I ./src/execute
INCLUDE += -I ./src/various

INCLUDE += -I ../
INCLUDE += -I ../pass

default: debug

debug:   $(LIBRARY) obj $(TARGET)
release: $(LIBRARY) obj $(TARGET)

obj:
	@mkdir -p obj


src/various/Grammar.org: src/GrammarParser.yy
	@echo "GEN " $@
	@grep -e "^[:|] [alpha]*" $< -B 2 -A 1 |\
		sed "/^  {/d" |\
		sed "/^  }/d" |\
		sed "/^--/d"  |\
		sed "/^\t/d"  > $@

src/various/GrammarParser.cpp: src/GrammarParser.yy src/GrammarToken.h
	@echo "YAC " $<
	@mkdir -p `dirname obj/$<`
	@head -n +`grep -n "{{grammartoken}}" $< | grep -o "[0-9]*"` $< | cat  > obj/$<
	@cat $(filter %.h,$^) | sed "/^\/\/ /d" | sed "s/{ /\/\/ {/g"         >> obj/$< 
	@tail -n +`grep -n "{{grammartoken}}" $< | grep -o "[0-9]*"` $< | cat >> obj/$<
	@sed -i "/^{{grammartoken}}/d" obj/$<
	@cd src/various && $(YAC) $(YAC_FLAG) -b src/various/ --output GrammarParser.cpp --defines=GrammarParser.tab.h ../../obj/$<


src/various/GrammarLexer.cpp: src/GrammarLexer.l src/GrammarToken.h
	@echo "LEX " $<
	@mkdir -p `dirname obj/$<`
	@head -n +`grep -n "{{grammartoken}}" $< | grep -o "[0-9]*"` $< | cat  > obj/$<
	@cat $(filter %.h,$^) | sed "/^\/\/ /d" | sed "s/[A-Za-z_]*[ ]* \"/\"/g"  >> obj/$< 
	@tail -n +`grep -n "{{grammartoken}}" $< | grep -o "[0-9]*"` $< | cat >> obj/$<
	@sed -i "/^{{grammartoken}}/d" obj/$<
	@$(LEX) $(LFLAGS) -o $@ obj/$<


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
	@rm -f $(TEST_TARGET)


TEST_TARGET = libcasm-fe-test.a

TEST_FILES   = $(shell find uts -name '*.cpp' | cut -d'.' -f1)
TEST_OBJECTS = $(TEST_FILES:%=obj/%.o)

TEST_INCLUDE  = -I ../gtest/googletest/include
TEST_INCLUDE += -I ../gtest/googletest

TEST_LIBRARY  = -lstdc++
TEST_LIBRARY += -lm
TEST_LIBRARY += -lpthread

obj/uts/%.o: uts/%.cpp
	@mkdir -p `dirname $@`
	@echo "CPP " $<
	@$(CPP) $(CPPFLAG) $(TEST_INCLUDE) $(INCLUDE) -c $< -o $@

test: tests
	@rm -f $@
	@echo "LD  " $@
	@$(CPP) $(CPPFLAG) $(TEST_INCLUDE) $(INCLUDE) $(TEST_LIBRARY) -o $@ \
		-Wl,--whole-archive $(TEST_TARGET) $(TARGET) -Wl,--no-whole-archive \
		 ../gtest/googletest/src/gtest-all.cc ../gtest/googletest/src/gtest_main.cc 
	@echo "RUN " $@
	@./$@

tests: obj $(TARGET) $(TEST_TARGET) default

$(TEST_TARGET): $(TEST_OBJECTS)
	@echo "AR  " $@
	@$(AR) rsc $@ $(filter %.o,$^)
	@ranlib $@
