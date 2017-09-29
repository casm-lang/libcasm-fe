#
#   Copyright (c) 2014-2017 CASM Organization
#   All rights reserved.
#
#   Developed by: Philipp Paulweber
#                 Emmanuel Pescosta
#                 Florian Hahn
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

TARGET = libcasm-fe

include .cmake/config.mk


LX  = flex
YC  = bison
YF  = -Wall -v

grammar: $(OBJ)/src/various/GrammarParser.cpp $(OBJ)/src/various/GrammarLexer.cpp
.PHONY: grammar

%/src/various/Grammar.org: src/various/Grammar.org
	mkdir -p `dirname $@`
	cp -f $< $@

src/various/Grammar.org: src/GrammarParser.yy src/GrammarToken.hpp
	grep -e "^[:|] [alpha]*" $< -B 1 | \
		sed "/^  {/d" | \
		sed "/^  }/d" | \
		sed "/^--/d"  | \
		sed "/^\t/d"  | \
		sed "s/^[^:|]/\n&/" > $@

%/src/various/GrammarParser.cpp: src/various/GrammarParser.cpp
	mkdir -p `dirname $@`
	cp -f $< $@

src/various/GrammarParser.cpp: src/GrammarParser.yy src/GrammarToken.hpp
	mkdir -p `dirname obj/$<`
	head -n +`grep -n "{{grammartoken}}" $< | grep -o "[0-9]*"` $< | cat  > obj/$<
	cat $(filter %.hpp,$^) | sed "/^\/\//d" | sed "s/{ /\/\/ {/g"         >> obj/$< 
	tail -n +`grep -n "{{grammartoken}}" $< | grep -o "[0-9]*"` $< | cat >> obj/$<
	sed -i "/^{{grammartoken}}/d" obj/$<
	cd src/various && $(YC) $(YF) -b src/various/ --output GrammarParser.cpp --defines=GrammarParser.tab.h ../../obj/$<

%/src/various/GrammarLexer.cpp: src/various/GrammarLexer.cpp
	mkdir -p `dirname $@`
	cp -f $< $@

src/various/GrammarLexer.cpp: src/GrammarLexer.l src/GrammarToken.hpp
	mkdir -p `dirname obj/$<`
	head -n +`grep -n "{{grammartoken}}" $< | grep -o "[0-9]*"` $< | cat  > obj/$<
	cat $(filter %.hpp,$^) | sed "/^\/\//d" | sed "s/[A-Za-z_]*[ ]* \"/\"/g"  >> obj/$< 
	tail -n +`grep -n "{{grammartoken}}" $< | grep -o "[0-9]*"` $< | cat >> obj/$<
	sed -i "/^{{grammartoken}}/d" obj/$<
	$(LX) $(LFLAGS) -o $@ obj/$<
	sed -i "s/#define yyFlexLexer yyFlexLexer//g" $@
