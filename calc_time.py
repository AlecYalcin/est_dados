import random as rm
import time

from distribution_sort  import distribution_sort
from insertion_sort     import insertion_sort
from merge_sort         import merge_sort
from quick_sort         import quick_sort
from selection_sort     import selection_sort

def write_file(file_names):
    for file_name in file_names:
        file = open(file_name, "w")
        file.close()

file_names = [
    "time_distribution.txt",
    "time_insertion.txt",
    "time_merge.txt",
    "time_quick.txt",
    "time_selection.txt"
]

write_file(file_names)
for n in range(2, 1001, 1):
    array = [rm.randint(0, 100) for x in range(n)]

    # Distribution Sort
    start_t = time.time_ns()
    z = distribution_sort(array, len(array)-1)
    end_t = time.time_ns()
    
    exec_t = end_t - start_t

    with open(file_names[0], "a") as f:
        f.write(str(n) + ", " + str(exec_t) + "\n")

    # Insertion Sort
    start_t = time.time_ns()
    z = insertion_sort(array, len(array)-1)
    end_t = time.time_ns()
    
    exec_t = end_t - start_t

    with open(file_names[1],  "a") as f:
        f.write(str(n) + ", " + str(exec_t) + "\n")

    # Merge Sort
    start_t = time.time_ns()
    z = merge_sort(array, 0, len(array)-1)
    end_t = time.time_ns()
    
    exec_t = end_t - start_t

    with open(file_names[2],  "a") as f:
        f.write(str(n) + ", " + str(exec_t) + "\n")

    # Quick Sort
    start_t = time.time_ns()
    z = quick_sort(array, 0, len(array)-1)
    end_t = time.time_ns()
    
    exec_t = end_t - start_t

    with open(file_names[3], "a") as f:
        f.write(str(n) + ", " + str(exec_t) + "\n")

    # Selection Sort
    start_t = time.time_ns()
    z = selection_sort(array, len(array)-1)
    end_t = time.time_ns()
    
    exec_t = end_t - start_t

    with open(file_names[4], "a") as f:
        f.write(str(n) + ", " + str(exec_t) + "\n")

