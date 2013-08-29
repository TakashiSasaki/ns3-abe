/* -*-  Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2009 The Boeing Company
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
 */

#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/mobility-module.h"
#include "ns3/config-store-module.h"
#include "ns3/wifi-module.h"
#include "ns3/internet-module.h"
#include "ns3/propagation-module.h"
#include "ns3/olsr-helper.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

NS_LOG_COMPONENT_DEFINE ("WifiBufferTest");

using namespace ns3;

void ReceivePacket (Ptr<Socket> socket)
{
  NS_LOG_UNCOND ("Received one packet!");
}

static void GenerateTraffic (Ptr<Socket> socket, uint32_t pktSize)                             
{
  socket->Send (Create<Packet> (pktSize));
}

int main (int argc, char *argv[])
{
  std::string phyMode ("DsssRate1Mbps");
  double rss = -80;  // -dBm
  double Prss = -80;
  uint32_t packetSize = 1000; // bytes
  uint32_t numPackets = 10;
  double interval = 0.001; // seconds
  bool verbose = false;
  double offset = 91;
  
  CommandLine cmd;

  cmd.AddValue ("phyMode", "Wifi Phy mode", phyMode);
  cmd.AddValue ("rss", "received signal strength", rss);
  cmd.AddValue ("packetSize", "size of application packet sent", packetSize);
  cmd.AddValue ("numPackets", "number of packets generated", numPackets);
  cmd.AddValue ("interval", "interval (seconds) between packets", interval);
  cmd.AddValue ("verbose", "turn on all WifiNetDevice log components", verbose);

  cmd.Parse (argc, argv);

  // disable fragmentation for frames below 2200 bytes
  Config::SetDefault ("ns3::WifiRemoteStationManager::FragmentationThreshold", StringValue ("2200"));
  // turn off RTS/CTS for frames below 2200 bytes
  Config::SetDefault ("ns3::WifiRemoteStationManager::RtsCtsThreshold", StringValue ("2200"));
  // Fix non-unicast data rate to be the same as that of unicast
  Config::SetDefault ("ns3::WifiRemoteStationManager::NonUnicastMode", 
                      StringValue (phyMode));
  //キューが保持できる最大パケット数を1に制限
  Config::SetDefault ("ns3::DropTailQueue::MaxPackets", UintegerValue (1));
    
  NodeContainer c;
  c.Create (4);

  // The below set of helpers will help us to put together the wifi NICs we want
  WifiHelper wifi_helper;
  if (verbose)
    {
      wifi_helper.EnableLogComponents ();  // Turn on all Wifi logging
    }
  wifi_helper.SetStandard (WIFI_PHY_STANDARD_80211b);


  // 2. Place nodes somehow, this is required by every wireless simulation
  for (size_t i = 0; i < 4; ++i)
    {
      c.Get (i)->AggregateObject (CreateObject<ConstantPositionMobilityModel> ());
    }
  
  YansWifiPhyHelper wifiPhy =  YansWifiPhyHelper::Default ();
  // set it to zero; otherwise, gain will be added
  wifiPhy.Set ("RxGain", DoubleValue (0) );
  wifiPhy.Set ("CcaMode1Threshold", DoubleValue (0.0) );
  
  // 4. Create & setup wifi channel
  YansWifiChannelHelper wifiChannel;
  wifiChannel.SetPropagationDelay ("ns3::ConstantSpeedPropagationDelayModel");
  wifiChannel.AddPropagationLoss ("ns3::LogDistancePropagationLossModel");
  wifiPhy.SetChannel (wifiChannel.Create ());

  // 5. Install wireless devices
  NqosWifiMacHelper wifiMac = NqosWifiMacHelper::Default ();
  wifiMac.SetType ("ns3::AdhocWifiMac"); // use ad-hoc MAC
  //NetDeviceContainer devices = wifi.Install (wifiPhy, wifiMac, c);
  wifi_helper.SetStandard (WIFI_PHY_STANDARD_80211b);
  wifi_helper.SetRemoteStationManager ("ns3::ConstantRateWifiManager",
                                "DataMode",StringValue (phyMode),
                                "ControlMode",StringValue (phyMode));

  NetDeviceContainer devices;
  
  for ( int j = 0; j < 4; j++ ) {
    wifiPhy.Set ("EnergyDetectionThreshold", DoubleValue (0.0) );
    wifiPhy.Set ("TxGain", DoubleValue (offset + Prss) ); 
    devices.Add (wifi_helper.Install (wifiPhy, wifiMac, c.Get (j)));
  }
    
  MobilityHelper mobility;
  Ptr<ListPositionAllocator> positionAlloc = CreateObject<ListPositionAllocator> ();
  positionAlloc->Add (Vector (0.0, 0.0, 0.0));
  positionAlloc->Add (Vector (1.0, 0.0, 0.0));
  positionAlloc->Add (Vector (2.0, 0.0, 0.0));
  positionAlloc->Add (Vector (3.0, 0.0, 0.0));
  mobility.SetPositionAllocator (positionAlloc);
  mobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
  mobility.Install (c);

    // Enable OLSR
  OlsrHelper olsr;
  Ipv4StaticRoutingHelper staticRouting;

  Ipv4ListRoutingHelper list;
  list.Add (staticRouting, 0);
  list.Add (olsr, 10);

  InternetStackHelper internet;
  internet.SetRoutingHelper (list); // has effect on the next Install ()
  internet.Install (c);
  
  Ipv4AddressHelper ipv4;
  NS_LOG_INFO ("Assign IP Addresses.");
  ipv4.SetBase ("10.1.1.0", "255.255.255.0");
  Ipv4InterfaceContainer i = ipv4.Assign (devices);

  TypeId tid = TypeId::LookupByName ("ns3::UdpSocketFactory");
  Ptr<Socket> recvSink = Socket::CreateSocket (c.Get (1), tid);
  InetSocketAddress local = InetSocketAddress (Ipv4Address::GetAny (), 80);
  recvSink->Bind (local);
  //recvSink->SetRecvCallback (MakeCallback (&ReceivePacket));

  Ptr<Socket> recvSink2 = Socket::CreateSocket (c.Get (2), tid);
  InetSocketAddress local2 = InetSocketAddress (Ipv4Address::GetAny (), 80);
  recvSink2->Bind (local2);
  //recvSink2->SetRecvCallback (MakeCallback (&ReceivePacket));

  Ptr<Socket> recvSink3 = Socket::CreateSocket (c.Get (3), tid);
  InetSocketAddress local3 = InetSocketAddress (Ipv4Address::GetAny (), 80);
  recvSink3->Bind (local3);
  recvSink3->SetRecvCallback (MakeCallback (&ReceivePacket));

  Ptr<Socket> source = Socket::CreateSocket (c.Get (0), tid);
  InetSocketAddress remote = InetSocketAddress (Ipv4Address ("10.1.1.4"), 80);
  source->SetAllowBroadcast (true);
  source->Connect (remote);

  Ptr<Socket> source2 = Socket::CreateSocket (c.Get (1), tid);
  InetSocketAddress remote2 = InetSocketAddress (Ipv4Address ("10.1.1.4"), 80);
  source2->SetAllowBroadcast (true);
  source2->Connect (remote2);

  Ptr<Socket> source3 = Socket::CreateSocket (c.Get (2), tid);
  InetSocketAddress remote3 = InetSocketAddress (Ipv4Address ("10.1.1.4"), 80);
  source3->SetAllowBroadcast (true);
  source3->Connect (remote3);
  

  // Tracing
  wifiPhy.EnablePcap ("wifi-buffer-test", devices);

  // Output what we are doing
  NS_LOG_UNCOND ("Testing " << numPackets  << " packets sent with receiver rss " << rss );

  double t = 32.0;
  while (numPackets != 0) {
    Simulator::ScheduleWithContext (source->GetNode ()->GetId (),
                                    Seconds (t += interval), &GenerateTraffic, 
                                    source, packetSize);
    
    numPackets -= 1;
  }
  
  Simulator::Stop (Seconds (34.0));
  Simulator::Run ();
  Simulator::Destroy ();

  return 0;
}
