#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../graph_matrix.h"

int memory_remove(int** array, int size) {
    int x = (*array)[0];
    for(int i = 1; i < size; i++) {
        (*array)[i-1] = (*array)[i];
    }
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

void gsearch(int** graph, int size, int origin, int destiny) {
    // Array de Caminhos
    int* from = create_array(size);
    from[origin] = size;
    // Array de Memória
    int* memory = create_array(size);
    memory[0] = origin;
    // Fazer todos os caminhos até não ter mais memoria ou vizinhos
    while (isEmpty(memory, size) == 0)  {
        int x = memory_remove(&memory, size);
        for(int i=0; i < size; i++) {
            // Verificando todos os vizinhos de X
            if(graph[x][i] == 1) {
                // Se o vizinho já foi vizitado
                if(from[i] == -1) {
                    from[i] = x;
                    memory = memory_add(memory, size, i);

                    if(graph[x][i] == 1 && i == destiny) {
                        show_from(from, size, destiny);
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
    unsigned int n = atoi(argv[1]);
    unsigned int o = atoi(argv[2]);
    unsigned int d = atoi(argv[3]);

    // Inicializador de randomização
    srand(time(NULL));

    // Criação da Matriz
    int** g = create_graph(n);

    // Inserindo elementos
    for(int i = 0; i < n; i++) {
        insert_g(g, i, rand() % n, 1);
        insert_g(g, i, rand() % n, 1);
        insert_g(g, i, rand() % n, 1);
    }

    // Procurando na Matriz
    gsearch(g, n, o, d);

    // Mostrando Matriz
    print_matrix(g, n);

    return 0;
}