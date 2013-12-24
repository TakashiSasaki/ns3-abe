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
#include "WifiBase.h"

WifiBase::WifiBase(ns3::Node* p_node) :
	ptrNode(p_node, true), ifIndex(-1) {
	//NS_FATAL_ERROR("no default constructor for SimpleAp");
	auto wifi_channel_helper = ns3::YansWifiChannelHelper::Default();
	auto ptr_wifi_channel = wifi_channel_helper.Create();
	auto wifi_phy_helper = ns3::YansWifiPhyHelper::Default();
	wifi_phy_helper.SetChannel(ptr_wifi_channel);
	auto wifi_mac_helper = ns3::NqosWifiMacHelper::Default();
	wifi_mac_helper.SetType("ns3::ApWifiMac");
	auto wifi_helper = ns3::WifiHelper::Default();
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
}

WifiBase::~WifiBase() {
}

void WifiBase::setSsid(const ns3::Ssid& ssid) {
	this->ssid = ssid;
}
