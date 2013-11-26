#define NS3_LOG_ENABLE 1
#include "ns3/log.h"
NS_LOG_COMPONENT_DEFINE("SimpleSwitch");
#define NS3_ASSERT_ENABLE 1
#include "ns3/assert.h"
#include "ns3/type-id.h"
#include "ns3/bridge-helper.h"
#include "SimpleSwitch.h"

NS_OBJECT_ENSURE_REGISTERED( SimpleSwitch);

const ns3::DataRate SimpleSwitch::defaultUplinkDataRate("1000000000bps");
const ns3::TimeValue SimpleSwitch::defaultUplinkDelay(ns3::MilliSeconds(1));
const ns3::DataRate SimpleSwitch::defaultDownlinkDataRate("1000000000bps");
const ns3::TimeValue SimpleSwitch::defaultDownlinkDelay(ns3::MilliSeconds(1));

ns3::TypeId SimpleSwitch::GetTypeId(void) {
	static ns3::TypeId type_id =
			ns3::TypeId("SimpleSwitch").SetParent<Base> ().AddConstructor<
					SimpleSwitch> ();
	return type_id;
}//GetTypeId


SimpleSwitch::SimpleSwitch(const unsigned n_downlink_ports,
		const unsigned n_uplink_ports) :
	CsmaChannelNode(n_downlink_ports + n_uplink_ports), nUplinkPorts(
			n_uplink_ports), nDownlinkPorts(n_downlink_ports) {
	NS_LOG_INFO("constructing SimpleSwitch");
}

SimpleSwitch::~SimpleSwitch() {
	// TODO !CodeTemplates.destructorstub.tododesc!
}

ns3::Ptr<ns3::CsmaNetDevice> SimpleSwitch::getUplinkPort(
		const unsigned i_uplink_port) {
	NS_ASSERT(i_uplink_port < nUplinkPorts);
	auto p = this->getCsmaNetDevice(this->nDownlinkPorts + i_uplink_port);
	return p;
}//getUplinkPort

ns3::Ptr<ns3::CsmaNetDevice> SimpleSwitch::getDownlinkPort(
		const unsigned i_downlink_port) {
	NS_ASSERT(i_downlink_port < nDownlinkPorts);
	auto p = this->getCsmaNetDevice(i_downlink_port);
	return p;
}//getDownlinkPort

void SimpleSwitch::setDownlinkDataRate(ns3::DataRateValue data_rate) {
	for (unsigned i = 0; i < nDownlinkPorts; ++i) {
		this->setDataRate(data_rate, i);
	}
}

void SimpleSwitch::setDownlinkDelay(ns3::TimeValue delay) {
	for (unsigned i = 0; i < nDownlinkPorts; ++i) {
		this->setDelay(delay, i);
	}
}

void SimpleSwitch::setUplinkDataRate(ns3::DataRateValue data_rate) {
	for (unsigned i = 0; i < nUplinkPorts; ++i) {
		this->setDataRate(data_rate, nDownlinkPorts + i);
	}
}

void SimpleSwitch::setUplinkDelay(ns3::TimeValue delay) {
	for (unsigned i = 0; i < nUplinkPorts; ++i) {
		this->setDelay(delay, nDownlinkPorts + i);
	}
}

void SimpleSwitch::connectUpTo(const unsigned i_uplink_port, ns3::Ptr<
		SimpleSwitch> upstream_switch, const unsigned i_downlink_port) {
	this->bring(nDownlinkPorts + i_uplink_port, upstream_switch,
			i_downlink_port);
}//connectUpTo

void SimpleSwitch::connectDownTo(const unsigned i_downlink_port, ns3::Ptr<
		SimpleSwitch> downstream_switch, const unsigned i_uplink_port) {
	this->bring(i_downlink_port, downstream_switch,
			downstream_switch->nDownlinkPorts + i_uplink_port);
}//connectDownTo

void SimpleSwitch::connectSibling(const unsigned i_uplink_port, ns3::Ptr<
		SimpleSwitch> sibling_switch, const unsigned i_sibling_uplink_port) {
	this->bring(nDownlinkPorts + i_uplink_port, sibling_switch,
			sibling_switch->nDownlinkPorts + i_sibling_uplink_port);
}//connectSibling

void SimpleSwitch::NotifyConstructionCompleted() {
	NS_LOG_INFO("bridging all devices");
	Base::NotifyConstructionCompleted();
	ns3::NetDeviceContainer ndc;
	for (unsigned i = 0; i < nUplinkPorts + nDownlinkPorts; ++i) {
		auto ptr_csma_net_device = this->getCsmaNetDevice(i);
		ndc.Add(ptr_csma_net_device);
	}
	ns3::BridgeHelper bridge_helper;
	bridge_helper.Install(this, ndc);
	//this->logAllDevices();
	for (unsigned i = 0; i < this->GetNDevices(); ++i) {
		NS_LOG_INFO(this->GetDevice(i)->GetTypeId() << ", " << this->GetDevice(i)->GetInstanceTypeId());
	}
}

void SimpleSwitch::DoInitialize() {
	NS_LOG_INFO("just calling up");
	Base::DoInitialize();
}
