def selection_sort(A, n):
    for i in range(n):
        min_index = i
        for j in range(i+1, n):
            if (A[j] < A[min_index]):
                min_index = j
        A[i], A[min_index] = A[min_index], A[i]
    return A