#include <iostream>
#include <fstream>
#define NS3_LOG_ENABLE 1
#include "ns3/log.h"
NS_LOG_COMPONENT_DEFINE ("EunetRouterTest");
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
public:
	EunetRouterTestCase() :
		ns3::TestCase("EunetRouterTestCase") {
	}
	virtual ~EunetRouterTestCase() {
		NS_LOG_DEBUG("destructor called.");
	}

private:
	virtual void DoRun(void);
};

void EunetRouterTestCase::DoRun() {
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
	auto ptr_eunet_router_1 = ns3::CreateObject<EunetRouter>();
	auto ptr_eunet_router_2 = ns3::CreateObject<EunetRouter>();
	NS_ASSERT(ptr_eunet_router_1 != 0 && ptr_eunet_router_2 != 0);

	Ipv4AddressHelper ipv4_address_helper;
	ipv4_address_helper.SetBase("10.0.1.0", "255.255.255.0");
	ptr_eunet_router_1->assignAddress<ns3::CsmaNetDevice> (ipv4_address_helper,
			0);
	ptr_eunet_router_2->assignAddress<ns3::CsmaNetDevice> (ipv4_address_helper,
			0);

	ptr_eunet_router_1->enableOspf(0);
	ptr_eunet_router_1->enablePcap(0);
	ptr_eunet_router_2->enableOspf(0);
	ptr_eunet_router_2->enablePcap(0);

	//ns3::PacketMetadata::Enable();
	//ptr_eunet_router_1->getTerminals().assignAddresses();
	//ptr_eunet_router_1->getTerminals().setRemoteOfAtoB(0, 0);
	//ptr_eunet_router_1->getTerminals().setRemoteOfAtoB(1, 0);
	//ptr_eunet_router_1->getTerminals().Get(1)->startAt(ns3::Seconds(0.0));

	NS_LOG_INFO("Run Simulation.");
	ns3::Simulator::Stop(ns3::Seconds(10.0));
	ns3::Simulator::Run();
	ns3::Simulator::Destroy();
	//NS_LOG_INFO("Done.");
	//eunet_router->getTerminals().logTotalRx();
}

class EunetRouterTestSuite: public ns3::TestSuite {
public:
	EunetRouterTestSuite() :
		ns3::TestSuite("EunetRouterTestSuite", UNIT) {
		AddTestCase(new EunetRouterTestCase, ns3::TestCase::QUICK);
	}
};

static EunetRouterTestSuite eunet_router_test_suite;

