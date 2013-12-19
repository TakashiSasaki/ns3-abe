#define NS3_LOG_ENABLE 1
#define NS3_ASSERT_ENABLE 1
#include "ns3/log.h"
NS_LOG_COMPONENT_DEFINE("EunetTerminalsTest");
#include "ns3/test.h"
#include "ns3/simulator.h"
#include "ns3/internet-stack-helper.h"
#include "ns3/netanim-module.h"
#include "ns3/mobility-helper.h"
#include "ns3/core-module.h"
#include "EunetTerminals.h"

class EunetTerminalsTestCase: public ns3::TestCase {
public:
	EunetTerminalsTestCase() :
		ns3::TestCase("EunetTerminalsTestCase") {
		NS_LOG_UNCOND("constructing a test case");
	}
	virtual ~EunetTerminalsTestCase() {
	}

private:
	virtual void DoRun(void) {
		//ns3::GlobalValue::Bind("SimulatorImplementationType", ns3::StringValue(
		//"ns3::VisualSimulatorImpl"));
		EunetTerminals eunet_terminals(3);
		eunet_terminals.bringAtoB(1, 0);
		eunet_terminals.bringAtoB(2, 0);
		eunet_terminals.assignAddresses();
		eunet_terminals.setRemoteOfAtoB(0, 0);
		eunet_terminals.setRemoteOfAtoB(1, 0);
		eunet_terminals.setRemoteOfAtoB(2, 0);
		eunet_terminals.Get(0)->startAt(ns3::Seconds(0.0));
		eunet_terminals.Get(1)->startAt(ns3::Seconds(0.0));

		ns3::MobilityHelper mobility_helper;
#if 0
		mobility_helper.SetPositionAllocator(
				"ns3::RandomDiscPositionAllocator", "X", ns3::StringValue(
						"100.0"), "Y", ns3::StringValue("100.0"), "Rho",
				ns3::StringValue("ns3::UniformRandomVariable[Min=0|Max=30]"));
#endif

		auto node0 = eunet_terminals.Get(0);
		auto mobility_model = node0->GetObject<ns3::MobilityModel> ();
		NS_ASSERT(mobility_model != 0);

		ns3::AnimationInterface animation_interface("EunetTerminals.xml");
		//animation_interface.SetConstantPosition(eunet_terminals.Get(0), 0, 0);
		//animation_interface.SetConstantPosition(eunet_terminals.Get(1), 0, 0);
		//animation_interface.SetConstantPosition(eunet_terminals.Get(2), 0, 0);

		NS_LOG_INFO("Run Simulation.");
		ns3::Simulator::Stop(ns3::Seconds(10.0));
		ns3::Simulator::Run();
		ns3::Simulator::Destroy();
		NS_LOG_INFO("Done.");

	}//DoRun
};

class EunetTerminalsTestSuite: public ns3::TestSuite {
public:
	EunetTerminalsTestSuite() :
		ns3::TestSuite("EunetTerminals", UNIT) {
		AddTestCase(new EunetTerminalsTestCase, ns3::TestCase::QUICK);
	}
};

static EunetTerminalsTestSuite eunet_terminals_test_suite;

