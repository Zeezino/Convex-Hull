#include "convex-hull.h"
#include <math.h>

// Variável global necessária para o qsort ter acesso ao ponto pivô.
// Em C, o qsort não aceita contexto adicional, então usamos isso.
point p0; 

// --- Implementação das Funções da Pilha (TAD) ---

// Inicializa a pilha com NULL
void initStack(CH_stack* stack) {
    *stack = NULL;
}

// Verifica se está vazia
int isEmpty(CH_stack stack) {
    return stack == NULL;
}

// Empilha um novo ponto
void push(CH_stack* stack, point p) {
    node* novoNo = (node*)malloc(sizeof(node));
    if (novoNo == NULL) {
        fprintf(stderr, "Erro de alocação de memória!\n");
        exit(1);
    }
    novoNo->p = p;
    novoNo->next = *stack; // O próximo do novo é o antigo topo
    *stack = novoNo;       // O topo passa a ser o novo nó
}

// Desempilha e retorna o ponto
point pop(CH_stack* stack) {
    if (isEmpty(*stack)) {
        fprintf(stderr, "Erro: Tentativa de pop em pilha vazia.\n");
        exit(1);
    }
    node* temp = *stack;
    point p = temp->p;
    *stack = temp->next; // Topo desce um nível
    free(temp);          // Libera memória
    return p;
}

// Espia o topo
point top(CH_stack stack) {
    if (isEmpty(stack)) {
        fprintf(stderr, "Erro: Pilha vazia.\n");
        exit(1);
    }
    return stack->p;
}

// Espia o elemento abaixo do topo (Next-to-Top)
point nextTop(CH_stack stack) {
    if (isEmpty(stack) || stack->next == NULL) {
        fprintf(stderr, "Erro: Pilha não tem elementos suficientes para nextTop.\n");
        exit(1);
    }
    return stack->next->p;
}

// --- Funções Geométricas ---

point makePoint(int x, int y) {
    point p;
    p.x = x;
    p.y = y;
    return p;
}

void swap(point* p1, point* p2) {
    point temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

// Distância euclidiana ao quadrado (evita raiz quadrada)
int distSq(point p1, point p2) {
    return (p1.x - p2.x) * (p1.x - p2.x) + 
           (p1.y - p2.y) * (p1.y - p2.y);
}

/**
 * Retorna a orientação do trio (p, q, r).
 * 0 -> Colineares
 * 1 -> Horário (Clockwise)
 * 2 -> Anti-horário (Counter-Clockwise - Left Turn)
 * Fórmula baseada no produto vetorial.
 */
int orientation(point p, point q, point r) {
    int val = (q.y - p.y) * (r.x - q.x) - 
              (q.x - p.x) * (r.y - q.y);

    if (val == 0) return 0;  // Colinear
    return (val > 0) ? 1 : 2; // Horário ou Anti-horário
}

// Função de comparação para o qsort
int compare(const void* vp1, const void* vp2) {
    point* p1 = (point*)vp1;
    point* p2 = (point*)vp2;

    // Obtém a orientação em relação ao pivô p0
    int o = orientation(p0, *p1, *p2);

    if (o == 0) {
        // Se forem colineares, o mais distante deve vir depois
        return (distSq(p0, *p2) >= distSq(p0, *p1)) ? -1 : 1;
    }

    // Se o = 2 (Anti-horário), p2 está à esquerda de p1 -> p1 vem antes (-1)
    return (o == 2) ? -1 : 1;
}

// --- Algoritmo de Graham Scan ---

void grahamScan(point points[], int n) {
    // 1. Encontrar o ponto mais baixo (e mais à esquerda em caso de empate)
    int ymin = points[0].y, min = 0;
    for (int i = 1; i < n; i++) {
        int y = points[i].y;
        // Escolhe o menor Y ou, se Y igual, o menor X
        if ((y < ymin) || (ymin == y && points[i].x < points[min].x)) {
            ymin = points[i].y;
            min = i;
        }
    }

    // 2. Coloca o ponto pivô na posição 0
    swap(&points[0], &points[min]);
    
    // Define a variável global p0 para uso no qsort
    p0 = points[0];

    // 3. Ordena os pontos restantes (do índice 1 ao n-1) baseando-se no ângulo polar
    qsort(&points[1], n - 1, sizeof(point), compare);

    // *Tratamento de Colineares (Opcional mas recomendado)*:
    // Se dois ou mais pontos formam o mesmo ângulo com p0, qsort coloca o mais longe por último.
    // O ideal seria remover os pontos intermediários colineares aqui, mas o loop principal
    // do Graham geralmente cuida disso se a lógica estiver sólida.
    
    // Se houver menos de 3 pontos, o fecho convexo é impossível
    if (n < 3) return;

    // 4. Inicializa a pilha e coloca os 3 primeiros pontos
    CH_stack stack;
    initStack(&stack);
    
    push(&stack, points[0]);
    push(&stack, points[1]);
    push(&stack, points[2]);

    // 5. Itera sobre o restante dos pontos
    for (int i = 3; i < n; i++) {
        // Enquanto o ângulo formado por (nextTop, top, points[i]) NÃO for uma curva à esquerda (2),
        // significa que o ponto no topo está "entrando" no polígono, então removemos ele.
        while (!isEmpty(stack) && stack->next != NULL && 
               orientation(nextTop(stack), top(stack), points[i]) != 2) {
            pop(&stack);
        }
        push(&stack, points[i]);
    }

    // 6. Imprimir o resultado (pode ser movido para a main se preferir)
    printf("\n--- Pontos no Fecho Convexo ---\n");
    // Como é uma pilha, a ordem de impressão será inversa se apenas percorrermos.
    // Para imprimir bonitinho, podemos apenas iterar o encadeamento:
    node* current = stack;
    while (current != NULL) {
        printf("(%d, %d)\n", current->p.x, current->p.y);
        current = current->next;
    }
}