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
#include "ns3/csma-helper.h"

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
uint32_t stopTime = 60;

void DceQuaggaOspfdTest::DoRun() {
	//
	//  Step 1
	//  Node Basic Configuration
	//
	NodeContainer nodes;
	nodes.Create(nNodes);

	CsmaHelper csma_helper;
	csma_helper.SetChannelAttribute("DataRate", StringValue("5Mbps"));
	csma_helper.SetChannelAttribute("Delay", StringValue("2ms"));

	PointToPointHelper pointToPoint;
	pointToPoint.SetDeviceAttribute("DataRate", StringValue("5Mbps"));
	pointToPoint.SetChannelAttribute("Delay", StringValue("2ms"));

	NetDeviceContainer devices;
	devices = csma_helper.Install(nodes);
	auto ndc_point_to_point = pointToPoint.Install(nodes);

	//
	//
	// Address Configuration
	//
	//
#define SEPARATE true // Either case works
#if SEPARATE
	{
		// Internet stack install
		InternetStackHelper stack1; // IPv4 is required for GlobalRouteMan
		Ipv4DceRoutingHelper ipv4RoutingHelper1;
		stack1.SetRoutingHelper(ipv4RoutingHelper1);
		stack1.Install(nodes.Get(0));

		InternetStackHelper stack2; // IPv4 is required for GlobalRouteMan
		Ipv4DceRoutingHelper ipv4RoutingHelper2;
		stack2.SetRoutingHelper(ipv4RoutingHelper2);
		stack2.Install(nodes.Get(1));

	}
#else
	{
		// Internet stack install
		InternetStackHelper stack; // IPv4 is required for GlobalRouteMan
		Ipv4DceRoutingHelper ipv4RoutingHelper;
		stack.SetRoutingHelper(ipv4RoutingHelper);
		stack.Install(nodes);
	}
#endif

	{
		// assigning IP address
		Ipv4AddressHelper ipv4AddrHelper;
		ipv4AddrHelper.SetBase("10.0.0.0", "255.255.255.0");
		Ipv4InterfaceContainer interfaces = ipv4AddrHelper.Assign(devices);
		Ipv4InterfaceContainer iic_point_to_point = ipv4AddrHelper.Assign(
				ndc_point_to_point);
		//Ipv4GlobalRoutingHelper::PopulateRoutingTables();
	}

#if SEPARATE
	DceManagerHelper processManager1;
	processManager1.SetNetworkStack("ns3::Ns3SocketFdFactory");
	processManager1.Install(nodes.Get(0));

	QuaggaHelper quagga1;
	quagga1.EnableOspf(nodes.Get(0), "10.0.0.0/24");
	quagga1.EnableOspfDebug(nodes.Get(0));
	quagga1.EnableZebraDebug(nodes.Get(0));
	quagga1.Install(nodes.Get(0));

	DceManagerHelper processManager2;
	processManager2.SetNetworkStack("ns3::Ns3SocketFdFactory");
	processManager2.Install(nodes.Get(1));

	QuaggaHelper quagga2;
	quagga2.EnableOspf(nodes.Get(1), "10.0.0.0/24");
	quagga2.EnableOspfDebug(nodes.Get(1));
	quagga2.EnableZebraDebug(nodes.Get(1));
	quagga2.Install(nodes.Get(1));
#else
	DceManagerHelper processManager;
	processManager.SetNetworkStack("ns3::Ns3SocketFdFactory");
	processManager.Install(nodes);

	QuaggaHelper quagga;
	quagga.EnableOspf(nodes, "10.0.0.0/24");
	quagga.EnableOspfDebug(nodes);
	quagga.EnableZebraDebug(nodes);
	quagga.Install(nodes);
#endif

	pointToPoint.EnablePcapAll("dce-quagga-ospfd");
	csma_helper.EnablePcapAll("dce-quagga-ospfd");

	//
	// Step 9
	// Now It's ready to GO!
	//
	if (stopTime != 0) {
		Simulator::Stop(Seconds(stopTime));
	}
	Simulator::Run();
	Simulator::Destroy();
	NS_LOG_UNCOND("dfsofjdijad");
}//DceQuaggaOspfdTest::DoRun

class DceQuaggaOspfdTestSuite: public TestSuite {
public:
	DceQuaggaOspfdTestSuite() :
		ns3::TestSuite("DceQuaggaOspfdTestSuite", UNIT) {
		//NS_LOG_UNCOND("adding a test case");
		AddTestCase(new DceQuaggaOspfdTest, TestCase::QUICK);
	}
};

static DceQuaggaOspfdTestSuite dce_quagga_ospfd_test_suite;
