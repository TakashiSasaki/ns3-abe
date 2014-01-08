#define NS3_LOG_ENABLE 1
#include "ns3/log.h"
NS_LOG_COMPONENT_DEFINE("WifiMacTrace");
#define NS3_ASSERT_ENABLE 1
#include "ns3/assert.h"
#include "ns3/simulator.h"
#include "ns3/node.h"
#include "ns3/wifi-mac.h"
#include "ns3/wifi-net-device.h"
#include "WifiMacTrace.h"

void WifiMacTrace::traceMacTx(ns3::Ptr<const ns3::Packet> ptr_packet) const {
	std::ostringstream oss;
	getHex(oss, ptr_packet);
	NS_LOG_INFO(ns3::Simulator::Now() << "\t" << ptr_packet->GetSize() << " bytes " << "MacTx\t\ton node " << this->ptrNode->GetId() << " " << oss.str());
}

void WifiMacTrace::traceMacTxDrop(ns3::Ptr<const ns3::Packet> ptr_packet) const {
	std::ostringstream oss;
	getHex(oss, ptr_packet);
	NS_LOG_INFO(ns3::Simulator::Now() << "\t" << ptr_packet->GetSize() << " bytes " << "MacTxDrop\ton node " << this->ptrNode->GetId() << " " << oss.str());
}

void WifiMacTrace::traceMacPromiscRx(ns3::Ptr<const ns3::Packet> ptr_packet) const {
	NS_LOG_INFO(ptr_packet->GetSize() << " bytes " << "MacPromiscRx\ton node "<< this->ptrNode->GetId());
}

void WifiMacTrace::traceMacRx(ns3::Ptr<const ns3::Packet> ptr_packet) const {
	std::ostringstream oss;
	getHex(oss, ptr_packet);
	NS_LOG_INFO(ns3::Simulator::Now() << "\t" << ptr_packet->GetSize() << " bytes " << "MacRx\ton node "<< this->ptrNode->GetId() << " " << oss.str());
}

void WifiMacTrace::traceMacRxDrop(ns3::Ptr<const ns3::Packet> ptr_packet) const {
	std::ostringstream oss;
	getHex(oss, ptr_packet);
	NS_LOG_INFO(ns3::Simulator::Now() << "\t" << ptr_packet->GetSize() << " bytes " << "MacRxDrop\ton node " << this->ptrNode->GetId() << " " << oss.str());
}

WifiMacTrace::WifiMacTrace(ns3::Node* p_node) :
	TraceBase(p_node) {
}

WifiMacTrace::~WifiMacTrace() {
}

void WifiMacTrace::DoInitialize() {
	for (unsigned i = 0; i < this->ptrNode->GetNDevices(); ++i) {
		auto ptr_net_device = this->ptrNode->GetDevice(i);
		auto type_id = ptr_net_device->GetTypeId();
		if (!type_id.IsChildOf(ns3::WifiNetDevice::GetTypeId()))
			continue;
		auto ptr_wifi_net_device =
				ptr_net_device->GetObject<ns3::WifiNetDevice> ();
		auto ptr_wifi_mac = ptr_wifi_net_device->GetMac();
		ptr_wifi_mac->TraceConnectWithoutContext("MacTx", ns3::MakeCallback(
				&WifiMacTrace::traceMacTx, this));
		ptr_wifi_mac->TraceConnectWithoutContext("MacTxDrop",
				ns3::MakeCallback(&WifiMacTrace::traceMacTxDrop, this));
		ptr_wifi_mac->TraceConnectWithoutContext("MacPromiscRx",
				ns3::MakeCallback(&WifiMacTrace::traceMacPromiscRx, this));
		ptr_wifi_mac->TraceConnectWithoutContext("MacRx", ns3::MakeCallback(
				&WifiMacTrace::traceMacRx, this));
		ptr_wifi_mac->TraceConnectWithoutContext("MacRxDrop",
				ns3::MakeCallback(&WifiMacTrace::traceMacRxDrop, this));
	}//for
}
