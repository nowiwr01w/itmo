file1 = open("vectors.in", "r")
gile = open("vectors.out", "w")

# file1 = open("input.txt", "r")
# gile = open("output.txt", "w")

def getAnswer(n):
    a = [2, 3] + [0] * (n - 2)
    for i in range(2, n):
        a[i] = a[i - 1] + a[i - 2]
    gile.write(str(a[n - 1]))
    gile.write('\n')

def getResult(n, prefix = '', flag = True):
    if (len(prefix) == n):
        gile.write(prefix)
        gile.write('\n')
    else:
        if flag == True:
            getResult(n, prefix + '0')
            getResult(n, prefix + '1', flag=False)
        else:
            getResult(n, prefix + '0')

n = int(file1.readline())

getAnswer(n)
getResult(n)