#include "convex_hull.hpp"
#include <algorithm> // Para std::sort e std::swap
#include <vector>

// Distância ao quadrado
int distSq(Point p1, Point p2) {
    return (p1.x - p2.x) * (p1.x - p2.x) + 
           (p1.y - p2.y) * (p1.y - p2.y);
}

/**
 * 0 -> Colineares
 * 1 -> Horário
 * 2 -> Anti-horário
 */
int orientation(Point p, Point q, Point r) {
    int val = (q.y - p.y) * (r.x - q.x) - 
              (q.x - p.x) * (r.y - q.y);

    if (val == 0) return 0;
    return (val > 0) ? 1 : 2;
}

std::vector<Point> grahamScan(std::vector<Point>& points) {
    int n = points.size();
    if (n < 3) return {}; // Retorna vetor vazio se impossível

    // 1. Encontrar o ponto mais baixo (pivô)
    int ymin = points[0].y, minIdx = 0;
    for (int i = 1; i < n; i++) {
        int y = points[i].y;
        if ((y < ymin) || (ymin == y && points[i].x < points[minIdx].x)) {
            ymin = points[i].y;
            minIdx = i;
        }
    }

    // Coloca o pivô na posição 0
    std::swap(points[0], points[minIdx]);
    Point p0 = points[0]; // Capturamos p0 localmente para usar no sort

    // 2. Ordenar os pontos baseados no ângulo polar com p0
    // Usamos uma função LAMBDA aqui. Isso elimina a necessidade de p0 ser global!
    std::sort(points.begin() + 1, points.end(), [p0](Point p1, Point p2) {
        int o = orientation(p0, p1, p2);
        if (o == 0) {
            return distSq(p0, p2) >= distSq(p0, p1);
        }
        return (o == 2); // Retorna true se p2 for anti-horário em relação a p1
    });

    // 3. O Loop Principal usando vector como Pilha
    std::vector<Point> hull;
    
    // Adiciona os 3 primeiros pontos
    hull.push_back(points[0]);
    hull.push_back(points[1]);
    hull.push_back(points[2]);

    for (int i = 3; i < n; i++) {
        // Lógica do Graham: Enquanto não fizer curva à esquerda, remove o topo.
        // hull.back() é o Topo.
        // hull[hull.size() - 2] é o Next-to-Top.
        while (hull.size() > 1 && 
               orientation(hull[hull.size() - 2], hull.back(), points[i]) != 2) {
            hull.pop_back(); // Remove o topo
        }
        hull.push_back(points[i]);
    }

    return hull;
}