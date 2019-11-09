#!/bin/bash

for pid in $(ps -A -o pid)
do
	ppid=$(grep -E -s -h "PPid" /proc/$pid/status | grep -E -s -o "[0-9]+")
	sleepavg=$(grep -E -s -h "avg_atom" /proc/$pid/sched | grep -E -s -o "[0-9.]+")

	if [ -z $ppid ]
	then
		ppid=0
	fi 

	if [ -z $sleepavg ]
	then
		sleepavg=0
	fi

	echo "ProcessID="$pid" : Parent_ProcessID="$ppid" : Average_sleeping_Time=$="$sleepavg

done | sort -t " " -k2 > task5.txt

# Мы проходимся for-ом по всем PID из списочка действующих процессов. Далее мы пытаемся вычленить из файлов status и sched, 
# соответствующих текущему процессу, инфу о родительском процессе (PPID) и время бездействия (sleepavg). 
# Делаем это с помощью наших любимых регулярочек и команды grep.
# Если вдруг в поля ppid и sleepavg ничего не записалось, то поставим туда честные нули.
# Далее - вывод в нужном формате и сортировка