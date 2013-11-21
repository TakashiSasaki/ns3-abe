include ../CommonMakefile

gmon.out: EunetSwitchTest
	$(EXECENV) ./EunetSwitchTest 

gprof: gmon.out
	$(EXECENV) gprof ./EunetSwitchTest -p -q

EunetSwitchTest.cc: EunetSwitch.h

EunetSwitch.o: EunetSwitch.cc EunetSwitch.h
	g++ -g -pg -O2 -std=c++0x -c -o EunetSwitch.o $(CPPFLAGS) EunetSwitch.cc

EunetSwitchTest: EunetSwitchTest.cc EunetSwitch.o $(NS3LIBS)
	g++ -g -pg -O2 -std=c++0x -o EunetSwitchTest $(CPPFLAGS) $^

clean:
	-rm -f gmon.out
	-rm -f EunetSwitchTest
	-rm -f *.pcap *.tr

