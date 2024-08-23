#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "graph_matrix.h"

typedef struct edge {
    int a;
    int b;
    int w;
} Edge;

Edge* create_edge() {
    Edge* new_edge = (Edge*)malloc(sizeof(Edge));
    new_edge->a = -1;
    new_edge->b = -1;
    new_edge->w = -1;
    return new_edge;
}

int inEdgeList(Edge** edges, int max_edges, int a, int b) {
    for(int i = 0; i < max_edges; i++) {
        if(edges[i]->a == a && edges[i]->b == b) {
            if(edges[i]->w > 0) {
                return 0;
            }
        } else if (edges[i]->a == b && edges[i]->b == a) {
            if(edges[i]->w > 0) {
                return 0;
            }
        }
    }

    return 1;
}

int partition(Edge** edges, int start, int end) {
    Edge* pivot = edges[end];
    int i = start - 1;
    for(int j = start; j < end; j++) {
        if(edges[j]->w > 0 && edges[j]->w <= pivot->w) {
            i++;

            Edge* aux = edges[j];
            edges[j] = edges[i];
            edges[i] = aux;

        }
    }
    Edge* aux = edges[i+1];
    edges[i+1] = edges[end];
    edges[end] = aux;
    return i + 1;
}

Edge** quick_sort(Edge** edges, int start, int end) {
    if (start < end) {
        int pivot = partition(edges, start, end);
        quick_sort(edges, start, pivot - 1);
        quick_sort(edges, pivot + 1, end);
    }
    return edges;
}   

Edge** get_edges(int** graph, int size) {
    // Criação do Máximo de Arestas
    int max_edges = ((size-1)*size)/2;
    Edge** edges = (Edge**)malloc(max_edges*(sizeof(Edge*)));
    for(int i = 0; i < max_edges; i++) {
        edges[i] = create_edge();
    }
    int edge_index = 0;

    // Coletando todas as arestas
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            if(graph[i][j] > 0 && inEdgeList(edges, max_edges, i, j)) {
                edges[edge_index]->a = i;
                edges[edge_index]->b = j;
                edges[edge_index]->w = graph[i][j];

                edge_index++;
            }
        }
    }

    return edges;
}

int memory_size(Edge** array, int size) {
    int array_size = 0;
    for(int i = 0; i < size; i++) {
        if(array[i]->w > 0) {
            array_size++;
        }
    }

    return array_size;
}

Edge* memory_remove(Edge*** memory, int size) {
    Edge* e = (*memory)[0];
    for(int i = 1; i < size; i++) {
        (*memory)[i-1] = (*memory)[i];
    }
    return e;
}

Edge** memory_add(Edge** memory, Edge* e, int size) {
    for(int i = 0; i < size; i++) {
        if(memory[i]->w == -1) {
            memory[i] = e;
            return memory;
        }
    }
    return memory;
}

int same_group(Edge* e, int* group) {

    if(group[e->a] == group[e->b]) {
        return 1;
    }
    return 0;
}

void update_group(Edge* e, int* group, int size) {
    int a = group[e->a];
    int b = group[e->b];

    for(int i = 0; i < size; i++) {
        if(group[i] == group[a]) {
            group[i] = group[b];
        }
    }
}

int** kruskal_m(int** g, int size) {
    // Criando os grupos
    int group[size];
    for(int i = 0; i < size; i++) {
        group[i] = i;
    }

    // Pegando e Organizando lista de arestas
    int max_edges = ((size-1)*size)/2;
    Edge** edges = get_edges(g, size);

    int end = max_edges - 1;
    while(edges[end]->w == -1) {
        end--;
    }

    edges = quick_sort(edges, 0, end);

    // Criando a memória
    Edge** memory = (Edge**)malloc(size * sizeof(Edge*));
    for(int i = 0; i < size; i++) {
        memory[i] = create_edge();
    }

    // Realizando Comparações
    while(memory_size(memory, size) < size-1) {
        //printf("Tamanho: %d\n", memory_size(memory, size));
        Edge* e = memory_remove(&edges, size);
        if (!(same_group(e, group))) {
            memory = memory_add(memory, e, size);
            update_group(e, group, size);
        }
    }

    for(int i = 0; i < size; i++) {
        printf("Group[%d]: %d\n", i, group[i]);
        printf("Memory[%d]:\n a->%d\n b->%d\n w->%d\n", i, memory[i]->a, memory[i]->b, memory[i]->w);
    }
}

int main(int argc, char** argv) {
    // Tamanho da Matriz
    unsigned int n = atoi(argv[1]);

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
    
    // Testes
    kruskal_m(g, n);

    return 0;
}