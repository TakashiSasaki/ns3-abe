//lambda, sim_countをコマンドライン引数として与える必要あり
#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/mobility-module.h"
#include "ns3/config-store-module.h"
#include "ns3/wifi-module.h"
#include "ns3/internet-module.h"
#include "ns3/propagation-module.h"
#include "ns3/olsr-helper.h"
#include "ns3/object.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <string>
#include "difs-wifi-mac-helper.h"
#include "OutputFileStream.h"
NS_LOG_COMPONENT_DEFINE ("WifiMutihopTest");

//using namespace ns3;
//using namespace std;
namespace abe{
class DifsWifiMacTest {
	std::string phyMode;
	double txGain;
	uint32_t packetSize;
	double lambda;
	ns3::Address destinationAddress;
	//const int nNodes;
	abe::OutputFileStream outputFileStream;


	//std::ofstream ofs;
	//void SendPacket(ns3::Ptr<ns3::Socket> socket);
	//void ReceivePacket(ns3::Ptr<ns3::Socket> socket);
	//void ReceivePacketAtPhy(ns3::Ptr<ns3::Packet> p, double snr, ns3::WifiMode mode,
	//		enum ns3::WifiPreamble preamble);
	ns3::NodeContainer nodeContainer;
	//Ptr<Node> m_node[nNodes];
	//Ptr<WifiNetDevice> m_wifi_net_device[nNodes];
	//std::vector<ns3::Ptr<ns3::YansWifiPhy>> yans_wifi_phy;
	//Ptr<Socket> m_socket[nNodes];
	//Ptr<Ipv4L3Protocol> m_ipv4_l3_protocol[nNodes];

	double getUniformRandomValue() const {
		return ((double) rand() + 1.0) / ((double) RAND_MAX + 2.0);
	}//getUniformRnadomValue

	double getExponentialRandomValue() const {
		return -log(this->getUniformRandomValue()) / this->lambda;
	}//getExponentialRandomValue

	void receivePacket(ns3::Ptr<ns3::Socket> p_socket) {
		ns3::Ptr<ns3::Packet> p_packet = p_socket->Recv();
		ns3::FlowIdTag tag;
		p_packet->FindFirstMatchingByteTag(tag);
		this->outputFileStream << ns3::Simulator::Now() << " " << p_socket->GetNode()->GetId()
				<< " receive " << tag.GetFlowId() << std::endl;
		//      std::ostringstream oss;
		//      p_packet->CopyData(&oss, p_packet->GetSize());
		//NS_LOG_UNCOND (oss.str());
	}//receivePacket

	void sendPacket(ns3::Ptr<ns3::Socket> p_socket) {
		ns3::Ptr<ns3::Packet> p_packet = ns3::Create<ns3::Packet> (this->packetSize);
		uint32_t flowId = ns3::FlowIdTag::AllocateFlowId();
		p_packet->AddByteTag(ns3::FlowIdTag(flowId));
		p_socket->SendTo(p_packet, 0, this->destinationAddress);
		this->outputFileStream << ns3::Simulator::Now() << " " << p_socket->GetNode()->GetId() << " send "
				<< flowId << std::endl;
	}//sendPacket

	void initMobility(){
		for (int i = 0; i < this->nodeContainer.GetN(); ++i) {
			this->nodeContainer.Get(i)->AggregateObject(ns3::CreateObject<ns3::ConstantPositionMobilityModel> ());
		}//for
		ns3::MobilityHelper mobility_helper;
		ns3::Ptr<ns3::ListPositionAllocator> positionAlloc = ns3::CreateObject<ns3::ListPositionAllocator> ();
		double x = 0;
		for (int n = 0; n < this->nodeContainer.GetN(); n++) {
			positionAlloc->Add(ns3::Vector(x, 0.0, 0.0));
			x += 5.0;
		}//for
		mobility_helper.SetPositionAllocator(positionAlloc);
		mobility_helper.SetMobilityModel("ns3::ConstantPositionMobilityModel");
		mobility_helper.Install(this->nodeContainer);
	}//initMobility


	ns3::YansWifiChannelHelper yansWifiChannelHelper;
	void initYansWifiChannelHelper(){
		this->yansWifiChannelHelper.SetPropagationDelay("ns3::ConstantSpeedPropagationDelayModel");
		this->yansWifiChannelHelper.AddPropagationLoss("ns3::LogDistancePropagationLossModel");
	}//initYansWifiChannelHelper

	ns3::YansWifiPhyHelper yansWifiPhyHelper;
	void initYansWifiPhyHelper(){
		this->yansWifiPhyHelper = ns3::YansWifiPhyHelper::Default();
		this->yansWifiPhyHelper.SetChannel(this->yansWifiChannelHelper.Create());
		this->yansWifiPhyHelper.Set("TxGain", ns3::DoubleValue(this->txGain));
		this->yansWifiPhyHelper.Set("RxGain", ns3::DoubleValue(0));
		this->yansWifiPhyHelper.Set("CcaMode1Threshold", ns3::DoubleValue(0.0));
		this->yansWifiPhyHelper.Set("EnergyDetectionThreshold", ns3::DoubleValue(0.0));
	}//initYansWifiPhyHelper

	abe::DifsWifiMacHelper difsWifiMacHelper;
	void initDifsWifiMacHelper(){
		//NqosWifiMacHelper wifiMac = NqosWifiMacHelper::Default();
		//abe::DifsWifiMacHelper wifiMac(2,31,1023);
		this->difsWifiMacHelper = abe::DifsWifiMacHelper::Default();
		//wifiMac.SetType("ns3::AdhocWifiMac");
	}//initDifsWifiMacHelper

	ns3::WifiHelper wifiHelper;
	void initWifiHelper(){
		this->wifiHelper.SetStandard(ns3::WIFI_PHY_STANDARD_80211b);
		this->wifiHelper.SetRemoteStationManager("ns3::ConstantRateWifiManager",
				"DataMode", ns3::StringValue(this->phyMode), "ControlMode", ns3::StringValue(
						phyMode));
	}//initWifiHelper

	ns3::NetDeviceContainer netDeviceContainer;
	void installWifi(){
		for(int i=0; i<this->nodeContainer.GetN();++i){
			//WifiHelper.Install calles WifiMacHelper.Create to create WifiMac instance x.
			//x is configured by WifiMac.ConfigureStandard method.
			//WifiMac.Configure80211b is called for WIFI_PHY_STANDARD_80211b.
			//In Configure80211b, SetSifs, SetSlot, SetEifsNoDifs, SetPifs, SetCtsTimeout
			//and SetAckTimeout are called. SetEifsNoDifs is called with 314 microseconds.

			ns3::NetDeviceContainer ndc = this->wifiHelper.Install(this->yansWifiPhyHelper, this->difsWifiMacHelper,
					this->nodeContainer.Get(i));
			this->netDeviceContainer.Add(ndc);
		}//for
	}//installWifi

	ns3::Ipv4InterfaceContainer ipv4InterfaceContainer;
	void initIpv4Interface(){
		ns3::Ipv4ListRoutingHelper ipv4_list_routing_helper;
		ipv4_list_routing_helper.Add(ns3::Ipv4StaticRoutingHelper(), 0);
		ipv4_list_routing_helper.Add(ns3::OlsrHelper(), 10);

		ns3::InternetStackHelper internet_stack_helper;
		internet_stack_helper.SetRoutingHelper(ipv4_list_routing_helper);
		internet_stack_helper.Install(this->nodeContainer);

		ns3::Ipv4AddressHelper ipv4_address_helper;
		NS_LOG_INFO ("Assign IP Addresses.");
		ipv4_address_helper.SetBase("10.1.1.0", "255.255.255.0");
		ns3::Ipv4InterfaceContainer i = ipv4_address_helper.Assign(this->netDeviceContainer);
	}//initIpv4Interface


	ns3::Ptr<ns3::Ipv4L3Protocol> getIpv4L3Protocol(const int i_node) const {
		return this->nodeContainer.Get(i_node)->GetObject<ns3::Ipv4L3Protocol>();
	}//getIpv4L3Protocol

	ns3::Ptr<ns3::Socket> getIpv4RawSocket(const int i_node) {
		ns3::Ptr<ns3::Socket> ipv4_raw_socket = this->getIpv4L3Protocol(i_node)->CreateRawSocket();
		ipv4_raw_socket->SetRecvCallback(ns3::MakeCallback(&abe::DifsWifiMacTest::receivePacket, this));
		return ipv4_raw_socket;
	}//getIpv4RawSocket

	ns3::Ptr<ns3::WifiNetDevice> getWifiNetDevice(const int i_node) const {
		return ns3::DynamicCast<ns3::WifiNetDevice> (this->netDeviceContainer.Get(i_node));
	}//getWifiNetDevice

	ns3::Ptr<ns3::YansWifiPhy> getYansWifiPhy(const int i_node) const {
		return ns3::DynamicCast<ns3::YansWifiPhy> (this->getWifiNetDevice(i_node)->GetPhy());
	}//getYansWifiPhy

	void installWifiPhyCallback(){
		for(int i=0; i<this->nodeContainer.GetN(); ++i){
			this->getYansWifiPhy(i)->SetReceiveOkCallback (ns3::MakeCallback (&abe::DifsWifiMacTest::receivePacketAtPhy, this));
		}//for
	}//installWifiPhyCallback

	void receivePacketAtPhy(ns3::Ptr<ns3::Packet> ptr_packet, double snr, ns3::WifiMode wifi_mode, enum ns3::WifiPreamble wifi_preamble) {
		NS_LOG_UNCOND ("receive packet at phy");
	}//receivePacketAtPhy

public:
	DifsWifiMacTest(const std::string phyMode = std::string("DsssRate11Mbps"), const double txGain=56, const uint32_t packetSize=500, const double lambda=1, const ns3::Address destinationAddress = ns3::InetSocketAddress(ns3::Ipv4Address("10.1.1.4"), 0), const int sim_count=0, const int nNodes=4):
		phyMode(phyMode), txGain(txGain), packetSize(packetSize), lambda(lambda), destinationAddress(destinationAddress), outputFileStream(lambda, sim_count)
	{
		srand((static_cast<unsigned int> (sim_count)) + (unsigned) time(NULL)); //並列処理のため、sim_countで乱数を初期化
		DifsWifiMacTest::setDefault();
		this->nodeContainer.Create(nNodes);
		this->initYansWifiChannelHelper();
		this->initYansWifiPhyHelper();
		this->initDifsWifiMacHelper();
		this->initWifiHelper();
		this->installWifi();
		this->installWifiPhyCallback();
		this->initIpv4Interface();
		this->initMobility();
	}// a constructor

	void scheduleSendPacket(const ns3::Time& t, const int i_node) {
		ns3::Simulator::Schedule(t, &abe::DifsWifiMacTest::sendPacket, this, this->getIpv4RawSocket(0) );
	}//scheduleSendPacket

	void schedule(){
		DifsWifiMacTest::setDefault();
		//ルーティング情報を交換するためのパケット送信
		this->scheduleSendPacket(ns3::Seconds(32.0), 0);
		this->scheduleSendPacket(ns3::Seconds(33.0), 1);
		this->scheduleSendPacket(ns3::Seconds(34.0), 2);

		//パケットの送信をスケジューリング
		double send_time = 35.0;
		for (int n = 0; n < this->nodeContainer.GetN() - 1; n++) {
			do {
				this->scheduleSendPacket(ns3::Seconds(send_time += this->getExponentialRandomValue() ), n);
			} while (send_time < 150.0);
			send_time = 35.0;
		}//for
	}//run

	void setDefault(){
		ns3::Config::SetDefault("ns3::WifiRemoteStationManager::NonUnicastMode",
				ns3::StringValue(this->phyMode));
		ns3::Config::SetDefault("ns3::WifiMacQueue::MaxPacketNumber", ns3::UintegerValue(1)); //Mac層のキューの大きさ
		ns3::Config::SetDefault("ns3::ConstantSpeedPropagationDelayModel::Speed",
				ns3::DoubleValue(5.0 * 1000000.0 / 2.0));
		ns3::Config::SetDefault("ns3::WifiRemoteStationManager::MaxSlrc", ns3::UintegerValue(
				5)); //csma/caによる再送回数の上限
	}//setDefault
};//DifsWifiMacTest


}
int main(int argc, char *argv[]) {
	ns3::CommandLine cmd;
	//if no value is parsed, this variable is not modified
	//cmd.AddValue("phyMode", "Wifi Phy mode", input.phyMode);
	//cmd.AddValue("lambda", "packet arrival rate", input.lambda);
	//cmd.AddValue("sim_count", "counter for simulation", input.sim_count);
	//cmd.Parse(argc, argv);
	//std::cerr << "phyMode = " << input.phyMode << std::endl;
	//std::cerr << "lambda = " << input.lambda << std::endl;
	//std::cerr << "sim_count= " << input.sim_count << std::endl;


	abe::DifsWifiMacTest difs_wifi_mac_test;
	difs_wifi_mac_test.schedule();

	ns3::Simulator::Stop(ns3::Seconds(150.0));
	ns3::Simulator::Run();
	ns3::Simulator::Destroy();
	return EXIT_SUCCESS;
}//main
