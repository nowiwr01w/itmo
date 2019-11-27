#!/bin/bash

# at - once run
# -m - when
# -f - add info to file -> print
# -n 0 - don't read in file (updating)

at -m now+2minutes -f ./script1.sh
tail -n 0 -f ~/report.txt