#include <stdio.h>
#include <stdbool.h>

// Definições de constantes para o tamanho do tabuleiro e dos navios
#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define AGUA 0
#define NAVIO 3

// --- Protótipos de Funções ---
void inicializar_tabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]);
bool posicionar_navio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha_inicial, int coluna_inicial, char orientacao);
void exibir_tabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]);


int main() {
    // 1. Represente o Tabuleiro: Array bidimensional 10x10
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];

    // Inicializa todas as posições com 0 (ÁGUA)
    inicializar_tabuleiro(tabuleiro);

    // --- Coordenadas Iniciais dos Navios (Definidas no Código) ---
    // Navio Horizontal: Começa na Linha 1, Coluna 1
    int linha_h = 1;
    int coluna_h = 1;

    // Navio Vertical: Começa na Linha 5, Coluna 6
    int linha_v = 5;
    int coluna_v = 6;


    // 2. Posicione os Navios:

    printf("--- Posicionamento dos Navios ---\n");

    // Tenta posicionar o Navio Horizontal
    if (posicionar_navio(tabuleiro, linha_h, coluna_h, 'H')) {
        printf("Navio Horizontal (Tamanho %d) posicionado em (%d, %d).\n", TAMANHO_NAVIO, linha_h, coluna_h);
    } else {
        printf("ERRO: Não foi possível posicionar o Navio Horizontal em (%d, %d). Fora dos limites ou sobreposição.\n", linha_h, coluna_h);
    }

    // Tenta posicionar o Navio Vertical
    if (posicionar_navio(tabuleiro, linha_v, coluna_v, 'V')) {
        printf("Navio Vertical (Tamanho %d) posicionado em (%d, %d).\n", TAMANHO_NAVIO, linha_v, coluna_v);
    } else {
        printf("ERRO: Não foi possível posicionar o Navio Vertical em (%d, %d). Fora dos limites ou sobreposição.\n", linha_v, coluna_v);
    }

    printf("\n");

    // 3. Exiba o Tabuleiro
    printf("--- Tabuleiro de Batalha Naval 10x10 ---\n");
    exibir_tabuleiro(tabuleiro);

    return 0;
}

// --- Implementação das Funções ---

/**
 * Inicializa todas as posições do tabuleiro com o valor AGUA (0).
 */
void inicializar_tabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

/**
 * Tenta posicionar um navio no tabuleiro, validando limites e sobreposição.
 * @param tabuleiro A matriz 10x10 do jogo.
 * @param linha_inicial Linha de início do navio (0-9).
 * @param coluna_inicial Coluna de início do navio (0-9).
 * @param orientacao 'H' para horizontal, 'V' para vertical.
 * @return true se o navio foi posicionado com sucesso, false caso contrário.
 */
bool posicionar_navio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha_inicial, int coluna_inicial, char orientacao) {
    // 1. VALIDAÇÃO DE LIMITES
    if (linha_inicial < 0 || linha_inicial >= TAMANHO_TABULEIRO ||
        coluna_inicial < 0 || coluna_inicial >= TAMANHO_TABULEIRO) {
        // Ponto de partida fora dos limites
        return false;
    }

    if (orientacao == 'H' || orientacao == 'h') {
        // Validação Horizontal: O navio de tamanho 3 deve caber.
        if (coluna_inicial + TAMANHO_NAVIO > TAMANHO_TABULEIRO) {
            return false; // Navio excede o limite da coluna
        }

        // 2. VALIDAÇÃO DE SOBREPOSIÇÃO (simplificada)
        for (int j = 0; j < TAMANHO_NAVIO; j++) {
            if (tabuleiro[linha_inicial][coluna_inicial + j] == NAVIO) {
                return false; // Encontrou outro navio (sobreposição)
            }
        }

        // 3. POSICIONAMENTO
        for (int j = 0; j < TAMANHO_NAVIO; j++) {
            tabuleiro[linha_inicial][coluna_inicial + j] = NAVIO;
        }

    } else if (orientacao == 'V' || orientacao == 'v') {
        // Validação Vertical: O navio de tamanho 3 deve caber.
        if (linha_inicial + TAMANHO_NAVIO > TAMANHO_TABULEIRO) {
            return false; // Navio excede o limite da linha
        }

        // 2. VALIDAÇÃO DE SOBREPOSIÇÃO (simplificada)
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            if (tabuleiro[linha_inicial + i][coluna_inicial] == NAVIO) {
                return false; // Encontrou outro navio (sobreposição)
            }
        }

        // 3. POSICIONAMENTO
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            tabuleiro[linha_inicial + i][coluna_inicial] = NAVIO;
        }
    } else {
        return false; // Orientação inválida
    }

    return true; // Navio posicionado com sucesso
}

/**
 * Exibe o tabuleiro 10x10 no console com um formato claro.
 */
void exibir_tabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    // Imprime o cabeçalho das colunas (0 a 9)
    printf("  "); // Espaço para a coluna de índice da linha
    for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
        printf(" %d", j);
    }
    printf("\n");

    // Imprime uma linha separadora
    printf("  ");
    for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
        printf("--");
    }
    printf("-\n");


    // Loops aninhados para percorrer e imprimir a matriz
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        // Imprime o índice da linha
        printf("%d|", i);

        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            // Imprime o valor da posição, usando um espaço como separador
            // 0 = Água, 3 = Navio
            printf(" %d", tabuleiro[i][j]);
        }
        printf(" |\n"); // Nova linha após o fim da linha do tabuleiro
    }

    // Imprime o rodapé
    printf("  ");
    for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
        printf("--");
    }
    printf("-\n");
    printf("\nLegenda: 0 = Água, 3 = Navio\n");
}
