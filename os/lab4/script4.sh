#!/bin/bash

# nice - run process with certain priority
# $! - PID 
# renice - change priority
# cpulimit -p PID -l COUNT - change limit CPU usage of the process by acting with PID to COUNT
# +10 - read man nice 

nice ./script4_1.sh&pid1=$!
nice ./script4_1.sh&pid2=$!

renice +10 $pid1

cpulimit -p $pid1 -l 20 &
cpulimit -p $pid2 -l 20 &