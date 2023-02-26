#!/usr/bin/env bash

echo "====================================="
echo "Running a styling tool:"
echo "-------------------------------------"
source cclang-formatter.sh

echo "====================================="
echo "Building the source code:"
echo "-------------------------------------"
rm -rf build
cmake -S . -B build -D TARGET_GROUP=$1
cmake --build build

echo "====================================="
echo "Basic static code analysis:"
echo "-------------------------------------"
cppcheck --std=c99 --template='{file}:{line},{severity},{id},{message}' $1/$1.c

if [[ $2 == "run" ]]; then
  
  echo "====================================="
  echo "Executing the application:"
  echo "-------------------------------------"
  ./build/$1/$1
fi