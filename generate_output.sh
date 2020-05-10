#!/bin/bash

rm output.cpp

headers=`find . -path ./build -prune -o -name "*.hpp" -print`
sources=`find . -path ./build -prune -o -name "*.cpp" -print`

touch output.cpp

for f in ${headers}
do
  echo ${f}
  cat ${f} >> output.cpp
done

for f in ${sources}
do
  echo ${f}
  cat ${f} >> output.cpp
done

sed -i 's/#include \".*\"//g' output.cpp
