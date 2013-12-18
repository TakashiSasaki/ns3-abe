/*!
 @mainpage

 EunetSwitchTest.cc shows some simple usage of EunetSwitches class.
 If you need any assistance, contact the author.

 @author Takashi SASAKI
 @email takashi316@gmail.com
 */
#include <iostream>
#include <fstream>
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
#include "EunetSwitches.h"
#include "EunetTerminals.h"
#include "SimpleAp.h"
//using namespace ns3;
NS_LOG_COMPONENT_DEFINE ("EunetSwitchTest");

void testEunetTerminal() {
	ns3::ObjectFactory object_factory;

	object_factory.SetTypeId("ns3::Node");
	//ns3::Ptr<ns3::Node> ptr_node (object_factory.Create<ns3::Node>());
	ns3::Ptr<ns3::Node> ptr_node(object_factory.Create<ns3::Node> ());

	ns3::InternetStackHelper internet_stack_helper;
	internet_stack_helper.Install(ptr_node);

	object_factory.SetTypeId("CsmaNode");
	ns3::Ptr<CsmaNode> ptr_csma_node(object_factory.Create<CsmaNode> ());
	internet_stack_helper.Install(ptr_csma_node);
	NS_ASSERT(ptr_csma_node->GetNDevices() == 1);

	object_factory.SetTypeId("EunetTerminal");
	ns3::Ptr<EunetTerminal> ptr_eunet_terminal(object_factory.Create<
			EunetTerminal> ());
	NS_ASSERT(ptr_eunet_terminal->GetNDevices() == 1);

	ns3::Ptr<EunetTerminal> ptr_eunet_terminal_2(object_factory.Create<
			EunetTerminal> ());
	NS_ASSERT(ptr_eunet_terminal_2->GetNDevices() == 1);

	ns3::ObjectFactory object_factory_2;
	object_factory_2.SetTypeId("EunetTerminal");
	ns3::Ptr<EunetTerminal> ptr_eunet_terminal_3(object_factory_2.Create<
			EunetTerminal> ());
	NS_ASSERT(ptr_eunet_terminal_3->GetNDevices() == 1);

	NS_LOG_INFO("Run Simulation.");
	ns3::Simulator::Stop(ns3::Seconds(0.1));
	ns3::Simulator::Run();
	ns3::Simulator::Destroy();
	NS_LOG_INFO("Done.");
}

void testEunetTerminals() {
	//ns3::GlobalValue::Bind("SimulatorImplementationType", ns3::StringValue(
	//"ns3::VisualSimulatorImpl"));
	EunetTerminals eunet_terminals(3);
	eunet_terminals.bringAtoB(1, 0);
	eunet_terminals.bringAtoB(2, 0);
	eunet_terminals.assignAddresses();
	eunet_terminals.setRemoteOfAtoB(0, 0);
	eunet_terminals.setRemoteOfAtoB(1, 0);
	eunet_terminals.setRemoteOfAtoB(2, 0);
	eunet_terminals.Get(0)->startAt(ns3::Seconds(0.0));
	eunet_terminals.Get(1)->startAt(ns3::Seconds(0.0));
	ns3::AnimationInterface animation_interface("EunetTerminals.xml");
	NS_LOG_INFO("Run Simulation.");
	ns3::Simulator::Stop(ns3::Seconds(10.0));
	ns3::Simulator::Run();
	ns3::Simulator::Destroy();
	NS_LOG_INFO("Done.");
}

void testEunetSwitch() {
	ns3::ObjectFactory object_factory;
	object_factory.SetTypeId("EunetSwitch");
	ns3::Ptr<EunetSwitch> eunet_switch(object_factory.Create<EunetSwitch> ());
	eunet_switch->getTerminals().assignAddresses();
	eunet_switch->getTerminals().setRemoteOfAtoB(0, 0);
	eunet_switch->getTerminals().setRemoteOfAtoB(1, 0);
	eunet_switch->getTerminals().Get(1)->startAt(ns3::Seconds(0.0));
	NS_LOG_INFO("Run Simulation.");
	ns3::Simulator::Stop(ns3::Seconds(0.1));
	ns3::Simulator::Run();
	ns3::Simulator::Destroy();
	NS_LOG_INFO("Done.");
	eunet_switch->getTerminals().logTotalRx();
}

void testEunetSwitches() {
	EunetSwitches eunet_switches(3, 2);
	auto source_switch = eunet_switches.getEunetSwitch(2, 3);
	auto source_terminal = source_switch->getTerminal(5);
	auto dest_switch = eunet_switches.getEunetSwitch(0, 0);
	auto dest_terminal = dest_switch->getTerminal(5);
	source_terminal->setRemote(dest_terminal);
	source_terminal->startAt(ns3::Seconds(0.0));
	source_switch->enableAsciiTraceDownlink(5);
	source_switch->enablePcapDownlink(5);
	dest_switch->enableAsciiTraceDownlink(5);
	dest_switch->enablePcapDownlink(5);
	//ns3::CsmaHelper csma_helper;
	//csma_helper.EnableAsciiAll("a");
	ns3::AnimationInterface animation_interface("EunetSwitch.xml");
	NS_LOG_INFO("Run Simulation.");
	ns3::Simulator::Stop(ns3::Seconds(0.1));
	ns3::Simulator::Run();
	ns3::Simulator::Destroy();
	NS_LOG_INFO("Done.");
	source_terminal->logTotalRx();
	dest_terminal->logTotalRx();
}

void testSimpleAp() {
	NS_LOG_UNCOND("creating instances of SimpleAp");
	ns3::ObjectFactory object_factory;
	object_factory.SetTypeId("SimpleAp");
	auto simple_ap = object_factory.Create<SimpleAp> ();
	simple_ap->setSsid(ns3::Ssid("eunet"));
	NS_LOG_UNCOND("done.");
	NS_LOG_INFO("Run Simulation.");
	ns3::Simulator::Stop(ns3::Seconds(0.1));
	ns3::Simulator::Run();
	ns3::Simulator::Destroy();
	NS_LOG_INFO("Done.");
}

int main(int argc, char *argv[]) {
	//LogComponentEnable ("EunetSwitchTest", LOG_LEVEL_INFO);
	ns3::CommandLine command_line;
	std::string test;
	command_line.AddValue("scenario", "name of test scenario", test);
	command_line.Parse(argc, argv);
	if (test == "EunetSwitches") {
		testEunetSwitches();
	} else if (test == "EunetTerminals") {
		testEunetTerminals();
	} else if (test == "SimpleAp") {
		testSimpleAp();
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
	return EXIT_SUCCESS;
}//main
