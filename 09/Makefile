test_sort: test_sort.o sort.o
	g++ -o test_sort test_sort.o sort.o -pthread

test_sort.o: test_sort.cpp sort.h
	g++ -c test_sort.cpp -O2 -std=c++14 -pthread

sort.o: sort.cpp sort.h
	g++ -c sort.cpp -O2 -std=c++14 -pthread

test: test_sort
	./test_sort

clean:
	rm -rf *.o test_sort
