#ifndef TRACEBASE_H_
#define TRACEBASE_H_
#include "ns3/packet.h"
#include "ns3/node.h"

class TraceBase {
protected:
	ns3::Ptr<ns3::Node> ptrNode;
	TraceBase(ns3::Node* p_node);
	TraceBase(ns3::Ptr<ns3::Node> node);
public:
	virtual ~TraceBase();
protected:
	static void getHex(std::ostream&, ns3::Ptr<const ns3::Packet> ptr_packet);
};

#endif /* TRACEBASE_H_ */
