main:
	rm -rf Debug/
	../waf --run csma-bridge 

hello-gprof:
	rm gmon.out
	g++ -o hello -pg -g -O0 hello.cc
	./hello
	gprof hello -p

