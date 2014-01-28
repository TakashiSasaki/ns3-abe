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
#include "ns3/test.h"
#include "SimpleSwitch.h"

using namespace ns3;

class SimpleSwitchTestCase: public TestCase {
public:
	SimpleSwitchTestCase() :
		ns3::TestCase("SimpleSwitchTestCase") {
	}
	virtual ~SimpleSwitchTestCase() {
	}

private:
	virtual void DoRun(void);
}; //class SimpleSwitchTestCase

void SimpleSwitchTestCase::DoRun() {
	ns3::Ptr<SimpleSwitch> sw;
	{
		sw = ns3::CreateObject<SimpleSwitch>();
		sw->SetAttribute("nDownlinkPorts", ns3::UintegerValue(48));
		sw->SetAttribute("nUplinkPorts", ns3::UintegerValue(4));
		sw->SetAttribute("uplinkDataRate", ns3::StringValue("10Gbps"));
		sw->SetAttribute("downlinkDataRate", ns3::StringValue("1Gbps"));
		NS_LOG_UNCOND(sw->getNDevices<CsmaDevice>());
		sw->Initialize();
		NS_ASSERT_MSG(sw->getNDevices<CsmaDevice>() == 1, sw->getNDevices<CsmaDevice>());
		NS_ASSERT_MSG(sw->getNDevices<DownlinkDevice>() == 48, sw->getNDevices<DownlinkDevice>());
		NS_ASSERT_MSG(sw->getNDevices<UplinkDevice>() == 4, sw->getNDevices<UplinkDevice>());
	}
	{
		auto ptr_csma_net_device = sw->getUnusedPort<CsmaDevice> ();
		NS_ASSERT(ptr_csma_net_device != NULL);
	}

	ns3::Ptr<SimpleSwitch> sw1, sw2;
	ns3::ObjectFactory object_factory;
	object_factory.SetTypeId(SimpleSwitch::GetTypeId());
	object_factory.Set("nDownlinkPorts", ns3::UintegerValue(48));
	object_factory.Set("nUplinkPorts", ns3::UintegerValue(4));
	object_factory.Set("uplinkDataRate", ns3::StringValue("10Gbps"));
	object_factory.Set("downlinkDataRate", ns3::StringValue("1Gbps"));
	sw1 = object_factory.Create<SimpleSwitch> ();
	ns3::UintegerValue uv_uplink_ports;
	sw1 ->GetAttribute("nDownlinkPorts", uv_uplink_ports);
	NS_ASSERT(48==uv_uplink_ports.Get());
	ns3::UintegerValue uv_downlink_ports;
	sw1->GetAttribute("nUplinkPorts", uv_downlink_ports);
	NS_ASSERT(4==uv_downlink_ports.Get());
	//NS_ASSERT_MSG(52 == ptr_simple_switch_1->getNPorts(), "getNports() " << ptr_simple_switch_1->getNPorts());
	sw1->Initialize();
	NS_ASSERT_MSG(sw1->getNDevices<CsmaDevice>() == 1, sw1->getNDevices<CsmaDevice>());
	NS_ASSERT_MSG(sw1->getNDevices<UplinkDevice>() == 4, sw1->getNDevices<CsmaDevice>());
	NS_ASSERT_MSG(sw1->getNDevices<DownlinkDevice>() == 48, sw1->getNDevices<CsmaDevice>());
	sw2 = object_factory.Create<SimpleSwitch> ();
	sw2->Initialize();
	NS_ASSERT_MSG(sw2->getNDevices<CsmaDevice>() == 1, sw2->getNDevices<CsmaDevice>());
	NS_ASSERT_MSG(sw2->getNDevices<UplinkDevice>() == 4, sw2->getNDevices<CsmaDevice>());
	NS_ASSERT_MSG(sw2->getNDevices<DownlinkDevice>() == 48, sw2->getNDevices<CsmaDevice>());

	{
		auto device = sw1->getUnusedPort<CsmaDevice> ();
		NS_LOG_INFO(device->GetNode()->GetId() << ' '<< device->GetIfIndex());
	}
	{
		auto device = sw1->getUnusedPort<UplinkDevice> ();
		NS_LOG_INFO(device->GetNode()->GetId() << ' '<< device->GetIfIndex());
	}
	{
		auto device = sw1->getUnusedPort<DownlinkDevice> ();
		NS_LOG_INFO(device->GetNode()->GetId() << ' '<< device->GetIfIndex());
	}
	{
		auto device = sw2->getUnusedPort<CsmaDevice> ();
		NS_LOG_INFO(device->GetNode()->GetId() << ' '<< device->GetIfIndex());
	}
	{
		auto device = sw2->getUnusedPort<UplinkDevice> ();
		NS_LOG_INFO(device->GetNode()->GetId() << ' '<< device->GetIfIndex());
	}
	{
		auto device = sw2->getUnusedPort<DownlinkDevice> ();
		NS_LOG_INFO(device->GetNode()->GetId() << ' '<< device->GetIfIndex());
	}

	sw2->bring<CsmaDevice, CsmaDevice> (0, sw1, 0);

	{
		auto device = sw1->getUnusedPort<CsmaDevice> ();
		NS_ASSERT(device == NULL);
	}
	{
		auto device = sw1->getUnusedPort<UplinkDevice> ();
		NS_LOG_INFO(device->GetNode()->GetId() << ' '<< device->GetIfIndex());
	}
	{
		auto device = sw1->getUnusedPort<DownlinkDevice> ();
		NS_LOG_INFO(device->GetNode()->GetId() << ' '<< device->GetIfIndex());
	}
	{
		auto device = sw2->getUnusedPort<CsmaDevice> ();
		NS_ASSERT(device == NULL);
	}
	{
		auto device = sw2->getUnusedPort<UplinkDevice> ();
		NS_LOG_INFO(device->GetNode()->GetId() << ' '<< device->GetIfIndex());
	}
	{
		auto device = sw2->getUnusedPort<DownlinkDevice> ();
		NS_LOG_INFO(device->GetNode()->GetId() << ' '<< device->GetIfIndex());
	}

	Simulator::Stop(Seconds(10.0));
	Simulator::Run();
	Simulator::Destroy();
}//DoRun

class SimpleSwitchTestSuite: public TestSuite {
public:
	SimpleSwitchTestSuite() :
		ns3::TestSuite("SimpleSwitchTestSuite", UNIT) {
		NS_LOG_UNCOND("adding a test case");
		AddTestCase(new SimpleSwitchTestCase(), TestCase::QUICK);
	}
};

static SimpleSwitchTestSuite simple_switch_test_suite;
