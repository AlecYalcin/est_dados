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

Node* create_node(int v) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->v = v;
    node->w = 1;
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
    } else {
        Node* current = table->nodes[key];
        while(current->next != NULL || current->v == value) {
            if(current->v == value) {
                return;
            }
            current = current->next;
        }
        current->next = new_node;
    }
}

int graphDegree(Table* table, int key) {
    // Verificar Grau de Saída (Null)
    if(table->nodes[key] != NULL) {
        return 0;
    }
    // Verificar Grau de Entrada (Max)
    int n = table->n;
    for(int i = 0; i < n; i++) {
        // Verificar se for a chave, para ignorar
        if(i == key) {
            if(i+1 == n) {
                break;
            }
            i++;
        }

        // Se algum dos Nós tiver Grau de Saída NULO
        if(table->nodes[i] == NULL) {
            return 0;
        }

        // Verificar se o Nó tem a chave correspondente
        int has_nodes[n];
        Node* current = table->nodes[i];
        while(current != NULL) {
            has_nodes[current->v] = 1;
            current = current->next;
        }

        if(has_nodes[key] == 0) {
            return 0;
        }
    }
    
    return 1;
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

int main(int argc, char** argv) {
    // Quantidades de Nós
    unsigned int n = atoi(argv[1]);
    // Criando a Tabela
    Table* table = create_table(n);

    // Criando Vizinhos
    for(int i = 0; i < table->n; i++) {
        if(i != 4) insert_node(table, i, 4);
    }

    // Mostrando Vizinhos
    print_table(table);

    // Verificando se algum nó possui grau de entrada máximo e grau de saída mínimo
    for(int i = 0; i < table->n; i++) {
        printf("O nó %d possui? %d\n", i+1, graphDegree(table, i));
    }


    return 0;
}