#define NS3_LOG_ENABLE 1
#include "ns3/log.h"
#include "WifiPhyTraces.h"
NS_LOG_COMPONENT_DEFINE("WifiPhyTraces");

void abe::WifiPhyTraces::install(ns3::Ptr<ns3::WifiPhy> ptr_wifi_phy){
	this->install(*ptr_wifi_phy);
}//install


void abe::WifiPhyTraces::install(ns3::WifiPhy& wifi_phy){
	NS_LOG_FUNCTION(this);
	wifi_phy.TraceConnectWithoutContext("PhyTxBegin",ns3::MakeCallback(&WifiPhyTraces::phyTxBeginTraceCallback, this));
	wifi_phy.TraceConnectWithoutContext("PhyTxEnd",ns3::MakeCallback(&WifiPhyTraces::phyTxEndTraceCallback, this));
	wifi_phy.TraceConnectWithoutContext("PhyTxDrop",ns3::MakeCallback(&WifiPhyTraces::phyTxDropTraceCallback, this));
	wifi_phy.TraceConnectWithoutContext("PhyRxBegin",ns3::MakeCallback(&WifiPhyTraces::phyRxBeginTraceCallback, this));
	wifi_phy.TraceConnectWithoutContext("PhyRxEnd",ns3::MakeCallback(&WifiPhyTraces::phyRxEndTraceCallback, this));
	wifi_phy.TraceConnectWithoutContext("PhyRxDrop",ns3::MakeCallback(&WifiPhyTraces::phyRxDropTraceCallback, this));
	wifi_phy.TraceConnectWithoutContext("MonitorSnifferRx",ns3::MakeCallback(&WifiPhyTraces::monitorSnifferRx, this));
	wifi_phy.TraceConnectWithoutContext("MonitorSnifferTx",ns3::MakeCallback(&WifiPhyTraces::monitorSnifferTx, this));
}//install

void abe::WifiPhyTraces::phyTxBeginTraceCallback(ns3::Ptr<const ns3::Packet> packet){
	NS_LOG_INFO("YansWifiPhy::SendPacket calls YansWifiPhy::NotifyTxBegin.");
	NS_LOG_INFO("YansWifiPhy::SendPacket calls YansWifiChannel::Send.");
}//phyTxBeginTraceCallbak

void abe::WifiPhyTraces::phyTxEndTraceCallback(ns3::Ptr<const ns3::Packet> packet){
	NS_LOG_INFO("YansWifiPhy::NotifyTxEnd is not called from any other Wi-Fi component");
}//phyTxEndTraceCallback

void abe::WifiPhyTraces::phyTxDropTraceCallback(ns3::Ptr<const ns3::Packet> packet){
	NS_LOG_INFO("YansWifiPhy::NotifyTxDrop is not called from any other Wi-Fi component");
}//phyTxDropTraceCallback

void abe::WifiPhyTraces::phyRxBeginTraceCallback(ns3::Ptr<const ns3::Packet> packet){
	NS_LOG_INFO("YansWifiChannel::Receive calls YansWifiPhy::StartReceivePacket.");
	NS_LOG_INFO("YansWifiPhy::StartReceivePacket calls YansWifiPhy::NotifyRxBegin when its state is IDLE.");
}//phyTxBeginTraceCallback

void abe::WifiPhyTraces::phyRxEndTraceCallback(ns3::Ptr<const ns3::Packet> packet){
	NS_LOG_INFO("YansWifiChannel::Receive calls YansWifiPhy::StartReceivePacket.");
	NS_LOG_INFO("YansWifiPhy::StartReceivePacket schedules YansWifiPhy::EndReceivePacket.");
	NS_LOG_INFO("YansWifiPhy::EndReceivePacket calls YansWifiPhy::NotifyRxEnd when SNR is high enough.");
}//phyRxEndTraceCallback

void abe::WifiPhyTraces::phyRxDropTraceCallback(ns3::Ptr<const ns3::Packet> packet){
	NS_LOG_INFO("YansWifiChannel::Receive calls YansWifiPhy::StartReceivePacket");
	NS_LOG_INFO("YansWifiPhy::NotifyRxDrop is called by YansWifiPhy::StartReceivePacket when its state not IDLE.");
	NS_LOG_INFO("YansWifiPhy::NotifyRxDrop is called by YansWifiPhy::EndReceivePacket when SNR is too low.");
}//phyRxDropTraceCallback

void abe::WifiPhyTraces::monitorSnifferRx(ns3::Ptr<const ns3::Packet>, uint16_t, uint16_t, uint32_t, bool, double, double){
	NS_LOG_INFO("YansWifiPhy::EndReceive calls YansWifiPhy::NotifyMnitorSniffRx for PCAP trace");
}//monitorSnifferRx

void abe::WifiPhyTraces::monitorSnifferTx(ns3::Ptr<const ns3::Packet>, uint16_t, uint16_t, uint32_t, bool){
	NS_LOG_INFO("YansWifiPhy::SendPacket calls YansWifiPhy::NotifyMnitorSniffTx for PCAP trace");
}//monitorSnifferTx
