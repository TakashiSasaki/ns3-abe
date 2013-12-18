#define NS3_LOG_ENABLE 1
#include "ns3/log.h"
NS_LOG_COMPONENT_DEFINE("SimpleAp");
#define NS3_ASSERT_ENABLE 1
#include "ns3/assert.h"
#include "ns3/wifi-helper.h"
#include "ns3/nqos-wifi-mac-helper.h"
#include "ns3/yans-wifi-helper.h"
#include "ns3/ssid.h"
#include "ns3/boolean.h"
#include "ns3/mobility-helper.h"
#include "SimpleAp.h"
NS_OBJECT_ENSURE_REGISTERED(SimpleAp);

ns3::TypeId SimpleAp::GetTypeId(void) {
	static ns3::TypeId type_id =
			ns3::TypeId("SimpleAp").SetParent<SimpleSwitch> ().AddConstructor<
					SimpleAp> ();
	return type_id;
}//GetTypeId

SimpleAp::SimpleAp() {
	//NS_FATAL_ERROR("no default constructor for SimpleAp");
	auto wifi_channel_helper = ns3::YansWifiChannelHelper::Default();
	auto ptr_wifi_channel = wifi_channel_helper.Create();
	auto wifi_phy_helper = ns3::YansWifiPhyHelper::Default();
	wifi_phy_helper.SetChannel(ptr_wifi_channel);
	auto wifi_mac_helper = ns3::NqosWifiMacHelper::Default();
	//auto ssid = ns3::Ssid("eunet");
	wifi_mac_helper.SetType("ns3::ApWifiMac"/*, "Ssid", ns3::SsidValue(ssid)*/);
	auto wifi_helper = ns3::WifiHelper::Default();
	auto ptr_node = ns3::Ptr<SimpleSwitch>(this, true);
	//auto ptr_node = ns3::CreateObject<ns3::Node>();
	auto n_devices_before = this->GetNDevices();
	NS_LOG_INFO("installing wifi phy and mac on this node.");
	wifi_helper.Install(wifi_phy_helper, wifi_mac_helper, ptr_node);
	auto n_devices_after = this->GetNDevices();
	NS_ASSERT(n_devices_after == n_devices_before + 1);
}

void SimpleAp::setPosition(const ns3::Vector& position) {
	this->position = position;
}//setPosition

void SimpleAp::DoInitialize() {
	auto ptr_node = ns3::Ptr<SimpleAp>(this, true);
	NS_LOG_INFO("setting position to " << this->position);
	ns3::MobilityHelper mobility_helper;
	auto ptr_position_allocator =
			ns3::CreateObject<ns3::ListPositionAllocator>();
	ptr_position_allocator->Add(this->position);
	mobility_helper.SetPositionAllocator(ptr_position_allocator);
	mobility_helper.SetMobilityModel("ns3::ConstantPositionMobilityModel");
	mobility_helper.Install(ptr_node);
	NS_LOG_INFO("calling up SimpleSwitch::DoInitialize");
	Base::DoInitialize();
}

void SimpleAp::NotifyConstructionCompleted() {
	NS_LOG_INFO("just calling up SimpleSwitch::NotifyConstructionCompleted");
	Base::NotifyConstructionCompleted();
}

SimpleAp::~SimpleAp() {
	// TODO !CodeTemplates.destructorstub.tododesc!
}
