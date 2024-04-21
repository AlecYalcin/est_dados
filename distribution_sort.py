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

n = rm.randint(1, 10)
v = [rm.randint(1, 100) for i in range(n)]

print(f"Vetor Original: {v}")
print(f"Vetor Transformado: {distribution_sort(v,n)}")