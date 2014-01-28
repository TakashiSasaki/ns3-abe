#define NS3_LOG_ENABLE 1
#include "ns3/log.h"
NS_LOG_COMPONENT_DEFINE("EunetTerminalTest");
#define NS3_ASSERT_ENABLE 1
#include "ns3/assert.h"
#include "ns3/test.h"
#include "ns3/simulator.h"
#include "ns3/internet-stack-helper.h"
#include "ns3/loopback-net-device.h"
#include "ns3/global-value.h"
#include "ns3/string.h"
#include "EunetTerminal.h"

class EunetTerminalTestCase: public ns3::TestCase {
	const bool isVisual;
public:
	EunetTerminalTestCase(const bool is_visual = false) :
		ns3::TestCase("EunetTerminalTestCase"), isVisual(is_visual) {
		//NS_LOG_UNCOND("constructing a test case");
	}
	virtual ~EunetTerminalTestCase() {
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

		object_factory.SetTypeId("ns3::Node");
		//ns3::Ptr<ns3::Node> ptr_node (object_factory.Create<ns3::Node>());


		ns3::Ptr<ns3::Node> ptr_node(object_factory.Create<ns3::Node> ());
		NS_ASSERT_MSG(ptr_node->GetNDevices() == 0, ptr_node->GetNDevices());

		ns3::InternetStackHelper internet_stack_helper;

		NS_ASSERT_MSG(ptr_node->GetNDevices() == 0, ptr_node->GetNDevices());
		internet_stack_helper.Install(ptr_node);
		NS_ASSERT_MSG(ptr_node->GetNDevices() == 1, ptr_node->GetNDevices());

		object_factory.SetTypeId("CsmaNode");
		ns3::Ptr<CsmaNode> ptr_csma_node(object_factory.Create<CsmaNode> ());
		NS_ASSERT_MSG(ptr_csma_node->GetNDevices() == 1, ptr_csma_node->GetNDevices());
		NS_ASSERT_MSG(ptr_csma_node->getNDevices<ns3::CsmaNetDevice>() == 1, ptr_csma_node->getNDevices<ns3::CsmaNetDevice>());
		NS_ASSERT_MSG(ptr_csma_node->getNDevices<ns3::LoopbackNetDevice>() == 0, ptr_csma_node->getNDevices<ns3::LoopbackNetDevice>());
		ptr_csma_node->Initialize();
		ptr_csma_node->Dispose();

		object_factory.SetTypeId("EunetTerminal");
		ns3::Ptr<EunetTerminal> ptr_eunet_terminal(object_factory.Create<
				EunetTerminal> ());
		NS_ASSERT_MSG(ptr_eunet_terminal->GetNDevices() == 2, ptr_eunet_terminal->GetNDevices());
		ptr_eunet_terminal->Initialize();
		NS_ASSERT_MSG(ptr_eunet_terminal->GetNDevices() == 2, ptr_eunet_terminal->GetNDevices());
		NS_ASSERT_MSG(ptr_eunet_terminal->getNDevices<ns3::CsmaNetDevice>()==1, ptr_eunet_terminal->getNDevices<ns3::CsmaNetDevice>());
		NS_ASSERT_MSG(ptr_eunet_terminal->getNDevices<ns3::LoopbackNetDevice>()==1, ptr_eunet_terminal->getNDevices<ns3::LoopbackNetDevice>());

		ns3::Ptr<EunetTerminal> ptr_eunet_terminal_2(object_factory.Create<
				EunetTerminal> ());
		NS_ASSERT_MSG(ptr_eunet_terminal_2->GetNDevices() == 2, ptr_eunet_terminal->GetNDevices());
		ptr_eunet_terminal_2->Initialize();
		NS_ASSERT_MSG(ptr_eunet_terminal_2->GetNDevices() == 2, ptr_eunet_terminal->GetNDevices());

		ns3::ObjectFactory object_factory_2;
		object_factory_2.SetTypeId("EunetTerminal");
		ns3::Ptr<EunetTerminal> ptr_eunet_terminal_3(object_factory_2.Create<
				EunetTerminal> ());
		NS_ASSERT_MSG(ptr_eunet_terminal_3->GetNDevices() == 2, ptr_eunet_terminal->GetNDevices());
		ptr_eunet_terminal_3->Initialize();
		NS_ASSERT_MSG(ptr_eunet_terminal_3->GetNDevices() == 2, ptr_eunet_terminal->GetNDevices());

		{
			auto device2 = ptr_eunet_terminal_2->getNetDevice<CsmaDevice> (0);
			auto device3 = ptr_eunet_terminal_3->getNetDevice<CsmaDevice> (0);
			device2->enablePcap();
			device3->enablePcap();
			ptr_eunet_terminal_2->enableAsciiTrace<ns3::CsmaNetDevice> (0);
			ptr_eunet_terminal_3->enableAsciiTrace<ns3::CsmaNetDevice> (0);
		}
		{
			auto p = ptr_eunet_terminal_2->getNetDevice<CsmaDevice> (0);
			ptr_eunet_terminal_2->assignAddress(p, "10.0.0.2", "255.0.0.0");
			NS_ASSERT(ptr_eunet_terminal_2->getAddress(p) == "10.0.0.2");
		}
		{
			auto p = ptr_eunet_terminal_3->getNetDevice<CsmaDevice> (0);
			ptr_eunet_terminal_3->assignAddress(p, "10.0.0.3", "255.0.0.0");
			NS_ASSERT(ptr_eunet_terminal_3->getAddress(p) == "10.0.0.3");
		}

		ptr_eunet_terminal_2->bring<ns3::CsmaNetDevice, ns3::CsmaNetDevice> (0,
				ptr_eunet_terminal_3, 0);
		{
			auto p = ptr_eunet_terminal_2->getNetDevice<ns3::CsmaNetDevice> (0);
			ptr_eunet_terminal_2->setRemote(ptr_eunet_terminal_2->getAddress(p));
		}

		NS_LOG_INFO("Run Simulation.");
		ns3::Simulator::Stop(ns3::Seconds(10.11));
		ns3::Simulator::Run();
		ns3::Simulator::Destroy();
		NS_ASSERT_MSG(ptr_eunet_terminal_2->getTotalRx() == 631808, ptr_eunet_terminal_2->getTotalRx());
		NS_ASSERT_MSG(ptr_eunet_terminal_3->getTotalRx() == 0, ptr_eunet_terminal_3->getTotalRx());
		NS_ASSERT_MSG(ptr_eunet_terminal_2->getTotalTxBytes() == 631808, ptr_eunet_terminal_2->getTotalTxBytes());
		NS_ASSERT_MSG(ptr_eunet_terminal_3->getTotalTxBytes() == 631808, ptr_eunet_terminal_3->getTotalTxBytes());
		NS_LOG_INFO("Done.");
	}//DoRun
};//EunetTerminalTestCase

class EunetTerminalTestSuite: public ns3::TestSuite {
public:
	EunetTerminalTestSuite(ns3::TestSuite::Type type) :
		ns3::TestSuite("EunetTerminalTestSuite", type) {
		switch (type) {
		case UNIT:
			AddTestCase(new EunetTerminalTestCase, ns3::TestCase::QUICK);
			break;
		case PERFORMANCE:
			AddTestCase(new EunetTerminalTestCase(true), ns3::TestCase::QUICK);
			break;
		default:
			break;
		}
		//NS_LOG_UNCOND("adding a test case");
	}
};

static EunetTerminalTestSuite eunet_terminal_test_suite(ns3::TestSuite::UNIT);
static EunetTerminalTestSuite eunet_terminal_test_suite_visual(
		ns3::TestSuite::Type::PERFORMANCE);
