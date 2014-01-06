vpath %.h container:model
vpath %.cc container:model:test:../../utils
vpath %.so ../../build:libs
.PHONY: test visualize

CXXFLAGSDCE=-I./dce/build -I./dce/build/include/ns3 -Icontainer -Imodel -Iinclude -L. -Llibs -L./dce/build -L./dce/build/include/ns3 -g -pg -O0 -std=c++0x
CXXFLAGS317=-I./dce/build -I./dce/build/include/ns3 -Icontainer -Imodel -I../../build -Iinclude -L../../build -L. -Llibs -L./dce/build -L./dce/build/include/ns3 -g -pg -O0 -std=c++0x
CXXFLAGS=$(CXXFLAGSDCE)

ifeq ($(OS),Windows_NT)
        SOSUFFIX=dll.a
        SOPREFIX=libns3.17-
        EXECENV=PATH="$(PATH):../../build"
else
	SOSUFFIX=so
	EXECENV=LD_LIBRARY_PATH=./dce/build:./dce/build/include/ns3:../../build:libs PYTHONPATH=../../build/bindings/python:../../src/visualizer:../../../pybindgen-0.16.0.825 DCE_PATH=dce/build/bin_dce
endif

CPPFLAGS = -g -pg -O0 -std=c++0x -Wall -Werror -I../../build -I../../build/include -I../../../ns-3-dev/build

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

#define NS_LOG
#NS_LOG="NamedRouters=**:EunetRouters=**:EunetRouter=**:SimpleRouter=**:BridgingAp=**:SimpleAp=**:NamedSwitches=**:EunetSwitch=**:EunetSwitches=**:EunetTerminal=**:EunetTerminals=**:CsmaNode=debug:OnOffApplication=info:CsmaChannelNode=debug:CsmaInternetNode=**:PacketSinkNode=debug:OnOffNode=**:SimpleSwitch=**"
#endef

define NS_LOG
NS_LOG="AnimationInterface=error"
endef

libeunet.a :NamedSwitches.o EunetSwitch.o EunetSwitches.o \
                        EunetTerminal.o EunetTerminals.o CsmaNode.o CsmaChannelNode.o \
                        CsmaInternetNode.o PacketSinkNode.o OnOffNode.o SimpleSwitch.o \
                        SimpleAp.o BridgingAp.o \
                        NamedRouters.o EunetRouter.o SimpleRouter.o EunetRouters.o
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

gdb: EunetSwitchTest
		$(EXECENV) gdb ./EunetSwitchTest

doxygen:
		doxygen
		make -C latex

clean:
		-rm -f gmon.out
		-rm -f EunetSwitchTest
		-rm -f *.pcap *.tr
		-rm -f container/*.o model/*.o test/*.o *.o
		-rm *.a

test-runner-dce: test-runner.o $(NS3LIBS) SimpleApTest.o EunetTerminalTest.o EunetTerminalsTest.o EunetSwitchesTest.o EunetSwitchTest.o EunetRouterTest.o libeunet.a 
	g++ -o $@ $(CXXFLAGS) $^

test-runner: test-runner.o $(NS3LIBS) $(NS3LIBSDCE) $(NS3LIBSDEV) SimpleApTest.o EunetTerminalTest.o EunetTerminalsTest.o EunetSwitchesTest.o EunetSwitchTest.o EunetRouterTest.o libeunet.a 
	g++ -o $@ $(CXXFLAGS) $^

test: test-runner
		$(EXECENV) $(NS_LOG) ./test-runner

#build this target first to use DCE feature
install-dce-quagga: build-dce-quagga copy-shared-library copy-include-files

build-dce-quagga:
		sh build-dce-quagga.sh

run-dce-quagga:
	$(EXECENV) dce/build/bin/dce-quagga-ospfd

copy-from-dce-build: copy-shared-library copy-include-files

copy-shared-library:
		-mkdir libs/
		cp dce/build/lib/*.so libs/

copy-include-files:
		-mkdir -p include/ns3
		cp dce/build/include/ns3/*.h include/ns3/
		cp dce/build/include/ns3-dev/ns3/*.h include/ns3/
