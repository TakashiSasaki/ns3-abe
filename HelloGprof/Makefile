.PHONY: all gprof

all: gprof

hello: hello.cc
	g++ -o hello -pg -g -O0 $^

gprof: hello
	-rm gmon.out
	./hello
	gprof hello -p

