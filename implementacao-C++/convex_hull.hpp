#ifndef CONVEX_HULL_HPP
#define CONVEX_HULL_HPP

#include <vector>
#include <iostream>

// Estrutura simples para Ponto
struct Point {
    int x, y;

    // Sobrecarga do operador == para facilitar comparações
    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
};

// Funções Geométricas Auxiliares
int distSq(Point p1, Point p2);
int orientation(Point p, Point q, Point r);

// O Algoritmo Principal
// Recebe um vetor de pontos e retorna um novo vetor contendo apenas o Fecho Convexo
std::vector<Point> grahamScan(std::vector<Point>& points);

#endif