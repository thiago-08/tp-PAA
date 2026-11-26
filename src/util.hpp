#pragma once
#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Cronometro {
    chrono::steady_clock::time_point ini = chrono::steady_clock::now();
    double ms() const {
        return chrono::duration<double, milli>(chrono::steady_clock::now() - ini).count();
    }
};

using Grafo = vector<vector<char>>;  // matriz de adjacência n x n

// Formato: 1ª linha = n; depois n linhas com n valores (0/1).
inline bool lerGrafo(const string& caminho, Grafo& g) {
    ifstream f(caminho);
    if (!f) { cerr << "Erro: nao foi possivel abrir '" << caminho << "'\n"; return false; }
    int n;
    if (!(f >> n) || n < 0) { cerr << "Erro: primeira linha deve conter n >= 0\n"; return false; }
    g.assign(n, vector<char>(n, 0));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            int x;
            if (!(f >> x)) { cerr << "Erro: matriz incompleta\n"; return false; }
            g[i][j] = (x != 0);
        }
    for (int i = 0; i < n; i++) {
        g[i][i] = 0;
        for (int j = i + 1; j < n; j++) g[i][j] = g[j][i] = (g[i][j] || g[j][i]);
    }
    return true;
}

inline bool ehClique(const Grafo& g, const vector<int>& v) {
    for (size_t i = 0; i < v.size(); i++)
        for (size_t j = i + 1; j < v.size(); j++)
            if (!g[v[i]][v[j]]) return false;
    return true;
}

inline bool ehIndependente(const Grafo& g, const vector<int>& v) {
    for (size_t i = 0; i < v.size(); i++)
        for (size_t j = i + 1; j < v.size(); j++)
            if (g[v[i]][v[j]]) return false;
    return true;
}

struct Formula {
    int nVars = 0;
    vector<vector<int>> clausulas;
};

inline bool lerFormula(const string& caminho, Formula& f) {
    ifstream in(caminho);
    if (!in) { cerr << "Erro: nao foi possivel abrir '" << caminho << "'\n"; return false; }
    int n;
    if (!(in >> n) || n < 0) { cerr << "Erro: primeira linha deve conter n >= 0\n"; return false; }
    f.nVars = n;
    f.clausulas.clear();
    if (n == 0) return true;
    int x;
    while (in >> x) {
        vector<int> row(n);
        row[0] = x;
        for (int j = 1; j < n; j++)
            if (!(in >> row[j])) { cerr << "Erro: clausula incompleta\n"; return false; }
        vector<int> c;
        for (int j = 0; j < n; j++) {
            if (row[j] == 1) c.push_back(j + 1);
            else if (row[j] == 0) c.push_back(-(j + 1));
            else if (row[j] != -1) { cerr << "Erro: valor invalido " << row[j] << "\n"; return false; }
        }
        f.clausulas.push_back(c);  
    }
    return true;
}

inline bool satisfaz(const Formula& f, const vector<char>& valores) {
    for (const auto& c : f.clausulas) {
        bool ok = false;
        for (int l : c) {
            int v = l > 0 ? l : -l;
            if ((l > 0) == (valores[v] != 0)) { ok = true; break; }
        }
        if (!ok) return false;
    }
    return true;
}

inline void imprimeAtribuicao(int nVars, const vector<char>& valores) {
    for (int i = 1; i <= nVars; i++)
        cout << "  x" << i << " = " << (valores[i] ? "V (1)" : "F (0)") << "\n";
}
