#!/bin/bash
ARRAY=(ver01 ver02 ver03a ver03b ver04a ver04b ver04c ver04d ver05)
ELEMENTS=${#ARRAY[@]}
for (( i=0;i<$ELEMENTS;i++)); do
	echo "Compiling ${ARRAY[${i}]}.cc ..."
 	g++ ${ARRAY[${i}]}.cc --std=c++14 -lcurl -lcurlpp  -lpthread -Wall -Wextra -O -pedantic -o exe-${ARRAY[${i}]}
done
echo "Done."
