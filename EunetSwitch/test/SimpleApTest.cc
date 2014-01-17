#define NS3_LOG_ENABLE 1
#include "ns3/log.h"
NS_LOG_COMPONENT_DEFINE("SimpleApTest");
#define NS3_ASSERT_ENABLE 1
#include "ns3/assert.h"
#include "ns3/test.h"
#include "ns3/simulator.h"
#include "SimpleAp.h"

class SimpleApTestCase: public ns3::TestCase {
public:
	SimpleApTestCase() :
		ns3::TestCase("SimpleApTestCase") {
	}
	virtual ~SimpleApTestCase() {
	}

private:
	virtual void DoRun(void) {
		ns3::ObjectFactory object_factory;
		object_factory.SetTypeId("SimpleAp");
		auto simple_ap = object_factory.Create<SimpleAp> ();
		simple_ap->setSsid(ns3::Ssid("eunet"));
		auto simple_ap_2 = object_factory.Create<SimpleAp> ();
		simple_ap_2->setSsid(ns3::Ssid("eunet"));
		NS_LOG_INFO("Run Simulation.");
		ns3::Simulator::Stop(ns3::Seconds(0.1));
		ns3::Simulator::Run();
		ns3::Simulator::Destroy();
		NS_LOG_INFO("Done.");
	}
};

class SimpleApTestSuite: public ns3::TestSuite {
public:
	SimpleApTestSuite() :
		ns3::TestSuite("SimpleAp", UNIT) {
		AddTestCase(new SimpleApTestCase, ns3::TestCase::QUICK);
	}
};

static SimpleApTestSuite simple_ap_test_suite;
