include ../CommonMakefile

all: difs-wifi-mac-test

run: difs-wifi-mac-test 
	@$(EXECENV) NS_LOG="*=all|prefix_func|prefix_time:*=error:Buffer=error:Object=error:ObjectBase=error" ./difs-wifi-mac-test 2>&1 | cat
	
print-list: difs-wifi-mac-test
	@$(EXECENV) ./difs-wifi-mac-test --print-list=1 2>&1 | cat

gmon.out: difs-wifi-mac-test
	$(EXECENV) ./difs-wifi-mac-test 

OutputFileStream.o : OutputFileStream.cc OutputFileStream.h
	g++ $(CPPFLAGS) -c $<

ConstantMobilityNodeContainer.o : ConstantMobilityNodeContainer.cc ConstantMobilityNodeContainer.h
	g++ $(CPPFLAGS) -c $<

WifiNodeContainer.o : WifiNodeContainer.cc WifiNodeContainer.h
	g++ $(CPPFLAGS) -c $<
	
Ipv4NodeContainer.o : Ipv4NodeContainer.cc Ipv4NodeContainer.h
	g++ $(CPPFLAGS) -c $<

difs-wifi-mac.o : difs-wifi-mac.cc difs-wifi-mac.h
	g++ $(CPPFLAGS) -c $<
	
difs-wifi-mac-test.o: difs-wifi-mac-test.cc difs-wifi-mac.h difs-wifi-mac-helper.h
	g++ $(CPPFLAGS) -c $<

difs-wifi-mac-test: difs-wifi-mac-test.o difs-wifi-mac.o ConstantMobilityNodeContainer.o WifiNodeContainer.o OutputFileStream.o Ipv4NodeContainer.o $(NS3LIBS)
	g++ $(CPPFLAGS) -o $@  $^

clean:
	rm -f *.o
	rm -f difs-wifi-mac-test
	rm -f gmon.out
	rm -f sim_out*.txt

gdb: difs-wifi-mac-test
	$(EXECENV) gdb ./difs-wifi-mac-test 

