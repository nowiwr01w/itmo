#!/bin/bash
 
restore=~/restore/
if [[ ! -d "$restore" ]];
then
    mkdir $restore
fi
 
lastBackup=$(find ~/Backup-* -maxdepth 0 | sort -n | tail -n 1)"/"
 
for file in $(ls $lastBackup -1);
do
    if [ -z "$(echo $file | grep -E "*.[0-9]{4}-[0-9]{2}-[0-9]{2}")" ]
    then
        cp -r $lastBackup$file $restore$file
    fi
done