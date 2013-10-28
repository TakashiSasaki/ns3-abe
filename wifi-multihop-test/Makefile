CPPFLAGS = -g -pg -O2 -std=c++0x -I ../../build
VPATH=../../build
NS3LIBS=libns3.17-core-debug.so libns3.17-network-debug.so libns3.17-bridge-debug.so libns3.17-csma-debug.so libns3.17-internet-debug.so libns3.17-mpi-debug.so libns3.17-applications-debug.so libns3.17-stats-debug.so libns3.17-config-store-debug.so libns3.17-tools-debug.so
.PHONY: all build

current: difs-wifi-mac-test

OutputFileStream.o : OutputFileStream.cc OutputFileStream.h
	g++ $(CPPFLAGS) -c $<

difs-wifi-mac.o : difs-wifi-mac.cc difs-wifi-mac.h
	g++ $(CPPFLAGS) -c $<
	
difs-wifi-mac-test.o: difs-wifi-mac-test.cc difs-wifi-mac.h difs-wifi-mac-helper.h
	g++ $(CPPFLAGS) -c $<

difs-wifi-mac-test: difs-wifi-mac-test.o difs-wifi-mac.o
	g++ $(CPPFLAGS) -o $@  $^

all: difs-wifi-mac-test

clean:
	git clean -x -f -r

gmon.out: difs-wifi-mac-test
	LD_LIBRARY_PATH=../../build time ./difs-wifi-mac-test 
