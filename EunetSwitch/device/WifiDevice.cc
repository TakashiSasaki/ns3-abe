#define NS3_LOG_ENABLE 1
#include "ns3/log.h"
NS_LOG_COMPONENT_DEFINE("WifiDevice");
#define NS3_ASSERT_ENABLE 1
#include "ns3/assert.h"
#include "ns3/names.h"
#include "ns3/yans-wifi-helper.h"
#include "ns3/yans-wifi-phy.h"
#include "ns3/constant-rate-wifi-manager.h"
#include "ns3/nqos-wifi-mac-helper.h"
#include "ns3/string.h"
#include "ns3/double.h"
#include "ns3/boolean.h"
#include "ns3/regular-wifi-mac.h"
#include "ns3/error-rate-model.h"
#include "WifiDevice.h"
#include "init.h"

ns3::TypeId WifiDevice::GetTypeId(void) {
	static ns3::TypeId type_id = ns3::TypeId("WifiDevice"). SetParent<
			ns3::WifiNetDevice> () .AddConstructor<WifiDevice> ().AddAttribute(
			"phyMode", "phyMode", ns3::StringValue("DsssRate1Mbps"),
			ns3::MakeStringAccessor(&WifiDevice::phyMode),
			ns3::MakeStringChecker()). AddAttribute("rss", "rss",
			ns3::DoubleValue(-80.0), ns3::MakeDoubleAccessor(&WifiDevice::rss),
			ns3::MakeDoubleChecker<double>()).AddAttribute("wifiMacType",
			"wifiMacType", ns3::StringValue("ns3::AdhocWifiMac"),
			ns3::MakeStringAccessor(&WifiDevice::wifiMacType),
			ns3::MakeStringChecker());
	return type_id;
}//GetTypeId

WifiDevice::WifiDevice() {
}

WifiDevice::~WifiDevice() {
}

void WifiDevice::NotifyConstructionCompleted() {
	ASSERT_NCC;
	ns3::WifiNetDevice::NotifyConstructionCompleted();
	this->SetAddress(ns3::Mac48Address::Allocate());
	this->SetMac(this->createMac());
	this->SetPhy(this->createPhy());
	this->SetRemoteStationManager(this->createRemoteStationManager());
}

void WifiDevice::DoInitialize(){
	ASSERT_DI;
	ns3::WifiNetDevice::DoInitialize();
	//TODO
	NS_LOG_UNCOND("to be implemented");
}

void WifiDevice::DoDispose(){
	ASSERT_DD;
	ns3::WifiNetDevice::DoDispose();
	//TODO
	NS_LOG_UNCOND("to be implemented");
}

void WifiDevice::enablePcap(const bool promiscuous) {
	auto name = ns3::Names::FindName(this);
	if (name.empty()) {
		std::ostringstream oss;
		oss << this->GetInstanceTypeId() << "-" << this->GetNode()->GetId()
				<< "-" << this->GetIfIndex();
		name = oss.str();
	}
	{
		NS_LOG_DEBUG("enablePcap on node " << name);
		ns3::YansWifiPhyHelper yans_wifi_phy_helper;
		yans_wifi_phy_helper.EnablePcap(name, this, promiscuous);
	}
}//enablePcap

#if 0
void WifiDevice::enablePcap(const bool promiscuous) {
	//TODO: to be merged and compromised
	NS_LOG_UNCOND("");
	ns3::YansWifiPhyHelper yans_wifi_phy_helper;
	yans_wifi_phy_helper.SetPcapDataLinkType(
			ns3::YansWifiPhyHelper::DLT_IEEE802_11_RADIO);
	auto node = this->GetNode();
	auto name = ns3::Names::FindName(node);
	yans_wifi_phy_helper.EnablePcap(name, ns3::Ptr<WifiDevice>(this, true));
}
#endif



int WifiDevice::getInt(const int i) {
	return i + 234;
}

ns3::Ptr<ns3::NetDevice> WifiDevice::getNetDevice() {
	return ns3::Ptr<ns3::NetDevice>(this, true);
}

ns3::Ptr<ns3::WifiRemoteStationManager> WifiDevice::createRemoteStationManager() {
	ns3::ObjectFactory object_factory;
	object_factory.SetTypeId(ns3::ConstantRateWifiManager::GetTypeId());
	// enable rts cts all the time
	object_factory.Set("ns3::WifiRemoteStationManager::RtsCtsThreshold",
			ns3::StringValue("2200"));
	// disable fragmentation
	object_factory.Set("ns3::WifiRemoteStationManager::FragmentationThreshold",
			ns3::StringValue("2200"));
	// fix non-unicast data rate to be the same as that of unicast
	object_factory.Set("ns3::WifiRemoteStationManager::NonUnicastMode",
			ns3::StringValue(phyMode));
	// ConstantRateWifiManager is a derived class of WifiRemoteStationManager.
	// Other options are AarfWifiManager, AmrrWifiManager, ArfWifiManager, RraaWifiManage, etc.
	object_factory.Set("DataMode", ns3::StringValue(phyMode));
	object_factory.Set("ControlMode", ns3::StringValue(phyMode));
	return object_factory.Create<ns3::ConstantRateWifiManager> ();
}

ns3::Ptr<ns3::WifiPhy> WifiDevice::createPhy() {
	// creating wifi phy helper
	ns3::ObjectFactory of;
	of.SetTypeId(ns3::YansWifiPhy::GetTypeId());
	of.Set("RxGain", ns3::DoubleValue(0.0));
	ns3::Ptr<ns3::YansWifiPhy> phy = of.Create<ns3::YansWifiPhy> ();

	phy->SetErrorRateModel(this->createErrorRateModel());
	phy->SetChannel(this->createChannel());
	phy->ConfigureStandard(ns3::WifiPhyStandard::WIFI_PHY_STANDARD_80211b);
	return phy;

	//243 phy->SetMobility (node);
	//244 phy->SetDevice (device);

}

ns3::Ptr<ns3::ErrorRateModel> WifiDevice::createErrorRateModel() {
	ns3::ObjectFactory of;
	of.SetTypeId("ns3::NistErrorRateModel");
	auto error_rate_model = of.Create<ns3::ErrorRateModel> ();
	return error_rate_model;
}

ns3::Ptr<ns3::YansWifiChannel> WifiDevice::createChannel() {
	// creating wifi channel helper
	ns3::YansWifiChannelHelper wifi_channel_helper;
	wifi_channel_helper.SetPropagationDelay(
			"ns3::ConstantSpeedPropagationDelayModel");
	wifi_channel_helper.AddPropagationLoss("ns3::FixedRssLossModel", "Rss",
			ns3::DoubleValue(this->rss));

	// wifi phy helper takes wifi channel
	ns3::Ptr<ns3::YansWifiChannel> wifi_channel = wifi_channel_helper.Create();
	return wifi_channel;
}

ns3::Ptr<ns3::WifiMac> WifiDevice::createMac() {
	// creating mac helper
	ns3::NqosWifiMacHelper nqos_wifi_mac_helper =
			ns3::NqosWifiMacHelper::Default();
	//wifi_mac_helper.SetType("ns3::AdhocWifiMac");
	ns3::ObjectFactory of;
	of.SetTypeId(this->wifiMacType);
	of.Set("QosSupported", ns3::BooleanValue(false));
	auto mac = of.Create<ns3::RegularWifiMac> ();
	mac->ConfigureStandard(ns3::WifiPhyStandard::WIFI_PHY_STANDARD_80211b);
	return mac;
}
