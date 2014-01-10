#ifndef PACKETSINKNODE_H_
#define PACKETSINKNODE_H_
#include "CsmaInternetNode.h"

class PacketSinkNode: public CsmaInternetNode {
	typedef CsmaInternetNode Base;
public:
	static ns3::TypeId GetTypeId(void);
	PacketSinkNode();
	virtual ~PacketSinkNode(){};
	uint32_t getTotalRx();
	void logTotalRx(const ns3::LogLevel log_level = ns3::LOG_LEVEL_INFO);
protected:
	virtual void DoInitialize();
	virtual void NotifyConstructionCompleted();
	virtual void DoDispose();
protected:
	static const int PACKET_SINK_UDP_PORT = 9; // Discard port (RFC 863)
private:
	ns3::ApplicationContainer packetSink;
};

#endif /* PACKETSINKNODE_H_ */
