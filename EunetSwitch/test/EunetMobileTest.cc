#define NS3_LOG_ENABLE 1
#include "ns3/log.h"
NS_LOG_COMPONENT_DEFINE("EunetMobileTest");
#define NS3_ASSERT_ENABLE 1
#include "ns3/assert.h"
#include "ns3/test.h"
#include "ns3/simulator.h"
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
		auto eunet_mobile_1 = object_factory.Create<EunetMobile> ();
		eunet_mobile_1->setSsid(ns3::Ssid("eunet"));
		auto eunet_mobile_2 = object_factory.Create<EunetMobile> ();
		eunet_mobile_2->setSsid(ns3::Ssid("eunet"));

		ns3::Ipv4Address ipv4_address("10.0.0.0");
		ns3::Ipv4Mask ipv4_mask("255.0.0.0");
		ns3::Ipv4AddressHelper ipv4_address_helper(ipv4_address, ipv4_mask);

		auto ptr_wifi_net_device = eunet_mobile_1->getNetDevice<
				ns3::WifiNetDevice> (0);
		NS_ASSERT(ptr_wifi_net_device != 0);
		NS_LOG_INFO(ptr_wifi_net_device->GetInstanceTypeId());
		NS_ASSERT(ptr_wifi_net_device->GetInstanceTypeId() == ns3::WifiNetDevice::GetTypeId());

		{
			auto device1 = eunet_mobile_1->getNetDevice<ns3::WifiNetDevice> (0);
			auto device2 = eunet_mobile_2->getNetDevice<ns3::WifiNetDevice> (0);
			eunet_mobile_1->assignAddress(device1, ipv4_address_helper);
			eunet_mobile_2->assignAddress(device2, ipv4_address_helper);
		}

		//eunet_mobile_1->startAt(ns3::Seconds(0.0));
		//eunet_mobile_1->stopAt(ns3::Seconds(10.0));
		{
			auto device = eunet_mobile_1->getNetDevice<ns3::WifiNetDevice> (0);
			auto address = eunet_mobile_1->getAddress(device);
			eunet_mobile_1->setRemote(address);
		}

		NS_ASSERT(eunet_mobile_2->getTotalRx()==0);

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

		NS_LOG_INFO("Run Simulation.");
		ns3::Simulator::Stop(ns3::Seconds(10.1));
		ns3::Simulator::Run();
		ns3::Simulator::Destroy();
		NS_ASSERT(eunet_mobile_2->getTotalRx()>0);
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

