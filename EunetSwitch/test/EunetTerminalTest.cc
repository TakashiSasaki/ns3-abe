#define NS3_LOG_ENABLE 1
#include "ns3/log.h"
NS_LOG_COMPONENT_DEFINE("EunetTerminalTest");
#include "ns3/test.h"
#include "ns3/simulator.h"
#include "ns3/internet-stack-helper.h"
#include "EunetTerminal.h"

class EunetTerminalTestCase: public ns3::TestCase {
public:
	EunetTerminalTestCase() :
		ns3::TestCase("EunetTerminalTestCase") {
		NS_LOG_UNCOND("constructing a test case");
	}
	virtual ~EunetTerminalTestCase() {
	}

private:
	virtual void DoRun(void) {
		ns3::ObjectFactory object_factory;

		object_factory.SetTypeId("ns3::Node");
		//ns3::Ptr<ns3::Node> ptr_node (object_factory.Create<ns3::Node>());
		ns3::Ptr<ns3::Node> ptr_node(object_factory.Create<ns3::Node> ());

		ns3::InternetStackHelper internet_stack_helper;
		internet_stack_helper.Install(ptr_node);

		object_factory.SetTypeId("CsmaNode");
		ns3::Ptr<CsmaNode> ptr_csma_node(object_factory.Create<CsmaNode> ());
		internet_stack_helper.Install(ptr_csma_node);
		NS_ASSERT(ptr_csma_node->GetNDevices() == 1);

		object_factory.SetTypeId("EunetTerminal");
		ns3::Ptr<EunetTerminal> ptr_eunet_terminal(object_factory.Create<
				EunetTerminal> ());
		NS_ASSERT(ptr_eunet_terminal->GetNDevices() == 1);

		ns3::Ptr<EunetTerminal> ptr_eunet_terminal_2(object_factory.Create<
				EunetTerminal> ());
		NS_ASSERT(ptr_eunet_terminal_2->GetNDevices() == 1);

		ns3::ObjectFactory object_factory_2;
		object_factory_2.SetTypeId("EunetTerminal");
		ns3::Ptr<EunetTerminal> ptr_eunet_terminal_3(object_factory_2.Create<
				EunetTerminal> ());
		NS_ASSERT(ptr_eunet_terminal_3->GetNDevices() == 1);

		NS_LOG_INFO("Run Simulation.");
		ns3::Simulator::Stop(ns3::Seconds(0.1));
		ns3::Simulator::Run();
		ns3::Simulator::Destroy();
		NS_LOG_INFO("Done.");
	}//DoRun
};

class EunetTerminalTestSuite: public ns3::TestSuite {
public:
	EunetTerminalTestSuite() :
		ns3::TestSuite("EunetTerminal", UNIT) {
		NS_LOG_UNCOND("adding a test case");
		AddTestCase(new EunetTerminalTestCase, ns3::TestCase::QUICK);
	}
};

static EunetTerminalTestSuite eunet_terminal_test_suite;

