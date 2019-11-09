def counting_sort(cur_array, mn, mx):
    if mx > max(cur_array):
        mx = max(cur_array)
    count, result = [0] * (max(cur_array) + 1), []
    i, j = 0, mn
    while i < len(cur_array):
        count[cur_array[i]] += 1
        i += 1
    while j <= mx:
        result += [j] * count[j]
        j += 1
    return result

a = [int(i) for i in input().split()]
print(*counting_sort(a, 0, 100))