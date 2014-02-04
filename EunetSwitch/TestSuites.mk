EunetMobileTestSuite: test-runner
	echo run --suite=$@ --verbose --test-type=unit > gdbinit
	$(EXECENV) gdb ./test-runner --command=gdbinit 
	#$(EXECENV) ./test-runner --suite=$@ --verbose --test-type=performance
	#$(EXECENV) ./test-runner --suite=$@ --verbose --test-type=unit

EunetSwitchTestSuite: test-runner
	echo handle SIGUSR1 nostop > gdbinit
	echo run --suite=$@ --verbose --test-type=unit >> gdbinit
	#$(EXECENV) gdb ./test-runner -q --command=gdbinit 
	$(EXECENV) ./test-runner --suite=$@ --verbose --test-type=unit

EunetSwitchesTestSuite: test-runner
	echo handle SIGUSR1 nostop > gdbinit
	echo run --suite=$@ --verbose --test-type=unit >> gdbinit
	#$(EXECENV) gdb ./test-runner -q --command=gdbinit 
	$(EXECENV) ./test-runner --suite=$@ --verbose --test-type=unit

EunetTerminalTestSuite: test-runner
	echo run --suite=$@ --verbose --test-type=unit > gdbinit
	$(EXECENV) gdb ./test-runner -q --command=gdbinit 
	#$(EXECENV) ./test-runner --suite=$@ --verbose --test-type=unit

EunetTerminalsTestSuite: test-runner
	echo run --suite=$@ --verbose --test-type=unit > gdbinit
	#$(EXECENV) gdb ./test-runner -q --command=gdbinit 
	$(EXECENV) ./test-runner --suite=$@ --verbose --test-type=unit

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

EunetTestSuite: test-runner
	echo run --suite=$@ --verbose > gdbinit
	#$(EXECENV) gdb ./test-runner -q --command=gdbinit 
	$(EXECENV) ./test-runner --suite=$@ --test-type=unit

EunetTestSuiteVisual: test-runner
	echo run --suite=$@ --verbose > gdbinit
	#$(EXECENV) gdb ./test-runner -q --command=gdbinit 
	$(EXECENV) ./test-runner --suite=EunetTestSuite --test-type=performance

SandboxTestSuite: test-runner
	$(EXECENV) ./test-runner --suite=$@ --test-type=unit

SimpleSwitchTestSuite: test-runner
	echo run --suite=$@ --verbose > gdbinit
	$(EXECENV) gdb ./test-runner -q --command=gdbinit 
	#$(EXECENV) ./test-runner --suite=$@ --verbose

	