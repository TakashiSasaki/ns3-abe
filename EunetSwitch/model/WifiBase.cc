#define NS3_LOG_ENABLE 1
#include "ns3/log.h"
NS_LOG_COMPONENT_DEFINE("WifiBase");
#define NS3_ASSERT_ENABLE 1
#include "ns3/assert.h"
#include "ns3/net-device.h"
#include "ns3/wifi-mac.h"
#include "ns3/yans-wifi-helper.h"
#include "ns3/nqos-wifi-mac-helper.h"
#include "ns3/wifi-net-device.h"
#include "ns3/wifi-mac-header.h"
#include "ns3/traced-value.h"
#include "ns3/trace-source-accessor.h"
#include "WifiBase.h"

WifiBase::WifiMacTypeString WifiBase::AdhocWifiMac = "ns3::AdhocWifiMac";
WifiBase::WifiMacTypeString WifiBase::ApWifiMac = "ns3::ApWifiMac";
WifiBase::WifiMacTypeString WifiBase::MeshWifiNeterfaceMac =
		"ns3::MeshWifiInterfaceMac";
WifiBase::WifiMacTypeString WifiBase::OcbWifimac = "ns3::OcbWifiMac";
WifiBase::WifiMacTypeString WifiBase::StaWifiMac = "ns3::StaWifiMac";

WifiBase::WifiBase(ns3::Node* p_node,
		const WifiBase::WifiMacTypeString wifi_mac_type_string,
		bool active_probing) :
	ptrNode(p_node, true), ifIndex(-1) {
	//NS_FATAL_ERROR("no default constructor for SimpleAp");
	auto wifi_channel_helper = ns3::YansWifiChannelHelper::Default();
	auto ptr_wifi_channel = wifi_channel_helper.Create();
	auto wifi_phy_helper = ns3::YansWifiPhyHelper::Default();
	wifi_phy_helper.SetChannel(ptr_wifi_channel);
	auto wifi_mac_helper = ns3::NqosWifiMacHelper::Default();
	if (active_probing == true) {
		wifi_mac_helper.SetType(wifi_mac_type_string, "ActiveProbing",
				ns3::BooleanValue(active_probing));
	} else {
		wifi_mac_helper.SetType(wifi_mac_type_string);
	}
	auto wifi_helper = ns3::WifiHelper::Default();
	wifi_helper.SetRemoteStationManager("ns3::ArfWifiManager");
	auto n_devices_before = ptrNode->GetNDevices();
	NS_LOG_INFO("installing wifi phy and mac on this node.");
	auto devices = wifi_helper.Install(wifi_phy_helper, wifi_mac_helper,
			ptrNode);
	NS_ASSERT(devices.GetN()==1);
	this->ifIndex = devices.Get(0)->GetIfIndex();
	auto n_devices_after = ptrNode->GetNDevices();
	NS_ASSERT(n_devices_after == n_devices_before + 1);
}// a constructor

void WifiBase::DoInitialize() {
	NS_LOG_INFO("setting ssid to " << this->ssid);
	NS_ASSERT(this->ifIndex >= 0);
	ns3::Ptr<ns3::NetDevice> ptr_net_device = ptrNode->GetDevice(this->ifIndex);
	ns3::Ptr<ns3::WifiNetDevice> ptr_wifi_net_device =
			ptr_net_device->GetObject<ns3::WifiNetDevice> ();
	NS_ASSERT(ptr_wifi_net_device != 0);
	auto ptr_wifi_mac = ptr_wifi_net_device->GetMac();
	NS_ASSERT(ptr_wifi_mac != 0);
	//NS_LOG_UNCOND(ptr_wifi_mac);
	if (this->ssid.IsEqual(ns3::Ssid())) {
		NS_FATAL_ERROR("ssid is not specified. call setSsid in advance.");
	}
	ptr_wifi_mac->SetSsid(this->ssid);

	ptr_wifi_mac->TraceConnectWithoutContext("MacTx", ns3::MakeCallback(
			&WifiBase::traceMacTx, this));
	ptr_wifi_mac->TraceConnectWithoutContext("MacTxDrop", ns3::MakeCallback(
			&WifiBase::traceMacTxDrop, this));
	ptr_wifi_mac->TraceConnectWithoutContext("MacPromiscRx", ns3::MakeCallback(
			&WifiBase::traceMacPromiscRx, this));
	ptr_wifi_mac->TraceConnectWithoutContext("MacRx", ns3::MakeCallback(
			&WifiBase::traceMacRx, this));
	ptr_wifi_mac->TraceConnectWithoutContext("MacRxDrop", ns3::MakeCallback(
			&WifiBase::traceMacRxDrop, this));

	auto ptr_wifi_phy = ptr_wifi_net_device->GetPhy();

	ptr_wifi_phy->TraceConnectWithoutContext("PhyTxBegin", ns3::MakeCallback(
			&WifiBase::tracePhyTxBegin, this));
	ptr_wifi_phy->TraceConnectWithoutContext("PhyTxEnd", ns3::MakeCallback(
			&WifiBase::tracePhyTxEnd, this));
	ptr_wifi_phy->TraceConnectWithoutContext("PhyTxDrop", ns3::MakeCallback(
			&WifiBase::tracePhyTxDrop, this));
}

WifiBase::~WifiBase() {
}

void WifiBase::setSsid(const ns3::Ssid& ssid) {
	this->ssid = ssid;
}

ns3::Ptr<ns3::WifiNetDevice> WifiBase::getWifiNetDevice() {
	auto ptr_net_device = this->ptrNode->GetDevice(this->ifIndex);
	auto ptr_wifi_net_device = ptr_net_device->GetObject<ns3::WifiNetDevice> ();
	NS_ASSERT(ptr_wifi_net_device != 0);
	return ptr_wifi_net_device;
}

void WifiBase::traceMacTx(ns3::Ptr<const ns3::Packet> ptr_packet) const {
	NS_LOG_INFO(ptr_packet->GetSize() << " bytes " << "MacTx on node " << this->ptrNode->GetId());
}

void WifiBase::traceMacTxDrop(ns3::Ptr<const ns3::Packet> ptr_packet) const {
	NS_LOG_INFO(ptr_packet->GetSize() << " bytes " << "MacTxDrop on node " << this->ptrNode->GetId());
}

void WifiBase::traceMacPromiscRx(ns3::Ptr<const ns3::Packet> ptr_packet) const {
	NS_LOG_INFO(ptr_packet->GetSize() << " bytes " << "MacPromiscRx on node "<< this->ptrNode->GetId());
}

void WifiBase::traceMacRx(ns3::Ptr<const ns3::Packet> ptr_packet) const {
	NS_LOG_INFO(ptr_packet->GetSize() << " bytes " << "MacRx on node "<< this->ptrNode->GetId());
}

void WifiBase::traceMacRxDrop(ns3::Ptr<const ns3::Packet> ptr_packet) const {
	NS_LOG_INFO(ptr_packet->GetSize() << " bytes " << "MacRxDrop on node " << this->ptrNode->GetId());
}

void WifiBase::tracePhyTxBegin(ns3::Ptr<const ns3::Packet> ptr_packet) const {
	NS_LOG_INFO(ptr_packet->GetSize() << " bytes " <<" PhyTxBegin on node " << this->ptrNode->GetId());
}

void WifiBase::tracePhyTxEnd(ns3::Ptr<const ns3::Packet> ptr_packet) const {
	NS_LOG_INFO(ptr_packet->GetSize() << " bytes " <<" PhyTxEnd on node " << this->ptrNode->GetId());
}

void WifiBase::tracePhyTxDrop(ns3::Ptr<const ns3::Packet> ptr_packet) const {
	NS_LOG_INFO(ptr_packet->GetSize() << " bytes " <<" PhyTxDrop on node " << this->ptrNode->GetId());
}
