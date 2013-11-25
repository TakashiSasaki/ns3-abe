#ifndef ONOFFNODE_H_
#define ONOFFNODE_H_
#include "PacketSinkNode.h"

class OnOffNode: public PacketSinkNode {
	typedef PacketSinkNode Base;
	ns3::ApplicationContainer onOffApplication;
public:
	static ns3::TypeId GetTypeId(void);
	OnOffNode();
	virtual ~OnOffNode();
	void startAt(ns3::Time start_seconds = ns3::Seconds(0.0));
	void stopAt(ns3::Time stop_seconds = ns3::Seconds(10.0));
	void setRemote(ns3::Ptr<PacketSinkNode> ptr_remote);
protected:
	virtual void DoInitialize();
	virtual void NotifyConstructionCompleted();
private:
	void installOnOffApplication();
	static const int ON_OFF_APPLICATION_UDP_PORT = 10009;
};

#endif /* ONOFFNODE_H_ */
