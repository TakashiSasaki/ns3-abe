#ifndef WIFIBASE_H_
#define WIFIBASE_H_
#include "ns3/node.h"
#include "ns3/ssid.h"
#include "ns3/wifi-net-device.h"
#include "CsmaNode.h"
#include <memory>
class WifiBase {
	ns3::Ptr<ns3::Node> ptrNode;
	ns3::Ssid ssid;
	unsigned ifIndex;
public:
	void setSsid(const ns3::Ssid& ssid);
	typedef const char* WifiMacTypeString;
	static WifiMacTypeString AdhocWifiMac;
	static WifiMacTypeString ApWifiMac;
	static WifiMacTypeString MeshWifiNeterfaceMac;
	static WifiMacTypeString OcbWifimac;
	static WifiMacTypeString StaWifiMac;
	ns3::Ptr<ns3::WifiNetDevice> getWifiNetDevice();
	void bringWifiBase(WifiBase& foreign_node);
protected:
	WifiBase(ns3::Node* p_node, const WifiMacTypeString, bool active_probing);
	virtual ~WifiBase();
	void DoInitialize();
	static void getHex(std::ostream&, ns3::Ptr<const ns3::Packet> ptr_packet);
private:
	void traceMacTx(ns3::Ptr<const ns3::Packet>) const;
	void traceMacTxDrop(ns3::Ptr<const ns3::Packet>) const;
	void traceMacPromiscRx(ns3::Ptr<const ns3::Packet>) const;
	void traceMacRx(ns3::Ptr<const ns3::Packet>) const;
	void traceMacRxDrop(ns3::Ptr<const ns3::Packet>) const;
	void tracePhyTxBegin(ns3::Ptr<const ns3::Packet>) const;
	void tracePhyTxEnd(ns3::Ptr<const ns3::Packet>) const;
	void tracePhyTxDrop(ns3::Ptr<const ns3::Packet>) const;
	void tracePhyRxBegin(ns3::Ptr<const ns3::Packet>) const;
	void tracePhyRxEnd(ns3::Ptr<const ns3::Packet>) const;
	void tracePhyRxDrop(ns3::Ptr<const ns3::Packet>) const;
	void traceMonitorSnifferRx(ns3::Ptr<const ns3::Packet>, uint16_t, uint16_t,
			uint32_t, bool, double, double) const;
	void traceMonitorSnifferTx(ns3::Ptr<const ns3::Packet>, uint16_t, uint16_t,
			uint32_t, bool, uint8_t) const;
};

#endif /* WIFIBASE_H_ */
