# Start with: ./b.txt 8 4 9

#Количество параметров
counter=$#
cur_maximum=$1

if [[ counter -eq 1 ]] 
then
    echo "Param 1: "$1
    exit
fi
if [[ counter -eq 2 ]]
then
    echo "Param 1: "$1
    echo "Param 2: "$2
    exit
fi
	
if [[ cur_maximum -lt $2 ]]
then
cur_maximum=$2
fi

if [[ cur_maximum -lt $3 ]]
then
cur_maximum=$3
fi

echo $cur_maximum