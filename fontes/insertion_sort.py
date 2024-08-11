import sys
import time
import random as rm

def insertion_sort(v, n):
    for i in range(1, n):
        k = v[i]
        j = i-1
        while(j>=0 and v[j] > k):
            v[j+1] = v[j]
            j = j-1
        v[j+1] = k
    return v

# médio caso: vetor aleatório
if __name__ == "__main__":
    n = int(sys.argv[1])
    v = [rm.randint(0, n) for x in range(n)]
    first_time = time.time_ns()
    v = insertion_sort(v, n)
    final_time = time.time_ns()
    total_time = final_time - first_time
    print(total_time)