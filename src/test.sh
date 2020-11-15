#!/bin/bash

prog=$1
path=$2
i=1

tmp_error=$(mktemp)
tmp_out=$(mktemp)

for file in "$path"/*.in
do
	# Poniższa linijka testuje program przy użyciu valgrinda. 
	#valgrind --error-exitcode=15 --leak-check=full --show-leak-kinds=all --errors-for-leak-kinds=all -q > c ./forests<./$prog<$file
	$prog<$file>"$tmp_out" 2>"$tmp_error"
	if diff "$tmp_out" ${file%in}out > /dev/null
	then 
		if diff "$tmp_error" ${file%in}err > /dev/null
		then 
			echo "test$i OK $file"
		else 
		    echo "test$i BLAD $file"
		fi
	else 
		echo "test$i BLAD $file"
	fi
	((i++))
done

rm ${tmp_error}
rm ${tmp_out}
