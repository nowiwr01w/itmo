w, h, n = map(float, input().split())
left, right = 0, 1
while (right // w) * (right // h) < n:
    right *= 2
while left + 1 < right:
    middle = (left + right) / 2
    if (middle // w) * (middle // h) < n:
        left = middle
    else:
        right = middle
print(int(right))