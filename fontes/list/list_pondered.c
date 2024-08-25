#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../graph_list.h"

int has_memory(int* memory, int* distance, int destiny, int n) {
    for(int i = 0; i < n; i++) {
        if(memory[i] != -1 && (distance[memory[i]] < distance[destiny])) {
            return 1;
        }
    }
    return 0;
};

int memory_remove(int* memory, int n) {
    // Pegando o índice para tirar o elemento no final
    int index = 0;
    // Pegando o primeiro elemento
    int x = memory[index];
    for(int i = 1; i < n; i++) {
        if((memory[i] < x && memory[i] != -1) || x == -1) {
            x = memory[i];
            index = i;
        }
    }
    // Alterando a memória do índice
    memory[index] = -1;

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
    // Array de Pesos
    int distance[n];
    // Memória do Programa
    int memory[n];
    // Preenchendo com valores negativos
    for(int i = 0; i < n; i++) {
        from[i] = -1;
        memory[i] = -1;
        distance[i] = -1;
    }
    // Adicionando origem, origem é sempre 0 e qualquer outro nó é Nó+1
    from[origin] = 0;
    distance[origin] = 0;
    // Adicionando a memória
    memory[0] = origin;

    while(!(isEmpty(memory, n))) {
        // Memória Atual
        int x = memory_remove(memory, n);

        // Vizinhos
        Node* y = table->nodes[x];
        while(y != NULL) {
            if(from[y->v] == -1 || distance[y->v] > (distance[x] + y->w)) {
                from[y->v] = x+1;
                distance[y->v] = distance[x] + y->w;
                memory_add(memory, y->v, n);
                // Verificar se é o destino
                if(y->v == destiny && !(has_memory(memory, distance, destiny, n))) {
                    break;
                }
            }
            // Próximo vizinho do nó
            y = y->next;
        }
    }

    for(int i = 0; i < n; i++) {
        printf("From[%d]: %d, Distance: %d\n", i+1, from[i], distance[i]);
    }
}

int main(int argc, char** argv) {
    // Quantidades de Nós
    unsigned int n = atoi(argv[1]);
    // Criando a Tabela
    Table* table = create_table(n);

    // Criando Vizinhos
    insert_weight(table, 0, 1, 2);
    insert_weight(table, 0, 3, 5);
    insert_weight(table, 1, 2, 4);
    insert_weight(table, 3, 2, 2);
    insert_weight(table, 3, 4, 3);
    insert_weight(table, 2, 4, 1);

    // Mostrando Vizinhos
    print_table(table);

    // Procurando...
    gsearch(table, 0, 4);

    return 0;
}