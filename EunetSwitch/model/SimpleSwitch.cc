#define NS3_LOG_ENABLE 1
#include "ns3/log.h"
NS_LOG_COMPONENT_DEFINE("SimpleSwitch");
#define NS3_ASSERT_ENABLE 1
#include "ns3/assert.h"
#include "ns3/type-id.h"
#include "ns3/bridge-helper.h"
#include "ns3/names.h"
#include "UplinkDevice.h"
#include "DownlinkDevice.h"
#include "SimpleSwitch.h"
NS_OBJECT_ENSURE_REGISTERED(SimpleSwitch);

ns3::TypeId SimpleSwitch::GetTypeId(void) {
	static ns3::TypeId type_id = ns3::TypeId("SimpleSwitch").SetParent<
			CsmaChannelNode> ().AddConstructor<SimpleSwitch> () .AddAttribute(
			"nDownlinkPorts", "nDownlinkPorts", ns3::UintegerValue(4),
			ns3::MakeUintegerAccessor(&SimpleSwitch::nDownlinkPorts),
			ns3::MakeUintegerChecker<uint32_t>()) .AddAttribute("nUplinkPorts",
			"nUplinkPorts", ns3::UintegerValue(1), ns3::MakeUintegerAccessor(
					&SimpleSwitch::nUplinkPorts), ns3::MakeUintegerChecker<
					uint32_t>()) .AddAttribute("uplinkDataRate",
			"uplinkDataRate", ns3::DataRateValue(1000000000),
			ns3::MakeDataRateAccessor(&SimpleSwitch::uplinkDataRate),
			ns3::MakeDataRateChecker()).AddAttribute("downlinkDataRate",
			"downlinkDataRate", ns3::DataRateValue(1000000000),
			ns3::MakeDataRateAccessor(&SimpleSwitch::downlinkDataRate),
			ns3::MakeDataRateChecker()) .AddAttribute("uplinkDelay",
			"uplinkDelay", ns3::TimeValue(ns3::MilliSeconds(1)),
			ns3::MakeTimeAccessor(&SimpleSwitch::uplinkDelay),
			ns3::MakeTimeChecker()).AddAttribute("downlinkDelay",
			"downlinkDelay", ns3::TimeValue(ns3::MilliSeconds(1)),
			ns3::MakeTimeAccessor(&SimpleSwitch::downlinkDelay),
			ns3::MakeTimeChecker());
	return type_id;
}//GetTypeId


SimpleSwitch::SimpleSwitch() :
	nUplinkPorts(0), nDownlinkPorts(0), INIT_DIDDNCC_FLAGS {
}// the constructor

SimpleSwitch::~SimpleSwitch() {
}

void SimpleSwitch::NotifyConstructionCompleted() {
	ASSERT_NCC;
	CsmaChannelNode::NotifyConstructionCompleted();
}

void SimpleSwitch::DoInitialize() {
	ASSERT_DI;
	NS_ASSERT(this->getNDevices<CsmaDevice>()==nPorts);
	CsmaChannelNode::DoInitialize();
	NS_LOG_INFO("bridging all devices");

	NS_LOG_INFO(getNDevices<CsmaDevice>() << " " << getNDevices<UplinkDevice> () << " " << getNDevices<DownlinkDevice> ());
	for (unsigned i = 0; i < this->nUplinkPorts; ++i) {
		this->addCsmaNetDevice<UplinkDevice> ();
	}//for

	NS_LOG_INFO(getNDevices<CsmaDevice>() << " " << getNDevices<UplinkDevice> () << " " << getNDevices<DownlinkDevice> ());

	for (unsigned i = 0; i < this->nDownlinkPorts; ++i) {
		this->addCsmaNetDevice<DownlinkDevice> ();
	}//for

	NS_LOG_INFO(getNDevices<CsmaDevice>() << " " << getNDevices<UplinkDevice> () << " " << getNDevices<DownlinkDevice> ());

	for (unsigned i = 0; i < this->nUplinkPorts; ++i) {
		this->addCsmaChannel<UplinkDevice> (i, this->uplinkDataRate,
				this->uplinkDelay);
	}//for

	for (unsigned i = 0; i < this->nDownlinkPorts; ++i) {
		this->addCsmaChannel<DownlinkDevice> (i, this->downlinkDataRate,
				this->downlinkDelay);
	}//for

	ns3::NetDeviceContainer ndc;
	ndc.Add(this->getNetDevices<CsmaDevice> ());
	ndc.Add(this->getNetDevices<UplinkDevice> ());
	ndc.Add(this->getNetDevices<DownlinkDevice> ());
	NS_ASSERT_MSG(ndc.GetN() == this->GetNDevices(), ndc.GetN() << " " << this->GetNDevices());

	ns3::BridgeHelper bridge_helper;
	bridge_helper.Install(this, ndc);

	for (unsigned i = 0; i < this->GetNDevices(); ++i) {
		NS_LOG_INFO(this->GetDevice(i)->GetTypeId() << ", " << this->GetDevice(i)->GetInstanceTypeId());
	}//for
}//DoInitialize

void SimpleSwitch::DoDispose() {
	ASSERT_DD;
	CsmaChannelNode::DoDispose();
}//DoDispose

void SimpleSwitch::connectUpTo(const unsigned i_uplink_port, ns3::Ptr<
		SimpleSwitch> upstream_switch, const unsigned i_downlink_port) {
	this->bring<UplinkDevice, DownlinkDevice> (i_uplink_port, upstream_switch,
			i_downlink_port);
	NS_ASSERT((this->isConnectedTo<UplinkDevice, SimpleSwitch>(i_uplink_port)));
	NS_ASSERT((upstream_switch->isConnectedTo<DownlinkDevice, SimpleSwitch>(i_downlink_port)));
}//connectUpTo

void SimpleSwitch::connectUpTo(std::string upstream_switch_name) {
	auto ptr_node = ns3::Names::Find<ns3::Node>(upstream_switch_name);
	auto ptr_upstream_switch = ptr_node->GetObject<SimpleSwitch> ();
	auto unused_uplink_port = this->getUnusedPort<UplinkDevice> ();
	auto unused_downlink_port = ptr_upstream_switch->getUnusedPort<
			DownlinkDevice> ();
	unused_downlink_port->Attach(unused_uplink_port->GetChannel()->GetObject<
			ns3::CsmaChannel> ());
}//connectUpTo

void SimpleSwitch::connectDownTo(std::string downstream_switch_name) {
	auto ptr_node = ns3::Names::Find<ns3::Node>(downstream_switch_name);
	auto ptr_downstream_switch = ptr_node->GetObject<SimpleSwitch> ();
	auto unused_downlink_port = this->getUnusedPort<DownlinkDevice> ();
	auto unused_uplink_port =
			ptr_downstream_switch->getUnusedPort<UplinkDevice> ();
	unused_uplink_port->Attach(unused_downlink_port->GetChannel()->GetObject<
			ns3::CsmaChannel> ());
}//connectDownTo

void SimpleSwitch::connectSibling(const unsigned i_our_port, ns3::Ptr<
		SimpleSwitch> sibling_switch, const unsigned i_their_port) {
	this->bring<CsmaDevice, CsmaDevice> (i_our_port, sibling_switch,
			+i_their_port);
	NS_ASSERT((this->isConnectedTo<CsmaDevice, SimpleSwitch>(i_our_port)));
	NS_ASSERT((sibling_switch->isConnectedTo<CsmaDevice, SimpleSwitch>(+i_their_port)));
}//connectSibling

void SimpleSwitch::SimpleSwitch::enableAsciiTraceDownlink(
		const int i_downlink_port) {
	ns3::CsmaHelper csma_helper;
	csma_helper.EnableAscii(this->GetInstanceTypeId().GetName(),
			this->getNetDevice<DownlinkDevice> (i_downlink_port));
}

void SimpleSwitch::enableAsciiTraceUplink(const int i_uplink_port) {
	ns3::CsmaHelper csma_helper;
	csma_helper.EnableAscii(this->GetInstanceTypeId().GetName(),
			this->getNetDevice<UplinkDevice> (i_uplink_port));
}

#if 0
template bool SimpleSwitch::isConnectedTo<ns3::CsmaNetDevice, SimpleSwitch>(
		const unsigned);
template bool SimpleSwitch::isConnectedTo<DownlinkNetDevice, SimpleSwitch>(
		const unsigned);
template bool SimpleSwitch::isConnectedTo<UplinkNetDevice, SimpleSwitch>(
		const unsigned);
#endif
template
bool CsmaChannelNode::isConnectedTo<CsmaDevice, SimpleSwitch>(
		const unsigned i_port);
template
bool CsmaChannelNode::isConnectedTo<UplinkDevice, SimpleSwitch>(
		const unsigned i_port);
template
bool CsmaChannelNode::isConnectedTo<DownlinkDevice, SimpleSwitch>(
		const unsigned i_port);
