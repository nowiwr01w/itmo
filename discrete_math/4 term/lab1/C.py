k = int(input())

c1 = c2 = c11 = 0

p = [0] * 1000000
a = [int(x) for x in input().split()]
c = [-1] + [int(x) for x in input().split()]

for i in range(k + 1):
    с2 = c2 + 1 if c[i] == 0 else 0
        
for i in range(k):
    for j in range(i + 1):
        p[i] += -1 * c[j] * a[i - j]
    c1 += 1
    c11 = c11 + 1 if p[i] == 0 else 0
        
print(c1 - c11 - 1)
for i in range(c1 - c11):
    print(p[i], sep=' ')
    
print(k - c2)
for i in range(k - c2 + 1):
    print(-1 * c[i], end=' ')