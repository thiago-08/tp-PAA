// Programa 1: Clique máximo (Branch and Bound)
// Uso: ./clique <arquivo_grafo>
#include "reducoes.hpp"

int main(int argc, char** argv) {
    if (argc < 2) { cerr << "Uso: " << argv[0] << " <arquivo_grafo>\n"; return 1; }
    Grafo g;
    if (!lerGrafo(argv[1], g)) return 1;

    Cronometro t;
    CliqueBB solver;
    ResultadoClique r = solver.resolver(g);
    double ms = t.ms();

    cout << "=== Clique maximo (Branch and Bound) ===\n";
    cout << "Vertices do grafo: " << g.size() << "\n";
    cout << "Tamanho do clique: " << r.vertices.size() << "\n";
    cout << "Vertices (1..n):  ";
    for (int v : r.vertices) cout << " " << v + 1;
    cout << "\nNos explorados: " << r.nos << "\n";
    cout << "Verificacao: " << (ehClique(g, r.vertices) ? "OK" : "FALHOU") << "\n";
    cout << "Tempo de execucao: " << ms << " ms\n";
    return 0; 
}
