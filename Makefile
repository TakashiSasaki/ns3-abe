help:
	@echo To run all scripts, just type "'make run'".

run: run-wifi-phy-test

run-wifi-phy-test:
	../waf --run wifi-phy-test

run-collision_sample:
	../waf --run collision_sample


