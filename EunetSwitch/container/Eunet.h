#ifndef EUNET_H_
#define EUNET_H_
#include <cmath>
#include "ns3/node-container.h"
#include "Eunet.h"

class Eunet: public ns3::NodeContainer {
public:
	Eunet();
	virtual ~Eunet();
};

#endif /* EUNET_H_ */
