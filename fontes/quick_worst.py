import sys
import time
from quick_sort import quick_sort

# pior caso: o vetor já está ordenado
if __name__ == "__main__":
    n = int(sys.argv[1])
    v = list(range(n))
    v.reverse()
    first_time = time.time_ns()
    v = quick_sort(v, 0, n-1)
    final_time = time.time_ns()
    total_time = final_time - first_time
    print(total_time)