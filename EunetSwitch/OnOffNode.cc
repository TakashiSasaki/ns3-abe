#define NS3_LOG_ENABLE 1
#include "ns3/log.h"
NS_LOG_COMPONENT_DEFINE("OnOffNode");
#define NS3_ASSERT_ENABLE 1
#include "ns3/assert.h"
#include "ns3/applications-module.h"
#include "ns3/ipv4-address-helper.h"
#include "ns3/nstime.h"
#include "OnOffNode.h"
NS_OBJECT_ENSURE_REGISTERED(OnOffNode);

ns3::TypeId OnOffNode::GetTypeId(void) {
	static ns3::TypeId type_id =
			ns3::TypeId("OnOffNode").SetParent<Base> ().AddConstructor<
					OnOffNode> ();
	return type_id;
}//GetTypeId

OnOffNode::OnOffNode() {
	// TODO 自動生成されたコンストラクター・スタブ

}

OnOffNode::~OnOffNode() {
	// TODO !CodeTemplates.destructorstub.tododesc!
}

void OnOffNode::DoInitialize() {
	Base::DoInitialize();
}

void OnOffNode::NotifyConstructionCompleted() {
	NS_LOG_INFO("notified the completion of OnOffNode");
	NS_ASSERT(this->GetNDevices() == 1);
	Base::NotifyConstructionCompleted();
	NS_ASSERT(this->GetNDevices() == 2);NS_LOG_INFO("installing on-off application on node " << this->GetId());
	ns3::OnOffHelper on_off_helper("ns3::UdpSocketFactory", ns3::Address(
			ns3::InetSocketAddress(ns3::Ipv4Address("1.2.3.4"),
					PACKET_SINK_UDP_PORT)));
	on_off_helper.SetConstantRate(ns3::DataRate("500kb/s"));
	on_off_helper.SetAttribute("StartTime", ns3::TimeValue(ns3::Time(
			std::numeric_limits<int64_t>::max())));
	on_off_helper.SetAttribute("StopTime", ns3::TimeValue(ns3::Seconds(0.0)));
	//on_off_helper.SetAttribute("Remote", ns3::AddressValue(
	//		ns3::InetSocketAddress(ns3::Ipv4Address("127.0.0.1"),
	//				PACKET_SINK_UDP_PORT)));
	this->onOffApplication = on_off_helper.Install(this);
	NS_ASSERT(this->GetNDevices() == 2);
	NS_ASSERT(this->onOffApplication.GetN()==1);
}

void OnOffNode::startAt(ns3::Time start_seconds) {
	this->onOffApplication.Start(start_seconds);
}//startOnOffApplication

void OnOffNode::stopAt(ns3::Time stop_seconds) {
	this->onOffApplication.Stop(stop_seconds);
}//stopOnOffApplication

void OnOffNode::setRemote(ns3::Ptr<PacketSinkNode> ptr_remote) {
	this->onOffApplication.Get(0)->SetAttribute("Remote", ns3::AddressValue(
			ns3::InetSocketAddress(ptr_remote->getCsmaNetDeviceAddress(),
					PACKET_SINK_UDP_PORT)));
}
