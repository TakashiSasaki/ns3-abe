#define NS3_LOG_ENABLE 1
#include "ns3/log.h"
#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/applications-module.h"
#include "ns3/bridge-module.h"
#include "ns3/csma-module.h"
#include "ns3/internet-module.h"
#include "ns3/internet-stack-helper.h"
#include "ns3/netanim-module.h"
#include "EunetSimulation.h"
#include "EunetSwitches.h"
#include "EunetTerminal.h"
#include "NamedSwitches.h"
NS_LOG_COMPONENT_DEFINE ("EunetSimulation");

EunetSimulation::EunetSimulation() {
	ns3::AnimationInterface animation_interface("EunetSimulation.xml");
	NamedSwitches named_switches("133.71.0.0", "255.255.0.0");
	named_switches.addEunetSwitch("キャンパス間接続L2", 64);

	//城北キャンパスネットワーク
	/*
	 named_switches.addEunetSwitch("dpc_02_core01", 64);
	 named_switches.findEunetSwitch("dpc_02_core01")->setUplinkDataRate(
	 ns3::DataRate("10Gbps"));
	 named_switches.findEunetSwitch("dpc_02_core01")->connectUpTo("キャンパス間接続L2");

	 named_switches.addEunetSwitch("dpc_02_01_sw01", 64);
	 named_switches.findEunetSwitch("dpc_02_01_sw01")->setUplinkDataRate(
	 ns3::DataRate("10Gbps"));
	 named_switches.findEunetSwitch("dpc_02_01_sw01")->connectUpTo("キャンパス間接続L2");

	 named_switches.addEunetSwitch("dpc_02_01_sw02", 64);
	 named_switches.findEunetSwitch("dpc_02_01_sw02")->setUplinkDataRate(
	 ns3::DataRate("10Gbps"));
	 named_switches.findEunetSwitch("dpc_02_01_sw02")->connectUpTo("キャンパス間接続L2");

	 named_switches.addEunetSwitch("dpc_02_01_sw03", 64);
	 named_switches.findEunetSwitch("dpc_02_01_sw03")->setUplinkDataRate(
	 ns3::DataRate("10Gbps"));
	 named_switches.findEunetSwitch("dpc_02_01_sw03")->connectUpTo("キャンパス間接続L2");

	 named_switches.addEunetSwitch("dpc_04_1_sw01", 48);
	 named_switches.findEunetSwitch("dpc_04_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("10Gbps"));
	 named_switches.findEunetSwitch("dpc_04_1_sw01")->connectUpTo(
	 "dpc_02_01_sw02");

	 named_switches.addEunetSwitch("dpc_04_1_sw02", 24);
	 named_switches.findEunetSwitch("dpc_04_1_sw02")->setUplinkDataRate(
	 ns3::DataRate("10Gbps"));
	 named_switches.findEunetSwitch("dpc_04_1_sw02")->connectUpTo(
	 "dpc_02_01_sw02");

	 named_switches.addEunetSwitch("dpc_04_2_sw01", 48);
	 named_switches.findEunetSwitch("dpc_04_2_sw01")->setUplinkDataRate(
	 ns3::DataRate("10Gbps"));
	 named_switches.findEunetSwitch("dpc_04_2_sw01")->connectUpTo(
	 "dpc_02_01_sw02");

	 named_switches.addEunetSwitch("dpc_04_2_sw02", 24);
	 named_switches.findEunetSwitch("dpc_04_2_sw02")->setUplinkDataRate(
	 ns3::DataRate("10Gbps"));
	 named_switches.findEunetSwitch("dpc_04_2_sw02")->connectUpTo(
	 "dpc_02_01_sw02");

	 named_switches.addEunetSwitch("dpc_04_3_sw01", 24);
	 named_switches.findEunetSwitch("dpc_04_3_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("dpc_04_3_sw01")->connectUpTo(
	 "dpc_02_core01");

	 named_switches.addEunetSwitch("dpc_03_1_sw01", 48);
	 named_switches.findEunetSwitch("dpc_03_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("10Gbps"));
	 named_switches.findEunetSwitch("dpc_03_1_sw01")->connectUpTo(
	 "dpc_02_01_sw02");

	 named_switches.addEunetSwitch("dpc_03_1_sw02", 24);
	 named_switches.findEunetSwitch("dpc_03_1_sw02")->setUplinkDataRate(
	 ns3::DataRate("10Gbps"));
	 named_switches.findEunetSwitch("dpc_03_1_sw02")->connectUpTo(
	 "dpc_02_01_sw02");

	 named_switches.addEunetSwitch("dpc_03_2_sw01", 48);
	 named_switches.findEunetSwitch("dpc_03_2_sw01")->setUplinkDataRate(
	 ns3::DataRate("10Gbps"));
	 named_switches.findEunetSwitch("dpc_03_2_sw01")->connectUpTo(
	 "dpc_02_01_sw02");

	 named_switches.addEunetSwitch("dpc_03_2_sw02", 48);
	 named_switches.findEunetSwitch("dpc_03_2_sw02")->setUplinkDataRate(
	 ns3::DataRate("10Gbps"));
	 named_switches.findEunetSwitch("dpc_03_2_sw02")->connectUpTo(
	 "dpc_02_01_sw02");

	 named_switches.addEunetSwitch("dpc_02_2_sw01", 48);
	 named_switches.findEunetSwitch("dpc_02_2_sw01")->setUplinkDataRate(
	 ns3::DataRate("10Gbps"));
	 named_switches.findEunetSwitch("dpc_02_2_sw01")->connectUpTo(
	 "dpc_02_01_sw02");

	 named_switches.addEunetSwitch("dpc_02_2_sw02", 24);
	 named_switches.findEunetSwitch("dpc_02_2_sw02")->setUplinkDataRate(
	 ns3::DataRate("10Gbps"));
	 named_switches.findEunetSwitch("dpc_02_2_sw02")->connectUpTo(
	 "dpc_02_01_sw02");

	 named_switches.addEunetSwitch("dpc_02_3_sw01", 48);
	 named_switches.findEunetSwitch("dpc_02_3_sw01")->setUplinkDataRate(
	 ns3::DataRate("10Gbps"));
	 named_switches.findEunetSwitch("dpc_02_3_sw01")->connectUpTo(
	 "dpc_02_01_sw02");

	 named_switches.addEunetSwitch("dpc_02_3_sw02", 24);
	 named_switches.findEunetSwitch("dpc_02_3_sw02")->setUplinkDataRate(
	 ns3::DataRate("10Gbps"));
	 named_switches.findEunetSwitch("dpc_02_3_sw02")->connectUpTo(
	 "dpc_02_01_sw02");

	 named_switches.addEunetSwitch("dpc_02_4_sw01", 48);
	 named_switches.findEunetSwitch("dpc_02_4_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("dpc_02_4_sw01")->connectUpTo(
	 "dpc_02_core01");

	 named_switches.addEunetSwitch("dpc_02_4_sw02", 24);
	 named_switches.findEunetSwitch("dpc_02_4_sw02")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("dpc_02_4_sw02")->connectUpTo(
	 "dpc_02_4_sw01");

	 named_switches.addEunetSwitch("dpc_01_2_sw01", 48);
	 named_switches.findEunetSwitch("dpc_01_2_sw01")->setUplinkDataRate(
	 ns3::DataRate("10Gbps"));
	 named_switches.findEunetSwitch("dpc_01_2_sw01")->connectUpTo(
	 "dpc_02_01_sw02");

	 named_switches.addEunetSwitch("dpc_01_1_sw01", 48);
	 named_switches.findEunetSwitch("dpc_01_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("10Gbps"));
	 named_switches.findEunetSwitch("dpc_01_1_sw01")->connectUpTo(
	 "dpc_02_core01");

	 named_switches.addEunetSwitch("dpc_01_1_sw02", 48);
	 named_switches.findEunetSwitch("dpc_01_1_sw02")->setUplinkDataRate(
	 ns3::DataRate("10Gbps"));
	 named_switches.findEunetSwitch("dpc_01_1_sw02")->connectUpTo(
	 "dpc_01_1_sw01");

	 named_switches.addEunetSwitch("dpc_01_3_sw01", 24);
	 named_switches.findEunetSwitch("dpc_01_3_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("dpc_01_3_sw01")->connectUpTo(
	 "dpc_02_4_sw01");

	 named_switches.addEunetSwitch("dpc_01_4_sw01", 24);
	 named_switches.findEunetSwitch("dpc_01_4_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("dpc_01_4_sw01")->connectUpTo(
	 "dpc_02_core01");

	 named_switches.addEunetSwitch("en1_01_1_sw01", 24);
	 named_switches.findEunetSwitch("en1_01_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("10Gbps"));
	 named_switches.findEunetSwitch("en1_01_1_sw01")->connectUpTo(
	 "dpc_02_core01");

	 named_switches.addEunetSwitch("en1_02_1_sw01", 48);
	 named_switches.findEunetSwitch("en1_02_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("en1_02_1_sw01")->connectUpTo(
	 "en1_01_1_sw01");

	 named_switches.addEunetSwitch("en1_04_1_sw01", 48);
	 named_switches.findEunetSwitch("en1_04_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("en1_04_1_sw01")->connectUpTo(
	 "en1_01_1_sw01");

	 named_switches.addEunetSwitch("en1_06_1_sw01", 48);
	 named_switches.findEunetSwitch("en1_06_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("en1_06_1_sw01")->connectUpTo(
	 "en1_01_1_sw01");

	 named_switches.addEunetSwitch("enh_02_1_sw01", 24);
	 named_switches.findEunetSwitch("enh_02_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("10Gbps"));
	 named_switches.findEunetSwitch("enh_02_1_sw01")->connectUpTo(
	 "dpc_02_core01");

	 named_switches.addEunetSwitch("enh_02_1_sw02", 24);
	 named_switches.findEunetSwitch("enh_02_1_sw02")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("enh_02_1_sw02")->connectUpTo(
	 "enh_02_1_sw01");

	 named_switches.addEunetSwitch("enh_02_1_sw03", 24);
	 named_switches.findEunetSwitch("enh_02_1_sw03")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("enh_02_1_sw03")->connectUpTo(
	 "enh_02_1_sw01");

	 named_switches.addEunetSwitch("enh_01_1_sw01", 24);
	 named_switches.findEunetSwitch("enh_01_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("enh_01_1_sw01")->connectUpTo(
	 "enh_02_1_sw01");

	 named_switches.addEunetSwitch("enh_08_1_sw01", 48);
	 named_switches.findEunetSwitch("enh_08_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("enh_08_1_sw01")->connectUpTo(
	 "enh_02_1_sw01");

	 named_switches.addEunetSwitch("enh_07_1_sw01", 48);
	 named_switches.findEunetSwitch("enh_07_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("10Gbps"));
	 named_switches.findEunetSwitch("enh_07_1_sw01")->connectUpTo(
	 "enh_02_1_sw01");

	 named_switches.addEunetSwitch("enh_06_1_sw01", 72);
	 named_switches.findEunetSwitch("enh_06_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("enh_06_1_sw01")->connectUpTo(
	 "enh_02_1_sw01");

	 named_switches.addEunetSwitch("enh_04_1_sw01", 24);
	 named_switches.findEunetSwitch("enh_04_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("enh_04_1_sw01")->connectUpTo(
	 "enh_02_1_sw01");

	 named_switches.addEunetSwitch("enh_03_1_sw01", 48);
	 named_switches.findEunetSwitch("enh_03_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("enh_03_1_sw01")->connectUpTo(
	 "enh_02_1_sw01");

	 named_switches.addEunetSwitch("en2_01_1_sw01", 48);
	 named_switches.findEunetSwitch("en2_01_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("10Gbps"));
	 named_switches.findEunetSwitch("en2_01_1_sw01")->connectUpTo(
	 "dpc_02_core01");

	 named_switches.addEunetSwitch("en2_01_1_sw02", 24);
	 named_switches.findEunetSwitch("en2_01_1_sw02")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("en2_01_1_sw02")->connectUpTo(
	 "en2_01_1_sw01");

	 named_switches.addEunetSwitch("en2_02_1_sw01", 72);
	 named_switches.findEunetSwitch("en2_02_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("en2_02_1_sw01")->connectUpTo(
	 "en2_01_1_sw01");

	 named_switches.addEunetSwitch("en2_03_1_sw01", 72);
	 named_switches.findEunetSwitch("en2_03_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("en2_03_1_sw01")->connectUpTo(
	 "en2_01_1_sw01");

	 named_switches.addEunetSwitch("en2_04_1_sw01", 72);
	 named_switches.findEunetSwitch("en2_04_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("en2_04_1_sw01")->connectUpTo(
	 "en2_01_1_sw01");

	 named_switches.addEunetSwitch("en2_05_1_sw01", 48);
	 named_switches.findEunetSwitch("en2_05_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("en2_05_1_sw01")->connectUpTo(
	 "en2_01_1_sw01");

	 named_switches.addEunetSwitch("en2_05_1_sw02", 48);
	 named_switches.findEunetSwitch("en2_05_1_sw02")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("en2_05_1_sw02")->connectUpTo(
	 "en2_01_1_sw01");

	 named_switches.addEunetSwitch("en2_06_1_sw01", 48);
	 named_switches.findEunetSwitch("en2_06_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("en2_06_1_sw01")->connectUpTo(
	 "en2_01_1_sw01");

	 named_switches.addEunetSwitch("en3_03_1_sw01", 72);
	 named_switches.findEunetSwitch("en3_03_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("10Gbps"));
	 named_switches.findEunetSwitch("en3_03_1_sw01")->connectUpTo(
	 "dpc_02_core01");

	 named_switches.addEunetSwitch("en3_03_1_sw02", 24);
	 named_switches.findEunetSwitch("en3_03_1_sw02")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("en3_03_1_sw02")->connectUpTo(
	 "en3_03_1_sw01");

	 named_switches.addEunetSwitch("en4_03_1_sw01", 48);
	 named_switches.findEunetSwitch("en4_03_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("10Gbps"));
	 named_switches.findEunetSwitch("en4_03_1_sw01")->connectUpTo(
	 "dpc_02_core01");

	 named_switches.addEunetSwitch("en4_07_1_sw01", 48);
	 named_switches.findEunetSwitch("en4_07_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("en4_07_1_sw01")->connectUpTo(
	 "en4_03_1_sw01");

	 named_switches.addEunetSwitch("en4_07_1_sw02", 48);
	 named_switches.findEunetSwitch("en4_07_1_sw02")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("en4_07_1_sw02")->connectUpTo(
	 "en4_03_1_sw01");

	 named_switches.addEunetSwitch("en5_01_1_sw01", 24);
	 named_switches.findEunetSwitch("en5_01_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("10Gbps"));
	 named_switches.findEunetSwitch("en5_01_1_sw01")->connectUpTo(
	 "dpc_02_core01");

	 named_switches.addEunetSwitch("en5_01_1_sw02", 24);
	 named_switches.findEunetSwitch("en5_01_1_sw02")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("en5_01_1_sw02")->connectUpTo(
	 "en5_01_1_sw01");

	 named_switches.addEunetSwitch("en5_01_1_sw03", 24);
	 named_switches.findEunetSwitch("en5_01_1_sw03")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("en5_01_1_sw03")->connectUpTo(
	 "en5_01_1_sw01");

	 named_switches.addEunetSwitch("en5_02_1_sw01", 24);
	 named_switches.findEunetSwitch("en5_02_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("en5_02_1_sw01")->connectUpTo(
	 "en5_01_1_sw03");

	 named_switches.addEunetSwitch("en5_03_1_sw01", 24);
	 named_switches.findEunetSwitch("en5_03_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("en5_03_1_sw01")->connectUpTo(
	 "en5_01_1_sw03");

	 named_switches.addEunetSwitch("en5_04_1_sw01", 48);
	 named_switches.findEunetSwitch("en5_04_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("en5_04_1_sw01")->connectUpTo(
	 "en5_01_1_sw03");

	 named_switches.addEunetSwitch("en5_05_1_sw01", 24);
	 named_switches.findEunetSwitch("en5_05_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("en5_05_1_sw01")->connectUpTo(
	 "en5_01_1_sw03");

	 named_switches.addEunetSwitch("en5_06_1_sw01", 24);
	 named_switches.findEunetSwitch("en5_06_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("en5_06_1_sw01")->connectUpTo(
	 "en5_01_1_sw03");

	 named_switches.addEunetSwitch("en5_07_1_sw01", 48);
	 named_switches.findEunetSwitch("en5_07_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("en5_07_1_sw01")->connectUpTo(
	 "en5_01_1_sw02");

	 named_switches.addEunetSwitch("en5_08_1_sw01", 48);
	 named_switches.findEunetSwitch("en5_08_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("en5_08_1_sw01")->connectUpTo(
	 "en5_01_1_sw02");

	 named_switches.addEunetSwitch("en5_09_1_sw01", 48);
	 named_switches.findEunetSwitch("en5_09_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("en5_09_1_sw01")->connectUpTo(
	 "en5_01_1_sw02");

	 named_switches.addEunetSwitch("en5_10_1_sw01", 48);
	 named_switches.findEunetSwitch("en5_10_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("en5_10_1_sw01")->connectUpTo(
	 "en5_01_1_sw02");

	 named_switches.addEunetSwitch("en02_01_1_sw01", 48);
	 named_switches.findEunetSwitch("en02_01_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("10Gbps"));
	 named_switches.findEunetSwitch("en02_01_1_sw01")->connectUpTo(
	 "dpc_02_core01");

	 named_switches.addEunetSwitch("en02_01_1_sw02", 48);
	 named_switches.findEunetSwitch("en02_01_1_sw02")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("en02_01_1_sw02")->connectUpTo(
	 "en02_01_1_sw01");

	 named_switches.addEunetSwitch("en02_02_1_sw01", 72);
	 named_switches.findEunetSwitch("en02_02_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("en02_02_1_sw01")->connectUpTo(
	 "en02_01_1_sw01");

	 named_switches.addEunetSwitch("en02_02_1_sw02", 72);
	 named_switches.findEunetSwitch("en02_02_1_sw02")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("en02_02_1_sw02")->connectUpTo(
	 "en02_01_1_sw02");

	 named_switches.addEunetSwitch("en02_03_1_sw01", 48);
	 named_switches.findEunetSwitch("en02_03_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("en02_03_1_sw01")->connectUpTo(
	 "en02_01_1_sw02");

	 named_switches.addEunetSwitch("en02_03_1_sw02", 48);
	 named_switches.findEunetSwitch("en02_03_1_sw02")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("en02_03_1_sw02")->connectUpTo(
	 "en02_03_1_sw01");

	 named_switches.addEunetSwitch("en02_03_1_sw03", 48);
	 named_switches.findEunetSwitch("en02_03_1_sw03")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("en02_03_1_sw03")->connectUpTo(
	 "en02_03_1_sw01");

	 named_switches.addEunetSwitch("en02_03_1_sw04", 48);
	 named_switches.findEunetSwitch("en02_03_1_sw04")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("en02_03_1_sw04")->connectUpTo(
	 "en02_03_1_sw01");

	 named_switches.addEunetSwitch("en02_04_1_sw01", 48);
	 named_switches.findEunetSwitch("en02_04_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("en02_04_1_sw01")->connectUpTo(
	 "en02_01_1_sw02");

	 named_switches.addEunetSwitch("en02_04_1_sw02", 48);
	 named_switches.findEunetSwitch("en02_04_1_sw02")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("en02_04_1_sw02")->connectUpTo(
	 "en02_04_1_sw01");

	 named_switches.addEunetSwitch("en02_04_1_sw03", 48);
	 named_switches.findEunetSwitch("en02_04_1_sw03")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("en02_04_1_sw03")->connectUpTo(
	 "en02_04_1_sw01");

	 named_switches.addEunetSwitch("en02_04_1_sw04", 48);
	 named_switches.findEunetSwitch("en02_04_1_sw04")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("en02_04_1_sw04")->connectUpTo(
	 "en02_04_1_sw01");

	 named_switches.addEunetSwitch("enk_04_1_sw01", 96);
	 named_switches.findEunetSwitch("enk_04_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("10Gbps"));
	 named_switches.findEunetSwitch("enk_04_1_sw01")->connectUpTo(
	 "dpc_02_01_sw01");

	 named_switches.addEunetSwitch("enk_01_1_sw01", 48);
	 named_switches.findEunetSwitch("enk_01_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("enk_01_1_sw01")->connectUpTo(
	 "en02_01_1_sw01");

	 named_switches.addEunetSwitch("eng_01_1_sw01", 48);
	 named_switches.findEunetSwitch("eng_01_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("eng_01_1_sw01")->connectUpTo(
	 "en02_01_1_sw02");

	 named_switches.addEunetSwitch("sche_01_1_sw01", 48);
	 named_switches.findEunetSwitch("sche_01_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("10Gbps"));
	 named_switches.findEunetSwitch("sche_01_1_sw01")->connectUpTo(
	 "dpc_02_core01");

	 named_switches.addEunetSwitch("sche_01_1_sw02", 24);
	 named_switches.findEunetSwitch("sche_01_1_sw02")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("sche_01_1_sw02")->connectUpTo(
	 "sche_01_1_sw01");

	 named_switches.addEunetSwitch("sche_01_2_sw01", 48);
	 named_switches.findEunetSwitch("sche_01_2_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("sche_01_2_sw01")->connectUpTo(
	 "sche_01_1_sw01");

	 named_switches.addEunetSwitch("sche_02_1_sw01", 48);
	 named_switches.findEunetSwitch("sche_02_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("sche_02_1_sw01")->connectUpTo(
	 "sche_01_1_sw01");

	 named_switches.addEunetSwitch("sche_03_1_sw01", 48);
	 named_switches.findEunetSwitch("sche_03_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("sche_03_1_sw01")->connectUpTo(
	 "sche_01_1_sw01");

	 named_switches.addEunetSwitch("sche_04_1_sw01", 48);
	 named_switches.findEunetSwitch("sche_04_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("sche_04_1_sw01")->connectUpTo(
	 "sche_01_1_sw01");

	 named_switches.addEunetSwitch("sche_05_1_sw01", 48);
	 named_switches.findEunetSwitch("sche_05_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("sche_05_1_sw01")->connectUpTo(
	 "sche_01_1_sw01");

	 named_switches.addEunetSwitch("sche_05_2_sw01", 48);
	 named_switches.findEunetSwitch("sche_05_2_sw01")->setUplinkDataRate(
	 ns3::DataRate("10Gbps"));
	 named_switches.findEunetSwitch("sche_05_2_sw01")->connectUpTo(
	 "dpc_02_01_sw01");

	 named_switches.addEunetSwitch("sc2_01_1_sw01", 48);
	 named_switches.findEunetSwitch("sc2_01_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("sc2_01_1_sw01")->connectUpTo(
	 "sche_01_1_sw01");

	 named_switches.addEunetSwitch("sc2_02_1_sw01", 24);
	 named_switches.findEunetSwitch("sc2_02_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("sc2_02_1_sw01")->connectUpTo(
	 "sc2_01_1_sw01");

	 named_switches.addEunetSwitch("sc2_03_1_sw01", 48);
	 named_switches.findEunetSwitch("sc2_03_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("sc2_03_1_sw01")->connectUpTo(
	 "sc2_01_1_sw01");

	 named_switches.addEunetSwitch("sc2_04_1_sw01", 24);
	 named_switches.findEunetSwitch("sc2_04_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("sc2_04_1_sw01")->connectUpTo(
	 "sc2_01_1_sw01");

	 named_switches.addEunetSwitch("sck_02_1_sw01", 48);
	 named_switches.findEunetSwitch("sck_02_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("sck_02_1_sw01")->connectUpTo(
	 "sche_01_1_sw02");

	 named_switches.addEunetSwitch("en0w_01_1_sw01", 24);
	 named_switches.findEunetSwitch("en0w_01_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("10Gbps"));
	 named_switches.findEunetSwitch("en0w_01_1_sw01")->connectUpTo(
	 "dpc_02_core01");

	 named_switches.addEunetSwitch("en0w_01_1_sw02", 48);
	 named_switches.findEunetSwitch("en0w_01_1_sw02")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("en0w_01_1_sw02")->connectUpTo(
	 "en0w_01_1_sw01");

	 named_switches.addEunetSwitch("en0w_02_1_sw01", 48);
	 named_switches.findEunetSwitch("en0w_02_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("en0w_02_1_sw01")->connectUpTo(
	 "en0w_01_1_sw01");

	 named_switches.addEunetSwitch("en0w_03_1_sw01", 48);
	 named_switches.findEunetSwitch("en0w_03_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("en0w_03_1_sw01")->connectUpTo(
	 "en0w_01_1_sw01");

	 named_switches.addEunetSwitch("en0w_04_1_sw01", 72);
	 named_switches.findEunetSwitch("en0w_04_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("en0w_04_1_sw01")->connectUpTo(
	 "en0w_01_1_sw01");

	 named_switches.addEunetSwitch("en0w_05_1_sw01", 48);
	 named_switches.findEunetSwitch("en0w_05_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("en0w_05_1_sw01")->connectUpTo(
	 "en0w_01_1_sw01");

	 named_switches.addEunetSwitch("en0w_06_1_sw01", 48);
	 named_switches.findEunetSwitch("en0w_06_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("en0w_06_1_sw01")->connectUpTo(
	 "en0w_01_1_sw01");

	 named_switches.addEunetSwitch("en0w_07_1_sw01", 48);
	 named_switches.findEunetSwitch("en0w_07_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("en0w_07_1_sw01")->connectUpTo(
	 "en0w_01_1_sw01");

	 named_switches.addEunetSwitch("en0e_01_1_sw01", 72);
	 named_switches.findEunetSwitch("en0e_01_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("en0e_01_1_sw01")->connectUpTo(
	 "en0w_01_1_sw02");

	 named_switches.addEunetSwitch("en0e_02_1_sw01", 72);
	 named_switches.findEunetSwitch("en0e_02_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("en0e_02_1_sw01")->connectUpTo(
	 "en0w_01_1_sw02");

	 named_switches.addEunetSwitch("en0e_03_1_sw01", 72);
	 named_switches.findEunetSwitch("en0e_03_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("en0e_03_1_sw01")->connectUpTo(
	 "en0w_01_1_sw02");

	 named_switches.addEunetSwitch("en0e_04_1_sw01", 72);
	 named_switches.findEunetSwitch("en0e_04_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("en0e_04_1_sw01")->connectUpTo(
	 "en0w_01_1_sw02");

	 named_switches.addEunetSwitch("en0e_05_1_sw01", 48);
	 named_switches.findEunetSwitch("en0e_05_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("en0e_05_1_sw01")->connectUpTo(
	 "en0w_01_1_sw02");

	 named_switches.addEunetSwitch("en0e_06_1_sw01", 48);
	 named_switches.findEunetSwitch("en0e_06_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("en0e_06_1_sw01")->connectUpTo(
	 "en0w_01_1_sw02");

	 named_switches.addEunetSwitch("en0e_07_1_sw01", 48);
	 named_switches.findEunetSwitch("en0e_07_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("en0e_07_1_sw01")->connectUpTo(
	 "en0w_01_1_sw02");

	 named_switches.addEunetSwitch("schw_01_1_sw01", 48);
	 named_switches.findEunetSwitch("schw_01_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("schw_01_1_sw01")->connectUpTo(
	 "sche_01_1_sw02");

	 named_switches.addEunetSwitch("schw_02_1_sw01", 72);
	 named_switches.findEunetSwitch("schw_02_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("schw_02_1_sw01")->connectUpTo(
	 "schw_01_1_sw01");

	 named_switches.addEunetSwitch("schw_03_1_sw01", 72);
	 named_switches.findEunetSwitch("schw_03_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("schw_03_1_sw01")->connectUpTo(
	 "schw_01_1_sw01");

	 named_switches.addEunetSwitch("schw_04_1_sw01", 48);
	 named_switches.findEunetSwitch("schw_04_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("schw_04_1_sw01")->connectUpTo(
	 "schw_01_1_sw01");

	 named_switches.addEunetSwitch("schw_05_1_sw01", 48);
	 named_switches.findEunetSwitch("schw_05_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("schw_05_1_sw01")->connectUpTo(
	 "schw_01_1_sw01");

	 named_switches.addEunetSwitch("llh_01_2_sw02", 48);
	 named_switches.findEunetSwitch("llh_01_2_sw02")->setUplinkDataRate(
	 ns3::DataRate("10Gbps"));
	 named_switches.findEunetSwitch("llh_01_2_sw02")->connectUpTo(
	 "dpc_02_01_sw01");

	 named_switches.addEunetSwitch("llh_01_1_sw01", 24);
	 named_switches.findEunetSwitch("llh_01_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("10Gbps"));
	 named_switches.findEunetSwitch("llh_01_1_sw01")->connectUpTo(
	 "dpc_02_core01");

	 named_switches.addEunetSwitch("llh_01_1_sw02", 24);
	 named_switches.findEunetSwitch("llh_01_1_sw02")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("llh_01_1_sw02")->connectUpTo(
	 "llh_01_1_sw01");

	 named_switches.addEunetSwitch("llh_01_2_sw01", 48);
	 named_switches.findEunetSwitch("llh_01_2_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("llh_01_2_sw01")->connectUpTo(
	 "llh_01_1_sw01");

	 named_switches.addEunetSwitch("llh_02_1_sw01", 48);
	 named_switches.findEunetSwitch("llh_02_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("llh_02_1_sw01")->connectUpTo(
	 "llh_01_1_sw01");

	 named_switches.addEunetSwitch("llh_03_1_sw01", 24);
	 named_switches.findEunetSwitch("llh_03_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("llh_03_1_sw01")->connectUpTo(
	 "llh_01_1_sw02");

	 named_switches.addEunetSwitch("llh_04_1_sw01", 48);
	 named_switches.findEunetSwitch("llh_04_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("llh_04_1_sw01")->connectUpTo(
	 "llh_01_1_sw02");

	 named_switches.addEunetSwitch("llh_05_1_sw01", 48);
	 named_switches.findEunetSwitch("llh_05_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("llh_05_1_sw01")->connectUpTo(
	 "llh_01_1_sw02");

	 named_switches.addEunetSwitch("llh_05_2_sw01", 24);
	 named_switches.findEunetSwitch("llh_05_2_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("llh_05_2_sw01")->connectUpTo(
	 "llh_05_1_sw01");

	 named_switches.addEunetSwitch("llh_06_1_sw01", 48);
	 named_switches.findEunetSwitch("llh_06_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("llh_06_1_sw01")->connectUpTo(
	 "llh_05_1_sw01");

	 named_switches.addEunetSwitch("llh_07_1_sw01", 48);
	 named_switches.findEunetSwitch("llh_07_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("llh_07_1_sw01")->connectUpTo(
	 "llh_05_1_sw01");

	 named_switches.addEunetSwitch("llh_08_1_sw01", 48);
	 named_switches.findEunetSwitch("llh_08_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("llh_08_1_sw01")->connectUpTo(
	 "llh_05_1_sw01");

	 named_switches.addEunetSwitch("ll2_01_1_sw01", 48);
	 named_switches.findEunetSwitch("ll2_01_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("ll2_01_1_sw01")->connectUpTo(
	 "llh_01_1_sw01");

	 named_switches.addEunetSwitch("ll2_01_2_sw01", 24);
	 named_switches.findEunetSwitch("ll2_01_2_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("ll2_01_2_sw01")->connectUpTo(
	 "ll2_01_1_sw01");

	 named_switches.addEunetSwitch("ll2_02_1_sw01", 24);
	 named_switches.findEunetSwitch("ll2_02_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("ll2_02_1_sw01")->connectUpTo(
	 "ll2_01_1_sw01");

	 named_switches.addEunetSwitch("ll2_03_1_sw01", 48);
	 named_switches.findEunetSwitch("ll2_03_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("ll2_03_1_sw01")->connectUpTo(
	 "ll2_01_1_sw01");

	 named_switches.addEunetSwitch("ed2_02_1_sw01", 48);
	 named_switches.findEunetSwitch("ed2_02_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("10Gbps"));
	 named_switches.findEunetSwitch("ed2_02_1_sw01")->connectUpTo(
	 "dpc_02_core01");

	 named_switches.addEunetSwitch("ed2_02_1_sw02", 24);
	 named_switches.findEunetSwitch("ed2_02_1_sw02")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("ed2_02_1_sw02")->connectUpTo(
	 "ed2_02_1_sw01");

	 named_switches.addEunetSwitch("ed2_01_1_sw01", 72);
	 named_switches.findEunetSwitch("ed2_01_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("ed2_01_1_sw01")->connectUpTo(
	 "ed2_02_1_sw01");

	 named_switches.addEunetSwitch("ed2_03_1_sw01", 72);
	 named_switches.findEunetSwitch("ed2_03_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("10Gbps"));
	 named_switches.findEunetSwitch("ed2_03_1_sw01")->connectUpTo(
	 "dpc_02_01_sw01");

	 named_switches.addEunetSwitch("ed2_03_2_sw01", 48);
	 named_switches.findEunetSwitch("ed2_03_2_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("ed2_03_2_sw01")->connectUpTo(
	 "ed2_02_1_sw01");

	 named_switches.addEunetSwitch("ed2_03_2_sw02", 24);
	 named_switches.findEunetSwitch("ed2_03_2_sw02")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("ed2_03_2_sw02")->connectUpTo(
	 "ed2_03_2_sw01");

	 named_switches.addEunetSwitch("ed2_04_1_sw01", 48);
	 named_switches.findEunetSwitch("ed2_04_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("ed2_04_1_sw01")->connectUpTo(
	 "ed2_02_1_sw01");

	 named_switches.addEunetSwitch("ed2_04_1_sw02", 24);
	 named_switches.findEunetSwitch("ed2_04_1_sw02")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("ed2_04_1_sw02")->connectUpTo(
	 "ed2_04_1_sw01");

	 named_switches.addEunetSwitch("ed2_05_1_sw01", 48);
	 named_switches.findEunetSwitch("ed2_05_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("ed2_05_1_sw01")->connectUpTo(
	 "ed2_02_1_sw01");

	 named_switches.addEunetSwitch("ed3_02_1_sw01", 24);
	 named_switches.findEunetSwitch("ed3_02_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("10Gbps"));
	 named_switches.findEunetSwitch("ed3_02_1_sw01")->connectUpTo(
	 "dpc_02_core01");

	 named_switches.addEunetSwitch("ed3_02_1_sw02", 24);
	 named_switches.findEunetSwitch("ed3_02_1_sw02")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("ed3_02_1_sw02")->connectUpTo(
	 "ed3_02_1_sw01");

	 named_switches.addEunetSwitch("ed3_01_1_sw01", 24);
	 named_switches.findEunetSwitch("ed3_01_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("ed3_01_1_sw01")->connectUpTo(
	 "ed3_02_1_sw01");

	 named_switches.addEunetSwitch("ed3_03_1_sw01", 24);
	 named_switches.findEunetSwitch("ed3_03_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("ed3_03_1_sw01")->connectUpTo(
	 "ed3_02_1_sw01");

	 named_switches.addEunetSwitch("ed3_04_1_sw01", 48);
	 named_switches.findEunetSwitch("ed3_04_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("ed3_04_1_sw01")->connectUpTo(
	 "ed3_02_1_sw01");

	 named_switches.addEunetSwitch("ed3_05_1_sw01", 24);
	 named_switches.findEunetSwitch("ed3_05_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("ed3_05_1_sw01")->connectUpTo(
	 "ed3_02_1_sw01");

	 named_switches.addEunetSwitch("ed3_06_1_sw01", 24);
	 named_switches.findEunetSwitch("ed3_06_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("ed3_06_1_sw01")->connectUpTo(
	 "ed3_02_1_sw01");

	 named_switches.addEunetSwitch("su_02_1_sw01", 24);
	 named_switches.findEunetSwitch("su_02_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("su_02_1_sw01")->connectUpTo(
	 "dpc_02_01_sw01");

	 named_switches.addEunetSwitch("edh_01_1_sw01", 48);
	 named_switches.findEunetSwitch("edh_01_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("edh_01_1_sw01")->connectUpTo(
	 "ed3_02_1_sw01");

	 named_switches.addEunetSwitch("edh_02_1_sw01", 48);
	 named_switches.findEunetSwitch("edh_02_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("edh_02_1_sw01")->connectUpTo(
	 "edh_01_1_sw01");

	 named_switches.addEunetSwitch("edh_03_1_sw01", 48);
	 named_switches.findEunetSwitch("edh_03_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("edh_03_1_sw01")->connectUpTo(
	 "edh_01_1_sw01");

	 named_switches.addEunetSwitch("edh_03_1_sw02", 24);
	 named_switches.findEunetSwitch("edh_03_1_sw02")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("edh_03_1_sw02")->connectUpTo(
	 "edh_03_1_sw01");

	 named_switches.addEunetSwitch("edh_04_1_sw01", 24);
	 named_switches.findEunetSwitch("edh_04_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("edh_04_1_sw01")->connectUpTo(
	 "edh_01_1_sw01");

	 named_switches.addEunetSwitch("ed4_01_1_sw01", 24);
	 named_switches.findEunetSwitch("ed4_01_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("ed4_01_1_sw01")->connectUpTo(
	 "ed3_02_1_sw02");

	 named_switches.addEunetSwitch("ed4_01_2_sw01", 24);
	 named_switches.findEunetSwitch("ed4_01_2_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("ed4_01_2_sw01")->connectUpTo(
	 "ed3_02_1_sw02");

	 named_switches.addEunetSwitch("ed4_01_3_sw01", 24);
	 named_switches.findEunetSwitch("ed4_01_3_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("ed4_01_3_sw01")->connectUpTo(
	 "ed4_01_2_sw01");

	 named_switches.addEunetSwitch("ed4_02_1_sw01", 24);
	 named_switches.findEunetSwitch("ed4_02_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("ed4_02_1_sw01")->connectUpTo(
	 "ed4_01_2_sw01");

	 named_switches.addEunetSwitch("ed4_03_1_sw01", 24);
	 named_switches.findEunetSwitch("ed4_03_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("ed4_03_1_sw01")->connectUpTo(
	 "ed4_01_2_sw01");

	 named_switches.addEunetSwitch("ed4_04_1_sw01", 24);
	 named_switches.findEunetSwitch("ed4_04_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("ed4_04_1_sw01")->connectUpTo(
	 "ed4_01_2_sw01");

	 named_switches.addEunetSwitch("ph1_01_1_sw01", 8);
	 named_switches.findEunetSwitch("ph1_01_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("ph1_01_1_sw01")->connectUpTo(
	 "ed3_02_1_sw01");

	 named_switches.addEunetSwitch("ph3_01_1_sw01", 8);
	 named_switches.findEunetSwitch("ph3_01_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("ph3_01_1_sw01")->connectUpTo(
	 "ph1_01_1_sw01");

	 named_switches.addEunetSwitch("gk_04_1_sw01", 24);
	 named_switches.findEunetSwitch("gk_04_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("gk_04_1_sw01")->connectUpTo("ed3_02_1_sw01");

	 named_switches.addEunetSwitch("gee_01_1_sw01", 24);
	 named_switches.findEunetSwitch("gee_01_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("10Gbps"));
	 named_switches.findEunetSwitch("gee_01_1_sw01")->connectUpTo(
	 "dpc_02_core01");

	 named_switches.addEunetSwitch("gee_01_1_sw02", 24);
	 named_switches.findEunetSwitch("gee_01_1_sw02")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("gee_01_1_sw02")->connectUpTo(
	 "gee_01_1_sw01");

	 named_switches.addEunetSwitch("gee_01_1_sw03", 24);
	 named_switches.findEunetSwitch("gee_01_1_sw03")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("gee_01_1_sw03")->connectUpTo(
	 "gee_01_1_sw01");

	 named_switches.addEunetSwitch("gee_02_1_sw01", 24);
	 named_switches.findEunetSwitch("gee_02_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("gee_02_1_sw01")->connectUpTo(
	 "gee_01_1_sw01");

	 named_switches.addEunetSwitch("gee_02_1_sw02", 24);
	 named_switches.findEunetSwitch("gee_02_1_sw02")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("gee_02_1_sw02")->connectUpTo(
	 "gee_02_1_sw01");

	 named_switches.addEunetSwitch("gee_03_1_sw01", 24);
	 named_switches.findEunetSwitch("gee_03_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("gee_03_1_sw01")->connectUpTo(
	 "gee_01_1_sw01");

	 named_switches.addEunetSwitch("gew_01_1_sw01", 48);
	 named_switches.findEunetSwitch("gew_01_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("gew_01_1_sw01")->connectUpTo(
	 "gee_01_1_sw03");

	 named_switches.addEunetSwitch("gew_02_1_sw01", 48);
	 named_switches.findEunetSwitch("gew_02_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("gew_02_1_sw01")->connectUpTo(
	 "gew_01_1_sw01");

	 named_switches.addEunetSwitch("gew_03_1_sw01", 48);
	 named_switches.findEunetSwitch("gew_03_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("gew_03_1_sw01")->connectUpTo(
	 "gew_01_1_sw01");

	 named_switches.addEunetSwitch("gew_03_1_sw02", 24);
	 named_switches.findEunetSwitch("gew_03_1_sw02")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("gew_03_1_sw02")->connectUpTo(
	 "gew_03_1_sw01");

	 named_switches.addEunetSwitch("ges_02_2_sw01", 72);
	 named_switches.findEunetSwitch("ges_02_2_sw01")->setUplinkDataRate(
	 ns3::DataRate("10Gbps"));
	 named_switches.findEunetSwitch("ges_02_2_sw01")->connectUpTo(
	 "dpc_02_01_sw01");

	 named_switches.addEunetSwitch("ges_03_2_sw01", 72);
	 named_switches.findEunetSwitch("ges_03_2_sw01")->setUplinkDataRate(
	 ns3::DataRate("10Gbps"));
	 named_switches.findEunetSwitch("ges_03_2_sw01")->connectUpTo(
	 "dpc_02_01_sw01");

	 named_switches.addEunetSwitch("ges_01_1_sw01", 48);
	 named_switches.findEunetSwitch("ges_01_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("ges_01_1_sw01")->connectUpTo(
	 "gee_01_1_sw02");

	 named_switches.addEunetSwitch("ges_02_1_sw01", 48);
	 named_switches.findEunetSwitch("ges_02_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("ges_02_1_sw01")->connectUpTo(
	 "ges_01_1_sw01");

	 named_switches.addEunetSwitch("ges_03_1_sw01", 48);
	 named_switches.findEunetSwitch("ges_03_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("ges_03_1_sw01")->connectUpTo(
	 "ges_01_1_sw01");

	 named_switches.addEunetSwitch("gek_01_1_sw01", 48);
	 named_switches.findEunetSwitch("gek_01_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("gek_01_1_sw01")->connectUpTo(
	 "gee_01_1_sw02");

	 named_switches.addEunetSwitch("ven_01_1_sw01", 24);
	 named_switches.findEunetSwitch("ven_01_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("10Gbps"));
	 named_switches.findEunetSwitch("ven_01_1_sw01")->connectUpTo(
	 "dpc_02_core01");

	 named_switches.addEunetSwitch("ven_02_1_sw01", 24);
	 named_switches.findEunetSwitch("ven_02_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("ven_02_1_sw01")->connectUpTo(
	 "ven_01_1_sw01");

	 named_switches.addEunetSwitch("ven_03_1_sw01", 24);
	 named_switches.findEunetSwitch("ven_03_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("ven_03_1_sw01")->connectUpTo(
	 "ven_01_1_sw01");

	 named_switches.addEunetSwitch("ven_04_1_sw01", 24);
	 named_switches.findEunetSwitch("ven_04_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("ven_04_1_sw01")->connectUpTo(
	 "ven_01_1_sw01");

	 named_switches.addEunetSwitch("ccr_01_1_sw01", 24);
	 named_switches.findEunetSwitch("ccr_01_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("ccr_01_1_sw01")->connectUpTo(
	 "ven_01_1_sw01");

	 named_switches.addEunetSwitch("ccr_02_1_sw01", 24);
	 named_switches.findEunetSwitch("ccr_02_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("ccr_02_1_sw01")->connectUpTo(
	 "ven_01_1_sw01");

	 named_switches.addEunetSwitch("ccr_03_1_sw01", 24);
	 named_switches.findEunetSwitch("ccr_03_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("ccr_03_1_sw01")->connectUpTo(
	 "ven_01_1_sw01");

	 named_switches.addEunetSwitch("ci_01_1_sw01", 48);
	 named_switches.findEunetSwitch("ci_01_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("10Gbps"));
	 named_switches.findEunetSwitch("ci_01_1_sw01")->connectUpTo("dpc_02_core01");

	 named_switches.addEunetSwitch("ci_02_1_sw01", 24);
	 named_switches.findEunetSwitch("ci_02_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("ci_02_1_sw01")->connectUpTo("ci_01_1_sw01");

	 named_switches.addEunetSwitch("ci_03_1_sw01", 24);
	 named_switches.findEunetSwitch("ci_03_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("ci_03_1_sw01")->connectUpTo("ci_01_1_sw01");

	 named_switches.addEunetSwitch("libs_02_1_sw01", 24);
	 named_switches.findEunetSwitch("libs_02_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("10Gbps"));
	 named_switches.findEunetSwitch("libs_02_1_sw01")->connectUpTo(
	 "dpc_02_core01");

	 named_switches.addEunetSwitch("libw_01_1_sw01", 48);
	 named_switches.findEunetSwitch("libw_01_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("libw_01_1_sw01")->connectUpTo(
	 "libs_02_1_sw01");

	 named_switches.addEunetSwitch("libe_01_1_sw01", 72);
	 named_switches.findEunetSwitch("libe_01_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("libe_01_1_sw01")->connectUpTo(
	 "libw_01_1_sw01");

	 named_switches.addEunetSwitch("libw_02_1_sw01", 24);
	 named_switches.findEunetSwitch("libw_02_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("libw_02_1_sw01")->connectUpTo(
	 "libw_01_1_sw01");

	 named_switches.addEunetSwitch("libe_02_1_sw01", 72);
	 named_switches.findEunetSwitch("libe_02_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("libe_02_1_sw01")->connectUpTo(
	 "libe_01_1_sw01");

	 named_switches.addEunetSwitch("libe_02_1_sw02", 24);
	 named_switches.findEunetSwitch("libe_02_1_sw02")->setUplinkDataRate(
	 ns3::DataRate("10Gbps"));
	 named_switches.findEunetSwitch("libe_02_1_sw02")->connectUpTo(
	 "dpc_02_01_sw01");

	 named_switches.addEunetSwitch("libw_03_1_sw01", 24);
	 named_switches.findEunetSwitch("libw_03_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("libw_03_1_sw01")->connectUpTo(
	 "libw_01_1_sw01");

	 named_switches.addEunetSwitch("libe_03_1_sw01", 24);
	 named_switches.findEunetSwitch("libe_03_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("libe_03_1_sw01")->connectUpTo(
	 "libe_01_1_sw01");

	 named_switches.addEunetSwitch("libw_04_1_sw01", 24);
	 named_switches.findEunetSwitch("libw_04_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("libw_04_1_sw01")->connectUpTo(
	 "libw_01_1_sw01");

	 named_switches.addEunetSwitch("libe_04_1_sw01", 24);
	 named_switches.findEunetSwitch("libe_04_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("libe_04_1_sw01")->connectUpTo(
	 "libe_01_1_sw01");

	 named_switches.addEunetSwitch("jim_02_1_sw01", 72);
	 named_switches.findEunetSwitch("jim_02_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("10Gbps"));
	 named_switches.findEunetSwitch("jim_02_1_sw01")->connectUpTo(
	 "dpc_02_core01");

	 named_switches.addEunetSwitch("odpc_01_1_sw01", 24);
	 named_switches.findEunetSwitch("odpc_01_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("10Gbps"));
	 named_switches.findEunetSwitch("odpc_01_1_sw01")->connectUpTo(
	 "dpc_02_01_sw01");
	 */

	/*
	 //重信キャンパスネットワーク
	 //医学部寮
	 named_switches.addEunetSwitch("me0_02_1_core01", 64);
	 named_switches.findEunetSwitch("me0_02_1_core01")->setUplinkDataRate(
	 ns3::DataRate("10Gbps"));
	 named_switches.findEunetSwitch("me0_02_1_core01")->connectUpTo("キャンパス間接続L2");

	 named_switches.addEunetSwitch("me0_02_1_sw01", 64);
	 named_switches.findEunetSwitch("me0_02_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("10Gbps"));
	 named_switches.findEunetSwitch("me0_02_1_sw01")->connectUpTo("キャンパス間接続L2");

	 named_switches.addEunetSwitch("me0_02_1_sw02", 24);
	 named_switches.findEunetSwitch("me0_02_1_sw02")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("me0_02_1_sw02")->connectUpTo(
	 "me0_02_1_core01");

	 named_switches.addEunetSwitch("me0_02_1_sw03", 24);
	 named_switches.findEunetSwitch("me0_02_1_sw03")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("me0_02_1_sw03")->connectUpTo(
	 "me0_02_1_core01");

	 named_switches.addEunetSwitch("me0_02_1_sw04", 48);
	 named_switches.findEunetSwitch("me0_02_1_sw04")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("me0_02_1_sw04")->connectUpTo(
	 "me0_02_1_core01");

	 named_switches.addEunetSwitch("me0_02_2_sw01", 48);
	 named_switches.findEunetSwitch("me0_02_2_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("me0_02_2_sw01")->connectUpTo(
	 "me0_02_1_core01");

	 named_switches.addEunetSwitch("me0_02_3_sw01", 48);
	 named_switches.findEunetSwitch("me0_02_3_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("me0_02_3_sw01")->connectUpTo(
	 "me0_02_1_sw04");

	 named_switches.addEunetSwitch("me0_01_1_sw01", 48);
	 named_switches.findEunetSwitch("me0_01_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("me0_01_1_sw01")->connectUpTo(
	 "me0_02_1_sw02");

	 named_switches.addEunetSwitch("me0_03_1_sw01", 72);
	 named_switches.findEunetSwitch("me0_03_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("me0_03_1_sw01")->connectUpTo(
	 "me0_02_1_sw02");

	 named_switches.addEunetSwitch("me0_04_1_sw01", 48);
	 named_switches.findEunetSwitch("me0_04_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("me0_04_1_sw01")->connectUpTo(
	 "me0_02_1_sw02");

	 named_switches.addEunetSwitch("me0_05_1_sw01", 48);
	 named_switches.findEunetSwitch("me0_05_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("me0_05_1_sw01")->connectUpTo(
	 "me0_02_1_sw02");

	 named_switches.addEunetSwitch("me0_06_1_sw01", 48);
	 named_switches.findEunetSwitch("me0_06_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("me0_06_1_sw01")->connectUpTo(
	 "me0_02_1_sw03");

	 named_switches.addEunetSwitch("me0_07_1_sw01", 72);
	 named_switches.findEunetSwitch("me0_07_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("me0_07_1_sw01")->connectUpTo(
	 "me0_02_1_sw03");

	 named_switches.addEunetSwitch("me0_08_1_sw01", 72);
	 named_switches.findEunetSwitch("me0_08_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("me0_08_1_sw01")->connectUpTo(
	 "me0_02_1_sw03");

	 named_switches.addEunetSwitch("me0_09_1_sw01", 72);
	 named_switches.findEunetSwitch("me0_09_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("me0_09_1_sw01")->connectUpTo(
	 "me0_02_1_sw03");

	 //総合科学研究支援センタ
	 named_switches.addEunetSwitch("mes_02_1_sw01", 24);
	 named_switches.findEunetSwitch("mes_02_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("10Gbps"));
	 named_switches.findEunetSwitch("mes_02_1_sw01")->connectUpTo(
	 "me0_02_1_sw01");

	 named_switches.addEunetSwitch("mes_01_1_sw01", 24);
	 named_switches.findEunetSwitch("mes_01_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("mes_01_1_sw01")->connectUpTo(
	 "mes_02_1_sw01");

	 //総合教育棟
	 named_switches.addEunetSwitch("mej_02_1_sw02", 144);
	 named_switches.findEunetSwitch("mej_02_1_sw02")->setUplinkDataRate(
	 ns3::DataRate("10Gbps"));
	 named_switches.findEunetSwitch("mej_02_1_sw02")->connectUpTo(
	 "me0_02_1_sw01");

	 named_switches.addEunetSwitch("mej_02_1_sw01", 72);
	 named_switches.findEunetSwitch("mej_02_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("mej_02_1_sw01")->connectUpTo(
	 "me0_02_1_sw02");

	 named_switches.addEunetSwitch("mej_01_1_sw01", 24);
	 named_switches.findEunetSwitch("mej_01_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("mej_01_1_sw01")->connectUpTo(
	 "me0_02_1_sw01");

	 //臨床研究棟
	 named_switches.addEunetSwitch("mer_01_1_sw01", 24);
	 named_switches.findEunetSwitch("mer_01_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("10Gbps"));
	 named_switches.findEunetSwitch("mer_01_1_sw01")->connectUpTo(
	 "me0_　02_1_core01");

	 named_switches.addEunetSwitch("mer_02_1_sw01", 24);
	 named_switches.findEunetSwitch("mer_02_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("mer_02_1_sw01")->connectUpTo(
	 "mer_01_1_sw01");

	 named_switches.addEunetSwitch("mer_03_1_sw01", 24);
	 named_switches.findEunetSwitch("mer_03_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("mer_03_1_sw01")->connectUpTo(
	 "mer_01_1_sw01");

	 //看護学科校舎
	 named_switches.addEunetSwitch("men_03_1_sw01", 24);
	 named_switches.findEunetSwitch("men_03_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("10Gbps"));
	 named_switches.findEunetSwitch("men_03_1_sw01")->connectUpTo(
	 "me0_02_1_core01");

	 named_switches.addEunetSwitch("men_01_1_sw01", 24);
	 named_switches.findEunetSwitch("men_01_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("men_01_1_sw01")->connectUpTo(
	 "men_03_1_sw01");

	 named_switches.addEunetSwitch("men_02_1_sw01", 24);
	 named_switches.findEunetSwitch("men_02_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("men_02_1_sw01")->connectUpTo(
	 "men_03_1_sw01");

	 named_switches.addEunetSwitch("men_04_1_sw01", 24);
	 named_switches.findEunetSwitch("men_04_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("men_04_1_sw01")->connectUpTo(
	 "men_03_1_sw01");

	 named_switches.addEunetSwitch("men_04_2_sw01", 48);
	 named_switches.findEunetSwitch("men_04_2_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("men_04_2_sw01")->connectUpTo(
	 "men_03_1_sw01");

	 named_switches.addEunetSwitch("men_04_2_sw02", 96);
	 named_switches.findEunetSwitch("men_04_2_sw02")->setUplinkDataRate(
	 ns3::DataRate("10Gbps"));
	 named_switches.findEunetSwitch("men_04_2_sw02")->connectUpTo(
	 "men_03_1_sw01");

	 named_switches.addEunetSwitch("men_05_1_sw01", 24);
	 named_switches.findEunetSwitch("men_05_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("men_05_1_sw01")->connectUpTo(
	 "men_03_1_sw01");

	 named_switches.addEunetSwitch("men_06_1_sw01", 24);
	 named_switches.findEunetSwitch("men_06_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("men_06_1_sw01")->connectUpTo(
	 "men_03_1_sw01");

	 //管理棟
	 named_switches.addEunetSwitch("mek_03_1_sw01", 24);
	 named_switches.findEunetSwitch("mek_03_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("10Gbps"));
	 named_switches.findEunetSwitch("mek_03_1_sw01")->connectUpTo(
	 "me0_02_1_core01");

	 named_switches.addEunetSwitch("mek_02_1_sw01", 24);
	 named_switches.findEunetSwitch("mek_02_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("mek_02_1_sw01")->connectUpTo(
	 "me0_02_1_sw01");

	 //付属図書館医学部分館
	 named_switches.addEunetSwitch("melib_01_1_sw01", 72);
	 named_switches.findEunetSwitch("melib_01_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("10Gbps"));
	 named_switches.findEunetSwitch("melib_01_1_sw01")->connectUpTo(
	 "me0_02_1_core01");

	 //付属病院1号館
	 named_switches.addEunetSwitch("me1_02_1_sw01", 48);
	 named_switches.findEunetSwitch("me1_02_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("10Gbps"));
	 named_switches.findEunetSwitch("me1_02_1_sw01")->connectUpTo(
	 "me0_02_1_core01");

	 named_switches.addEunetSwitch("me1_02_1_sw02", 24);
	 named_switches.findEunetSwitch("me1_02_1_sw02")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("me1_02_1_sw02")->connectUpTo(
	 "me1_02_1_sw01");

	 named_switches.addEunetSwitch("me1_02_1_sw03", 24);
	 named_switches.findEunetSwitch("me1_02_1_sw03")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("me1_02_1_sw03")->connectUpTo(
	 "me1_02_1_sw01");

	 named_switches.addEunetSwitch("me1_02_1_sw04", 24);
	 named_switches.findEunetSwitch("me1_02_1_sw04")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("me1_02_1_sw04")->connectUpTo(
	 "me1_02_1_sw01");

	 named_switches.addEunetSwitch("me1_02_1_sw05", 24);
	 named_switches.findEunetSwitch("me1_02_1_sw05")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("me1_02_1_sw05")->connectUpTo(
	 "me1_02_1_sw01");

	 named_switches.addEunetSwitch("me1_02_1_sw06", 24);
	 named_switches.findEunetSwitch("me1_02_1_sw06")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("me1_02_1_sw06")->connectUpTo(
	 "me1_02_1_sw01");

	 named_switches.addEunetSwitch("me1_02_1_sw07", 24);
	 named_switches.findEunetSwitch("me1_02_1_sw07")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("me1_02_1_sw07")->connectUpTo(
	 "me1_02_1_sw01");

	 named_switches.addEunetSwitch("me1_02_1_sw08", 24);
	 named_switches.findEunetSwitch("me1_02_1_sw08")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("me1_02_1_sw08")->connectUpTo(
	 "me1_02_1_sw01");

	 named_switches.addEunetSwitch("me1_02_1_sw09", 48);
	 named_switches.findEunetSwitch("me1_02_1_sw09")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("me1_02_1_sw09")->connectUpTo(
	 "me1_02_1_sw01");

	 named_switches.addEunetSwitch("me1_02_2_sw01", 24);
	 named_switches.findEunetSwitch("me1_02_2_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("me1_02_2_sw01")->connectUpTo(
	 "me1_02_1_sw04");

	 named_switches.addEunetSwitch("me1_02_3_sw01", 24);
	 named_switches.findEunetSwitch("me1_02_3_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("me1_02_3_sw01")->connectUpTo(
	 "me1_02_1_sw05");

	 named_switches.addEunetSwitch("me1_01_1_sw01", 24);
	 named_switches.findEunetSwitch("me1_01_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("me1_01_1_sw01")->connectUpTo(
	 "me1_02_1_sw05");

	 named_switches.addEunetSwitch("me1_01_2_sw01", 24);
	 named_switches.findEunetSwitch("me1_01_2_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("me1_01_2_sw01")->connectUpTo(
	 "me1_02_1_sw05");

	 named_switches.addEunetSwitch("me1_03_1_sw01", 24);
	 named_switches.findEunetSwitch("me1_03_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("me1_03_1_sw01")->connectUpTo(
	 "me1_02_1_sw04");

	 named_switches.addEunetSwitch("me1_03_2_sw01", 48);
	 named_switches.findEunetSwitch("me1_03_2_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("me1_03_2_sw01")->connectUpTo(
	 "me1_02_1_sw04");

	 named_switches.addEunetSwitch("me1_04_1_sw01", 24);
	 named_switches.findEunetSwitch("me1_04_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("me1_04_1_sw01")->connectUpTo(
	 "me1_02_1_sw04");

	 named_switches.addEunetSwitch("me1_05_1_sw01", 24);
	 named_switches.findEunetSwitch("me1_05_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("me1_05_1_sw01")->connectUpTo(
	 "me1_02_1_sw03");

	 named_switches.addEunetSwitch("me1_06_1_sw01", 24);
	 named_switches.findEunetSwitch("me1_06_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("me1_06_1_sw01")->connectUpTo(
	 "me1_02_1_sw03");

	 named_switches.addEunetSwitch("me1_07_1_sw01", 24);
	 named_switches.findEunetSwitch("me1_07_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("me1_07_1_sw01")->connectUpTo(
	 "me1_02_1_sw03");

	 named_switches.addEunetSwitch("me1_08_1_sw01", 24);
	 named_switches.findEunetSwitch("me1_08_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("me1_08_1_sw01")->connectUpTo(
	 "me1_02_1_sw03");

	 named_switches.addEunetSwitch("me1_09_1_sw01", 24);
	 named_switches.findEunetSwitch("me1_09_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("me1_09_1_sw01")->connectUpTo(
	 "me1_02_1_sw03");

	 named_switches.addEunetSwitch("me1_10_1_sw01", 24);
	 named_switches.findEunetSwitch("me1_10_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("me1_10_1_sw01")->connectUpTo(
	 "me1_02_1_sw03");

	 //付属病院2号館
	 named_switches.addEunetSwitch("me2_01_1_sw01", 48);
	 named_switches.findEunetSwitch("me2_01_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("10Gbps"));
	 named_switches.findEunetSwitch("me2_01_1_sw01")->connectUpTo(
	 "me0_02_1_core01");

	 named_switches.addEunetSwitch("me2_01_1_sw02", 24);
	 named_switches.findEunetSwitch("me2_01_1_sw02")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("me2_01_1_sw02")->connectUpTo(
	 "me2_01_1_sw01");

	 named_switches.addEunetSwitch("me2_01_1_sw03", 24);
	 named_switches.findEunetSwitch("me2_01_1_sw03")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("me2_01_1_sw03")->connectUpTo(
	 "me2_01_1_sw01");

	 named_switches.addEunetSwitch("me2_B1_1_sw01", 24);
	 named_switches.findEunetSwitch("me2_B1_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("me2_B1_1_sw01")->connectUpTo(
	 "me2_01_1_sw03");

	 named_switches.addEunetSwitch("me2_03_1_sw01", 48);
	 named_switches.findEunetSwitch("me2_03_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("me2_03_1_sw01")->connectUpTo(
	 "me2_01_1_sw03");

	 named_switches.addEunetSwitch("me2_04_1_sw01", 24);
	 named_switches.findEunetSwitch("me2_04_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("me2_04_1_sw01")->connectUpTo(
	 "me2_01_1_sw03");

	 named_switches.addEunetSwitch("me2_05_1_sw01", 24);
	 named_switches.findEunetSwitch("me2_05_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("me2_05_1_sw01")->connectUpTo(
	 "me2_01_1_sw02");

	 named_switches.addEunetSwitch("me2_06_1_sw01", 24);
	 named_switches.findEunetSwitch("me2_06_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("me2_06_1_sw01")->connectUpTo(
	 "me2_01_1_sw02");

	 named_switches.addEunetSwitch("me2_07_1_sw01", 24);
	 named_switches.findEunetSwitch("me2_07_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("me2_07_1_sw01")->connectUpTo(
	 "me2_01_1_sw02");

	 named_switches.addEunetSwitch("me2_08_1_sw01", 24);
	 named_switches.findEunetSwitch("me2_08_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("me2_08_1_sw01")->connectUpTo(
	 "me2_01_1_sw02");

	 //付属病院病歴棟
	 named_switches.addEunetSwitch("meb_03_1_sw01", 24);
	 named_switches.findEunetSwitch("meb_03_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("meb_03_1_sw01")->connectUpTo(
	 "me0_02_1_core01");

	 //地域医療支援センター
	 named_switches.addEunetSwitch("mels_01_1_sw01", 24);
	 named_switches.findEunetSwitch("mels_01_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("mels_01_1_sw01")->connectUpTo(
	 "me1_02_1_sw01");

	 named_switches.addEunetSwitch("mels_02_1_sw01", 24);
	 named_switches.findEunetSwitch("mels_02_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("mels_02_1_sw01")->connectUpTo(
	 "me1_02_1_sw01");

	 named_switches.addEunetSwitch("mels_03_1_sw01", 24);
	 named_switches.findEunetSwitch("mels_03_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("mels_03_1_sw01")->connectUpTo(
	 "me1_02_1_sw01");

	 //総合学習棟
	 named_switches.addEunetSwitch("melng_02_1_sw01", 72);
	 named_switches.findEunetSwitch("melng_02_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("melng_02_1_sw01")->connectUpTo(
	 "melib_01_1_sw01");

	 //付属病院3号棟
	 named_switches.addEunetSwitch("me3_01_1_sw01", 24);
	 named_switches.findEunetSwitch("me3_01_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("me3_01_1_sw01")->connectUpTo(
	 "me1_02_1_sw01");

	 named_switches.addEunetSwitch("me3_02_1_sw01", 24);
	 named_switches.findEunetSwitch("me3_02_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("me3_02_1_sw01")->connectUpTo(
	 "me1_02_1_sw01");

	 named_switches.addEunetSwitch("me3_03_1_sw01", 24);
	 named_switches.findEunetSwitch("me3_03_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("me3_03_1_sw01")->connectUpTo(
	 "me1_02_1_sw01");

	 //MRI-CT-PET装置棟
	 named_switches.addEunetSwitch("memcp_01_1_sw01", 24);
	 named_switches.findEunetSwitch("memcp_01_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("memcp_01_1_sw01")->connectUpTo(
	 "me1_02_1_sw01");

	 named_switches.addEunetSwitch("memcp_B1_1_sw01", 24);
	 named_switches.findEunetSwitch("memcp_B1_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("memcp_B1_1_sw01")->connectUpTo(
	 "me1_02_1_sw01");

	 //講義棟(東ウイング北)
	 named_switches.addEunetSwitch("mekg_01_1_sw01", 24);
	 named_switches.findEunetSwitch("mekg_01_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("mekg_01_1_sw01")->connectUpTo(
	 "me0_02_1_core01");

	 named_switches.addEunetSwitch("mekg_02_1_sw01", 24);
	 named_switches.findEunetSwitch("mekg_02_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("mekg_02_1_sw01")->connectUpTo(
	 "mekg_01_1_sw01");

	 //講義棟(東ウイング南)
	 named_switches.addEunetSwitch("mekg_01_2_sw01", 24);
	 named_switches.findEunetSwitch("mekg_01_2_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("mekg_01_2_sw01")->connectUpTo(
	 "mekg_01_1_sw01");

	 named_switches.addEunetSwitch("mekg_02_2_sw01", 24);
	 named_switches.findEunetSwitch("mekg_02_2_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("mekg_02_2_sw01")->connectUpTo(
	 "mekg_01_2_sw01");

	 //解剖棟(西ウイング)
	 named_switches.addEunetSwitch("meds_02_1_sw01", 24);
	 named_switches.findEunetSwitch("meds_02_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("meds_02_1_sw01")->connectUpTo(
	 "me0_02_1_core01");

	 named_switches.addEunetSwitch("meds_01_1_sw01", 24);
	 named_switches.findEunetSwitch("meds_01_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("meds_01_1_sw01")->connectUpTo(
	 "meds_02_1_sw01");

	 //職員福利棟
	 named_switches.addEunetSwitch("mesh_01_1_sw01", 24);
	 named_switches.findEunetSwitch("mesh_01_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("mesh_01_1_sw01")->connectUpTo(
	 "me0_02_1_sw01");

	 //看護師宿舎
	 named_switches.addEunetSwitch("ns_01_1_sw01", 24);
	 named_switches.findEunetSwitch("ns_01_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("ns_01_1_sw01")->connectUpTo(
	 "me0_02_1_core01");

	 //外来棟
	 named_switches.addEunetSwitch("meg_01_1_sw01", 48);
	 named_switches.findEunetSwitch("meg_01_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("meg_01_1_sw01")->connectUpTo(
	 "me0_02_1_core01");

	 named_switches.addEunetSwitch("meg_01_2_sw01", 24);
	 named_switches.findEunetSwitch("meg_01_2_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("meg_01_2_sw01")->connectUpTo(
	 "me1_02_1_sw02");

	 named_switches.addEunetSwitch("meg_01_3_sw01", 48);
	 named_switches.findEunetSwitch("meg_01_3_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("meg_01_3_sw01")->connectUpTo(
	 "me1_02_1_sw01");

	 named_switches.addEunetSwitch("meg_01_4_sw01", 48);
	 named_switches.findEunetSwitch("meg_01_4_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("meg_01_4_sw01")->connectUpTo(
	 "me1_02_1_sw01");

	 named_switches.addEunetSwitch("meg_02_1_sw01", 24);
	 named_switches.findEunetSwitch("meg_02_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("meg_02_1_sw01")->connectUpTo(
	 "meg_01_2_sw01");

	 named_switches.addEunetSwitch("meg_02_2_sw01", 48);
	 named_switches.findEunetSwitch("meg_02_2_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("meg_02_2_sw01")->connectUpTo(
	 "me1_02_1_sw01");

	 named_switches.addEunetSwitch("meg_02_3_sw01", 48);
	 named_switches.findEunetSwitch("meg_02_3_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("meg_02_3_sw01")->connectUpTo(
	 "me1_02_1_sw01");

	 named_switches.addEunetSwitch("meg_03_1_sw01", 24);
	 named_switches.findEunetSwitch("meg_03_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("meg_03_1_sw01")->connectUpTo(
	 "me1_02_1_sw02");

	 named_switches.addEunetSwitch("meg_03_2_sw01", 24);
	 named_switches.findEunetSwitch("meg_03_2_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("meg_03_2_sw01")->connectUpTo(
	 "me1_02_1_sw01");

	 named_switches.addEunetSwitch("meg_04_1_sw01", 24);
	 named_switches.findEunetSwitch("meg_04_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("meg_04_1_sw01")->connectUpTo(
	 "me1_02_1_sw01");

	 //コミュニティハウス
	 named_switches.addEunetSwitch("huku_01_1_sw01", 48);
	 named_switches.findEunetSwitch("huku_01_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("huku_01_1_sw01")->connectUpTo(
	 "me2_01_1_sw01");
	 */

	//樽味キャンパスネットワーク
	//農学部2号館
	named_switches.addEunetSwitch("ag2_03_1_core01", 64);
	named_switches.findEunetSwitch("ag2_03_1_core01")->setUplinkDataRate(
			ns3::DataRate("10Gbps"));
	named_switches.findEunetSwitch("ag2_03_1_core01")->connectUpTo("キャンパス間接続L2");

	named_switches.addEunetSwitch("ag2_03_1_sw01", 64);
	named_switches.findEunetSwitch("ag2_03_1_sw01")->setUplinkDataRate(
			ns3::DataRate("10Gbps"));
	named_switches.findEunetSwitch("ag2_03_1_sw01")->connectUpTo("キャンパス間接続L2");

	named_switches.addEunetSwitch("ag2_03_1_sw02", 48);
	named_switches.findEunetSwitch("ag2_03_1_sw02")->setUplinkDataRate(
			ns3::DataRate("10Gbps"));
	named_switches.findEunetSwitch("ag2_03_1_sw02")->connectUpTo(
			"ag2_03_1_core01");

	named_switches.addEunetSwitch("ag2_03_1_sw03", 48);
	named_switches.findEunetSwitch("ag2_03_1_sw03")->setUplinkDataRate(
			ns3::DataRate("10Gbps"));
	named_switches.findEunetSwitch("ag2_03_1_sw03")->connectUpTo(
			"ag2_03_1_core01");

	named_switches.addEunetSwitch("ag2_03_1_sw04", 24);
	named_switches.findEunetSwitch("ag2_03_1_sw04")->setUplinkDataRate(
			ns3::DataRate("1Gbps"));
	named_switches.findEunetSwitch("ag2_03_1_sw04")->connectUpTo(
			"ag2_03_1_sw02");

	named_switches.addEunetSwitch("ag2_03_1_sw05", 24);
	named_switches.findEunetSwitch("ag2_03_1_sw05")->setUplinkDataRate(
			ns3::DataRate("1Gbps"));
	named_switches.findEunetSwitch("ag2_03_1_sw05")->connectUpTo(
			"ag2_03_1_core01");

	named_switches.addEunetSwitch("ag2_03_1_sw06", 24);
	named_switches.findEunetSwitch("ag2_03_1_sw06")->setUplinkDataRate(
			ns3::DataRate("1Gbps"));
	named_switches.findEunetSwitch("ag2_03_1_sw06")->connectUpTo(
			"ag2_03_1_core01");

	named_switches.addEunetSwitch("ag2_03_2_sw01", 48);
	named_switches.findEunetSwitch("ag2_03_2_sw01")->setUplinkDataRate(
			ns3::DataRate("10Gbps"));
	named_switches.findEunetSwitch("ag2_03_2_sw01")->connectUpTo(
			"ag2_03_1_sw01");

	named_switches.addEunetSwitch("ag2_02_2_sw01", 48);
	named_switches.findEunetSwitch("ag2_02_2_sw01")->setUplinkDataRate(
			ns3::DataRate("1Gbps"));
	named_switches.findEunetSwitch("ag2_02_2_sw01")->connectUpTo(
			"ag2_03_1_core01");

	named_switches.addEunetSwitch("ag2_02_2_sw02", 24);
	named_switches.findEunetSwitch("ag2_02_2_sw02")->setUplinkDataRate(
			ns3::DataRate("1Gbps"));
	named_switches.findEunetSwitch("ag2_02_2_sw02")->connectUpTo(
			"ag2_03_2_sw01");

	named_switches.addEunetSwitch("ag2_02_1_sw01", 48);
	named_switches.findEunetSwitch("ag2_02_1_sw01")->setUplinkDataRate(
			ns3::DataRate("1Gbps"));
	named_switches.findEunetSwitch("ag2_02_1_sw01")->connectUpTo(
			"ag2_02_2_sw01");

	//農学部本館(北)
	named_switches.addEunetSwitch("aghn_01_1_sw01", 48);
	named_switches.findEunetSwitch("aghn_01_1_sw01")->setUplinkDataRate(
			ns3::DataRate("10Gbps"));
	named_switches.findEunetSwitch("aghn_01_1_sw01")->connectUpTo(
			"ag2_03_1_core01");

	named_switches.addEunetSwitch("aghn_01_1_sw02", 48);
	named_switches.findEunetSwitch("aghn_01_1_sw02")->setUplinkDataRate(
			ns3::DataRate("1Gbps"));
	named_switches.findEunetSwitch("aghn_01_1_sw02")->connectUpTo(
			"aghn_01_1_sw01");

	named_switches.addEunetSwitch("aghn_02_1_sw01", 48);
	named_switches.findEunetSwitch("aghn_02_1_sw01")->setUplinkDataRate(
			ns3::DataRate("1Gbps"));
	named_switches.findEunetSwitch("aghn_02_1_sw01")->connectUpTo(
			"aghn_01_1_sw01");

	named_switches.addEunetSwitch("aghn_03_1_sw01", 72);
	named_switches.findEunetSwitch("aghn_03_1_sw01")->setUplinkDataRate(
			ns3::DataRate("1Gbps"));
	named_switches.findEunetSwitch("aghn_03_1_sw01")->connectUpTo(
			"aghn_01_1_sw01");

	named_switches.addEunetSwitch("aghn_06_1_sw01", 48);
	named_switches.findEunetSwitch("aghn_06_1_sw01")->setUplinkDataRate(
			ns3::DataRate("1Gbps"));
	named_switches.findEunetSwitch("aghn_06_1_sw01")->connectUpTo(
			"aghn_01_1_sw01");

	named_switches.addEunetSwitch("aghn_06_2_sw01", 48);
	named_switches.findEunetSwitch("aghn_06_2_sw01")->setUplinkDataRate(
			ns3::DataRate("1Gbps"));
	named_switches.findEunetSwitch("aghn_06_2_sw01")->connectUpTo(
			"aghn_06_1_sw01");

	named_switches.addEunetSwitch("aghn_05_1_sw01", 48);
	named_switches.findEunetSwitch("aghn_05_1_sw01")->setUplinkDataRate(
			ns3::DataRate("1Gbps"));
	named_switches.findEunetSwitch("aghn_05_1_sw01")->connectUpTo(
			"aghn_06_1_sw01");

	named_switches.addEunetSwitch("aghn_04_1_sw01", 72);
	named_switches.findEunetSwitch("aghn_04_1_sw01")->setUplinkDataRate(
			ns3::DataRate("1Gbps"));
	named_switches.findEunetSwitch("aghn_04_1_sw01")->connectUpTo(
			"aghn_06_1_sw01");

	//農学部3号館
	named_switches.addEunetSwitch("ag3_04_1_sw01", 48);
	named_switches.findEunetSwitch("ag3_04_1_sw01")->setUplinkDataRate(
			ns3::DataRate("10Gbps"));
	named_switches.findEunetSwitch("ag3_04_1_sw01")->connectUpTo(
			"ag2_03_1_core01");

	named_switches.addEunetSwitch("ag3_04_1_sw02", 48);
	named_switches.findEunetSwitch("ag3_04_1_sw02")->setUplinkDataRate(
			ns3::DataRate("1Gbps"));
	named_switches.findEunetSwitch("ag3_04_1_sw02")->connectUpTo(
			"ag3_04_1_sw01");

	named_switches.addEunetSwitch("ag3_03_1_sw01", 24);
	named_switches.findEunetSwitch("ag3_03_1_sw01")->setUplinkDataRate(
			ns3::DataRate("1Gbps"));
	named_switches.findEunetSwitch("ag3_03_1_sw01")->connectUpTo(
			"ag3_04_1_sw01");

	named_switches.addEunetSwitch("ag3_02_1_sw01", 24);
	named_switches.findEunetSwitch("ag3_02_1_sw01")->setUplinkDataRate(
			ns3::DataRate("1Gbps"));
	named_switches.findEunetSwitch("ag3_02_1_sw01")->connectUpTo(
			"ag3_04_1_sw01");

	named_switches.addEunetSwitch("ag3_02_2_sw01", 24);
	named_switches.findEunetSwitch("ag3_02_2_sw01")->setUplinkDataRate(
			ns3::DataRate("1Gbps"));
	named_switches.findEunetSwitch("ag3_02_2_sw01")->connectUpTo(
			"ag3_04_1_sw01");

	named_switches.addEunetSwitch("ag3_01_1_sw01", 24);
	named_switches.findEunetSwitch("ag3_01_1_sw01")->setUplinkDataRate(
			ns3::DataRate("1Gbps"));
	named_switches.findEunetSwitch("ag3_01_1_sw01")->connectUpTo(
			"ag3_04_1_sw01");

	named_switches.addEunetSwitch("ag3_05_1_sw01", 24);
	named_switches.findEunetSwitch("ag3_05_1_sw01")->setUplinkDataRate(
			ns3::DataRate("1Gbps"));
	named_switches.findEunetSwitch("ag3_05_1_sw01")->connectUpTo(
			"ag3_04_1_sw01");

	named_switches.addEunetSwitch("ag3_05_2_sw01", 24);
	named_switches.findEunetSwitch("ag3_05_2_sw01")->setUplinkDataRate(
			ns3::DataRate("1Gbps"));
	named_switches.findEunetSwitch("ag3_05_2_sw01")->connectUpTo(
			"ag3_04_1_sw01");

	//総合科学研究支援センター
	named_switches.addEunetSwitch("ags_02_1_sw01", 48);
	named_switches.findEunetSwitch("ags_02_1_sw01")->setUplinkDataRate(
			ns3::DataRate("1Gbps"));
	named_switches.findEunetSwitch("ags_02_1_sw01")->connectUpTo(
			"ag2_03_1_sw01");

	//三科実験室
	named_switches.addEunetSwitch("agm_01_1_sw01", 48);
	named_switches.findEunetSwitch("agm_01_1_sw01")->setUplinkDataRate(
			ns3::DataRate("1Gbps"));
	named_switches.findEunetSwitch("agm_01_1_sw01")->connectUpTo(
			"ag2_03_1_sw01");

	//連合農学研究科
	named_switches.addEunetSwitch("agr_02_1_sw01", 48);
	named_switches.findEunetSwitch("agr_02_1_sw01")->setUplinkDataRate(
			ns3::DataRate("1Gbps"));
	named_switches.findEunetSwitch("agr_02_1_sw01")->connectUpTo(
			"ag2_03_1_sw01");

	named_switches.addEunetSwitch("agr_03_1_sw01", 48);
	named_switches.findEunetSwitch("agr_03_1_sw01")->setUplinkDataRate(
			ns3::DataRate("1Gbps"));
	named_switches.findEunetSwitch("agr_03_1_sw01")->connectUpTo(
			"agr_02_1_sw01");

	named_switches.addEunetSwitch("agr_01_1_sw01", 24);
	named_switches.findEunetSwitch("agr_01_1_sw01")->setUplinkDataRate(
			ns3::DataRate("1Gbps"));
	named_switches.findEunetSwitch("agr_01_1_sw01")->connectUpTo(
			"agr_02_1_sw01");

	//ユーカリ会館
	named_switches.addEunetSwitch("agu_02_1_sw01", 24);
	named_switches.findEunetSwitch("agu_02_1_sw01")->setUplinkDataRate(
			ns3::DataRate("1Gbps"));
	named_switches.findEunetSwitch("agu_02_1_sw01")->connectUpTo(
			"agr_02_1_sw01");

	//附属高校校舎(南)
	named_switches.addEunetSwitch("agfs_01_1_sw01", 24);
	named_switches.findEunetSwitch("agfs_01_1_sw01")->setUplinkDataRate(
			ns3::DataRate("1Gbps"));
	named_switches.findEunetSwitch("agfs_01_1_sw01")->connectUpTo(
			"ag2_03_1_sw01");

	named_switches.addEunetSwitch("agfs_01_1_sw02", 48);
	named_switches.findEunetSwitch("agfs_01_1_sw02")->setUplinkDataRate(
			ns3::DataRate("10Gbps"));
	named_switches.findEunetSwitch("agfs_01_1_sw02")->connectUpTo(
			"ag2_03_1_sw01");

	named_switches.addEunetSwitch("agfs_05_1_sw01", 24);
	named_switches.findEunetSwitch("agfs_05_1_sw01")->setUplinkDataRate(
			ns3::DataRate("1Gbps"));
	named_switches.findEunetSwitch("agfs_05_1_sw01")->connectUpTo(
			"ag2_03_1_sw01");

	named_switches.addEunetSwitch("agfs_05_1_sw02", 48);
	named_switches.findEunetSwitch("agfs_05_1_sw02")->setUplinkDataRate(
			ns3::DataRate("10Gbps"));
	named_switches.findEunetSwitch("agfs_05_1_sw02")->connectUpTo(
			"ag2_03_1_sw01");

	//附属高校舎（北）
	named_switches.addEunetSwitch("agfn_03_1_sw01", 48);
	named_switches.findEunetSwitch("agfn_03_1_sw01")->setUplinkDataRate(
			ns3::DataRate("10Gbps"));
	named_switches.findEunetSwitch("agfn_03_1_sw01")->connectUpTo(
			"ag2_03_1_core01");

	//環境産業研究施設
	named_switches.addEunetSwitch("agk_01_1_sw01", 24);
	named_switches.findEunetSwitch("agk_01_1_sw01")->setUplinkDataRate(
			ns3::DataRate("1Gbps"));
	named_switches.findEunetSwitch("agk_01_1_sw01")->connectUpTo(
			"ag2_03_1_sw01");

	//農学部本館（南）
	named_switches.addEunetSwitch("aghs_03_1_sw01", 48);
	named_switches.findEunetSwitch("aghs_03_1_sw01")->setUplinkDataRate(
			ns3::DataRate("10Gbps"));
	named_switches.findEunetSwitch("aghs_03_1_sw01")->connectUpTo(
			"ag2_03_1_core01");

	named_switches.addEunetSwitch("aghs_03_1_sw02", 48);
	named_switches.findEunetSwitch("aghs_03_1_sw02")->setUplinkDataRate(
			ns3::DataRate("1Gbps"));
	named_switches.findEunetSwitch("aghs_03_1_sw02")->connectUpTo(
			"aghs_03_1_sw01");

	named_switches.addEunetSwitch("aghs_02_1_sw01", 48);
	named_switches.findEunetSwitch("aghs_02_1_sw01")->setUplinkDataRate(
			ns3::DataRate("1Gbps"));
	named_switches.findEunetSwitch("aghs_02_1_sw01")->connectUpTo(
			"aghs_03_1_sw01");

	named_switches.addEunetSwitch("aghs_02_2_sw01", 24);
	named_switches.findEunetSwitch("aghs_02_2_sw01")->setUplinkDataRate(
			ns3::DataRate("1Gbps"));
	named_switches.findEunetSwitch("aghs_02_2_sw01")->connectUpTo(
			"aghs_03_1_sw01");

	named_switches.addEunetSwitch("aghs_01_1_sw01", 48);
	named_switches.findEunetSwitch("aghs_01_1_sw01")->setUplinkDataRate(
			ns3::DataRate("1Gbps"));
	named_switches.findEunetSwitch("aghs_01_1_sw01")->connectUpTo(
			"aghs_03_1_sw01");

	named_switches.addEunetSwitch("aghs_04_1_sw01", 72);
	named_switches.findEunetSwitch("aghs_04_1_sw01")->setUplinkDataRate(
			ns3::DataRate("1Gbps"));
	named_switches.findEunetSwitch("aghs_04_1_sw01")->connectUpTo(
			"aghs_03_1_sw01");

	named_switches.addEunetSwitch("aghs_05_1_sw01", 48);
	named_switches.findEunetSwitch("aghs_05_1_sw01")->setUplinkDataRate(
			ns3::DataRate("1Gbps"));
	named_switches.findEunetSwitch("aghs_05_1_sw01")->connectUpTo(
			"aghs_03_1_sw01");

	//植物工場棟
	named_switches.addEunetSwitch("agp_02_1_sw01", 48);
	named_switches.findEunetSwitch("agp_02_1_sw01")->setUplinkDataRate(
			ns3::DataRate("1Gbps"));
	named_switches.findEunetSwitch("agp_02_1_sw01")->connectUpTo(
			"agk_01_1_sw01");

	//農学部制御化実験施設
	named_switches.addEunetSwitch("agce_01_1_sw01", 24);
	named_switches.findEunetSwitch("agce_01_1_sw01")->setUplinkDataRate(
			ns3::DataRate("1Gbps"));
	named_switches.findEunetSwitch("agce_01_1_sw01")->connectUpTo(
			"ag3_02_1_sw01");

	//附属高校（中_北）2棟 廊下
	named_switches.addEunetSwitch("agfcn_02_1_sw01", 48);
	named_switches.findEunetSwitch("agfcn_02_1_sw01")->setUplinkDataRate(
			ns3::DataRate("1Gbps"));
	named_switches.findEunetSwitch("agfcn_02_1_sw01")->connectUpTo(
			"agfn_03_1_sw01");

	/*
	 //持田キャンパス
	 //附属小学校校舎（事務室）
	 named_switches.addEunetSwitch("syou_01_2_sw01", 24);
	 named_switches.findEunetSwitch("syou_01_2_sw01")->setUplinkDataRate(
	 ns3::DataRate("10Gbps"));
	 named_switches.findEunetSwitch("syou_01_2_sw01")->connectUpTo("キャンパス間接続L2");

	 //附属小学校・センター棟
	 named_switches.addEunetSwitch("syou_01_1_core01", 72);
	 named_switches.findEunetSwitch("syou_01_1_core01")->setUplinkDataRate(
	 ns3::DataRate("10Gbps"));
	 named_switches.findEunetSwitch("syou_01_1_core01")->connectUpTo(
	 "syou_01_2_sw01");

	 named_switches.addEunetSwitch("syou_01_1_sw01", 48);
	 named_switches.findEunetSwitch("syou_01_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("syou_01_1_sw01")->connectUpTo(
	 "syou_01_1_core01");

	 //附属小学校校舎（視聴覚室）
	 named_switches.addEunetSwitch("syou_02_1_sw01", 24);
	 named_switches.findEunetSwitch("syou_02_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("syou_02_1_sw01")->connectUpTo(
	 "syou_01_1_core01");

	 named_switches.addEunetSwitch("syou_02_1_sw02", 48);
	 named_switches.findEunetSwitch("syou_02_1_sw02")->setUplinkDataRate(
	 ns3::DataRate("10Gbps"));
	 named_switches.findEunetSwitch("syou_02_1_sw02")->connectUpTo(
	 "syou_01_1_core01");

	 //附属中学校本館
	 named_switches.addEunetSwitch("tyuu_01_1_sw02", 48);
	 named_switches.findEunetSwitch("tyuu_01_1_sw02")->setUplinkDataRate(
	 ns3::DataRate("10Gbps"));
	 named_switches.findEunetSwitch("tyuu_01_1_sw02")->connectUpTo(
	 "syou_01_1_core01");

	 named_switches.addEunetSwitch("tyuu_01_1_sw01", 24);
	 named_switches.findEunetSwitch("tyuu_01_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("tyuu_01_1_sw01")->connectUpTo(
	 "syou_01_1_sw01");

	 named_switches.addEunetSwitch("tyuu_02_1_sw01", 24);
	 named_switches.findEunetSwitch("tyuu_02_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("tyuu_02_1_sw01")->connectUpTo(
	 "syou_01_1_sw01");

	 //附属特別支援学校校舎
	 named_switches.addEunetSwitch("yougo_02_1_sw01", 24);
	 named_switches.findEunetSwitch("yougo_02_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("10Gbps"));
	 named_switches.findEunetSwitch("yougo_02_1_sw01")->connectUpTo(
	 "syou_01_1_sw01");

	 named_switches.addEunetSwitch("yougo_01_1_sw01", 24);
	 named_switches.findEunetSwitch("yougo_01_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("yougo_01_1_sw01")->connectUpTo(
	 "yougo_02_1_sw01");

	 //附属幼稚園本館
	 named_switches.addEunetSwitch("youchi_01_1_sw01", 24);
	 named_switches.findEunetSwitch("youchi_01_1_sw01")->setUplinkDataRate(
	 ns3::DataRate("1Gbps"));
	 named_switches.findEunetSwitch("youchi_01_1_sw01")->connectUpTo(
	 "syou_01_1_sw01");
	 */
}

EunetSimulation::~EunetSimulation() {
}

int EunetSimulation::run() {
	NS_LOG_INFO("Run Simulation.");
	ns3::Simulator::Stop(ns3::Seconds(0.1));
	ns3::Simulator::Run();
	ns3::Simulator::Destroy();
	NS_LOG_INFO("Done.");
	//this->sourceTerminal->logTotalRx();
	//this->destTerminal->logTotalRx();
	return EXIT_SUCCESS;
}

int main(int argc, char** argv) {
	ns3::CommandLine command_line;
	command_line.Parse(argc, argv);
	EunetSimulation eunet_simulation;
	auto r = eunet_simulation.run();
	NS_LOG_UNCOND("EunetSimulation finished.");
	return r;
}
