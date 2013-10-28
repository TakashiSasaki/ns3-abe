CPPFLAGS = -I ../../build
VPATH=../../build
NS3LIBS=libns3.17-core-debug.so libns3.17-network-debug.so libns3.17-bridge-debug.so libns3.17-csma-debug.so libns3.17-internet-debug.so libns3.17-mpi-debug.so libns3.17-applications-debug.so libns3.17-stats-debug.so libns3.17-config-store-debug.so libns3.17-tools-debug.so
#vpath %.so ../../build

all: gmon.out
	LD_LIBRARY_PATH=../../build gprof ./EunetSwitchTest -p -q

EunetSwitchTest: EunetSwitchTest.cc $(NS3LIBS)
	g++ -g -pg -O0 -o EunetSwitchTest $(CPPFLAGS) $^

gmon.out: EunetSwitchTest
	LD_LIBRARY_PATH=../../build ./EunetSwitchTest 

clean:
	-rm gmon.out
	-rm EunetSwitchTest
	-rm *.pcap *.tr
