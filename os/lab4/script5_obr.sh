#!/bin/bash

# tail -n 0 - don't read file (updating after tail)
# -f - read if info was added
# kill $$ - end process

prevRes=1
res=1
mode='+'
(tail -n 0 -f file.txt) |
while true
do
    read line;
    case $line in
    '+')
    	mode='+'
    	;;
    '*')
    	mode='*'
    	;;
    [0-9]*) 
	prevRes=$res
        case $mode in
        '+')
     		((res=$res + $line))
    		;;
        '*')
		((res=$res * $line))
		;;

    	esac
        echo "$prevRes$mode$line = $res"
    	;;
     QUIT)
	echo "Result is: $res"
	killall tail
	exit
	;;
    *)
    	echo "Invalid input"
    	kill $$
    	;;
    esac
done