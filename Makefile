build: build-wifi-buffer-test

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


