#define NS3_LOG_ENABLE 1
#include "ns3/log.h"
NS_LOG_COMPONENT_DEFINE("OnOffNode");
#define NS3_ASSERT_ENABLE 1
#include "ns3/assert.h"
#include "ns3/applications-module.h"
#include "ns3/ipv4-address-helper.h"
#include "ns3/nstime.h"
#include "ns3/string.h"
#include "init.h"
#include "OnOffNode.h"
NS_OBJECT_ENSURE_REGISTERED(OnOffNode);

ns3::TypeId OnOffNode::GetTypeId(void) {
	static ns3::TypeId
			type_id =
					ns3::TypeId("OnOffNode").SetParent<PacketSinkNode> ().AddConstructor<
							OnOffNode> () .AddAttribute("onOffStartTime",
							"onOffStartTime", ns3::TimeValue(ns3::Seconds(0)),
							ns3::MakeTimeAccessor(&OnOffNode::onOffStartTime),
							ns3::MakeTimeChecker()).AddAttribute(
							"onOffStopTime", "onOffStopTime",
							ns3::TimeValue(ns3::Time(std::numeric_limits<
									int64_t>::max())), ns3::MakeTimeAccessor(
									&OnOffNode::onOffStopTime),
							ns3::MakeTimeChecker()) .AddAttribute(
							"onOffDataRate",
							"onOffDataRate",
							ns3::DataRateValue(ns3::DataRate("1kb/s")),
							ns3::MakeDataRateAccessor(&OnOffNode::onOffDataRate),
							ns3::MakeDataRateChecker()) .AddAttribute(
							"onOffRemoteAddress", "onOffRemoteAddress",
							ns3::StringValue("0.0.0.0"),
							ns3::MakeStringAccessor(&OnOffNode::onOffRemote),
							ns3::MakeStringChecker());
	return type_id;
}//GetTypeId

OnOffNode::OnOffNode(const bool start_at_the_beginning) :
	totalTxBytes(0), totalTxPackets(0), INIT_DIDDNCC_FLAGS {
}// the constructor

OnOffNode::~OnOffNode() {
}

void OnOffNode::DoInitialize() {
	ASSERT_DI;
	NS_ASSERT(this->GetNDevices()==nPorts+1);
	PacketSinkNode::DoInitialize();
	NS_ASSERT_MSG(this->GetNDevices()==2,this->GetNDevices());
	ns3::OnOffHelper on_off_helper("ns3::UdpSocketFactory", ns3::Address(
			ns3::InetSocketAddress(ns3::Ipv4Address(this->onOffRemote.c_str()),
					PACKET_SINK_UDP_PORT)));
	on_off_helper.SetConstantRate(this->onOffDataRate);
	on_off_helper.SetAttribute("StartTime",
			ns3::TimeValue(this->onOffStartTime));
	on_off_helper.SetAttribute("StopTime", ns3::TimeValue(this->onOffStopTime));

	auto ac = on_off_helper.Install(this);
	NS_ASSERT(ac.GetN()==1);
	NS_ASSERT(this->getApplication<ns3::OnOffApplication> () != NULL);
	ac.Get(0)->TraceConnectWithoutContext("Tx", ns3::MakeCallback(
			&OnOffNode::traceTxCallback, this));
}//DoInitialize

void OnOffNode::DoDispose() {
	ASSERT_DD;
	PacketSinkNode::DoDispose();
}//DoDispose

void OnOffNode::NotifyConstructionCompleted() {
	ASSERT_NCC;
	PacketSinkNode::NotifyConstructionCompleted();
}

void OnOffNode::setRemote(const ns3::Ipv4Address& ipv4_address) {
	NS_LOG_DEBUG(ipv4_address);
	auto on_off_application = this->getApplication<ns3::OnOffApplication> ();
	NS_ASSERT(on_off_application != NULL);
	on_off_application->SetAttribute("Remote", ns3::AddressValue(
			ns3::InetSocketAddress(ipv4_address, PACKET_SINK_UDP_PORT)));
}//setRemote

ns3::Address OnOffNode::getRemote() {
	auto on_off_application = this->getApplication<ns3::OnOffApplication> ();
	NS_ASSERT(on_off_application != NULL);
	ns3::AddressValue address_value;
	on_off_application->GetAttribute("Remote", address_value);
	return address_value.Get();
}

void OnOffNode::traceTxCallback(ns3::Ptr<const ns3::Packet> p) {
	totalTxBytes += p->GetSize();
	++totalTxPackets;
}

unsigned long OnOffNode::getTotalTxBytes() {
	return this->totalTxBytes;
}

unsigned long OnOffNode::getTotalTxPackets() {
	return this->totalTxPackets;
}
