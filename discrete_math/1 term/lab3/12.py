file1 = open("part2sets.in", "r")
gile1 = open("part2sets.out", "w")

# file1 = open("input.txt", "r")
# gile1 = open("output.txt", "w")

def generatePartSets(cur_vec: list, n: int, k: int, i: int, j: int):
    if i == n and j != k:
        return
    elif i == n:
        vec_str: list = [""] * k
        for i in range(n):
            vec_str[cur_vec[i]] += str(i + 1) + " "
        vec_str = sorted(vec_str)
        for temp in vec_str:
            if len(temp) != 0:
                gile1.write(temp + '\n')
        gile1.write('\n')
    else:
        for temp in range(j + 1):
            cur_vec[i] = temp
            if temp != j:
                generatePartSets(cur_vec, n, k, i + 1, j)
            else:
                generatePartSets(cur_vec, n, k, i + 1, j + 1)


line = file1.readline()
n, k = int(line.split()[0]), int(line.split()[1])
cur_vec: list = [0] * n

generatePartSets(cur_vec, n, k, 0, 0)
