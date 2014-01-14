#ifndef ONOFFNODE_H_
#define ONOFFNODE_H_
#include "init.h"
#include "PacketSinkNode.h"

class OnOffNode: public PacketSinkNode {
	ns3::ApplicationContainer onOffApplication;
	const bool startAtTheBeginning;
public:
	static ns3::TypeId GetTypeId(void);
	OnOffNode(const bool start_at_the_beginning = false);
	virtual ~OnOffNode() {
	}
	;
	void startAt(ns3::Time start_seconds = ns3::Seconds(0.0));
	void stopAt(ns3::Time stop_seconds = ns3::Seconds(10.0));
	template<class T>
	void setRemote(ns3::Ptr<PacketSinkNode> ptr_remote);
private:
	void installOnOffApplication();
	static const int ON_OFF_APPLICATION_UDP_PORT = 10009;
DECLARE_DIDDNCC
};

template<class T>
void OnOffNode::setRemote(ns3::Ptr<PacketSinkNode> ptr_remote) {
	this->onOffApplication.Get(0)->SetAttribute("Remote", ns3::AddressValue(
			ns3::InetSocketAddress(ptr_remote->getAddress<T> (0),
					PACKET_SINK_UDP_PORT)));
}

#endif /* ONOFFNODE_H_ */
