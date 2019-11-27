#!/bin/bash

# mkdir - create folder
# touch - remane file
# ping -c 1 - count of requests
# 2 - error code

mkdir ~/test && echo "catalog test was created successfully" > ~/report.txt && touch ~/test/$(date '+%d.%m.%y_%H:%M:%S')
ping -c 1 "www.net_nikogo.ru" 2>> ~/report.txt 
