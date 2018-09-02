#!/bin/bash
# 
#   Copyright (C) 2017-2018 CASM Organization <https://casm-lang.org>
#   All rights reserved.
# 
#   Developed by: Philipp Paulweber
#                 <https://github.com/casm-lang/casm-lang.container.linux>
# 
#   This file is part of casm-lang.container.linux.
# 
#   casm-lang.container.linux is free software: you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation, either version 3 of the License, or
#   (at your option) any later version.
# 
#   casm-lang.container.linux is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
#   GNU General Public License for more details.
# 
#   You should have received a copy of the GNU General Public License
#   along with casm-lang.container.linux. If not, see <http://www.gnu.org/licenses/>.
# 

APP=`basename $0`

function usage
{
    echo "usage: $APP <generate-token|generate-parser>"
    exit -1
}

function generate_token
{
    local src=$1
    local dst=$2

    mkdir -p `dirname $src`
    cat `dirname $src`/../obj/notice.txt | sed 's/^/\/\/  /g' > $dst
    echo "" >> $dst
    echo "#ifndef _LIBCASM_FE_GRAMMAR_TOKEN_H_" >> $dst
    echo "#define _LIBCASM_FE_GRAMMAR_TOKEN_H_" >> $dst
    echo "" >> $dst
    echo "namespace libcasm_fe" >> $dst
    echo "{" >> $dst
    echo "    namespace Grammar" >> $dst
    echo "    {" >> $dst
    echo "        enum class Token" >> $dst
    echo "        {" >> $dst

    local tokens=`cat $src | grep '.*\"' | sed 's/{ return.*//g' | sed 's/{ YY_.*//g'`
    local mode=name
    declare -i uid=0
    for element in $tokens; do
        #printf "%2i -> %s\n" $uid $element
	if [ "$mode" = "name" ]; then
	    printf "            /* %2i */ $element,\n" $uid >> $dst
	    mode=token
	else
	    # mode token
	    mode=name
            uid+=1
	fi
    done

    echo "        };" >> $dst
    echo "        " >> $dst
    echo "        static std::string tokenAsString( const Token token )" >> $dst
    echo "        {" >> $dst
    echo "            switch( token )" >> $dst
    echo "            {" >> $dst

    mode=name
    uid=0
    for element in $tokens; do
	if [ "$mode" = "name" ]; then
	    printf "                case /* %2i */ Token::$element:\n" $uid >> $dst
	    mode=token
	else
	    # mode token
	    echo "                {" >> $dst
	    printf "                    return %s;\n" $element >> $dst
	    echo "                }" >> $dst
	    mode=name
            uid+=1
	fi
    done

    echo "            }" >> $dst
    echo "        }" >> $dst
    echo "    };" >> $dst
    echo "}" >> $dst
    echo "" >> $dst
    echo "#endif  // _LIBCASM_FE_GRAMMAR_TOKEN_H_" >> $dst
    echo "" >> $dst
    echo "//" >> $dst
    echo "//  Local variables:" >> $dst
    echo "//  mode: c++" >> $dst
    echo "//  indent-tabs-mode: nil" >> $dst
    echo "//  c-basic-offset: 4" >> $dst
    echo "//  tab-width: 4" >> $dst
    echo "//  End:" >> $dst
    echo "//  vim:noexpandtab:sw=4:ts=4:" >> $dst
    echo "//" >> $dst

    exit 0
}

function generate_parser
{
    local src=$1
    local dst=$2
    local grammartoken=$3
    
    mkdir -p `dirname $src`
    
	head -n +`grep -n "{{grammartoken}}" $src | grep -o "[0-9]*"` $src | cat  > $dst
	cat $grammartoken | sed "/^\/\//d" | sed "s/{ /\/\/ {/g"                 >> $dst

    local tokens=`cat $grammartoken | grep '.*\"' | sed 's/{ return.*//g' | sed 's/{ YY_.*//g'`
    local mode=name
    declare -i uid=0
    for element in $tokens; do
        #printf "%2i -> %s\n" $uid $element
	    if [ "$mode" = "name" ]; then
	        echo "%type <Ast::Token::Ptr> $element" >> $dst
	        mode=token
	    else
	        # mode token
	        mode=name
            uid+=1
	    fi
    done

	tail -n +`grep -n "{{grammartoken}}" $src | grep -o "[0-9]*"` $src | cat >> $dst
	sed -i "/^{{grammartoken}}/d" $dst

    exit 0
}


if [ -z "$1" ]; then
    usage
    exit -1
fi

if [ "$1" = "generate-token" ]; then
    generate_token $2 $3
elif [ "$1" = "generate-parser" ]; then
    generate_parser $2 $3 $4
else
    usage
fi
