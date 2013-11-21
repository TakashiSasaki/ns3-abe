.PHONY: all clean

all: fact

clean:
	rm -f fact fact.o

fact: fact.cc
	g++ -g -pg -O2 -o fact $^ 

gmon.out: fact
	./fact

prof: gmon.out
	gprof fact -p -q

