#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../graph_list.h"

int memory_remove(int* memory, int n) {
    int x = memory[0];
    for(int i = 1; i < n; i++) {
        memory[i-1] = memory[i];
    }
    return x;
}

void memory_add(int* memory, int value, int n) {
    for(int i = 0; i < n; i++) {
        if(memory[i] == -1) {
            memory[i] = value;
            return;
        }
    }
}

void gsearch(Table* table, int origin, int destiny) {
    // Quantidade de nós
    int n = table->n;
    // Array de Caminhos
    int from[n];
    // Memória do Programa
    int memory[n];
    // Preenchendo com valores negativos
    for(int i = 0; i < n; i++) {
        from[i] = -1;
        memory[i] = -1;
    }
    // Adicionando origem, origem é sempre 0 e qualquer outro nó é Nó+1
    from[origin] = 0;
    // Adicionando a memória
    memory[0] = origin;

    while(!(isEmpty(memory, n))) {
        // Memória Atual
        int x = memory_remove(memory, n);
        
        // Vizinhos
        Node* y = table->nodes[x];
        while(y != NULL) {
            if(from[y->v] == -1) {
                from[y->v] = x+1;
                memory_add(memory, y->v, n);

                // Verificar se é o destino
                if(y->v == destiny) {
                    break;
                }
            }
            // Próximo vizinho do nó
            y = y->next;
        }
    }

    for(int i = 0; i < n; i++) {
        printf("From[%d]: %d\n", i+1, from[i]);
    }
}

int main(int argc, char** argv) {
    // Quantidades de Nós
    unsigned int n = atoi(argv[1]);
    // Criando a Tabela
    Table* table = create_table(n);

    // Criando Vizinhos
    insert_node(table, 0, 1);
    insert_node(table, 0, 3);
    insert_node(table, 1, 2);
    insert_node(table, 3, 2);
    insert_node(table, 3, 4);
    insert_node(table, 2, 4);

    // Mostrando Vizinhos
    print_table(table);

    // Procurando...
    gsearch(table, 1, 4);

    return 0;
}