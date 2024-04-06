COMPILER = g++
FLAGS = -g -Wall -std=c++14
COMPILE = $(COMPILER) $(FLAGS)

all: main.o CancerData.o 
	$(COMPILE) main.o CancerData.o -o PA3

%.o: %.cpp CancerData.h AVLNode.h AVLTree.h
	$(COMPILE) -c $< -o $@

clean:
	rm *.o PA3