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

function message
{
    if [ -z "$1" ]; then
        echo "internal error"
        exit -1
    fi
    echo "ci: $1"
}

function usage
{
    message "usage: ci.sh <template> <branch>"
}

function warning
{
    message "warning: $1"
}

function error
{
    echo "ci: error: $1"
    usage
}

template=$1
if [ -z "$1" ]; then
    error "missing template"
    exit -1
fi

branch=$2
if [ -z "$2" ]; then
    branch=`git branch | grep "*" | sed -e "s/\* //g"`
    warning "missing branch, using '$branch'"
fi

obj=obj

tempname=`basename $1 .yml`
branch_filename=`echo $branch | sed -e 's/\//-/g'`

mkdir -p $tempname
config=$tempname/$branch_filename.yml
#mkdir -p $obj
#config=$obj/$tempname.yml
cp $template $config

message "created '$config'"

sed -i -e "s/{{branch}}/$branch_filename/g" $config
#sed -i -e "s/{{template}}/$tempname/g" $config

message "patched '$config'"
message ">>>"

cat $config

message "<<<"
