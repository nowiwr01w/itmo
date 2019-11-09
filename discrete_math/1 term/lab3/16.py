file1 = open("choose2num.in", "r")
gile1 = open("choose2num.out", "w")
line = file1.readline()
n, count = int(line.split()[0]), int(line.split()[1])
perm = [int(x) for x in file1.readline().split()]
factorials = [1] + [0 for i in range(n - 1)]
for i in range(1, n):
    factorials[i] = factorials[i - 1] * (i + 1)
number, start_numder = 0, 1
for i in range(count - 1):
    digit = perm[i]
    for j in range(start_numder, digit):
        temp_choose = int(factorials[n - j - 1] // (factorials[n - j - count + i] * factorials[count - i - 2]) + 0.01)
        number += temp_choose
    start_numder = digit + 1
number += perm[count - 1] - start_numder
gile1.write(str(number))
file1.close()
gile1.close()