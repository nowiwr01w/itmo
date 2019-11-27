#!/bin/bash

while true
do
	read line
	echo "$line" >> file.txt

	if [[ "$line" == "QUIT" ]]
	then
		exit 0
	fi

	if [[ ! "$line" =~ [0-9]+ && "$line" != "+" && "$line" != "*" ]]
	then
		echo "Stopped by incorrect message"
		exit 1
	fi
done