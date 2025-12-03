#include "convex-hull.h"
#include <time.h>

int main() {
    srand(time(NULL));

    // Defina os tamanhos que você quer testar para o gráfico
    int testes[] = {10000, 50000, 100000, 200000, 500000, 1000000};
    int num_testes = 6;

    printf("=== INICIANDO BATERIA DE TESTES (Stress Test) ===\n");
    printf("N        | Tempo (ms)\n");
    printf("---------------------\n");

    for (int t = 0; t < num_testes; t++) {
        int n = testes[t];

        // Aloca memória
        point* inputAleatorio = (point*)malloc(n * sizeof(point));
        
        // CORREÇÃO 1: Grid maior (0 a 10000) para evitar colisão de pontos
        // CORREÇÃO 2: Sem printf dos pontos aqui!
        for(int i = 0; i < n; i++) {
            inputAleatorio[i] = makePoint(rand() % 10000, rand() % 10000);
        }

        // Medição de tempo
        clock_t inicio = clock();
        
        grahamScan(inputAleatorio, n);
        
        clock_t fim = clock();

        // Cálculo
        double tempo_ms = ((double)(fim - inicio) / CLOCKS_PER_SEC) * 1000.0;
        
        printf("%-8d | %.2f ms\n", n, tempo_ms);

        free(inputAleatorio);
    }

    return 0;
}

/*
#include "convex-hull.h"
#include <time.h>

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
        inputAleatorio[i] = makePoint(rand() % 10000, rand() % 10000);
    }

    printf("Entrada Aleatoria Gerada:\n");
    printArray(inputAleatorio, n2);

    clock_t inicio = clock();
    // Executa o Graham Scan
    grahamScan(inputAleatorio, n2);
    clock_t fim = clock();

    double tempo_ms = ((double)(fim - inicio) / CLOCKS_PER_SEC) * 1000.0;
    
    printf("N = %d, Tempo = %.2f ms\n", n2, tempo_ms);

    // Libera a memória
    free(inputAleatorio);

    printf("\n\nFim da execucao.\n");
    return 0;
}
*/