#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Estrutura de Nó
typedef struct node {
    int value;
    struct node* next;
} Node;

// Estrutura de Tabela Hash
typedef struct hashTable {
    unsigned int m; // Tamanho da tabela
    unsigned int n;     // Quantidade de Elementos
    Node** nodes;
} HashTable;

// Protótipos das funções
void insert(HashTable* hashTable, int value);
void reHash(HashTable *hashTable);
int search(HashTable *hashTable, int value);
void delete(HashTable *hashTable, int value);

// Função Hash - Para transformar o valor da chave dada em uma chave da lista
unsigned int hash(int value, int m) {
    // Se o valor da operação for negativo, adicione +m, se não, devolva a operação
    return value % m < 0 ? (value % m) + m : value % m;
}

// Função Re-hash - Para aumentar a quantidade de espaços na tabela e evitar que o tempo não seja constante
void reHash(HashTable* hashTable) {
    // Pegando a lista anteriormente salva
    unsigned int old_m = hashTable->m;
    Node** old_nodes = hashTable->nodes;

    // Reconfigurar Tabela e Dobrar o Tamanho
    hashTable->m *= 2;  
    hashTable->n = 0;
    hashTable->nodes = (Node**)malloc(sizeof(Node*) * hashTable->m);

    // Nulificando endereços da lista dentro da tabela
    for(int i = 0; i < hashTable->m; i++) {
        hashTable->nodes[i] = NULL;
    }

    // Inserindo antigos valores na lista
    for(int i = 0;i < old_m; i++) {
        Node* aux = old_nodes[i];
        while(aux != NULL) {
            // Inserção dos elementos
            insert(hashTable, aux->value);

            // Variável para liberar memória alocada
            Node* toFree = aux;

            // Atualizando valor de aux;
            aux = aux->next;

            // Liberando rmemória antiga
            free(toFree);
        }
    }
    // Liberando memória da antiga lista
    free(old_nodes);
}

// Função para calcular o fator de carga - Usado para prever se a lista está constante ou não
float loadFactor(HashTable* hashTable) {
    return (float)hashTable->n / hashTable->m;
}

// Criando um novo nó
Node* create_node(int value) {
    // Alocando memória no novo nó
    Node* node = (Node*)malloc(sizeof(Node));

    // Alterando valores internos do nó
    node->value = value;
    node->next = NULL;

    // Retronando o nó
    return node;
}

// Inicialização de Tabela Hash
HashTable* create_table(unsigned int m) {
    // Alocando memória na nova tabela
    HashTable* hashTable = (HashTable*)malloc(sizeof(HashTable));

    // Alterando valores internos da tabela
    hashTable->m = m;
    hashTable->n = 0;
    hashTable->nodes = (Node**)malloc(sizeof(Node*) * m);

    // Nulificando endereços da lista dentro da tabela
    for(int i = 0; i < m; i++) {
        hashTable->nodes[i] = NULL;
    }

    // Retornando a tabela
    return hashTable;
}

// Inserindo elementos na Tabela Hash
void insert(HashTable* hashTable, int value) {
    // Transformando o elemento em uma chave - Esse processo não é necessário caso o Inserta já indique um chave
    unsigned int key = hash(value, hashTable->m);

    // Se o fator de carga for menor que 1, insira
    if(loadFactor(hashTable) < 1) {
        // Índice de acordo com a chave escolhida (ou transformada)
        unsigned int index = hash(key, hashTable->m);

        // Novo nó para ser inserido
        Node* new_node = create_node(value);

        // Verificando se, na tabela, o índice já possui algum valor
        if(hashTable->nodes[index] == NULL) {
            hashTable->nodes[index] = new_node;
        } else {
            // Pegando o node do índice atual
            Node* index_node = hashTable->nodes[index];
            // Procurnado o próximo índice da lista até não existir
            while(index_node->next != NULL) {
                index_node = index_node->next;
            }
            // Adicionando novo nó na lista
            index_node->next = new_node;
        }

        // Aumenta o valor da quantidade de itens na tabela
        hashTable->n++;
    // Se o fator de carga for maior ou igual a 1, refaça a lista maior
    } else {
        reHash(hashTable);
        insert(hashTable, value);
    }
}

// Procurando elementos na tabela Hash
int search(HashTable* hashTable, int value) {
    // Pegando elemento e transformando em chave
    unsigned int index = hash(value, hashTable->m); 
    Node* aux = hashTable->nodes[index];   

    while(aux != NULL) {
        if(aux->value == value) {
            return index;
        }
        aux = aux->next;
    }

    return -1;
}

// Excluindo elementos na tabela Hash
void delete_table(HashTable* hashTable) {
    for(int i=0; i < hashTable->m; i++) {
        Node* current_node = hashTable->nodes[i];

        while(current_node != NULL) {
            Node* aux_node = current_node;
            current_node = current_node->next;
            free(aux_node);
        }
    }

    free(hashTable->nodes);
    free(hashTable);
}

// Printar a tabela completa
void printHashTable(HashTable* hashTable) {
    for(int i = 0; i < hashTable->m; i++) {
        printf("[%d] -> ", i);
        Node* temp = hashTable->nodes[i];
        while(temp != NULL) {
            printf("(%d) -> ", temp->value);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

int main(int argc, char **argv) {
    // Quantidade de elementos na tabela
    unsigned int n = atoi(argv[1]);

    // Criando tabela hash com o tamanho fornecido pelo usuário
    HashTable* hashTable = create_table(n);

    // Inicializador de randomização
    srand(time(NULL));

    // inteiro auxiliar para ter acesso ao último elemento da lista
    int last;
    // Inserindo elemento aleatório na árvore binária
    for(int i = 0; i < n; i++) {
        last = rand();
        insert(hashTable, (last + (last % 2)));
    }

    last = rand();
    last = last + (last % 2);

    // Inicializando variáveis de tempo
    struct timespec start, end;

    // Guardando valores de tempo
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    int aux = search(hashTable, last);
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);

    // Calculando o tempo
    unsigned  time = (end.tv_sec * 1e9 + end.tv_nsec) - (start.tv_sec * 1e9 + start.tv_nsec);

    // Mostrando o tempo para iterate
    printf("%u\n", time);

    // Liberando memória
    delete_table(hashTable);

    return 0;
}