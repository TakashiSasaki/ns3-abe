#include "ns3/network-module.h"
#include "ns3/core-module.h"
#include "ns3/internet-module.h"
#include "ns3/dce-module.h"
#include "ns3/quagga-helper.h"
#include "ns3/point-to-point-helper.h"
#include "ns3/csma-helper.h"
#include "SimpleSwitch.h"

using namespace ns3;
NS_LOG_COMPONENT_DEFINE ("SimpleSwitchTest");

class SimpleSwitchTestCase: public TestCase {
public:
	SimpleSwitchTestCase() :
		ns3::TestCase("SimpleSwitchTestCase") {
		//NS_LOG_UNCOND("constructing a test case");
	}
	virtual ~SimpleSwitchTestCase() {
	}

private:
	virtual void DoRun(void);
}; //class SimpleSwitchTestCase

// Parameters
uint32_t nNodes = 2;
uint32_t stopTime = 20;

void SimpleSwitchTestCase::DoRun() {
	auto ptr_simple_switch = ns3::CreateObject<SimpleSwitch>();
	ptr_simple_switch->SetAttribute("nDownlinkPorts", ns3::UintegerValue(48));
	ptr_simple_switch->SetAttribute("nUplinkPorts", ns3::UintegerValue(4));
	ptr_simple_switch->SetAttribute("uplinkDataRate",
			ns3::StringValue("10Gbps"));
	ptr_simple_switch->SetAttribute("downlinkDataRate", ns3::StringValue(
			"1Gbps"));
	ptr_simple_switch->Initialize();
	Simulator::Stop(Seconds(10.0));
	Simulator::Run();
	Simulator::Destroy();
}//DceQuaggaOspfdTest::DoRun

class SimpleSwitchTestSuite: public TestSuite {
public:
	SimpleSwitchTestSuite() :
		ns3::TestSuite("SimpleSwitchTestSuite", UNIT) {
		//NS_LOG_UNCOND("adding a test case");
		AddTestCase(new SimpleSwitchTestCase(), TestCase::QUICK);
	}
};

static SimpleSwitchTestSuite simple_switch_test_suite;
