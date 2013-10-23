main:
	rm -rf Debug/
	../waf --run csma-bridge 

hello-gprof:
	g++ -o hello hello.cc -pg -O0
	gprof hello -p

