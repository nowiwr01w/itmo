def add(heap, elem):
    heap.append(elem)
    cur_pos = len(heap) - 1
    while cur_pos > 1 and heap[cur_pos] > heap[cur_pos // 2]:
        heap[cur_pos], heap[cur_pos // 2] = heap[cur_pos // 2], heap[cur_pos]
        cur_pos = cur_pos // 2

def pop(heap):
    if len(heap) == 2:
        return heap.pop()
    res = heap[1]
    heap[1] = heap.pop()
    cur_index = 1
    while 2 * cur_index < len(heap):
        max_idx = 2 * cur_index
        max_val = heap[2 * cur_index]
        if 2 * cur_index + 1 < len(heap) and heap[2 * cur_index + 1] > max_val:
            max_idx = 2 * cur_index + 1
            max_val = heap[2 * cur_index + 1]
        if max_val <= heap[cur_index]:
            return res
        else:
            heap[cur_index], heap[max_idx] = heap[max_idx], heap[cur_index]
            cur_index = max_idx
    return res

def siftDiwn(heap, cur_index, size):
    while 2 * cur_index < size:
        max_idx = 2 * cur_index
        max_val = heap[2 * cur_index]
        if 2 * cur_index + 1 < len(heap) and heap[2 * cur_index + 1] > max_val:
            max_idx = 2 * cur_index + 1
            max_val = heap[2 * cur_index + 1]
        if max_val <= heap[cur_index]:
            return
        else:
            heap[cur_index], heap[max_idx] = heap[max_idx], heap[cur_index]
            cur_index = max_idx


heap = [0]
n = int(input())
for i in range(n):
    cur_str = input().split()
    if len(cur_str) == 1:
        print(heap[1])
        pop(heap)
    else:
        add(heap, int(cur_str[1]))
close