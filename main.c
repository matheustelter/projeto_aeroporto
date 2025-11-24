#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

#define MAX 20 //possível cadastrar no máximo 20 aeroportos
#define TAM_NOME 4 
#define INFINITO 9999999 // variavel de numero padrão para valor de arestas

typedef struct grafo {
    int vertices; //inicia contador aeroportos 
    char aeroportos[MAX][TAM_NOME]; //matriz que guarda sigla dos aeroportos
    int matriz[MAX][MAX]; //matriz de adjacência do grafo
    int total_voos; //contador de voos
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
void valor_passagem (GRAFO *g);
void grau_aeroporto(GRAFO* g);
void criar_arquivo(GRAFO* g, int* versao);
void aeroportos_inancansaveis(GRAFO* g);
void carregar_grafo_pre_pronto(GRAFO* g);


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
    "  \\        |       |        / " "             ________________________________________         :^\\            ______    .\n"
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
   
        printf("\033[1;33m\nMENU DE CONTROLE\n\033[0m");

        printf("\033[1;32m");//Código define a cor verde 

        printf("\n1. Adicionar aeroporto");
        printf("\n2. Remover aeroporto");
        printf("\n3. Inserir voo");
        printf("\n4. Remover voo");
        printf("\n5. Listar aeroportos");
        printf("\n6. Exibir matriz de voos");
        printf("\n7. Verificar se há voo entre dois aeroportos");
        printf("\n8. Buscar aeroportos inalcansáveis");
        printf("\n9. Realizar busca em largura");
        printf("\n10. Verficar quantidade de voos existentes");
        printf("\n11. Consultar valor da passagem");
        printf("\n12. Verificar grau do aeroporto(Quantos voos chegam e quantos saem)");
        printf("\n13. Carregar grafo de aeroportos Pré Pronto");
        printf("\n14. Criar arquivo do gráfico");
        
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
                aeroportos_inancansaveis(&g);
                break;
            case 9:
                busca_largura(&g);
                break;
            case 10:
                total_voos(&g);
                break;
            case 11:
                valor_passagem(&g);
                break;
            case 12:
                grau_aeroporto(&g);
                break;
            case 13: 
                carregar_grafo_pre_pronto(&g);
                break;
            case 14:
                criar_arquivo(&g, &versao_arquivo);
                break;
            case 0:
                printf("\033[1;31m\nSaindo...\n\033[0m");
                printf("\n");
                break;
            default:
                printf("\033[1;31m\nOpção inválida!\n\033[0m");

        }

    } while(op != 0);

    return 0;
}

void cria_grafo(GRAFO* g) {
    //inicia estrutura com valor 0
    g->vertices = 0;
    g->total_voos = 0;
    for(int i = 0; i < MAX; i++)
        for(int j = 0; j < MAX; j++)
            g->matriz[i][j] = INFINITO;
}

void adiciona_aeroporto(GRAFO* g) {

    printf("\033[1;33m");//Código define a cor azul 
    printf("\nOperação: Adicionar Aeroporto\n"); //descrição da atividade
    printf("\033[0m"); //reseta a cor

    if (g->vertices >= MAX) {
        printf("\nLimite máximo de aeroportos atingido!\n");
        return;
    }

    char sigla[TAM_NOME];

    while (1) {
        printf("\nDigite a sigla do aeroporto: ");
        scanf("%3s", sigla); // %3s pega somente as 3 primeiras caracteres da sigla digitada

        int c;
        while ((c = getchar()) != '\n' && c != EOF); //limpa o que foi digitado após as 3 primeiras caracteres

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

    printf("\033[1;33m");//Código define a cor azul 
    printf("\nOperação: Remover Aeroporto\n"); //descrição da atividade
    printf("\033[0m"); //reseta a cor

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
    for (int j = 0; j < g->vertices; j++) { //percorre a coluna 
        if (g->matriz[indice][j] != INFINITO) { 
            printf(" - %s -> %s\n", g->aeroportos[indice], g->aeroportos[j]);
            encontrou = 1;
            g->total_voos--;
        }
    }

    //Voos que CHEGAM no aeroporto removido
    for (int i = 0; i < g->vertices; i++) { //percorre a linha 
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

    printf("\033[1;33m");//Código define a cor azul 
    printf("\nOperação: Inserir Voo\n"); //descrição da atividade
    printf("\033[0m"); //reseta a cor

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

    if (origem == destino){ // impede infomrar um voo laço (dele para ele mesmo)
        printf("\nNão é possível cadastra um voo de um aeroporto para ele mesmo!");
        return; 
    }

    if(origem < 0 || destino < 0 || origem >= g->vertices || destino >= g->vertices) { 
        printf("\nAeroporto inválido!\n");
        return;
    }   

    if(g->matriz[origem][destino] != INFINITO) { // se espaço no array for diferente de infinito significa que já existe voo 
        printf("\nJá existe um voo de %s para %s!\n", g->aeroportos[origem], g->aeroportos[destino]);
        return;
    }

    // após verificações pede a distância
    printf("\nDigite a distância entre os aeroportos, em KM: ");
    scanf("%d", &distancia);

    if(distancia >= INFINITO) {
        printf("\nDistância inválida!");
        return;
    }

    g->matriz[origem][destino] = distancia; // onde era INFINITO recebe distância de acordo com aeroporto origem e destino
    g->total_voos++; 
    printf("\nVoo criado com sucesso de %s para %s com distância de %dKM!\n", g->aeroportos[origem], g->aeroportos[destino], g->matriz[origem][destino]);
}

void remove_voo(GRAFO* g) {

    printf("\033[1;33m");//Código define a cor azul 
    printf("\nOperação: Remover Voo\n"); //descrição da atividade
    printf("\033[0m"); //reseta a cor

    int origem, destino, existe = 0;

    //verifica se há pelo menos um voo
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

    if(g->matriz[origem][destino] == INFINITO) { // se espaço no array for infinito significa que ñ existe voo para remover 
        printf("\nNão existe voo de %s para %s para remover!\n", g->aeroportos[origem], g->aeroportos[destino]);
        return;
    }

    g->matriz[origem][destino] = INFINITO; // onde existia a distância passa a ser INFINITO (voo excluído)
    g->total_voos--; 
    printf("\nVoo removido com sucesso!\n");
}

void listar_aeroportos(GRAFO *g){

    printf("\033[1;33m");//Código define a cor azul 
    printf("\nOperação: Listar Aeroportos\n"); //descrição da atividade
    printf("\033[0m"); //reseta a cor

    if (g->vertices == 0) {
        printf("\nNão há aeroportos para listar!\n");
        return;
    }

    printf("\nLista de aeroportos:\n");
    for(int i = 0; i < g->vertices; i++)
        printf("%d - %s\n", i, g->aeroportos[i]);
}

void mostra_matriz(GRAFO* g) {

    printf("\033[1;33m");//Código define a cor azul 
    printf("\nOperação: Exibir Matriz de Adjacência\n"); //descrição da atividade
    printf("\033[0m"); //reseta a cor

    if(g->vertices == 0) {
        printf("\nNenhum aeroporto cadastrado!\n");
        return;
    }

    printf("\nMatriz de voos entre aeroportos):\n\n");
    printf("%11s", ""); // espaço inicial para alinhamento

    // imprime as siglas como nome das colunas
    for(int i = 0; i < g->vertices; i++) 
        printf("%10s", g->aeroportos[i]);
    printf("\n");

    for(int i = 0; i < g->vertices; i++) { 
        printf("%10s", g->aeroportos[i]); //imprime as sligas como nome da linha
        for(int j = 0; j < g->vertices; j++) //percorre todas colunas da linha
            if(g->matriz[i][j] == INFINITO) {
                printf("   Sem voo");   //se espaço no array estiver como infinito irá informar que não existe voo entre os aeroportos
            } else {
                printf("%10d", g->matriz[i][j]); // caso contrário mostra a distância entre os aeroportos 
            }
        printf("\n");
    }
}

void verifica_conexao(GRAFO* g) {

    printf("\033[1;33m");//Código define a cor azul 
    printf("\nOperação: Verificar se existe voo entre dois aeroportos\n"); //descrição da atividade
    printf("\033[0m"); //reseta a cor

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

    if(g->matriz[origem][destino] != INFINITO) // se no array estiver dif infinito (não foi cadastrado voo) irá imrpimir a conexão
        printf("\nHá um voo de %dKM do %s para o %s\n", g->matriz[origem][destino], g->aeroportos[origem], g->aeroportos[destino]);
    else // caso contrário irá informar que não existe voo cadastrado
        printf("\nNão há voo do %s para o %s\n", g->aeroportos[origem], g->aeroportos[destino]);
}

void busca_largura(GRAFO* g) {

    printf("\033[1;33m");//Código define a cor azul 
    printf("\nOperação: Busca em Largura\n"); //descrição da atividade
    printf("\033[0m"); //reseta a cor

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

        printf("-%s", g->aeroportos[atual]);

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

    printf("\033[1;33m");//Código define a cor azul 
    printf("\nOperação: Verficar Total de Voos\n"); //descrição da atividade
    printf("\033[0m"); //reseta a cor

    //A cada adição e remoção de voo o contador recebe + ou -, a função serve somente para mostrar
    if (g->total_voos <=0)
        printf("\nNão existem voos cadastrados no sistema!\n");
    else if (g->total_voos == 1)
        printf("\nExiste %d voo cadastrados no sistema!\n", g->total_voos);
    else
        printf("\nExiste %d voos cadastrados no sistema!\n", g->total_voos);
}

void valor_passagem (GRAFO *g){

    printf("\033[1;33m");//Código define a cor azul 
    printf("\nOperação: Consultar Valor da Passagem\n"); //descrição da atividade
    printf("\033[0m"); //reseta a cor

    if (g->total_voos <=0){
        printf("\nNenhum voo cadastrado!\n");
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

    if(g->matriz[origem][destino] != INFINITO){
        printf("\nValor da passagem de %s para %s:\n", g->aeroportos[origem], g->aeroportos[destino]);
        printf("R$ %d,00\n", (g->matriz[origem][destino])*2);
    }else{
        printf("\nNão existe voo para %s -> %s!\n", g->aeroportos[origem], g->aeroportos[destino]);
    }
}

void grau_aeroporto(GRAFO* g) {

    printf("\033[1;33m");//Código define a cor azul 
    printf("\nOperação: Verificar grau de emissão e recepção do aeroporto\n"); //descrição da atividade
    printf("\033[0m"); //reseta a cor

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

void criar_arquivo(GRAFO* g, int* versao) {

    printf("\033[1;33m");//Código define a cor azul 
    printf("\nOperação: Criar Arquivo\n"); //descrição da atividade
    printf("\033[0m"); //reseta a cor

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

void carregar_grafo_pre_pronto(GRAFO* g) {

    printf("\033[1;33m");//Código define a cor azul 
    printf("\nOperação: Carregar Grafo Pré Pronto\n"); //descrição da atividade
    printf("\033[0m"); //reseta a cor

    printf("\nSubstituindo dados...\n");

    g->vertices = 7;

    char* aeroportos_prontos[MAX] = {
        "GRU",
        "GIG",  
        "JFK",
        "LAX",
        "CDG",
        "HND",
        "DXB"
    };

    for(int i = 0; i < g->vertices; i++) {
        strcpy(g->aeroportos[i], aeroportos_prontos[i]);
    }
    
    for(int i = 0; i < MAX; i++) {
        for(int j = 0; j < MAX; j++) {
            g->matriz[i][j] = INFINITO; // Zera a matriz de arestas
        }
    }

    g->matriz[0][1] = 400;    
    g->matriz[1][0] = 420;   
    g->matriz[2][3] = 3800;  
    g->matriz[3][4] = 9100;  
    g->matriz[4][5] = 9700;  
    g->matriz[6][0] = 12000; 
    g->matriz[5][6] = 7800;

    g->total_voos = 7;

    printf("\nDados pré prontos inseridos!\n");
}

void aeroportos_inancansaveis(GRAFO* g) {

    printf("\033[1;33m");
    printf("\nOperação: Buscar Aeroportos Inalcansáveis\n");
    printf("\033[0m");

    if (g->vertices == 0) {
        printf("\nNenhum aeroporto cadastrado!\n");
        return;
    }

    int inicio;

    printf("\nLista de aeroportos:\n");
    for (int i = 0; i < g->vertices; i++) {
        printf("%d - %s\n", i, g->aeroportos[i]);
    }

    printf("\nDigite o número do aeroporto: ");
    scanf("%d", &inicio);

    if (inicio < 0 || inicio >= g->vertices) {
        printf("\nAeroporto inválido!\n");
        return;
    }

    int visitado[MAX] = {0};
    int fila[MAX];
    int ini = 0;
    int fim = 0;

    fila[fim++] = inicio;
    visitado[inicio] = 1;

    while (ini < fim) {

        int atual = fila[ini++];

        for (int i = 0; i < g->vertices; i++) {

            if (g->matriz[atual][i] != INFINITO && visitado[i] == 0) {
                visitado[i] = 1;
                fila[fim++] = i;
            }
        }
    }

    printf("\nAeroportos inalcansáveis deste ponto:\n");

    int achou = 0;

    for (int i = 0; i < g->vertices; i++) {
        if (!visitado[i]) {
            printf(" - %s\n", g->aeroportos[i]);
            achou = 1;
        }
    }

    if (!achou) {
        printf("Todos os aeroportos são alcançáveis a partir deste ponto.\n");
    }

    printf("\n");
}
