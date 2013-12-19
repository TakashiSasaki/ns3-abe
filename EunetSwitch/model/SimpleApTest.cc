#define NS3_LOG_ENABLE 1
#include "ns3/log.h"
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
		SimpleAp simple_ap;
		ns3::Simulator::Run();
		ns3::Simulator::Destroy();
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
