EunetTerminalTestSuite: test-runner
	$(EXECENV) ./test-runner --suite=$@ --verbose --test-type=performance

SimpleSwitchTestSuite: test-runner
	$(EXECENV) ./test-runner --suite=$@ --verbose

EunetRouterTestSuite: test-runner
	$(EXECENV) ./test-runner --suite=$@ --verbose 

WifiTestSuite: test-runner
	#$(EXECENV) ./test-runner --suite=$@ --verbose --test-type=performance 
	$(EXECENV) ./test-runner --suite=$@ --verbose  

DceQuaggaOspfdTestSuite: test-runner
	echo run --suite=$@ --verbose > gdbinit
	#$(EXECENV) ./test-runner --suite=$@ --verbose --test-type=performance 
	$(EXECENV) ./test-runner --suite=$@ --verbose  
	#$(EXECENV) gdb ./test-runner --command=gdbinit 

EunetMobileTestSuite: test-runner
	echo run --suite=$@ --verbose > gdbinit
	#$(EXECENV) gdb ./test-runner --command=gdbinit 
	$(EXECENV) ./test-runner --suite=$@ --verbose --test-type=performance

EunetTestSuite: test-runner
	echo run --suite=$@ --verbose > gdbinit
	#$(EXECENV) gdb ./test-runner -q --command=gdbinit 
	$(EXECENV) ./test-runner --suite=$@ --test-type=unit

EunetTestSuiteVisual: test-runner
	echo run --suite=$@ --verbose > gdbinit
	#$(EXECENV) gdb ./test-runner -q --command=gdbinit 
	$(EXECENV) ./test-runner --suite=EunetTestSuite --test-type=performance
