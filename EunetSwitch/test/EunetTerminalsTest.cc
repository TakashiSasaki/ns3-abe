#define NS3_LOG_ENABLE 1
#include "ns3/log.h"
NS_LOG_COMPONENT_DEFINE("EunetTerminalsTest");
#define NS3_ASSERT_ENABLE 1
#include "ns3/assert.h"
#include "ns3/test.h"
#include "ns3/simulator.h"
#include "ns3/internet-stack-helper.h"
#include "ns3/netanim-module.h"
#include "ns3/mobility-helper.h"
#include "ns3/core-module.h"
#include "ns3/on-off-helper.h"
#include "EunetTerminals.h"

class EunetTerminalsTestCase: public ns3::TestCase {
public:
	EunetTerminalsTestCase() :
		ns3::TestCase("EunetTerminalsTestCase") {
	}
	virtual ~EunetTerminalsTestCase() {
	}

private:
	virtual void DoRun(void) {
		//ns3::GlobalValue::Bind("SimulatorImplementationType", ns3::StringValue(
		//"ns3::VisualSimulatorImpl"));
		ns3::PacketMetadata::Enable();
		EunetTerminals terminals;
		terminals.initialize(3);
		auto terminal0 = terminals.Get(0);
		auto terminal1 = terminals.Get(1);
		auto terminal2 = terminals.Get(2);
		{
			NS_ASSERT(terminals.Get(0)->GetNDevices()==2);
			NS_ASSERT(terminals.Get(1)->GetNDevices()==2);
			NS_ASSERT(terminals.Get(2)->GetNDevices()==2);
			NS_LOG_DEBUG("remote of terminal0 " << terminal0->getRemote());
			NS_LOG_DEBUG("remote of terminal1 " << terminal1->getRemote());
			NS_LOG_DEBUG("remote of terminal2 " << terminal2->getRemote());
		}
		terminals.bringAtoB(1, 0);
		terminals.bringAtoB(2, 0);
		terminals.assignAddresses();
		terminals.setRemoteOfAtoB(0, 0);
		terminals.setRemoteOfAtoB(1, 0);
		terminals.setRemoteOfAtoB(2, 0);
		//eunet_terminals.Get(0)->startAt(ns3::Seconds(0.0));
		//eunet_terminals.Get(1)->startAt(ns3::Seconds(0.0));

		if (false) {
			ns3::MobilityHelper mobility_helper;
			mobility_helper.SetPositionAllocator(
					"ns3::RandomDiscPositionAllocator",
					"X",
					ns3::StringValue("100.0"),
					"Y",
					ns3::StringValue("100.0"),
					"Rho",
					ns3::StringValue("ns3::UniformRandomVariable[Min=0|Max=30]"));
		}
		if (false) {
			auto terminal0 = terminals.Get(0);
			auto mobility_model = terminal0->GetObject<ns3::MobilityModel> ();
			NS_ASSERT(mobility_model != NULL);
		}

		ns3::AnimationInterface animation_interface("EunetTerminals.xml");
		//animation_interface.SetConstantPosition(eunet_terminals.Get(0), 0, 0);
		//animation_interface.SetConstantPosition(eunet_terminals.Get(1), 0, 0);
		//animation_interface.SetConstantPosition(eunet_terminals.Get(2), 0, 0);

		NS_LOG_INFO("Run Simulation.");
		ns3::Simulator::Stop(ns3::Seconds(10.0));
		ns3::Simulator::Run();

		if (true) {
			NS_ASSERT(terminal0->getApplication<ns3::OnOffApplication>()!= NULL);
			NS_ASSERT(terminal1->getApplication<ns3::OnOffApplication>()!= NULL);
			NS_ASSERT(terminal2->getApplication<ns3::OnOffApplication>()!= NULL);
			NS_LOG_DEBUG("remote of terminal0 " << terminal0->getRemote());
			NS_LOG_DEBUG("remote of terminal1 " << terminal1->getRemote());
			NS_LOG_DEBUG("remote of terminal2 " << terminal2->getRemote());
			NS_ASSERT(terminal0->getTotalTxBytes()>0);
			NS_ASSERT(terminal1->getTotalTxBytes()>0);
			NS_ASSERT(terminal2->getTotalTxBytes()>0);
			NS_ASSERT(terminal0->getTotalTxPackets()>0);
			NS_ASSERT(terminal1->getTotalTxPackets()>0);
			NS_ASSERT(terminal2->getTotalTxPackets()>0);
			NS_ASSERT(terminal0->getTotalRxPackets()>0);
			NS_ASSERT(terminal1->getTotalRxPackets()==0);
			NS_ASSERT(terminal2->getTotalRxPackets()==0);
			NS_ASSERT(terminal0->getTotalRx()>0);
			NS_ASSERT(terminal1->getTotalRx()==0);
			NS_ASSERT(terminal2->getTotalRx()==0);
			NS_ASSERT(terminal0->getTotalTxBytes()+terminal1->getTotalTxBytes()+terminal2->getTotalTxBytes()==terminal0->getTotalRx());
		}

		ns3::Simulator::Destroy();
		NS_LOG_INFO("Done.");

		if (true) {
			NS_ASSERT(terminal0->getApplication<ns3::OnOffApplication>()== NULL);
			NS_ASSERT(terminal1->getApplication<ns3::OnOffApplication>()== NULL);
			NS_ASSERT(terminal2->getApplication<ns3::OnOffApplication>()== NULL);
		}
	}//DoRun
};

class EunetTerminalsTestSuite: public ns3::TestSuite {
public:
	EunetTerminalsTestSuite() :
		ns3::TestSuite("EunetTerminalsTestSuite", UNIT) {
		AddTestCase(new EunetTerminalsTestCase, ns3::TestCase::QUICK);
	}
};

static EunetTerminalsTestSuite eunet_terminals_test_suite;

