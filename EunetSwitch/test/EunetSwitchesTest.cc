#define NS3_LOG_ENABLE 1
#include "ns3/log.h"
NS_LOG_COMPONENT_DEFINE("EunetSwitchesTest");
#include "ns3/test.h"
#include "ns3/simulator.h"
#include "ns3/internet-stack-helper.h"
#include "ns3/netanim-module.h"
#include "EunetSwitches.h"

class EunetSwitchesTestCase: public ns3::TestCase {
public:
	EunetSwitchesTestCase() :
		ns3::TestCase("EunetSwitchesTestCase") {
		NS_LOG_UNCOND("constructing a test case");
	}
	virtual ~EunetSwitchesTestCase() {
	}

private:
	virtual void DoRun(void) {
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
	}//DoRun
};

class ThisTestSuite: public ns3::TestSuite {
public:
	ThisTestSuite() :
		ns3::TestSuite("EunetSwitches", UNIT) {
		AddTestCase(new EunetSwitchesTestCase, ns3::TestCase::QUICK);
	}
};

static ThisTestSuite this_test_suite;

