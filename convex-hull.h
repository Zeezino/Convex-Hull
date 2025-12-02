#ifndef CONVEX_HULL_H
#define CONVEX_HULL_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Definição do Ponto
typedef struct {
    int x;
    int y;
} point;

// Definição do Nó da Pilha (Corrigido para permitir autorreferência)
typedef struct Node {
    point p;
    struct Node* next;
} node;

// O tipo CH_stack é um ponteiro para o topo da pilha
typedef node* CH_stack;

// --- Funções de Manipulação da Pilha (TAD) ---

// Inicializa a pilha
void initStack(CH_stack* stack);

// Empilha um ponto (recebe o ponto, não o nó)
void push(CH_stack* stack, point p);

// Desempilha e retorna o ponto removido (útil para lógica)
point pop(CH_stack* stack);

// Retorna o ponto no topo sem remover
point top(CH_stack stack);

// Retorna o elemento logo abaixo do topo (essencial para Graham Scan)
point nextTop(CH_stack stack);

// Verifica se a pilha está vazia
int isEmpty(CH_stack stack);


// --- Funções Geométricas e Auxiliares ---

// Cria um ponto
point makePoint(int x, int y);

// Troca dois pontos (útil para ordenação)
void swap(point* p1, point* p2);

// Distância ao quadrado entre p1 e p2 (evita raiz quadrada, melhor performance)
int distSq(point p1, point p2);

/**
 * Encontra a orientação do trio ordenado (p, q, r).
 * Retorna:
 * 0 -> Colineares
 * 1 -> Horário (Right turn)
 * 2 -> Anti-horário (Left turn) - O que queremos!
 */
int orientation(point p, point q, point r);

// Função de comparação para o qsort (necessária para ordenar por ângulo polar)
int compare(const void* vp1, const void* vp2);

// O Algoritmo Principal
void grahamScan(point points[], int n);

#endif