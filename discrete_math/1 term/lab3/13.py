import math


def getPermutation(n: int, k: int) -> list:
    result, check = [], [1] * n
    fact = math.factorial(n - 1)
    while n > 0:
        count = number = 0
        it, cur_fact = 1, fact

        while cur_fact <= k:
            it += 1
            cur_fact += fact

        while number < it:
            if check[count] == 1:
                number += 1
            count += 1

        n -= 1
        check[count - 1] = -1
        result.append(count)

        if k != 0:
            k -= (it - 1) * fact
        if n != 0:
            fact //= n

    return result


file1 = open("num2perm.in", "r")
gile1 = open("num2perm.out", "w")

line = file1.readline()
n, k = int(line.split()[0]), int(line.split()[1])
cur_vec: list = getPermutation(n, k)

for elem in cur_vec:
    gile1.write(str(elem) + ' ')
