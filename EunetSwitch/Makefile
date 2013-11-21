include ../CommonMakefile

gmon.out: EunetSwitchTest
	$(EXECENV) NS_LOG="EunetSwitch=**:EunetSwitches=**" ./EunetSwitchTest 

gprof: gmon.out
	$(EXECENV) gprof ./EunetSwitchTest -p -q

gdb: EunetSwitchTest
	$(EXECENV) gdb ./EunetSwitchTest 

EunetSwitchTest.cc: EunetSwitch.h

EunetSwitches.o: EunetSwitches.cc EunetSwitches.h EunetSwitch.h
	g++ -g -pg -O2 -std=c++0x -c -o EunetSwitches.o $(CPPFLAGS) EunetSwitches.cc

EunetSwitch.o: EunetSwitch.cc EunetSwitch.h
	g++ -g -pg -O2 -std=c++0x -c -o EunetSwitch.o $(CPPFLAGS) EunetSwitch.cc

EunetTerminal.o: EunetTerminal.cc EunetTerminal.h
	g++ -g -pg -O2 -std=c++0x -c -o EunetTerminal.o $(CPPFLAGS) EunetTerminal.cc

EunetSwitchTest: EunetSwitchTest.cc EunetSwitch.o EunetSwitches.o EunetTerminal.o $(NS3LIBS)
	g++ -g -pg -O2 -std=c++0x -o EunetSwitchTest $(CPPFLAGS) $^

clean:
	-rm -f gmon.out
	-rm -f EunetSwitchTest
	-rm -f *.pcap *.tr

