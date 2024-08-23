#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../graph_matrix.h"

int memory_remove(int* distance, int** memory, int size) {
    // Pegando o primeiro índice para comparativo
    int lowest;
    int index;

    if((*memory)[0] != -1) {
        lowest = distance[(*memory)[0]];
        index = 0;
    } else {
        lowest = -1;
        index = -1; 
    }

    for(int i = 1; i < size; i++) {
        if((*memory)[i] != -1 && distance[(*memory)[i]] < lowest) {
            lowest = distance[(*memory)[i]];
            index = i;
        }

        if (lowest == -1 && (*memory)[i] != -1) {
            lowest = distance[(*memory)[i]];
            index = i;
        }
    }

    int x = (*memory)[index];
    (*memory)[index] = -1;
    return x;
}

int* memory_add(int* array, int size, int key) {
    for(int i = 0; i < size; i++) {
        if(array[i] == -1) {
            array[i] = key;
            return array;
        }
    }
    return array;
}

int has_memory(int size, int destiny, int* memory, int* distance) {
    for(int i = 0; i < size; i++) {
        if(memory[i] != -1 && distance[memory[i]] < distance[destiny]) {
            return 0;
        }
    }
    return 1;
}

void show_distance(int* distance, int* from, int size, int destiny) {
    printf("%d -> ", distance[destiny]);
    if(from[destiny] != size) {
        show_distance(distance, from, size, from[destiny]);
    } else {
        printf("\n");
    }
}

void gsearch(int** graph, int size, int origin, int destiny) {
    // Array de Caminhos
    int* from = create_array(size);
    from[origin] = size;
    // Array de Distâncias
    int* distance = create_array(size);
    distance[origin] = 0;
    // Array de Memória
    int* memory = create_array(size);
    memory[0] = origin;


    // Fazer todos os caminhos até não ter mais memoria ou vizinhos
    while (isEmpty(memory, size) == 0)  {
        int x = memory_remove(distance, &memory, size);
        for(int i=0; i < size; i++) {
            if(graph[x][i] > 0) {
                // Verificando se o lugar já foi preenchido
                if(from[i] == -1 || distance[i] > (distance[x] + graph[x][i])) {
                    from[i] = x;
                    distance[i] = distance[x] + graph[x][i];
                    memory = memory_add(memory, size, i);
                    if(i == destiny && has_memory(size, destiny, memory, distance)) {
                        show_from(from, size, destiny);
                        show_distance(distance, from, size, destiny);
                        return;
                    }
                } 
            }
        }
    }
    printf("Não existe caminho possível.\n");
}

int main(int argc, char** argv) {
    // Tamanho da Matriz
    unsigned int n = 5;
    //unsigned int n = atoi(argv[1]);
    //unsigned int o = atoi(argv[2]);
    //unsigned int d = atoi(argv[3]);

    // Inicializador de randomização
    srand(time(NULL));

    // Criação da Matriz
    int** g = create_graph(n);

    // Inserindo elementos
    insert_g(g, 0, 1, 2);
    insert_g(g, 0, 3, 5);
    insert_g(g, 1, 2, 4);
    insert_g(g, 2, 3, 2);
    insert_g(g, 2, 4, 1);
    insert_g(g, 3, 4, 3);

    // Mostrando Matriz
    print_matrix(g, n);

    // Procurando na Matriz
    gsearch(g, n, 0, 4);

    return 0;
}