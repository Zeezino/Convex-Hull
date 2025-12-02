#include "convex-hull.h"

// Função auxiliar para imprimir o array de pontos (antes do processamento)
void printArray(point points[], int n) {
    for (int i = 0; i < n; i++) {
        printf("(%d, %d) ", points[i].x, points[i].y);
    }
    printf("\n");
}

int main() {
    // Semente para números aleatórios
    srand(time(NULL));

    printf("=== TESTE 1: Pontos Fixos (Verificação Logica) ===\n");
    
    // Pontos que formam um quadrado (0,0)-(10,10) com pontos "inúteis" no meio (5,5), (2,2)
    point inputFixos[] = {
        {0, 0}, {10, 0}, {5, 5}, {10, 10}, {0, 10}, {2, 2}, {5, 0}
    };
    
    int n1 = sizeof(inputFixos) / sizeof(inputFixos[0]);

    printf("Entrada original:\n");
    printArray(inputFixos, n1);

    // Executa o Graham Scan
    grahamScan(inputFixos, n1);

    printf("\n------------------------------------------------\n");
    printf("\n=== TESTE 2: Pontos Aleatorios (Teste de Stress) ===\n");
    
    int n2;
    printf("Digite o numero de pontos aleatorios a gerar (ex: 20): ");
    if (scanf("%d", &n2) != 1 || n2 < 3) {
        printf("Numero invalido. Usando padrao: 10 pontos.\n");
        n2 = 10;
    }

    // Alocação dinâmica para os pontos aleatórios
    point* inputAleatorio = (point*)malloc(n2 * sizeof(point));
    
    // Gera coordenadas entre 0 e 100
    for(int i = 0; i < n2; i++) {
        inputAleatorio[i] = makePoint(rand() % 50, rand() % 50);
    }

    printf("Entrada Aleatoria Gerada:\n");
    printArray(inputAleatorio, n2);

    // Executa o Graham Scan
    grahamScan(inputAleatorio, n2);

    // Libera a memória
    free(inputAleatorio);

    printf("\n\nFim da execucao.\n");
    return 0;
}