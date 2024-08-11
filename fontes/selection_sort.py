import sys
import time
import random as rm

def selection_sort(A, n):
    for i in range(n):
        min_index = i
        for j in range(i+1, n):
            if (A[j] < A[min_index]):
                min_index = j
        A[i], A[min_index] = A[min_index], A[i]
    return A

# médio caso: vetor aleatório
if __name__ == "__main__":
    n = int(sys.argv[1])
    v = [rm.randint(0, n) for x in range(n)]
    first_time = time.time_ns()
    v = selection_sort(v, n)
    final_time = time.time_ns()
    total_time = final_time - first_time
    print(total_time)