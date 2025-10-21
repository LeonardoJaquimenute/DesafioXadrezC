#include <stdio.h>
#include <stdlib.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#define TAM 8 // Tamanho do tabuleiro

void limparTela() {
    #ifdef _WIN32
        system("cls");   // Limpa terminal Windows
    #else
        system("clear"); // Limpa terminal Unix/Linux/macOS
    #endif
}

void delay(int milliseconds) {
    #ifdef _WIN32
        Sleep(milliseconds);
    #else
        usleep(milliseconds * 1000);
    #endif
}


void imprimirTabuleiro(char tabuleiro[TAM][TAM]) {
    int i, j;
    limparTela();
    printf("\n   ");
    for (j = 0; j < TAM; j++) {
        printf("%d ", j + 1);
    }
    printf("\n");
    
    for (i = 0; i < TAM; i++) {
        printf("%d  ", i + 1);
        for (j = 0; j < TAM; j++) {
            printf("%c ", tabuleiro[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    delay(300); // 0.3 segundos de delay
}


void moverTorre(char tabuleiro[TAM][TAM], int linha, int coluna, int passo, int total) {
    if (passo > total) return;
    tabuleiro[linha][coluna + passo - 1] = 'T';
    imprimirTabuleiro(tabuleiro);
    if (passo > 1) tabuleiro[linha][coluna + passo - 2] = '.';
    moverTorre(tabuleiro, linha, coluna, passo + 1, total);
}

void moverRainha(char tabuleiro[TAM][TAM], int linha, int coluna, int passo, int total) {
    if (passo > total) return;
    tabuleiro[linha][coluna - passo + 1] = 'R';
    imprimirTabuleiro(tabuleiro);
    if (passo > 1) tabuleiro[linha][coluna - passo + 2] = '.';
    moverRainha(tabuleiro, linha, coluna, passo + 1, total);
}

void moverBispo(char tabuleiro[TAM][TAM], int linha, int coluna, int casas) {
    int v, h;
    for (v = 1; v <= casas; v++) {
        for (h = 1; h <= casas; h++) {
            int novaLinha = linha - v;
            int novaColuna = coluna + h;
            if (novaLinha >= 0 && novaColuna < TAM) {
                tabuleiro[novaLinha][novaColuna] = 'B';
                imprimirTabuleiro(tabuleiro);
                tabuleiro[novaLinha][novaColuna] = '.';
            }
        }
    }
}

void moverCavalo(char tabuleiro[TAM][TAM], int linha, int coluna, int movimentos) {
    int m;
    int movimentosL[8] = {-2, -2, -1, -1, 1, 1, 2, 2};
    int movimentosC[8] = {-1, 1, -2, 2, -2, 2, -1, 1};
    
    for (m = 0; m < movimentos; m++) {
        int posAtual = m % 8;
        int novaLinha = linha + movimentosL[posAtual];
        int novaColuna = coluna + movimentosC[posAtual];
        
        if (novaLinha >= 0 && novaLinha < TAM && novaColuna >= 0 && novaColuna < TAM) {
            tabuleiro[novaLinha][novaColuna] = 'C';
            imprimirTabuleiro(tabuleiro);
            tabuleiro[novaLinha][novaColuna] = '.';
            linha = novaLinha;
            coluna = novaColuna;
        }
    }
}

int main() {
    char tabuleiro[TAM][TAM];
    int i, j;

    // Inicializa o tabuleiro
    for (i = 0; i < TAM; i++)
        for (j = 0; j < TAM; j++)
            tabuleiro[i][j] = '.';

    printf("=== Movimento da Torre ===\n");
    moverTorre(tabuleiro, 7, 0, 1, 5);
    delay(500);

    // Limpa o tabuleiro
    for (i = 0; i < TAM; i++)
        for (j = 0; j < TAM; j++)
            tabuleiro[i][j] = '.';

    printf("=== Movimento do Bispo ===\n");
    moverBispo(tabuleiro, 7, 2, 5);
    delay(500);

    // Limpa o tabuleiro
    for (i = 0; i < TAM; i++)
        for (j = 0; j < TAM; j++)
            tabuleiro[i][j] = '.';

    printf("=== Movimento da Rainha ===\n");
    moverRainha(tabuleiro, 7, 7, 1, 8);
    delay(500);

    // Limpa o tabuleiro
    for (i = 0; i < TAM; i++)
        for (j = 0; j < TAM; j++)
            tabuleiro[i][j] = '.';

    printf("=== Movimento do Cavalo ===\n");
    moverCavalo(tabuleiro, 6, 1, 8);
    delay(500);

    printf("=== Fim da Simulação ===\n");

    return 0;
}
