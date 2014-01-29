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
#include "WifiDevice.h"

WifiBase::WifiMacTypeString WifiBase::AdhocWifiMac = "ns3::AdhocWifiMac";
WifiBase::WifiMacTypeString WifiBase::ApWifiMac = "ns3::ApWifiMac";
WifiBase::WifiMacTypeString WifiBase::MeshWifiNeterfaceMac =
		"ns3::MeshWifiInterfaceMac";
WifiBase::WifiMacTypeString WifiBase::OcbWifimac = "ns3::OcbWifiMac";
WifiBase::WifiMacTypeString WifiBase::StaWifiMac = "ns3::StaWifiMac";

WifiBase::WifiBase(ns3::Node* p_node,
		const WifiBase::WifiMacTypeString wifi_mac_type_string,
		bool active_probing) :
	TraceBase(p_node), WifiPhyTrace(p_node), WifiMacTrace(p_node), ptrNode(
			p_node, true), ifIndex(-1) {
	// enable rts cts all the time.#define NS3_LOG_ENABLE 1
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
	NS_LOG_INFO(ptr_wifi_mac->GetAddress());
	NS_ASSERT(ptr_wifi_mac != 0);
	//NS_LOG_UNCOND(ptr_wifi_mac);
	if (this->ssid.IsEqual(ns3::Ssid())) {
		NS_FATAL_ERROR("ssid is not specified. call setSsid in advance.");
	}
	ptr_wifi_mac->SetSsid(this->ssid);

	WifiMacTrace::DoInitialize();
	WifiPhyTrace::DoInitialize();
}

WifiBase::~WifiBase() {
}

void WifiBase::NotifyConstructionCompleted() {
}

void WifiBase::DoDispose() {
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
			this->ptrNode->GetObject<CsmaNode> ()->getDevice<WifiDevice> (0);
	auto ptr_wifi_phy = ptr_wifi_net_device->GetPhy();
	auto ptr_yans_wifi_phy = ptr_wifi_phy->GetObject<ns3::YansWifiPhy> ();
	auto ptr_wifi_channel = ptr_wifi_phy->GetChannel();
	auto ptr_yans_wifi_channel = ptr_wifi_channel->GetObject<
			ns3::YansWifiChannel> ();
	auto
			ptr_foreign_wifi_net_device = foreign_node.ptrNode->GetObject<
					CsmaNode> ()->getDevice<WifiDevice> (0);
	auto ptr_foreign_wifi_phy = ptr_foreign_wifi_net_device->GetPhy();
	auto ptr_foreign_yans_wifi_phy = ptr_foreign_wifi_phy->GetObject<
			ns3::YansWifiPhy> ();
	ptr_foreign_yans_wifi_phy->SetChannel(ptr_yans_wifi_channel);
}

void WifiBase::traceMacTx(ns3::Ptr<const ns3::Packet> ptr_packet) const {
	std::ostringstream oss;
	getHex(oss, ptr_packet);
	NS_LOG_INFO(ns3::Simulator::Now() << "\t" << ptr_packet->GetSize() << " bytes " << "MacTx\t\ton node " << this->ptrNode->GetId() << " " << oss.str());
}

void WifiBase::traceMacTxDrop(ns3::Ptr<const ns3::Packet> ptr_packet) const {
	std::ostringstream oss;
	getHex(oss, ptr_packet);
	NS_LOG_INFO(ns3::Simulator::Now() << "\t" << ptr_packet->GetSize() << " bytes " << "MacTxDrop\ton node " << this->ptrNode->GetId() << " " << oss.str());
}

void WifiBase::traceMacPromiscRx(ns3::Ptr<const ns3::Packet> ptr_packet) const {
	NS_LOG_INFO(ptr_packet->GetSize() << " bytes " << "MacPromiscRx\ton node "<< this->ptrNode->GetId());
}

void WifiBase::traceMacRx(ns3::Ptr<const ns3::Packet> ptr_packet) const {
	std::ostringstream oss;
	getHex(oss, ptr_packet);
	NS_LOG_INFO(ns3::Simulator::Now() << "\t" << ptr_packet->GetSize() << " bytes " << "MacRx\ton node "<< this->ptrNode->GetId() << " " << oss.str());
}

void WifiBase::traceMacRxDrop(ns3::Ptr<const ns3::Packet> ptr_packet) const {
	std::ostringstream oss;
	getHex(oss, ptr_packet);
	NS_LOG_INFO(ns3::Simulator::Now() << "\t" << ptr_packet->GetSize() << " bytes " << "MacRxDrop\ton node " << this->ptrNode->GetId() << " " << oss.str());
}

void WifiBase::tracePhyTxBegin(ns3::Ptr<const ns3::Packet> ptr_packet) const {
	std::ostringstream oss;
	getHex(oss, ptr_packet);
	NS_LOG_INFO(ns3::Simulator::Now() << "\t" << ptr_packet->GetSize() << " bytes " <<"PhyTxBegin\ton node " << this->ptrNode->GetId() << " " << oss.str());
}

void WifiBase::tracePhyTxEnd(ns3::Ptr<const ns3::Packet> ptr_packet) const {
	std::ostringstream oss;
	getHex(oss, ptr_packet);
	NS_LOG_INFO(ns3::Simulator::Now() << "\t" << ptr_packet->GetSize() << " bytes " <<"PhyTxEnd\ton node " << this->ptrNode->GetId() << " " << oss.str());
}

void WifiBase::tracePhyTxDrop(ns3::Ptr<const ns3::Packet> ptr_packet) const {
	std::ostringstream oss;
	getHex(oss, ptr_packet);
	NS_LOG_INFO(ns3::Simulator::Now() << "\t" << ptr_packet->GetSize() << " bytes " <<"PhyTxDrop\ton node " << this->ptrNode->GetId() << " " << oss.str());
}

void WifiBase::tracePhyRxBegin(ns3::Ptr<const ns3::Packet> ptr_packet) const {
	std::ostringstream oss;
	getHex(oss, ptr_packet);
	NS_LOG_INFO(ns3::Simulator::Now() << "\t" << ptr_packet->GetSize() << " bytes " <<"PhyRxBegin\ton node " << this->ptrNode->GetId() << " " << oss.str());
}

void WifiBase::tracePhyRxEnd(ns3::Ptr<const ns3::Packet> ptr_packet) const {
	std::ostringstream oss;
	getHex(oss, ptr_packet);
	NS_LOG_INFO(ns3::Simulator::Now() << "\t" << ptr_packet->GetSize() << " bytes " <<"PhyRxEnd\ton node " << this->ptrNode->GetId() << " " << oss.str());
}

void WifiBase::tracePhyRxDrop(ns3::Ptr<const ns3::Packet> ptr_packet) const {
	std::ostringstream oss;
	getHex(oss, ptr_packet);
	NS_LOG_INFO(ns3::Simulator::Now() << "\t" << ptr_packet->GetSize() << " bytes " <<"PhyRxDrop\ton node " << this->ptrNode->GetId() << " " << oss.str());
}
