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
	ns3::Ptr<EunetSwitch> getSwitch(const int depth, const int width) {
		return this->switches[depth][width];
	}
	ns3::Ptr<ns3::Node> getTerminal(const int depth, const int width,
			const int i_downlink_port) {
		return this->getSwitch(depth, width)->getTerminal(i_downlink_port);
	}

private:
	void assignAddresses();
	ns3::NetDeviceContainer getTerminalDevices();
};

#endif /* EUNETSWITCHES_H_ */
