#ifndef EUNETTERMINALS_H_
#define EUNETTERMINALS_H_
#include "ns3/node-container.h"
#include "ns3/ipv4-address-helper.h"
#include "EunetTerminal.h"

class EunetTerminals: public ns3::NodeContainer {
	typedef ns3::NodeContainer Base;

public:
	EunetTerminals(const unsigned n_terminals = 3);
	void assignAddresses(const char* network_address = "10.0.0.0",
			const char* netmask = "255.0.0.0");
	void assignAddresses(ns3::Ipv4AddressHelper&);
	virtual ~EunetTerminals();
	ns3::Ptr<EunetTerminal> Get(const int i_eunet_terminal);
	void logTotalRx(ns3::LogLevel log_level = ns3::LOG_LEVEL_INFO);
	void bringAtoB(const unsigned i_eunet_terminal_a,
			const unsigned i_eunet_terminal_b);
	void setRemoteOfAtoB(const unsigned i_eunet_terminal_a,
			const unsigned i_eunet_terminal_b);

private:
	ns3::NetDeviceContainer getDevicesAll();
};

#endif /* EUNETTERMINALS_H_ */
