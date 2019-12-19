def heapify(sqc, end, i):   
    l = 2 * i + 1  
    r = 2 * (i + 1)   
    max_i = i   
    if l < end and sqc[i] < sqc[l]:   
        max_i = l   
    if r < end and sqc[max_i] < sqc[r]:   
        max_i = r   
    if max_i != i:
        sqc[i], sqc[max_i] = sqc[max_i], sqc[i]
        heapify(sqc, end, max_i)   

# пирамидальная сортировка
# sqc - массив
def heap_sort(sqc):     
    end = len(sqc)   
    start = end // 2 - 1
    for i in range(start, -1, -1):   
        heapify(sqc, end, i)   
    for i in range(end - 1, 0, -1):   
        sqc[i], sqc[0] = sqc[0], sqc[i]
        heapify(sqc, i, 0)

    return sqc

#sqc = [2, 7, 1, -2, 56, 5, 3]
#print(heap_sort(sqc[:]))
#print(sqc)
