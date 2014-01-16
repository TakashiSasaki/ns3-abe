#ifndef WIFIPHYTRACE_H_
#define WIFIPHYTRACE_H_

#include "ns3/node.h"
#include "ns3/packet.h"
#include "TraceBase.h"

class WifiPhyTrace: virtual public TraceBase {
public:
	WifiPhyTrace(ns3::Node* p_node);
	virtual ~WifiPhyTrace();
public:
	virtual void DoInitialize();
	virtual void NotifyConstructionCompleted();
	virtual void DoDispose();
private:
	void tracePhyTxBegin(ns3::Ptr<const ns3::Packet>) const;
	void tracePhyTxEnd(ns3::Ptr<const ns3::Packet>) const;
	void tracePhyTxDrop(ns3::Ptr<const ns3::Packet>) const;
	void tracePhyRxBegin(ns3::Ptr<const ns3::Packet>) const;
	void tracePhyRxEnd(ns3::Ptr<const ns3::Packet>) const;
	void tracePhyRxDrop(ns3::Ptr<const ns3::Packet>) const;
};

#endif /* WIFIPHYTRACE_H_ */
