file1 = open("part2num.in", "r")
gile1 = open("part2num.out", "w")

line = file1.readline()

def getNumber(curStr):
    curList = curStr.split('+')
    cur_sum, length = 0, len(curList)
    curIntList = [0] * length
    for i in range(length):
        curIntList[i] = int(curList[i])
        cur_sum += curIntList[i]

    dp = [[0] * (cur_sum + 2) for i in range(cur_sum + 1)]

    for i in range(cur_sum + 1):
        dp[0][i] = 1

    for i in range(1, cur_sum + 1):
        for j in range(cur_sum, 0, -1):
            dp[i][j] += dp[i][j + 1]
            if i >= j:
                dp[i][j] += dp[i - j][j]

    result, m = 0, 1

    for i in range(length):
        for j in range(m, curIntList[i]):
            if cur_sum >= j:
                result += dp[cur_sum - j][j]
        m = curIntList[i]
        cur_sum -= curIntList[i]

    gile1.write(str(result))

getNumber(line)

file1.close()
gile1.close()