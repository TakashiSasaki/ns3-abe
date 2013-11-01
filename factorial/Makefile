.PHONY: all clean

all: prof

clean:
	-rm fact fact.o

fact: fact.cc
	g++ -g -pg -O2 -o fact $^ 

gmon.out: fact
	time ./fact

prof: gmon.out
	gprof fact -p -q

