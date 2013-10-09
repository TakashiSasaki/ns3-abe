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
#include<time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <string>
NS_LOG_COMPONENT_DEFINE ("WifiMutihopTest");

using namespace ns3;
using namespace std;

class CollisionExperiment {
public:
	struct Input {
		Input();
		int sim_count; //シミュレーションの実行回数
		std::string phyMode;
		double txGain;
		uint32_t packetSize;
		double lambda;
		Address destination_address;
	};
	struct Output {
	};
	CollisionExperiment();

	struct CollisionExperiment::Output Run(
			struct CollisionExperiment::Input input);
private:
	std::ofstream ofs;
	void SendPacket(Ptr<Socket> socket);
	void ReceivePacket(Ptr<Socket> socket);
	void ReceivePacketAtPhy(Ptr<Packet> p, double snr, WifiMode mode,
			enum WifiPreamble preamble);
	double Uniform(void);
	double rand_exp(double lambda);
	static const int nNodes = 4;
	Ptr<Node> m_node[nNodes];
	Ptr<WifiNetDevice> m_wifi_net_device[nNodes];
	Ptr<YansWifiPhy> m_yans_wifi_phy[nNodes];
	Ptr<Socket> m_socket[nNodes];
	Ptr<Ipv4L3Protocol> m_ipv4_l3_protocol[nNodes];
	struct Input m_input;
	struct Output m_output;
};

//一様分布の生成
double CollisionExperiment::Uniform(void) {
	return ((double) rand() + 1.0) / ((double) RAND_MAX + 2.0);
}

//指数分布の生成
double CollisionExperiment::rand_exp(double lambda) {
	return -log(Uniform()) / lambda;
}

void CollisionExperiment::ReceivePacketAtPhy(Ptr<Packet> p, double snr,
		WifiMode mode, enum WifiPreamble preamble) {
	NS_LOG_UNCOND ("receive packet at phy");
}

void CollisionExperiment::ReceivePacket(Ptr<Socket> p_socket) {
	Ptr<Packet> p_packet = p_socket->Recv();
	FlowIdTag tag;
	p_packet->FindFirstMatchingByteTag(tag);
	ofs << Simulator::Now() << " " << p_socket->GetNode()->GetId()
			<< " receive " << tag.GetFlowId() << std::endl;
	//      std::ostringstream oss;
	//      p_packet->CopyData(&oss, p_packet->GetSize());
	//NS_LOG_UNCOND (oss.str());
}

void CollisionExperiment::SendPacket(Ptr<Socket> p_socket) {
	Ptr<Packet> p_packet = Create<Packet> (m_input.packetSize);
	uint32_t flowId = FlowIdTag::AllocateFlowId();
	p_packet->AddByteTag(FlowIdTag(flowId));
	p_socket->SendTo(p_packet, 0, m_input.destination_address);
	ofs << Simulator::Now() << " " << p_socket->GetNode()->GetId() << " send "
			<< flowId << std::endl;
}

//コンストラクタ
CollisionExperiment::CollisionExperiment() {
}

CollisionExperiment::Input::Input() {
	sim_count = 0;
	phyMode = "DsssRate11Mbps";
	txGain = 56;
	packetSize = 500;
	lambda = 0;
	destination_address = InetSocketAddress(Ipv4Address("10.1.1.4"), 0);
}

struct CollisionExperiment::Output CollisionExperiment::Run(
		struct CollisionExperiment::Input input) {
	m_input = input;

	//出力用ファイルの作成
	time_t now = time(NULL);
	struct tm *pnow = localtime(&now);
	char filename[256];
	sprintf(filename, "sim_out_%d_%d_%d%d%d%d%d%d.txt",
			static_cast<int> (m_input.lambda), m_input.sim_count, pnow->tm_year
					+ 1900, pnow->tm_mon + 1, pnow->tm_mday, pnow->tm_hour,
			pnow->tm_min, pnow->tm_sec);
	ofs.open(filename);
	ofs << "     time        node  process   packet   " << std::endl;

	NodeContainer node_container;
	node_container.Create(nNodes);

	for (int i = 0; i < nNodes; ++i) {
		node_container.Get(i)->AggregateObject(CreateObject<
				ConstantPositionMobilityModel> ());
	}

	YansWifiChannelHelper wifiChannel;
	wifiChannel.SetPropagationDelay("ns3::ConstantSpeedPropagationDelayModel");
	wifiChannel.AddPropagationLoss("ns3::LogDistancePropagationLossModel");

	YansWifiPhyHelper wifiPhy = YansWifiPhyHelper::Default();
	wifiPhy.SetChannel(wifiChannel.Create());
	wifiPhy.Set("TxGain", DoubleValue(input.txGain));
	wifiPhy.Set("RxGain", DoubleValue(0));
	wifiPhy.Set("CcaMode1Threshold", DoubleValue(0.0));
	wifiPhy.Set("EnergyDetectionThreshold", DoubleValue(0.0));

	NqosWifiMacHelper wifiMac = NqosWifiMacHelper::Default();
	wifiMac.SetType("ns3::AdhocWifiMac");

	WifiHelper wifi_helper;
	wifi_helper.SetStandard(WIFI_PHY_STANDARD_80211b);
	wifi_helper.SetRemoteStationManager("ns3::ConstantRateWifiManager",
			"DataMode", StringValue(input.phyMode), "ControlMode", StringValue(
					input.phyMode));

	NetDeviceContainer net_device_container;

	for (int n = 0; n < nNodes; n++) {
		//WifiHelper.Install calles WifiMacHelper.Create to create WifiMac instance x.
		//x is configured by WifiMac.ConfigureStandard method.
		//WifiMac.Configure80211b is called for WIFI_PHY_STANDARD_80211b.
		//In Configure80211b, SetSifs, SetSlot, SetEifsNoDifs, SetPifs, SetCtsTimeout
		//and SetAckTimeout are called. SetEifsNoDifs is called with 314 microseconds.
		NetDeviceContainer ndc = wifi_helper.Install(wifiPhy, wifiMac,
				node_container.Get(n));
		net_device_container.Add(ndc);
	}

	MobilityHelper mobility;
	Ptr<ListPositionAllocator> positionAlloc = CreateObject<
			ListPositionAllocator> ();
	double x = 0;
	for (int n = 0; n < nNodes; n++) {
		positionAlloc->Add(Vector(x, 0.0, 0.0));
		x += 5.0;
	}
	mobility.SetPositionAllocator(positionAlloc);
	mobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");
	mobility.Install(node_container);

	Ipv4ListRoutingHelper ipv4_list_routing_helper;
	ipv4_list_routing_helper.Add(Ipv4StaticRoutingHelper(), 0);
	ipv4_list_routing_helper.Add(OlsrHelper(), 10);

	InternetStackHelper internet_stack_helper;
	internet_stack_helper.SetRoutingHelper(ipv4_list_routing_helper);
	internet_stack_helper.Install(node_container);

	Ipv4AddressHelper ipv4_address_helper;
	NS_LOG_INFO ("Assign IP Addresses.");
	ipv4_address_helper.SetBase("10.1.1.0", "255.255.255.0");
	Ipv4InterfaceContainer i = ipv4_address_helper.Assign(net_device_container);

	Ptr<Node> node[nNodes];
	Ptr<WifiNetDevice> wifi_net_device[nNodes];
	Ptr<YansWifiPhy> yans_wifi_phy[nNodes];
	Ptr<Socket> socket[nNodes];
	Ptr<Ipv4L3Protocol> ipv4_l3_protocol[nNodes];

	for (int n = 0; n < nNodes; n++) {
		node[n] = node_container.Get(n);
		ipv4_l3_protocol[n] = node[n]->GetObject<Ipv4L3Protocol> ();
		socket[n] = ipv4_l3_protocol[n]->CreateRawSocket();
		socket[n]->SetRecvCallback(MakeCallback(
				&CollisionExperiment::ReceivePacket, this));
		wifi_net_device[n] = DynamicCast<WifiNetDevice> (
				net_device_container.Get(n));
		yans_wifi_phy[n] = DynamicCast<YansWifiPhy> (
				wifi_net_device[n]->GetPhy());
		//yans_wifi_phy[n]->SetReceiveOkCallback (MakeCallback (&CollisionExperiment::ReceivePacketAtPhy, this));
	}

	//ルーティング情報を交換するためのパケット送信
	Simulator::Schedule(Seconds(32.0), &CollisionExperiment::SendPacket, this,
			socket[0]);
	Simulator::Schedule(Seconds(33.0), &CollisionExperiment::SendPacket, this,
			socket[1]);
	Simulator::Schedule(Seconds(34.0), &CollisionExperiment::SendPacket, this,
			socket[2]);

	//パケットの送信をスケジューリング
	double send_time = 35.0;
	srand((static_cast<unsigned int> (input.sim_count)) + (unsigned) time(NULL)); //並列処理のため、sim_countで乱数を初期化
	for (int n = 0; n < nNodes - 1; n++) {
		do {
			Simulator::Schedule(Seconds(send_time += rand_exp(m_input.lambda)),
					&CollisionExperiment::SendPacket, this, socket[n]);
		} while (send_time < 150.0);
		send_time = 35.0;
	}

	for (int n = 0; n < nNodes; n++) {
		m_node[n] = node[n];
		m_wifi_net_device[n] = wifi_net_device[n];
		m_yans_wifi_phy[n] = yans_wifi_phy[n];
		m_socket[n] = socket[n];
		m_ipv4_l3_protocol[n] = ipv4_l3_protocol[n];
	}
	Simulator::Stop(Seconds(150.0));
	Simulator::Run();
	Simulator::Destroy();
	return m_output;
}

static void Run(int argc, char *argv[]) {
	CollisionExperiment::Input input;

	CommandLine cmd;
	//if no value is parsed, this variable is not modified
	cmd.AddValue("phyMode", "Wifi Phy mode", input.phyMode);
	cmd.AddValue("lambda", "packet arrival rate", input.lambda);
	cmd.AddValue("sim_count", "counter for simulation", input.sim_count);
	cmd.Parse(argc, argv);
	std::cerr << "phyMode = " << input.phyMode << std::endl;
	std::cerr << "lambda = " << input.lambda << std::endl;
	std::cerr << "sim_count= " << input.sim_count << std::endl;

	Config::SetDefault("ns3::WifiRemoteStationManager::NonUnicastMode",
			StringValue(input.phyMode));
	Config::SetDefault("ns3::WifiMacQueue::MaxPacketNumber", UintegerValue(1)); //Mac層のキューの大きさ
	Config::SetDefault("ns3::ConstantSpeedPropagationDelayModel::Speed",
			DoubleValue(5.0 * 1000000.0 / 2.0));
	Config::SetDefault("ns3::WifiRemoteStationManager::MaxSlrc", UintegerValue(
			5)); //csma/caによる再送回数の上限

	CollisionExperiment experiment;
	CollisionExperiment::Output output;
	output = experiment.Run(input);
}

int main(int argc, char *argv[]) {
	Run(argc, argv);
	return 0;
}

