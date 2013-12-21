#include <cstdlib>
#include "ns3/command-line.h"
#include "ns3/simulator.h"
int main(int argc, char *argv[]) {
	//LogComponentEnable ("EunetSwitchTest", LOG_LEVEL_INFO);
	ns3::CommandLine command_line;
	//std::string test;
	//command_line.AddValue("scenario", "name of test scenario", test);
	command_line.Parse(argc, argv);
#if 0
	if (test == "EunetSwitches") {
		testEunetSwitches();
	} else if (test == "EunetTerminals") {
		testEunetTerminals();
	} else {
		NS_LOG_UNCOND("");
		NS_LOG_UNCOND("Usage:");
		NS_LOG_UNCOND(" EunetSwitchTest --scenario=<ScenarioName>");
		NS_LOG_UNCOND("");
		NS_LOG_UNCOND("Scenario name:");
		NS_LOG_UNCOND(
				" testEunetSwitches: sample scenario for EunetSwitches class");
		NS_LOG_UNCOND("");
	}
#endif
	ns3::Simulator::Stop(ns3::Seconds(0.1));
	ns3::Simulator::Run();
	ns3::Simulator::Destroy();
	return EXIT_SUCCESS;
}//main
