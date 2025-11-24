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
    int total_voos; //  contador de voos
} GRAFO;

// Protótipos
void cria_grafo(GRAFO* g);
void adiciona_aeroporto(GRAFO* g);
void remover_aeroporto (GRAFO* g);
void insere_voo(GRAFO* g);
void remove_voo(GRAFO* g);
void listar_aeroportos(GRAFO* g);
void mostra_matriz(GRAFO* g);
void verifica_conexao(GRAFO* g);
void busca_largura(GRAFO* g);
void total_voos (GRAFO *g);
void grau_aeroporto(GRAFO* g);
void criar_arquivo(GRAFO* g, int* versao);

int main() {

        system("chcp 65001 > nul");
        setlocale(LC_ALL, "pt_BR.UTF-8");

    GRAFO g;
    int op;

    int versao_arquivo = 1;

    cria_grafo(&g);

    printf("\033[94m"); //Código representa a cor azul

    printf(
    "  ===========================\n"
    "  |      AEROPORTO UNISC     |\n"
    "  ===========================\n"
    "  \\        |       |        / " "            ________________________________________         :^\\            ______    .\n"
    "  |        =========        |             |      ESTRUTURA DE DADOS E PROGRAMAÇÃO  |        |__`\\________-'__:__;\\___|\n"
    "  |        |       |        |            |        PROJETO FINAL - 2 SEMESTRE      |________`\\_  UNISC                |)\n"
    "  |        |       |        |           |         Instrument Airplane            |           `~~~~~~~~~---\\\\---\\|-'\n"
    "  |        =========        |            `---------------------------------------'                        (o)  (o)  \n"
    "   \\       |       |       /\n"
    "    \\      |       |      /\n"
    "      ===================\n"
    "      ||               ||\n"
    "      ||               ||       ___\n"
    "      ||               ||        | \\_______________                 ╔═══════════════════════════╗\n"
    "      ||   _           ||       ====( oooooooooo  O\\___             ║  TORRE DE CONTROLE AÉREO  ║\n"
    "      ||  | |          ||        (________/=====>______)-           ╚═══════════════════════════╝\n"
    "      ||  | |          ||                  OO        O\n"
    "  =======================================================================================================================================\n"
    );


    do {

        printf("\033[0m"); //reseta a cor 
   
        printf("\033[1;32m");//Código define a cor verde 
   
        printf("\n1. Adicionar aeroporto");
        printf("\n2. Remover aeroporto");
        printf("\n3. Inserir voo");
        printf("\n4. Remover voo");
        printf("\n5. Listar aeroportos");
        printf("\n6. Exibir matriz de voos");
        printf("\n7. Verificar se há voo entre dois aeroportos");
        printf("\n8. Realizar busca em largura");
        printf("\n9. Verficar quantidade de voos existentes");
        printf("\n10. Verificar grau do aeroporto(Quantos voos chegam e quantos saem)");
        printf("\n0. Sair");
        printf("\033[0m");  // reset cor

        printf("\n\nEntrada >>  ");
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
                listar_aeroportos(&g);
                break;
            case 6:
                mostra_matriz(&g);
                break;
            case 7:
                verifica_conexao(&g);
                break;
            case 8:
                busca_largura(&g);
                break;
            case 9:
                total_voos(&g);
                break;
            case 10:
                grau_aeroporto(&g);
                break;
            case 0:
                printf("\033[1;36m\nSaindo...\n\033[0m");
                printf("\n");
                break;
            default:
                printf("\033[1;31m\nOpção inválida!\n\033[0m");

        }

    } while(op != 0);

    return 0;
}

void cria_grafo(GRAFO* g) {
    g->vertices = 0;
    g->total_voos = 0;
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

    getchar();
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
            g->total_voos--;
        }
    }

    //Voos que CHEGAM no aeroporto removido
    for (int i = 0; i < g->vertices; i++) {
        if (g->matriz[i][indice] != INFINITO) {
            printf(" - %s -> %s\n", g->aeroportos[i], g->aeroportos[indice]);
            encontrou = 1;
            g->total_voos--;
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

    if (origem == destino){
        printf("\nNão é possível cadastra um voo de um aeroporto para ele mesmo!");
        return; 
    }

    if(origem < 0 || destino < 0 || origem >= g->vertices || destino >= g->vertices) {
        printf("\nAeroporto inválido!\n");
        return;
    }   

    if(g->matriz[origem][destino] != INFINITO) {
        printf("\nJá existe um voo de %s para %s!\n", g->aeroportos[origem], g->aeroportos[destino]);
        return;
    }

    printf("\nDigite a distância entre os aeroportos, em KM: ");
    scanf("%d", &distancia);

    if(distancia >= INFINITO) {
        printf("\nDistância inválida!");
        return;
    }

    g->matriz[origem][destino] = distancia;
    g->total_voos++; 
    printf("\nVoo criado com sucesso de %s para %s com distância de %dKM!\n", g->aeroportos[origem], g->aeroportos[destino], g->matriz[origem][destino]);
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
    g->total_voos--; 
    printf("\nVoo removido com sucesso!\n");
}

void listar_aeroportos(GRAFO *g){
    if (g->vertices == 0) {
        printf("\nNão há aeroportos para listar!\n");
        return;
    }

    printf("\nLista de aeroportos:\n");
    for(int i = 0; i < g->vertices; i++)
        printf("%d - %s\n", i, g->aeroportos[i]);
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
    if(g->vertices == 0) {
        printf("\nNenhum aeroporto cadastrado!\n");
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

    if(g->matriz[origem][destino] != INFINITO)
        printf("\nHá um voo de %dKM do %s para o %s\n", g->matriz[origem][destino], g->aeroportos[origem], g->aeroportos[destino]);
    else
        printf("\nNão há voo do %s para o %s\n", g->aeroportos[origem], g->aeroportos[destino]);
}

void busca_largura(GRAFO* g) {

    //verificar se grafo esta vazio
    if (g->vertices == 0) {
        printf("\nNenhum aeroporto cadastrado!\n");
        return;
    }

    //ponto de inicio
    int inicio;


    //listagem de opções de aeroportos
    printf("\nLista de aeroportos:\n");
    for (int i = 0; i < g->vertices; i++) {
        printf("%d - %s\n", i, g->aeroportos[i]);
    }

    printf("\nDigite o número do aeroporto para iniciar a BFS: ");
    scanf("%d", &inicio);

    //condicoes de invalidez: ponto de inicio menor que 0 e inicio maior que a quantidade total de vertices
    if (inicio < 0 || inicio >= g->vertices) {
        printf("\nAeroporto inválido!\n");
        return;
    }

    int visitado[MAX] = {0};
    int fila[MAX];
    int ini = 0;
    int fim = 0;

    fila[fim] = inicio;
    fim += 1;

    visitado[inicio] = 1;

    printf("\nOrdem de visita (BFS) a partir de %s:\n", g->aeroportos[inicio]);

    while (ini < fim) {

        int atual = fila[ini];
        ini += 1;

        printf("%s", g->aeroportos[atual]);

        // Percorre todos os possíveis vizinhos
        for (int i = 0; i < g->vertices; i++) {

            // Se existe ligação e ainda não foi visitado
            if (g->matriz[atual][i] != INFINITO && visitado[i] == 0) {

                visitado[i] = 1;

                fila[fim] = i;
                fim += 1;
            }
        }
    }

    printf("\n");
}

void total_voos (GRAFO *g){
    //A cada adição e remoção de voo o contador recebe + ou -, a função serve somente para mostrar
    if (g->total_voos <=0)
        printf("\nNão existem voos cadastrados no sistema!\n");
    else if (g->total_voos == 1)
        printf("\nExiste %d voo cadastrados no sistema!\n", g->total_voos);
    else
        printf("\nExiste %d voos cadastrados no sistema!\n", g->total_voos);
}

void grau_aeroporto(GRAFO* g) {

    if (g->vertices == 0) {
        printf("\nNenhum aeroporto cadastrado!\n");
        return;
    }

    int indice;

    // Mostra todos os aeroportos com seus índices
    printf("\nLista de aeroportos:\n");
    for (int i = 0; i < g->vertices; i++)
        printf("%d - %s\n", i, g->aeroportos[i]);

    printf("\nDigite o número do aeroporto para verificar o grau: ");
    scanf("%d", &indice);

    // Validação da entrada do usuário
    if (indice < 0 || indice >= g->vertices) {
        printf("\nAeroporto inválido!\n");
        return;
    }

    int grau_saida = 0;
    int grau_entrada = 0;

    // Conta quantos voos saem do aeroporto (linha da matriz)
    for (int j = 0; j < g->vertices; j++){
        if (g->matriz[indice][j] != INFINITO)
            grau_saida++;
    }
    // Conta quantos voos chegam ao aeroporto (coluna da matriz)
    for (int i = 0; i < g->vertices; i++){
        if (g->matriz[i][indice] != INFINITO)
            grau_entrada++;
    }   
    
    printf("\nAeroporto: %s", g->aeroportos[indice]);
    printf("\nGrau de emissão (voos que saem): %d", grau_saida);
    printf("\nGrau de recepção (voos que chegam): %d\n", grau_entrada);
}