CPPFLAGS = -I ../../build
VPATH=../../build
NS3LIBS=libns3.17-core-debug.so libns3.17-network-debug.so libns3.17-bridge-debug.so libns3.17-csma-debug.so libns3.17-internet-debug.so libns3.17-mpi-debug.so libns3.17-applications-debug.so libns3.17-stats-debug.so libns3.17-config-store-debug.so libns3.17-tools-debug.so
#vpath %.so ../../build
.PHONY: all clean

all: gmon.out
        LD_LIBRARY_PATH=../../build gprof ./EunetSwitchTest -p -q

EunetSwitch.o: EunetSwitch.cpp EunetSwitch.h
	g++ -g -pg -O0 -std=c++0x -c -o $@ $(CPPFLAGS) $*.cpp

EunetSwitchTest.o: EunetSwitchTest.cc EunetSwitch.h
	g++ -g -pg -O0 -std=c++0x -c -o $@ $(CPPFLAGS) $*.cc

EunetSwitchTest: EunetSwitchTest.o EunetSwitch.o $(NS3LIBS)
	g++ -g -pg -O0 -std=c++0x -o $@ $(CPPFLAGS) $^

gmon.out: EunetSwitchTest
	NS_LOG="EunetSwitchTest=**:EunetSwitch=**:CsmaHelper=**:TraceHelper=**:OutputStreamWrapper=**:FatalImpl=**:Packet=**" LD_LIBRARY_PATH=../../build ./EunetSwitchTest

clean:
	-rm -f gmon.out
	-rm -f EunetSwitchTest
	-rm -f *.pcap *.tr
	-rm -f *.o

