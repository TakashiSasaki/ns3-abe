include ../CommonMakefile

gmon.out: HelloNsLog
	$(EXECENV) ./HelloNsLog

HelloNsLog: HelloNsLog.o $(NS3LIBS)
	g++ -g -O0 -o $@ $^ 

HelloNsLog.E.cc: HelloNsLog.cc 
	g++ -g -O0 -E -I../../build -o $@ $^ 

HelloNsLog.o: HelloNsLog.cc
	g++ -g -O0 -c -o $@ $^ 

gdb: HelloNsLog
	$(EXECENV) NS_LOG="*" gdb ./HelloNsLog

print-list: HelloNsLog
	# When print-list is set in environment variable NS_LOG, out main function does not run
	$(EXECENV) NS_LOG="print-list" ./HelloNsLog


