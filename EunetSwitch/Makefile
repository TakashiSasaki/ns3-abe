include ../CommonMakefile
vpath %.h container:model
vpath %.cc container:model:test:../../utils
.PHONY: test

CXXFLAGS=-Icontainer -Imodel -I. -I../../build -L. -g -pg -O0 -std=c++0x

#define NS_LOG
#NS_LOG="BridgingAp=**:SimpleAp=**:NamedSwitches=**:EunetSwitch=**:EunetSwitches=**:EunetTerminal=**:EunetTerminals=**:CsmaNode=debug:OnOffApplication=info:CsmaChannelNode=debug:CsmaInternetNode=**:PacketSinkNode=debug:OnOffNode=**:SimpleSwitch=**"
#endef

define NS_LOG
NS_LOG="*"
endef

libeunet.a : NamedSwitches.o EunetSwitch.o EunetSwitches.o \
			EunetTerminal.o EunetTerminals.o CsmaNode.o CsmaChannelNode.o \
			CsmaInternetNode.o PacketSinkNode.o OnOffNode.o SimpleSwitch.o \
			SimpleAp.o BridgingAp.o
	ar r $@ $^

run2: EunetSimulation
	$(EXECENV) $(NS_LOG):EunetSimulation=** ./EunetSimulation 

gdb2: EunetSimulation
	$(EXECENV) gdb ./EunetSimulation
	
visualize2: EunetSimulation 
	$(EXECENV) $(NS_LOG) ./EunetSimulation --SimulatorImplementationType=ns3::VisualSimulatorImpl

EunetSimulation: EunetSimulation.cc libeunet.a $(NS3LIBS)
	g++ -o $@ $(CXXFLAGS) $^

run: EunetSwitchTest
	$(EXECENV) $(NS_LOG):EunetSwitchTest=** ./EunetSwitchTest --scenario=SimpleAp

visualize:
	$(EXECENV) $(NS_LOG) ./EunetSwitchTest --scenario=EunetSwitches --SimulatorImplementationType=ns3::VisualSimulatorImpl

gmon.out: EunetSwitchTest
	$(EXECENV) $(NS_LOG)"EunetSwitch=**:EunetSwitches=**:EunetSwitchTest=**:EunetTerminal=**:EunetTerminals=**:CsmaNode=**" ./EunetSwitchTest 

gprof: gmon.out
	$(EXECENV) gprof ./EunetSwitchTest -p -q

gdb: EunetSwitchTest
	$(EXECENV) gdb ./EunetSwitchTest 

EunetSwitchTest: EunetSwitchTest.cc libeunet.a $(NS3LIBS)
	g++ -o $@ $(CXXFLAGS) $^

doxygen:
	doxygen
	make -C latex

clean:
	-rm -f gmon.out
	-rm -f EunetSwitchTest
	-rm -f *.pcap *.tr
	-rm -f container/*.o model/*.o test/*.o *.o
	-rm *.a

test-runner: test-runner.o $(NS3LIBS) SimpleApTest.o EunetTerminalTest.o EunetTerminalsTest.o EunetSwitchesTest.o EunetSwitchTest.o libeunet.a 
	g++ -o $@ $(CXXFLAGS) $^

test: test-runner
	$(EXECENV) ./test-runner
