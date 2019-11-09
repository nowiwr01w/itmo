n, x, y = map(int, input().split())
left, right = 0, (n - 1) * max(x, y)
while left < right:
    middle = (left + right) // 2
    first = middle // x
    second = middle // y
    if first + second < n - 1:
        left = middle + 1
    else:
        right = middle
print(right + min(x, y))