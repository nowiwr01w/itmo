file1 = open('mtf.in', 'r')
gile = open('mtf.out', 'w')
 
def mtf(cur_string, alphabet):
    result_answer = []
    current_alphabet = sorted(list(set(alphabet)))
    for symbol in cur_string:
        index = current_alphabet.index(symbol)
        result_answer.append(index + 1)
        deleted_element = current_alphabet.pop(index)
        current_alphabet = [deleted_element] + current_alphabet
    return result_answer
 
cur_dict = []
for i in range(97, 123):
    cur_dict.append(chr((i)))
 
cur_str = file1.readline()
 
new_str = ""
for i in cur_str:
    if i in cur_dict:
        new_str += i
 
for i in mtf(new_str, new_str):
    gile.write(str(i))
    gile.write(" ")
 
gile.close()
file1.close()