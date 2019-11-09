def getChoose(n: int, k: int) -> int:
    result = 1
    for i in range(1, k + 1):
        result *= (n - k + i) / i
    return int(result)


def num2choose(n: int, k: int, m: int) -> list:
    combinations = [[1] * (n + 1) for i in range(k + 1)]
    for i in range(k + 1):
        for j in range(n + 1):
            combinations[i][j] = getChoose(j, i)

    next, combinations[0][n], choose = 1, 1, []

    while k > 0:
        if m >= combinations[k - 1][n - 1]:
            m -= combinations[k - 1][n - 1]
        else:
            k -= 1
            choose.append(next)
        n -= 1
        next += 1

    return choose


file1 = open("num2choose.in", "r")
gile1 = open("num2choose.out", "w")

# file1 = open("input.txt", "r")
# gile1 = open("output.txt", "w")

line = file1.readline()
n, k, m = int(line.split()[0]), int(line.split()[1]), int(line.split()[2])
cur_vec = num2choose(n, k, m)

for elem in cur_vec:
    gile1.write(str(elem) + ' ')

file1.close()
gile1.close()

