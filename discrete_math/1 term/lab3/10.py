file1 = open("partition.in", "r")
gile = open("partition.out", "w")

# file1 = open("input.txt", "r")
# gile = open("output.txt", "w")

def generate(a, n):
    if n == 0:
        gile.write(str(a[1]))
        for i in a[2 : ]:
            gile.write('+{0}'.format(i))
        gile.write('\n')
    else:
        if (n >= a[len(a) - 1]):
            for i in range(max(1, a[len(a) - 1]), n + 1):
                generate(a + [i], n - i)

n = int(file1.readline())
generate([0], n)