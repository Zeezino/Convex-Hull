#include <iostream>
#include <vector>
#include <cstdlib> // srand, rand
#include <ctime>   // time
#include "convex_hull.hpp"

using namespace std;

void printPoints(const vector<Point>& pts) {
    for (const auto& p : pts) {
        cout << "(" << p.x << ", " << p.y << ")\n";
    }
}

int main() {
    srand(time(0));

    cout << "=== Graham Scan em C++ ===\n\n";

    // Exemplo Fixo (Inicialização direta do C++11)
    vector<Point> pontos = {
        {0, 0}, {10, 0}, {5, 5}, {10, 10}, {0, 10}, {2, 2}, {5, 0}
    };

    cout << "Entrada (7 pontos fixos):\n";
    printPoints(pontos);

    // Chama o algoritmo
    vector<Point> resultado = grahamScan(pontos);

    cout << "\n--- Fecho Convexo (" << resultado.size() << " pontos) ---\n";
    printPoints(resultado);

    // Teste Aleatório
    cout << "\n-----------------------------\n";
    cout << "Gerando 20 pontos aleatorios...\n";
    
    vector<Point> aleatorios;
    for(int i=0; i<20; i++) {
        aleatorios.push_back({rand() % 100, rand() % 100});
    }

    vector<Point> resultadoAleatorio = grahamScan(aleatorios);

    cout << "Fecho Convexo Aleatorio:\n";
    printPoints(resultadoAleatorio);

    return 0;
}