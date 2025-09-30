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

// --- Constantes Globais ---
// Definem valores fixos para o número de territórios, missões e tamanho máximo de strings, facilitando a manutenção.

// --- Estrutura de Dados ---
// Define a estrutura para um território, contendo seu nome, a cor do exército que o domina e o número de tropas.

// --- Protótipos das Funções ---
// Declarações antecipadas de todas as funções que serão usadas no programa, organizadas por categoria.
// Funções de setup e gerenciamento de memória:
// Funções de interface com o usuário:
// Funções de lógica principal do jogo:
// Função utilitária:

// --- Função Principal (main) ---
// Função principal que orquestra o fluxo do jogo, chamando as outras funções em ordem.
int main() {
    // 1. Configuração Inicial (Setup):
    // - Define o locale para português.
    // - Inicializa a semente para geração de números aleatórios com base no tempo atual.
    // - Aloca a memória para o mapa do mundo e verifica se a alocação foi bem-sucedida.
    // - Preenche os territórios com seus dados iniciais (tropas, donos, etc.).
    // - Define a cor do jogador e sorteia sua missão secreta.

    // 2. Laço Principal do Jogo (Game Loop):
    // - Roda em um loop 'do-while' que continua até o jogador sair (opção 0) ou vencer.
    // - A cada iteração, exibe o mapa, a missão e o menu de ações.
    // - Lê a escolha do jogador e usa um 'switch' para chamar a função apropriada:
    //   - Opção 1: Inicia a fase de ataque.
    //   - Opção 2: Verifica se a condição de vitória foi alcançada e informa o jogador.
    //   - Opção 0: Encerra o jogo.
    // - Pausa a execução para que o jogador possa ler os resultados antes da próxima rodada.

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

// ============================================================================
//
// >> A partir daqui começa a implementação da PARTE 1 - Nível Novato
//
// ============================================================================

// ----------------------------------------------
// Projeto: Nível Novato: Cadastro Inicial dos Territórios
// Autor: Fabrício Vieira de Souza
// Data: 30/09/2025
// Objetivo:
// Criar uma struct chamada Territorio.
// Usar um vetor estático de 5 elementos para armazenar os territórios.
// Cadastrar os dados de cada território: Nome, Cor do Exército, e Número de Tropas.
// Exibir o estado atual do mapa.
// ----------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//--constantes globais
#define MAX_TERRITORIOS 5
#define TAM_STRING 30

//--define estrutura struct
struct Territorio
{
    char nome[TAM_STRING];
    char cor[TAM_STRING];
    int tropas;
};

//--limpar buffer de entrada
void LimparBufferEntrada()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

int main()
{
    struct Territorio territorios[MAX_TERRITORIOS];
    int totalTerritorios = 0;
    int opcao;

    do
    {
        printf("=============================================\n");
        printf("      SISTEMA DE CADASTRO DE TERRITORIOS\n");
        printf("=============================================\n");
        printf("1 - Cadastrar Novo Territorio\n");
        printf("2 - Listar Todos os Territorios\n");
        printf("0 - Sair\n");
        printf("---------------------------------------------\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        LimparBufferEntrada();

        switch (opcao)
        {
        case 1:
            printf("---Cadastro de Novo Territorio---\n");

            if (totalTerritorios < MAX_TERRITORIOS)
            {
                printf("Digite o Nome do Territorio: ");
                fgets(territorios[totalTerritorios].nome, TAM_STRING, stdin);

                printf("Digite a Cor do Exercito: ");
                fgets(territorios[totalTerritorios].cor, TAM_STRING, stdin);

                printf("Digite a quantidade de Tropas: ");
                scanf("%d", &territorios[totalTerritorios].tropas);
                LimparBufferEntrada();

                // Removendo \n das strings
                territorios[totalTerritorios].nome[strcspn(territorios[totalTerritorios].nome, "\n")] = '\0';
                territorios[totalTerritorios].cor[strcspn(territorios[totalTerritorios].cor, "\n")] = '\0';

                totalTerritorios++;
                printf("\nTerritorio Cadastrado com Sucesso!\n");
            }
            else
            {
                printf("\nLimite de territorios atingido! Não é possível cadastrar mais.\n");
            }

            printf("\nPressione ENTER para continuar...");
            getchar();
            break;

        case 2:
            printf("---Lista de Territorios Cadastrados---\n");

            if (totalTerritorios == 0)
            {
                printf("Nenhum territorio cadastrado.\n");
            }
            else
            {
                for (int i = 0; i < totalTerritorios; i++)
                {
                    printf("--------------------------------------\n");
                    printf("TERRITORIO %d\n", i + 1);
                    printf("Nome: %s\n", territorios[i].nome);
                    printf("Cor do Exercito: %s\n", territorios[i].cor);
                    printf("Tropas: %d\n", territorios[i].tropas);
                }
                printf("--------------------------------------\n");
            }

            printf("\nPressione ENTER para continuar...");
            getchar();
            break;

        case 0:
            printf("\nSaindo do sistema...\n");
            break;

        default:
            printf("\nOpção invalida! Tente novamente.\n");
            printf("\nPressione ENTER para continuar...");
            getchar();
            break;
        }
    } while (opcao != 0);

    return 0;
}
