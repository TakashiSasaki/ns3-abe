#include <iostream>
#define NS3_LOG_ENABLE 1
#include "ns3/log.h"
NS_LOG_COMPONENT_DEFINE ("Sandbox");
#define NS3_ASSERT_ENABLE 1
#include "ns3/assert.h"
#include "assert.h"
#include "ns3/network-module.h"
#include "ns3/core-module.h"
#include "ns3/internet-module.h"
#include "ns3/dce-module.h"
#include "ns3/quagga-helper.h"
#include "ns3/point-to-point-helper.h"
#include "ns3/csma-helper.h"
#include "ns3/csma-net-device.h"

using namespace ns3;

class SandboxTestCase: public TestCase {
public:
	SandboxTestCase() :
		ns3::TestCase("SandboxTestCase") {
	}
	virtual ~SandboxTestCase() {
	}

private:
	virtual void DoRun(void);
};

class B1 {
	virtual std::string getName() = 0;
public:
	void greet() {
		std::cout << "hello " << getName() << std::endl;
	}
};

class B2 {
	virtual std::string getName() = 0;
public:
	void shout() {
		std::cout << getName() << "!!!!" << std::endl;
	}
};

class D: public B1, public B2 {
	virtual std::string getName() {
		return "John";
	}
};

void SandboxTestCase::DoRun() {
	D d;
	d.shout();
	d.greet();
}

class SandboxTestSuite: public TestSuite {
public:
	SandboxTestSuite() :
		ns3::TestSuite("SandboxTestSuite", UNIT) {
		AddTestCase(new SandboxTestCase, TestCase::QUICK);
	}
};

static SandboxTestSuite sandbox_test_suite;
