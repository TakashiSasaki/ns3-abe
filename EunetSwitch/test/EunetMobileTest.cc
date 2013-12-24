#define NS3_LOG_ENABLE 1
#include "ns3/log.h"
NS_LOG_COMPONENT_DEFINE("EunetMobileTest");
#include "ns3/test.h"
#include "ns3/simulator.h"
#include "EunetMobile.h"

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
		auto simple_ap = object_factory.Create<EunetMobile> ();
		simple_ap->setSsid(ns3::Ssid("eunet"));
		auto simple_ap_2 = object_factory.Create<EunetMobile> ();
		simple_ap_2->setSsid(ns3::Ssid("eunet"));
		NS_LOG_INFO("Run Simulation.");
		ns3::Simulator::Stop(ns3::Seconds(0.1));
		ns3::Simulator::Run();
		ns3::Simulator::Destroy();
		NS_LOG_INFO("Done.");
	}
};

class EunetMobileTestSuite: public ns3::TestSuite {
public:
	EunetMobileTestSuite() :
		ns3::TestSuite("EunetMobile", UNIT) {
		//NS_LOG_UNCOND("adding a test case");
		AddTestCase(new EunetMobileTestCase, ns3::TestCase::QUICK);
	}
};

static EunetMobileTestSuite eunet_mobile_test_suite;

