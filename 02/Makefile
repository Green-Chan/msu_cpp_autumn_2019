all: allocator.o

allocator.o: allocator.cpp allocator.h
	g++ -c allocator.cpp -O2 -std=c++14

test_allocator: test.o allocator.o
	g++ -o test_allocator test.o allocator.o

test.o: test.cpp allocator.h
	g++ -c test.cpp -O2 -std=c++14

test: test_allocator
	./test_allocator

clean:
	rm -rf *.o test_allocator