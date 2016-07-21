#!/bin/bash
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

function usage
{
    echo "ci: usage: ci.sh <template> <branch>"
}

function error
{
    if [ -z "$1" ]; then
        echo "internal error"
        exit -1
    fi
    echo "ci: error: $1"
    usage
}

if [ -z "$1" ]; then
    error "missing template"
    exit -1
fi

if [ -z "$2" ]; then
    error "missing branch"
    exit -1
fi

template=$1

tempname=`basename $1 .yml`

branch=$2
branch_replace=`echo $branch | sed -e 's/\//\\\\\//g'`
branch_filename=`echo $branch | sed -e 's/\//_/g'`

mkdir -p $tempname

config=$tempname/$branch_filename.yml

cp $template $config

echo "ci: created '$config'"
sed -i -e "s/BRANCH/$branch_replace/g" $config
