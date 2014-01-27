#include <memory>
#include <sstream>
#define NS3_LOG_ENABLE 1
#include "ns3/log.h"
NS_LOG_COMPONENT_DEFINE("EunetTest");
#define NS3_ASSERT_ENABLE 1
#include "ns3/assert.h"
#include "ns3/dce-module.h"
#include "ns3/names.h"
#include "CsmaDevice.h"
#include "Eunet.h"

using namespace ns3;

class EunetTestCase: public TestCase {
	static const double stopTime = 120.0;
	const bool isVisual;
public:
	EunetTestCase(const bool is_visual = false) :
		ns3::TestCase("EunetTestCase"), isVisual(is_visual) {
	}
	virtual ~EunetTestCase() {
	}

private:
	virtual void DoRun(void);
};

void EunetTestCase::DoRun() {
	if (this->isVisual) {
		NS_LOG_DEBUG("--SimulatorImplementationType=ns3::VisualSimulatorImpl");
		ns3::GlobalValue::Bind("SimulatorImplementationType", ns3::StringValue(
				"ns3::VisualSimulatorImpl"));
	}//if

	Eunet eunet;
	const ns3::DataRate DATARATE_10GBPS("10Gbps");
	const ns3::DataRate DATARATE_1GBPS("1Gbps");

	ns3::NodeContainer nodes;

	/*
	 * configuring network 1 with three switches
	 *
	 *   s12---s11---s13
	 *
	 */
	// creating three switches for network 1
	auto s11 = eunet.addEunetSwitch("s11", 1, 6, DATARATE_10GBPS,
			DATARATE_1GBPS);
	NS_ASSERT(ns3::Names::Find<EunetSwitch>("s11") == s11);
	auto s12 = eunet.addEunetSwitch("s12", 1, 6, DATARATE_10GBPS,
			DATARATE_1GBPS);
	NS_ASSERT(ns3::Names::Find<EunetSwitch>("s12") == s12);
	auto s13 = eunet.addEunetSwitch("s13", 1, 6, DATARATE_10GBPS,
			DATARATE_1GBPS);
	NS_ASSERT(ns3::Names::Find<EunetSwitch>("s13") == s13);

	ns3::InternetStackHelper internet_stack_helper;

	// connecting switches in network 1
	{
		auto devices_s11_s12 = eunet.connectDownTo("s11", "s12");
		NS_ASSERT(devices_s11_s12.Get(0)->GetChannel()->GetId() == devices_s11_s12.Get(1)->GetChannel()->GetId());
		auto devices_s11_s13 = eunet.connectDownTo("s11", "s13");
		NS_ASSERT(devices_s11_s13.Get(0)->GetChannel()->GetId() == devices_s11_s13.Get(1)->GetChannel()->GetId());
	}

	// assiging IP addresses to terminals under s11
	{
		ns3::Ipv4AddressHelper ipv4_address_helper_1(ns3::Ipv4Address(
				"192.168.1.0"), ns3::Ipv4Mask("255.255.255.0"));
		s11->eunetTerminals.assignAddresses(ipv4_address_helper_1);
		s12->eunetTerminals.assignAddresses(ipv4_address_helper_1);
		s13->eunetTerminals.assignAddresses(ipv4_address_helper_1);
	}
	/*
	 * setting destination address for OnOffApplication on s11/terminal3 to s12/terminal5
	 *
	 *   s12---s11---s13
	 *     |             |
	 *   t125        t133
	 * PacketSink  OnOffApplication
	 */
	auto t133 = s13->eunetTerminals.Get(3)->GetObject<EunetTerminal> ();
	ns3::Names::Add("t133", t133);
	auto t125 = s12->eunetTerminals.Get(5)->GetObject<EunetTerminal> ();
	ns3::Names::Add("t125", t125);
	{
		auto device = t125->getNetDevice<CsmaDevice> (0);
		t133->setRemote(t125->getAddress(device));
	}

	/*
	 * configuring network 2 with three switches
	 *
	 *   s22---s21---s23
	 *     |             |
	 *   t225        t233
	 * PacketSink  OnOffApplication
	 */
	auto s21 = eunet.addEunetSwitch("s21", 1, 6, DATARATE_10GBPS,
			DATARATE_1GBPS);
	auto s22 = eunet.addEunetSwitch("s22", 1, 6, DATARATE_10GBPS,
			DATARATE_1GBPS);
	auto s23 = eunet.addEunetSwitch("s23", 1, 6, DATARATE_10GBPS,
			DATARATE_1GBPS);

	{
		auto devices_s21_s22 = eunet.connectDownTo("s21", "s22");
		NS_ASSERT(devices_s21_s22.Get(0)->GetChannel()->GetId() == devices_s21_s22.Get(1)->GetChannel()->GetId());
		auto devices_s21_s23 = eunet.connectDownTo("s21", "s23");
		NS_ASSERT(devices_s21_s23.Get(0)->GetChannel()->GetId() == devices_s21_s23.Get(1)->GetChannel()->GetId());
	}
	{
		ns3::Ipv4AddressHelper ipv4_address_helper_2(ns3::Ipv4Address(
				"192.168.2.0"), ns3::Ipv4Mask("255.255.255.0"));
		s21->eunetTerminals.assignAddresses(ipv4_address_helper_2);
		s22->eunetTerminals.assignAddresses(ipv4_address_helper_2);
		s23->eunetTerminals.assignAddresses(ipv4_address_helper_2);
	}
	auto t233 = s23->eunetTerminals.Get(3)->GetObject<EunetTerminal> ();
	NS_LOG_DEBUG("address of t233 is " << t233->getAddress(t233->GetDevice(0)));
	auto t225 = s22->eunetTerminals.Get(5)->GetObject<EunetTerminal> ();
	NS_LOG_DEBUG("address of t225 is " << t225->getAddress(t225->GetDevice(0)));
	{
		auto device = t225->getNetDevice<CsmaDevice> (0);
		t233->setRemote(t225->getAddress(device));
	}

	/*
	 *  routing between network 1 and 2 via router r1 with OSPF.
	 *
	 *     OnOffApplication
	 *       192.168.1.12
	 *         t125             t133
	 *           |                |
	 *         s12-----s11------s13
	 *                  |
	 *                  | 192.168.1.101
	 *192.168.12.1 |----r1 OSPF
	 *192.168.12.2 |    | 192.168.13.1
	 *        OSPF r2   |
	 *192.168.23.2 |    | 192.168.13.3
	 *192.168.23.3 |----r3 OSPF
	 *                  |192.168.2.103
	 *                  |
	 *         s22-----s21---s23
	 *           |             |
	 *         t225          t233
	 *                     PacketSink
	 *       192.168.2.12     192.168.2.16
	 */
	auto r1 = eunet.addEunetRouter("r1");
	NS_ASSERT(ns3::Names::FindName(r1) == "r1");
	auto r2 = eunet.addEunetRouter("r2");
	NS_ASSERT(ns3::Names::FindName(r2) == "r2");
	auto r3 = eunet.addEunetRouter("r3");
	NS_ASSERT(ns3::Names::FindName(r3) == "r3");

	//////////////////////////////////////////////
	// connecting five links around routers
	//////////////////////////////////////////////
	{
		auto devices_s11_r1 = eunet.connectToRouter("s11", "r1",
				ns3::Ipv4Address("192.168.1.101"), ns3::Ipv4Mask(
						"255.255.255.0"));
		NS_ASSERT(devices_s11_r1.Get(0)->GetNode()->GetInstanceTypeId()==EunetSwitch::GetTypeId());
		NS_ASSERT(devices_s11_r1.Get(1)->GetNode()->GetInstanceTypeId()==EunetRouter::GetTypeId());
		NS_ASSERT(devices_s11_r1.Get(0)->GetChannel()->GetId() == devices_s11_r1.Get(1)->GetChannel()->GetId());
	}
	auto devices_s21_r3 = eunet.connectToRouter("s21", "r3", ns3::Ipv4Address(
			"192.168.2.103"), ns3::Ipv4Mask("255.255.255.0"));
	auto devices_r1_r3 = eunet.connectRouters("r1", "r3", ns3::Ipv4Address(
			"192.168.13.1"), ns3::Ipv4Address("192.168.13.3"), ns3::Ipv4Mask(
			"255.255.255.0"));
	auto devices_r1_r2 = eunet.connectRouters("r1", "r2", ns3::Ipv4Address(
			"192.168.12.1"), ns3::Ipv4Address("192.168.12.2"), ns3::Ipv4Mask(
			"255.255.255.0"));
	auto devices_r2_r3 = eunet.connectRouters("r2", "r3", ns3::Ipv4Address(
			"192.168.23.2"), ns3::Ipv4Address("192.168.23.3"), ns3::Ipv4Mask(
			"255.255.255.0"));

	// setting default route to two nodes
	t125->setDefaultRoute(ns3::Ipv4Address("192.168.1.101"));
	t233->setDefaultRoute(ns3::Ipv4Address("192.168.2.103"));

	// enabling packet capture on some ports
	//ns3::Ptr<EunetRouter> r1 = ns3::Names::Find<EunetRouter>("r1");
	{
		auto device = r1->getDevice(ns3::Ipv4Address("192.168.1.101"));
		r1->enablePcap(device);
		auto device2 = r1->getDevice(ns3::Ipv4Address("192.168.13.1"));
		r1->enablePcap(device2);
		auto device3 = r1->getDevice(ns3::Ipv4Address("192.168.12.1"));
		r1->enablePcap(device3);
	}

	//ns3::Ptr<EunetRouter> r2 = ns3::Names::Find<EunetRouter>("r2");
	{
		auto device = r2->getDevice(ns3::Ipv4Address("192.168.12.2"));
		r2->enablePcap(device);
		auto device2 = r2->getDevice(ns3::Ipv4Address("192.168.23.2"));
		r2->enablePcap(device2);
	}
	//auto ptr_s12 = ns3::Names::Find("s12");
	//auto ptr_s23 = ns3::Names::Find("s23");
	//auto t125 = ptr_s12->eunetTerminals->Get(5);
	//auto t233 = ptr_s23->eunetTerminals->Get(5);
	if (true) {
		auto device = t233->getNetDevice<CsmaDevice> (0);
		NS_ASSERT(device != NULL);
		auto address = t233->getAddress(device);
		NS_LOG_DEBUG("set remote address of t125 to " << address);
		t125->setRemote(address);
	}

	if (true) {
		auto output_stream_wrapper = Create<OutputStreamWrapper> (&std::cout);
		ns3::Ipv4DceRoutingHelper ipv4_dce_routing_helper;
		ipv4_dce_routing_helper.PrintRoutingTableEvery(ns3::Seconds(10.0), r1,
				output_stream_wrapper);
		ipv4_dce_routing_helper.PrintRoutingTableEvery(ns3::Seconds(10.0), r2,
				output_stream_wrapper);
		ipv4_dce_routing_helper.PrintRoutingTableEvery(ns3::Seconds(10.0), r3,
				output_stream_wrapper);
	}

	// attaching corresponding CSMA channel to EunetTerminals
	eunet.attachEunetTerminals();
	Simulator::Stop(Seconds(120));
	Simulator::Run();
	Simulator::Destroy();

	if (true) {//transmission inside segment 1
		NS_LOG_DEBUG("test for transmission inside segment 1");
		NS_ASSERT_MSG(t133->getTotalRx() == 0, t133->getTotalRx());
		NS_ASSERT_MSG(t133->getTotalRxPackets() == 0, t133->getTotalRxPackets());
		NS_ASSERT_MSG(t125->getTotalRx() > 0, t125->getTotalRx());
		NS_ASSERT_MSG(t125->getTotalRxPackets() > 0, t125->getTotalRxPackets());
		NS_ASSERT_MSG(t133->getTotalTxPackets() == t125->getTotalRxPackets(), t133->getTotalTxPackets() << "," << t125->getTotalRxPackets());
		NS_ASSERT_MSG(t133->getTotalTxBytes() == t125->getTotalRx(), t133->getTotalTxBytes() << "," << t125->getTotalRx());
	}
	if (true) {//transmission inside segment 2
		NS_LOG_DEBUG("test for transmission inside segment 2");
		//NS_ASSERT_MSG(t233->getTotalRx() == 0, t233->getTotalRx());
		//NS_ASSERT_MSG(t233->getTotalRxPackets() == 0, t233->getTotalRxPackets());
		NS_ASSERT_MSG(t225->getTotalRx() > 0, t225->getTotalRx());
		NS_ASSERT_MSG(t225->getTotalRxPackets() > 0, t225->getTotalRxPackets());
		NS_ASSERT_MSG(t233->getTotalTxPackets() == t225->getTotalRxPackets(), t233->getTotalTxPackets() << "," << t225->getTotalTxPackets());
		NS_ASSERT_MSG(t233->getTotalTxBytes() == t225->getTotalRx(), t233->getTotalTxBytes() << "," << t225->getTotalTxBytes());
	}
	if (true) {
		NS_LOG_DEBUG("test for transmission between segment 1 and 2");
		//NS_ASSERT_MSG(t233->getTotalRxPackets() == t125->getTotalTxPackets(), t233->getTotalRxPackets() << "," <<t125->getTotalTxPackets());
		//NS_ASSERT_MSG(t233->getTotalRx() == t125->getTotalTxBytes(), t233->getTotalRx() << "," <<t125->getTotalTxBytes());
		NS_ASSERT_MSG(t233->getTotalRxPackets() > 0, t233->getTotalRxPackets());
		NS_ASSERT_MSG(t233->getTotalRx() > 0, t233->getTotalRx());
	}
}

class EunetTestSuite: public TestSuite {
public:
	EunetTestSuite(ns3::TestSuite::Type type) :
		ns3::TestSuite("EunetTestSuite", type) {
		switch (type) {
		case UNIT:
			AddTestCase(new EunetTestCase, TestCase::QUICK);
			break;
		case PERFORMANCE:
			AddTestCase(new EunetTestCase(true), TestCase::QUICK);
			break;
		default:
			break;
		}
	}
};

static EunetTestSuite eunet_test_suite(ns3::TestSuite::UNIT);
static EunetTestSuite eunet_test_suite_visual(ns3::TestSuite::PERFORMANCE);
