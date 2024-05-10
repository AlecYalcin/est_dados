import sys
import time
import random as rm

def distribution_sort(v, n):
    s = min(v)
    e = max(v)
    k = e-s

    c, z = [],[]
    for i in range(k+1):
        c.append(0)
    for i in range(n):
        c[v[i]-s] = c[v[i]-s]+1
        z.append(0)
    for i in range(1,k+1):
        c[i] = c[i]+c[i-1]
    for i in range(n):
        d = v[i]-s
        z[c[d]-1] = v[i]
        c[d] = c[d]-1

    return z

if __name__ == "__main__":
    n = int(sys.argv[1])
    v = [rm.randint(0, 1000) for x in range(n)]
    first_time = time.time_ns()
    v = distribution_sort(v, n)
    final_time = time.time_ns()
    total_time = final_time - first_time
    print(total_time)