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
	NS_ASSERT_MSG(ptr_simple_switch->getNDevices<ns3::CsmaNetDevice>() == 1, ptr_simple_switch->getNDevices<ns3::CsmaNetDevice>());
	NS_ASSERT_MSG(ptr_simple_switch->getNDevices<DownlinkNetDevice>() == 48, ptr_simple_switch->getNDevices<DownlinkNetDevice>());
	NS_ASSERT_MSG(ptr_simple_switch->getNDevices<UplinkNetDevice>() == 4, ptr_simple_switch->getNDevices<UplinkNetDevice>());

	{
		auto ptr_csma_net_device = ptr_simple_switch->getUnusedPort<
				ns3::CsmaNetDevice> ();
		NS_ASSERT(ptr_csma_net_device != NULL);
	}

	ns3::ObjectFactory object_factory;
	object_factory.SetTypeId(SimpleSwitch::GetTypeId());
	object_factory.Set("nDownlinkPorts", ns3::UintegerValue(48));
	object_factory.Set("nUplinkPorts", ns3::UintegerValue(4));
	object_factory.Set("uplinkDataRate", ns3::StringValue("10Gbps"));
	object_factory.Set("downlinkDataRate", ns3::StringValue("1Gbps"));
	ns3::Ptr<SimpleSwitch> ptr_simple_switch_1 = object_factory.Create<
			SimpleSwitch> ();
	ns3::UintegerValue uv_uplink_ports;
	ptr_simple_switch_1 ->GetAttribute("nDownlinkPorts", uv_uplink_ports);
	NS_ASSERT(48==uv_uplink_ports.Get());
	ns3::UintegerValue uv_downlink_ports;
	ptr_simple_switch_1->GetAttribute("nUplinkPorts", uv_downlink_ports);
	NS_ASSERT(4==uv_downlink_ports.Get());
	//NS_ASSERT_MSG(52 == ptr_simple_switch_1->getNPorts(), "getNports() " << ptr_simple_switch_1->getNPorts());
	ptr_simple_switch_1->Initialize();
	NS_ASSERT_MSG(ptr_simple_switch_1->getNDevices<ns3::CsmaNetDevice>() == 1, ptr_simple_switch_1->getNDevices<ns3::CsmaNetDevice>());
	NS_ASSERT_MSG(ptr_simple_switch_1->getNDevices<UplinkNetDevice>() == 4, ptr_simple_switch_1->getNDevices<ns3::CsmaNetDevice>());
	NS_ASSERT_MSG(ptr_simple_switch_1->getNDevices<DownlinkNetDevice>() == 48, ptr_simple_switch_1->getNDevices<ns3::CsmaNetDevice>());
	auto ptr_simple_switch_2 = object_factory.Create<SimpleSwitch> ();
	ptr_simple_switch_2->Initialize();
	NS_ASSERT_MSG(ptr_simple_switch_2->getNDevices<ns3::CsmaNetDevice>() == 1, ptr_simple_switch_2->getNDevices<ns3::CsmaNetDevice>());
	NS_ASSERT_MSG(ptr_simple_switch_2->getNDevices<UplinkNetDevice>() == 4, ptr_simple_switch_2->getNDevices<ns3::CsmaNetDevice>());
	NS_ASSERT_MSG(ptr_simple_switch_2->getNDevices<DownlinkNetDevice>() == 48, ptr_simple_switch_2->getNDevices<ns3::CsmaNetDevice>());

	{
		auto ptr_unused_csma_net_device_on_switch_1_before =
				ptr_simple_switch_1->getUnusedPort<ns3::CsmaNetDevice> ();
		NS_LOG_INFO(ptr_unused_csma_net_device_on_switch_1_before->GetNode()->GetId() << ' '<< ptr_unused_csma_net_device_on_switch_1_before->GetIfIndex());
		auto ptr_unused_uplink_device_on_switch_1_before =
				ptr_simple_switch_1->getUnusedPort<UplinkNetDevice> ();
		NS_LOG_INFO(ptr_unused_uplink_device_on_switch_1_before->GetNode()->GetId() << ' '<< ptr_unused_uplink_device_on_switch_1_before->GetIfIndex());
		auto ptr_unused_downlink_device_on_switch_1_before =
				ptr_simple_switch_1->getUnusedPort<DownlinkNetDevice> ();
		NS_LOG_INFO(ptr_unused_downlink_device_on_switch_1_before->GetNode()->GetId() << ' '<< ptr_unused_downlink_device_on_switch_1_before->GetIfIndex());
		auto ptr_unused_csma_net_device_on_switch_2_before =
				ptr_simple_switch_2->getUnusedPort<ns3::CsmaNetDevice> ();
		NS_LOG_INFO(ptr_unused_csma_net_device_on_switch_2_before->GetNode()->GetId() << ' '<< ptr_unused_csma_net_device_on_switch_2_before->GetIfIndex());
		auto ptr_unused_uplink_device_on_switch_2_before =
				ptr_simple_switch_2->getUnusedPort<UplinkNetDevice> ();
		NS_LOG_INFO(ptr_unused_uplink_device_on_switch_2_before->GetNode()->GetId() << ' '<< ptr_unused_uplink_device_on_switch_2_before->GetIfIndex());
		auto ptr_unused_downlink_device_on_switch_2_before =
				ptr_simple_switch_2->getUnusedPort<DownlinkNetDevice> ();
		NS_LOG_INFO(ptr_unused_downlink_device_on_switch_2_before->GetNode()->GetId() << ' '<< ptr_unused_downlink_device_on_switch_2_before->GetIfIndex());
	}

	ptr_simple_switch_2->bring<ns3::CsmaNetDevice, ns3::CsmaNetDevice> (0,
			ptr_simple_switch_1, 0);

	{
		auto ptr_unused_csma_net_device_on_switch_1_after =
				ptr_simple_switch_1->getUnusedPort<ns3::CsmaNetDevice> ();
		NS_ASSERT(ptr_unused_csma_net_device_on_switch_1_after == NULL);
		auto ptr_unused_uplink_device_on_switch_1_after =
				ptr_simple_switch_1->getUnusedPort<UplinkNetDevice> ();
		NS_LOG_INFO(ptr_unused_uplink_device_on_switch_1_after->GetNode()->GetId() << ' '<< ptr_unused_uplink_device_on_switch_1_after->GetIfIndex());
		auto ptr_unused_downlink_device_on_switch_1_after =
				ptr_simple_switch_1->getUnusedPort<DownlinkNetDevice> ();
		NS_LOG_INFO(ptr_unused_downlink_device_on_switch_1_after->GetNode()->GetId() << ' '<< ptr_unused_downlink_device_on_switch_1_after->GetIfIndex());
		auto ptr_unused_csma_net_device_on_switch_2_after =
				ptr_simple_switch_2->getUnusedPort<ns3::CsmaNetDevice> ();
		NS_ASSERT(ptr_unused_csma_net_device_on_switch_2_after == NULL);
		auto ptr_unused_uplink_device_on_switch_2_after =
				ptr_simple_switch_2->getUnusedPort<UplinkNetDevice> ();
		NS_LOG_INFO(ptr_unused_uplink_device_on_switch_2_after->GetNode()->GetId() << ' '<< ptr_unused_uplink_device_on_switch_2_after->GetIfIndex());
		auto ptr_unused_downlink_device_on_switch_2_after =
				ptr_simple_switch_2->getUnusedPort<DownlinkNetDevice> ();
		NS_LOG_INFO(ptr_unused_downlink_device_on_switch_2_after->GetNode()->GetId() << ' '<< ptr_unused_downlink_device_on_switch_2_after->GetIfIndex());
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
