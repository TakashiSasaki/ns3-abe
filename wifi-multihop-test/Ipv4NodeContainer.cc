/*
 * Ipv4NodeContainer.cc
 *
 *  Created on: 2013/10/29
 *      Author: sasaki
 */
#include "ns3/ipv4-list-routing-helper.h"
#include "ns3/ipv4-static-routing-helper.h"
#include "ns3/olsr-helper.h"
#include "ns3/internet-stack-helper.h"
#include "ns3/ipv4-address-helper.h"
#include "ns3/log.h"
#include "ns3/flow-id-tag.h"
#include "Ipv4NodeContainer.h"

namespace abe {

Ipv4NodeContainer::Ipv4NodeContainer(const int packetSize) :
	packetSize(packetSize) {
	ns3::Ipv4ListRoutingHelper ipv4_list_routing_helper;
	ipv4_list_routing_helper.Add(ns3::Ipv4StaticRoutingHelper(), 0);
	ipv4_list_routing_helper.Add(ns3::OlsrHelper(), 10);

	ns3::InternetStackHelper internet_stack_helper;
	internet_stack_helper.SetRoutingHelper(ipv4_list_routing_helper);
	internet_stack_helper.Install(*this);

	ns3::Ipv4AddressHelper ipv4_address_helper;
	NS_LOG_INFO ("Assign IP Addresses.");
	ipv4_address_helper.SetBase("10.1.1.0", "255.255.255.0");
	ns3::Ipv4InterfaceContainer i = ipv4_address_helper.Assign(
			this->getNetDeviceContainer());
}

Ipv4NodeContainer::~Ipv4NodeContainer() {
	// TODO !CodeTemplates.destructorstub.tododesc!
}

ns3::Ptr<ns3::Ipv4L3Protocol> Ipv4NodeContainer::getIpv4L3Protocol(
		const int i_node) const {
	return this->Get(i_node)->GetObject<ns3::Ipv4L3Protocol> ();
}//getIpv4L3Protocol

ns3::Ptr<ns3::Socket> Ipv4NodeContainer::getIpv4RawSocket(const int i_node) {
	ns3::Ptr<ns3::Socket> ipv4_raw_socket =
			this->getIpv4L3Protocol(i_node)->CreateRawSocket();
	ipv4_raw_socket->SetRecvCallback(ns3::MakeCallback(
			&abe::Ipv4NodeContainer::receiveCallback, this));
	return ipv4_raw_socket;
}//getIpv4RawSocket

void Ipv4NodeContainer::scheduleSendPacket(const ns3::Time& t, const int i_node) {
	ns3::Simulator::Schedule(t, &abe::Ipv4NodeContainer::sendPacket, this,
			this->getIpv4RawSocket(0), this->getAddress(i_node));
}//scheduleSendPacket

void Ipv4NodeContainer::receiveCallback(ns3::Ptr<ns3::Socket> p_socket) {
	ns3::Ptr<ns3::Packet> p_packet = p_socket->Recv();
	ns3::FlowIdTag tag;
	p_packet->FindFirstMatchingByteTag(tag);
	std::ostringstream oss;
	oss << ns3::Simulator::Now() << " " << p_socket->GetNode()->GetId()
			<< " receive " << tag.GetFlowId();
	p_packet->CopyData(&oss, p_packet->GetSize());
	oss << std::endl;
	NS_LOG_INFO(oss.str());
	//      std::ostringstream oss;
	//      p_packet->CopyData(&oss, p_packet->GetSize());
	//NS_LOG_UNCOND (oss.str());
}//receivePacket

ns3::Address Ipv4NodeContainer::getAddress(const int i_node) {
	return this->Get(i_node)->GetDevice(0)->GetAddress();
}//getAddress

void Ipv4NodeContainer::sendPacket(const ns3::Ptr<ns3::Socket> p_socket,
		const ns3::Address& destination_address) {
	ns3::Ptr<ns3::Packet> p_packet = ns3::Create<ns3::Packet>(this->packetSize);
	uint32_t flowId = ns3::FlowIdTag::AllocateFlowId();
	p_packet->AddByteTag(ns3::FlowIdTag(flowId));
	p_socket->SendTo(p_packet, 0, destination_address);
	std::ostringstream oss;
	oss << ns3::Simulator::Now() << " " << p_socket->GetNode()->GetId()
			<< " send " << flowId << std::endl;
	NS_LOG_INFO(oss.str());
}//sendPacket


}//abe
