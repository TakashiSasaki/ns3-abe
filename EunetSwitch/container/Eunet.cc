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
		const unsigned n_uplink_ports, const unsigned n_downlik_ports,
		const ns3::DataRate& uplink_data_rate,
		const ns3::DataRate& downlink_data_rate, const ns3::Time& uplink_delay,
		const ns3::Time& downlink_delay) {
	this->eunetSwitchFactory.Set("nUplinkPorts", ns3::UintegerValue(
			n_uplink_ports));
	this->eunetSwitchFactory.Set("nDownlinkPorts", ns3::UintegerValue(
			n_downlik_ports));
	this->eunetSwitchFactory.Set("uplinkDataRate", ns3::DataRateValue(
			uplink_data_rate));
	this->eunetSwitchFactory.Set("downlinkDataRate", ns3::DataRateValue(
			downlink_data_rate));
	this->eunetSwitchFactory.Set("uplinkDelay", ns3::TimeValue(uplink_delay));
	this->eunetSwitchFactory.Set("downlinkDelay",
			ns3::TimeValue(downlink_delay));
	ns3::Ptr<EunetSwitch> ptr_eunet_switch = this->eunetSwitchFactory.Create<
			EunetSwitch> ();
	return ptr_eunet_switch;
}

template void Eunet::connect<EunetSwitch, UplinkNetDevice, EunetSwitch,
		DownlinkNetDevice>(std::string src_name, std::string dst_name,
		bool use_source_channel);
