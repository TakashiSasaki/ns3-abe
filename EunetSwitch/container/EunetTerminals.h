#ifndef EUNETTERMINALS_H_
#define EUNETTERMINALS_H_
#include "ns3/node-container.h"
#include "ns3/ipv4-address-helper.h"
#include "EunetTerminal.h"
#include "Nodes.h"

class EunetTerminals: public Nodes {
public:
	EunetTerminals();
	void initialize(const uint32_t n_terminals);
	void assignAddresses(const char* network_address = "10.0.0.0",
			const char* netmask = "255.0.0.0");
	void assignAddresses(ns3::Ipv4AddressHelper&);
	virtual ~EunetTerminals();
	ns3::Ptr<EunetTerminal> Get(const int i_eunet_terminal);
	unsigned getTotalRx();
	void bringAtoB(const unsigned i_eunet_terminal_a,
			const unsigned i_eunet_terminal_b);
	void setRemoteOfAtoB(const unsigned i_eunet_terminal_a,
			const unsigned i_eunet_terminal_b);
private:
	ns3::NetDeviceContainer getDevicesAll();
};

#endif /* EUNETTERMINALS_H_ */
