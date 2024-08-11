#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Estrutura base
typedef struct node {
    int value;
    unsigned int height;
    
    struct node* left;
    struct node* right;
    struct node* parent;
} Node;

// Coletar altura de qualquer nó
int height(Node* node) {
    return (node == NULL) ? 0 : node->height;
}

// Descobrir o maior termo entre duas variáveis
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Criar um novo nó
Node* create_node(int value) {
    // Criação de um novo nó
    Node* new_node = (Node*)malloc(sizeof(Node));
    // Atribuição de valores
    new_node->value = value;
    new_node->height = 1;
    // Definição de 'rotas'
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->parent = NULL;
    // Retornando o novo nó
    return new_node;
}

// Fator de balanceamento
int getBalance(Node* node) {
    return (node == NULL) ? 0 : height(node->left) - height(node->right); 
}

// Encontrar o real "root" da arvore
Node* find_root(Node* root) {
    if (root->parent != NULL) {
        return find_root(root->parent);
    } else {
        return root;
    }
}

// Calcula a altura do nó atual
void calculate_height(Node* root) {
    if (root != NULL) {
        root->height = 1 + max(height(root->left), height(root->right));
        calculate_height(root->parent);
    }
}

// Rotação a Esquerda
Node* rotate_left(Node* x) {
    Node* y = x->right;
    Node* C_TREE = y->left;

    // Rotação
    y->left = x;
    x->right = C_TREE;

    // Redefinindo parentes de x e y
    y->parent = x->parent;
    x->parent = y;

    // Redefinindo o pai
    Node* parent = y->parent;
    if (parent != NULL) {
        if(parent->left == x) {
            parent->left = y;
        } else {
            parent->right = y;
        }   
    }

    // Redefinindo parente de C_TREE
    if(C_TREE != NULL) {
        C_TREE->parent = x;
    }

    // Redefinindo alturas
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

// Rotação a Direita
Node* rotate_right(Node* x) {
    Node* y = x->left;
    Node* C_TREE = y->right;

    // Rotação
    y->right = x;
    x->left = C_TREE;

    // Redefinindo parentes de x e y
    y->parent = x->parent;
    x->parent = y;

    // Redefinindo o pai
    Node* parent = y->parent;
    if (parent != NULL) {
        if(parent->left == x) {
            parent->left = y;
        } else {
            parent->right = y;
        }   
    }

    // Redefinindo parente de C_TREE
    if(C_TREE != NULL) {
        C_TREE->parent = x;
    }

    // Redefinindo alturas
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

// Printar em ordem
void print_tree(Node* root) {
    if (root != NULL) {
        print_tree(root->left);
        printf("Height: %u, Node: %p, Value: %d, Parent: %p\n", root->height, root, root->value, root->parent);
        print_tree(root->right);
    }
}

// Verifica o fator de balanceamento e balanceia a árvore
void balance_tree(Node* root) {
    int balance = getBalance(root);

    // Caso Esquerda-Esquerda (LL) ou Caso 01
    if(balance > 1 && getBalance(root->left) >= 0) {
        // Rotação a Direita (X)
        root = rotate_right(root);
    }

    // Caso Direita-Direita (RR) ou Caso 02
    if(balance < -1 && getBalance(root->right) <= 0) {
        // Rotação a Esquerda (X)
        root = rotate_left(root);
    }

    // Caso Esquerda-Direita (LR) ou Caso 03
    if(balance > 1 && getBalance(root->left) < 0) {      
        // Rotação a Esquerda em (Y)
        root->left = rotate_left(root->left);
        // Rotação a Direita em (X)
        root = rotate_right(root);
    }

    // Caso Direita-Esquerda (RL) ou Caso 04
    if(balance < -1 && getBalance(root->right) > 0) {    
        // Rotação a Direita em (Y)
        root->right = rotate_right(root->right);
        // Rotação a Esquerda em (X)
        root = rotate_left(root);
    }
}

// Adicionar novo elemento na árvore
void insert_node(Node** root, int value) {
    // Verificando se o root atual é nulo
    if ((*root) != NULL) {
        if((*root)->value > value) {
            insert_node(&(*root)->left, value);
            (*root)->left->parent = (*root);
        } else {
            insert_node(&(*root)->right, value);
            (*root)->right->parent = (*root);
        }
        
        // Calcula a altura do nó atual
        calculate_height((*root));

        // Balanceia a árvore AVL
        balance_tree((*root));
    } else {
        // Criando o novo nó
        (*root) = create_node(value);
    }
}

// Binary Search
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

int main(int argc, char **argv) {
    // Raiz inicial da árvore
    Node* root = NULL;

    // Quantidade de elementos da árvore
    unsigned int n = atoi(argv[1]);

    // Inicializador de randomização
    srand(time(NULL));

    // inteiro auxiliar para ter acesso ao último elemento da lista
    int last;
    // Inserindo elemento aleatório na árvore binária
    for(int i = 0; i < n; i++) {
        last = (rand() % (n*10)) + 1;
        insert_node(&root, last);
        root = find_root(root);
    }

    // Inicializando variáveis de tempo
    struct timespec start, end;

    // Guardando valores de tempo
    clock_gettime(CLOCK_MONOTONIC, &start);
    Node* aux = binary_search(root, last);
    clock_gettime(CLOCK_MONOTONIC, &end);

    // liberando aux
    free(aux);

    // Calculando o tempo
    unsigned  time = (end.tv_sec * 1e9 + end.tv_nsec) - (start.tv_sec * 1e9 + start.tv_nsec);

    // Mostrando o tempo para iterate
    printf("%u\n", time);


    return 0;
}