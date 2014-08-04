#!/bin/bash

name=plt-r5rs
command=plt-r5rs

if [[ ! -e gen ]]; then
	echo "Compiling gen"
	g++ -std=c++11 -o gen gen.cpp
fi
rm -f ${name}.log

for depth in 2 4
do
	
	for (( i = 0; i < 10; ++i ))
	do
		echo "testing ${depth} ${i}" | tee -a ${name}.log 
		./gen ${depth} ${depth} 1000 > ${name}_${depth}_${i}.in 
		plt-r5rs ${name}_${depth}_${i}.in > ${name}_${depth}_${i}.out
		
		${command} ${name}_${depth}_${i}.in > tmp.out
		if [[ $? == 0 ]]; then

			diff tmp.out ${name}_${depth}_${i}.out 
			if [[ $? == 0 ]]; then
				echo "CORRECT" | tee -a ${name}.log
			else
				cp tmp.out wrong_${depth}_${i}.out
				echo "WRONG" | tee -a ${name}.log
			fi
		else 
		
			echo "RE" | tee -a ${name}.log
		fi
	done
done
