COMPILER = g++
FLAGS: -g -fopenmp -Wall -std=c++14



COMPILE = $(COMPILER) $(FLAGS)

all: main.o
	$(COMPILE) main.o -o test

%.o: %.cpp
	$(COMPILE) -c $< -o $@

clean:
	rm *.o test
