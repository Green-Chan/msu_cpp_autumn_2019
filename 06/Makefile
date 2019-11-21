test_format: test_format.o
	g++ -o test_format test_format.o

test_format.o: test_format.cpp format.h
	g++ -c test_format.cpp -O2 -std=c++14

test: test_format
	./test_format

clean:
	rm -rf *.o test_format
