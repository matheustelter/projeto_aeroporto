#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

#define MAX 20
#define TAM_NOME 4
#define INFINITO 9999999 // variavel de numero padrão para valor de arestas

typedef struct grafo {
    int vertices;
    char aeroportos[MAX][TAM_NOME];
    int matriz[MAX][MAX];
} GRAFO;

// Protótipos
void cria_grafo(GRAFO* g);
void adiciona_aeroporto(GRAFO* g);
void remover_aeroporto (GRAFO* g);
void insere_voo(GRAFO* g);
void remove_voo(GRAFO* g);
void mostra_matriz(GRAFO* g);
void verifica_conexao(GRAFO* g);

void criar_arquivo(GRAFO* g, int* versao);

int main() {

        system("chcp 65001 > nul");
        setlocale(LC_ALL, "pt_BR.UTF-8");

    GRAFO g;
    int op;

    int versao_arquivo = 1;

    cria_grafo(&g);

    do {
        printf("\n\tSISTEMA DE CONTROLE AÉREO");
        printf("\n--------------------------------------------");
        printf("\n1 - Adicionar aeroporto");
        printf("\n2 - Remover aeroporto");
        printf("\n3 - Inserir voo (ligação entre aeroportos)");
        printf("\n4 - Remover voo");
        printf("\n5 - Exibir matriz de voos");
        printf("\n6 - Verificar se há voo entre dois aeroportos");
        printf("\n7 - Criar arquivo GraphViz");
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
                remover_aeroporto(&g);
                break; 
            case 3: 
                insere_voo(&g); 
                break;
            case 4: 
                remove_voo(&g);
                break;
            case 5: 
                mostra_matriz(&g); 
                break;
            case 6: 
                verifica_conexao(&g); 
                break;
            case 7:
                criar_arquivo(&g, &versao_arquivo);
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
            g->matriz[i][j] = INFINITO;
}

void adiciona_aeroporto(GRAFO* g) {
    if (g->vertices >= MAX) {
        printf("Limite máximo de aeroportos atingido!\n");
        return;
    }

    char sigla[TAM_NOME];

    while (1) {
        printf("Digite a sigla do aeroporto: ");
        scanf("%3s", sigla);

        // Verificar repetição
        int repetido = 0;
        for (int i = 0; i < g->vertices; i++) {
            if (strcmp(g->aeroportos[i], sigla) == 0) { //strcmp = verifica se a sigla ja existe e retorna 0 se sim
                repetido = 1;
                break;
            }
        }

        if (repetido) { 
            printf("Erro: esse aeroporto já foi cadastrado!\n");
            continue;
        }

        break;
    }

    strcpy(g->aeroportos[g->vertices], sigla); //strcpy irá copiar a sigla para o próximo vértice (aeroporto)
    g->vertices++;

    printf("Aeroporto %s adicionado com sucesso!\n", sigla);
}

void remover_aeroporto(GRAFO* g) {
    if (g->vertices == 0) {
        printf("\nNão há aeroportos para remover!\n");
        return;
    }

    int indice;

    printf("\nLista de aeroportos:\n");
    for (int i = 0; i < g->vertices; i++)
        printf("%d - %s\n", i, g->aeroportos[i]);

    printf("\nDigite o número do aeroporto que deseja remover: ");
    scanf("%d", &indice);

    if (indice < 0 || indice >= g->vertices) {
        printf("\nAeroporto inválido!\n");
        return;
    }

    printf("\nVoos que serão removidos por causa da exclusão de %s:\n",
           g->aeroportos[indice]);

    int encontrou = 0;

    //Voos que SAEM do aeroporto removido
    for (int j = 0; j < g->vertices; j++) {
        if (g->matriz[indice][j] != INFINITO) {
            printf(" - %s -> %s\n", g->aeroportos[indice], g->aeroportos[j]);
            encontrou = 1;
        }
    }

    //Voos que CHEGAM no aeroporto removido
    for (int i = 0; i < g->vertices; i++) {
        if (g->matriz[i][indice] != INFINITO) {
            printf(" - %s -> %s\n", g->aeroportos[i], g->aeroportos[indice]);
            encontrou = 1;
        }
    }

    if (!encontrou)
        printf("Nenhum voo será perdido.\n");

    //Remoção do aeroporto da lista
    for (int i = indice; i < g->vertices - 1; i++) {
        strcpy(g->aeroportos[i], g->aeroportos[i + 1]);
    }

    //Remoção da linha
    for (int i = indice; i < g->vertices - 1; i++) {
        for (int j = 0; j < g->vertices; j++)
            g->matriz[i][j] = g->matriz[i + 1][j];
    }

    //Remoção da coluna
    for (int j = indice; j < g->vertices - 1; j++) {
        for (int i = 0; i < g->vertices; i++)
            g->matriz[i][j] = g->matriz[i][j + 1];
    }

    g->vertices--;

    printf("\nAeroporto removido com sucesso!\n");
}

void insere_voo(GRAFO* g) {
    if(g->vertices < 2) {
        printf("\nÉ necessário pelo menos 2 aeroportos cadastrados para criar um voo!\n");
        return;
    }

    int origem, destino, distancia;
    printf("\nLista de aeroportos:\n");
    for(int i = 0; i < g->vertices; i++)
        printf("%d - %s\n", i, g->aeroportos[i]);

    printf("\nDigite o número do aeroporto de origem: ");
    scanf("%d", &origem);
    printf("Digite o número do aeroporto de destino: ");
    scanf("%d", &destino);
    printf("\nDigite a distância entre os aeroportos, em metros: ");
    scanf("%d", &distancia);

    if(origem < 0 || destino < 0 || origem >= g->vertices || destino >= g->vertices) {
        printf("\nAeroporto inválido!\n");
        return;
    }

    if(g->matriz[origem][destino] != INFINITO) {
        printf("\nJá existe um voo de %s para %s!\n", g->aeroportos[origem], g->aeroportos[destino]);
        return;
    }

    if(distancia >= INFINITO) {
        printf("\nDistância inválida!");
        return;
    }

    g->matriz[origem][destino] = distancia;
    printf("\nVoo criado com sucesso de %s para %s com distancia de %d!\n", g->aeroportos[origem], g->aeroportos[destino], g->matriz[origem][destino]);
}

void remove_voo(GRAFO* g) {
    int origem, destino, existe = 0;

    // verifica se há pelo menos um voo
    for(int i = 0; i < g->vertices; i++){
        for(int j = 0; j < g->vertices; j++){
            if(g->matriz[i][j] != INFINITO)
                existe = 1;
        }
    }

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

    if(g->matriz[origem][destino] == INFINITO) {
        printf("\nNão existe voo de %s para %s para remover!\n", g->aeroportos[origem], g->aeroportos[destino]);
        return;
    }

    g->matriz[origem][destino] = INFINITO;
    printf("\nVoo removido com sucesso!\n");
}

void mostra_matriz(GRAFO* g) {
    if(g->vertices == 0) {
        printf("\nNenhum aeroporto cadastrado!\n");
        return;
    }

    printf("\nMatriz de voos entre aeroportos):\n\n");
    printf("%11s", ""); // espaço inicial para alinhamento

    for(int i = 0; i < g->vertices; i++)
        printf("%10s", g->aeroportos[i]);
    printf("\n");

    for(int i = 0; i < g->vertices; i++) {
        printf("%10s", g->aeroportos[i]);
        for(int j = 0; j < g->vertices; j++)
            if(g->matriz[i][j] == INFINITO) {
                printf("   Sem voo");
            } else {
                printf("%10d", g->matriz[i][j]);
            }
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

    if(g->matriz[origem][destino] != INFINITO)
        printf("\nHá um voo entre %s -> %s\n", g->aeroportos[origem], g->aeroportos[destino]);
    else
        printf("\nNão há voo entre %s -> %s\n", g->aeroportos[origem], g->aeroportos[destino]);
}

void criar_arquivo(GRAFO* g, int* versao) {
    if(g->vertices == 0) {
        printf("\nNenhum aeroporto cadastrado!\n");
        return;
    }

    FILE *arquivo;

    char nome_arquivo[20]; 

    sprintf(nome_arquivo, "grafo-%d.txt", *versao);

    arquivo = fopen(nome_arquivo, "w");


    if(arquivo == NULL) {
        printf("\nErro ao abrir o arquivo\n");
        return;
    } else {
        printf("\nArquivo criado com sucesso\n");
    }

    fprintf(arquivo,
    "digraph aeroportos {\n"
    "  graph [\n"
    "    layout = neato,\n"
    "    model = \"mds\",\n"
    "    splines = true,\n"
    "    overlap = false,\n"
    "    fontname = \"Arial\",\n"
    "    fontsize = 12\n"
    "  ];\n"
    "  node [\n"
    "    shape = square,\n"
    "    style = filled,\n"
    "    fillcolor = \"#58a6ff\",\n"
    "    fontcolor = white,\n"
    "    fontname = \"Arial\",\n"
    "    fixedsize = true,\n"
    "    width = 1.2\n"
    "  ];\n"
    "  edge [\n"
    "    fontname = \"Arial\",\n"
    "    fontsize = 20,\n"
    "    color = \"#8b949e\",\n"
    "    fontcolor = \"#c9d1d9\",\n"
    "    penwidth = 10\n"
    "  ];\n"
    );

    for(int i = 0; i < g->vertices; i++) {
        fprintf(arquivo, "\n%d [label=\"%s\"];", i, g->aeroportos[i]);
    }

    fprintf(arquivo, "\n");

    for(int i = 0; i < MAX; i++) {
        for(int j = 0; j < MAX; j++) {
            if(g->matriz[i][j] != INFINITO) {
                fprintf(arquivo, "\n%d -> %d [label=\"%dkm\", len=\"%f\"];", i, j, g->matriz[i][j], g->matriz[i][j] / 1000.0);
            }
        }
    }

    fprintf(arquivo, "\n}");

    fclose(arquivo);

    (*versao)++;
}