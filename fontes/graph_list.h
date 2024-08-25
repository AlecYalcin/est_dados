#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int v;
    int w;
    struct node* next;
} Node;

typedef struct table {
    unsigned int n;
    Node** nodes;
} Table;

Node* create_node(int);
Table* create_table(unsigned int n);
void insert_node(Table*, int, int);
void insert_weight(Table*, int, int, int);
void print_table(Table*);
int isEmpty(int*, int);