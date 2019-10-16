input=
all: mycalc

mycalc: mycalc.o
	g++ -o mycalc mycalc.o

mycalc.o: mycalc.cpp
	g++ -c mycalc.cpp -O2 -std=c++14

clean:
	rm -rf *.o mycalc

run: mycalc
	./mycalc $(input)

test: mycalc test.py
	python test.py
