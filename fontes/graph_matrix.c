#include <stdio.h>
#include <stdlib.h>
#include "graph_matrix.h"

void print_matrix(int** matrix, int size) {
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int isEmpty(int *array, int size)
{
    for(int i = 0; i < size; i++) {
        if(array[i] > -1) {
            return 0;
        }
    }
    return 1;
}

int* create_array(int size) {
    int* array;
    array = (int*)malloc(size * sizeof(int*));

    for(int i = 0; i < size; i++) {
        array[i] = -1;
    }

    return array;
}


void print_memory(int* memory, int size) {
    for(int i = 0; i < size; i++) {
        printf("m[%d] = %d \n", i, memory[i]);
    }
}

void print_from(int* from, int size) {
    printf("\n------------------------------------------\n");
    for(int i = 0; i < size; i++) {
        printf(">> from[%d] = %d \n", i, from[i]);
    }
}

void show_from(int* from, int size, int destiny) {
    printf("%d -> ", destiny);
    if(from[destiny] != size) {
        show_from(from, size, from[destiny]);
    } else {
        printf("\n");
    }
}

int** create_graph(int size) {
    int** matrix;
    matrix = (int**)malloc(size * sizeof(int*));
    
    for(int i = 0; i < size; i++) {
        matrix[i] = (int*)malloc(size * sizeof(int));
        for(int j = 0; j < size; j++) {
            matrix[i][j] = 0;
        }
    }

    return matrix;
}

void insert_g(int** graph, int key, int neighbor, int value) {
    if(key != neighbor && graph[key][neighbor] != 1) {
        graph[key][neighbor] = value;
        graph[neighbor][key] = value;
    }
}

void remove_g(int** graph, int key, int neighbor) {
    if(key != neighbor && graph[key][neighbor] != 0) {
        graph[key][neighbor] = 0;
        graph[neighbor][key] = 0;
    }
}
