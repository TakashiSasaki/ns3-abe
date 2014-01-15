#define NS3_LOG_ENABLE 1
#include "ns3/log.h"
NS_LOG_COMPONENT_DEFINE ("SimpleSwitchTest");
#define NS3_ASSERT_ENABLE 1
#include "ns3/assert.h"
#include "ns3/network-module.h"
#include "ns3/core-module.h"
#include "ns3/internet-module.h"
#include "ns3/dce-module.h"
#include "ns3/quagga-helper.h"
#include "ns3/point-to-point-helper.h"
#include "ns3/csma-helper.h"
#include "SimpleSwitch.h"

using namespace ns3;

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
	NS_LOG_UNCOND(ptr_simple_switch->getNDevices<ns3::CsmaNetDevice>());
	ptr_simple_switch->Initialize();
	NS_ASSERT(ptr_simple_switch->getNDevices<ns3::CsmaNetDevice>() == 52);

	ns3::ObjectFactory object_factory;
	object_factory.SetTypeId(SimpleSwitch::GetTypeId());
	object_factory.Set("nDownlinkPorts", ns3::UintegerValue(48));
	object_factory.Set("nUplinkPorts", ns3::UintegerValue(4));
	object_factory.Set("uplinkDataRate", ns3::StringValue("10Gbps"));
	object_factory.Set("downlinkDataRate", ns3::StringValue("1Gbps"));
	ns3::Ptr<SimpleSwitch> ptr_simple_switch_1 = object_factory.Create<
			SimpleSwitch> ();
	NS_ASSERT(48==ptr_simple_switch_1->getNDownlinkPorts());
	NS_ASSERT(4==ptr_simple_switch_1->getNUplinkPorts());
	//NS_ASSERT_MSG(52 == ptr_simple_switch_1->getNPorts(), "getNports() " << ptr_simple_switch_1->getNPorts());
	ptr_simple_switch_1->Initialize();
	NS_ASSERT(ptr_simple_switch_1->getNDevices<ns3::CsmaNetDevice>() == 52);
	auto ptr_simple_switch_2 = object_factory.Create<SimpleSwitch> ();
	ptr_simple_switch_2->Initialize();
	NS_ASSERT(ptr_simple_switch_2->getNDevices<ns3::CsmaNetDevice>() == 52);

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
