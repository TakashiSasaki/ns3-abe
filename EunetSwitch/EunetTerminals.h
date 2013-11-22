#ifndef EUNETTERMINALS_H_
#define EUNETTERMINALS_H_
#include "ns3/node-container.h"

class EunetTerminals {
	ns3::NodeContainer terminals;
public:
	EunetTerminals(const int n_terminals = 3);
	virtual ~EunetTerminals();
	ns3::Ptr<EunetTerminal> getEunetTerminal(const int i_eunet_terminal);
private:
	ns3::NetDeviceContainer getDevicesAll();
};

#endif /* EUNETTERMINALS_H_ */
