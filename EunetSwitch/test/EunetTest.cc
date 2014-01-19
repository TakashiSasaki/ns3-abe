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
	const ns3::DataRate DATARATE_10GBPS("10Gbps");
	const ns3::DataRate DATARATE_1GBPS("1Gbps");

	/*
	 * configuring network 1 with three switches
	 *
	 *   s12---s11---s13
	 *
	 */

	// creating three switches for network 1
	auto ptr_s11 = eunet.addEunetSwitch("s11", 4, 24, DATARATE_10GBPS,
			DATARATE_1GBPS);
	auto ptr_s12 = eunet.addEunetSwitch("s12", 4, 24, DATARATE_10GBPS,
			DATARATE_1GBPS);
	auto ptr_s13 = eunet.addEunetSwitch("s13", 4, 24, DATARATE_10GBPS,
			DATARATE_1GBPS);

	// connecting switches in network 1
	eunet.connectDownTo("s11", "s12");
	eunet.connectDownTo("s11", "s13");

	// assiging IP addresses to terminals under s11
	ns3::Ipv4AddressHelper ipv4_address_helper_1(
			ns3::Ipv4Address("192.168.1.0"), ns3::Ipv4Mask("255.255.255.0"));
	ptr_s11->eunetTerminals.assignAddresses(ipv4_address_helper_1);
	ptr_s12->eunetTerminals.assignAddresses(ipv4_address_helper_1);
	ptr_s13->eunetTerminals.assignAddresses(ipv4_address_helper_1);

	/*
	 * setting destination address for OnOffApplication on s11/terminal3 to s12/terminal5
	 *
	 *   s12---s11---s13
	 *     |             |
	 *   t125        t133
	 * PacketSink  OnOffApplication
	 */
	auto t133 = ptr_s13->eunetTerminals.Get(3)->GetObject<EunetTerminal> ();
	auto t125 = ptr_s12->eunetTerminals.Get(5)->GetObject<EunetTerminal> ();
	t133->setRemote(t125->getAddress<ns3::CsmaNetDevice> (0));

	/*
	 * configuring network 2 with three switches
	 *
	 *   s22---s21---s23
	 *     |             |
	 *   t225        t233
	 * PacketSink  OnOffApplication
	 */
	auto ptr_s21 = eunet.addEunetSwitch("s21", 4, 24, DATARATE_10GBPS,
			DATARATE_1GBPS);
	auto ptr_s22 = eunet.addEunetSwitch("s22", 4, 24, DATARATE_10GBPS,
			DATARATE_1GBPS);
	auto ptr_s23 = eunet.addEunetSwitch("s23", 4, 24, DATARATE_10GBPS,
			DATARATE_1GBPS);

	eunet.connectDownTo("s21", "s22");
	eunet.connectDownTo("s21", "s23");

	ns3::Ipv4AddressHelper ipv4_address_helper_2(
			ns3::Ipv4Address("192.168.2.0"), ns3::Ipv4Mask("255.255.255.0"));
	ptr_s21->eunetTerminals.assignAddresses(ipv4_address_helper_2);
	ptr_s22->eunetTerminals.assignAddresses(ipv4_address_helper_2);
	ptr_s23->eunetTerminals.assignAddresses(ipv4_address_helper_2);

	auto t233 = ptr_s23->eunetTerminals.Get(3)->GetObject<EunetTerminal> ();
	auto t225 = ptr_s22->eunetTerminals.Get(5)->GetObject<EunetTerminal> ();
	t233->setRemote(t225->getAddress<ns3::CsmaNetDevice> (0));

	// attaching corresponding CSMA channel to EunetTerminals
	eunet.attachEunetTerminals();

	/*
	 *  routing between network 1 and 2 via router r1 with OSPF.
	 *
	 *OnOffApplication
	 *   t125           t133
	 *     |                |
	 *   s12---s11------s13
	 *            |
	 *          r1 OSPF
	 *            |
	 *   s22---s21---s23
	 *     |             |
	 *   t225        t233
	 *            PacketSink
	 *
	 */
	eunet.addEunetRouter("r1");

	Simulator::Stop(Seconds(this->stopTime));
	Simulator::Run();
	Simulator::Destroy();
	NS_ASSERT_MSG(t133->getTotalRx() == 0, t133->getTotalRx());
	NS_ASSERT_MSG(t125->getTotalRx() == 340992, t125->getTotalRx());
	NS_ASSERT_MSG(t233->getTotalRx() == 0, t133->getTotalRx());
	NS_ASSERT_MSG(t225->getTotalRx() == 340480, t225->getTotalRx());
}

class EunetTestSuite: public TestSuite {
public:
	EunetTestSuite() :
		ns3::TestSuite("EunetTestSuite", UNIT) {
		AddTestCase(new EunetTestCase, TestCase::QUICK);
	}
};

static EunetTestSuite eunet_test_suite;
