#ifndef NAMEDSWITCHES_H_
#define NAMEDSWITCHES_H_
#include "ns3/node-container.h"
#include "EunetRouters.h"

class NamedRouters: protected ns3::NodeContainer {
	const std::string baseIpAddress;
	const std::string subnetMask;
public:
	NamedRouters(const std::string base_ip_address,
			const std::string subnet_mask);
	void addEunetRouter(std::string name, const unsigned n_link_ports);
	ns3::Ptr<EunetRouter> findEunetRouter(std::string name);
	ns3::Ptr<EunetRouter> getEunetRouter(unsigned i_router) {
		//TODO: should be moved to common base class.
		return this->Get(i_router)->GetObject<EunetRouter> ();
	}
	virtual ~NamedRouters() {
	}
	void assignIpAddresses();
};

#endif
