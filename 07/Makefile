test_vector: test_vector.cpp vector.h
	g++ test_vector.cpp -o test_vector -O2 -std=c++14 -pthread


test: test_vector
	./test_vector

clean:
	rm -rf *.o test_vector
