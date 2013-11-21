.PHONY: all gprof clean

all: hello

clean:
	rm -f *.o

hello: hello.cc
	g++ -o hello -pg -g -O0 $^

gprof: hello
	-rm gmon.out
	./hello
	gprof hello -p
