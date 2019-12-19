def merge(A, p, r, q):
    max_a = A[r]
    if max_a < A[q]:
        max_a = A[q]
        
    kp = r - p + 1
    p1 = p
    
    Bp = []
    for i in range(kp):
        Bp.append(A[p1 + i])
    Bp.append(max_a)
    
    kq = q - r
    
    Bq = []
    for i in range(kq):
        Bq.append(A[r + i + 1])
    Bq.append(max_a)
    
    pp = 0
    pq = 0
    for i in range(p, q + 1):
        if Bp[pp] < Bq[pq]:
            A[i] = Bp[pp]
            pp += 1 if pp < kp else 0
        else:
            A[i] = Bq[pq]
            pq += 1 if pq < kq else 0
        
def merge_sort(A, p, q):
    if p != q:
        r = (p + q) // 2
        merge_sort(A, p, r)
        merge_sort(A, r + 1, q)
        
        merge(A, p, r, q)
    
    return A
    
print(merge_sort([9, 9, 0, 3, 0, 2], 0, 5))

from random import randint

for i in range(1, 1000):
    test_arr = [randint(0, 100000) for j in range(i)]

    try:
        t1 = merge_sort(test_arr[:], 0, i - 1)
    except:
        print(test_arr, i - 1)
    test_arr.sort()

    if t1 != test_arr:
        print("Error:", t1, test_arr)
