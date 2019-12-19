def merge(left, right):
    result = []
    i ,j = 0, 0
    while i < len(left) and j < len(right):
        if left[i] <= right[j]:
            result.append(left[i])
            i += 1
        else:
            result.append(right[j])
            j += 1
    result += left[i:]
    result += right[j:]
    return result

# сортировка слиянием
# l - массив
def mergesort(l):
    if len(l) < 2:
        return l
    middle = len(l) // 2
    left = mergesort(l[:middle])
    right = mergesort(l[middle:])
    return merge(left, right)

#print(mergesort([9, 3, 1, 0, 2]))
