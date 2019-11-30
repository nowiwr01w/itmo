#!/bin/bash
 
trash=~/.trash
trashLog=~/.trash.log
 
restore_file () {
    path=$1
    fileName=$2
    ln "$trash/$fileName" $path
}
 
 
fileName=$1
line=""
grep $fileName $trashLog |
while read line; do
 
    file_to_restore=$(echo $line | cut -d ":" -f 1)
    file_in_trash=$(echo $line | cut -d ":" -f 2)
 
    echo $file_in_trash
 
    echo "Restore $file_to_restore ? (y/n)"
    read answer < /dev/tty
    if [[ "$answer" == "y" ]]; then
        parent_directory=$(dirname "$file_to_restore") &&
            if [[ -d "$parent_directory" ]]; then
                $(restore_file "$file_to_restore" "$file_in_trash")
            else
                $(restore_file "$HOME/$fileName" "$file_in_trash") &&
                    echo "Directory $parent_directory not exists anymore, restoring at $HOME"
            fi &&
            rm $trash/$file_in_trash && {
                sed -i "/$file_in_trash/d" $trashLog
                echo "Restored $file_to_restore"
            }
    fi
done