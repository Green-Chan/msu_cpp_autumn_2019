all: matrix.o

matrix.o: matrix.cpp matrix.h
	g++ -c matrix.cpp -O2 -std=c++14

test_matrix: test_matrix.o matrix.o
	g++ -o test_matrix test_matrix.o matrix.o

test_matrix.o: test_matrix.cpp matrix.h
	g++ -c test_matrix.cpp -O2 -std=c++14

test: test_matrix
	./test_matrix

clean:
	rm -rf *.o test_matrix
