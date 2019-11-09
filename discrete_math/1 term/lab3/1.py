file1 = open('allvectors.in', 'r')
gile = open('allvectors.out', 'w')

n = int(file1.readline())

for i in range(2 ** n):
    gile.write(bin(i)[2:].rjust(n, '0'))
    gile.write('\n')

file1.close()
gile.close()
