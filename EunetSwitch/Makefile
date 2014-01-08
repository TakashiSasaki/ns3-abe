vpath %.h container:model:eunet
vpath %.cc container:model:eunet:test
vpath %.so ../../build:libs
.PHONY: test visualize

DCEDIR=$(shell ls | grep dce)
$(info DCEDIR=$(DCEDIR))
ifneq ($(DCEDIR),)
    VER:=DCE
    DCE:=DCE
    $(info DCE directory was detected)
else
    VER:=STD
    STD:=STD
    $(info DCE directory was not detedted)
endif

ifeq ($(VER),)
    $(error Can\'t determine ns3 version)
endif

ifeq ($(OS),Windows_NT)
    CYGWIN:=CYGWIN
    SOSUFFIX:=dll.a
    SOPREFIX:=libns3.17-
    EXECENV:=PATH="$(PATH):../../build"
else
    LINUX:=LINUX
    SOSUFFIX:=so
    EXECENV:=LD_LIBRARY_PATH=$(LD_LIBRARY_PATH) DCE_PATH=$(DCE_PATH) DCE_ROOT=$(DCE_ROOT) 
endif

CXXFLAGS_COMMON:= -Icontainer -Imodel -Iinclude -Ieunet -L. -Llibs -g -pg -O0 -std=c++0x -Wall -Werror
CXXFLAGS_DCE := -I./dce/build -I./dce/build/include -L./dce/build -L./dce/build/lib -L./dce/build/include/ns3 
CXXFLAGS_STD := -I../../build -L../../build 
CXXFLAGS:=$(CXXFLAGS_COMMON) $(CXXFLAGS_$(VER))

ifdef DCE
  TEST_RUNNER:=../../utils/test-runner.cc
endif
ifdef STD
  TEST_RUNNER:=dce/sources/ns-3-dce/utils/test-runner.cc
endif

PWD:=$(shell pwd)
$(info PWD=$(PWD))

ifdef DCE
    LD_LIBRARY_PATH:=$(LD_LIBRARY_PATH):$(PWD)/dce/source/ns-3-dce/build/lib
    LD_LIBRARY_PATH:=$(LD_LIBRARY_PATH):$(PWD)/dce/source/ns-3-dce/build/bin
    LD_LIBRARY_PATH:=$(LD_LIBRARY_PATH):$(PWD)/dce/source/ns-3-dce/build/bin_dce
    LD_LIBRARY_PATH:=$(LD_LIBRARY_PATH):$(PWD)/dce/build/lib
    LD_LIBRARY_PATH:=$(LD_LIBRARY_PATH):$(PWD)/dce/build/sbin
    LD_LIBRARY_PATH:=$(LD_LIBRARY_PATH):$(PWD)/dce/build/bin_dce
    LD_LIBRARY_PATH:=$(LD_LIBRARY_PATH):$(PWD)/dce/build/bin
    $(info LD_LIBRARY_PATH=$(LD_LIBRARY_PATH))
    DCE_PATH:=$(DCE_PATH):$(PWD)/dce/source/ns-3-dce/build/lib
    DCE_PATH:=$(DCE_PATH):$(PWD)/dce/source/ns-3-dce/build/bin
    DCE_PATH:=$(DCE_PATH):$(PWD)/dce/source/ns-3-dce/build/bin_dce
    DCE_PATH:=$(DCE_PATH):$(PWD)/dce/build/lib
    DCE_PATH:=$(DCE_PATH):$(PWD)/dce/biuld/sbin
    DCE_PATH:=$(DCE_PATH):$(PWD)/dce/build/bin_dce
    DCE_PATH:=$(DCE_PATH):$(PWD)/dce/build/bin
    $(info DCE_PATH=$(DCE_PATH))
    DCE_ROOT:=$(PWD)/dce/source/ns-3-dce/build:$(PWD)/dce/build
    $(info DCE_ROOT=$(DCE_ROOT))
    PYTHONPATH:=
endif

ifdef STD
    LD_LIBRARY_PATH:=$(LD_LIBRARY_PATH):../build
    DCE_PATH:=
    DCE_ROOT:=
    PYTHONPATH:=../../build/bindings/python:../../src/visualizer:../../../pybindgen-0.16.0.825 
endif

NS_LOG_STD=WifiBase=*:EunetMobile=*:CsmaInternetNode=*:CsmaNode=*:EunetMobileTest=*
NS_LOG_DCE=
#define NS_LOG
#NS_LOG="NamedRouters=**:EunetRouters=**:EunetRouter=**:SimpleRouter=**:BridgingAp=**:SimpleAp=**:NamedSwitches=**:EunetSwitch=**:EunetSwitches=**:EunetTerminal=**:EunetTerminals=**:CsmaNode=debug:OnOffApplication=info:CsmaChannelNode=debug:CsmaInternetNode=**:PacketSinkNode=debug:OnOffNode=**:SimpleSwitch=**"
#endef


EXECENV:=LD_LIBRARY_PATH=$(LD_LIBRARY_PATH) DCE_PATH=$(DCE_PATH) DCE_ROOT=$(DCE_ROOT) PYTHONPATH=$(PYTHONPATH) NS_LOG=$(NS_LOG_$(VER))
$(info EXECENV=$(EXECENV))

SOPREFIX317:=libns3.17-
SOPREFIXDEV:=libns3-dev-

#keep alphabetical order
NS3LIBS_STD=\
    $(SOPREFIXDEV)applications-debug.$(SOSUFFIX) \
    $(SOPREFIXDEV)bridge-debug.$(SOSUFFIX) \
    $(SOPREFIXDEV)buildings-debug.$(SOSUFFIX) \
    $(SOPREFIXDEV)config-store-debug.$(SOSUFFIX) \
    $(SOPREFIXDEV)core-debug.$(SOSUFFIX) \
    $(SOPREFIXDEV)csma-debug.$(SOSUFFIX) \
    $(SOPREFIXDEV)csma-layout-debug.$(SOSUFFIX) \
    $(SOPREFIXDEV)dsr-debug.$(SOSUFFIX) \
    $(SOPREFIXDEV)energy-debug.$(SOSUFFIX) \
    $(SOPREFIXDEV)flow-monitor-debug.$(SOSUFFIX) \
    $(SOPREFIXDEV)internet-debug.$(SOSUFFIX) \
    $(SOPREFIXDEV)lte-debug.$(SOSUFFIX) \
    $(SOPREFIXDEV)mesh-debug.$(SOSUFFIX) \
    $(SOPREFIXDEV)mpi-debug.$(SOSUFFIX) \
    $(SOPREFIXDEV)netanim-debug.$(SOSUFFIX) \
    $(SOPREFIXDEV)network-debug.$(SOSUFFIX) \
    $(SOPREFIXDEV)point-to-point-debug.$(SOSUFFIX) \
    $(SOPREFIXDEV)stats-debug.$(SOSUFFIX) \
    $(SOPREFIXDEV)olsr-debug.$(SOSUFFIX) \
    $(SOPREFIXDEV)propagation-debug.$(SOSUFFIX) \
    $(SOPREFIXDEV)tools-debug.$(SOSUFFIX) \
    $(SOPREFIXDEV)wifi-debug.$(SOSUFFIX) \
    $(SOPREFIXDEV)mobility-debug.$(SOSUFFIX) \
    $(SOPREFIXDEV)spectrum-debug.$(SOSUFFIX) \
    $(SOPREFIXDEV)uan-debug.$(SOSUFFIX) \
    $(SOPREFIXDEV)virtual-net-device-debug.$(SOSUFFIX) \
    $(SOPREFIXDEV)visualizer-debug.$(SOSUFFIX) \
    $(SOPREFIXDEV)wimax-debug.$(SOSUFFIX) \
    $(SOPREFIXDEV)test-debug.$(SOSUFFIX) \
    $(SOPREFIXDEV)tools-test-debug.$(SOSUFFIX) \

# keep alphabetical order
SOPREFIX=$(SOPREFIXDEV)
NS3LIBS_DCE=\
    $(SOPREFIXDEV)antenna-debug.$(SOSUFFIX) \
    $(SOPREFIXDEV)applications-debug.$(SOSUFFIX) \
    $(SOPREFIXDEV)bridge-debug.so \
    $(SOPREFIXDEV)buildings-debug.$(SOSUFFIX) \
    $(SOPREFIXDEV)config-store-debug.$(SOSUFFIX) \
    $(SOPREFIXDEV)core-debug.so \
    $(SOPREFIXDEV)csma-debug.$(SOSUFFIX) \
    $(SOPREFIXDEV)csma-layout-debug.$(SOSUFFIX) \
    $(SOPREFIXDEV)energy-debug.$(SOSUFFIX) \
    $(SOPREFIXDEV)flow-monitor-debug.$(SOSUFFIX) \
    $(SOPREFIXDEV)internet-debug.so \
    $(SOPREFIXDEV)lte-debug.$(SOSUFFIX) \
    $(SOPREFIXDEV)netanim-debug.$(SOSUFFIX) \
    $(SOPREFIXDEV)network-debug.so \
    $(SOPREFIXDEV)mobility-debug.$(SOSUFFIX) \
    $(SOPREFIXDEV)mpi-debug.$(SOSUFFIX) \
    $(SOPREFIXDEV)point-to-point-debug.$(SOSUFFIX) \
    $(SOPREFIXDEV)propagation-debug.$(SOSUFFIX) \
    $(SOPREFIXDEV)spectrum-debug.$(SOSUFFIX) \
    $(SOPREFIXDEV)stats-debug.so \
    $(SOPREFIXDEV)uan-debug.$(SOSUFFIX) \
    $(SOPREFIXDEV)virtual-net-device-debug.$(SOSUFFIX) \
    $(SOPREFIXDEV)wifi-debug.$(SOSUFFIX) \
    $(SOPREFIXDEV)wimax-debug.$(SOSUFFIX) \
    libns3-dce.so libns3-dce-quagga.so \
    libns3-netlink.so

TESTS_COMMON= \
    SimpleApTest.o \
    EunetTerminalTest.o \
    EunetTerminalsTest.o \
    EunetSwitchesTest.o \
    EunetSwitchTest.o 

TESTS_STD= \
    EunetMobileTest.o 

TESTS_DCE= \
    EunetRouterTest.o 

OBJS_COMMON:= \
    NamedSwitches.o EunetSwitch.o EunetSwitches.o \
    EunetTerminal.o EunetTerminals.o CsmaNode.o CsmaChannelNode.o \
    CsmaInternetNode.o PacketSinkNode.o OnOffNode.o SimpleSwitch.o 

OBJS_STD:= \
    SimpleAp.o BridgingAp.o \
    WifiBase.o MobilityBase.o EunetMobile.o

OBJS_DCE:= \
    NamedRouters.o EunetRouter.o SimpleRouter.o EunetRouters.o

libeunet.a : $(OBJS_COMMON) $(OBJS_$(VER))
	ar r $@ $^

        
build-visualize: EunetSwitchTest.o libeunet.a $(NS3LIBS) visualize.cc
	g++ -o $@ $(CXXFLAGS) $^

run-visualize:
	$(EXECENV) ./visualize --SimulatorImplementationType=ns3::VisualSimulatorImpl

gmon.out: EunetSwitchTest
	$(EXECENV) ./EunetSwitchTest

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

test-runner: $(TEST_RUNNER) $(NS3LIBS_$(VER)) $(TESTS_$(VER)) libeunet.a 
	g++ -o $@ $(CXXFLAGS) $^

test: test-runner
	$(EXECENV) ./test-runner --stop-on-failure
	#$(EXECENV) $(NS_LOG) ./test-runner --verbose --xml --tempdir=testpy-output/2014-01-06-04-35-10-CUT --out=process-manager.xml

#build this target first to use DCE feature
install-dce-quagga: build-dce-quagga test-dce-quagga copy-shared-library copy-include-files

build-dce-quagga:
	sh build-dce-quagga.sh

run-dce-quagga:
	#$(EXECENV) dce/build/bin/test-runner --test-name=process-manager --stop-on-failure --fullness=QUICK --verbose
	#(cd dce/source/ns-3-dce; ./test.py -s process-manager --verbose)
	$(EXECENV) dce/build/bin/test-runner --verbose
	$(EXECENV) dce/build/bin/dce-quagga-ospfd 

test-dce-quagga:
	(cd dce/source/ns-3-dev; ./test.py)
	-(cd dce/source/ns-3-dce; ./test.py)

copy-from-dce-build: copy-shared-library copy-include-files

copy-shared-library:
	-mkdir libs/
	cp dce/build/lib/*.so libs/

copy-include-files:
	-mkdir -p include/ns3
	cp dce/build/include/ns3/*.h include/ns3/
	cp dce/build/include/ns3-dev/ns3/*.h include/ns3/

