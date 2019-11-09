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
 
def isNull(function):
    return function[0] == '0'
 
def isOne(function):
    return function[len(function) - 1] == '1'
 
def isMonotone(function):
    if len(function) == 1:
        return True
    midle = len(function) // 2
    for i in range(midle):
        if function[i] > function[i + midle]:
            return False
    return isMonotone(function[0 : midle]) and isMonotone(function[midle : ])
 
def isSelfDual(function):
    for i in range(len(function)):
        if function[i] == function[len(function) - 1 - i]:
            return False
    return True
 
def isLinear(function):
    coefPolinom = list(map(int, function))
    zeroArray = [0]*(len(coefPolinom) - 1)
    polinom = treg(coefPolinom, zeroArray)
    index = 0
    for i in range(len(polinom)):
        current = polinom[i]
        if current == 1:
            if i != index:
                return False
            if index == 0:
                index = 1
            else:
                index *= 2
        if i == index:
            if index == 0:
                index = 1
            else:
                index *= 2
    return True
 
n = int(input())
saveZero = saveOne = saveLinear = saveMonoton = saveSelfDual = True
for i in range(n):
    dataValue, bulValue = map(str, input().split())
    if not isOne(bulValue):
        saveOne = False
    if not isNull(bulValue):
        saveZero = False
    if not isLinear(bulValue):
        saveLinear = False
    if not isMonotone(bulValue):
        saveMonoton = False
    if not isSelfDual(bulValue):
        saveSelfDual = False
if not(saveZero or saveOne or saveLinear or saveMonoton or saveSelfDual):
    print('YES')
else:
    print('NO')