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
#   along with this program. If not, see <http://www.gnu.org/licenses/>.
#   

LEX = flex
CXX = clang
CFLAGS = -Isrc -Iobj/src -std=c++11 -O0 -g
# -stdlib=libstdc++
OBJ_DIR = obj
AR = /usr/bin/ar

SRC = $(shell find src -name '*.cpp' | cut -d'.' -f1)

OBJS = $(SRC:%=obj/%.o)

.PHONY: all clean
# test

all: lib

clean:
	rm -rf obj

# test: obj/test_parse obj/test_typecheck
#	python tests/integration/test_runner.py

$(OBJ_DIR):
	mkdir -p $@/src/libsyntax
	mkdir -p $@/src/libutil
	mkdir -p $@/src/libmiddle

obj/libfrontend.a: obj/src/libsyntax/parser.o obj/src/libsyntax/lexer.o $(OBJS)
	@echo "AR  " $@
	@$(AR) rsc obj/libfrontend.a $(OBJS) obj/src/libsyntax/lexer.o obj/src/libsyntax/parser.o
	@ranlib obj/libfrontend.a

lib: $(OBJ_DIR) obj/libfrontend.a

obj/src/libsyntax/parser.cpp: src/libsyntax/grammer.yy
	@echo "YAC " $<
	@cd obj/src/libsyntax && bison --output parser.cpp --defines=parser.tab.h ../../../src/libsyntax/grammer.yy

$(OBJ_DIR)/src/libsyntax/lexer.cpp: src/libsyntax/lexer.l
	@echo "LEX " $<
	@$(LEX) $(LFLAGS) -o $(OBJ_DIR)/src/libsyntax/lexer.cpp src/libsyntax/lexer.l

$(OBJ_DIR)/src/libsyntax/%.o: obj/src/libsyntax/%.cpp
	@echo "CPP " $<
	@$(CXX) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/src/libutil/%.o: src/libutil/%.cpp
	@echo "CPP " $<
	@$(CXX) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/src/libsyntax/%.o: src/libsyntax/%.cpp
	@echo "CPP " $<
	@$(CXX) $(CFLAGS) -c $< -o $@

$(obj_dir)/src/libmiddle/%.o: src/libmiddle/%.cpp
	@echo "CPP " $<
	@$(cxx) $(cflags) -c $< -o $@

$(OBJ_DIR)/src/%.o: src/%.cpp
	@echo "CPP " $<
	@$(CXX) $(CFLAGS) -c $< -o $@

# obj/test_parse: $(OBJ_DIR) obj/libfrontend.a tests/integration/test_parse.cpp
# 	@echo "CPP " $<
# 	@$(CXX) $(CFLAGS) -o $@ tests/integration/test_parse.cpp obj/libfrontend.a -lstdc++ -lm
# 
# obj/test_typecheck: $(OBJ_DIR) obj/libfrontend.a tests/integration/test_typecheck.cpp
# 	@echo "CPP " $<
# 	@$(CXX) $(CFLAGS) -o $@ tests/integration/test_typecheck.cpp obj/libfrontend.a -lstdc++ -lm
# 
# obj/test_dump: $(OBJ_DIR) obj/libfrontend.a tests/integration/test_dump.cpp
# 	@echo "CPP " $<
# 	@$(CXX) $(CFLAGS) -o $@ tests/integration/test_dump.cpp obj/libfrontend.a -lstdc++ -lm
