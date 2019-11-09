def nextPartition(part: list) -> list:
    part[len(part) - 1] -= 1
    part[len(part) - 2] += 1
    if part[len(part) - 2] > part[len(part) - 1]:
        part[len(part) - 2] += part[len(part) - 1]
        part.pop()
    else:
        while 2 * part[len(part) - 2] <= part[len(part) - 1]:
            part.append(part[len(part) - 1] - part[len(part) - 2])
            part[len(part) - 2] = part[len(part) - 3]
    return part


file1 = open("nextpartition.in", "r")
gile1 = open("nextpartition.out", "w")

line = file1.readline().split()
partition = line[0].split('=')
first_part = partition[0]
second_part = partition[1].split('+')
second_part_ = [''] * len(second_part)

for i in range(len(second_part)):
    second_part_[i] = int(second_part[i])

if len(second_part_) == 1:
    gile1.write("No solution")
else:
    result = nextPartition(second_part_)
    gile1.write(first_part + '=')
    for i in range(len(result)):
        if i != len(result) - 1:
            gile1.write(str(result[i]) + '+')
        else:
            gile1.write(str(result[i]))

file1.close()
gile1.close()