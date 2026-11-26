# Trabalho Prático – PAA (UFOP) 

SAT, 3-SAT, Conjunto Independente e Clique. Só o Clique é resolvido de fato
(Branch and Bound com poda por coloração); os demais são reduções polinomiais a ele.

    SAT -> 3-SAT -> Clique        Conjunto Independente -> Clique

## Compilar e executar
    make
    ./clique                 instancias/grafo_exemplo.txt
    ./conjunto_independente  instancias/grafo_exemplo.txt
    ./sat3                   instancias/3sat_media.txt
    ./sat                    instancias/sat_media.txt
    ./gerador grafo 50 0.5 42 > g.txt          # n, densidade, seed
    ./gerador sat 10 30 3 42 > f.txt           # vars, clausulas, lit/clausula, seed

## Arquivos
- src/util.hpp          cronômetro, leitura (grafo/fórmula), verificadores
- src/clique_bb.hpp     solver Branch and Bound (bitsets + coloração gulosa)
- src/reducoes.hpp      complemento, SAT->3-SAT, 3-SAT->Clique (Karp)
- src/clique.cpp, conjunto_independente.cpp, sat3.cpp, sat.cpp   os 4 programas
- src/gerador.cpp       gerador de instâncias aleatórias
- instancias/           12 instâncias (3 por problema) + os exemplos do enunciado

Vértices são impressos de 1 a n. Todo programa verifica a própria resposta.
