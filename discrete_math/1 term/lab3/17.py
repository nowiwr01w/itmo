file1 = open("num2brackets.in", "r")
gile1 = open("num2brackets.out", "w")

line = file1.readline()
count, number = 2 * int(line.split()[0]), int(line.split()[1])
dp = [[0] * (count + 2) for i in range(count)]

dp[0][1] = 1
for i in range(1, count):
    for j in range(1, i + 2):
        dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j + 1]

result_string = ""
cur_balance = count_open = 0

for i in range(count - 1, -1, -1):
    if count_open < count // 2:
        if number < dp[i][cur_balance + 2] and cur_balance < count - count_open:
            result_string += '('
            count_open += 1
            cur_balance += 1
        elif cur_balance > 0:
            result_string += ')'
            number -= dp[i][cur_balance + 2]
            cur_balance -= 1
    else:
        break

for j in range(count_open, count // 2):
    result_string += '('

end = count - len(result_string)

for j in range(end):
    result_string += ')'

gile1.write(result_string)
file1.close()
gile1.close()
