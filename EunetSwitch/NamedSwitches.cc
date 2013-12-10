#define NS3_LOG_ENABLE 1
#include "ns3/log.h"
NS_LOG_COMPONENT_DEFINE("NamedSwitches");
#define NS3_ASSERT_ENABLE 1
#include "ns3/assert.h"
#include "ns3/ipv4-address-helper.h"
#include "ns3/names.h"
#include "EunetSwitch.h"
#include "NamedSwitches.h"

NamedSwitches::NamedSwitches(const std::string base_ip_address,
		const std::string subnet_mask) :
	baseIpAddress(base_ip_address), subnetMask(subnet_mask) {
}// a constructor

void NamedSwitches::addEunetSwitch(std::string name) {
	auto ptr_eunet_switch(ns3::CreateObject<EunetSwitch>());
	ns3::Names::Add(name, ptr_eunet_switch);
}

ns3::Ptr<EunetSwitch> NamedSwitches::findEunetSwitch(std::string name) {
	auto p(ns3::Names::Find<EunetSwitch>(name));
	return p;
}

void NamedSwitches::assignIpAddresses() {
	NS_LOG_INFO ("assigning IP addresses to all terminal devices.");
	ns3::Ipv4AddressHelper ipv4_address_helper;
	ipv4_address_helper.SetBase(this->baseIpAddress.c_str(),
			this->subnetMask.c_str());
	for (unsigned i = 0; i < this->GetN(); ++i) {
		ipv4_address_helper.Assign(
				this->getEunetSwitch(i)->getTerminalDevices());
	}// for
}//assignIpAddresses
