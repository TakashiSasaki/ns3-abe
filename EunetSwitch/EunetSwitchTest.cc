#include <iostream>
#include <fstream>
#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/applications-module.h"
#include "ns3/bridge-module.h"
#include "ns3/csma-module.h"
#include "ns3/internet-module.h"
#include "EunetSwitches.h"

//using namespace ns3;
NS_LOG_COMPONENT_DEFINE ("EunetSwitchTest");

int main(int argc, char *argv[]) {
	//EunetTerminal eunet_terminal;
	EunetSwitch eunet_switch;
	//EunetSwitches eunet_switches(3, 2);
	//LogComponentEnable ("EunetSwitchTest", LOG_LEVEL_INFO);
	//CommandLine command_line;
	//command_line.AddValue("nDownlinkPorts", "number of downlink ports on a switch", nDownlinkPorts);
	//command_line.AddValue("nSwitches", "number of switches", nSwitches);
	//command_line.Parse(argc, argv);

	//on_off_applications.Start(Seconds(1.0));
	//on_off_applications.Stop(Seconds(10.0));


#if 0
	NS_LOG_INFO ("Run Simulation.");
	Simulator::Run();
	Simulator::Destroy();
	NS_LOG_INFO ("Done.");
#endif

	return EXIT_SUCCESS;
}//main

