#!/bin/bash

g++ -std=c++11 generate.cpp -o generate
g++ -std=c++11 ../submissions/accepted/paul.cpp -o paul

while read line; do
	name=secret/`echo $line | tr ' ' '-'`.in
	if [ ! -e $name ]; then
		echo Creating $name...
		echo $line | cut -d' ' -f2- | ./generate > $name
		./paul < $name > ${name%.in}.ans
	fi
done < cases.txt

rm generate paul
