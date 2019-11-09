def getNextSetPartition(cur_list):
    used = []
    for ind in range(len(cur_list) - 1, -1, -1):
        last = cur_list[ind][len(cur_list[ind]) - 1]
        used.sort()
        found = -1
        for ind1 in range(len(used)):
            if used[ind1] > last:
                found = used[ind1]
                break
        if found != -1:
            cur_list[ind].append(found)
            for element in used:
                if element != found:
                    cur_list.append([element])
            return
        if len(cur_list[ind]) == 1:
            used.append(last)
            cur_list.pop()
        else:
            used.append(last)
            cur_list[ind].pop()
            for ind1 in range(len(cur_list[ind]) - 1, 0, -1):
                cur = cur_list[ind][ind1]
                used.sort()
                found = -1
                for ind2 in range(len(used)):
                    if used[ind2] > cur:
                        found = used[ind2]
                        break
                if found != -1:
                    cur_list[ind][ind1] = found
                    for element in used:
                        if element == found:
                            element = cur
                        cur_list.append([element])
                    return
                used.append(cur)
                cur_list[ind].pop()
            used.append(cur_list[ind][0])
            cur_list.pop()
    used.sort()
    for element in used:
        cur_list.append([element])
    return

file1 = open("nextsetpartition.in", "r")
gile1 = open("nextsetpartition.out", "w")

line = file1.readlines()
for i in range(len(line)):
    if line[i][len(line[i]) - 1:] == '\n':
        line[i] = line[i][:len(line[i]) - 1]

i = 0
while i < len(line):
    if line[i] == '':
        i += 1
        continue
    cur_list = []
    temp_array = []
    n, k = int(line[i].split()[0]), int(line[i].split()[1])
    if k == 0:
        break
    for j in range(i + 1, i + k + 1):
        temp_list = line[j].split()
        for elem in temp_list:
            temp_array.append(int(elem))
        cur_list.append(temp_array)
        temp_array = []
    getNextSetPartition(cur_list)
    gile1.write(str(n) + ' ')
    gile1.write(str(len(cur_list)) + '\n')
    for array in cur_list:
        for element in array:
            gile1.write(str(element) + ' ')
        gile1.write('\n')
    gile1.write('\n')
    cur_list = []
    i = i + k + 1

file1.close()
gile1.close()
