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

/* ============================================================================
   PROJETO WAR - NÍVEL MESTRE
   Autor: Fabrício Vieira de Souza
   Matricula:202501549322
   Data: 01/10/2025
   Objetivo: manter o N2 (cadastro manual, listagem, ataque) e adicionar
             MISSÕES (aleatórias, alocadas dinamicamente), verificação,
             modularização, uso de ponteiros e gerenciamento de memória.
   ========================================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAM_STRING 30
#define MAX_MISSOES 2

// --- Estrutura de dados ---
typedef struct
{
    char nome[TAM_STRING];
    char cor[TAM_STRING];
    int tropas;
} Territorio;

// --- Protótipos ---
// utilitários
void limparBufferEntrada(void);
int lerInt(const char *prompt);
void lerString(const char *prompt, char *buf, size_t size);

/* memória / setup */
Territorio *alocarTerritorios(int n);
void liberarMemoria(Territorio *mapa);

// cadastro / listagem
void cadastrarTerritorio(Territorio *mapa, int pos);
void listarTerritorios(const Territorio *mapa, int total);

// combate
void atacar(Territorio *atacante, Territorio *defensor);

// missões
char *sortearMissao(char *missoes[], int totalMissoes);
int verificarMissao(const Territorio *mapa, int total, const char *missao, const char *corJogador);

//--- main: orquestra o jogo ---
int main(void)
{
    srand((unsigned)time(NULL));

    // 1) inicialização: capacidade dinâmica
    int capacidade = lerInt("Digite a capacidade maxima de territorios: ");
    if (capacidade <= 0)
    {
        printf("Capacidade invalida. Encerrando.\n");
        return 1;
    }

    Territorio *mapa = alocarTerritorios(capacidade);
    if (!mapa)
        return 1;

    // 2) Sorteio de missão (armazenada dinamicamente) e cor do jogador
    char *missoes[MAX_MISSOES] = {
        "Conquistar 3 territorios",
        "Destruir todo o exercito Verde"};
    char *missaoAtual = sortearMissao(missoes, MAX_MISSOES);

    char corJogador[TAM_STRING] = {0};
    printf("\nMissao sorteada (sera exibida uma vez):\n");
    printf("  -> %s\n", missaoAtual);
    lerString("Escolha a cor do seu exercito (ex: Azul, Verde, Vermelho): ", corJogador, TAM_STRING);
    printf("Missao atribuida: %s | Sua cor: %s\n\n", missaoAtual, corJogador);

    // 3) Loop principal (mantendo N2: cadastro manual etc.)
    int total = 0;
    int opcao;
    do
    {
        printf("\n=== WAR - NIVEL MESTRE  ===\n");
        printf("1 - Cadastrar novo territorio\n");
        printf("2 - Listar territorios cadastrados\n");
        printf("3 - Atacar (simular batalha)\n");
        printf("4 - Verificar Missao\n");
        printf("0 - Sair\n");
        opcao = lerInt("Escolha uma opcao: ");

        switch (opcao)
        {
        case 1:
            if (total < capacidade)
            {
                cadastrarTerritorio(mapa, total);
                total++;
            }
            else
            {
                printf("Capacidade atingida. Nao e possivel cadastrar mais territorios.\n");
            }
            break;

        case 2:
            listarTerritorios(mapa, total);
            break;

        case 3:
            if (total < 2)
            {
                printf("Sao necessarios pelo menos 2 territórios cadastrados para atacar.\n");
                break;
            }
            listarTerritorios(mapa, total);
            {
                int a = lerInt("Numero do territorio ATACANTE (1..): ");
                int d = lerInt("Numero do territorio DEFENSOR (1..): ");
                a--;
                d--;
                if (a < 0 || a >= total || d < 0 || d >= total)
                {
                    printf("Indice invalido. Operacao abortada.\n");
                    break;
                }
                if (a == d)
                {
                    printf("Atacante e defensor nao podem ser o mesmo territorio.\n");
                    break;
                }
                if (strcmp(mapa[a].cor, mapa[d].cor) == 0)
                {
                    printf("Nao e permitido atacar territorio do mesmo exercito (mesma cor).\n");
                    break;
                }
                if (mapa[a].tropas <= 0)
                {
                    printf("Territorio atacante nao possui tropas suficientes para atacar.\n");
                    break;
                }
                atacar(&mapa[a], &mapa[d]);

                // verificação automática opcional da missão após o ataque
                if (verificarMissao(mapa, total, missaoAtual, corJogador))
                {
                    printf("\n*** MISSAO CUMPRIDA! Voce venceu! ***\n");
                    opcao = 0; // finaliza o jogo
                }
            }
            break;

        case 4:
            if (verificarMissao(mapa, total, missaoAtual, corJogador))
            {
                printf("\n*** PARABENS: Missao cumprida! ***\n");
                opcao = 0; // força saída
            }
            else
            {
                printf("\nMissao ainda nao concluida. Continue jogando.\n");
            }
            break;

        case 0:
            printf("Saindo... liberando recursos.\n");
            break;

        default:
            printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 0);

    // 4) Cleanup: liberar toda memória alocada
    free(missaoAtual);
    liberarMemoria(mapa);

    return 0;
}

// Implementação das funções

void limparBufferEntrada(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    { /* descarta */
    }
}

int lerInt(const char *prompt)
{
    int v;
    int r;
    while (1)
    {
        printf("%s", prompt);
        r = scanf("%d", &v);
        limparBufferEntrada();
        if (r == 1)
            return v;
        printf("Entrada invalida. Digite um numero inteiro.\n");
    }
}

void lerString(const char *prompt, char *buf, size_t size)
{
    printf("%s", prompt);
    if (fgets(buf, (int)size, stdin) == NULL)
    {
        buf[0] = '\0';
        return;
    }
    buf[strcspn(buf, "\n")] = '\0';
}

// Aloca dinamicamente o vetor de territórios
Territorio *alocarTerritorios(int n)
{
    Territorio *m = (Territorio *)calloc((size_t)n, sizeof(Territorio));
    if (!m)
    {
        fprintf(stderr, "Erro: falha ao alocar memoria para %d territorios.\n", n);
        return NULL;
    }
    return m;
}

// Libera memória do mapa
void liberarMemoria(Territorio *mapa)
{
    free(mapa);
}

// Cadastro manual de um território
void cadastrarTerritorio(Territorio *mapa, int pos)
{
    printf("\n--- Cadastro Territorio %d ---\n", pos + 1);
    lerString("Nome: ", mapa[pos].nome, TAM_STRING);
    lerString("Cor do Exercito: ", mapa[pos].cor, TAM_STRING);
    mapa[pos].tropas = lerInt("Numero de Tropas: ");
    if (mapa[pos].tropas < 0)
        mapa[pos].tropas = 0;
    printf("Registrado: %s | %s | Tropas: %d\n", mapa[pos].nome, mapa[pos].cor, mapa[pos].tropas);
}

// Listagem
void listarTerritorios(const Territorio *mapa, int total)
{
    if (total == 0)
    {
        printf("Nenhum territorio cadastrado.\n");
        return;
    }
    printf("\n--- Territorios Cadastrados ---\n");
    for (int i = 0; i < total; ++i)
    {
        printf("[%d] %s | Cor: %s | Tropas: %d\n",
               i + 1,
               mapa[i].nome[0] ? mapa[i].nome : "<sem nome>",
               mapa[i].cor[0] ? mapa[i].cor : "<sem cor>",
               mapa[i].tropas);
    }
}

// Regras de batalha (usando ponteiros)
// Empate favorece atacante. Se defensor chega a 0 tropas -> conquista:
//   transfere metade das tropas do atacante (ao menos 1) e altera a cor do defensor.

void atacar(Territorio *atacante, Territorio *defensor)
{
    printf("\n>>> BATALHA: %s (%d) -> %s (%d)\n",
           atacante->nome, atacante->tropas, defensor->nome, defensor->tropas);

    int dadoA = rand() % 6 + 1;
    int dadoD = rand() % 6 + 1;

    printf("Rolagem: atacante=%d | defensor=%d\n", dadoA, dadoD);

    if (dadoA >= dadoD)
    { /* atacante vence (empate favorece atacante) */
        defensor->tropas -= 1;
        printf("Atacante vence: %s perde 1 tropa (agora %d).\n", defensor->nome, defensor->tropas);

        if (defensor->tropas <= 0)
        {
            int transf = atacante->tropas / 2;
            if (transf < 1)
                transf = 1;
            defensor->tropas = transf;
            strcpy(defensor->cor, atacante->cor);
            atacante->tropas -= transf;
            if (atacante->tropas < 0)
                atacante->tropas = 0;
            printf("%s foi conquistado! Nova cor: %s | Tropas transferidas: %d\n",
                   defensor->nome, defensor->cor, transf);
        }
    }
    else
    { // defensor vence
        atacante->tropas -= 1;
        if (atacante->tropas < 0)
            atacante->tropas = 0;
        printf("Defensor resistiu: %s perde 1 tropa (agora %d).\n", atacante->nome, atacante->tropas);
    }
}

// Sorteia uma missão e retorna uma string alocada pelo chamador (malloc).
//   O chamador deve dar free() quando não precisar mais.

char *sortearMissao(char *missoes[], int totalMissoes)
{
    int idx = rand() % totalMissoes;
    char *missao = (char *)malloc(TAM_STRING * sizeof(char));
    if (!missao)
    {
        fprintf(stderr, "Erro ao alocar memoria para missao.\n");
        exit(1);
    }
    strncpy(missao, missoes[idx], TAM_STRING - 1);
    missao[TAM_STRING - 1] = '\0';
    return missao;
}

/* Verifica se a missão foi cumprida.
   - "Conquistar 3 territórios": conta quantos territórios têm cor == corJogador.
   - "Destruir todo o exército Verde": retorna true se não existir território com cor "Verde" e tropas>0.
*/

int verificarMissao(const Territorio *mapa, int total, const char *missao, const char *corJogador)
{
    if (strcmp(missao, "Conquistar 3 territorios") == 0)
    {
        int cont = 0;
        for (int i = 0; i < total; ++i)
        {
            if (strcmp(mapa[i].cor, corJogador) == 0 && mapa[i].tropas > 0)
                cont++;
        }
        return cont >= 3;
    }
    else if (strcmp(missao, "Destruir todo o exercito Verde") == 0)
    {
        for (int i = 0; i < total; ++i)
            if (strcmp(mapa[i].cor, "Verde") == 0 && mapa[i].tropas > 0)
                return 0;
        return 1;
    }
    return 0;
}
