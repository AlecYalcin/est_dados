import sys
import time
import random as rm

def merge_sort(A, start, end):
    if start < end:
        middle = (start + end)//2

        merge_sort(A, start, middle)
        merge_sort(A, middle+1, end)
        merge(A, start, middle, end)
    return A

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

# médio caso: vetor aleatório
if __name__ == "__main__":
    n = int(sys.argv[1])
    v = [rm.randint(0, 1000) for x in range(n)]
    first_time = time.time_ns()
    v = merge_sort(v, 0, n-1)
    final_time = time.time_ns()
    total_time = final_time - first_time
    print(total_time)