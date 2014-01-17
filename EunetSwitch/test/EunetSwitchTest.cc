#include <iostream>
#include <fstream>
#define NS3_LOG_ENABLE 1
#include "ns3/log.h"
NS_LOG_COMPONENT_DEFINE ("EunetSwitchTest");
#define NS3_ASSERT_ENABLE 1
#include "ns3/assert.h"
#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/applications-module.h"
#include "ns3/bridge-module.h"
#include "ns3/csma-module.h"
#include "ns3/internet-module.h"
#include "ns3/internet-stack-helper.h"
#include "EunetSwitches.h"
#include "EunetTerminals.h"

class EunetSwitchTestCase: public ns3::TestCase {
public:
	EunetSwitchTestCase() :
		ns3::TestCase("EunetSwitchTestCase") {
	}
	virtual ~EunetSwitchTestCase() {
	}

private:
	virtual void DoRun(void) {
		auto ptr_node = ns3::CreateObject<ns3::Node>();
		NS_ASSERT(ptr_node->GetNDevices()==0);

		ns3::PacketMetadata::Enable();
		ns3::ObjectFactory object_factory;
		object_factory.SetTypeId("EunetSwitch");
		ns3::Ptr<EunetSwitch> eunet_switch(
				object_factory.Create<EunetSwitch> ());
		eunet_switch->Initialize();
		NS_ASSERT_MSG(eunet_switch->getNDownlinkPorts() == eunet_switch->getTerminals().GetN(),
				eunet_switch->getNDownlinkPorts()<< ' ' << eunet_switch->getTerminals().GetN());
		eunet_switch->getTerminals().assignAddresses();
		eunet_switch->getTerminals().setRemoteOfAtoB(0, 0);
		eunet_switch->getTerminals().setRemoteOfAtoB(1, 0);
		//eunet_switch->getTerminals().Get(1)->startAt(ns3::Seconds(0.0));
		NS_LOG_INFO("Run Simulation.");
		ns3::Simulator::Stop(ns3::Seconds(0.2));
		ns3::Simulator::Run();
		ns3::Simulator::Destroy();
		NS_LOG_INFO("Done.");
		//eunet_switch->getTerminals().logTotalRx();
		NS_LOG_INFO(eunet_switch->getTerminals().getTotalRx() << " bytes received over EunetTerminals");
		NS_ASSERT_MSG (eunet_switch->getTerminals().getTotalRx()==48640, eunet_switch->getTerminals().getTotalRx());
	}//DoRun
};

class EunetSwitchTestSuite: public ns3::TestSuite {
public:
	EunetSwitchTestSuite() :
		ns3::TestSuite("EunetSwitchTestSuite", UNIT) {
		AddTestCase(new EunetSwitchTestCase, ns3::TestCase::QUICK);
	}
};

static EunetSwitchTestSuite eunet_switch_test_suite;

#if 0
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
#endif
