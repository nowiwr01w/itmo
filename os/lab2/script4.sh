#!/bin/bash

dr="/bin/"

for file in $(ls $dr)
do
	if [[ -r "$dr/$file" && -x "$dr/$file" ]]
	then
		grep -E -o -s "^#!$dr.*" "$dr/$file" | sed -E "s/^/$file /"
	fi
done 

# -r и -x это ключи доступа к файлам