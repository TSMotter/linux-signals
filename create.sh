#!/usr/bin/env bash

mkdir $1

echo "# Creates a binary target
add_executable($1 $1.c)" > $1/CMakeLists.txt

cp helloworld/helloworld.c $1/$1.c

touch $1/readme.md

echo "# $1" > $1/readme.md