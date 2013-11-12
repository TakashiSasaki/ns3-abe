/*
 * EunetSwitchTest.cc
 *
 *  Created on: 2013/10/28
 *      Author: w535070h
 */

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
NS_LOG_COMPONENT_DEFINE ("EunetSwitchTest");

int main(int argc, char *argv[]) {
        LogComponentEnable ("EunetSwitchTest", LOG_LEVEL_INFO);
        int nSwitches = 1;
        CommandLine command_line;
        //command_line.AddValue("nDownlinkPorts", "number of downlink ports on a switch", nDownlinkPorts);
        //command_line.AddValue("nSwitches", "number of switches", nSwitches);
        //command_line.Parse(argc, argv);

        Ptr<EunetSwitch> ptr_root_switch(new EunetSwitch());
        Ptr<EunetSwitch> ptr_distribution_switches[nSwitches];
        for(int i=0; i<nSwitches; ++i){
                ptr_distribution_switches[i] = new EunetSwitch();
        }//for

        for (int i = 0; i < nSwitches; ++i) {
                NS_LOG_INFO("Connecting distribution switches to the root switch.");
                ptr_distribution_switches[i]->connectUpTo(0, ptr_root_switch, i);
        }//for

        NS_LOG_INFO ("Assigning IP Addresses.");
        Ipv4AddressHelper ipv4_address_helper;
        ipv4_address_helper.SetBase("10.1.0.0", "255.255.0.0");
        for (int i = 0; i < nSwitches; ++i) {
                ipv4_address_helper.Assign(
                                ptr_distribution_switches[i]->getTerminalDevices());
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
                                ptr_distribution_switches[i]->getTerminals());
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
                                ptr_distribution_switches[i]->getTerminals());
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
        // csma-bridge-<nodeId>-<interfaceId>.pcap
        // and can be read by the "tcpdump -r" command (use "-tt" option to
        // display timestamps correctly)
        //
        //csma_helper.EnablePcapAll("csma-bridge",false);

        /*for(int i=0; i < nSwitches; i++){
        csma_helper.EnablePcap("csma-bridge", ns3::NodeContainer(ptr_distribution_switches[i]) ,false);
        }//for
         */
        csma_helper.EnablePcap("csma-bridge", ns3::NodeContainer(ptr_root_switch) ,false);

        Ptr<Node> ptr_node1(new EunetSwitch());
        Ptr<Node> ptr_node2(new EunetSwitch());
        {
                CsmaHelper csma_helper;
                NetDeviceContainer ndc = csma_helper.Install(NodeContainer(ptr_node1, ptr_node2));
                BridgeHelper bridge_helper1;
                bridge_helper1.Install(ptr_node1 ,NetDeviceContainer(ndc.Get(1)));
                BridgeHelper bridge_helper2;
                bridge_helper2.Install(ptr_node2 ,NetDeviceContainer(ndc.Get(0)));
        }

#if 0
        NS_LOG_INFO ("Run Simulation.");
        Simulator::Run();
        Simulator::Destroy();
        NS_LOG_INFO ("Done.");
#endif

        return EXIT_SUCCESS;
}//main
