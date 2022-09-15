all: main

main: test_sfml.o vector.o basic_vector.o
	g++ test_sfml.o vector.o basic_vector.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system 

test_sfml.o: test_sfml.cpp
	g++ -c test_sfml.cpp

vector.o: vector.cpp
	g++ -c vector.cpp

basic_vector.o: basic_vector.cpp
	g++ -c basic_vector.cpp

clean:
	rm -rf *.o hello

