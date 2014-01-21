#include <iostream>
#include <fstream>
#define NS3_LOG_ENABLE 1
#include "ns3/log.h"
NS_LOG_COMPONENT_DEFINE ("EunetRouterTest");
#define NS3_ASSERT_ENABLE 1
#include "ns3/assert.h"
#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/applications-module.h"
#include "ns3/bridge-module.h"
#include "ns3/csma-module.h"
#include "ns3/internet-module.h"
#include "ns3/internet-stack-helper.h"
#include "ns3/point-to-point-helper.h"
#include "ns3/dce-application-helper.h"
#include "EunetSwitches.h"
#include "EunetTerminals.h"
#include "SimpleAp.h"
#include "EunetRouter.h"
//using namespace ns3;

class EunetRouterTestCase: public ns3::TestCase {
	bool isVisual;
public:
	EunetRouterTestCase(const bool is_visual = false) :
		ns3::TestCase("EunetRouterTestCase"), isVisual(is_visual) {
	}
	virtual ~EunetRouterTestCase() {
	}

private:
	virtual void DoRun(void);
};

void EunetRouterTestCase::DoRun() {
	if (this->isVisual) {
		NS_LOG_DEBUG("--SimulatorImplementationType=ns3::VisualSimulatorImpl");
		ns3::GlobalValue::Bind("SimulatorImplementationType", ns3::StringValue(
				"ns3::VisualSimulatorImpl"));
	}//if
	NS_LOG_INFO("creating Node via CreateObject");
	auto ptr_node = ns3::CreateObject<Node>();
	NS_ASSERT(ptr_node != 0);

	NS_LOG_INFO("creating CsmaNode via ObjectFactory");
	auto object_factory = ns3::ObjectFactory();
	object_factory.SetTypeId(CsmaNode::GetTypeId());
	//auto ptr_csma_node = ns3::CreateObject<CsmaNode>();
	auto ptr_csma_node = object_factory.Create();
	NS_ASSERT(ptr_csma_node != 0);

	NS_LOG_INFO("creating CsmaChannelNode via ObjectFactory");
	//auto ptr_csma_channel_node = ns3::CreateObject<CsmaChannelNode>();
	object_factory.SetTypeId(CsmaChannelNode::GetTypeId());
	auto ptr_csma_channel_node = object_factory.Create();
	NS_ASSERT(ptr_csma_channel_node != 0);

	NS_LOG_INFO("creating SimpleRouter via CreateObject");
	auto ptr_simple_router = ns3::CreateObject<SimpleRouter>();
	NS_ASSERT(ptr_simple_router != 0);

	NS_LOG_DEBUG("creating EunetRouter via CreateObject");
	object_factory.SetTypeId(EunetRouter::GetTypeId());
	object_factory.Set("nPorts", ns3::UintegerValue(2));
	auto ptr_eunet_router_1 = object_factory.Create<EunetRouter> ();
	NS_ASSERT_MSG(ptr_eunet_router_1->getNDevices<ns3::CsmaNetDevice>() == 2, ptr_eunet_router_1->getNDevices<ns3::CsmaNetDevice>());
	NS_ASSERT_MSG(ptr_eunet_router_1->getNDevices<ns3::LoopbackNetDevice>() == 1, ptr_eunet_router_1->getNDevices<ns3::LoopbackNetDevice>());
	ptr_eunet_router_1->Initialize();
	NS_ASSERT_MSG(ptr_eunet_router_1->getNDevices<ns3::CsmaNetDevice>() == 2, ptr_eunet_router_1->getNDevices<ns3::CsmaNetDevice>());

	auto ptr_eunet_router_2 = ns3::CreateObject<EunetRouter>();
	ptr_eunet_router_2->Initialize();
	NS_ASSERT(ptr_eunet_router_1 != 0 && ptr_eunet_router_2 != 0);

	Ipv4AddressHelper ipv4_address_helper;
	ipv4_address_helper.SetBase("10.0.1.0", "255.255.255.0");
	{
		auto ptr_csma_net_device = ptr_eunet_router_1->getNetDevice<
				ns3::CsmaNetDevice> (0);
		ptr_eunet_router_1->assignAddress(ptr_csma_net_device,
				ipv4_address_helper);
	}
	//ptr_eunet_router_1->assignAddress<ns3::CsmaNetDevice> (ipv4_address_helper,
	//		1);
	{
		auto p = ptr_eunet_router_1->getNetDevice<ns3::CsmaNetDevice> (1);
		ptr_eunet_router_1->assignAddress(p, ns3::Ipv4Address("0.0.0.0"),
				ns3::Ipv4Mask("255.255.255.255"));
	}
	{
		auto ptr_ipv4 = ptr_eunet_router_1->GetObject<ns3::Ipv4> ();
		NS_ASSERT_MSG(ptr_ipv4 != 0, ptr_ipv4);
		ns3::Ptr<ns3::CsmaNetDevice> ptr_device =
				ptr_eunet_router_1->getNetDevice<ns3::CsmaNetDevice> (1);
		NS_LOG_DEBUG(ptr_device);
		auto i_interface = ptr_ipv4->GetInterfaceForDevice(ptr_device);
		auto n_addresses = ptr_ipv4->GetNAddresses(i_interface);
		for (unsigned i = 0; i < n_addresses; ++i) {
			auto ipv4_interface_address = ptr_ipv4->GetAddress(i_interface, i);
			NS_LOG_DEBUG(ipv4_interface_address);
		}
	}

	{
		auto ptr_csma_net_device = ptr_eunet_router_2->getNetDevice<
				ns3::CsmaNetDevice> (0);
		ptr_eunet_router_2->assignAddress(ptr_csma_net_device,
				ipv4_address_helper);
	}

	{
		auto device1 = ptr_eunet_router_1->getNetDevice<ns3::CsmaNetDevice> ();
		auto device2 = ptr_eunet_router_2->getNetDevice<ns3::CsmaNetDevice> ();
		ptr_eunet_router_1->enableOspf(device1);
		ptr_eunet_router_1->enablePcap(device1);
		ptr_eunet_router_2->enableOspf(device2);
		ptr_eunet_router_2->enablePcap(device2);
	}

	//ns3::PacketMetadata::Enable();
	//ptr_eunet_router_1->getTerminals().assignAddresses();
	//ptr_eunet_router_1->getTerminals().setRemoteOfAtoB(0, 0);
	//ptr_eunet_router_1->getTerminals().setRemoteOfAtoB(1, 0);
	//ptr_eunet_router_1->getTerminals().Get(1)->startAt(ns3::Seconds(0.0));

	NS_LOG_INFO("Run Simulation.");
	ns3::Simulator::Stop(ns3::Seconds(60.0));
	ns3::Simulator::Run();
	ns3::Simulator::Destroy();
	//NS_LOG_INFO("Done.");
	//eunet_router->getTerminals().logTotalRx();
}

class EunetRouterTestSuite: public ns3::TestSuite {
public:
	EunetRouterTestSuite() :
		ns3::TestSuite("EunetRouterTestSuite", UNIT) {
		const char* p_ns_visual = getenv("NS_VISUAL");
		if (p_ns_visual == NULL) {
			AddTestCase(new EunetRouterTestCase, ns3::TestCase::QUICK);
		} else {
			AddTestCase(new EunetRouterTestCase(true),
					ns3::TestCase::TAKES_FOREVER);
		}//if
	}// the constructor
};

static EunetRouterTestSuite eunet_router_test_suite;

