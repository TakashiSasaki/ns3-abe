#ifndef TRACEBASE_H_
#define TRACEBASE_H_
#include "ns3/packet.h"

class TraceBase {
protected:
	ns3::Ptr<ns3::Node> ptrNode;
public:
	TraceBase(ns3::Node* p_node);
	virtual ~TraceBase();
protected:
	static void getHex(std::ostream&, ns3::Ptr<const ns3::Packet> ptr_packet);
};

#endif /* TRACEBASE_H_ */
