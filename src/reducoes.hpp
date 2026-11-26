 #pragma once
#include "clique_bb.hpp"
#include "util.hpp"

//Conjunto Independente -> Clique
inline Grafo complemento(const Grafo& g) {
    int n = (int)g.size();
    Grafo c(n, vector<char>(n, 0));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (i != j) c[i][j] = !g[i][j];
    return c;
}

//SAT -> 3-SAT
inline Formula satPara3Sat(const Formula& f) {
    Formula r;
    int prox = f.nVars;
    for (const auto& c : f.clausulas) {
        int k = (int)c.size();
        if (k <= 3) { r.clausulas.push_back(c); continue; }
        int y = ++prox;
        r.clausulas.push_back({c[0], c[1], y});
        for (int i = 2; i < k - 2; i++) {
            int y2 = ++prox;
            r.clausulas.push_back({-y, c[i], y2});
            y = y2;
        }
        r.clausulas.push_back({-y, c[k - 2], c[k - 1]});
    }
    r.nVars = prox;
    return r;
}

// 3-SAT -> Clique
struct InfoReducao3Sat {
    Grafo g;
    vector<int> literal;   // literal associado a cada vértice
    vector<int> clausula;  // cláusula de cada vértice
};

inline InfoReducao3Sat construirGrafo3Sat(const Formula& f) {
    InfoReducao3Sat r;
    for (size_t i = 0; i < f.clausulas.size(); i++)
        for (int l : f.clausulas[i]) {
            r.literal.push_back(l);
            r.clausula.push_back((int)i);
        }
    int N = (int)r.literal.size();
    r.g.assign(N, vector<char>(N, 0));
    for (int a = 0; a < N; a++)
        for (int b = a + 1; b < N; b++)
            if (r.clausula[a] != r.clausula[b] && r.literal[a] != -r.literal[b])
                r.g[a][b] = r.g[b][a] = 1;
    return r;
}

struct Resultado3Sat {
    bool satisfativel = false;
    vector<char> valores;  
    long long nos = 0;
    int verticesGrafo = 0;
};

// Resolve a fórmula (cada cláusula com no máximo 3 literais) via Clique.
inline Resultado3Sat resolver3SatPorClique(const Formula& f) {
    Resultado3Sat res;
    res.valores.assign(f.nVars + 1, 1);
    int m = (int)f.clausulas.size();
    for (const auto& c : f.clausulas)
        if (c.empty()) return res;  // cláusula vazia é falsa -> insatisfatível
    if (m == 0) { res.satisfativel = true; return res; }

    InfoReducao3Sat r = construirGrafo3Sat(f);
    res.verticesGrafo = (int)r.g.size();
    CliqueBB solver;
    ResultadoClique cl = solver.resolver(r.g, m);  // para ao achar clique de tamanho m
    res.nos = cl.nos;
    if ((int)cl.vertices.size() == m) {
        res.satisfativel = true;
        for (int v : cl.vertices) {  // literal do clique é verdadeiro
            int l = r.literal[v];
            res.valores[l > 0 ? l : -l] = (l > 0);
        }
    }
    return res;
}
