#ifndef EUNETSWITCHES_H_
#define EUNETSWITCHES_H_
#include <vector>
#include "EunetSwitch.h"

class EunetSwitches {
	const int nDepth;
	const int nWidth;
	EunetSwitch rootSwitch;
	std::vector<std::vector<ns3::Ptr<EunetSwitch> > > switches;
public:
	EunetSwitches(const int depth = 1, const int width = 1);
	virtual ~EunetSwitches();
};

#endif /* EUNETSWITCHES_H_ */
