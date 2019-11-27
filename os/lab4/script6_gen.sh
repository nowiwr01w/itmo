#!/bin/bash

# $(cat script6.sh) - transition signal through script6.sh

while true
do
	read line
	if [[ $line = "TERM" ]]
		then
			echo "TERMINATION"
			kill -SIGTERM $(cat script6.sh)
			exit
	fi
done