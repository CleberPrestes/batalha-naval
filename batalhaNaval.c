#include <stdio.h>
#include <stdbool.h>

// Definições de constantes para o tamanho do tabuleiro e dos navios
#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define AGUA 0
#define NAVIO 3

// --- Protótipos de Funções ---
void inicializar_tabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]);
// A função de posicionamento agora aceita mais orientações: 'H', 'V', 'DP', 'DS'
bool posicionar_navio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha_inicial, int coluna_inicial, const char *orientacao);
void exibir_tabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]);


int main() {
    // 1. Criar um Tabuleiro 10x10
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    inicializar_tabuleiro(tabuleiro);

    // --- Coordenadas e Tipos dos Quatro Navios (Tamanho fixo = 3) ---

    // Navio 1: Horizontal
    int lin1 = 1, col1 = 1;
    const char *ori1 = "H";

    // Navio 2: Vertical
    int lin2 = 7, col2 = 8;
    const char *ori2 = "V";

    // Navio 3: Diagonal Principal (Linha e Coluna aumentam)
    // Ex: (0,0), (1,1), (2,2)
    int lin3 = 3, col3 = 3;
    const char *ori3 = "DP";

    // Navio 4: Diagonal Secundária (Linha aumenta, Coluna diminui)
    // Ex: (0,9), (1,8), (2,7)
    int lin4 = 0, col4 = 6;
    const char *ori4 = "DS";


    printf("--- Tentando Posicionar 4 Navios ---\n");

    // Tenta posicionar os navios sequencialmente
    if (posicionar_navio(tabuleiro, lin1, col1, ori1)) {
        printf("1. Navio H posicionado em (%d, %d).\n", lin1, col1);
    } else {
        printf("ERRO: 1. Falha ao posicionar Navio H.\n");
    }

    if (posicionar_navio(tabuleiro, lin2, col2, ori2)) {
        printf("2. Navio V posicionado em (%d, %d).\n", lin2, col2);
    } else {
        printf("ERRO: 2. Falha ao posicionar Navio V.\n");
    }

    if (posicionar_navio(tabuleiro, lin3, col3, ori3)) {
        printf("3. Navio DP posicionado em (%d, %d).\n", lin3, col3);
    } else {
        printf("ERRO: 3. Falha ao posicionar Navio DP.\n");
    }
    
    if (posicionar_navio(tabuleiro, lin4, col4, ori4)) {
        printf("4. Navio DS posicionado em (%d, %d).\n", lin4, col4);
    } else {
        printf("ERRO: 4. Falha ao posicionar Navio DS.\n");
    }

    printf("\n");

    // 3. Exibir o Tabuleiro
    printf("--- Tabuleiro de Batalha Naval 10x10 Completo ---\n");
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
 * Tenta posicionar um navio no tabuleiro, validando limites e sobreposição,
 * incluindo orientações diagonais.
 * @param tabuleiro A matriz 10x10 do jogo.
 * @param linha_inicial Linha de início do navio (0-9).
 * @param coluna_inicial Coluna de início do navio (0-9).
 * @param orientacao "H" (Horizontal), "V" (Vertical), "DP" (Diagonal Principal), "DS" (Diagonal Secundária).
 * @return true se o navio foi posicionado, false caso contrário.
 */
bool posicionar_navio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha_inicial, int coluna_inicial, const char *orientacao) {
    int i, j; // Variáveis de controle de linha e coluna

    // 1. VALIDAÇÃO DE PONTO DE PARTIDA
    if (linha_inicial < 0 || linha_inicial >= TAMANHO_TABULEIRO ||
        coluna_inicial < 0 || coluna_inicial >= TAMANHO_TABULEIRO) {
        return false;
    }

    // --- Lógica de Posicionamento e Validação ---

    for (int k = 0; k < TAMANHO_NAVIO; k++) {
        if (orientacao[0] == 'H') {
            i = linha_inicial;
            j = coluna_inicial + k;
        } else if (orientacao[0] == 'V') {
            i = linha_inicial + k;
            j = coluna_inicial;
        } else if (orientacao[0] == 'D' && orientacao[1] == 'P') { // Diagonal Principal (i++, j++)
            i = linha_inicial + k;
            j = coluna_inicial + k;
        } else if (orientacao[0] == 'D' && orientacao[1] == 'S') { // Diagonal Secundária (i++, j--)
            i = linha_inicial + k;
            j = coluna_inicial - k;
        } else {
            return false; // Orientação inválida
        }

        // 2. VALIDAÇÃO DE LIMITES para a posição atual do segmento do navio
        if (i < 0 || i >= TAMANHO_TABULEIRO || j < 0 || j >= TAMANHO_TABULEIRO) {
            // O navio está fora dos limites em algum segmento
            return false;
        }

        // 3. VALIDAÇÃO DE SOBREPOSIÇÃO
        if (tabuleiro[i][j] == NAVIO) {
            // O navio se sobrepõe a outro navio
            return false;
        }
    }

    // Se passou por todas as validações, realiza o POSICIONAMENTO
    for (int k = 0; k < TAMANHO_NAVIO; k++) {
        if (orientacao[0] == 'H') {
            i = linha_inicial;
            j = coluna_inicial + k;
        } else if (orientacao[0] == 'V') {
            i = linha_inicial + k;
            j = coluna_inicial;
        } else if (orientacao[0] == 'D' && orientacao[1] == 'P') {
            i = linha_inicial + k;
            j = coluna_inicial + k;
        } else if (orientacao[0] == 'D' && orientacao[1] == 'S') {
            i = linha_inicial + k;
            j = coluna_inicial - k;
        }
        tabuleiro[i][j] = NAVIO;
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
