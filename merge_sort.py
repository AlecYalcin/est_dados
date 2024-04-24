def merge_sort(A, start, end):
    if start < end:
        middle = (start + end)//2

        merge_sort(A, start, middle)
        merge_sort(A, middle+1, end)
        merge(A, start, middle, end)

def merge(A, start, middle, end):
    i = start
    j = middle + 1

    v = [0]*len(A)
    for k in range(0, end-start):
        if (i <= middle) and ((j>end) or (A[i] < A[j])):
            v[k] = A[i]
            i += 1
        else:
            v[k] = A[j]
            j += 1
    for k in range(0, end-start):
        A[start+k] = v[k]


