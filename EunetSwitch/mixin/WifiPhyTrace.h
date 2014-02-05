#ifndef WIFIPHYTRACE_H_
#define WIFIPHYTRACE_H_

#include "ns3/node.h"
#include "ns3/packet.h"
#include "TraceBase.h"

class WifiPhyTrace: virtual public TraceBase {
public:
	WifiPhyTrace(ns3::Ptr<ns3::Node> node);
	virtual ~WifiPhyTrace();
private:
	void tracePhyTxBegin(ns3::Ptr<const ns3::Packet>) const;
	void tracePhyTxEnd(ns3::Ptr<const ns3::Packet>) const;
	void tracePhyTxDrop(ns3::Ptr<const ns3::Packet>) const;
	void tracePhyRxBegin(ns3::Ptr<const ns3::Packet>) const;
	void tracePhyRxEnd(ns3::Ptr<const ns3::Packet>) const;
	void tracePhyRxDrop(ns3::Ptr<const ns3::Packet>) const;
};

#endif /* WIFIPHYTRACE_H_ */
