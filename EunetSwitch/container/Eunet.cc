#include <string>
#define NS3_LOG_ENABLE 1
#include "ns3/log.h"
NS_LOG_COMPONENT_DEFINE("Eunet");
#define NS3_ASSERT_ENABLE 1
#include "ns3/assert.h"
#include "ns3/ipv4-address-helper.h"
#include "ns3/mobility-helper.h"
#include "Eunet.h"
#include "UplinkDevice.h"
#include "DownlinkDevice.h"

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
	this->eunetSwitchFactory.Set("dontAttachTerminals", ns3::BooleanValue(true));
	ns3::Ptr<EunetSwitch> ptr_eunet_switch = this->eunetSwitchFactory.Create<
			EunetSwitch> ();
	ptr_eunet_switch->Initialize();
	NS_ASSERT_MSG(ptr_eunet_switch->getNDevices<DownlinkDevice>() == n_downlink_ports, ptr_eunet_switch->getNDevices<DownlinkDevice>());
	this->Add(ptr_eunet_switch);
	ns3::Names::Add(name, ptr_eunet_switch);
	return ptr_eunet_switch;
}

ns3::Ptr<EunetRouter> Eunet::addEunetRouter(std::string name) {
	this->eunetRouterFactory.Set("nPorts", ns3::UintegerValue(3));
	ns3::Ptr<EunetRouter> ptr_eunet_router = this->eunetRouterFactory.Create<
			EunetRouter> ();
	ptr_eunet_router->Initialize();
	this->Add(ptr_eunet_router);
	ns3::Names::Add(name, ptr_eunet_router);
	return ptr_eunet_router;
}

ns3::NetDeviceContainer Eunet::connectUpTo(const std::string& src_name,
		const std::string& dst_name, Eunet::ActiveChannel active_channel) {
	return this->connect<EunetSwitch, UplinkDevice, EunetSwitch, DownlinkDevice> (
			src_name, dst_name, active_channel);
}

ns3::NetDeviceContainer Eunet::connectDownTo(const std::string& src_name,
		const std::string& dst_name, Eunet::ActiveChannel active_channel) {
	return this->connect<EunetSwitch, DownlinkDevice, EunetSwitch, UplinkDevice> (
			src_name, dst_name, active_channel);
}

ns3::NetDeviceContainer Eunet::connectToRouter(std::string src_name,
		std::string dst_name, ns3::Ipv4Address dst_address,
		ns3::Ipv4Mask dst_mask, Eunet::ActiveChannel active_channel) {
	auto ndc = connect<EunetSwitch, CsmaDevice, EunetRouter, CsmaDevice> (
			src_name, dst_name, DST);
	ns3::Ptr<CsmaDevice> ptr_dst_net_device =
			ndc.Get(1)->GetObject<CsmaDevice> ();
	ns3::Ptr<EunetRouter> ptr_dst_node =
			ptr_dst_net_device->GetNode()->GetObject<EunetRouter> ();
	ptr_dst_node->assignAddress(ptr_dst_net_device, dst_address, dst_mask);
	ptr_dst_node->enableOspf(ptr_dst_net_device);
	return ndc;
}

ns3::NetDeviceContainer Eunet::connectRouters(std::string src_name,
		std::string dst_name, ns3::Ipv4Address src_address,
		ns3::Ipv4Address dst_address, ns3::Ipv4Mask ipv4_mask,
		Eunet::ActiveChannel active_channel) {
	auto ndc = connect<EunetRouter, CsmaDevice, EunetRouter, CsmaDevice> (
			src_name, dst_name, active_channel);
	auto src_dev = ndc.Get(0)->GetObject<CsmaDevice> ();
	auto dst_dev = ndc.Get(1)->GetObject<CsmaDevice> ();
	auto src_node = src_dev->GetNode()->GetObject<EunetRouter> ();
	auto dst_node = dst_dev->GetNode()->GetObject<EunetRouter> ();
	src_node->assignAddress(src_dev, src_address, ipv4_mask);
	dst_node->assignAddress(dst_dev, dst_address, ipv4_mask);
	src_node->enableOspf(src_dev);
	dst_node->enableOspf(dst_dev);
	return ndc;
}

void Eunet::attachEunetTerminals() {
	for (unsigned i = 0; i < this->GetN(); ++i) {
		auto ptr_node = this->Get(i);
		auto type_id = ptr_node->GetInstanceTypeId();
		if (type_id == EunetSwitch::GetTypeId()) {
			ptr_node->GetObject<EunetSwitch> ()->attachTerminals();
		}//if
	}//for
}
