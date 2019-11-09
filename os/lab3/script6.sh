#!/bin/bash

# bc - standart calculator
# -d - use : instead of tab
# -f - only this fields

cnt=0
sum=0
previous_ppid=-1

while read line
do
	echo $line
	ppid=$(echo $line | cut -d ":" -f 2 | grep -E -s -o "[0-9]+")
	sleepavg=$(echo $line | cut -d ":" -f 3 | grep -E -s -o "[0-9]+")
	if (( previous_ppid != -1 && ppid != previous_ppid ))
	then
		echo Average_Sleeping_Children_of_ParentID=$previous_ppid is $(echo "scale=2; $sum / $cnt" | bc -l)
		cnt=0
		sum=0
	fi

	sum=$(echo "scale=2; $sum + $sleepavg" | bc -l)
	previous_ppid=$ppid
	((cnt++))

done < task5.txt > task6.txt

echo Average_Sleeping_Childred_of_ParentID=$previous_ppid is $(echo "scale=2; $sum / $cnt" | bc -l) >> task6.txt

# Итак, это задание базируется на 5-ом, поэтому мы сначала запускаем пятый скрипт.
# Дальше идём while-ом построчно. Делаем примерно то же самое действие, что и в 5-ом скрипте: с помощью grep ищем PPID родителя и время сна.
# Считаем количество подряд идущих процессов с одинаковым PPID. Если череда одинаковых строк заканчивается,
# то мы выводим количество процессов, у которых был такой PPID и среднее арифметическое времени сна.
# echo "scale=2; $sum + $sleepavg" | bc -l
# Эта строчка говорит: посчитай мне сумму двух переменных, подключив при этом библиотеку bc с ключом l (для математических вычислений)
# Последнее действие мы повторяем ещё раз, потому что мы не выведем информацию про самую последнюю череду процессов с одинаковым PPID