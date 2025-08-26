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

// Inclusão das bibliotecas padrão necessárias para entrada/saída, alocação de memória, manipulação de strings e tempo.
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
typedef struct Territorio
{
    char nome[MAX_STRING];
    char cor[MAX_STRING]; 
    int tropas;
} Territorio;

// --- Protótipos das Funções ---
// Declarações antecipadas de todas as funções que serão usadas no programa, organizadas por categoria.
// Funções de setup e gerenciamento de memória:

// Funções de interface com o usuário:
// Funções de lógica principal do jogo:
// Função utilitária:
void limparBufferEntrada(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
};

// --- Função Principal (main) ---
// Função principal que orquestra o fluxo do jogo, chamando as outras funções em ordem.
int main() {
    // 1. Configuração Inicial (Setup):
    // - Define o locale para português.
    setlocale(LC_ALL, "Portuguese");
    // - Inicializa a semente para geração de números aleatórios com base no tempo atual.
    srand(time(NULL));
    // - Aloca a memória para o mapa do mundo e verifica se a alocação foi bem-sucedida.
    // - Preenche os territórios com seus dados iniciais (tropas, donos, etc.).
    // - Define a cor do jogador e sorteia sua missão secreta.
    struct Territorio mapa[NUM_TERRITORIOS];
    int totalTerritorios = 0;
    int opcaoMenu;
    // 2. Laço Principal do Jogo (Game Loop):
    // - Roda em um loop 'do-while' que continua até o jogador sair (opção 0) ou vencer.
    // - A cada iteração, exibe o mapa, a missão e o menu de ações.
    // - Lê a escolha do jogador e usa um 'switch' para chamar a função apropriada:
    //   - Opção 1: Inicia a fase de ataque.
    //   - Opção 2: Verifica se a condição de vitória foi alcançada e informa o jogador.
    //   - Opção 0: Encerra o jogo.
    // - Pausa a execução para que o jogador possa ler os resultados antes da próxima rodada.
    do
    {
        printf("\n============================================\n");
        printf("---            Menu Principal            ---\n");
        printf("============================================\n");
        printf("1. Cadastro de Territórios\n");
        printf("2. Lista de Territórios Cadastrados\n");
        printf("0. Sair do Jogo\n");
        printf("--------------------------------------------\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcaoMenu);
        limparBufferEntrada();
        switch (opcaoMenu)
        {
        case 1:
            if(totalTerritorios < NUM_TERRITORIOS){
                printf("------------------------------------------------\n");
                printf("---          Cadastro de Territórios         ---\n");
                printf("------------------------------------------------\n");
                printf("Digite o nome do território: ");
                fgets(mapa[totalTerritorios].nome, MAX_STRING, stdin);
                
                printf("Digite a cor do exército: ");
                fgets(mapa[totalTerritorios].cor, MAX_STRING, stdin);
                 
                printf("Digite o número de tropas: ");
                scanf("%d", &mapa[totalTerritorios].tropas);
                // Remove o '\n' do final:
                mapa[totalTerritorios].nome[strcspn(mapa[totalTerritorios].nome, "\n")] = 0; 
                mapa[totalTerritorios].cor[strcspn(mapa[totalTerritorios].cor, "\n")] = 0; 
                
                limparBufferEntrada();
                
                totalTerritorios++;
                printf("\nTerritório cadastrado com sucesso!!!\n");
                } else {
                printf("Limite de territórios atingido!!!\n");
            }
            break;
        case 2:
            if (totalTerritorios == 0) {
                printf("\nNenhum território cadastrado!\nPressione Enter para continuar...\n");
            } else {
                printf("\n ______________________________________________________________\n");
                printf("|                            MAPA                              |\n");
                printf("---------------------------------------------------------------\n");
                printf("| %-10s | %-20s | %-15s | %-6s |\n", "Território", "Nome", "Cor do Exército", "Tropas");
                printf("---------------------------------------------------------------\n");
                for (int i = 0; i < totalTerritorios; i++) {
                    printf("| %-10d | %-20s | %-15s | %-6d |\n",
                        i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
                }
                printf("---------------------------------------------------------------\n");
                printf("Total de Territórios: %d/5\n", totalTerritorios);
                printf("---------------------------------------------------------------\n");
                printf("Pressione ENTER para voltar ao menu...\n");
            }
            limparBufferEntrada();
            break;
        case 0:
            printf("Saindo do jogo. Até a próxima!\n");
            break;

        default:
            printf("\nOpção inválida! Tente novamente!\n");
            printf("Pressione Enter para continuar...");
            limparBufferEntrada();
            break;
        }
    } while (opcaoMenu != 0);
    
    // 3. Limpeza:
    // - Ao final do jogo, libera a memória alocada para o mapa para evitar vazamentos de memória.

    return 0;
}

// --- Implementação das Funções ---

// alocarMapa():
// Aloca dinamicamente a memória para o vetor de territórios usando calloc.
// Retorna um ponteiro para a memória alocada ou NULL em caso de falha.

// inicializarTerritorios():
// Preenche os dados iniciais de cada território no mapa (nome, cor do exército, número de tropas).
// Esta função modifica o mapa passado por referência (ponteiro).

// liberarMemoria():
// Libera a memória previamente alocada para o mapa usando free.

// exibirMenuPrincipal():
// Imprime na tela o menu de ações disponíveis para o jogador.

// exibirMapa():
// Mostra o estado atual de todos os territórios no mapa, formatado como uma tabela.
// Usa 'const' para garantir que a função apenas leia os dados do mapa, sem modificá-los.

// exibirMissao():
// Exibe a descrição da missão atual do jogador com base no ID da missão sorteada.

// faseDeAtaque():
// Gerencia a interface para a ação de ataque, solicitando ao jogador os territórios de origem e destino.
// Chama a função simularAtaque() para executar a lógica da batalha.

// simularAtaque():
// Executa a lógica de uma batalha entre dois territórios.
// Realiza validações, rola os dados, compara os resultados e atualiza o número de tropas.
// Se um território for conquistado, atualiza seu dono e move uma tropa.

// sortearMissao():
// Sorteia e retorna um ID de missão aleatório para o jogador.

// verificarVitoria():
// Verifica se o jogador cumpriu os requisitos de sua missão atual.
// Implementa a lógica para cada tipo de missão (destruir um exército ou conquistar um número de territórios).
// Retorna 1 (verdadeiro) se a missão foi cumprida, e 0 (falso) caso contrário.

// limparBufferEntrada():
// Função utilitária para limpar o buffer de entrada do teclado (stdin), evitando problemas com leituras consecutivas de scanf e getchar.
