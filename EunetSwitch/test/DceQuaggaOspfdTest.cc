/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2012 Hajime Tazaki, NICT
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: Hajime Tazaki <tazaki@nict.go.jp>
 */
// modified by Takashi SASAKI

#include "ns3/network-module.h"
#include "ns3/core-module.h"
#include "ns3/internet-module.h"
#include "ns3/dce-module.h"
#include "ns3/quagga-helper.h"
#include "ns3/point-to-point-helper.h"

using namespace ns3;
NS_LOG_COMPONENT_DEFINE ("DceQuaggaOspfdTest");

class DceQuaggaOspfdTest: public TestCase {
public:
	DceQuaggaOspfdTest() :
		ns3::TestCase("DceQuaggaOspfdTest") {
		//NS_LOG_UNCOND("constructing a test case");
	}
	virtual ~DceQuaggaOspfdTest() {
	}

private:
	virtual void DoRun(void);
}; //class DceQuaggaOspfdTest

// Parameters
uint32_t nNodes = 2;
uint32_t stopTime = 20;
std::string netStack = "ns3";

void DceQuaggaOspfdTest::DoRun() {
	//
	//  Step 1
	//  Node Basic Configuration
	//
	NodeContainer nodes;
	nodes.Create(nNodes);

	PointToPointHelper pointToPoint;
	pointToPoint.SetDeviceAttribute("DataRate", StringValue("5Mbps"));
	pointToPoint.SetChannelAttribute("Delay", StringValue("2ms"));

	NetDeviceContainer devices;
	devices = pointToPoint.Install(nodes);
	DceManagerHelper processManager;

	//
	//
	// Address Configuration
	//
	//
	Ipv4AddressHelper ipv4AddrHelper;
	Ipv6AddressHelper ipv6AddrHelper;
	// Internet stack install
	InternetStackHelper stack; // IPv4 is required for GlobalRouteMan
	Ipv4DceRoutingHelper ipv4RoutingHelper;
	stack.SetRoutingHelper(ipv4RoutingHelper);
	stack.Install(nodes);

	ipv4AddrHelper.SetBase("10.0.0.0", "255.255.255.0");
	Ipv4InterfaceContainer interfaces = ipv4AddrHelper.Assign(devices);
	Ipv4GlobalRoutingHelper::PopulateRoutingTables();

	processManager.SetNetworkStack("ns3::Ns3SocketFdFactory");
	processManager.Install(nodes);

	QuaggaHelper quagga;
	quagga.EnableOspf(nodes, "10.0.0.0/24");
	quagga.EnableOspfDebug(nodes);
	quagga.EnableZebraDebug(nodes);
	quagga.Install(nodes);

	pointToPoint.EnablePcapAll("dce-quagga-ospfd");

	//
	// Step 9
	// Now It's ready to GO!
	//
	if (stopTime != 0) {
		Simulator::Stop(Seconds(stopTime));
	}
	Simulator::Run();
	Simulator::Destroy();
}//DceQuaggaOspfdTest::DoRun

class DceQuaggaOspfdTestSuite: public TestSuite {
public:
	DceQuaggaOspfdTestSuite() :
		ns3::TestSuite("DceQuaggaOspfd", UNIT) {
		//NS_LOG_UNCOND("adding a test case");
		AddTestCase(new DceQuaggaOspfdTest, TestCase::QUICK);
	}
};

static DceQuaggaOspfdTestSuite dce_quagga_ospfd_test_suite;

