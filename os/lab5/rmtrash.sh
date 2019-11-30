#!/bin/bash
 
fileName=$1
trash=~/.trash
trashLog=~/.trash.log

if [[ $# -ne 1 ]]
then
    exit 1
fi

if [[ ! -d $trash ]]
then
        mkdir $trash
fi

echo "Delete $fileName ? (y/n)"
read answer < /dev/tty

if [[ "$answer" == "y" ]]; then
    trashFile=$(date +%s)
    ln $fileName "$trash/$trashFile"
    rm $fileName
    if [[ ! -e $trashLog ]]
    then
        touch $trashLog
    fi
echo "$PWD/$fileName:$trashFile" >> $trashLog
fi