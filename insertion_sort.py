import random as rm

def insertion_sort(v, n):
    for i in range(1, n):
        k = v[i]
        j = i-1
        while(j>=0 and v[j] > k):
            v[j+1] = v[j]
            j = j-1
        v[j+1] = k
        print(v)
    return v

n = rm.randint(1, 10)
v = [rm.randint(1, 100) for i in range(n)]

print(f"Vetor Original: {v}")
print(f"Vetor Transformado: {insertion_sort(v,n)}")