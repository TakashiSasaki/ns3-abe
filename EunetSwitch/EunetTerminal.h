#ifndef EUNETTERMINAL_H_
#define EUNETTERMINAL_H_

#include "ns3/node.h"
#include "ns3/application-container.h"
#include "ns3/nstime.h"

class EunetTerminal: public ns3::Node {
	ns3::ApplicationContainer onOffApplication;
	ns3::ApplicationContainer packetSync;
public:
	static ns3::TypeId GetTypeId(void);
	EunetTerminal();
	virtual ~EunetTerminal();
	ns3::Ipv4Address getAddress();
	void startOnOffApplication(ns3::Time start_seconds = ns3::Seconds(0.0));
	void stopOnOffApplication(ns3::Time stop_seconds = ns3::Seconds(10.0));
private:
	static const int PACKET_SYNC_UDP_PORT = 9; // Discard port (RFC 863)
	static const int ON_OFF_APPLICATION_UDP_PORT = 10009;
	void installPacketSync();
	void installOnOffApplication();
};

#endif /* EUNETTERMINAL_H_ */
