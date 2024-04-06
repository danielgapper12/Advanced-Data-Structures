out: mainexe

mainexe: main.o TwitterData.o
	g++ -std=c++14 main.o TwitterData.o -o mainexe

main.o: main.cpp TwitterData.hpp
	g++ -std=c++14 -c main.cpp

TwitterData.o: TwitterData.cpp TwitterData.hpp
	g++ -std=c++14 -c TwitterData.cpp

