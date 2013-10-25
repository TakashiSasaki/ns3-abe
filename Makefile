build: run-wifi-multihop-test

help:
	@echo To run all scripts, just type "'make run'".

build-wifi-buffer-test:
	../waf build wifi-buffer-test

run: run-wifi-buffer-test

run-wifi-buffer-test:
	../waf --run wifi-buffer-test

run-wifi-phy-test:
	../waf --run wifi-phy-test

run-collision_sample:
	../waf --run collision_sample

run-wifi-multihop-test:
	rm -rf Debug/
	../waf --run "wifi-multihop-test --lambda=1 --sim_count=1"

hello-gprof:
	rm gmon.out
	g++ -o hello -pg -g -O0 hello.cc
	./hello
	gprof hello -p

