//lambda, sim_countをコマンドライン引数として与える必要あり
#include "ns3/core-module.h"
#include "ns3/network-module.h"
//#include "ns3/mobility-module.h"
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
#include "ConstantMobilityNodeContainer.h"
#include "WifiNodeContainer.h"
NS_LOG_COMPONENT_DEFINE ("WifiMutihopTest");

//using namespace ns3;
//using namespace std;
namespace abe{
class DifsWifiMacTest {
	std::string phyMode;
	//double txGain;
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
	abe::WifiNodeContainer nodeContainer;
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
		ns3::Ipv4InterfaceContainer i = ipv4_address_helper.Assign(this->nodeContainer.getNetDeviceContainer());
	}//initIpv4Interface


	ns3::Ptr<ns3::Ipv4L3Protocol> getIpv4L3Protocol(const int i_node) const {
		return this->nodeContainer.Get(i_node)->GetObject<ns3::Ipv4L3Protocol>();
	}//getIpv4L3Protocol

	ns3::Ptr<ns3::Socket> getIpv4RawSocket(const int i_node) {
		ns3::Ptr<ns3::Socket> ipv4_raw_socket = this->getIpv4L3Protocol(i_node)->CreateRawSocket();
		ipv4_raw_socket->SetRecvCallback(ns3::MakeCallback(&abe::DifsWifiMacTest::receivePacket, this));
		return ipv4_raw_socket;
	}//getIpv4RawSocket

public:
	DifsWifiMacTest(const std::string phyMode = std::string("DsssRate11Mbps"), const double txGain=56, const uint32_t packetSize=500, const double lambda=1, const ns3::Address destinationAddress = ns3::InetSocketAddress(ns3::Ipv4Address("10.1.1.4"), 0), const int sim_count=0, const int nNodes=4):
		phyMode(phyMode), packetSize(packetSize), lambda(lambda), destinationAddress(destinationAddress), outputFileStream(lambda, sim_count)
	{
		srand((static_cast<unsigned int> (sim_count)) + (unsigned) time(NULL)); //並列処理のため、sim_countで乱数を初期化
		//this->nodeContainer.Create(nNodes);
		//this->installWifiPhyCallback();
		this->initIpv4Interface();
	}// a constructor

	void scheduleSendPacket(const ns3::Time& t, const int i_node) {
		ns3::Simulator::Schedule(t, &abe::DifsWifiMacTest::sendPacket, this, this->getIpv4RawSocket(0) );
	}//scheduleSendPacket

	void schedule(){
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
