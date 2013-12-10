#ifndef EUNETSIMULATION_H_
#define EUNETSIMULATION_H_
#include "EunetTerminal.h"
class EunetSimulation {
	ns3::Ptr<EunetTerminal> sourceTerminal;
	ns3::Ptr<EunetTerminal> destTerminal;
public:
	EunetSimulation();
	int run();
	virtual ~EunetSimulation();
};

#endif /* EUNETSIMULATION_H_ */
