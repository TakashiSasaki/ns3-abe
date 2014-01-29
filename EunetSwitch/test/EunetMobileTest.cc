#define NS3_LOG_ENABLE 1
#include "ns3/log.h"
NS_LOG_COMPONENT_DEFINE("EunetMobileTest");
#define NS3_ASSERT_ENABLE 1
#include "ns3/assert.h"
#include "ns3/test.h"
#include "ns3/simulator.h"
#include "ns3/config.h"
#include "ns3/string.h"
#include "ns3/wifi-net-device.h"
#include "ns3/yans-wifi-helper.h"
#include "ns3/yans-wifi-phy.h"
#include "ns3/global-value.h"
#include "EunetMobile.h"
#include "SimpleAp.h"
#include "WifiDevice.h"

class EunetMobileTestCase: public ns3::TestCase {
	const bool isVisual;
public:
	EunetMobileTestCase(const bool is_visual = false) :
		ns3::TestCase("EunetMobileTestCase"), isVisual(is_visual) {
		//NS_LOG_UNCOND("constructing a test case");
	}
	virtual ~EunetMobileTestCase() {
	}

private:
	virtual void DoRun(void) {
		if (this->isVisual) {
			NS_LOG_DEBUG("--SimulatorImplementationType=ns3::VisualSimulatorImpl");
			ns3::GlobalValue::Bind("SimulatorImplementationType",
					ns3::StringValue("ns3::VisualSimulatorImpl"));
		}//if

		ns3::PacketMetadata::Enable();

		ns3::ObjectFactory object_factory;
		object_factory.SetTypeId("EunetMobile");
		object_factory.Set("onOffStartTime", ns3::TimeValue(ns3::Seconds(0)));
		object_factory.Set("onOffStopTime", ns3::TimeValue(ns3::Seconds(10)));
		object_factory .Set("wifiMacType",
				ns3::StringValue("ns3::AdhocWifiMac"));
		ns3::Config::SetDefault("ns3::WifiMac::Ssid", ns3::StringValue("eunet"));

		auto node1 = object_factory.Create<EunetMobile> ();
		auto node2 = object_factory.Create<EunetMobile> ();
		node1->Initialize();
		node2->Initialize();
		auto device1 = node1->getDevice<WifiDevice> (0);
		NS_ASSERT(device1 != NULL);
		auto device2 = node2->getDevice<WifiDevice> (0);
		NS_ASSERT(device2 != NULL);

		{
			NS_ASSERT(node1->getInt() == 23456);
		}

		ns3::Ipv4Address ipv4_address("10.0.0.0");
		ns3::Ipv4Mask ipv4_mask("255.0.0.0");
		ns3::Ipv4AddressHelper ipv4_address_helper(ipv4_address, ipv4_mask);

		NS_LOG_DEBUG("abc");
		{
			ns3::Ptr<WifiDevice> device1 = node1->getDevice<WifiDevice> (0);
			NS_ASSERT(device1 != NULL);
			ns3::Ptr<WifiDevice> device2 = node2->getDevice<WifiDevice> (0);
			NS_ASSERT(device2 != NULL);

			node2->joinTo(node1);

			node1->assignAddress(device1, ipv4_address_helper);
			node2->assignAddress(device2, ipv4_address_helper);
			auto address1 = node1->getAddress(device1);
			NS_LOG_INFO("node " << node1->GetId() << " has address " << address1);
			auto address2 = node2->getAddress(device2);
			NS_LOG_INFO("node " << node2->GetId() << " has address " << address2);

			node1->setRemote(address2);
		}

		device1->enablePcap();
		device2->enablePcap();

		ns3::YansWifiPhyHelper phy_helper;
		phy_helper.EnablePcapAll("aaaaa");

		NS_ASSERT_MSG(node2->getTotalRx()==0, node2->getTotalRx());
#if 0
		object_factory.SetTypeId("SimpleAp");
		auto simple_ap = object_factory.Create<SimpleAp> ();
		simple_ap->setSsid(ns3::Ssid("eunet"));
		simple_ap->bringWifiBase(*eunet_mobile_1);
		simple_ap->bringWifiBase(*eunet_mobile_2);
		NS_LOG_INFO(simple_ap);

		eunet_mobile_1->logAllDevices();
		eunet_mobile_2->logAllDevices();
		simple_ap->logAllDevices();

		//NS_LOG_INFO(eunet_mobile);
#endif

		node1->setPosition(ns3::Vector(10, 10, 10));
		node2->setPosition(ns3::Vector(20, 20, 20));

		NS_LOG_INFO("Run Simulation.");
		ns3::Simulator::Stop(ns3::Seconds(100.1));
		ns3::Simulator::Run();
		ns3::Simulator::Destroy();
		NS_ASSERT_MSG(node1->getTotalTxBytes()>10, node1->getTotalTxBytes());
		NS_ASSERT_MSG(node2->getTotalRx()>10, node2->getTotalRx());
		NS_ASSERT_MSG (node1->getTotalTxBytes()==node2->getTotalRx(), node1->getTotalTxBytes() << " "<<node2->getTotalRx() );
		NS_ASSERT_MSG (node1->getTotalTxPackets()==node2->getTotalRxPackets(), node1->getTotalTxPackets() << " "<<node2->getTotalRxPackets() );
	}
};

class ApStaTestCase: public ns3::TestCase {
	const bool isVisual;
public:
	ApStaTestCase(const bool is_visual = false) :
		ns3::TestCase("ApStaTestCase"), isVisual(is_visual) {
	}
	virtual ~ApStaTestCase() {
	}

private:
	virtual void DoRun(void) {
		if (this->isVisual) {
			NS_LOG_DEBUG("--SimulatorImplementationType=ns3::VisualSimulatorImpl");
			ns3::GlobalValue::Bind("SimulatorImplementationType",
					ns3::StringValue("ns3::VisualSimulatorImpl"));
		}//if

		ns3::PacketMetadata::Enable();

		ns3::ObjectFactory object_factory;
		object_factory.SetTypeId("EunetMobile");
		object_factory.Set("onOffStartTime", ns3::TimeValue(ns3::Seconds(0)));
		object_factory.Set("onOffStopTime", ns3::TimeValue(ns3::Seconds(10)));
		object_factory .Set("wifiMacType", ns3::StringValue("ns3::StaWifiMac"));
		ns3::Config::SetDefault("ns3::WifiMac::Ssid", ns3::StringValue("eunet"));

		auto node1 = object_factory.Create<EunetMobile> ();
		auto node2 = object_factory.Create<EunetMobile> ();
		node1->Initialize();
		node2->Initialize();
		auto device1 = node1->getDevice<WifiDevice> (0);
		NS_ASSERT(device1 != NULL);
		auto device2 = node2->getDevice<WifiDevice> (0);
		NS_ASSERT(device2 != NULL);

		ns3::Ipv4Address ipv4_address("10.0.0.0");
		ns3::Ipv4Mask ipv4_mask("255.0.0.0");
		ns3::Ipv4AddressHelper ipv4_address_helper(ipv4_address, ipv4_mask);

		{
			ns3::Ptr<WifiDevice> device1 = node1->getDevice<WifiDevice> (0);
			NS_ASSERT(device1 != NULL);
			ns3::Ptr<WifiDevice> device2 = node2->getDevice<WifiDevice> (0);
			NS_ASSERT(device2 != NULL);

			node2->joinTo(node1);

			node1->assignAddress(device1, ipv4_address_helper);
			node2->assignAddress(device2, ipv4_address_helper);
			auto address1 = node1->getAddress(device1);
			NS_LOG_INFO("node " << node1->GetId() << " has address " << address1);
			auto address2 = node2->getAddress(device2);
			NS_LOG_INFO("node " << node2->GetId() << " has address " << address2);

			node1->setRemote(address2);
		}

		device1->enablePcap();
		device2->enablePcap();

		ns3::YansWifiPhyHelper phy_helper;
		phy_helper.EnablePcapAll("aaaaa");

		NS_ASSERT_MSG(node2->getTotalRx()==0, node2->getTotalRx());

		node1->setPosition(ns3::Vector(10, 10, 10));
		node2->setPosition(ns3::Vector(20, 20, 20));

		object_factory.Set("wifiMacType", ns3::StringValue("ns3::ApWifiMac"));
		auto node3 = object_factory.Create<EunetMobile> ();
		node3->Initialize();
		node3->setPosition(ns3::Vector(30, -30, 30));

		node1->joinTo(node3);
		node2->joinTo(node3);

		NS_LOG_INFO("Run Simulation.");
		ns3::Simulator::Stop(ns3::Seconds(100.1));
		ns3::Simulator::Run();
		ns3::Simulator::Destroy();
		NS_ASSERT_MSG(node1->getTotalTxBytes()>10, node1->getTotalTxBytes());
		NS_ASSERT_MSG(node2->getTotalRx()>10, node2->getTotalRx());
		NS_ASSERT_MSG(node1->getTotalTxBytes()==node2->getTotalRx(), node1->getTotalTxBytes() << "," << node2->getTotalRx());
	}
};

class EunetMobileTestSuite: public ns3::TestSuite {
public:
	EunetMobileTestSuite(ns3::TestSuite::Type type) :
		ns3::TestSuite("EunetMobileTestSuite", type) {
		switch (type) {
		case UNIT:
			AddTestCase(new EunetMobileTestCase, ns3::TestCase::QUICK);
			AddTestCase(new ApStaTestCase, ns3::TestCase::QUICK);
			break;
		case PERFORMANCE:
			AddTestCase(new EunetMobileTestCase(true), ns3::TestCase::QUICK);
			AddTestCase(new ApStaTestCase(true), ns3::TestCase::QUICK);
			break;
		default:
			break;
		}
	}

};

static EunetMobileTestSuite eunet_mobile_test_suite(ns3::TestSuite::UNIT);
static EunetMobileTestSuite eunet_mobile_test_suite_visual(
		ns3::TestSuite::PERFORMANCE);

