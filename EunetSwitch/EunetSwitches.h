#ifndef EUNETSWITCHES_H_
#define EUNETSWITCHES_H_
#include <vector>
#include "ns3/node-container.h"
#include "EunetSwitch.h"

class EunetSwitches: public ns3::NodeContainer {
	static const unsigned iRootSwitch = 0;
	const unsigned nDepth;
	const unsigned nWidth;
	//EunetSwitch rootSwitch;
	//std::vector<std::vector<ns3::Ptr<EunetSwitch> > > switches;
public:
	EunetSwitches(const unsigned depth = 1, const unsigned width = 1);
	virtual ~EunetSwitches() {
	}

	ns3::Ptr<EunetSwitch> getEunetSwitch(unsigned i_depth, unsigned i_width);

	ns3::Ptr<EunetSwitch> getEunetSwitch(unsigned i_switch) {
		return this->Get(i_switch)->GetObject<EunetSwitch> ();
	}
};

#endif /* EUNETSWITCHES_H_ */
