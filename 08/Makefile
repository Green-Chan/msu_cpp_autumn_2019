test_pool: test_pool.o thread_pool.o
	g++ -o test_pool test_pool.o thread_pool.o

test_pool.o: test_pool.cpp thread_pool.h
	g++ -c test_pool.cpp -O2 -std=c++14 -pthread

tread_pool.o: thread_pool.cpp thread_pool.h
	g++ -c thread_pool.cpp -O2 -std=c++14 -pthread

test: test_pool
	./test_pool

clean:
	rm -rf *.o test_pool
