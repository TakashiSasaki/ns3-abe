#define NS3_LOG_ENABLE 1
#include "ns3/log.h"
NS_LOG_COMPONENT_DEFINE("NamedSwitches");
#define NS3_ASSERT_ENABLE 1
#include "ns3/object-factory.h"
#include "ns3/assert.h"
#include "ns3/ipv4-address-helper.h"
#include "ns3/names.h"
#include "EunetSwitch.h"
#include "NamedSwitches.h"

NamedSwitches::NamedSwitches(const std::string base_ip_address,
		const std::string subnet_mask) :
	baseIpAddress(base_ip_address), subnetMask(subnet_mask) {
}// a constructor

void NamedSwitches::addEunetSwitch(std::string name,
		const unsigned n_downlink_ports) {
	ns3::ObjectFactory object_factory;
	object_factory.SetTypeId(EunetSwitch::GetTypeId());
	object_factory.Set("nDownlinkPorts", ns3::UintegerValue(n_downlink_ports));
	auto ptr_eunet_switch(object_factory.Create());
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
