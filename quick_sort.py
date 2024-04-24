import random as rm

def partition(A, start, end):
    pivot = A[end]
    i = start - 1
    for j in range(start, end):
        if A[j] <= pivot:
            i += 1
            A[i], A[j] = A[j], A[i]
    A[i + 1], A[end] = A[end], A[i + 1]
    return i + 1

def quick_sort(A, start, end):
    if start < end:
        pivot = partition(A, start, end)
        quick_sort(A, start, pivot - 1)
        quick_sort(A, pivot + 1, end)
    return A