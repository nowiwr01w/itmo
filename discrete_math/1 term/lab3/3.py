def drawCircleShift(a, n):
    b = ''
    if a[0] == '0' and a.count('0') == n:
        return '1' * n
    if a[0] == '1' and a.count('1') == n:
        return '2' * n
    if a[0] == '2' and a.count('2') == n:
        return '0' * n
    for i in range(n):
        if a[i] == '0': b += '1'
        if a[i] == '1': b += '2'
        if a[i] == '2': b += '0'
    return b


def perevod(n):
    p = ""
    while n > 0:
        y = str(n % 3)
        p = y + p
        n = int(n / 3)
    return p


file1 = open('antigray.in', 'r')
gile = open('antigray.out', 'w')

# file1 = open('input.txt', 'r')
# gile = open('output.txt', 'w')

n = int(file1.readline())
for i in range(0, 3 ** (n - 1)):
    xd = str(perevod(i)).rjust(n, '0')
    a = drawCircleShift(xd, n)
    b = drawCircleShift(a, n)
    gile.write(xd)
    gile.write('\n')
    gile.write(a)
    gile.write('\n')
    gile.write(b)
    gile.write('\n')