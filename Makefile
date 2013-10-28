.PHONY: build help clean all

all:
	make -C DifsWifiMac $@
	make -C EunetSwitch $@
	make -C factorial $@
	make -C HelloGprof $@
	make -C HelloNsLog $@
	make -C wifi-multihop-test $@

clean:
	make -C DifsWifiMac $@
	make -C EunetSwitch $@
	make -C factorial $@
	make -C HelloGprof $@
	make -C HelloNsLog $@
	make -C wifi-multihop-test $@
	-rm -f gmon.out
	-rm -f EunetSwitchTest
	-rm -f *.pcap *.tr

build: run-wifi-multihop-test

help:
	@echo To run all scripts, just type "'make run'".

build-wifi-buffer-test:
	../waf build wifi-buffer-test

run: run-wifi-buffer-test

run-wifi-buffer-test:
	../waf --run wifi-buffer-test

run-wifi-phy-test:
	../waf --run wifi-phy-test

run-collision_sample:
	../waf --run collision_sample

run-wifi-multihop-test:
	rm -rf Debug/
	../waf --run "wifi-multihop-test --lambda=1 --sim_count=1"

hello-gprof:
	rm gmon.out
	g++ -o hello -pg -g -O0 hello.cc
	./hello
	gprof hello -p

difs-wifi-mac-test:
	make -C wifi-multihop-test $@

main:
	rm -rf Debug/
	../waf --run csma-bridge 

hello-gprof:
	g++ -o hello hello.cc -pg -O0
	gprof hello -p

CPPFLAGS = -I ../../build
VPATH=../../build
NS3LIBS=libns3.17-core-debug.so libns3.17-network-debug.so libns3.17-bridge-debug.so libns3.17-csma-debug.so libns3.17-internet-debug.so libns3.17-mpi-debug.so libns3.17-applications-debug.so libns3.17-stats-debug.so libns3.17-config-store-debug.so libns3.17-tools-debug.so
#vpath %.so ../../build

#all: gmon.out
#        LD_LIBRARY_PATH=../../build gprof ./EunetSwitchTest -p -q

EunetSwitchTest: EunetSwitchTest.cc $(NS3LIBS)
        g++ -g -pg -O2 -std=c++0x -o EunetSwitchTest $(CPPFLAGS) $^

gmon.out: EunetSwitchTest
        LD_LIBRARY_PATH=../../build ./EunetSwitchTest

