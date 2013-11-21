include ../CommonMakefile

gmon.out: wifi-multihop-test
	$(EXECENV) ./$^ --lambda=1

difs-wifi-mac.o : difs-wifi-mac.cc difs-wifi-mac.h
	g++ $(CPPFLAGS) -c $<
	
difs-wifi-mac-test.o: difs-wifi-mac-test.cc difs-wifi-mac.h difs-wifi-mac-helper.h
	g++ $(CPPFLAGS) -c $<

wifi-multihop-test.o: wifi-multihop-test.cc
	g++ $(CPPFLAGS) -c $<

wifi-multihop-test: wifi-multihop-test.o difs-wifi-mac.o $(NS3LIBS)
	g++ $(CPPFLAGS) -o $@  $^

