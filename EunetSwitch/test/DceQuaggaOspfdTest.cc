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
#include <iostream>
#define NS3_LOG_ENABLE 1
#include "ns3/log.h"
NS_LOG_COMPONENT_DEFINE ("DceQuaggaOspfdTest");
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

class DceQuaggaOspfdTestCase: public TestCase {
public:
	DceQuaggaOspfdTestCase() :
		ns3::TestCase("DceQuaggaOspfdTest") {
		//NS_LOG_UNCOND("constructing a test case");
	}
	virtual ~DceQuaggaOspfdTestCase() {
	}

private:
	virtual void DoRun(void);
}; //class DceQuaggaOspfdTestCase

// Parameters
uint32_t nNodes = 2;
uint32_t stopTime = 60;

void DceQuaggaOspfdTestCase::DoRun() {
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
	{
		// Internet stack install
		InternetStackHelper stack; // IPv4 is required for GlobalRouteMan
		Ipv4DceRoutingHelper ipv4RoutingHelper;
		stack.SetRoutingHelper(ipv4RoutingHelper);
		stack.Install(nodes);
	}

	{
		// assigning IP address
		Ipv4AddressHelper ipv4AddrHelper;
		ipv4AddrHelper.SetBase("10.0.0.0", "255.255.255.0");
		Ipv4InterfaceContainer interfaces = ipv4AddrHelper.Assign(devices);
		Ipv4InterfaceContainer iic_point_to_point = ipv4AddrHelper.Assign(
				ndc_point_to_point);
		//Ipv4GlobalRoutingHelper::PopulateRoutingTables();
	}

	DceManagerHelper processManager;
	processManager.SetNetworkStack("ns3::Ns3SocketFdFactory");
	processManager.Install(nodes);

	QuaggaHelper quagga;
	quagga.EnableOspf(nodes, "10.0.0.0/24");
	quagga.EnableOspfDebug(nodes);
	quagga.EnableZebraDebug(nodes);
	quagga.Install(nodes);

	pointToPoint.EnablePcapAll("DceQuaggaOspfdTestCase");
	csma_helper.EnablePcapAll("DceQuaggaOspfdTestCase");

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

class DceQuaggaOspfdSeparatedTestCase: public TestCase {
public:
	DceQuaggaOspfdSeparatedTestCase() :
		ns3::TestCase("DceQuaggaOspfdSeparatedTestCase") {
	}
	virtual ~DceQuaggaOspfdSeparatedTestCase() {
	}

private:
	virtual void DoRun(void);
}; //class DceQuaggaOspfdSeparatedTestCase

void DceQuaggaOspfdSeparatedTestCase::DoRun() {
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

	{
		// assigning IP address
		Ipv4AddressHelper ipv4AddrHelper;
		ipv4AddrHelper.SetBase("10.0.0.0", "255.255.255.0");
		Ipv4InterfaceContainer interfaces = ipv4AddrHelper.Assign(devices);
		Ipv4InterfaceContainer iic_point_to_point = ipv4AddrHelper.Assign(
				ndc_point_to_point);
		//Ipv4GlobalRoutingHelper::PopulateRoutingTables();
	}

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

	pointToPoint.EnablePcapAll("DceQuaggaOspfdSeparatedTestCase");
	csma_helper.EnablePcapAll("DceQuaggaOspfdSeparatedTestCase");

	//
	// Step 9
	// Now It's ready to GO!
	//
	if (stopTime != 0) {
		Simulator::Stop(Seconds(stopTime));
	}
	Simulator::Run();
	Simulator::Destroy();
}//DceQuaggaOspfdSeparatedTestCase::DoRun

class DceQuaggaOspfdSetRoutingProtocolTestCase: public TestCase {
public:
	DceQuaggaOspfdSetRoutingProtocolTestCase() :
		ns3::TestCase("DceQuaggaOspfdSetRoutingProtocolTestCase") {
	}
	virtual ~DceQuaggaOspfdSetRoutingProtocolTestCase() {
	}

private:
	virtual void DoRun(void);
}; //class DceQuaggaOspfdSetRoutingProtocolTestCase

void DceQuaggaOspfdSetRoutingProtocolTestCase::DoRun() {
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

	{
		// Internet stack install
		InternetStackHelper stack1; // IPv4 is required for GlobalRouteMan
		//Ipv4DceRoutingHelper ipv4RoutingHelper1;
		//stack1.SetRoutingHelper(ipv4RoutingHelper1);
		stack1.Install(nodes.Get(0));

		InternetStackHelper stack2; // IPv4 is required for GlobalRouteMan
		//Ipv4DceRoutingHelper ipv4RoutingHelper2;
		//stack2.SetRoutingHelper(ipv4RoutingHelper2);
		stack2.Install(nodes.Get(1));

	}

	{
		auto ipv4_0 = nodes.Get(0)->GetObject<ns3::Ipv4> ();
		Ipv4DceRoutingHelper ipv4_routing_helper_0;
		auto ipv4_routing_protocol_0 = ipv4_routing_helper_0.Create(
				nodes.Get(0));
		ipv4_0->SetRoutingProtocol(ipv4_routing_protocol_0);

		auto ipv4_1 = nodes.Get(1)->GetObject<ns3::Ipv4> ();
		Ipv4DceRoutingHelper ipv4_routing_helper_1;
		auto ipv4_routing_protocol_1 = ipv4_routing_helper_1.Create(
				nodes.Get(1));
		ipv4_1->SetRoutingProtocol(ipv4_routing_protocol_1);
	}

	{
		// assigning IP address
		Ipv4AddressHelper ipv4AddrHelper;
		ipv4AddrHelper.SetBase("10.0.0.0", "255.255.255.0");
		Ipv4InterfaceContainer interfaces = ipv4AddrHelper.Assign(devices);
		Ipv4InterfaceContainer iic_point_to_point = ipv4AddrHelper.Assign(
				ndc_point_to_point);
		//Ipv4GlobalRoutingHelper::PopulateRoutingTables();
	}

	{
		DceManagerHelper processManager1;
		processManager1.SetNetworkStack("ns3::Ns3SocketFdFactory");
		processManager1.Install(nodes.Get(0));
	}

	{
		QuaggaHelper quagga1;
		quagga1.EnableOspf(nodes.Get(0), "10.0.0.0/24");
		quagga1.EnableOspfDebug(nodes.Get(0));
		quagga1.EnableZebraDebug(nodes.Get(0));
		quagga1.Install(nodes.Get(0));
	}

	{
		DceManagerHelper processManager2;
		processManager2.SetNetworkStack("ns3::Ns3SocketFdFactory");
		processManager2.Install(nodes.Get(1));
	}

	{
		QuaggaHelper quagga2;
		quagga2.EnableOspf(nodes.Get(1), "10.0.0.0/24");
		quagga2.EnableOspfDebug(nodes.Get(1));
		quagga2.EnableZebraDebug(nodes.Get(1));
		quagga2.Install(nodes.Get(1));
	}

	pointToPoint.EnablePcapAll("DceQuaggaOspfdSetRoutingProtocolTestCase");
	csma_helper.EnablePcapAll("DceQuaggaOspfdSetRoutingProtocolTestCase");

	if (stopTime != 0) {
		Simulator::Stop(Seconds(stopTime));
	}
	Simulator::Run();
	Simulator::Destroy();
}//DceQuaggaOspfdSetRoutingProtocolTestCase::DoRun

class DceQuaggaOspfd3TestCase: public TestCase {
public:
	DceQuaggaOspfd3TestCase() :
		ns3::TestCase("DceQuaggaOspfd3TestCase") {
	}
	virtual ~DceQuaggaOspfd3TestCase() {
	}

private:
	virtual void DoRun(void);
}; //class DceQuaggaOspfd3TestCase

void DceQuaggaOspfd3TestCase::DoRun() {
	NodeContainer nodes;
	nodes.Create(3);
	auto node0 = nodes.Get(0);
	auto node1 = nodes.Get(1);
	auto node2 = nodes.Get(2);
	NodeContainer nodes01(node0, node1);
	NodeContainer nodes02(node0, node2);
	NodeContainer nodes12(node1, node2);

	CsmaHelper csma_helper;
	csma_helper.SetChannelAttribute("DataRate", StringValue("5Mbps"));
	csma_helper.SetChannelAttribute("Delay", StringValue("2ms"));

	auto devices01 = csma_helper.Install(nodes01);
	auto devices02 = csma_helper.Install(nodes02);
	auto devices12 = csma_helper.Install(nodes12);
	NS_ASSERT_MSG(devices01.GetN()==2, devices01.GetN());
	NS_ASSERT_MSG(devices02.GetN()==2, devices02.GetN());
	NS_ASSERT_MSG(devices12.GetN()==2, devices12.GetN());

	{
		// Internet stack install
		InternetStackHelper stack0; // IPv4 is required for GlobalRouteMan
		stack0.Install(node0);

		InternetStackHelper stack1; // IPv4 is required for GlobalRouteMan
		stack1.Install(node1);

		InternetStackHelper stack2; // IPv4 is required for GlobalRouteMan
		stack2.Install(node2);

		NS_ASSERT_MSG(node0->GetNDevices()==3, node0->GetNDevices());
		NS_ASSERT_MSG(node1->GetNDevices()==3, node1->GetNDevices());
		NS_ASSERT_MSG(node2->GetNDevices()==3, node2->GetNDevices());
	}

	{
		auto ipv4_0 = node0->GetObject<ns3::Ipv4> ();
		Ipv4DceRoutingHelper ipv4_routing_helper_0;
		auto ipv4_routing_protocol_0 = ipv4_routing_helper_0.Create(node0);
		ipv4_0->SetRoutingProtocol(ipv4_routing_protocol_0);

		auto ipv4_1 = node1->GetObject<ns3::Ipv4> ();
		Ipv4DceRoutingHelper ipv4_routing_helper_1;
		auto ipv4_routing_protocol_1 = ipv4_routing_helper_1.Create(node1);
		ipv4_1->SetRoutingProtocol(ipv4_routing_protocol_1);

		auto ipv4_2 = node2->GetObject<ns3::Ipv4> ();
		Ipv4DceRoutingHelper ipv4_routing_helper_2;
		auto ipv4_routing_protocol_2 = ipv4_routing_helper_2.Create(node2);
		ipv4_2->SetRoutingProtocol(ipv4_routing_protocol_2);
	}

	{
		Ipv4AddressHelper ipv4AddrHelper;
		ipv4AddrHelper.SetBase("10.0.1.0", "255.255.255.0");
		Ipv4InterfaceContainer interfaces = ipv4AddrHelper.Assign(devices01);
	}

	{
		Ipv4AddressHelper ipv4AddrHelper;
		ipv4AddrHelper.SetBase("10.0.2.0", "255.255.255.0");
		Ipv4InterfaceContainer interfaces = ipv4AddrHelper.Assign(devices02);
	}

	{
		Ipv4AddressHelper ipv4AddrHelper;
		ipv4AddrHelper.SetBase("10.0.3.0", "255.255.255.0");
		Ipv4InterfaceContainer interfaces = ipv4AddrHelper.Assign(devices12);
	}

	{
		DceManagerHelper processManager0;
		processManager0.SetNetworkStack("ns3::Ns3SocketFdFactory");
		processManager0.Install(node0);
	}
	{
		DceManagerHelper processManager1;
		processManager1.SetNetworkStack("ns3::Ns3SocketFdFactory");
		processManager1.Install(node1);
	}
	{
		DceManagerHelper processManager2;
		processManager2.SetNetworkStack("ns3::Ns3SocketFdFactory");
		processManager2.Install(node2);
	}
	{
		QuaggaHelper quagga0;
		quagga0.EnableOspf(node0, "10.0.1.0/24");
		quagga0.EnableOspfDebug(node0);
		quagga0.EnableZebraDebug(node0);
		quagga0.Install(node0);
	}
	{
		QuaggaHelper quagga0;
		quagga0.EnableOspf(node0, "10.0.2.0/24");
		quagga0.EnableOspfDebug(node0);
		quagga0.EnableZebraDebug(node0);
		quagga0.Install(node0);
	}
	{
		QuaggaHelper quagga1;
		quagga1.EnableOspf(node1, "10.0.1.0/24");
		quagga1.EnableOspfDebug(node1);
		quagga1.EnableZebraDebug(node1);
		quagga1.Install(node1);
	}
	{
		QuaggaHelper quagga1;
		quagga1.EnableOspf(node1, "10.0.3.0/24");
		quagga1.EnableOspfDebug(node1);
		quagga1.EnableZebraDebug(node1);
		quagga1.Install(node1);
	}
	{
		QuaggaHelper quagga2;
		quagga2.EnableOspf(node2, "10.0.2.0/24");
		quagga2.EnableOspfDebug(node2);
		quagga2.EnableZebraDebug(node2);
		quagga2.Install(node2);
	}
	{
		QuaggaHelper quagga2;
		quagga2.EnableOspf(node2, "10.0.3.0/24");
		quagga2.EnableOspfDebug(node2);
		quagga2.EnableZebraDebug(node2);
		quagga2.Install(node2);
	}

	csma_helper.EnablePcapAll("DceQuaggaOspfd3TestCase");

	auto output_stream_wrapper = Create<OutputStreamWrapper> (&std::cout);

	Ipv4DceRoutingHelper ipv4_dce_routing_helper;
	ipv4_dce_routing_helper.PrintRoutingTableAllEvery(ns3::Seconds(20.0),
			output_stream_wrapper);

	Simulator::Stop(Seconds(62));
	Simulator::Run();
	Simulator::Destroy();
}//DceQuaggaOspfd3TestCase::DoRun

class DceQuaggaOspfdChannelTestCase: public TestCase {
public:
	DceQuaggaOspfdChannelTestCase() :
		ns3::TestCase("DceQuaggaOspfdChannelTestCase") {
	}
	virtual ~DceQuaggaOspfdChannelTestCase() {
	}

private:
	virtual void DoRun(void);
}; //class DceQuaggaOspfdChannelTestCase

void DceQuaggaOspfdChannelTestCase::DoRun() {
	NodeContainer nodes;
	nodes.Create(3);
	auto node0 = nodes.Get(0);
	auto node1 = nodes.Get(1);
	auto node2 = nodes.Get(2);
	NodeContainer nodes01(node0, node1);
	NodeContainer nodes02(node0, node2);
	NodeContainer nodes12(node1, node2);

	ObjectFactory csma_net_device_factory;
	csma_net_device_factory.SetTypeId(CsmaNetDevice::GetTypeId());
	auto device00 = csma_net_device_factory.Create<CsmaNetDevice> ();
	auto device01 = csma_net_device_factory.Create<CsmaNetDevice> ();
	auto device10 = csma_net_device_factory.Create<CsmaNetDevice> ();
	auto device11 = csma_net_device_factory.Create<CsmaNetDevice> ();
	auto device20 = csma_net_device_factory.Create<CsmaNetDevice> ();
	auto device21 = csma_net_device_factory.Create<CsmaNetDevice> ();
	{
		device00->SetAddress(Mac48Address::Allocate());
		device01->SetAddress(Mac48Address::Allocate());
		device10->SetAddress(Mac48Address::Allocate());
		device11->SetAddress(Mac48Address::Allocate());
		device20->SetAddress(Mac48Address::Allocate());
		device21->SetAddress(Mac48Address::Allocate());
		ObjectFactory queue_factory;
		queue_factory.SetTypeId(DropTailQueue::GetTypeId());
		device00->SetQueue(queue_factory.Create<DropTailQueue> ());
		device01->SetQueue(queue_factory.Create<DropTailQueue> ());
		device10->SetQueue(queue_factory.Create<DropTailQueue> ());
		device11->SetQueue(queue_factory.Create<DropTailQueue> ());
		device20->SetQueue(queue_factory.Create<DropTailQueue> ());
		device21->SetQueue(queue_factory.Create<DropTailQueue> ());
		node0->AddDevice(device00);
		node0->AddDevice(device01);
		node1->AddDevice(device10);
		node1->AddDevice(device11);
		node2->AddDevice(device20);
		node2->AddDevice(device21);
	}

	//NS_ASSERT_MSG(devices01.GetN()==2, devices01.GetN());
	//NS_ASSERT_MSG(devices02.GetN()==2, devices02.GetN());
	//NS_ASSERT_MSG(devices12.GetN()==2, devices12.GetN());

	{
		ObjectFactory object_factory;
		object_factory.SetTypeId(CsmaChannel::GetTypeId());
		object_factory.Set("DataRate", StringValue("5Mbps"));
		object_factory.Set("Delay", StringValue("2ms"));
		auto channel01 = object_factory.Create<CsmaChannel> ();
		auto channel02 = object_factory.Create<CsmaChannel> ();
		auto channel12 = object_factory.Create<CsmaChannel> ();
		device00->Attach(channel01);
		device10->Attach(channel01);
		device01->Attach(channel02);
		device20->Attach(channel02);
		device11->Attach(channel12);
		device21->Attach(channel12);
	}

	NetDeviceContainer devices01, devices02, devices12;
	devices01.Add(device00);
	devices01.Add(device10);
	devices02.Add(device01);
	devices02.Add(device20);
	devices12.Add(device11);
	devices12.Add(device21);

	{
		// Internet stack install
		InternetStackHelper stack0; // IPv4 is required for GlobalRouteMan
		stack0.Install(node0);

		InternetStackHelper stack1; // IPv4 is required for GlobalRouteMan
		stack1.Install(node1);

		InternetStackHelper stack2; // IPv4 is required for GlobalRouteMan
		stack2.Install(node2);

		NS_ASSERT_MSG(node0->GetNDevices()==3, node0->GetNDevices());
		NS_ASSERT_MSG(node1->GetNDevices()==3, node1->GetNDevices());
		NS_ASSERT_MSG(node2->GetNDevices()==3, node2->GetNDevices());
	}

	{
		Ipv4DceRoutingHelper ipv4_dce_routing_helper;
		auto ipv4_routing_protocol = ipv4_dce_routing_helper.Create(node0);
		auto ipv4 = node0->GetObject<ns3::Ipv4> ();
		ipv4->SetRoutingProtocol(ipv4_routing_protocol);
	}
	{
		Ipv4DceRoutingHelper ipv4_dce_routing_helper;
		auto ipv4_routing_protocol = ipv4_dce_routing_helper.Create(node1);
		auto ipv4 = node1->GetObject<ns3::Ipv4> ();
		ipv4->SetRoutingProtocol(ipv4_routing_protocol);
	}
	{
		Ipv4DceRoutingHelper ipv4_dce_routing_helper;
		auto ipv4_routing_protocol = ipv4_dce_routing_helper.Create(node2);
		auto ipv4 = node2->GetObject<ns3::Ipv4> ();
		ipv4->SetRoutingProtocol(ipv4_routing_protocol);
	}
	{
		DceManagerHelper dce_manager_helper;
		dce_manager_helper.SetNetworkStack("ns3::Ns3SocketFdFactory");
		dce_manager_helper.Install(node0);
	}
	{
		DceManagerHelper dce_manager_helper;
		dce_manager_helper.SetNetworkStack("ns3::Ns3SocketFdFactory");
		dce_manager_helper.Install(node1);
	}
	{
		DceManagerHelper dce_manager_helper;
		dce_manager_helper.SetNetworkStack("ns3::Ns3SocketFdFactory");
		dce_manager_helper.Install(node2);
	}
	{
		Ipv4AddressHelper ipv4_address_helper;
		ipv4_address_helper.SetBase("10.0.1.0", "255.255.255.0");
		Ipv4InterfaceContainer interfaces = ipv4_address_helper.Assign(
				devices01);
	}
	{
		Ipv4AddressHelper ipv4_address_helper;
		ipv4_address_helper.SetBase("10.0.2.0", "255.255.255.0");
		Ipv4InterfaceContainer interfaces = ipv4_address_helper.Assign(
				devices02);
	}
	{
		Ipv4AddressHelper ipv4_address_helper;
		ipv4_address_helper.SetBase("10.0.3.0", "255.255.255.0");
		Ipv4InterfaceContainer interfaces = ipv4_address_helper.Assign(
				devices12);
	}
	{
		QuaggaHelper quagga_helper;
		quagga_helper.EnableOspf(node0, "10.0.1.0/24");
		quagga_helper.EnableOspfDebug(node0);
		quagga_helper.EnableZebraDebug(node0);
		quagga_helper.Install(node0);
	}
	{
		QuaggaHelper quagga_helper;
		quagga_helper.EnableOspf(node0, "10.0.2.0/24");
		quagga_helper.EnableOspfDebug(node0);
		quagga_helper.EnableZebraDebug(node0);
		quagga_helper.Install(node0);
	}
	{
		QuaggaHelper quagga_helper;
		quagga_helper.EnableOspf(node1, "10.0.1.0/24");
		quagga_helper.EnableOspfDebug(node1);
		quagga_helper.EnableZebraDebug(node1);
		quagga_helper.Install(node1);
	}
	{
		QuaggaHelper quagga_helper;
		quagga_helper.EnableOspf(node1, "10.0.3.0/24");
		quagga_helper.EnableOspfDebug(node1);
		quagga_helper.EnableZebraDebug(node1);
		quagga_helper.Install(node1);
	}
	{
		QuaggaHelper quagga_helper;
		quagga_helper.EnableOspf(node2, "10.0.2.0/24");
		quagga_helper.EnableOspfDebug(node2);
		quagga_helper.EnableZebraDebug(node2);
		quagga_helper.Install(node2);
	}
	{
		QuaggaHelper quagga_helper;
		quagga_helper.EnableOspf(node2, "10.0.3.0/24");
		quagga_helper.EnableOspfDebug(node2);
		quagga_helper.EnableZebraDebug(node2);
		quagga_helper.Install(node2);
	}
	{
		CsmaHelper csma_helper;
		csma_helper.EnablePcapAll("DceQuaggaOspfdChannelTestCase");
	}
	{
		auto output_stream_wrapper = Create<OutputStreamWrapper> (&std::cout);
		Ipv4DceRoutingHelper ipv4_dce_routing_helper;
		ipv4_dce_routing_helper.PrintRoutingTableAllEvery(ns3::Seconds(10.0),
				output_stream_wrapper);
	}
	Simulator::Stop(Seconds(120));
	Simulator::Run();
	Simulator::Destroy();
}//DceQuaggaOspfdChannelTestCase::DoRun

class DceQuaggaOspfdTestSuite: public TestSuite {
public:
	DceQuaggaOspfdTestSuite() :
		ns3::TestSuite("DceQuaggaOspfdTestSuite", UNIT) {
		//NS_LOG_UNCOND("adding a test case");
		AddTestCase(new DceQuaggaOspfdTestCase, TestCase::QUICK);
		AddTestCase(new DceQuaggaOspfdSeparatedTestCase, TestCase::QUICK);
		AddTestCase(new DceQuaggaOspfdSetRoutingProtocolTestCase,
				TestCase::QUICK);
		AddTestCase(new DceQuaggaOspfd3TestCase, TestCase::QUICK);
		AddTestCase(new DceQuaggaOspfdChannelTestCase, TestCase::QUICK);
	}
};

static DceQuaggaOspfdTestSuite dce_quagga_ospfd_test_suite;
