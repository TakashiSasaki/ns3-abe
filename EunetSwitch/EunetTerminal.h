#ifndef EUNETTERMINAL_H_
#define EUNETTERMINAL_H_

#include "ns3/node.h"
#include "ns3/application-container.h"
#include "ns3/nstime.h"
#include "ns3/ipv4-address-helper.h"
#include "PacketSinkNode.h"

class EunetTerminal: public PacketSinkNode {
	ns3::ApplicationContainer onOffApplication;
public:
	static ns3::TypeId GetTypeId(void);
	EunetTerminal();
	virtual ~EunetTerminal();
	void installInternetStack();
	void startOnOffApplication(ns3::Time start_seconds = ns3::Seconds(0.0));
	void stopOnOffApplication(ns3::Time stop_seconds = ns3::Seconds(10.0));
	void setRemote(ns3::Ptr<EunetTerminal> ptr_remote);
	void assignAddress(ns3::Ipv4AddressHelper&);
protected:
	virtual void DoInitialize();
	virtual void NotifyConstructionCompleted();
private:
	void installOnOffApplication();
	static const int ON_OFF_APPLICATION_UDP_PORT = 10009;
};//EunetTerminal

#endif /* EUNETTERMINAL_H_ */
