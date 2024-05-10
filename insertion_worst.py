import sys
import time
from insertion_sort import insertion_sort

# Pior caso: vetor ordenado inversamente
if __name__ == "__main__":
    n = int(sys.argv[1])
    v = list(range(n))
    v.reverse()
    first_time = time.time_ns()
    v = insertion_sort(v, n)
    final_time = time.time_ns()
    total_time = final_time - first_time
    print(total_time)