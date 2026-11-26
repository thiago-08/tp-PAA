CXX      = g++
CXXFLAGS = -O2 -std=c++17 -Wall -Wextra

all: clique conjunto_independente sat3 sat gerador

clique: src/clique.cpp src/clique_bb.hpp src/reducoes.hpp src/util.hpp
	$(CXX) $(CXXFLAGS) -o $@ src/clique.cpp
conjunto_independente: src/conjunto_independente.cpp src/clique_bb.hpp src/reducoes.hpp src/util.hpp
	$(CXX) $(CXXFLAGS) -o $@ src/conjunto_independente.cpp
sat3: src/sat3.cpp src/clique_bb.hpp src/reducoes.hpp src/util.hpp
	$(CXX) $(CXXFLAGS) -o $@ src/sat3.cpp
sat: src/sat.cpp src/clique_bb.hpp src/reducoes.hpp src/util.hpp
	$(CXX) $(CXXFLAGS) -o $@ src/sat.cpp
gerador: src/gerador.cpp
	$(CXX) $(CXXFLAGS) -o $@ src/gerador.cpp

clean:
	rm -f clique conjunto_independente sat3 sat gerador
