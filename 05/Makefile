test_ser: test_ser.o
	g++ -o test_ser test_ser.o

test_ser.o: test_ser.cpp deserializer.h serializer.h error.h
	g++ -c test_ser.cpp -O2 -std=c++14

test: test_ser
	./test_ser

clean:
	rm -rf *.o test_ser
