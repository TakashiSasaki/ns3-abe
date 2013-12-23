#define NS3_LOG_ENABLE 1
#include "ns3/log.h"
NS_LOG_COMPONENT_DEFINE("NamedRouters");
#define NS3_ASSERT_ENABLE 1
#include "ns3/assert.h"
#include "ns3/ipv4-address-helper.h"
#include "ns3/names.h"
#include "EunetRouter.h"
#include "NamedRouters.h"

NamedRouters::NamedRouters(const std::string base_ip_address,
		const std::string subnet_mask) :
	baseIpAddress(base_ip_address), subnetMask(subnet_mask) {
}// a constructor

void NamedRouters::addEunetRouter(std::string name,
		const unsigned n_link_ports) {
	auto ptr_eunet_router(ns3::CreateObject<EunetRouter>(n_link_ports));
	ns3::Names::Add(name, ptr_eunet_router);
}

ns3::Ptr<EunetRouter> NamedRouters::findEunetRouter(std::string name) {
	auto p(ns3::Names::Find<EunetRouter>(name));
	return p;
}

void NamedRouters::assignIpAddresses() {
	NS_LOG_INFO ("assigning IP addresses to all terminal devices.");
	ns3::Ipv4AddressHelper ipv4_address_helper;
	ipv4_address_helper.SetBase(this->baseIpAddress.c_str(),
			this->subnetMask.c_str());
	for (unsigned i = 0; i < this->GetN(); ++i) {
		ipv4_address_helper.Assign(
				this->getEunetRouter(i)->getTerminalDevices());
	}// for
}//assignIpAddresses
