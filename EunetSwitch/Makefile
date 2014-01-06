vpath %.h container:model:eunet
vpath %.cc container:model:eunet:test:../../utils
vpath %.so ../../build:libs
.PHONY: test visualize

DCEDIR=$(shell ls | grep dce)
$(info DCEDIR=$(DCEDIR))
ifneq ($(DCEDIR),)
	NS3VERSION=DCE
else
	NS3VERSION=317
endif
ifeq ($(NS3VERSION),)
	$(error Can\'t determine ns3 version)
endif

$(info NS3VERSION=$(NS3VERSION))

CXXFLAGSCOMMON=-Icontainer -Imodel -Iinclude -Ieunet -L. -Llibs -g -pg -O0 -std=c++0x -Wall -Werror
CXXFLAGSDCE=-I./dce/build -I./dce/build/include/ns3 -L./dce/build -L./dce/build/include/ns3
CXXFLAGS317=-I../../build -L../../build 
ifeq ($(NS3VERSION),DCE)
	CXXFLAGS=$(CXXFLAGSCOMMON) $(CXXFLAGSDCE)
endif
ifeq ($(NS3VERSION),317)
	CXXFLAGS=$(CXXFLAGSCOMMON) $(CXXFLAGS317)
endif

ifeq ($(OS),Windows_NT)
	SOSUFFIX=dll.a
	SOPREFIX=libns3.17-
	EXECENV=PATH="$(PATH):../../build"
else
	SOSUFFIX=so
	EXECENV=LD_LIBRARY_PATH=./dce/build:./dce/build/include/ns3:../../build:libs PYTHONPATH=../../build/bindings/python:../../src/visualizer:../../../pybindgen-0.16.0.825 DCE_PATH=dce/build/bin_dce
endif

#CPPFLAGS = -g -pg -O0 -std=c++0x -Wall -Werror -I../../build -I../../build/include -I../../../ns-3-dev/build 

SOPREFIX317=libns3.17-
SOPREFIXDEV=libns3-dev-

#keep alphabetical order
SOPREFIX=$(SOPREFIX317)
NS3LIBS317=\
	$(SOPREFIX)antenna-debug.$(SOSUFFIX) \
	$(SOPREFIX)applications-debug.$(SOSUFFIX) \
	$(SOPREFIX)bridge-debug.$(SOSUFFIX) \
	$(SOPREFIX)buildings-debug.$(SOSUFFIX) \
	$(SOPREFIX)config-store-debug.$(SOSUFFIX) \
	$(SOPREFIX)core-debug.$(SOSUFFIX) \
	$(SOPREFIX)csma-debug.$(SOSUFFIX) \
	$(SOPREFIX)csma-layout-debug.$(SOSUFFIX) \
	$(SOPREFIX)dsr-debug.$(SOSUFFIX) \
	$(SOPREFIX)energy-debug.$(SOSUFFIX) \
	$(SOPREFIX)flow-monitor-debug.$(SOSUFFIX) \
	$(SOPREFIX)internet-debug.$(SOSUFFIX) \
	$(SOPREFIX)lte-debug.$(SOSUFFIX) \
	$(SOPREFIX)mesh-debug.$(SOSUFFIX) \
	$(SOPREFIX)mpi-debug.$(SOSUFFIX) \
	$(SOPREFIX)netanim-debug.$(SOSUFFIX) \
	$(SOPREFIX)network-debug.$(SOSUFFIX) \
	$(SOPREFIX)point-to-point-debug.$(SOSUFFIX) \
	$(SOPREFIX)stats-debug.$(SOSUFFIX) \
	$(SOPREFIX)olsr-debug.$(SOSUFFIX) \
	$(SOPREFIX)propagation-debug.$(SOSUFFIX) \
	$(SOPREFIX)tools-debug.$(SOSUFFIX) \
	$(SOPREFIX)wifi-debug.$(SOSUFFIX) \
	$(SOPREFIX)mobility-debug.$(SOSUFFIX) \
	$(SOPREFIX)spectrum-debug.$(SOSUFFIX) \
	$(SOPREFIX)uan-debug.$(SOSUFFIX) \
	$(SOPREFIX)virtual-net-device-debug.$(SOSUFFIX) \
	$(SOPREFIX)visualizer-debug.$(SOSUFFIX) \
	$(SOPREFIX)wimax-debug.$(SOSUFFIX) \
	$(SOPREFIX)test-debug.$(SOSUFFIX) \
	$(SOPREFIX)tools-test-debug.$(SOSUFFIX) \


# keep alphabetical order
SOPREFIX=$(SOPREFIXDEV)
NS3LIBSDEV=\
	$(SOPREFIX)antenna-debug.$(SOSUFFIX) \
	$(SOPREFIX)applications-debug.$(SOSUFFIX) \
	$(SOPREFIX)bridge-debug.so \
	$(SOPREFIX)buildings-debug.$(SOSUFFIX) \
	$(SOPREFIX)config-store-debug.$(SOSUFFIX) \
	$(SOPREFIX)core-debug.so \
	$(SOPREFIX)core-test-debug.so \
	$(SOPREFIX)csma-debug.$(SOSUFFIX) \
	$(SOPREFIX)csma-layout-debug.$(SOSUFFIX) \
	$(SOPREFIX)energy-debug.$(SOSUFFIX) \
	$(SOPREFIX)flow-monitor-debug.$(SOSUFFIX) \
	$(SOPREFIX)internet-debug.so \
	$(SOPREFIX)lte-debug.$(SOSUFFIX) \
	$(SOPREFIX)netanim-debug.$(SOSUFFIX) \
	$(SOPREFIX)network-debug.so \
	$(SOPREFIX)mobility-debug.$(SOSUFFIX) \
	$(SOPREFIX)mpi-debug.$(SOSUFFIX) \
	$(SOPREFIX)point-to-point-debug.$(SOSUFFIX) \
	$(SOPREFIX)propagation-debug.$(SOSUFFIX) \
	$(SOPREFIX)spectrum-debug.$(SOSUFFIX) \
	$(SOPREFIX)stats-debug.so \
	$(SOPREFIX)test-debug.$(SOSUFFIX) \
	$(SOPREFIX)uan-debug.$(SOSUFFIX) \
	$(SOPREFIX)virtual-net-device-debug.$(SOSUFFIX) \
	$(SOPREFIX)wifi-debug.$(SOSUFFIX) \
	$(SOPREFIX)wimax-debug.$(SOSUFFIX) \

	
NS3LIBSDCE=libns3-dce.so libns3-dce-quagga.so libns3-dce-quagga-test.so libns3-dce-test-netlink.so libns3-dce-test.so libns3-netlink.so

NS3LIBS=$(NS3LIBSDEV) $(NS3LIBSDCE)

TESTSUITECOMMON= \
#	SimpleApTest.o \
	EunetTerminalTest.o \
	EunetTerminalsTest.o \
	EunetSwitchesTest.o \
	EunetSwitchTest.o 

TESTSUITE317= \
	EunetMobileTest.o 

TESTSUITEDCE= \
#	EunetRouterTest.o 

ifeq ($(NS3VERSION),317)
	TESTSUITES=$(TESTSUITECOMMON) $(TESTSUITE317)
else
	TESTSUITES=$(TESTSUITECOMMON) $(TESTSUITEDCE)
endif
$(info TESTSUITES=$(TESTSUITES))

NS_LOG_317=NS_LOG=WifiBase=*:EunetMobile=*:CsmaInternetNode=*:CsmaNode=*:EunetMobileTest=*
NS_LOG_DCE=NS_LOG=
ifeq ($(NS3VERSION),317)
	NS_LOG=$(NS_LOG_317)
else
	NS_LOG=$(NS_LOG_DCE)
endif
#define NS_LOG
#NS_LOG="NamedRouters=**:EunetRouters=**:EunetRouter=**:SimpleRouter=**:BridgingAp=**:SimpleAp=**:NamedSwitches=**:EunetSwitch=**:EunetSwitches=**:EunetTerminal=**:EunetTerminals=**:CsmaNode=debug:OnOffApplication=info:CsmaChannelNode=debug:CsmaInternetNode=**:PacketSinkNode=debug:OnOffNode=**:SimpleSwitch=**"
#endef

libeunet.a :NamedSwitches.o EunetSwitch.o EunetSwitches.o \
	EunetTerminal.o EunetTerminals.o CsmaNode.o CsmaChannelNode.o \
	CsmaInternetNode.o PacketSinkNode.o OnOffNode.o SimpleSwitch.o \
	SimpleAp.o BridgingAp.o \
	NamedRouters.o EunetRouter.o SimpleRouter.o EunetRouters.o \
	WifiBase.o MobilityBase.o EunetMobile.o
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
	-rm -f *.a

test-runner: test-runner.o $(NS3LIBS) $(TESTSUITES) libeunet.a 
	g++ -o $@ $(CXXFLAGS) $^

test: test-runner
	$(EXECENV) $(NS_LOG) ./test-runner --stop-on-failure

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
