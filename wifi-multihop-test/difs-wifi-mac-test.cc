//lambda, sim_countをコマンドライン引数として与える必要あり
#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/config-store-module.h"
#include "ns3/log.h"
NS_LOG_COMPONENT_DEFINE ("DifsWifiMacTest");
//#include "ns3/internet-module.h"
//#include "ns3/object.h"
#include <iostream>
//#include <fstream>
//#include <vector>
#include <string>
#include <math.h>
#include <ctime>
//#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <string>
#include <cassert>
#include "difs-wifi-mac-helper.h"
#include "OutputFileStream.h"
#include "ConstantMobilityNodeContainer.h"
#include "Ipv4NodeContainer.h"

namespace abe {
class DifsWifiMacTest {
	const double lambda;
	ns3::Address destinationAddress;
	abe::OutputFileStream outputFileStream;
	abe::Ipv4NodeContainer nodeContainer;

	double getUniformRandomValue() const {
		return ((double) rand() + 1.0) / ((double) RAND_MAX + 2.0);
	}//getUniformRnadomValue

	double getExponentialRandomValue() const {
		return -log(this->getUniformRandomValue()) / this->lambda;
	}//getExponentialRandomValue


public:
	DifsWifiMacTest(const int n_nodes = 4, const double lambda = 1,
			const int sim_count = 1, const ns3::Address destinationAddress =
					ns3::InetSocketAddress(ns3::Ipv4Address("10.1.1.4"), 0)) :
		lambda(lambda), destinationAddress(destinationAddress),
				outputFileStream(lambda, sim_count), nodeContainer(n_nodes) {
		NS_LOG_UNCOND("DifsWifiMacTest::DifsWifiMacTest");
		srand((static_cast<unsigned int> (sim_count)) + (unsigned) time(NULL)); //並列処理のため、sim_countで乱数を初期化

		this->nodeContainer.scheduleSendPacket(ns3::Seconds(32.0), 0, 3);
		this->nodeContainer.scheduleSendPacket(ns3::Seconds(33.0), 1, 3);
		this->nodeContainer.scheduleSendPacket(ns3::Seconds(34.0), 2, 3);

		//パケットの送信をスケジューリング
		for (int n = 0; n < n_nodes - 1; n++) {
			this->nodeContainer.scheduleSendPacket(ns3::Seconds(35.0
					+ this->getExponentialRandomValue()), n, n_nodes - 1);
		}//for
		ns3::Simulator::Stop(ns3::Seconds(150.0));
	}// a constructor
};//DifsWifiMacTest


}
int main(int argc, char *argv[]) {
	ns3::LogComponentEnableAll(ns3::LOG_LEVEL_ALL);
	NS_LOG_INFO("main");
	return EXIT_SUCCESS;
	//if no value is parsed, this variable is not modified
	//cmd.AddValue("phyMode", "Wifi Phy mode", input.phyMode);
	int n_nodes = 4;
	double lambda = 1.0;
	int sim_count = 1;
	ns3::CommandLine cmd;
	cmd.AddValue("n_nodes", "number of nodes", n_nodes);
	cmd.AddValue("lambda", "packet arrival rate", lambda);
	cmd.AddValue("sim_count", "counter for simulation", sim_count);
	cmd.Parse(argc, argv);
	//std::cerr << "phyMode = " << input.phyMode << std::endl;
	//std::cerr << "lambda = " << input.lambda << std::endl;
	//std::cerr << "sim_count= " << input.sim_count << std::endl;


	abe::DifsWifiMacTest difs_wifi_mac_test(n_nodes, lambda, sim_count);

	ns3::Simulator::Run();
	ns3::Simulator::Destroy();
	return EXIT_SUCCESS;
}//main