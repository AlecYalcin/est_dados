#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node {
    int value;
    struct node* left;
    struct node* right;
} Node;

Node* create_node(int value) {
    // Inicializando novo nó
    Node* new_node = (Node*)malloc(sizeof(Node));
    // Adicionando valores
    new_node->value = value;
    new_node->left = NULL;
    new_node->right = NULL;
    // Retornando o nó
    return new_node;
}

void insert_node(Node** root, int value) {
    // Se o nó é válido
    if((*root) != NULL) {
        // Se o valor adicionado é menor que o valor do nó
        if ((*root)->value > value) {
            insert_node(&(*root)->left, value);
        } else {
            insert_node(&(*root)->right, value);
        }
    } else {
        (*root) = create_node(value);
    }
}

Node* binary_search(Node* root, int number) {
    if (root != NULL) {
        // Se o valor é igual ao número
        if(root->value == number) {
            return root;
        }
        // Se o valor é maior que o número  
        if(root->value > number) {
            return binary_search(root->left, number);
        }
        // Se o valor é menor que o número
        return binary_search(root->right, number);
    }
    // Se não existe o valor procurado
    return NULL;
}

void free_tree(Node** root) {
    if ((*root) != NULL) {
        free_tree(&(*root)->left);
        free_tree(&(*root)->right);
        free((*root));
    }
}

void print_tree(Node* root) {
    if (root != NULL) {
        print_tree(root->left);
        printf("%d\n", root->value);
        print_tree(root->right);
    }
}

int main(int argc, char **argv) {
    // Criando a raiz da árvore binária
    Node* root = NULL;

    // Tamanho do vetor/árvore binária
    unsigned int n = atoi(argv[1]);

    // Inicializador de randomização
    srand(time(NULL));
    
    // inteiro auxiliar para pegar último valor gerado na lista
    int last;     
    // Inserindo elemento aleatórios na árvore binária
    for(int i = 0; i < n; i++) {
        last = (rand() % n) + 1;
        insert_node(&root, last);
    }

    // Inicializando variáveis de tempo
    struct timespec start, end;

    // Guardando valores de tempo
    clock_gettime(CLOCK_MONOTONIC, &start);
    Node* aux = binary_search(root, last);
    clock_gettime(CLOCK_MONOTONIC, &end);

    // Calculando o tempo
    unsigned  time = (end.tv_sec * 1e9 + end.tv_nsec) - (start.tv_sec * 1e9 + start.tv_nsec);

    // Mostrando o tempo para iterate
    printf("%u\n", time);

    // Liberando memória
    free_tree(&root);
    aux = NULL;

    return 0;
}