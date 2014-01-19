#include <memory>
#include <sstream>
#define NS3_LOG_ENABLE 1
#include "ns3/log.h"
NS_LOG_COMPONENT_DEFINE("EunetTest");
#define NS3_ASSERT_ENABLE 1
#include "ns3/assert.h"
#include "Eunet.h"

using namespace ns3;

class EunetTestCase: public TestCase {
	static const double stopTime = 10.0;
public:
	EunetTestCase() :
		ns3::TestCase("EunetTestCase") {
	}
	virtual ~EunetTestCase() {
	}

private:
	virtual void DoRun(void);
};

void EunetTestCase::DoRun() {
	Eunet eunet;

	eunet.addEunetSwitch("キャンパス間接続L2", 4, 64, ns3::DataRate("10Gbps"),
			ns3::DataRate("1Gbps"));

	Simulator::Stop(Seconds(this->stopTime));
	Simulator::Run();
	Simulator::Destroy();
}

class EunetTestSuite: public TestSuite {
public:
	EunetTestSuite() :
		ns3::TestSuite("EunetTestSuite", UNIT) {
		AddTestCase(new EunetTestCase, TestCase::QUICK);
	}
};

static EunetTestSuite eunet_test_suite;
