import random
import time
import heap_sort
import merge_sort
import smooth_sort

# Тесты работоспособности
#def print_arr(arr):
#    print('\nОтсортированный массив:')
#    for i in arr:
#        print(i, end=' ')

#arr = list(map(int, input('Массив для сортировки: ').split()))
#heap_sort.heap_sort(arr)
#arr = merge_sort.mergesort(arr)
#arr = smooth_sort.smoothSort(smooth_sort.doListHeaps(arr))
#print_arr(arr)
# конец тестов работоспособности

arr_ms = []
arr_hs = []
arr_ss = []
T1 = open("T1.txt", 'a')
T2 = open("T2.txt", 'a')
T3 = open("T3.txt", 'a')
for i in range(100, 1001, 100):
    s1, s2, s3 = 0, 0, 0
    for j in range(10):
        arr_ms = [random.randint(-10000, 10000) for k in range(i)]
        arr_hs = [random.randint(-10000, 10000) for k in range(i)]
        arr_ss = [random.randint(-10000, 10000) for k in range(i)]
        t1_start = time.perf_counter()
        arr_ms = merge_sort.mergesort(arr_ms)
        t1 = time.perf_counter() - t1_start
        s1 += t1
        t2_start = time.perf_counter()
        heap_sort.heap_sort(arr_hs)
        t2 = time.perf_counter() - t2_start
        s2 += t2
        t3_start = time.perf_counter()
        smooth_sort.smoothSort(smooth_sort.doListHeaps(arr_ss))
        t3 = time.perf_counter() - t3_start
        s3 += t3
    T1.write(str(s1/10))
    T1.write("\n")
    T2.write(str(s2/10))
    T2.write("\n")
    T3.write(str(s3/10))
    T3.write("\n")
T1.close()
T2.close()
T3.close()

arr_ms = []
arr_hs = []
arr_ss = []
T4 = open("T4.txt", 'a')
T5 = open("T5.txt", 'a')
T6 = open("T6.txt", 'a')
for i in range(100, 1001, 100):
    s1, s2, s3 = 0, 0, 0
    for j in range(10):
        arr_ms = [k for k in range(i)]
        arr_hs = [k for k in range(i)]
        arr_ss = [k for k in range(i)]
        t1_start = time.perf_counter()
        arr_ms = merge_sort.mergesort(arr_ms)
        t1 = time.perf_counter() - t1_start
        s1 += t1
        t2_start = time.perf_counter()
        heap_sort.heap_sort(arr_hs)
        t2 = time.perf_counter() - t2_start
        s2 += t2
        t3_start = time.perf_counter()
        smooth_sort.smoothSort(smooth_sort.doListHeaps(arr_ss))
        t3 = time.perf_counter() - t3_start
        s3 += t3
    T4.write(str(s1/10))
    T4.write("\n")
    T5.write(str(s2/10))
    T5.write("\n")
    T6.write(str(s3/10))
    T6.write("\n")
T4.close()
T5.close()
T6.close()

arr_ms = []
arr_hs = []
arr_ss = []
T7 = open("T7.txt", 'a')
T8 = open("T8.txt", 'a')
T9 = open("T9.txt", 'a')
for i in range(100, 1001, 100):
    s1, s2, s3 = 0, 0, 0
    for j in range(10):
        arr_ms = [k for k in range(i, 0, -1)]
        arr_hs = [k for k in range(i, 0, -1)]
        arr_ss = [k for k in range(i, 0, -1)]
        t1_start = time.perf_counter()
        arr_ms = merge_sort.mergesort(arr_ms)
        t1 = time.perf_counter() - t1_start
        s1 += t1
        t2_start = time.perf_counter()
        heap_sort.heap_sort(arr_hs)
        t2 = time.perf_counter() - t2_start
        s2 += t2
        t3_start = time.perf_counter()
        smooth_sort.smoothSort(smooth_sort.doListHeaps(arr_ss))
        t3 = time.perf_counter() - t3_start
        s3 += t3
    T7.write(str(s1/10))
    T7.write("\n")
    T8.write(str(s2/10))
    T8.write("\n")
    T9.write(str(s3/10))
    T9.write("\n")
T7.close()
T8.close()
T9.close()
