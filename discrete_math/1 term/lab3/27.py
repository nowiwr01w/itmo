def nextBrackets(cur_string):
    open, close, ind = 0, 0, len(cur_string) - 1
    cur_list = list(cur_string)
    while ind != -1:
        if (cur_list[ind] == '('):
            open += 1
        else:
            close += 1
        if (cur_list[ind] == '(' and open < close):
            break
        ind -= 1
    if (ind == -1):
        return "-"
    cur_list[ind] = ')'
    ind += 1
    while open > 0:
        cur_list[ind] = '('
        ind += 1
        open -= 1
    while ind < len(cur_list):
        cur_list[ind] = ')'
        ind += 1
    return cur_list

file1 = open("nextbrackets.in", "r")
gile1 = open("nextbrackets.out", "w")

line = file1.readline().split()
result = nextBrackets(line[0])
for string in result:
    gile1.write(string)

file1.close()
gile1.close()