file1 = open("nextchoose.in", "r")
gile1 = open("nextchoose.out", "w")

line1 = file1.readline().split()
line2 = file1.readline().split()

end = result = ""
digits, countInLine = int(line1[0]), int(line1[1])

perm = [0] * countInLine
for i in range(countInLine - 1, -1, -1):
    end += str(digits - i) + ' '
    perm[countInLine - i - 1] = int(line2[countInLine - i - 1])
    result += str(perm[countInLine - i - 1]) + ' '

if end == result:
    result = '-1'
else:
    result = ""
    marker = g = countInLine - 1
    while g > 0 and perm[g] == digits - countInLine + g + 1:
        marker = g - 1
        g -= 1
    perm[marker] += 1
    for i in range(marker + 1, countInLine):
        perm[i] = perm[i - 1] + 1
    for i in range(countInLine):
        result += str(perm[i]) + ' '

gile1.write(result)
file1.close()
gile1.close()
