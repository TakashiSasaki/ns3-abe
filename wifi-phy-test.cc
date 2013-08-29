/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2005,2006 INRIA
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
 * Author: Mathieu Lacage <mathieu.lacage@sophia.inria.fr>
 */
#include "ns3/wifi-net-device.h"
#include "ns3/yans-wifi-channel.h"
#include "ns3/yans-wifi-phy.h"
#include "ns3/propagation-loss-model.h"
#include "ns3/propagation-delay-model.h"
#include "ns3/error-rate-model.h"
#include "ns3/yans-error-rate-model.h"
#include "ns3/ptr.h"
#include "ns3/mobility-model.h"
#include "ns3/constant-position-mobility-model.h"
#include "ns3/vector.h"
#include "ns3/packet.h"
#include "ns3/simulator.h"
#include "ns3/nstime.h"
#include "ns3/command-line.h"
#include "ns3/flow-id-tag.h"
#include "ns3/log.h"
#include "ns3/core-module.h"

using namespace ns3;


class CollisionExperiment
{
public:
  struct Input
  {
    Input ();
    Time interval;
    double xA;
    double xB;
    std::string txModeA;
    std::string txModeB;
    uint8_t txPowerLevelA;
    uint8_t txPowerLevelB;
    uint32_t packetSizeA;
    uint32_t packetSizeB;
    uint32_t nPackets;
  };
  struct Output
  {
    uint32_t receivedA;
    uint32_t receivedB;
  };
  CollisionExperiment ();

  struct CollisionExperiment::Output Run (struct CollisionExperiment::Input input);
private:
  void SendA (void) const;
  void SendB (void) const;
  void Receive (Ptr<Packet> p, double snr, WifiMode mode, enum WifiPreamble preamble);
  Ptr<WifiPhy> m_txA;
  Ptr<WifiPhy> m_txB;
  uint32_t m_flowIdA;
  uint32_t m_flowIdB;
  struct Input m_input;
  struct Output m_output;
};

void
CollisionExperiment::SendA (void) const
{
  Ptr<Packet> p = Create<Packet> (m_input.packetSizeA);
  p->AddByteTag (FlowIdTag (m_flowIdA));
  m_txA->SendPacket (p, WifiMode (m_input.txModeA),
                     WIFI_PREAMBLE_SHORT, m_input.txPowerLevelA);
}

void
CollisionExperiment::SendB (void) const
{
  Ptr<Packet> p = Create<Packet> (m_input.packetSizeB);
  p->AddByteTag (FlowIdTag (m_flowIdB));
  m_txB->SendPacket (p, WifiMode (m_input.txModeB),
                     WIFI_PREAMBLE_SHORT, m_input.txPowerLevelB);
}

void
CollisionExperiment::Receive (Ptr<Packet> p, double snr, WifiMode mode, enum WifiPreamble preamble)
{
  FlowIdTag tag;
  p->FindFirstMatchingByteTag (tag);
  if (tag.GetFlowId () == m_flowIdA)
    {
      m_output.receivedA++;
    }
  else if (tag.GetFlowId () == m_flowIdB)
    {
      m_output.receivedB++;
    }
}

void myRxOkCallback(Ptr<Packet> p, double snr, WifiMode mode, enum WifiPreamble preamble){
  NS_LOG_UNCOND("myRxOkCallback, snr=" << snr);
}

void myRxErrorCallback(Ptr<const Packet> packet, double snr) {
  NS_LOG_UNCOND("myRxErrorCallback, snr="<< snr);
}

CollisionExperiment::CollisionExperiment ()
{
}

CollisionExperiment::Input::Input ()
  : interval (MicroSeconds (0)),
    xA (-5),
    xB (5),
    txModeA ("OfdmRate6Mbps"),
    txModeB ("OfdmRate6Mbps"),
    txPowerLevelA (0),
    txPowerLevelB (0),
    packetSizeA (2304),
    packetSizeB (2304),
    nPackets (400)
{
}

struct CollisionExperiment::Output
CollisionExperiment::Run (struct CollisionExperiment::Input input)
{
  m_output.receivedA = 0;
  m_output.receivedB = 0;
  m_input = input;

  m_flowIdA = FlowIdTag::AllocateFlowId ();
  m_flowIdB = FlowIdTag::AllocateFlowId ();

  Ptr<YansWifiChannel> channel = CreateObject<YansWifiChannel> ();
  channel->SetPropagationDelayModel (CreateObject<ConstantSpeedPropagationDelayModel> ());
  Ptr<LogDistancePropagationLossModel> log = CreateObject<LogDistancePropagationLossModel> ();
  channel->SetPropagationLossModel (log);

  Ptr<MobilityModel> posTxA = CreateObject<ConstantPositionMobilityModel> ();
  posTxA->SetPosition (Vector (input.xA, 0.0, 0.0));
  Ptr<MobilityModel> posTxB = CreateObject<ConstantPositionMobilityModel> ();
  posTxB->SetPosition (Vector (input.xB, 0.0, 0.0));
  Ptr<MobilityModel> posRx = CreateObject<ConstantPositionMobilityModel> ();
  posRx->SetPosition (Vector (0, 0.0, 0.0));

  Ptr<YansWifiPhy> txA = CreateObject<YansWifiPhy> ();
  Ptr<YansWifiPhy> txB = CreateObject<YansWifiPhy> ();


#if 1
  //create rx using ObjectFactory
  ObjectFactory yans_wifi_phy_factory = ObjectFactory();
  yans_wifi_phy_factory.SetTypeId("ns3::YansWifiPhy");
  yans_wifi_phy_factory.Set ("RxGain", DoubleValue (0) );
  yans_wifi_phy_factory.Set ("CcaMode1Threshold", DoubleValue (0.0) );
  //yans_wifi_phy_factory.Set ("EnergyDetectionThreshold", DoubleValue (0.0) );
  yans_wifi_phy_factory.Set ("TxGain", DoubleValue (11) ); 
  Ptr<YansWifiPhy> p_yans_wifi_phy = yans_wifi_phy_factory.Create<YansWifiPhy>();
  //p_yans_wifi_phy->SetErrorRateModel(p_error_rate_model);
  //p_yans_wifi_phy->SetChannel(p_yans_wifi_hannel);
  //p_yans_wifi_phy->SetMobility(node);   
  //p_yans_wifi_phy->SetDevice(device);
  p_yans_wifi_phy->ConfigureStandard(WIFI_PHY_STANDARD_80211b);
  Ptr<YansWifiPhy> rx = p_yans_wifi_phy;
#else
  //create rx using CreateObject
  Ptr<YansWifiPhy> rx = CreateObject<YansWifiPhy>();
#endif

  Ptr<ErrorRateModel> error = CreateObject<YansErrorRateModel> ();
  txA->SetErrorRateModel (error);
  txB->SetErrorRateModel (error);
  rx->SetErrorRateModel (error);
  txA->SetChannel (channel);
  txB->SetChannel (channel);
  rx->SetChannel (channel);
  txA->SetMobility (posTxA);
  txB->SetMobility (posTxB);
  rx->SetMobility (posRx);


  rx->SetReceiveOkCallback (MakeCallback (&CollisionExperiment::Receive, this));
  rx->SetReceiveErrorCallback (MakeCallback (&myRxErrorCallback));

  for (uint32_t i = 0; i < m_input.nPackets; ++i)
    {
      Simulator::Schedule (Seconds (i), &CollisionExperiment::SendA, this);
    }
  for (uint32_t i = 0; i < m_input.nPackets; ++i)
    {
      Simulator::Schedule (Seconds (i) + m_input.interval, &CollisionExperiment::SendB, this);
    }
  m_txA = txA;
  m_txB = txB;
  Simulator::Run ();
  Simulator::Destroy();
  return m_output;
}


static void Run(int argc, char *argv[])
{
  CollisionExperiment::Input input;
  input.nPackets = 100;
  CommandLine cmd;
  cmd.AddValue ("NPackets", "The number of packets to send for each transmitter", input.nPackets);
  cmd.AddValue ("xA", "the position of transmitter A", input.xA);
  cmd.AddValue ("xB", "the position of transmitter B", input.xB);
  for (uint32_t i = 0; i < 100; i += 1)
    {
      CollisionExperiment experiment;
      CollisionExperiment::Output output;
      input.interval = MicroSeconds (i);
      output = experiment.Run (input);
      double perA = (output.receivedA + 0.0) / (input.nPackets + 0.0);
      double perB = (output.receivedB + 0.0) / (input.nPackets + 0.0);
      std::cout << i << " " << perA << " " << perB << std::endl;
    }
  for (uint32_t i = 100; i < 4000; i += 50)
    {
      CollisionExperiment experiment;
      CollisionExperiment::Output output;
      input.interval = MicroSeconds (i);
      output = experiment.Run (input);
      double perA = (output.receivedA + 0.0) / (input.nPackets + 0.0);
      double perB = (output.receivedB + 0.0) / (input.nPackets + 0.0);
      std::cout << i << " " << perA << " " << perB << std::endl;
    }
}



int main (int argc, char *argv[])
{
    Run (argc, argv);
  return 0;
}
