#include <iomanip>
#define NS3_LOG_ENABLE 1
#include "ns3/log.h"
NS_LOG_COMPONENT_DEFINE("WifiBase");
#define NS3_ASSERT_ENABLE 1
#include "ns3/assert.h"
#include "ns3/net-device.h"
#include "ns3/wifi-mac.h"
#include "ns3/yans-wifi-phy.h"
#include "ns3/yans-wifi-helper.h"
#include "ns3/nqos-wifi-mac-helper.h"
#include "ns3/wifi-net-device.h"
#include "ns3/wifi-mac-header.h"
#include "ns3/traced-value.h"
#include "ns3/trace-source-accessor.h"
#include "ns3/config.h"
#include "ns3/string.h"
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
	// enable rts cts all the time.
	ns3::Config::SetDefault("ns3::WifiRemoteStationManager::RtsCtsThreshold",
			ns3::StringValue("0"));
	// disable fragmentation
	ns3::Config::SetDefault(
			"ns3::WifiRemoteStationManager::FragmentationThreshold",
			ns3::StringValue("2200"));
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
	ptr_wifi_phy->TraceConnectWithoutContext("PhyRxBegin", ns3::MakeCallback(
			&WifiBase::tracePhyRxBegin, this));
	ptr_wifi_phy->TraceConnectWithoutContext("PhyRxDrop", ns3::MakeCallback(
			&WifiBase::tracePhyRxDrop, this));
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

void WifiBase::bringWifiBase(WifiBase& foreign_node) {
	auto ptr_wifi_net_device =
			this->ptrNode->GetObject<CsmaNode> ()->getNetDevice<
					ns3::WifiNetDevice> ();
	auto ptr_wifi_phy = ptr_wifi_net_device->GetPhy();
	auto ptr_yans_wifi_phy = ptr_wifi_phy->GetObject<ns3::YansWifiPhy> ();
	auto ptr_wifi_channel = ptr_wifi_phy->GetChannel();
	auto ptr_yans_wifi_channel = ptr_wifi_channel->GetObject<
			ns3::YansWifiChannel> ();
	auto ptr_foreign_wifi_net_device =
			foreign_node.ptrNode->GetObject<CsmaNode> ()->getNetDevice<
					ns3::WifiNetDevice> ();
	auto ptr_foreign_wifi_phy = ptr_foreign_wifi_net_device->GetPhy();
	auto ptr_foreign_yans_wifi_phy = ptr_foreign_wifi_phy->GetObject<
			ns3::YansWifiPhy> ();
	ptr_foreign_yans_wifi_phy->SetChannel(ptr_yans_wifi_channel);
}

void WifiBase::getHex(std::ostream& os, ns3::Ptr<const ns3::Packet> ptr_packet) {

	uint8_t buffer[ptr_packet->GetSize()];
	for (unsigned i = 0; i < sizeof buffer; ++i) {
		os << std::hex << std::setw(2) << std::setfill('0')
				<< (unsigned) buffer[i];
	}
}

void WifiBase::traceMacTx(ns3::Ptr<const ns3::Packet> ptr_packet) const {
	std::ostringstream oss;
	getHex(oss, ptr_packet);
	NS_LOG_INFO(ptr_packet->GetSize() << " bytes " << "MacTx\t\ton node " << this->ptrNode->GetId() << " " << oss.str());
}

void WifiBase::traceMacTxDrop(ns3::Ptr<const ns3::Packet> ptr_packet) const {
	std::ostringstream oss;
	getHex(oss, ptr_packet);
	NS_LOG_INFO(ptr_packet->GetSize() << " bytes " << "MacTxDrop\ton node " << this->ptrNode->GetId() << " " << oss.str());
}

void WifiBase::traceMacPromiscRx(ns3::Ptr<const ns3::Packet> ptr_packet) const {
	NS_LOG_INFO(ptr_packet->GetSize() << " bytes " << "MacPromiscRx\ton node "<< this->ptrNode->GetId());
}

void WifiBase::traceMacRx(ns3::Ptr<const ns3::Packet> ptr_packet) const {
	NS_LOG_INFO(ptr_packet->GetSize() << " bytes " << "MacRx on node "<< this->ptrNode->GetId());
}

void WifiBase::traceMacRxDrop(ns3::Ptr<const ns3::Packet> ptr_packet) const {
	NS_LOG_INFO(ptr_packet->GetSize() << " bytes " << "MacRxDrop on node " << this->ptrNode->GetId());
}

void WifiBase::tracePhyTxBegin(ns3::Ptr<const ns3::Packet> ptr_packet) const {
	std::ostringstream oss;
	getHex(oss, ptr_packet);
	NS_LOG_INFO(ptr_packet->GetSize() << " bytes " <<"PhyTxBegin\ton node " << this->ptrNode->GetId() << " " << oss.str());
}

void WifiBase::tracePhyTxEnd(ns3::Ptr<const ns3::Packet> ptr_packet) const {
	std::ostringstream oss;
	getHex(oss, ptr_packet);
	NS_LOG_INFO(ptr_packet->GetSize() << " bytes " <<"PhyTxEnd\ton node " << this->ptrNode->GetId() << " " << oss.str());
}

void WifiBase::tracePhyTxDrop(ns3::Ptr<const ns3::Packet> ptr_packet) const {
	std::ostringstream oss;
	getHex(oss, ptr_packet);
	NS_LOG_INFO(ptr_packet->GetSize() << " bytes " <<"PhyTxDrop\ton node " << this->ptrNode->GetId() << " " << oss.str());
}

void WifiBase::tracePhyRxBegin(ns3::Ptr<const ns3::Packet> ptr_packet) const {
	NS_LOG_INFO(ptr_packet->GetSize() << " bytes " <<"PhyRxBegin on node " << this->ptrNode->GetId());
}

void WifiBase::tracePhyRxDrop(ns3::Ptr<const ns3::Packet> ptr_packet) const {
	NS_LOG_INFO(ptr_packet->GetSize() << " bytes " <<"PhyRxDrop on node " << this->ptrNode->GetId());
}
