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

void SimpleSwitchTestCase::DoRun() {
	auto ptr_simple_switch = ns3::CreateObject<SimpleSwitch>();
	ptr_simple_switch->SetAttribute("nDownlinkPorts", ns3::UintegerValue(48));
	ptr_simple_switch->SetAttribute("nUplinkPorts", ns3::UintegerValue(4));
	ptr_simple_switch->SetAttribute("uplinkDataRate",
			ns3::StringValue("10Gbps"));
	ptr_simple_switch->SetAttribute("downlinkDataRate", ns3::StringValue(
			"1Gbps"));
	NS_LOG_UNCOND(ptr_simple_switch->getNDevices<CsmaDevice>());
	ptr_simple_switch->Initialize();
	NS_ASSERT_MSG(ptr_simple_switch->getNDevices<CsmaDevice>() == 1, ptr_simple_switch->getNDevices<CsmaDevice>());
	NS_ASSERT_MSG(ptr_simple_switch->getNDevices<DownlinkDevice>() == 48, ptr_simple_switch->getNDevices<DownlinkDevice>());
	NS_ASSERT_MSG(ptr_simple_switch->getNDevices<UplinkDevice>() == 4, ptr_simple_switch->getNDevices<UplinkDevice>());

	{
		auto ptr_csma_net_device =
				ptr_simple_switch->getUnusedPort<CsmaDevice> ();
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
	NS_ASSERT_MSG(ptr_simple_switch_1->getNDevices<CsmaDevice>() == 1, ptr_simple_switch_1->getNDevices<CsmaDevice>());
	NS_ASSERT_MSG(ptr_simple_switch_1->getNDevices<UplinkDevice>() == 4, ptr_simple_switch_1->getNDevices<CsmaDevice>());
	NS_ASSERT_MSG(ptr_simple_switch_1->getNDevices<DownlinkDevice>() == 48, ptr_simple_switch_1->getNDevices<CsmaDevice>());
	auto ptr_simple_switch_2 = object_factory.Create<SimpleSwitch> ();
	ptr_simple_switch_2->Initialize();
	NS_ASSERT_MSG(ptr_simple_switch_2->getNDevices<CsmaDevice>() == 1, ptr_simple_switch_2->getNDevices<CsmaDevice>());
	NS_ASSERT_MSG(ptr_simple_switch_2->getNDevices<UplinkDevice>() == 4, ptr_simple_switch_2->getNDevices<CsmaDevice>());
	NS_ASSERT_MSG(ptr_simple_switch_2->getNDevices<DownlinkDevice>() == 48, ptr_simple_switch_2->getNDevices<CsmaDevice>());

	{
		auto ptr_unused_csma_net_device_on_switch_1_before =
				ptr_simple_switch_1->getUnusedPort<CsmaDevice> ();
		NS_LOG_INFO(ptr_unused_csma_net_device_on_switch_1_before->GetNode()->GetId() << ' '<< ptr_unused_csma_net_device_on_switch_1_before->GetIfIndex());
		auto ptr_unused_uplink_device_on_switch_1_before =
				ptr_simple_switch_1->getUnusedPort<UplinkDevice> ();
		NS_LOG_INFO(ptr_unused_uplink_device_on_switch_1_before->GetNode()->GetId() << ' '<< ptr_unused_uplink_device_on_switch_1_before->GetIfIndex());
		auto ptr_unused_downlink_device_on_switch_1_before =
				ptr_simple_switch_1->getUnusedPort<DownlinkDevice> ();
		NS_LOG_INFO(ptr_unused_downlink_device_on_switch_1_before->GetNode()->GetId() << ' '<< ptr_unused_downlink_device_on_switch_1_before->GetIfIndex());
		auto ptr_unused_csma_net_device_on_switch_2_before =
				ptr_simple_switch_2->getUnusedPort<CsmaDevice> ();
		NS_LOG_INFO(ptr_unused_csma_net_device_on_switch_2_before->GetNode()->GetId() << ' '<< ptr_unused_csma_net_device_on_switch_2_before->GetIfIndex());
		auto ptr_unused_uplink_device_on_switch_2_before =
				ptr_simple_switch_2->getUnusedPort<UplinkDevice> ();
		NS_LOG_INFO(ptr_unused_uplink_device_on_switch_2_before->GetNode()->GetId() << ' '<< ptr_unused_uplink_device_on_switch_2_before->GetIfIndex());
		auto ptr_unused_downlink_device_on_switch_2_before =
				ptr_simple_switch_2->getUnusedPort<DownlinkDevice> ();
		NS_LOG_INFO(ptr_unused_downlink_device_on_switch_2_before->GetNode()->GetId() << ' '<< ptr_unused_downlink_device_on_switch_2_before->GetIfIndex());
	}

	ptr_simple_switch_2->bring<CsmaDevice, CsmaDevice> (0, ptr_simple_switch_1,
			0);

	{
		auto ptr_unused_csma_net_device_on_switch_1_after =
				ptr_simple_switch_1->getUnusedPort<CsmaDevice> ();
		NS_ASSERT(ptr_unused_csma_net_device_on_switch_1_after == NULL);
		auto ptr_unused_uplink_device_on_switch_1_after =
				ptr_simple_switch_1->getUnusedPort<UplinkDevice> ();
		NS_LOG_INFO(ptr_unused_uplink_device_on_switch_1_after->GetNode()->GetId() << ' '<< ptr_unused_uplink_device_on_switch_1_after->GetIfIndex());
		auto ptr_unused_downlink_device_on_switch_1_after =
				ptr_simple_switch_1->getUnusedPort<DownlinkDevice> ();
		NS_LOG_INFO(ptr_unused_downlink_device_on_switch_1_after->GetNode()->GetId() << ' '<< ptr_unused_downlink_device_on_switch_1_after->GetIfIndex());
		auto ptr_unused_csma_net_device_on_switch_2_after =
				ptr_simple_switch_2->getUnusedPort<CsmaDevice> ();
		NS_ASSERT(ptr_unused_csma_net_device_on_switch_2_after == NULL);
		auto ptr_unused_uplink_device_on_switch_2_after =
				ptr_simple_switch_2->getUnusedPort<UplinkDevice> ();
		NS_LOG_INFO(ptr_unused_uplink_device_on_switch_2_after->GetNode()->GetId() << ' '<< ptr_unused_uplink_device_on_switch_2_after->GetIfIndex());
		auto ptr_unused_downlink_device_on_switch_2_after =
				ptr_simple_switch_2->getUnusedPort<DownlinkDevice> ();
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
