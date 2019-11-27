#!/bin/bash

# $$ - system PID variable
# trap action signal - signal + action = love (action == function above)

echo $$ > script6.sh

mode="do"

handle()
{
	mode="stop"
}

cnt=0

trap 'handle' SIGTERM

while true
do
    case $mode in
        "do")
            cnt=$(($cnt + 1))
            ;;
        "stop")
            echo "Stopped by SIGTERM signal"
            exit 0
            ;;
    esac
    sleep 1
done