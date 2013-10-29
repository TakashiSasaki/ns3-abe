/*
 * WifiNodeContainer.h
 *
 *  Created on: 2013/10/29
 *      Author: sasaki
 */

#ifndef WIFINODECONTAINER_H_
#define WIFINODECONTAINER_H_
#include "ns3/yans-wifi-helper.h"
#include "difs-wifi-mac.h"
#include "difs-wifi-mac-helper.h"
#include "ConstantMobilityNodeContainer.h"
namespace abe {
class WifiNodeContainer : public ConstantMobilityNodeContainer{
public:
	WifiNodeContainer(const double txGain = 56);
	virtual ~WifiNodeContainer();
private:
	double txGain;
private:
	ns3::YansWifiChannelHelper& getYansWifiChannelHelper();
	ns3::YansWifiPhyHelper& getYansWifiPhyHelper();
	abe::DifsWifiMacHelper& getDifsWifiMacHelper();
	ns3::Ptr<ns3::YansWifiPhy> getYansWifiPhy(const int i_node) ;
	ns3::Ptr<ns3::WifiNetDevice> getWifiNetDevice(const int i_node) ;
	virtual void receivePacketAtPhy(ns3::Ptr<ns3::Packet> ptr_packet, double snr, ns3::WifiMode wifi_mode, enum ns3::WifiPreamble wifi_preamble);
};//WifiNodeContainer
}//abe
#endif /* WIFINODECONTAINER_H_ */
