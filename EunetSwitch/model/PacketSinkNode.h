#ifndef PACKETSINKNODE_H_
#define PACKETSINKNODE_H_
#include "init.h"
#include "CsmaInternetNode.h"

class PacketSinkNode: public CsmaInternetNode {
public:
	static ns3::TypeId GetTypeId(void);
	PacketSinkNode();
	virtual ~PacketSinkNode() {
	}
	;
	uint32_t getTotalRx();
	unsigned long getTotalRxPackets();
	void logTotalRx(const ns3::LogLevel log_level = ns3::LOG_LEVEL_INFO);
protected:
	static const int PACKET_SINK_UDP_PORT = 9; // Discard port (RFC 863)
private:
	ns3::ApplicationContainer packetSink;
	void traceRxCallback(ns3::Ptr<const ns3::Packet>, const ns3::Address &);
	unsigned long totalRxPackets;
DECLARE_DIDDNCC
};

#endif /* PACKETSINKNODE_H_ */
