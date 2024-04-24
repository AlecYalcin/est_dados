def insertion_sort(v, n):
    for i in range(1, n):
        k = v[i]
        j = i-1
        while(j>=0 and v[j] > k):
            v[j+1] = v[j]
            j = j-1
        v[j+1] = k
    return v