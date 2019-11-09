n = int(input())
dp = [[0] * 10 for i in range(n)]
t = [0, 1, 1, 1, 1, 1, 1, 1, 0, 1]
for j in range(10):
    dp[0][j] = t[j]
for t0 in range(1, n):
    for i in range(10):
        if (i == 5):
            continue
        if (i == 0):
            dp[t0][i] = dp[t0 - 1][4] + dp[t0 - 1][6]
        if (i == 1):
            dp[t0][i] = dp[t0 - 1][6] + dp[t0 - 1][8]
        if (i == 2):
            dp[t0][i] = dp[t0 - 1][7] + dp[t0 - 1][9]
        if (i == 3):
            dp[t0][i] = dp[t0 - 1][4] + dp[t0 - 1][8]
        if (i == 7):
            dp[t0][i] = dp[t0 - 1][2] + dp[t0 - 1][6]
        if (i == 8):
            dp[t0][i] = dp[t0 - 1][1] + dp[t0 - 1][3]
        if (i == 9):
            dp[t0][i] = dp[t0 - 1][4] + dp[t0 - 1][2]
        if (i == 4):
            dp[t0][i] = dp[t0 - 1][3] + dp[t0 - 1][9] + dp[t0 - 1][0]
        if (i == 6):
            dp[t0][i] = dp[t0 - 1][1] + dp[t0 - 1][7] + dp[t0 - 1][0]
sum = 0
for j in range(10):
    sum += dp[n-1][j]
print(sum % (10 ** 9))