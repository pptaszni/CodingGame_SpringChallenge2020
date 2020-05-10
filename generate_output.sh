#!/bin/bash

rm output.cpp

headers=`find . -not \( -path ./build -prune \) -not \( -path ./tests -prune \) -name "*.hpp"`
sources=`find . -not \( -path ./build -prune \) -not \( -path ./tests -prune \) -name "*.cpp"`

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
