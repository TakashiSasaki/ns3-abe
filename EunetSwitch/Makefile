vpath %.h container:model
vpath %.cc container:model:test:../../utils
vpath %.so ../../build:libs
.PHONY: test visualize

CXXFLAGS=-Icontainer -Imodel -I../../build -Iinclude -L../../build -L. -Llibs -g -pg -O0 -std=c++0x

ifeq ($(OS),Windows_NT)
	SOSUFFIX=dll.a
	SOPREFIX=libns3.17-
	EXECENV=PATH="$(PATH):../../build"
else
	SOSUFFIX=so
	EXECENV=LD_LIBRARY_PATH=../../build:libs PYTHONPATH=../../build/bindings/python:../../src/visualizer:../../../pybindgen-0.16.0.825 
endif

CPPFLAGS = -g -pg -O0 -std=c++0x -Wall -Werror -I../../build -I../../build/include -I../../../ns-3-dev/build

SOPREFIX=libns3.17-
SOPREFIXDEV=libns3-dev-

NS3LIBS=$(SOPREFIX)core-debug.$(SOSUFFIX) $(SOPREFIX)network-debug.$(SOSUFFIX) $(SOPREFIX)bridge-debug.$(SOSUFFIX) \
$(SOPREFIX)csma-debug.$(SOSUFFIX) \
$(SOPREFIX)internet-debug.$(SOSUFFIX) $(SOPREFIX)mpi-debug.$(SOSUFFIX) $(SOPREFIX)applications-debug.$(SOSUFFIX) \
$(SOPREFIX)stats-debug.$(SOSUFFIX) \
$(SOPREFIX)config-store-debug.$(SOSUFFIX) $(SOPREFIX)tools-debug.$(SOSUFFIX) $(SOPREFIX)olsr-debug.$(SOSUFFIX) \
$(SOPREFIX)point-to-point-debug.$(SOSUFFIX) \
$(SOPREFIX)wifi-debug.$(SOSUFFIX) $(SOPREFIX)propagation-debug.$(SOSUFFIX) $(SOPREFIX)mobility-debug.$(SOSUFFIX) \
$(SOPREFIX)netanim-debug.$(SOSUFFIX) $(SOPREFIX)lte-debug.$(SOSUFFIX) $(SOPREFIX)spectrum-debug.$(SOSUFFIX) \
$(SOPREFIX)virtual-net-device-debug.$(SOSUFFIX) $(SOPREFIX)buildings-debug.$(SOSUFFIX) \
$(SOPREFIX)antenna-debug.$(SOSUFFIX) $(SOPREFIX)visualizer-debug.$(SOSUFFIX) $(SOPREFIX)dsr-debug.$(SOSUFFIX) \
$(SOPREFIX)wimax-debug.$(SOSUFFIX) $(SOPREFIX)uan-debug.$(SOSUFFIX) $(SOPREFIX)energy-debug.$(SOSUFFIX) \
$(SOPREFIX)mesh-debug.$(SOSUFFIX) $(SOPREFIX)test-debug.$(SOSUFFIX) $(SOPREFIX)tools-test-debug.$(SOSUFFIX) \
$(SOPREFIX)csma-layout-debug.$(SOSUFFIX) $(SOPREFIX)flow-monitor-debug.$(SOSUFFIX)

NS3LIBSDEV=

NS3LIBSDCE=libns3-dce.so libns3-dce-quagga.so libns3-dce-quagga-test.so libns3-dce-test-netlink.so libns3-dce-test.so

#define NS_LOG
#NS_LOG="BridgingAp=**:SimpleAp=**:NamedSwitches=**:EunetSwitch=**:EunetSwitches=**:EunetTerminal=**:EunetTerminals=**:CsmaNode=debug:OnOffApplication=info:CsmaChannelNode=debug:CsmaInternetNode=**:PacketSinkNode=debug:OnOffNode=**:SimpleSwitch=**"
#endef

define NS_LOG
NS_LOG="EunetMobile=*:CsmaInternetNode=*:CsmaNode=*"
endef

libeunet.a : NamedSwitches.o EunetSwitch.o EunetSwitches.o \
			EunetTerminal.o EunetTerminals.o CsmaNode.o CsmaChannelNode.o \
			CsmaInternetNode.o PacketSinkNode.o OnOffNode.o SimpleSwitch.o \
			SimpleAp.o BridgingAp.o WifiBase.o MobilityBase.o EunetMobile.o
	ar r $@ $^

run2: EunetSimulation
	$(EXECENV) $(NS_LOG):EunetSimulation=** ./EunetSimulation 

gdb2: EunetSimulation
	$(EXECENV) gdb ./EunetSimulation
	
visualize2: EunetSimulation 
	$(EXECENV) $(NS_LOG) ./EunetSimulation --SimulatorImplementationType=ns3::VisualSimulatorImpl

EunetSimulation: EunetSimulation.cc libeunet.a $(NS3LIBS)
	g++ -o $@ $(CXXFLAGS) $^

visualize: EunetSwitchTest.o libeunet.a $(NS3LIBS) visualize.cc
	g++ -o $@ $(CXXFLAGS) $^
	$(EXECENV) $(NS_LOG) ./visualize --SimulatorImplementationType=ns3::VisualSimulatorImpl

gmon.out: EunetSwitchTest
	$(EXECENV) $(NS_LOG)"EunetSwitch=**:EunetSwitches=**:EunetSwitchTest=**:EunetTerminal=**:EunetTerminals=**:CsmaNode=**" ./EunetSwitchTest 

gprof: gmon.out
	$(EXECENV) gprof ./EunetSwitchTest -p -q

gdb: test-runner
	$(EXECENV) gdb ./test-runner 

doxygen:
	doxygen
	make -C latex

clean:
	-rm -f gmon.out
	-rm -f EunetSwitchTest
	-rm -f *.pcap *.tr
	-rm -f container/*.o model/*.o test/*.o *.o
	-rm *.a

test-runner: test-runner.o $(NS3LIBS) $(NS3LIBSDEV) $(NS3LIBDCE) \
	SimpleApTest.o EunetTerminalTest.o EunetTerminalsTest.o \
	EunetSwitchesTest.o EunetSwitchTest.o EunetMobileTest.o libeunet.a 
	g++ -o $@ $(CXXFLAGS) $^

test: test-runner
	$(EXECENV) $(NS_LOG) ./test-runner

install-dce-quagga: build-dce-quagga copy-shared-library copy-include-files

build-dce-quagga:
	sh build-dce-quagga.sh

copy-from-dce-build: copy-shared-library copy-include-files

copy-shared-library:
	-mkdir libs/
	cp dce/build/lib/*.so libs/

copy-include-files:
	-mkdir -p include/ns3
	cp dce/build/include/ns3/*.h include/ns3/
	cp dce/build/include/ns3-dev/ns3/*.h include/ns3/
