all: lab3-4

%.o: %.cpp *.h Makefile
	g++ -c $< -o $@

lab3-4: lab3-4.o
	g++ -o lab3-4 $^

clean:
	rm *.o

test: all
	./lab3-4
