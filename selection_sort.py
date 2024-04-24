import random as rm

def selection_sort(A, n):
    for i in range(n):
        min_index = i
        for j in range(i+1, n):
            if (A[j] < A[min_index]):
                min_index = j
        A[i], A[min_index] = A[min_index], A[i]

A = [rm.randint(0, 10) for x in range(0, 10)]
selection_sort(A, len(A))
print(A)