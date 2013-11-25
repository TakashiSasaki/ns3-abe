#define NS3_LOG_ENABLE 1
#include "ns3/log.h"
NS_LOG_COMPONENT_DEFINE("EunetTerminal");
#define NS3_ASSERT_ENABLE 1
#include "ns3/assert.h"
#include "ns3/applications-module.h"
#include "ns3/ipv4.h"
#include "ns3/internet-module.h"
#include "CsmaNode.h"
#include "EunetTerminal.h"
NS_OBJECT_ENSURE_REGISTERED(EunetTerminal);

ns3::TypeId EunetTerminal::GetTypeId(void) {
	static ns3::TypeId type_id = ns3::TypeId("EunetTerminal").SetParent<
			CsmaNode> ().AddConstructor<EunetTerminal> ();
	return type_id;
}//GetTypeId

EunetTerminal::EunetTerminal() :
	CsmaNode(1) {
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
	this->installInternetStack();
	NS_ASSERT(this->GetNDevices() == 2);
	this->installPacketSink();
	NS_ASSERT(this->GetNDevices() == 2);
	this->installOnOffApplication();
	NS_ASSERT(this->GetNDevices() == 2);
}

EunetTerminal::~EunetTerminal() {
	// TODO !CodeTemplates.destructorstub.tododesc!
}

void EunetTerminal::installInternetStack() {
	NS_ASSERT(this->GetNDevices() == 1);
	ns3::InternetStackHelper internet_stack_helper;
	internet_stack_helper.SetIpv4StackInstall(true);
	internet_stack_helper.SetIpv6StackInstall(false);
	NS_ASSERT(this->GetNDevices() == 1);
	this->logAllDevices();
	internet_stack_helper.Install(ns3::NodeContainer(this));
	NS_LOG_INFO("InternetStackHelper::Install finished");
	this->logAllDevices();
	NS_ASSERT(this->GetNDevices() == 2);
	NS_ASSERT(this->GetDevice(1)->GetObject<ns3::LoopbackNetDevice>(ns3::LoopbackNetDevice::GetTypeId()));
}

void EunetTerminal::installPacketSink() {
	NS_LOG_INFO("installing packet sink on node " << this->GetId());
	ns3::PacketSinkHelper packet_sink_helper("ns3::UdpSocketFactory",
			ns3::Address(ns3::InetSocketAddress(ns3::Ipv4Address::GetAny(),
					PACKET_SINK_UDP_PORT)));
	this->packetSink = packet_sink_helper.Install(this);
	this->packetSink.Start(ns3::Seconds(0.0));
}//installPacketSink

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

ns3::Ipv4Address EunetTerminal::getCsmaNetDeviceAddress() {
	NS_ASSERT(this->GetNDevices()==2);
	ns3::Ptr<ns3::Ipv4> ptr_ipv4 = this->GetObject<ns3::Ipv4> ();
	ns3::Ptr<ns3::CsmaNetDevice> ptr_csma_net_device = this->getCsmaNetDevice();
	const int i_interface =
			ptr_ipv4->GetInterfaceForDevice(ptr_csma_net_device);
	ns3::Ipv4InterfaceAddress ipv4_interface_address = ptr_ipv4->GetAddress(
			i_interface, 0);
	ns3::Ipv4Address ipv4_address = ipv4_interface_address.GetLocal();
	return ipv4_address;
}//getAddress

uint32_t EunetTerminal::getTotalRx() {
	return this->packetSink.Get(0)->GetObject<ns3::PacketSink> ()->GetTotalRx();
}

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
