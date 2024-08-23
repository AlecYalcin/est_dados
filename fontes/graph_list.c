#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct node {
    char* key;
    struct node* next;
} Node;

Node* create_node(char* key) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key  = key;
    node->next = NULL;
    return node;
}

typedef struct hashTable {
    unsigned int size;
    Node** list;
} HashTable;

unsigned int hash(char* key, unsigned int size) {
    unsigned long int value = 0;
    for(int i = 0; i < strlen(key); i++) {
        value = value * 37 + key[i];
    }
    return value % size;
}

HashTable* create_table(int size) {
    HashTable* table = (HashTable*)malloc(sizeof(HashTable));
    table->size = size;
    table->list = (Node**)malloc(size * sizeof(Node*));

    for(int i = 0; i < size; i++) {
        table->list[i] = NULL;
    }

    return table;
}


void insert(HashTable* table, Node* node, Node* neighbor) {
    unsigned int index = hash(node->key, table->size);
    
    if(table->list[index] == NULL) {
        table->list[index] = neighbor;
    } else {
        Node* current = table->list[index];
        while(current->next != NULL) {
            current = current->next;
        }
        current->next = neighbor;
    }
}

void print_table(HashTable* table) {
    for(int i = 0; i < table->size; i++) {
        printf("[%d] -> ", i);

        Node* current = table->list[i];
        while(current != NULL) {
            printf("(%s) -> ", current->key);
            current = current->next;
        }
        printf("NULL\n");
    }
}


int main(int argc, char** argv) {
    // Quantidade de elementos na tabela
    unsigned int n = atoi(argv[1]);

    // Tabela de Dispersão
    HashTable* table = create_table(n);    

    Node* caico = create_node("caico");
    Node* jucurutu = create_node("jucurutu");
    Node* jardim = create_node("jardim");

    // Teste
    insert(table, caico, jucurutu);
    insert(table, jucurutu, caico);
    insert(table, caico, jardim);
    insert(table, jardim, jucurutu);

    // Mostrando o Grafo
    print_table(table);

    return 0;
}