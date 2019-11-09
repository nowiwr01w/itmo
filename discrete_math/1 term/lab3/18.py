file1 = open("brackets2num.in", "r")
gile1 = open("brackets2num.out", "w")

# file1 = open("input.txt", "r")
# gile1 = open("output.txt", "w")

cur_str = file1.readline()
length = len(cur_str) // 2
dp = [[0] * (length + 2) for i in range(2 * length + 1)]

dp[0][0] = 1

for i in range(2 * length):
    for j in range(length + 2):
        if j + 1 <= length + 1:
            dp[i + 1][j + 1] += dp[i][j]
        if j > 0:
            dp[i + 1][j - 1] += dp[i][j]

number = depth = 0

for i in range(2 * length):
    if cur_str[i] == '(':
        depth += 1
    else:
        number += dp[2 * length - i - 1][depth + 1]
        depth -= 1

gile1.write(str(number))