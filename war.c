// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
// ============================================================================
//        
// ============================================================================
//
// OBJETIVOS:
// - Modularizar completamente o código em funções especializadas.
// - Implementar um sistema de missões para um jogador.
// - Criar uma função para verificar se a missão foi cumprida.
// - Utilizar passagem por referência (ponteiros) para modificar dados e
//   passagem por valor/referência constante (const) para apenas ler.
// - Foco em: Design de software, modularização, const correctness, lógica de jogo.
//
// ============================================================================

// Inclusão das bibliotecas padrão necessárias para entrada/saída, alocação de memória, manipulação de strings e tempo:
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>

// --- Constantes Globais ---
// Definem valores fixos para o número de territórios, missões e tamanho máximo de strings, facilitando a manutenção.
#define NUM_TERRITORIOS 5
#define NUM_MISSOES 3
#define MAX_STRING 50

// --- Estrutura de Dados ---
// Define a estrutura para um território, contendo seu nome, a cor do exército que o domina e o número de tropas.
typedef struct {
    char nome[MAX_STRING];
    char cor[MAX_STRING];
    int tropas;
} Territorio;

// --- Protótipos das Funções ---
// Declarações antecipadas de todas as funções que serão usadas no programa, organizadas por categoria.
// Funções de setup e gerenciamento de memória:
Territorio *alocarMapa(void);
void liberarMemoria(Territorio *territorios);
// Funções de interface com o usuário:
void cadastrarTerritorios(Territorio *territorios, int *totalTerritorios);
void listarTerritorios(Territorio *territorios, int totalTerritorios);
void ExibirMenu(void);
// Função utilitária:
void limparBufferEntrada(void);

// --- Função Principal (main) ---
// Função principal que orquestra o fluxo do jogo, chamando as outras funções em ordem.
int main(){
// 1. Configuração Inicial (Setup):
  setlocale(LC_ALL, "Portuguese");// - Define o locale para português.
  srand(time(NULL));// - Inicializa a semente para geração de números aleatórios com base no tempo atual.
  
  Territorio *mapa = alocarMapa();

    if (mapa == NULL) {
        // Se falhar, encerra o programa
        return 1;
    }
  int totalTerritorios = 0;// - Inicializa o contador de territórios cadastrados.
  int opcaoMenu;// - Variável para armazenar a opção escolhida no menu.
  
  
  do {
    ExibirMenu();// - Exibe o menu principal do jogo.
    scanf("%d", &opcaoMenu);
    limparBufferEntrada();
    switch (opcaoMenu) {
      case 1: 
        cadastrarTerritorios(mapa, &totalTerritorios);// - Permite o cadastro de novos territórios.
        listarTerritorios(mapa, totalTerritorios);// - Mostra os territórios cadastrados em formato de tabela.
        break;
      case 2:
        printf("Missao em desenvolvimento...\n");
        break;
      case 3:
        printf("Saindo do programa...\n");// - Mensagem de saída do programa.
        break;
      default:
        printf("Opcao invalida! Tente novamente.\n");// - Trata opções inválidas.
        break;
    }
  } while ( opcaoMenu != 3 );

  liberarMemoria(mapa);// - Libera a memória alocada para os territórios.

return 0;
}

// --- Implementação das Funções ---
// Funções de interface com o usuário:
void ExibirMenu() {
  printf("=======================================\n");
  printf("           PROJETO JOGO WAR\n");
  printf("=======================================\n");
  printf("1 - Atacar\n");
  printf("2 - Verificar Missao\n");
  printf("3 - Sair\n");
  printf("---------------------------------------\n");
  printf("Escolha uma opcao:   ");
}

// Funções de gerenciamento de territórios:
void cadastrarTerritorios(Territorio *territorios, int 
*totalTerritorios) {
  printf("\n---     Cadastro de Territorios     ---\n\n");
  for (int i = 0; i < NUM_TERRITORIOS; i++) {
    if(*totalTerritorios < NUM_TERRITORIOS){
    int indice = *totalTerritorios;

    printf("Digite o nome do territorio %d: ", i + 1);
    fgets(territorios[indice].nome, MAX_STRING, stdin);
    printf("Digite a cor do territorio %d: ", i + 1);
    fgets(territorios[indice].cor, MAX_STRING, stdin);
    printf("Digite o numero de tropas no territorio %d: ", i + 1);
    char buffer[MAX_STRING];
    fgets(buffer, MAX_STRING, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    territorios[indice].tropas = atoi(buffer);

    territorios[indice].nome[strcspn(territorios[indice].nome, "\n")] = '\0';
    territorios[indice].cor[strcspn(territorios[indice].cor, "\n")] = '\0';
    
    (*totalTerritorios)++;
    printf("\nTerritorio %d cadastrado com sucesso!\n\n", i + 1);
    
    }
  }
}

// Funções de listagem e exibição:
void listarTerritorios(Territorio *territorios, int totalTerritorios) {
  printf("\n ______________________________________________________________\n");
  printf("|                            MAPA                              |\n");
  printf("---------------------------------------------------------------\n");
  printf("| %-10s | %-20s | %-15s | %-6s |\n", "Numero", "Nome", "Cor", "Tropas");
  printf("---------------------------------------------------------------\n");
  for (int i = 0; i < totalTerritorios; i++) {
    printf("| %-10d | %-20s | %-15s | %-6d |\n", i + 1, 
    territorios[i].nome, territorios[i].cor, territorios[i].tropas);
  }
  printf("---------------------------------------------------------------\n");
  printf("Total de territorios cadastrados: %d\n\n", totalTerritorios);
  printf("---------------------------------------------------------------\n");
  printf("Pressione Enter para continuar...");
  getchar(); 
}

// Função utilitária:
void limparBufferEntrada() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF);
}

// Funções de gerenciamento de memória:
void liberarMemoria(Territorio *territorios) {
  free(territorios);
}

// Funções de fases do jogo:
Territorio *alocarMapa(void) {
    Territorio *territorios = calloc(NUM_TERRITORIOS, sizeof(Territorio));
    if (territorios == NULL) {
        printf("Erro: Falha ao alocar memoria.\n");
        return NULL;
    }
    return territorios;
}


