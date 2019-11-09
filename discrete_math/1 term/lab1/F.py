def treg(a, b):
    resArray = []
    resArray.append(a[0])
    while len(a) != 0 and len(b) != 0:
        if len(a) > len(b):
            for i in range(len(a) - 1):
                b[i] = (a[i] + a[i+1]) % 2
            resArray.append(b[0])
            a = [0]*(len(b) - 1)
        elif len(a) <= len(b):
            for i in range(len(b) - 1):
                a[i] = (b[i] + b[i+1]) % 2
            resArray.append(a[0])
            b = [0] * (len(a) - 1)
    return resArray
 
n = int(input())
valueOfBul = []
tablValue = []
for i in range(2 ** n):
    a, b = map(str, input().split())
    tablValue.append(a)
    valueOfBul.append(int(b))
zeroArray = [0]*(2 ** n - 1)
resArray = treg(valueOfBul, zeroArray)
for i in range(2 ** n):
    print(tablValue[i], resArray[i])