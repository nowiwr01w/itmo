#!/bin/bash

echo $$ > .pid
num=1

mode="add"
add()
{
	mode="add"
}

multiply()
{
	mode="multiply"
}

term()
{
	echo "STOP"
	exit
}

trap 'term' SIGTERM
trap 'add' USR1
trap 'multiply' USR2

while true
do
	case $mode in
	"add")
		let num=$num+2
		;;
	"multiply")
		let num=$num*2
		;;
	esac
	echo $num
	sleep 1
done 