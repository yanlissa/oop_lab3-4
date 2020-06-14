all: lab3-4

%.o: %.cpp *.h Makefile
	g++ -c $< -o $@

lab3-4: lab3-4.o UnorderedMap.o
	g++ -o lab3-4 lab3-4.o
