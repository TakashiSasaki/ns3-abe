#define NS3_LOG_ENABLE 1
#include "ns3/log.h"
NS_LOG_COMPONENT_DEFINE("WifiTest");
#define NS3_ASSERT_ENABLE 1
#include "ns3/assert.h"
#include "ns3/test.h"
#include "ns3/yans-wifi-channel.h"
#include "ns3/yans-wifi-helper.h"

class WifiTestCase: public ns3::TestCase {
	ns3::Ptr<ns3::YansWifiChannel> ptrYansWifiChannel;
public:
	WifiTestCase();
	virtual void DoRun();
	virtual ~WifiTestCase();
};//WifiTest

WifiTestCase::WifiTestCase() :
	ns3::TestCase("WifiTestCase") {
	auto wifi_channel_helper = ns3::YansWifiChannelHelper::Default();
	this->ptrYansWifiChannel = wifi_channel_helper.Create();
}
WifiTestCase::~WifiTestCase() {
}

void WifiTestCase::DoRun() {

}

class WifiTestSuite: public ns3::TestSuite {
public:
	WifiTestSuite() :
		ns3::TestSuite("WifiTestSuite", UNIT) {
		//NS_LOG_UNCOND("adding a test case");
		AddTestCase(new WifiTestCase, ns3::TestCase::QUICK);
	}
};

static WifiTestSuite wifi_test_suite;
