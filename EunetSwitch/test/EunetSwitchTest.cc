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
		ns3::PacketMetadata::Enable();
	}
	virtual ~EunetSwitchTestCase() {
	}

private:
	virtual void DoRun(void) {
		{
			auto ptr_node = ns3::CreateObject<ns3::Node>();
			NS_ASSERT(ptr_node->GetNDevices()==0);
		}
		ns3::Ptr<OnOffNode> on_off_node;
		{
			on_off_node = ns3::CreateObject<OnOffNode>();
			NS_ASSERT(on_off_node->GetNDevices()==2);
		}

		ns3::Ptr<EunetSwitch> sw;
		{
			ns3::ObjectFactory object_factory;
			object_factory.SetTypeId("EunetSwitch");
			sw = object_factory.Create<EunetSwitch> ();
			sw->Initialize();
			NS_ASSERT(sw->getTerminals().Get(0)->GetNDevices()==2);
			ns3::UintegerValue uv_downlink_ports;
			sw->GetAttribute("nDownlinkPorts", uv_downlink_ports);
			NS_ASSERT_MSG(uv_downlink_ports.Get() == sw->getTerminals().GetN(),
					uv_downlink_ports.Get()<< ' ' << sw->getTerminals().GetN());
			sw->getTerminals().assignAddresses();
			NS_ASSERT(sw->getTerminals().Get(0)->GetNDevices()==2);
			sw->getTerminals().setRemoteOfAtoB(0, 0);
			NS_ASSERT(sw->getTerminals().Get(0)->GetNDevices()==2);
			sw->getTerminals().setRemoteOfAtoB(1, 0);
			NS_ASSERT(sw->getTerminals().Get(0)->GetNDevices()==2);
		}

		ns3::Ptr<EunetTerminal> terminal0 = sw->getTerminal(0);
		ns3::Ptr<EunetTerminal> terminal1 = sw->getTerminal(1);
		NS_LOG_DEBUG(terminal0->getAddress(terminal0->getDevice<CsmaDevice>(0)));
		NS_LOG_DEBUG(terminal1->getAddress(terminal1->getDevice<CsmaDevice>(0)));

		ns3::Simulator::Stop(ns3::Seconds(10.0));
		NS_ASSERT(sw->getTerminals().Get(0)->GetNDevices()==2);
		ns3::Simulator::Run();
		NS_ASSERT(sw->getTerminals().Get(0)->GetNDevices()==2);
		//eunet_switch->getTerminals().logTotalRx();
		//NS_LOG_INFO(eunet_switch->getTerminals().getTotalRx() << " bytes received among all EunetTerminals");
		NS_ASSERT(on_off_node->getTotalTxPackets()>0);
		NS_ASSERT(on_off_node->getTotalTxBytes()>0);
		NS_ASSERT(sw->getTerminals().Get(0)->GetNDevices()==2);
		NS_ASSERT(terminal0->getTotalTxBytes()>0);
		NS_ASSERT(sw->getTerminals().Get(0)->getTotalTxPackets()>0);
		NS_ASSERT(sw->getTerminals().Get(1)->getTotalTxPackets()>0);
		NS_ASSERT(sw->getTerminals().Get(0)->getTotalRx() > 0);
		ns3::Simulator::Destroy();
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
