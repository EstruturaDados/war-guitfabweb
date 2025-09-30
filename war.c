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
//int main() {
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

//    return 0;
//}

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
// >> A partir daqui começa a implementação.
//
// ============================================================================

// ============================================================================
// PROJETO WAR - NÍVEL AVENTUREIRO
// Autor: Fabrício Vieira de Souza
//// Data: 30/09/2025
// Objetivo: Cadastro de territórios + Fase de Ataque com alocação dinâmica,
// utilização de ponteiros e dados aleatórios.
// ============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAM_STRING 30

// --- Estrutura de Dados ---
struct Territorio {
    char nome[TAM_STRING];
    char cor[TAM_STRING];
    int tropas;
};

// --- Funções ---
void limparBufferEntrada();
struct Territorio* alocarTerritorios(int n);
void liberarMemoria(struct Territorio* mapa);
void cadastrarTerritorios(struct Territorio* mapa, int n);
void exibirTerritorios(const struct Territorio* mapa, int n);
void atacar(struct Territorio* atacante, struct Territorio* defensor);

// --- Função Principal ---
int main() {
    srand(time(NULL)); // inicializa aleatoriedade

    int totalTerritorios;
    printf("Digite o número de territórios a cadastrar: ");
    scanf("%d", &totalTerritorios);
    limparBufferEntrada();

    if (totalTerritorios <= 0) {
        printf("Número inválido!\n");
        return 1;
    }

    struct Territorio* territorios = alocarTerritorios(totalTerritorios);
    if (!territorios) return 1;

    int opcao;
    do {
        printf("\n=== WAR - NÍVEL AVENTUREIRO ===\n");
        printf("1 - Cadastrar Territórios\n");
        printf("2 - Listar Territórios\n");
        printf("3 - Atacar\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        limparBufferEntrada();

        switch (opcao) {
            case 1:
                cadastrarTerritorios(territorios, totalTerritorios);
                break;
            case 2:
                exibirTerritorios(territorios, totalTerritorios);
                break;
            case 3: {
                int at, def;
                exibirTerritorios(territorios, totalTerritorios);
                printf("Escolha o território atacante (1 a %d): ", totalTerritorios);
                scanf("%d", &at);
                printf("Escolha o território defensor (1 a %d): ", totalTerritorios);
                scanf("%d", &def);
                limparBufferEntrada();

                if (at < 1 || at > totalTerritorios || def < 1 || def > totalTerritorios || at == def) {
                    printf("Escolha inválida!\n");
                    break;
                }

                atacar(&territorios[at-1], &territorios[def-1]);
                break;
            }
            case 0:
                printf("Saindo do jogo...\n");
                break;
            default:
                printf("Opção inválida!\n");
                break;
        }
    } while (opcao != 0);

    liberarMemoria(territorios);
    return 0;
}

// --- Implementação das Funções ---

void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Aloca memória dinamicamente para n territórios
struct Territorio* alocarTerritorios(int n) {
    struct Territorio* mapa = (struct Territorio*) calloc(n, sizeof(struct Territorio));
    if (!mapa) {
        printf("Erro ao alocar memória!\n");
        return NULL;
    }
    return mapa;
}

// Libera a memória alocada
void liberarMemoria(struct Territorio* mapa) {
    free(mapa);
}

// Cadastro dos territórios
void cadastrarTerritorios(struct Territorio* mapa, int n) {
    for (int i = 0; i < n; i++) {
        printf("\nTerritório %d\n", i+1);
        printf("Nome: ");
        fgets(mapa[i].nome, TAM_STRING, stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0';

        printf("Cor do Exército: ");
        fgets(mapa[i].cor, TAM_STRING, stdin);
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = '\0';

        printf("Número de Tropas: ");
        scanf("%d", &mapa[i].tropas);
        limparBufferEntrada();
    }
}

// Exibe todos os territórios
void exibirTerritorios(const struct Territorio* mapa, int n) {
    printf("\n--- Territórios ---\n");
    for (int i = 0; i < n; i++) {
        printf("Território %d: %s | Exército: %s | Tropas: %d\n",
               i+1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

// Simula um ataque entre dois territórios
void atacar(struct Territorio* atacante, struct Territorio* defensor) {
    printf("\nAtaque: %s (%d tropas) -> %s (%d tropas)\n",
           atacante->nome, atacante->tropas, defensor->nome, defensor->tropas);

    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("Dado do atacante: %d\n", dadoAtacante);
    printf("Dado do defensor: %d\n", dadoDefensor);

    if (dadoAtacante >= dadoDefensor) { // atacante vence ou empate favorece atacante
        defensor->tropas -= 1;
        printf("%s perde 1 tropa!\n", defensor->nome);
        if (defensor->tropas <= 0) { // conquista
            defensor->tropas = atacante->tropas / 2;
            strcpy(defensor->cor, atacante->cor);
            printf("%s foi conquistado! Cor do exército agora: %s\n", defensor->nome, defensor->cor);
        }
    } else {
        atacante->tropas -= 1;
        printf("%s perde 1 tropa!\n", atacante->nome);
    }
}
