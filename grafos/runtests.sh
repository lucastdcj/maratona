#!/bin/bash

COMPILE='g++ -g -W -Wall'

for t in testes/*.cpp ; do
    name=`echo $t | sed -e s%.cpp%%`
    $COMPILE $name.cpp -o $name
    $name < $name.in > $name.out
    cmp $name.out $name.res
    rm $name
done
