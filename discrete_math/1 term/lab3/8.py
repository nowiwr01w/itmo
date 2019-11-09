file1 = open("choose.in", "r")
gile1 = open("choose.out", "w")

# file1 = open("input.txt", "r")
# gile1 = open("output.txt", "w")

def getCombination(arr, temp, start, end, index, k):
    if index == k:
        for i in range(k):
            gile1.write(str(temp[i]) + ' ')
        gile1.write('\n')
        return
    i = start
    while i <= end and end - i + 1 >= k - index:
        temp[index] = arr[i]
        getCombination(arr, temp, i + 1, end, index + 1, k)
        i += 1

line = file1.readline()
n, k = int(line.split()[0]), int(line.split()[1])
temp = [0] * k
result = [0] * n

for i in range(n):
    result[i] = i + 1

getCombination(result, temp, 0, n - 1, 0, k)
