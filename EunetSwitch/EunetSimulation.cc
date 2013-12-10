#define NS3_LOG_ENABLE 1
#include "ns3/log.h"
#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/applications-module.h"
#include "ns3/bridge-module.h"
#include "ns3/csma-module.h"
#include "ns3/internet-module.h"
#include "ns3/internet-stack-helper.h"
#include "ns3/netanim-module.h"
#include "EunetSimulation.h"
#include "EunetSwitches.h"
#include "EunetTerminal.h"
#include "NamedSwitches.h"
NS_LOG_COMPONENT_DEFINE ("EunetSimulation");

EunetSimulation::EunetSimulation() {
	ns3::AnimationInterface animation_interface("EunetSimulation.xml");
	NamedSwitches named_switches("133.71.0.0", "255.255.0.0");
	named_switches.addEunetSwitch("dpc_04_1_sw01", 48);
	named_switches.findEunetSwitch("dpc_04_1_sw01")->setUplinkDataRate(
			ns3::DataRate("10Gbps"));
	named_switches.addEunetSwitch("dpc_02_01_sw02", 32);
	named_switches.findEunetSwitch("dpc_04_1_sw01")->connectUpTo(
			"dpc_02_01_sw02");
}

EunetSimulation::~EunetSimulation() {
}

int EunetSimulation::run() {
	NS_LOG_INFO("Run Simulation.");
	ns3::Simulator::Stop(ns3::Seconds(0.1));
	ns3::Simulator::Run();
	ns3::Simulator::Destroy();
	NS_LOG_INFO("Done.");
	//this->sourceTerminal->logTotalRx();
	//this->destTerminal->logTotalRx();
	return EXIT_SUCCESS;
}

int main(int argc, char** argv) {
	ns3::CommandLine command_line;
	command_line.Parse(argc, argv);
	EunetSimulation eunet_simulation;
	auto r = eunet_simulation.run();
	NS_LOG_UNCOND("EunetSimulation finished.");
	return r;
}
