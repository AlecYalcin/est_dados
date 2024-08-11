import sys
import time
from quick_sort import quick_sort

def quick_best(A, start, end):
    if start < end:
        middle = (start+end)//2
        quick_best(A, start, middle-1)
        quick_best(A, middle+1, end)
        A[middle], A[end] = A[end], A[middle]
    return A

# melhor caso: o vetor inicia no meio
if __name__ == "__main__":
    n = int(sys.argv[1])
    A = list(range(n))

    A = quick_best(A, 0, n-1)

    first_time = time.time_ns()
    A = quick_sort(A, 0, n-1)
    final_time = time.time_ns()
    total_time = final_time - first_time
    print(total_time)