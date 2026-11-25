CXX=g++
CXXFLAGS= -Wall -std=c++11 -g -O1
EXEC_FILES= Ensemble-main Ensemble-test

all: Ensemble-main
# Regle generique
%.o: %.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS)

Ensemble-main: Ensemble.o Ensemble-main.o
	$(CXX) -o $@ $^ $(LDFLAGS)
Ensemble-test: Ensemble.o Ensemble-test.o
	$(CXX) -o $@ $^ $(LDFLAGS)

Ensemble-main.o: Ensemble.hpp
Ensemble.o: Ensemble.hpp
Ensemble-test.o: Ensemble.hpp

check: Ensemble-test
	./Ensemble-test

clean:
	rm -f *.o $(EXEC_FILES)