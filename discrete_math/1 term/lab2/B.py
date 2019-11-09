file1 = open('bwt.in', 'r')
gile = open('bwt.out', 'w')
 
def rotate(l, n):
    return l[n:] + l[:n]
 
def generate(n, cur_list, cur_str):
    for i in range(n):
        cur_list.append(cur_str)
        cur_str = rotate(cur_str, 1)
    cur_list = sorted(cur_list)
    for i in range(n):
        gile.write(cur_list[i][n - 1])
    gile.write('\n')
 
cur_dict = []
for i in range(97, 123):
    cur_dict.append(chr((i)))
 
cur_list = []
cur_str = file1.readline()
 
new_str = ""
for i in cur_str:
    if i in cur_dict:
        new_str += i
length = len(new_str)
 
generate(length, cur_list, new_str)
gile.close()
file1.close()