// Programa 3: 3-SAT por redução ao Clique
// Uso: ./sat3 <arquivo_formula> 
#include "reducoes.hpp"

int main(int argc, char** argv) {
    if (argc < 2) { cerr << "Uso: " << argv[0] << " <arquivo_formula>\n"; return 1; }
    Formula f;
    if (!lerFormula(argv[1], f)) return 1;
    for (const auto& c : f.clausulas)
        if (c.size() > 3) {
            cerr << "Erro: 3-SAT exige no maximo 3 literais por clausula (use ./sat).\n";
            return 1;
        }

    Cronometro t;
    Resultado3Sat r = resolver3SatPorClique(f);
    double ms = t.ms();

    cout << "=== 3-SAT (via Clique) ===\n";
    cout << "Variaveis: " << f.nVars << " | Clausulas: " << f.clausulas.size()
         << " | Vertices do grafo: " << r.verticesGrafo << "\n";
    if (r.satisfativel) {
        cout << "Formula SATISFATIVEL. Atribuicao:\n";
        imprimeAtribuicao(f.nVars, r.valores);
        cout << "Verificacao: " << (satisfaz(f, r.valores) ? "OK" : "FALHOU") << "\n";
    } else {
        cout << "Formula INSATISFATIVEL.\n";
    }
    cout << "Nos explorados: " << r.nos << "\n";
    cout << "Tempo de execucao: " << ms << " ms\n";
    return 0;
}
