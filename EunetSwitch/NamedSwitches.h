#ifndef NAMEDSWITCHES_H_
#define NAMEDSWITCHES_H_
#include "ns3/node-container.h"
#include "EunetSwitches.h"

class NamedSwitches: protected ns3::NodeContainer {
	const std::string baseIpAddress;
	const std::string subnetMask;
public:
	NamedSwitches(const std::string base_ip_address,
			const std::string subnet_mask);
	void addEunetSwitch(std::string name);
	ns3::Ptr<EunetSwitch> findEunetSwitch(std::string name);
	ns3::Ptr<EunetSwitch> getEunetSwitch(unsigned i_switch) {
		//TODO: should be moved to common base class.
		return this->Get(i_switch)->GetObject<EunetSwitch> ();
	}
	virtual ~NamedSwitches() {
	}
	void assignIpAddresses();
};

#endif
