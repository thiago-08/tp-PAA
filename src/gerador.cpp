// Gerador de instâncias (não faz parte dos 4 programas pedidos)
//   ./gerador grafo <n> <densidade 0..1> <seed>
//   ./gerador sat   <nVars> <nClausulas> <literais_por_clausula> <seed> 
#include <cstdlib>
#include <iostream>
#include <random>
#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

int main(int argc, char** argv) {
    if (argc >= 5 && string(argv[1]) == "grafo") {
        int n = atoi(argv[2]);
        double p = atof(argv[3]);
        mt19937 rng(atoi(argv[4]));
        uniform_real_distribution<double> U(0, 1);
        vector<vector<int>> a(n, vector<int>(n, 0));
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++) a[i][j] = a[j][i] = (U(rng) < p);
        cout << n << "\n";
        for (auto& r : a) {
            for (int j = 0; j < n; j++) cout << r[j] << (j + 1 < n ? " " : "\n");
        }
    } else if (argc >= 6 && string(argv[1]) == "sat") {
        int n = atoi(argv[2]), m = atoi(argv[3]), k = min(atoi(argv[4]), atoi(argv[2]));
        mt19937 rng(atoi(argv[5]));
        cout << n << "\n";
        for (int c = 0; c < m; c++) {
            vector<int> vars(n);
            iota(vars.begin(), vars.end(), 0);
            shuffle(vars.begin(), vars.end(), rng);
            vector<int> row(n, -1);
            for (int i = 0; i < k; i++) row[vars[i]] = rng() % 2;
            for (int j = 0; j < n; j++) cout << row[j] << (j + 1 < n ? " " : "\n");
        }
    } else {
        cerr << "Uso:\n  " << argv[0] << " grafo <n> <densidade> <seed>\n  "
             << argv[0] << " sat <nVars> <nClausulas> <lit_por_clausula> <seed>\n";
        return 1;
    }
    return 0;
}
