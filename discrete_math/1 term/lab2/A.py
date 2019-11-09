file = open('huffman.in', 'r')
gile = open('huffman.out', 'w')
n = int(file.readline())
a = list(map(int, file.readline().split()))
sb = 0
while len(a) > 1:
    a.sort()
    a.reverse()
    m1 = a.pop()
    m2 = a.pop()
    sb += m1 + m2
    a.append(m1 + m2)
gile.write(str(sb))
gile.close()
file.close()