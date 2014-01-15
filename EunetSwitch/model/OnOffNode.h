#ifndef ONOFFNODE_H_
#define ONOFFNODE_H_
#include "init.h"
#include "PacketSinkNode.h"

class OnOffNode: public PacketSinkNode {
	//ns3::ApplicationContainer onOffApplication;
	//const bool startAtTheBeginning;
	ns3::Time onOffStartTime;
	ns3::Time onOffStopTime;
	ns3::DataRate onOffDataRate;
	std::string onOffRemote;
public:
	static ns3::TypeId GetTypeId(void);
	OnOffNode(const bool start_at_the_beginning = false);
	virtual ~OnOffNode() {
	}
	;
	void startAt(ns3::Time start_seconds = ns3::Seconds(0.0));
	void stopAt(ns3::Time stop_seconds = ns3::Seconds(10.0));
	void setRemote(ns3::Ipv4Address&);
private:
	void installOnOffApplication();
	static const int ON_OFF_APPLICATION_UDP_PORT = 10009;
DECLARE_DIDDNCC
};

#endif /* ONOFFNODE_H_ */
