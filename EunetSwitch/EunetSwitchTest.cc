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
#include "EunetSwitches.h"
#include "EunetTerminals.h"
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
	NS_ASSERT(ptr_csma_node->GetNDevices()==1);

	object_factory.SetTypeId("EunetTerminal");
	ns3::Ptr<EunetTerminal> ptr_eunet_terminal(object_factory.Create<
			EunetTerminal> ());
	NS_ASSERT(ptr_eunet_terminal->GetNDevices()==1);

	ns3::Ptr<EunetTerminal> ptr_eunet_terminal_2(object_factory.Create<
			EunetTerminal> ());
	NS_ASSERT(ptr_eunet_terminal_2->GetNDevices()==1);

	ns3::ObjectFactory object_factory_2;
	object_factory_2.SetTypeId("EunetTerminal");
	ns3::Ptr<EunetTerminal> ptr_eunet_terminal_3(object_factory_2.Create<
			EunetTerminal> ());
	NS_ASSERT(ptr_eunet_terminal_3->GetNDevices()==1);
}

void testEunetTerminals() {
	EunetTerminals eunet_terminals(3);
	eunet_terminals.bringAtoB(1, 0);
	eunet_terminals.bringAtoB(2, 0);
	eunet_terminals.assignAddresses();
	eunet_terminals.setRemoteOfAtoB(0, 0);
	eunet_terminals.setRemoteOfAtoB(1, 0);
	eunet_terminals.setRemoteOfAtoB(2, 0);
}

int main(int argc, char *argv[]) {
	ns3::ObjectFactory object_factory;
	object_factory.SetTypeId("EunetSwitch");
	ns3::Ptr<EunetSwitch> eunet_switch(object_factory.Create<EunetSwitch> ());
	eunet_switch->getTerminals().assignAddresses();
	eunet_switch->getTerminals().setRemoteOfAtoB(0, 0);
	eunet_switch->getTerminals().setRemoteOfAtoB(1, 0);
	eunet_switch->getTerminals().Get(1)->startAt(ns3::Seconds(0.0));
	//EunetTerminals eunet_terminals;

	//ns3::Node node;
	//testEunetSwitch();
	//testEunetTerminals();
	//EunetSwitches eunet_switches(3, 2);
	//LogComponentEnable ("EunetSwitchTest", LOG_LEVEL_INFO);
	//CommandLine command_line;
	//command_line.AddValue("nDownlinkPorts", "number of downlink ports on a switch", nDownlinkPorts);
	//command_line.AddValue("nSwitches", "number of switches", nSwitches);
	//command_line.Parse(argc, argv);

	//on_off_applications.Start(Seconds(1.0));
	//on_off_applications.Stop(Seconds(10.0));

	NS_LOG_INFO ("Run Simulation.");
	ns3::Simulator::Stop(ns3::Seconds(0.1));
	ns3::Simulator::Run();
	ns3::Simulator::Destroy();
	NS_LOG_INFO ("Done.");
	eunet_switch->getTerminals().logTotalRx();
	//eunet_terminals.logTotalRx();

	//NS_LOG_INFO("received " << eunet_terminals.getEunetTerminal(0)->getTotalRx());
	return EXIT_SUCCESS;
}//main
