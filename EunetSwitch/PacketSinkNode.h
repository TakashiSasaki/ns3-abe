#ifndef PACKETSINKNODE_H_
#define PACKETSINKNODE_H_
#include "CsmaInternetNode.h"

class PacketSinkNode: public CsmaInternetNode {
public:
	static ns3::TypeId GetTypeId(void);
	PacketSinkNode();
	virtual ~PacketSinkNode();
protected:
	virtual void DoInitialize();
	virtual void NotifyConstructionCompleted();
};

#endif /* PACKETSINKNODE_H_ */
