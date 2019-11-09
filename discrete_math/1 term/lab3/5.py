file1 = open("telemetry.in", "r")
gile = open("telemetry.out", "w")

# file1 = open("input.txt", "r")
# gile = open("output.txt", "w")

cur_str = file1.readline()
length, k = int(cur_str.split()[0]), int(cur_str.split()[1])
len1 = k ** length

vectors = [0] * len1

for i in range(k):
    vectors[i] = str(i)

count = k

while len(vectors[0]) < length:
    i = 0
    for j in range(2 * count - 1, count - 1, -1):
        vectors[j] = vectors[i]
        i += 1

    repeat, last = k // 2, 2 * count

    for c in range(repeat - 1):
        for j in range(2 * count):
            vectors[last] = vectors[j]
            last += 1

    if k % 2 == 1:
        for j in range(count):
            vectors[last] = vectors[j]
            last += 1

    last = 0

    for j in range(k):
        for c in range(count):
            vectors[last] += str(j)
            last += 1

    count *= k

for i in range(len1):
    gile.write(vectors[i])
    gile.write('\n')
