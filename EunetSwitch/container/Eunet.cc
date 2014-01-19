#include <string>
#define NS3_LOG_ENABLE 1
#include "ns3/log.h"
NS_LOG_COMPONENT_DEFINE("Eunet");
#define NS3_ASSERT_ENABLE 1
#include "ns3/assert.h"
#include "ns3/ipv4-address-helper.h"
#include "ns3/mobility-helper.h"
#include "Eunet.h"
#include "UplinkNetDevice.h"
#include "DownlinkNetDevice.h"

Eunet::Eunet() {
	this->eunetRouterFactory.SetTypeId(EunetRouter::GetTypeId());
	this->eunetSwitchFactory.SetTypeId(EunetSwitch::GetTypeId());
	this->eunetTerminalFactory.SetTypeId(EunetTerminal::GetTypeId());
}// a constructor

Eunet::~Eunet() {
}

ns3::Ptr<EunetSwitch> Eunet::addEunetSwitch(std::string name,
		const unsigned n_uplink_ports, const unsigned n_downlink_ports,
		const ns3::DataRate& uplink_data_rate,
		const ns3::DataRate& downlink_data_rate, const ns3::Time& uplink_delay,
		const ns3::Time& downlink_delay) {
	this->eunetSwitchFactory.Set("nUplinkPorts", ns3::UintegerValue(
			n_uplink_ports));
	this->eunetSwitchFactory.Set("nDownlinkPorts", ns3::UintegerValue(
			n_downlink_ports));
	this->eunetSwitchFactory.Set("uplinkDataRate", ns3::DataRateValue(
			uplink_data_rate));
	this->eunetSwitchFactory.Set("downlinkDataRate", ns3::DataRateValue(
			downlink_data_rate));
	this->eunetSwitchFactory.Set("uplinkDelay", ns3::TimeValue(uplink_delay));
	this->eunetSwitchFactory.Set("downlinkDelay",
			ns3::TimeValue(downlink_delay));
	ns3::Ptr<EunetSwitch> ptr_eunet_switch = this->eunetSwitchFactory.Create<
			EunetSwitch> ();
	ptr_eunet_switch->Initialize();
	NS_ASSERT_MSG(ptr_eunet_switch->getNDevices<DownlinkNetDevice>() == n_downlink_ports, ptr_eunet_switch->getNDevices<DownlinkNetDevice>());
	this->Add(ptr_eunet_switch);
	ns3::Names::Add(name, ptr_eunet_switch);
	return ptr_eunet_switch;
}

ns3::Ptr<ns3::CsmaChannel> Eunet::connectUpTo(const std::string& src_name,
		const std::string& dst_name, Eunet::ActiveChannel active_channel) {
	return this->connect<EunetSwitch, UplinkNetDevice, EunetSwitch,
			DownlinkNetDevice> (src_name, dst_name, active_channel);
}

ns3::Ptr<ns3::CsmaChannel> Eunet::connectDownTo(const std::string& src_name,
		const std::string& dst_name, Eunet::ActiveChannel active_channel) {
	return this->connect<EunetSwitch, DownlinkNetDevice, EunetSwitch,
			DownlinkNetDevice> (src_name, dst_name, active_channel);
}

