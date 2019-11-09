def rec(dp: list, prev: list, exist: list, left: int, right: int):
    if dp[left][right] == right - left + 1:
        return
    if dp[left][right] == 0:
        for i in range(left, right + 1):
            exist[i] = True
        return
    if prev[left][right] == -1:
        exist[left] = exist[right] = True
        rec(dp, prev, exist, left + 1, right - 1)
        return
    rec(dp, prev, exist, left, prev[left][right])
    rec(dp, prev, exist, prev[left][right] + 1, right)

cur_string: str = input()
cur_length = len(cur_string)
exist: list = [False] * cur_length
dp: list = [[0] * cur_length for i in range(cur_length)]
prev: list = [[0] * cur_length for i in range(cur_length)]

for i in range(cur_length - 1, -1, -1):
    for j in range(i, cur_length):
        best, optimal = 100 * 100 + 1, -1
        if i == j:
            dp[i][j] = 1
        else:
            if (cur_string[i] == '(' and cur_string[j] == ')') or (cur_string[i] == '[' and cur_string[j] == ']') \
                    or (cur_string[i] == '{' and cur_string[j] == '}'):
                best = dp[i + 1][j - 1]
            for k in range(i, j):
                if dp[i][k] + dp[k + 1][j] < best:
                    best = dp[i][k] + dp[k + 1][j]
                    optimal = k
            dp[i][j] = best
            prev[i][j] = optimal

rec(dp, prev, exist, 0, cur_length - 1)

for i in range(cur_length):
    if exist[i]:
        print(cur_string[i], end='')
