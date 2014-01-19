#define NS3_LOG_ENABLE 1
#include "ns3/log.h"
NS_LOG_COMPONENT_DEFINE("SimpleSwitch");
#define NS3_ASSERT_ENABLE 1
#include "ns3/assert.h"
#include "ns3/type-id.h"
#include "ns3/bridge-helper.h"
#include "ns3/names.h"
#include "UplinkNetDevice.h"
#include "DownlinkNetDevice.h"
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
			ns3::MakeDataRateChecker());
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
	NS_ASSERT(this->GetNDevices()==0);
	//this->setNPorts(this->nDownlinkPorts + this->nUplinkPorts);
	CsmaChannelNode::DoInitialize();
	//NS_ASSERT (this->getNPorts() == this->getNDevices<ns3::CsmaNetDevice>() );
	//NS_ASSERT_MSG(this->getNPorts() == this->getNUplinkPorts() + this->getNDownlinkPorts(), "node " << this->GetId() << " has " << this->getNDevices<ns3::CsmaNetDevice>() << " CsmaNetDevice(s)");
	NS_LOG_INFO("bridging all devices");

	NS_LOG_DEBUG(this->getNDevices<ns3::CsmaNetDevice>() << " " << this->getNDevices<UplinkNetDevice> () << " " << this->getNDevices<DownlinkNetDevice> ());
	for (unsigned i = 0; i < this->nUplinkPorts; ++i) {
		this->addCsmaNetDevice<UplinkNetDevice> ();
	}//for

	NS_LOG_DEBUG(this->getNDevices<ns3::CsmaNetDevice>() << " " << this->getNDevices<UplinkNetDevice> () << " " << this->getNDevices<DownlinkNetDevice> ());

	for (unsigned i = 0; i < this->nDownlinkPorts; ++i) {
		this->addCsmaNetDevice<DownlinkNetDevice> ();
	}//for

	NS_LOG_DEBUG(this->getNDevices<ns3::CsmaNetDevice>() << " " << this->getNDevices<UplinkNetDevice> () << " " << this->getNDevices<DownlinkNetDevice> ());

	for (unsigned i = 0; i < this->nUplinkPorts; ++i) {
		this->addCsmaChannel<UplinkNetDevice> (i, this->uplinkDataRate,
				this->uplinkDelay);
	}//for

	for (unsigned i = 0; i < this->nDownlinkPorts; ++i) {
		this->addCsmaChannel<DownlinkNetDevice> (i, this->downlinkDataRate,
				this->downlinkDelay);
	}//for

	ns3::NetDeviceContainer ndc;
	ndc.Add(this->getNetDevices<ns3::CsmaNetDevice> ());
	ndc.Add(this->getNetDevices<UplinkNetDevice> ());
	ndc.Add(this->getNetDevices<DownlinkNetDevice> ());
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

ns3::Ptr<ns3::CsmaNetDevice> SimpleSwitch::getUplinkPort(
		const unsigned i_uplink_port) {
	NS_ASSERT(i_uplink_port < nUplinkPorts);
	auto p = this->getNetDevice<UplinkNetDevice> (i_uplink_port);
	return p;
}//getUplinkPort

ns3::Ptr<ns3::CsmaNetDevice> SimpleSwitch::getDownlinkPort(
		const unsigned i_downlink_port) {
	NS_ASSERT(i_downlink_port < nDownlinkPorts);
	auto p = this->getNetDevice<DownlinkNetDevice> (i_downlink_port);
	return p;
}//getDownlinkPort

void SimpleSwitch::connectUpTo(const unsigned i_uplink_port, ns3::Ptr<
		SimpleSwitch> upstream_switch, const unsigned i_downlink_port) {
	this->bring<UplinkNetDevice, DownlinkNetDevice> (i_uplink_port,
			upstream_switch, i_downlink_port);
	NS_ASSERT((this->isConnectedTo<UplinkNetDevice, SimpleSwitch>(i_uplink_port)));
	NS_ASSERT((upstream_switch->isConnectedTo<DownlinkNetDevice, SimpleSwitch>(i_downlink_port)));
}//connectUpTo

void SimpleSwitch::connectUpTo(std::string upstream_switch_name) {
	auto ptr_node = ns3::Names::Find<ns3::Node>(upstream_switch_name);
	auto ptr_upstream_switch = ptr_node->GetObject<SimpleSwitch> ();
	auto unused_uplink_port = this->getUnusedPort<UplinkNetDevice> ();
	auto unused_downlink_port = ptr_upstream_switch->getUnusedPort<
			DownlinkNetDevice> ();
	unused_downlink_port->Attach(unused_uplink_port->GetChannel()->GetObject<
			ns3::CsmaChannel> ());
}//connectUpTo

void SimpleSwitch::connectDownTo(std::string downstream_switch_name) {
	auto ptr_node = ns3::Names::Find<ns3::Node>(downstream_switch_name);
	auto ptr_downstream_switch = ptr_node->GetObject<SimpleSwitch> ();
	auto unused_downlink_port = this->getUnusedPort<DownlinkNetDevice> ();
	auto unused_uplink_port = ptr_downstream_switch->getUnusedPort<
			UplinkNetDevice> ();
	unused_uplink_port->Attach(unused_downlink_port->GetChannel()->GetObject<
			ns3::CsmaChannel> ());
}//connectDownTo

void SimpleSwitch::connectSibling(const unsigned i_our_port, ns3::Ptr<
		SimpleSwitch> sibling_switch, const unsigned i_their_port) {
	this->bring<ns3::CsmaNetDevice, ns3::CsmaNetDevice> (i_our_port,
			sibling_switch, +i_their_port);
	NS_ASSERT((this->isConnectedTo<ns3::CsmaNetDevice, SimpleSwitch>(i_our_port)));
	NS_ASSERT((sibling_switch->isConnectedTo<ns3::CsmaNetDevice, SimpleSwitch>(+i_their_port)));
}//connectSibling

void SimpleSwitch::SimpleSwitch::enableAsciiTraceDownlink(
		const int i_downlink_port) {
	ns3::CsmaHelper csma_helper;
	csma_helper.EnableAscii(this->GetInstanceTypeId().GetName(),
			this->getDownlinkPort(i_downlink_port));
}

void SimpleSwitch::enableAsciiTraceUplink(const int i_uplink_port) {
	ns3::CsmaHelper csma_helper;
	csma_helper.EnableAscii(this->GetInstanceTypeId().GetName(),
			this->getUplinkPort(i_uplink_port));
}

void SimpleSwitch::enablePcapDownlink(const int i_downlink_port,
		const bool promiscuous) {
	ns3::CsmaHelper csma_helper;
	csma_helper.EnablePcap(this->GetInstanceTypeId().GetName(),
			this->getDownlinkPort(i_downlink_port), promiscuous);
}

void SimpleSwitch::enablePcapUplink(const int i_uplink_port,
		const bool promiscuous) {
	ns3::CsmaHelper csma_helper;
	csma_helper.EnablePcap(this->GetInstanceTypeId().GetName(),
			this->getUplinkPort(i_uplink_port), promiscuous);
}

template bool SimpleSwitch::isConnectedTo<ns3::CsmaNetDevice, SimpleSwitch>(
		const unsigned);
template bool SimpleSwitch::isConnectedTo<DownlinkNetDevice, SimpleSwitch>(
		const unsigned);
template bool SimpleSwitch::isConnectedTo<UplinkNetDevice, SimpleSwitch>(
		const unsigned);
