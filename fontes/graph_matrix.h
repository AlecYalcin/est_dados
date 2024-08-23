#include <stdio.h>

void print_matrix(int** matrix, int size);
int isEmpty(int* array, int size);
int* create_array(int size);
void print_memory(int* memory, int size);
void print_from(int* from, int size);
void show_from(int* from, int size, int destiny);
int** create_graph(int size);
void insert_g(int** graph, int key, int neighbor, int value);
void remove_g(int** graph, int key, int neighbor);