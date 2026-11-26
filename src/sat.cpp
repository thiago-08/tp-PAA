// Programa 4: SAT -> 3-SAT -> Clique
// Uso: ./sat <arquivo_formula> 
#include "reducoes.hpp"

int main(int argc, char** argv) {
    if (argc < 2) { cerr << "Uso: " << argv[0] << " <arquivo_formula>\n"; return 1; }
    Formula f;
    if (!lerFormula(argv[1], f)) return 1;

    Cronometro t;
    Formula f3 = satPara3Sat(f);              // SAT -> 3-SAT
    Resultado3Sat r = resolver3SatPorClique(f3);  // 3-SAT -> Clique
    double ms = t.ms();

    cout << "=== SAT (via 3-SAT e Clique) ===\n";
    cout << "Variaveis originais: " << f.nVars << " | Clausulas: " << f.clausulas.size() << "\n";
    cout << "Apos conversao 3-SAT: " << f3.nVars << " variaveis, " << f3.clausulas.size()
         << " clausulas, " << r.verticesGrafo << " vertices no grafo\n";
    if (r.satisfativel) {
        cout << "Formula SATISFATIVEL. Atribuicao (variaveis originais):\n";
        imprimeAtribuicao(f.nVars, r.valores);
        cout << "Verificacao na formula original: " << (satisfaz(f, r.valores) ? "OK" : "FALHOU") << "\n";
    } else {
        cout << "Formula INSATISFATIVEL.\n";
    }
    cout << "Nos explorados: " << r.nos << "\n";
    cout << "Tempo de execucao: " << ms << " ms\n";
    return 0;
}
