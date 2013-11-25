#ifndef EUNETTERMINAL_H_
#define EUNETTERMINAL_H_

#include "ns3/node.h"
#include "ns3/application-container.h"
#include "ns3/nstime.h"
#include "ns3/ipv4-address-helper.h"
#include "CsmaNode.h"
#include "CsmaChannelNode.h"
#include "CsmaInternetNode.h"

class EunetTerminal: public CsmaInternetNode {
	ns3::ApplicationContainer onOffApplication;
	ns3::ApplicationContainer packetSink;
public:
	static ns3::TypeId GetTypeId(void);
	EunetTerminal();
	virtual ~EunetTerminal();
	void installInternetStack();
	ns3::Ipv4Address getCsmaNetDeviceAddress();
	void startOnOffApplication(ns3::Time start_seconds = ns3::Seconds(0.0));
	void stopOnOffApplication(ns3::Time stop_seconds = ns3::Seconds(10.0));
	void setRemote(ns3::Ptr<EunetTerminal> ptr_remote);
	uint32_t getTotalRx();
	void logTotalRx(const ns3::LogLevel log_level = ns3::LOG_LEVEL_INFO);
	void assignAddress(ns3::Ipv4AddressHelper&);
protected:
	virtual void DoInitialize();
	virtual void NotifyConstructionCompleted();
private:
	static const int PACKET_SINK_UDP_PORT = 9; // Discard port (RFC 863)
	static const int ON_OFF_APPLICATION_UDP_PORT = 10009;
	void installPacketSink();
	void installOnOffApplication();
};//EunetTerminal

#endif /* EUNETTERMINAL_H_ */
