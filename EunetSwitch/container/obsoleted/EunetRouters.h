#ifndef EUNETROUTERS_H_
#define EUNETROUTERS_H_
#include <cmath>
#include "ns3/node-container.h"
#include "EunetRouter.h"

class EunetRouters: public ns3::NodeContainer {
	const unsigned nDepth;
	const unsigned nWidth;

public:
	EunetRouters(const unsigned depth = 1, const unsigned width = 1);
	virtual ~EunetRouters() {
	}

	ns3::Ptr<EunetRouter> getEunetRouter(unsigned i_depth, unsigned i_width);

	ns3::Ptr<EunetRouter> getEunetRouter(unsigned i_router) {
		return this->Get(i_router)->GetObject<EunetRouter> ();
	}
private:
	unsigned countTriangle(const unsigned depth) const {
		return (pow(nWidth, depth) - 1) / (nWidth - 1);
	}
};

#endif /* EUNETROUTERS_H_ */
