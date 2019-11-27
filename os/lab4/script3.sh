#!/bin/bash

# crontab - command which running at certain period
# */5 - every five minutes
# 6 - sin day of week

crontab -u nowiwr01 -l > hello.txt
echo "*/5 * * * 6 $HOME/laba4/script1.sh" >> hello.txt
crontab hello.txt