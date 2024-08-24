#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int v;
    struct node* next;
} Node;

typedef struct table {
    unsigned int n;
    Node** nodes;
} Table;

Node* create_node(int v) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->v = v;
    node->next = NULL;
    return node;
}

Table* create_table(unsigned int n) {
    Table* table = (Table*)malloc(sizeof(Table));

    table->n = n;
    table->nodes = (Node**)malloc(n * sizeof(Node*));

    for(int i = 0; i < n; i++) {
        table->nodes[i] = NULL;
    }

    return table;
}

void insert_node(Table* table, int key, int value) {
    Node* new_node = create_node(value);
    if(table->nodes[key] == NULL) {
        table->nodes[key] = new_node;
        insert_node(table, value, key);
    } else {
        Node* current = table->nodes[key];
        while(current->next != NULL || current->v == value) {
            if(current->v == value) {
                return;
            }
            current = current->next;
        }
        current->next = new_node;
        insert_node(table, value, key);
    }
}

void print_table(Table* table) {
    for(int i = 0; i < table->n; i++) {
        Node* current = table->nodes[i];
        printf("[%d] -> ", i);
        while(current != NULL) {
            printf("(%d) -> ", current->v);
            current = current->next;
        }
        printf("NULL\n");
    }
}

// Utils
int isEmpty(int* array, int n) {
    for(int i = 0; i < n; i++) {
        if(array[i] != -1) {
            return 0;
        }
    }
    return 1;
}