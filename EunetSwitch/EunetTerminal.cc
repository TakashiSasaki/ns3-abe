#define NS3_LOG_ENABLE 1
#include "ns3/log.h"
NS_LOG_COMPONENT_DEFINE("EunetTerminal");
#define NS3_ASSERT_ENABLE 1
#include "ns3/assert.h"
#include "ns3/applications-module.h"
#include "ns3/ipv4.h"
#include "ns3/internet-module.h"
#include "EunetTerminal.h"
NS_OBJECT_ENSURE_REGISTERED(EunetTerminal);

ns3::TypeId EunetTerminal::GetTypeId(void) {
	static ns3::TypeId type_id = ns3::TypeId("EunetTerminal").SetParent<
			PacketSinkNode> ().AddConstructor<EunetTerminal> ();
	return type_id;
}//GetTypeId

EunetTerminal::EunetTerminal() {
	NS_ASSERT(this->GetNDevices() == 1);
	//this->installInternetStack();
	//this->installPacketSink();
}

void EunetTerminal::DoInitialize() {
	CsmaNode::DoInitialize();
}

void EunetTerminal::NotifyConstructionCompleted() {
	NS_LOG_INFO("notified the completion of EunetTerminal");
	NS_ASSERT(this->GetNDevices() == 1);
	PacketSinkNode::NotifyConstructionCompleted();
	NS_ASSERT(this->GetNDevices() == 2);
	this->installOnOffApplication();
	NS_ASSERT(this->GetNDevices() == 2);
}

EunetTerminal::~EunetTerminal() {
	// TODO !CodeTemplates.destructorstub.tododesc!
}

void EunetTerminal::installOnOffApplication() {
	NS_LOG_INFO("installing on-off application on node " << this->GetId());
	ns3::OnOffHelper on_off_helper("ns3::UdpSocketFactory", ns3::Address(
			ns3::InetSocketAddress(ns3::Ipv4Address("1.2.3.4"),
					PACKET_SINK_UDP_PORT)));
	on_off_helper.SetConstantRate(ns3::DataRate("500kb/s"));
	//on_off_helper.SetAttribute("Remote", ns3::AddressValue(
	//		ns3::InetSocketAddress(ns3::Ipv4Address("127.0.0.1"),
	//				PACKET_SINK_UDP_PORT)));
	this->onOffApplication = on_off_helper.Install(this);
}//installOnOffApplication

void EunetTerminal::startOnOffApplication(ns3::Time start_seconds) {
	this->onOffApplication.Start(start_seconds);
}//startOnOffApplication

void EunetTerminal::stopOnOffApplication(ns3::Time stop_seconds) {
	this->onOffApplication.Stop(stop_seconds);
}//stopOnOffApplication

void EunetTerminal::assignAddress(ns3::Ipv4AddressHelper& ipv4_address_helper) {
	NS_ASSERT(this->GetNDevices()==2);
	ipv4_address_helper.Assign(
			ns3::NetDeviceContainer(this->getCsmaNetDevice()));
	//this->setRemote(this);
	NS_LOG_INFO(this->getCsmaNetDeviceAddress() << " node " << this->GetId());
}

void EunetTerminal::setRemote(ns3::Ptr<EunetTerminal> ptr_remote) {
	this->onOffApplication.Get(0)->SetAttribute("Remote", ns3::AddressValue(
			ns3::InetSocketAddress(ptr_remote->getCsmaNetDeviceAddress(),
					PACKET_SINK_UDP_PORT)));
}
