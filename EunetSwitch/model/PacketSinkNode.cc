#define NS3_LOG_ENABLE 1
#include "ns3/log.h"
NS_LOG_COMPONENT_DEFINE("PacketSinkNode");
#define NS3_ASSERT_ENABLE 1
#include "ns3/assert.h"
#include "ns3/applications-module.h"
#include "ns3/ipv4.h"
#include "ns3/internet-module.h"
#include "init.h"
#include "CsmaNode.h"
#include "CsmaChannelNode.h"
#include "CsmaInternetNode.h"
#include "PacketSinkNode.h"
NS_OBJECT_ENSURE_REGISTERED(PacketSinkNode);

ns3::TypeId PacketSinkNode::GetTypeId(void) {
	static ns3::TypeId type_id = ns3::TypeId("PacketSinkNode").SetParent<
			CsmaInternetNode> ().AddConstructor<PacketSinkNode> ();
	return type_id;
}//GetTypeId

PacketSinkNode::PacketSinkNode() :
	INIT_DIDDNCC_FLAGS {
}

void PacketSinkNode::DoInitialize() {
	ASSERT_DI;
	NS_ASSERT(this->GetNDevices()==nPorts+1);
	CsmaInternetNode::DoInitialize();
	NS_ASSERT_MSG(this->GetNDevices()==2, this->GetNDevices());
	const unsigned n_devices_before = this->GetNDevices();
	//NS_ASSERT(this->GetNDevices() == 2);

	NS_LOG_INFO("installing packet sink on node " << this->GetId());
	ns3::PacketSinkHelper packet_sink_helper("ns3::UdpSocketFactory",
			ns3::Address(ns3::InetSocketAddress(ns3::Ipv4Address::GetAny(),
					PACKET_SINK_UDP_PORT)));
	this->packetSink = packet_sink_helper.Install(this);
	this->packetSink.Start(ns3::Seconds(0.0));
	NS_ASSERT(this->GetNDevices() == n_devices_before);
}//DoInitialize

void PacketSinkNode::DoDispose() {
	ASSERT_DD;
	CsmaInternetNode::DoDispose();
}//DoDispose

void PacketSinkNode::NotifyConstructionCompleted() {
	ASSERT_NCC;
	NS_ASSERT_MSG(this->GetNDevices()==0, this->GetNDevices());
	CsmaInternetNode::NotifyConstructionCompleted();
	NS_ASSERT_MSG(this->GetNDevices()==nPorts+1, this->GetNDevices());
}//NotifyConstructionCompleted

uint32_t PacketSinkNode::getTotalRx() {
	return this->packetSink.Get(0)->GetObject<ns3::PacketSink> ()->GetTotalRx();
}//getTotalRx

void PacketSinkNode::logTotalRx(ns3::LogLevel log_level) {
	NS_LOG(ns3::LOG_LEVEL_INFO, "node " << this->GetId() << " have received " << this->getTotalRx() << " bytes");
}//logTotalRx

