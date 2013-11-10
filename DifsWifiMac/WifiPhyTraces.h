/*
 * WifiPhyTraces.h
 *
 *  Created on: 2013/11/10
 *      Author: Takashi
 */

#ifndef WIFIPHYTRACES_H_
#define WIFIPHYTRACES_H_
#include "ns3/ptr.h"
#include "ns3/log.h"
#include "ns3/wifi-phy.h"
namespace abe {
class WifiPhyTraces {
public:
	WifiPhyTraces(){}

	void install(ns3::Ptr<ns3::WifiPhy> ptr_wifi_phy);
	void install(ns3::WifiPhy& wifi_phy);
	virtual ~WifiPhyTraces(){};

private:
	void phyTxBeginTraceCallback(ns3::Ptr<const ns3::Packet> packet);
	void phyTxEndTraceCallback(ns3::Ptr<const ns3::Packet> packet);
	void phyTxDropTraceCallback(ns3::Ptr<const ns3::Packet> packet);
	void phyRxBeginTraceCallback(ns3::Ptr<const ns3::Packet> packet);
	void phyRxEndTraceCallback(ns3::Ptr<const ns3::Packet> packet);
	void phyRxDropTraceCallback(ns3::Ptr<const ns3::Packet> packet);
	void monitorSnifferRx(ns3::Ptr<const ns3::Packet>, uint16_t, uint16_t, uint32_t, bool, double, double);
	void monitorSnifferTx(ns3::Ptr<const ns3::Packet>, uint16_t, uint16_t, uint32_t, bool);
};//WifiPhyTraces
}//abe
#endif /* WIFIPHYTRACES_H_ */
