#include <cassert>
#include "ns3/core-module.h"
#include "ns3/wifi-helper.h"
#include "ns3/wifi-net-device.h"
#include "ns3/yans-wifi-phy.h"
#include "ns3/string.h"
#include "WifiNodeContainer.h"

abe::WifiNodeContainer::WifiNodeContainer(const uint32_t n_nodes,
		const double txGain) :
	ConstantMobilityNodeContainer(n_nodes), txGain(txGain) {
	ns3::Config::SetDefault("ns3::WifiRemoteStationManager::NonUnicastMode",
			ns3::StringValue(std::string("DsssRate11Mbps")));
	ns3::WifiHelper wifiHelper;
	wifiHelper.SetStandard(ns3::WIFI_PHY_STANDARD_80211b);
	wifiHelper.SetRemoteStationManager("ns3::ConstantRateWifiManager",
			"DataMode", ns3::StringValue(std::string("DsssRate11Mbps")),
			"ControlMode", ns3::StringValue(std::string("DsssRate11Mbps")));
	for (uint32_t i = 0; i < this->GetN(); ++i) {
		//WifiHelper.Install calles WifiMacHelper.Create to create WifiMac instance x.
		//x is configured by WifiMac.ConfigureStandard method.
		//WifiMac.Configure80211b is called for WIFI_PHY_STANDARD_80211b.
		//In Configure80211b, SetSifs, SetSlot, SetEifsNoDifs, SetPifs, SetCtsTimeout
		//and SetAckTimeout are called. SetEifsNoDifs is called with 314 microseconds.

		ns3::NetDeviceContainer ndc = wifiHelper.Install(
				this->getYansWifiPhyHelper(), this->getDifsWifiMacHelper(),
				this->Get(i));
		assert(ndc.GetN() == 1);
		assert(this->Get(i)->GetNDevices() == 1);
		this->getYansWifiPhy(i)->SetReceiveOkCallback(ns3::MakeCallback(
				&abe::WifiNodeContainer::receiveOkCallback, this));
		this->getYansWifiPhy(i)->SetReceiveErrorCallback(ns3::MakeCallback(
				&abe::WifiNodeContainer::receiveErrorCallback, this));
	}//for
}// a constructor

void abe::WifiNodeContainer::receiveOkCallback(
		ns3::Ptr<ns3::Packet> ptr_packet, double snr, ns3::WifiMode wifi_mode,
		enum ns3::WifiPreamble wifi_preamble) {
	NS_LOG_UNCOND ("receiveOkCallback");
}//receivePacketAtPhy

void abe::WifiNodeContainer::receiveErrorCallback(
		ns3::Ptr<const ns3::Packet> ptr_packet, double snr) {
	NS_LOG_UNCOND ("receiveErrorCallback");
}//receivePacketAtPhy

abe::WifiNodeContainer::~WifiNodeContainer() {
	// TODO !CodeTemplates.destructorstub.tododesc!
}// the destructor

ns3::YansWifiChannelHelper& abe::WifiNodeContainer::getYansWifiChannelHelper() {
	ns3::Config::SetDefault("ns3::ConstantSpeedPropagationDelayModel::Speed",
			ns3::DoubleValue(5.0 * 1000000.0 / 2.0));
	static ns3::YansWifiChannelHelper yansWifiChannelHelper =
			ns3::YansWifiChannelHelper::Default();
	yansWifiChannelHelper.SetPropagationDelay(
			"ns3::ConstantSpeedPropagationDelayModel");
	yansWifiChannelHelper.AddPropagationLoss(
			"ns3::LogDistancePropagationLossModel");
	return yansWifiChannelHelper;
}//initYansWifiChannelHelper

ns3::YansWifiPhyHelper& abe::WifiNodeContainer::getYansWifiPhyHelper() {
	static ns3::YansWifiPhyHelper yansWifiPhyHelper;
	yansWifiPhyHelper = ns3::YansWifiPhyHelper::Default();
	yansWifiPhyHelper.SetChannel(this->getYansWifiChannelHelper().Create());
	yansWifiPhyHelper.Set("TxGain", ns3::DoubleValue(this->txGain));
	yansWifiPhyHelper.Set("RxGain", ns3::DoubleValue(0));
	yansWifiPhyHelper.Set("CcaMode1Threshold", ns3::DoubleValue(0.0));
	yansWifiPhyHelper.Set("EnergyDetectionThreshold", ns3::DoubleValue(0.0));
	return yansWifiPhyHelper;
}//initYansWifiPhyHelper

abe::DifsWifiMacHelper& abe::WifiNodeContainer::getDifsWifiMacHelper() {
	ns3::Config::SetDefault("ns3::WifiMacQueue::MaxPacketNumber",
			ns3::UintegerValue(1)); //Mac層のキューの大きさ
	ns3::Config::SetDefault("ns3::WifiRemoteStationManager::MaxSlrc",
			ns3::UintegerValue(5)); //csma/caによる再送回数の上限
	static abe::DifsWifiMacHelper difsWifiMacHelper;
	//NqosWifiMacHelper wifiMac = NqosWifiMacHelper::Default();
	//abe::DifsWifiMacHelper wifiMac(2,31,1023);
	difsWifiMacHelper = abe::DifsWifiMacHelper::Default();
	//wifiMac.SetType("ns3::AdhocWifiMac");
	return difsWifiMacHelper;
}//initDifsWifiMacHelper


ns3::Ptr<ns3::YansWifiPhy> abe::WifiNodeContainer::getYansWifiPhy(
		const int i_node) {
	ns3::Ptr<ns3::WifiPhy> ptr_wifi_phy =
			this->getWifiNetDevice(i_node)->GetPhy();
	return ns3::DynamicCast<ns3::YansWifiPhy>(ptr_wifi_phy);
}//getYansWifiPhy

ns3::Ptr<ns3::WifiNetDevice> abe::WifiNodeContainer::getWifiNetDevice(
		const int i_node) {
	return ns3::DynamicCast<ns3::WifiNetDevice>(this->getNetDevice(i_node));
}//getWifiNetDevice
