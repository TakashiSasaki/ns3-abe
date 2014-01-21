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
#include "EunetMobile.h"
#include "SimpleAp.h"

class EunetMobileTestCase: public ns3::TestCase {
public:
	EunetMobileTestCase() :
		ns3::TestCase("EunetMobileTestCase") {
		//NS_LOG_UNCOND("constructing a test case");
	}
	virtual ~EunetMobileTestCase() {
	}

private:
	virtual void DoRun(void) {
		ns3::PacketMetadata::Enable();

		ns3::ObjectFactory object_factory;
		object_factory.SetTypeId("EunetMobile");
		object_factory.Set("onOffStartTime", ns3::TimeValue(ns3::Seconds(0)));
		object_factory.Set("onOffStopTime", ns3::TimeValue(ns3::Seconds(10)));
		ns3::Config::SetDefault("ns3::WifiMac::Ssid", ns3::StringValue("eunet"));

		auto node1 = object_factory.Create<EunetMobile> ();
		auto node2 = object_factory.Create<EunetMobile> ();
		node1->Initialize();
		node2->Initialize();
		auto device1 = node1->getNetDevice<ns3::WifiNetDevice> (0);
		NS_ASSERT(device1 != NULL);
		auto device2 = node2->getNetDevice<ns3::WifiNetDevice> (0);
		NS_ASSERT(device2 != NULL);

		ns3::Ipv4Address ipv4_address("10.0.0.0");
		ns3::Ipv4Mask ipv4_mask("255.0.0.0");
		ns3::Ipv4AddressHelper ipv4_address_helper(ipv4_address, ipv4_mask);

		NS_LOG_DEBUG("abc");
		{
			ns3::Ptr<ns3::WifiNetDevice> device1 = node1->getNetDevice<
					ns3::WifiNetDevice> (0);
			NS_ASSERT(device1 != NULL);
			ns3::Ptr<ns3::WifiNetDevice> device2 = node2->getNetDevice<
					ns3::WifiNetDevice> (0);
			NS_ASSERT(device2 != NULL);

			ns3::Ptr<ns3::YansWifiChannel> channel1 =
					device1->GetChannel()->GetObject<ns3::YansWifiChannel> ();
			ns3::Ptr<ns3::YansWifiChannel> channel2 =
					device2->GetChannel()->GetObject<ns3::YansWifiChannel> ();

			NS_LOG_INFO(device2->GetPhy()->GetChannel()->GetId());
			channel1->Add(device2->GetPhy()->GetObject<ns3::YansWifiPhy> ());
			NS_LOG_INFO(device2->GetPhy()->GetChannel()->GetId());
			device2->GetPhy()->GetObject<ns3::YansWifiPhy> ()->SetChannel(
					channel1);
			NS_LOG_INFO(device2->GetPhy()->GetChannel()->GetId());

			node1->assignAddress(device1, ipv4_address_helper);
			node2->assignAddress(device2, ipv4_address_helper);
			auto address1 = node1->getAddress(device1);
			NS_LOG_INFO("node " << node1->GetId() << " has address " << address1);
			auto address2 = node2->getAddress(device2);
			NS_LOG_INFO("node " << node2->GetId() << " has address " << address2);

			node1->setRemote(address2);
		}

		node1->enablePcap(device1);
		node2->enablePcap(device2);

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

		NS_LOG_INFO("Run Simulation.");
		ns3::Simulator::Stop(ns3::Seconds(100.1));
		ns3::Simulator::Run();
		ns3::Simulator::Destroy();
		NS_ASSERT_MSG(node1->getTotalTxBytes()>10000, node1->getTotalTxBytes());
		NS_ASSERT_MSG(node2->getTotalRx()>10000, node2->getTotalRx());
		NS_LOG_INFO("Done.");
	}
};

class EunetMobileTestSuite: public ns3::TestSuite {
public:
	EunetMobileTestSuite() :
		ns3::TestSuite("EunetMobileTestSuite", UNIT) {
		//NS_LOG_UNCOND("adding a test case");
		AddTestCase(new EunetMobileTestCase, ns3::TestCase::QUICK);
	}
};

static EunetMobileTestSuite eunet_mobile_test_suite;

