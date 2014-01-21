#define NS3_LOG_ENABLE 1
#include "ns3/log.h"
NS_LOG_COMPONENT_DEFINE("EunetMobile");
#define NS3_ASSERT_ENABLE 1
#include "ns3/assert.h"
#include "ns3/wifi-helper.h"
#include "ns3/nqos-wifi-mac-helper.h"
#include "ns3/yans-wifi-helper.h"
#include "ns3/ssid.h"
#include "ns3/wifi-net-device.h"
#include "ns3/mobility-helper.h"
#include "ns3/config.h"
#include "ns3/string.h"
#include "ns3/double.h"
#include "EunetMobile.h"
NS_OBJECT_ENSURE_REGISTERED(EunetMobile);

ns3::TypeId EunetMobile::GetTypeId(void) {
	static ns3::TypeId
			type_id =
					ns3::TypeId("EunetMobile").SetParent<OnOffNode> ().AddConstructor<
							EunetMobile> ().AddAttribute("phyMode", "phyMode",
							ns3::StringValue("DsssRate1Mbps"),
							ns3::MakeStringAccessor(&EunetMobile::phyMode),
							ns3::MakeStringChecker()).AddAttribute("rss",
							"rss", ns3::DoubleValue(-80.0),
							ns3::MakeDoubleAccessor(&EunetMobile::rss),
							ns3::MakeDoubleChecker<double>()) .AddAttribute(
							"position", "position", ns3::VectorValue(
									ns3::Vector(0.0, 0.0, 0.0)),
							ns3::MakeVectorAccessor(&EunetMobile::position),
							ns3::MakeVectorChecker());
	return type_id;
}//GetTypeId

EunetMobile::EunetMobile() :
	/*TraceBase(this), MobilityBase(this, ns3::Vector(0, 0, 0)), WifiBase(this,
	 WifiBase::StaWifiMac, true),*/INIT_DIDDNCC_FLAGS {
}// the default constructor

EunetMobile::~EunetMobile() {
}

void EunetMobile::DoInitialize() {
	ASSERT_DI
	OnOffNode::DoInitialize();
	//MobilityBase::DoInitialize();
	//WifiBase::DoInitialize();

	// enable rts cts all the time
	ns3::Config::SetDefault("ns3::WifiRemoteStationManager::RtsCtsThreshold",
			ns3::StringValue("2200"));
	// disable fragmentation
	ns3::Config::SetDefault(
			"ns3::WifiRemoteStationManager::FragmentationThreshold",
			ns3::StringValue("2200"));
	// fix non-unicast data rate to be the same as that of unicast
	ns3::Config::SetDefault("ns3::WifiRemoteStationManager::NonUnicastMode",
			ns3::StringValue(phyMode));

	// creating wifi helper
	ns3::WifiHelper wifi_helper;
	wifi_helper.SetStandard(ns3::WifiPhyStandard::WIFI_PHY_STANDARD_80211b);
	// ConstantRateWifiManager is a derived class of WifiRemoteStationManager.
	// Other options are AarfWifiManager, AmrrWifiManager, ArfWifiManager, RraaWifiManage, etc.
	wifi_helper.SetRemoteStationManager("ns3::ConstantRateWifiManager",
			"DataMode", ns3::StringValue(phyMode), "ControlMode",
			ns3::StringValue(phyMode));

	// creating wifi phy helper
	ns3::YansWifiPhyHelper wifi_phy_helper = ns3::YansWifiPhyHelper::Default();
	wifi_phy_helper.Set("RxGain", ns3::DoubleValue(0.0));
	wifi_phy_helper.SetPcapDataLinkType(
			ns3::YansWifiPhyHelper::DLT_IEEE802_11_RADIO);

	// creating wifi channel helper
	ns3::YansWifiChannelHelper wifi_channel_helper;
	wifi_channel_helper.SetPropagationDelay(
			"ns3::ConstantSpeedPropagationDelayModel");
	wifi_channel_helper.AddPropagationLoss("ns3::FixedRssLossModel", "Rss",
			ns3::DoubleValue(this->rss));

	// wifi phy helper takes wifi channel
	ns3::Ptr<ns3::YansWifiChannel> wifi_channel = wifi_channel_helper.Create();
	wifi_phy_helper.SetChannel(wifi_channel);

	// creating mac helper
	ns3::NqosWifiMacHelper wifi_mac_helper = ns3::NqosWifiMacHelper::Default();
	wifi_mac_helper.SetType("ns3::AdhocWifiMac");

	// installing wifi
	wifi_helper.Install(wifi_phy_helper, wifi_mac_helper, ns3::NodeContainer(
			ns3::Ptr<ns3::Node>(this, true)));

	// mobility
	ns3::MobilityHelper mobility_helper;
	auto positions = ns3::CreateObject<ns3::ListPositionAllocator>();
	positions->Add(position);
	mobility_helper.SetPositionAllocator(positions);
	mobility_helper.SetMobilityModel("ns3::ConstantPositionMobilityModel");
	mobility_helper.Install(ns3::NodeContainer(ns3::Ptr<ns3::Node>(this, true)));

}//DoInitialize

void EunetMobile::NotifyConstructionCompleted() {
	ASSERT_NCC
	for (unsigned i = 0; i < this->GetNDevices(); ++i) {
		NS_LOG_INFO(this->GetDevice(i)->GetTypeId().GetName());
	}//for
	NS_ASSERT(this->GetNDevices() == 2);
	OnOffNode::NotifyConstructionCompleted();
	NS_ASSERT(this->GetNDevices() == 3);
	//MobilityBase::NotifyConstructionCompleted();
	//WifiBase::NotifyConstructionCompleted();
}//NotifyConstructionCompleted

void EunetMobile::DoDispose() {
	ASSERT_DD;
	OnOffNode::DoDispose();
	//MobilityBase::DoDispose();
	//WifiBase::DoDispose();
}
