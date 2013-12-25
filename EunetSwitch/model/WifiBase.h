#ifndef WIFIBASE_H_
#define WIFIBASE_H_
#include "ns3/node.h"
#include "ns3/ssid.h"
#include "ns3/wifi-net-device.h"
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
	void bring(WifiBase& foreign_node);
protected:
	WifiBase(ns3::Node* p_node, const WifiMacTypeString, bool active_probing);
	virtual ~WifiBase();
	void DoInitialize();
private:
	void traceMacTx(ns3::Ptr<const ns3::Packet>) const;
	void traceMacTxDrop(ns3::Ptr<const ns3::Packet>) const;
	void traceMacPromiscRx(ns3::Ptr<const ns3::Packet>) const;
	void traceMacRx(ns3::Ptr<const ns3::Packet>) const;
	void traceMacRxDrop(ns3::Ptr<const ns3::Packet>) const;
};

#endif /* WIFIBASE_H_ */
