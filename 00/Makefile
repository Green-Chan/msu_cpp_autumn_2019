all: array_treversing

array_treversing: array_treversing.o
	g++ -o array_treversing array_treversing.o

array_treversing.o: array_treversing.cpp
	g++ -c array_treversing.cpp -O2 -std=c++14

clean:
	rm -rf *.o array_treversing

run: array_treversing
	./array_treversing
