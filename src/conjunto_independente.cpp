// Programa 2: Conjunto Independente máximo, por redução ao Clique (grafo complemento)
// Uso: ./conjunto_independente <arquivo_grafo> 
#include "reducoes.hpp"

int main(int argc, char** argv) {
    if (argc < 2) { cerr << "Uso: " << argv[0] << " <arquivo_grafo>\n"; return 1; }
    Grafo g;
    if (!lerGrafo(argv[1], g)) return 1;

    Cronometro t;
    Grafo comp = complemento(g);               // redução O(n^2)
    CliqueBB solver;
    ResultadoClique r = solver.resolver(comp);  // clique máximo do complemento
    double ms = t.ms();

    cout << "=== Conjunto Independente maximo (via Clique) ===\n";
    cout << "Vertices do grafo: " << g.size() << "\n";
    cout << "Tamanho do conjunto: " << r.vertices.size() << "\n";
    cout << "Vertices (1..n):  ";
    for (int v : r.vertices) cout << " " << v + 1;
    cout << "\nNos explorados: " << r.nos << "\n";
    cout << "Verificacao: " << (ehIndependente(g, r.vertices) ? "OK" : "FALHOU") << "\n";
    cout << "Tempo de execucao: " << ms << " ms\n";
    return 0;
}
