import math


def getNumber2Perm(cur_perm: list) -> int:
    result, length = 0, len(cur_perm)
    cur_fact = math.factorial(length - 1)

    mult = [True] * length

    for i in range(length):
        cur_position = 0
        for j in range(cur_perm[i]):
            if mult[j]:
                cur_position += 1

        mult[cur_perm[i] - 1] = False
        result += (cur_position - 1) * cur_fact

        if length - i - 1 != 0:
            cur_fact //= length - i - 1

    return result


file1 = open("perm2num.in", "r")
gile1 = open("perm2num.out", "w")

line, line1 = file1.readline(), file1.readline()
n: int = int(line)
cur_perm: list = [int(x) for x in line1.split()]

gile1.write(str(getNumber2Perm(cur_perm)))
