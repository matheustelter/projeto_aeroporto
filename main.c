#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
//CEBOLA
#define MAX 20123123
#define TAM_NOME 50

typedef struct grafo {
    int vertices;
    char aeroportos[MAX][TAM_NOME];
    int matriz[MAX][MAX];
} GRAFO;

// Protótipos
void cria_grafo(GRAFO* g);
void adiciona_aeroporto(GRAFO* g);
void insere_voo(GRAFO* g);
void remove_voo(GRAFO* g);
void mostra_matriz(GRAFO* g);
void verifica_conexao(GRAFO* g);

int main() {

        system("chcp 65001 > nul");
        setlocale(LC_ALL, "pt_BR.UTF-8");

    GRAFO g;
    int op;

    cria_grafo(&g);

    do {
        printf("\n\tSISTEMA DE CONTROLE AÉREO");
        printf("\n--------------------------------------------");
        printf("\n1 - Adicionar aeroporto");
        printf("\n2 - Inserir voo (ligação entre aeroportos)");
        printf("\n3 - Remover voo");
        printf("\n4 - Exibir matriz de voos");
        printf("\n5 - Verificar se há voo entre dois aeroportos");
        printf("\n0 - Sair");
        printf("\n--------------------------------------------");
        printf("\nOpção: ");
        scanf("%d", &op);
        getchar(); // limpar buffer

        switch(op) {
            case 1: 
                adiciona_aeroporto(&g);
                break;
            case 2: 
                insere_voo(&g); 
                break;
            case 3: 
                remove_voo(&g);
                break;
            case 4: 
                mostra_matriz(&g); 
                break;
            case 5: 
                verifica_conexao(&g); 
                break;
            case 0: 
                printf("\nSaindo...\n"); 
                break;
            default:
                printf("\nOpção inválida!\n");
        }

    } while(op != 0);

    return 0;
}

void cria_grafo(GRAFO* g) {
    g->vertices = 0;
    for(int i = 0; i < MAX; i++)
        for(int j = 0; j < MAX; j++)
            g->matriz[i][j] = 0;
}

void adiciona_aeroporto(GRAFO* g) {
    if(g->vertices >= MAX) {
        printf("\nLimite máximo de %d aeroportos atingido!\n", MAX);
        return;
    }

    printf("\nDigite o nome do aeroporto: ");
    fgets(g->aeroportos[g->vertices], TAM_NOME, stdin);
    g->aeroportos[g->vertices][strcspn(g->aeroportos[g->vertices], "\n")] = '\0'; // remover \n

    g->vertices++;
    printf("\nAeroporto adicionado com sucesso!\n");
}

void insere_voo(GRAFO* g) {
    if(g->vertices < 2) {
        printf("\nÉ necessário pelo menos 2 aeroportos cadastrados para criar um voo!\n");
        return;
    }

    int origem, destino;
    printf("\nLista de aeroportos:\n");
    for(int i = 0; i < g->vertices; i++)
        printf("%d - %s\n", i, g->aeroportos[i]);

    printf("\nDigite o número do aeroporto de origem: ");
    scanf("%d", &origem);
    printf("Digite o número do aeroporto de destino: ");
    scanf("%d", &destino);

    if(origem < 0 || destino < 0 || origem >= g->vertices || destino >= g->vertices) {
        printf("\nAeroporto inválido!\n");
        return;
    }

    if(g->matriz[origem][destino] == 1) {
        printf("\nJá existe um voo de %s para %s!\n", g->aeroportos[origem], g->aeroportos[destino]);
        return;
    }

    g->matriz[origem][destino] = 1;
    printf("\nVoo criado com sucesso de %s para %s!\n", g->aeroportos[origem], g->aeroportos[destino]);
}

void remove_voo(GRAFO* g) {
    int origem, destino, existe = 0;

    // verifica se há pelo menos um voo
    for(int i = 0; i < g->vertices; i++)
        for(int j = 0; j < g->vertices; j++)
            if(g->matriz[i][j] == 1)
                existe = 1;

    if(!existe) {
        printf("\nNão há voos cadastrados para remover!\n");
        return;
    }

    printf("\nLista de aeroportos:\n");
    for(int i = 0; i < g->vertices; i++)
        printf("%d - %s\n", i, g->aeroportos[i]);

    printf("\nDigite o número do aeroporto de origem: ");
    scanf("%d", &origem);
    printf("Digite o número do aeroporto de destino: ");
    scanf("%d", &destino);

    if(origem < 0 || destino < 0 || origem >= g->vertices || destino >= g->vertices) {
        printf("\nAeroporto inválido!\n");
        return;
    }

    if(g->matriz[origem][destino] == 0) {
        printf("\nNão existe voo de %s para %s para remover!\n", g->aeroportos[origem], g->aeroportos[destino]);
        return;
    }

    g->matriz[origem][destino] = 0;
    printf("\nVoo removido com sucesso!\n");
}

void mostra_matriz(GRAFO* g) {
    if(g->vertices == 0) {
        printf("\nNenhum aeroporto cadastrado!\n");
        return;
    }

    printf("\nMatriz de Adjacência (Voos entre aeroportos):\n\n");
    printf("%15s", ""); // espaço inicial para alinhamento

    for(int i = 0; i < g->vertices; i++)
        printf("%10s", g->aeroportos[i]);
    printf("\n");

    for(int i = 0; i < g->vertices; i++) {
        printf("%10s", g->aeroportos[i]);
        for(int j = 0; j < g->vertices; j++)
            printf("%10d", g->matriz[i][j]);
        printf("\n");
    }
}

void verifica_conexao(GRAFO* g) {
    int origem, destino;
    printf("\nLista de aeroportos:\n");
    for(int i = 0; i < g->vertices; i++)
        printf("%d - %s\n", i, g->aeroportos[i]);

    printf("\nDigite o número do aeroporto de origem: ");
    scanf("%d", &origem);
    printf("Digite o número do aeroporto de destino: ");
    scanf("%d", &destino);

    if(origem < 0 || destino < 0 || origem >= g->vertices || destino >= g->vertices) {
        printf("\nAeroporto inválido!\n");
        return;
    }

    if(g->matriz[origem][destino] == 1)
        printf("\nHá um voo entre %s -> %s\n", g->aeroportos[origem], g->aeroportos[destino]);
    else
        printf("\nNão há voo entre %s -> %s\n", g->aeroportos[origem], g->aeroportos[destino]);
}
