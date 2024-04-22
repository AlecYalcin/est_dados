import random as rm

def partition(arr, start, end):
    pivot = arr[end]
    i = start - 1
    for j in range(start, end):
        if arr[j] <= pivot:
            i += 1
            arr[i], arr[j] = arr[j], arr[i]
    arr[i + 1], arr[end] = arr[end], arr[i + 1]
    return i + 1

def quick_sort_recursive(arr, start, end):
    if start < end:
        pivot_index = partition(arr, start, end)
        quick_sort_recursive(arr, start, pivot_index - 1)
        quick_sort_recursive(arr, pivot_index + 1, end)

# Exemplo de uso:
arr = [rm.randint(1, 100) for i in range(rm.randint(10,15))]
quick_sort_recursive(arr, 0, len(arr) - 1)
print("Sorted array (recursive):", arr)