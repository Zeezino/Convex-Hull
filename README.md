# Fecho Convexo (Convex Hull) - Graham's Scan

Este repositório contém a implementação de algoritmos para solucionar o problema do **Fecho Convexo (Convex Hull)**, desenvolvido como parte da disciplina de **Análise e Projeto de Algoritmos**.

O foco principal deste projeto é a implementação do algoritmo **Graham's Scan**.

## 📐 O Que é o Fecho Convexo?

Imagine um tabuleiro com vários pregos fincados em posições aleatórias. Se você soltar um elástico esticado ao redor desses pregos, o elástico irá se contrair até encostar nos pregos mais externos, formando um polígono.

Esse polígono formado pelo elástico é o **Fecho Convexo**.
Formalmente, dado um conjunto de pontos no plano, o Fecho Convexo é o menor polígono convexo que contém todos os pontos desse conjunto (seja no interior ou na borda).

## ⚙️ O Algoritmo: Graham's Scan

Para resolver este problema, utilizamos o algoritmo de **Graham**, que possui complexidade de tempo **O(n log n)**, sendo muito eficiente para grandes conjuntos de dados.

### Como funciona?
1.  **Pivô:** Identifica o ponto com a menor coordenada Y (o mais baixo).
2.  **Ordenação:** Ordena todos os outros pontos angularmente em relação ao pivô.
3.  **Iteração (Pilha):** Percorre os pontos ordenados, mantendo em uma pilha apenas os pontos que formam curvas à esquerda (sentido anti-horário). Se um ponto gera uma curva à direita (concavidade), o algoritmo remove os pontos anteriores da pilha até que a convexidade seja restaurada.

## 📂 Estrutura do Projeto

O código foi modularizado utilizando o conceito de **TAD (Tipo Abstrato de Dados)** para separar a lógica do algoritmo da interface e da aplicação principal.

### Versão em C
* `convex_hull.c`: Definição das estruturas (`Point`) e protótipos das funções.
* `convex_hull.c`: Implementação da lógica do Graham's Scan, cálculos geométricos e manipulação de vetores.
* `main.c`: Arquivo principal para execução de testes (casos fixos e aleatórios).

*(Se você manteve a versão em C, pode listar os arquivos .h e .c aqui também)*

## 🚀 Como Compilar e Rodar

Certifique-se de ter um compilador C/C++.

### Compilando (Linux/Mac/WSL)
* Compilando (em C)
```bash
gcc -o executavel *.c
```
* Executando
```bash
./executavel
