#ifndef ONOFFNODE_H_
#define ONOFFNODE_H_
#include "init.h"
#include "PacketSinkNode.h"

class OnOffNode: public PacketSinkNode {
	ns3::Time onOffStartTime;
	ns3::Time onOffStopTime;
	ns3::DataRate onOffDataRate;
	std::string onOffRemote;
	unsigned long totalTxBytes;
	unsigned long totalTxPackets;
public:
	static ns3::TypeId GetTypeId(void);
	OnOffNode(const bool start_at_the_beginning = false);
	virtual ~OnOffNode();
	void setRemote(const ns3::Ipv4Address&);
	ns3::Address getRemote();
	unsigned long getTotalTxBytes();
	unsigned long getTotalTxPackets();
private:
	static const int ON_OFF_APPLICATION_UDP_PORT = 10009;
	void traceTxCallback(ns3::Ptr<const ns3::Packet>);
DECLARE_DIDDNCC
};

#endif /* ONOFFNODE_H_ */
