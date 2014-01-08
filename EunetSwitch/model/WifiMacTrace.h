#ifndef WIFIMACTRACE_H_
#define WIFIMACTRACE_H_
#include "ns3/wifi-phy.h"
#include "ns3/node.h"
#include "TraceBase.h"

class WifiMacTrace: virtual public TraceBase {
public:
	WifiMacTrace(ns3::Node* p_node);
	virtual ~WifiMacTrace();
	void DoInitialize();
private:
	void traceMacTx(ns3::Ptr<const ns3::Packet>) const;
	void traceMacTxDrop(ns3::Ptr<const ns3::Packet>) const;
	void traceMacPromiscRx(ns3::Ptr<const ns3::Packet>) const;
	void traceMacRx(ns3::Ptr<const ns3::Packet>) const;
	void traceMacRxDrop(ns3::Ptr<const ns3::Packet>) const;
};//WifiMacTrace

#endif /* WIFIMACTRACE_H_ */
