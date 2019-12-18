all: bigint.o

bigint.o: bigint.cpp bigint.h
	g++ -c bigint.cpp -O2 -std=c++14

test_bigint: test_bigint.o bigint.o
	g++ -o test_bigint test_bigint.o bigint.o -std=c++14

test_bigint.o: test_bigint.cpp bigint.h
	g++ -c test_bigint.cpp -O2 -std=c++14

test: test_bigint
	./test_bigint

clean:
	rm -rf *.o test_bigint
