#!/bin/bash

num_of_files=$1
min_size=$2 
max_size=$3 

rm text*.txt
for (( c=1; c<=num_of_files; c++ ))
do  
   size=$(shuf -i $min_size-$max_size -n 1)
   crfile -f text$c.txt -s $size
done
