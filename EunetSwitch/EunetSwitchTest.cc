/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
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
 */

// Network topology
//
//        n0     n1
//        |      | 
//       ----------
//       | Switch |
//       ----------
//        |      | 
//        n2     n3
//
//
// - CBR/UDP flows from n0 to n1 and from n3 to n0
// - DropTail queues 
// - Tracing of queues and packet receptions to file "csma-bridge.tr"

#include <iostream>
#include <fstream>
#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/applications-module.h"
#include "ns3/bridge-module.h"
#include "ns3/csma-module.h"
#include "ns3/internet-module.h"
#include "EunetSwitch.h"

using namespace ns3;
NS_LOG_COMPONENT_DEFINE ("CsmaBridgeforEUNET");

int main(int argc, char *argv[]) {
	//
	// Users may find it convenient to turn on explicit debugging
	// for selected modules; the below lines suggest how to do this
	//
	LogComponentEnable ("CsmaBridgeforEUNET", LOG_LEVEL_INFO);

	//
	// Allow the user to override any of the defaults and the above Bind() at
	// run-time, via command-line arguments
	//
	//int nDownlinkPorts;
	int nSwitches = 2;
	CommandLine command_line;
	//command_line.AddValue("nDownlinkPorts", "number of downlink ports on a switch", nDownlinkPorts);
	//command_line.AddValue("nSwitches", "number of switches", nSwitches);
	//command_line.Parse(argc, argv);


	EunetSwitch root_switch;
	NS_LOG_INFO("Creating switches");
	EunetSwitch distribution_switches[nSwitches];

	for (int i = 0; i < nSwitches; ++i) {
		NS_LOG_INFO("Connecting distribution switches to the root switch.");
		distribution_switches[i].connectUpTo(0, root_switch, i);
	}//for

	NS_LOG_INFO ("Assign IP Addresses.");
	Ipv4AddressHelper ipv4_address_helper;
	ipv4_address_helper.SetBase("10.1.1.0", "255.255.255.0");
	for (int i = 0; i < nSwitches; ++i) {
		ipv4_address_helper.Assign(
				distribution_switches[i].getTerminalDevices());
	}//for

	//
	// Create an OnOff application to send UDP datagrams from node zero to node 1.
	//
	NS_LOG_INFO ("Create Applications.");
	uint16_t port = 9; // Discard port (RFC 863)

	OnOffHelper on_off_helper("ns3::UdpSocketFactory", Address(
			InetSocketAddress(Ipv4Address("10.1.1.2"), port)));
	on_off_helper.SetConstantRate(DataRate("500kb/s"));
	on_off_helper.SetAttribute("Remote", AddressValue(InetSocketAddress(Ipv4Address(
			"10.1.1.1"), port)));

	ApplicationContainer on_off_applications;
	for (int i = 0; i < nSwitches; ++i) {
		ApplicationContainer ac = on_off_helper.Install(
				distribution_switches[i].getTerminals());
		on_off_applications.Add(ac);
	}//for

	// Start the application
	on_off_applications.Start(Seconds(1.0));
	on_off_applications.Stop(Seconds(10.0));

	// Create an optional packet sink to receive these packets
	PacketSinkHelper packet_sink_helper("ns3::UdpSocketFactory", Address(
			InetSocketAddress(Ipv4Address::GetAny(), port)));
	ApplicationContainer packet_sink_applications;
	for (int i = 0; i < nSwitches; ++i) {
		ApplicationContainer ac = packet_sink_helper.Install(
				distribution_switches[i].getTerminals());
		packet_sink_applications.Add(ac);
	}//for
	packet_sink_applications.Start(Seconds(0.0));


	NS_LOG_INFO ("Configure Tracing.");

	//
	// Configure tracing of all enqueue, dequeue, and NetDevice receive events.
	// Trace output will be sent to the file "csma-bridge.tr"
	//
	AsciiTraceHelper ascii;
	CsmaHelper csma_helper;
	csma_helper.EnableAsciiAll(ascii.CreateFileStream("csma-bridge.tr"));

	//
	// Also configure some tcpdump traces; each interface will be traced.
	// The output files will be named:
	//     csma-bridge-<nodeId>-<interfaceId>.pcap
	// and can be read by the "tcpdump -r" command (use "-tt" option to
	// display timestamps correctly)
	//
	csma_helper.EnablePcapAll("csma-bridge", false);

	//
	// Now, do the actual simulation.
	//
	NS_LOG_INFO ("Run Simulation.");
	Simulator::Run();
	Simulator::Destroy();
	NS_LOG_INFO ("Done.");

	return 0;
}