#include "graph_matrix.h"

int main(int argc, char** argv) {
    // Tamanho da Matriz
    unsigned int n = atoi(argv[1]);

    // Criação da Matriz
    int** g = create_graph(n);

    printf("%d\n", len(g));

    return 0;
}