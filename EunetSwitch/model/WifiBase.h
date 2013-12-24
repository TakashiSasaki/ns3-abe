#ifndef WIFIBASE_H_
#define WIFIBASE_H_
#include "ns3/node.h"
#include "ns3/ssid.h"
class WifiBase {
	ns3::Ptr<ns3::Node> ptrNode;
	ns3::Ssid ssid;
	unsigned ifIndex;
public:
	void setSsid(const ns3::Ssid& ssid);
protected:
	WifiBase(ns3::Node* p_node);
	virtual ~WifiBase();
	void DoInitialize();
};

#endif /* WIFIBASE_H_ */
