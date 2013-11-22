include ../CommonMakefile

gmon.out: EunetSwitchTest
	$(EXECENV) NS_LOG="EunetSwitch=**:EunetSwitches=**:EunetSwitchTest=**:EunetTerminal=**:EunetTerminals=**:CsmaNode=**" ./EunetSwitchTest 

gprof: gmon.out
	$(EXECENV) gprof ./EunetSwitchTest -p -q

gdb: EunetSwitchTest
	$(EXECENV) gdb ./EunetSwitchTest 

EunetSwitchTest.cc: EunetSwitch.h

EunetSwitches.o: EunetSwitches.cc EunetSwitches.h EunetSwitch.h
	g++ -g -pg -O0 -std=c++0x -c -o EunetSwitches.o $(CPPFLAGS) EunetSwitches.cc

EunetSwitch.o: EunetSwitch.cc EunetSwitch.h
	g++ -g -pg -O0 -std=c++0x -c -o EunetSwitch.o $(CPPFLAGS) EunetSwitch.cc

EunetTerminal.o: EunetTerminal.cc EunetTerminal.h
	g++ -g -pg -O0 -std=c++0x -c -o EunetTerminal.o $(CPPFLAGS) EunetTerminal.cc

CsmaNode.o: CsmaNode.cc CsmaNode.h
	g++ -g -pg -O0 -std=c++0x -c -o CsmaNode.o $(CPPFLAGS) CsmaNode.cc

EunetTerminals.o: EunetTerminals.cc EunetTerminals.h
	g++ -g -pg -O0 -std=c++0x -c -o EunetTerminals.o $(CPPFLAGS) EunetTerminals.cc

EunetSwitchTest: EunetSwitchTest.cc EunetSwitch.o EunetSwitches.o EunetTerminal.o EunetTerminals.o CsmaNode.o $(NS3LIBS)
	g++ -g -pg -O0 -std=c++0x -o EunetSwitchTest $(CPPFLAGS) $^

clean:
	-rm -f gmon.out
	-rm -f EunetSwitchTest
	-rm -f *.pcap *.tr
	-rm -f *.o

