// clique_bb.hpp - Clique máximo por Branch and Bound
//
// Branch: escolhe um vértice v do conjunto de candidatos P, inclui em R (clique atual)
//         e recursa com P ∩ N(v); depois remove v de P e continua.
// Bound : coloração gulosa de P (Tomita & Seki, MCQ/MCR). Os vértices de P são
//         ordenados por cor; um clique em P tem no máximo (#cores) vértices.
//         Se |R| + cor(v) <= |melhor|, o ramo é podado.
// Os conjuntos são bitsets (vector<uint64_t>) para operações rápidas
#pragma once
#include <algorithm>
#include <cstdint>
#include <numeric>
#include <vector>

#include "util.hpp"

struct ResultadoClique {
    vector<int> vertices;  // índices originais (0-based)
    long long nos = 0;     // nós da árvore de busca visitados
};

class CliqueBB {
    int n = 0, W = 0;
    vector<vector<uint64_t>> adj;  // adjacência (com vértices reordenados)
    vector<int> perm;              // novo índice -> índice original
    vector<int> melhor, atual;
    long long nos = 0;
    int alvo = 0;
    bool parar = false;

    static int primeiro(const vector<uint64_t>& b) {
        for (size_t w = 0; w < b.size(); w++)
            if (b[w]) return (int)(w * 64 + __builtin_ctzll(b[w]));
        return -1;
    }
    static void limpa(vector<uint64_t>& b, int v) { b[v >> 6] &= ~(1ULL << (v & 63)); }

    void expandir(const vector<uint64_t>& P) {
        nos++;
        // --- coloração gulosa de P: gera ordem[] e cor[] (cores crescentes)
        vector<int> ordem, cor;
        vector<uint64_t> Q = P;
        int k = 0;
        while (primeiro(Q) >= 0) {
            k++;
            vector<uint64_t> Qc = Q;
            int v;
            while ((v = primeiro(Qc)) >= 0) {
                limpa(Qc, v);
                limpa(Q, v);
                for (int w = 0; w < W; w++) Qc[w] &= ~adj[v][w];  // mesma cor: não adjacentes
                ordem.push_back(v);
                cor.push_back(k);
            }
        }
        vector<uint64_t> Pm = P;
        for (int i = (int)ordem.size() - 1; i >= 0 && !parar; i--) {
            if ((int)atual.size() + cor[i] <= (int)melhor.size()) return;  // BOUND
            int v = ordem[i];
            atual.push_back(v);  // BRANCH
            vector<uint64_t> NP(W);
            bool vazio = true;
            for (int w = 0; w < W; w++) {
                NP[w] = Pm[w] & adj[v][w];
                if (NP[w]) vazio = false;
            }
            if (vazio) {
                if (atual.size() > melhor.size()) {
                    melhor = atual;
                    if (alvo > 0 && (int)melhor.size() >= alvo) parar = true;
                }
            } else {
                expandir(NP);
            }
            atual.pop_back();
            limpa(Pm, v);
        }
    }

public:
    // alvo > 0: para assim que achar um clique com 'alvo' vértices (útil nas reduções de SAT).
    ResultadoClique resolver(const Grafo& g, int alvoParada = 0) {
        n = (int)g.size();
        W = (n + 63) / 64;
        alvo = alvoParada;
        parar = false;
        nos = 0;
        melhor.clear();
        atual.clear();
        ResultadoClique res;
        if (n == 0) return res;

        // reordena por grau decrescente (melhora a coloração gulosa)
        vector<int> grau(n, 0);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) grau[i] += g[i][j];
        perm.resize(n);
        iota(perm.begin(), perm.end(), 0);
        stable_sort(perm.begin(), perm.end(), [&](int a, int b) { return grau[a] > grau[b]; });

        adj.assign(n, vector<uint64_t>(W, 0));
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (g[perm[i]][perm[j]]) adj[i][j >> 6] |= 1ULL << (j & 63);

        vector<uint64_t> P(W, 0);
        for (int i = 0; i < n; i++) P[i >> 6] |= 1ULL << (i & 63);
        expandir(P);

        for (int v : melhor) res.vertices.push_back(perm[v]);
        sort(res.vertices.begin(), res.vertices.end());
        res.nos = nos;
        return res;
    }
};
