n = int(input())
d, prev = [0]*n, [0]*n
a = [int(x) for x in input().split()]

for i in range(n):
    d[i], prev[i] = 1, -1
    for j in range(i):
        if a[j] < a[i] and d[j] + 1 > d[i]:
            d[i], prev[i] = d[j] + 1, j

answer = 0
for i in range(n):
    answer = max(answer, d[i])

l, k = [0] * answer, 0
for i in range(1, n):
    if d[i] > d[k]:
        k = i

j = answer - 1
while k > -1:
    l[j] = k
    j -= 1
    k = prev[k]

print(answer)
for i in range(len(l)):
    print(a[l[i]], end=' ')