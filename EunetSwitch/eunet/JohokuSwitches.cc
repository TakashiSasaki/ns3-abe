#define NS3_LOG_ENABLE 1
#include "ns3/log.h"
NS_LOG_COMPONENT_DEFINE ("JohokuSwitches");
#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/applications-module.h"
#include "ns3/bridge-module.h"
#include "ns3/csma-module.h"
#include "ns3/internet-module.h"
#include "ns3/internet-stack-helper.h"
#include "ns3/netanim-module.h"
//#include "EunetSimulation.h"
#include "EunetSwitches.h"
#include "EunetTerminal.h"
#include "NamedSwitches.h"
#include "JohokuSwitches.h"

JohokuSwitches::JohokuSwitches():
    NamedSwitches("133.71.0.0", "255.255.0.0") {
    ns3::AnimationInterface animation_interface("EunetSimulation.xml");
    //NamedSwitches named_switches("133.71.0.0", "255.255.0.0");
    this->addEunetSwitch("キャンパス間接続L2", 64);

    //城北キャンパスネットワーク
    this->addEunetSwitch("dpc_02_core01", 64);
    this->findEunetSwitch("dpc_02_core01")->setUplinkDataRate(
        ns3::DataRate("10Gbps"));
    this->findEunetSwitch("dpc_02_core01")->connectUpTo("キャンパス間接続L2");

    this->addEunetSwitch("dpc_02_01_sw01", 64);
    this->findEunetSwitch("dpc_02_01_sw01")->setUplinkDataRate(
        ns3::DataRate("10Gbps"));
    this->findEunetSwitch("dpc_02_01_sw01")->connectUpTo("キャンパス間接続L2");

    this->addEunetSwitch("dpc_02_01_sw02", 64);
    this->findEunetSwitch("dpc_02_01_sw02")->setUplinkDataRate(
        ns3::DataRate("10Gbps"));
    this->findEunetSwitch("dpc_02_01_sw02")->connectUpTo("キャンパス間接続L2");

    this->addEunetSwitch("dpc_02_01_sw03", 64);
    this->findEunetSwitch("dpc_02_01_sw03")->setUplinkDataRate(
        ns3::DataRate("10Gbps"));
    this->findEunetSwitch("dpc_02_01_sw03")->connectUpTo("キャンパス間接続L2");

    this->addEunetSwitch("dpc_04_1_sw01", 48);
    this->findEunetSwitch("dpc_04_1_sw01")->setUplinkDataRate(
        ns3::DataRate("10Gbps"));
    this->findEunetSwitch("dpc_04_1_sw01")->connectUpTo(
        "dpc_02_01_sw02");

    this->addEunetSwitch("dpc_04_1_sw02", 24);
    this->findEunetSwitch("dpc_04_1_sw02")->setUplinkDataRate(
        ns3::DataRate("10Gbps"));
    this->findEunetSwitch("dpc_04_1_sw02")->connectUpTo(
        "dpc_02_01_sw02");

    this->addEunetSwitch("dpc_04_2_sw01", 48);
    this->findEunetSwitch("dpc_04_2_sw01")->setUplinkDataRate(
        ns3::DataRate("10Gbps"));
    this->findEunetSwitch("dpc_04_2_sw01")->connectUpTo(
        "dpc_02_01_sw02");

    this->addEunetSwitch("dpc_04_2_sw02", 24);
    this->findEunetSwitch("dpc_04_2_sw02")->setUplinkDataRate(
        ns3::DataRate("10Gbps"));
    this->findEunetSwitch("dpc_04_2_sw02")->connectUpTo(
        "dpc_02_01_sw02");

    this->addEunetSwitch("dpc_04_3_sw01", 24);
    this->findEunetSwitch("dpc_04_3_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("dpc_04_3_sw01")->connectUpTo(
        "dpc_02_core01");

    this->addEunetSwitch("dpc_03_1_sw01", 48);
    this->findEunetSwitch("dpc_03_1_sw01")->setUplinkDataRate(
        ns3::DataRate("10Gbps"));
    this->findEunetSwitch("dpc_03_1_sw01")->connectUpTo(
        "dpc_02_01_sw02");

    this->addEunetSwitch("dpc_03_1_sw02", 24);
    this->findEunetSwitch("dpc_03_1_sw02")->setUplinkDataRate(
        ns3::DataRate("10Gbps"));
    this->findEunetSwitch("dpc_03_1_sw02")->connectUpTo(
        "dpc_02_01_sw02");

    this->addEunetSwitch("dpc_03_2_sw01", 48);
    this->findEunetSwitch("dpc_03_2_sw01")->setUplinkDataRate(
        ns3::DataRate("10Gbps"));
    this->findEunetSwitch("dpc_03_2_sw01")->connectUpTo(
        "dpc_02_01_sw02");

    this->addEunetSwitch("dpc_03_2_sw02", 48);
    this->findEunetSwitch("dpc_03_2_sw02")->setUplinkDataRate(
        ns3::DataRate("10Gbps"));
    this->findEunetSwitch("dpc_03_2_sw02")->connectUpTo(
        "dpc_02_01_sw02");

    this->addEunetSwitch("dpc_02_2_sw01", 48);
    this->findEunetSwitch("dpc_02_2_sw01")->setUplinkDataRate(
        ns3::DataRate("10Gbps"));
    this->findEunetSwitch("dpc_02_2_sw01")->connectUpTo(
        "dpc_02_01_sw02");

    this->addEunetSwitch("dpc_02_2_sw02", 24);
    this->findEunetSwitch("dpc_02_2_sw02")->setUplinkDataRate(
        ns3::DataRate("10Gbps"));
    this->findEunetSwitch("dpc_02_2_sw02")->connectUpTo(
        "dpc_02_01_sw02");

    this->addEunetSwitch("dpc_02_3_sw01", 48);
    this->findEunetSwitch("dpc_02_3_sw01")->setUplinkDataRate(
        ns3::DataRate("10Gbps"));
    this->findEunetSwitch("dpc_02_3_sw01")->connectUpTo(
        "dpc_02_01_sw02");

    this->addEunetSwitch("dpc_02_3_sw02", 24);
    this->findEunetSwitch("dpc_02_3_sw02")->setUplinkDataRate(
        ns3::DataRate("10Gbps"));
    this->findEunetSwitch("dpc_02_3_sw02")->connectUpTo(
        "dpc_02_01_sw02");

    this->addEunetSwitch("dpc_02_4_sw01", 48);
    this->findEunetSwitch("dpc_02_4_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("dpc_02_4_sw01")->connectUpTo(
        "dpc_02_core01");

    this->addEunetSwitch("dpc_02_4_sw02", 24);
    this->findEunetSwitch("dpc_02_4_sw02")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("dpc_02_4_sw02")->connectUpTo(
        "dpc_02_4_sw01");

    this->addEunetSwitch("dpc_01_2_sw01", 48);
    this->findEunetSwitch("dpc_01_2_sw01")->setUplinkDataRate(
        ns3::DataRate("10Gbps"));
    this->findEunetSwitch("dpc_01_2_sw01")->connectUpTo(
        "dpc_02_01_sw02");

    this->addEunetSwitch("dpc_01_1_sw01", 48);
    this->findEunetSwitch("dpc_01_1_sw01")->setUplinkDataRate(
        ns3::DataRate("10Gbps"));
    this->findEunetSwitch("dpc_01_1_sw01")->connectUpTo(
        "dpc_02_core01");

    this->addEunetSwitch("dpc_01_1_sw02", 48);
    this->findEunetSwitch("dpc_01_1_sw02")->setUplinkDataRate(
        ns3::DataRate("10Gbps"));
    this->findEunetSwitch("dpc_01_1_sw02")->connectUpTo(
        "dpc_01_1_sw01");

    this->addEunetSwitch("dpc_01_3_sw01", 24);
    this->findEunetSwitch("dpc_01_3_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("dpc_01_3_sw01")->connectUpTo(
        "dpc_02_4_sw01");

    this->addEunetSwitch("dpc_01_4_sw01", 24);
    this->findEunetSwitch("dpc_01_4_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("dpc_01_4_sw01")->connectUpTo(
        "dpc_02_core01");

    this->addEunetSwitch("en1_01_1_sw01", 24);
    this->findEunetSwitch("en1_01_1_sw01")->setUplinkDataRate(
        ns3::DataRate("10Gbps"));
    this->findEunetSwitch("en1_01_1_sw01")->connectUpTo(
        "dpc_02_core01");

    this->addEunetSwitch("en1_02_1_sw01", 48);
    this->findEunetSwitch("en1_02_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("en1_02_1_sw01")->connectUpTo(
        "en1_01_1_sw01");

    this->addEunetSwitch("en1_04_1_sw01", 48);
    this->findEunetSwitch("en1_04_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("en1_04_1_sw01")->connectUpTo(
        "en1_01_1_sw01");

    this->addEunetSwitch("en1_06_1_sw01", 48);
    this->findEunetSwitch("en1_06_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("en1_06_1_sw01")->connectUpTo(
        "en1_01_1_sw01");

    this->addEunetSwitch("enh_02_1_sw01", 24);
    this->findEunetSwitch("enh_02_1_sw01")->setUplinkDataRate(
        ns3::DataRate("10Gbps"));
    this->findEunetSwitch("enh_02_1_sw01")->connectUpTo(
        "dpc_02_core01");

    this->addEunetSwitch("enh_02_1_sw02", 24);
    this->findEunetSwitch("enh_02_1_sw02")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("enh_02_1_sw02")->connectUpTo(
        "enh_02_1_sw01");

    this->addEunetSwitch("enh_02_1_sw03", 24);
    this->findEunetSwitch("enh_02_1_sw03")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("enh_02_1_sw03")->connectUpTo(
        "enh_02_1_sw01");

    this->addEunetSwitch("enh_01_1_sw01", 24);
    this->findEunetSwitch("enh_01_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("enh_01_1_sw01")->connectUpTo(
        "enh_02_1_sw01");

    this->addEunetSwitch("enh_08_1_sw01", 48);
    this->findEunetSwitch("enh_08_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("enh_08_1_sw01")->connectUpTo(
        "enh_02_1_sw01");

    this->addEunetSwitch("enh_07_1_sw01", 48);
    this->findEunetSwitch("enh_07_1_sw01")->setUplinkDataRate(
        ns3::DataRate("10Gbps"));
    this->findEunetSwitch("enh_07_1_sw01")->connectUpTo(
        "enh_02_1_sw01");

    this->addEunetSwitch("enh_06_1_sw01", 72);
    this->findEunetSwitch("enh_06_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("enh_06_1_sw01")->connectUpTo(
        "enh_02_1_sw01");

    this->addEunetSwitch("enh_04_1_sw01", 24);
    this->findEunetSwitch("enh_04_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("enh_04_1_sw01")->connectUpTo(
        "enh_02_1_sw01");

    this->addEunetSwitch("enh_03_1_sw01", 48);
    this->findEunetSwitch("enh_03_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("enh_03_1_sw01")->connectUpTo(
        "enh_02_1_sw01");

    this->addEunetSwitch("en2_01_1_sw01", 48);
    this->findEunetSwitch("en2_01_1_sw01")->setUplinkDataRate(
        ns3::DataRate("10Gbps"));
    this->findEunetSwitch("en2_01_1_sw01")->connectUpTo(
        "dpc_02_core01");

    this->addEunetSwitch("en2_01_1_sw02", 24);
    this->findEunetSwitch("en2_01_1_sw02")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("en2_01_1_sw02")->connectUpTo(
        "en2_01_1_sw01");

    this->addEunetSwitch("en2_02_1_sw01", 72);
    this->findEunetSwitch("en2_02_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("en2_02_1_sw01")->connectUpTo(
        "en2_01_1_sw01");

    this->addEunetSwitch("en2_03_1_sw01", 72);
    this->findEunetSwitch("en2_03_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("en2_03_1_sw01")->connectUpTo(
        "en2_01_1_sw01");

    this->addEunetSwitch("en2_04_1_sw01", 72);
    this->findEunetSwitch("en2_04_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("en2_04_1_sw01")->connectUpTo(
        "en2_01_1_sw01");

    this->addEunetSwitch("en2_05_1_sw01", 48);
    this->findEunetSwitch("en2_05_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("en2_05_1_sw01")->connectUpTo(
        "en2_01_1_sw01");

    this->addEunetSwitch("en2_05_1_sw02", 48);
    this->findEunetSwitch("en2_05_1_sw02")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("en2_05_1_sw02")->connectUpTo(
        "en2_01_1_sw01");

    this->addEunetSwitch("en2_06_1_sw01", 48);
    this->findEunetSwitch("en2_06_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("en2_06_1_sw01")->connectUpTo(
        "en2_01_1_sw01");

    this->addEunetSwitch("en3_03_1_sw01", 72);
    this->findEunetSwitch("en3_03_1_sw01")->setUplinkDataRate(
        ns3::DataRate("10Gbps"));
    this->findEunetSwitch("en3_03_1_sw01")->connectUpTo(
        "dpc_02_core01");

    this->addEunetSwitch("en3_03_1_sw02", 24);
    this->findEunetSwitch("en3_03_1_sw02")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("en3_03_1_sw02")->connectUpTo(
        "en3_03_1_sw01");

    this->addEunetSwitch("en4_03_1_sw01", 48);
    this->findEunetSwitch("en4_03_1_sw01")->setUplinkDataRate(
        ns3::DataRate("10Gbps"));
    this->findEunetSwitch("en4_03_1_sw01")->connectUpTo(
        "dpc_02_core01");

    this->addEunetSwitch("en4_07_1_sw01", 48);
    this->findEunetSwitch("en4_07_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("en4_07_1_sw01")->connectUpTo(
        "en4_03_1_sw01");

    this->addEunetSwitch("en4_07_1_sw02", 48);
    this->findEunetSwitch("en4_07_1_sw02")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("en4_07_1_sw02")->connectUpTo(
        "en4_03_1_sw01");

    this->addEunetSwitch("en5_01_1_sw01", 24);
    this->findEunetSwitch("en5_01_1_sw01")->setUplinkDataRate(
        ns3::DataRate("10Gbps"));
    this->findEunetSwitch("en5_01_1_sw01")->connectUpTo(
        "dpc_02_core01");

    this->addEunetSwitch("en5_01_1_sw02", 24);
    this->findEunetSwitch("en5_01_1_sw02")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("en5_01_1_sw02")->connectUpTo(
        "en5_01_1_sw01");

    this->addEunetSwitch("en5_01_1_sw03", 24);
    this->findEunetSwitch("en5_01_1_sw03")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("en5_01_1_sw03")->connectUpTo(
        "en5_01_1_sw01");

    this->addEunetSwitch("en5_02_1_sw01", 24);
    this->findEunetSwitch("en5_02_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("en5_02_1_sw01")->connectUpTo(
        "en5_01_1_sw03");

    this->addEunetSwitch("en5_03_1_sw01", 24);
    this->findEunetSwitch("en5_03_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("en5_03_1_sw01")->connectUpTo(
        "en5_01_1_sw03");

    this->addEunetSwitch("en5_04_1_sw01", 48);
    this->findEunetSwitch("en5_04_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("en5_04_1_sw01")->connectUpTo(
        "en5_01_1_sw03");

    this->addEunetSwitch("en5_05_1_sw01", 24);
    this->findEunetSwitch("en5_05_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("en5_05_1_sw01")->connectUpTo(
        "en5_01_1_sw03");

    this->addEunetSwitch("en5_06_1_sw01", 24);
    this->findEunetSwitch("en5_06_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("en5_06_1_sw01")->connectUpTo(
        "en5_01_1_sw03");

    this->addEunetSwitch("en5_07_1_sw01", 48);
    this->findEunetSwitch("en5_07_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("en5_07_1_sw01")->connectUpTo(
        "en5_01_1_sw02");

    this->addEunetSwitch("en5_08_1_sw01", 48);
    this->findEunetSwitch("en5_08_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("en5_08_1_sw01")->connectUpTo(
        "en5_01_1_sw02");

    this->addEunetSwitch("en5_09_1_sw01", 48);
    this->findEunetSwitch("en5_09_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("en5_09_1_sw01")->connectUpTo(
        "en5_01_1_sw02");

    this->addEunetSwitch("en5_10_1_sw01", 48);
    this->findEunetSwitch("en5_10_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("en5_10_1_sw01")->connectUpTo(
        "en5_01_1_sw02");

    this->addEunetSwitch("en02_01_1_sw01", 48);
    this->findEunetSwitch("en02_01_1_sw01")->setUplinkDataRate(
        ns3::DataRate("10Gbps"));
    this->findEunetSwitch("en02_01_1_sw01")->connectUpTo(
        "dpc_02_core01");

    this->addEunetSwitch("en02_01_1_sw02", 48);
    this->findEunetSwitch("en02_01_1_sw02")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("en02_01_1_sw02")->connectUpTo(
        "en02_01_1_sw01");

    this->addEunetSwitch("en02_02_1_sw01", 72);
    this->findEunetSwitch("en02_02_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("en02_02_1_sw01")->connectUpTo(
        "en02_01_1_sw01");

    this->addEunetSwitch("en02_02_1_sw02", 72);
    this->findEunetSwitch("en02_02_1_sw02")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("en02_02_1_sw02")->connectUpTo(
        "en02_01_1_sw02");

    this->addEunetSwitch("en02_03_1_sw01", 48);
    this->findEunetSwitch("en02_03_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("en02_03_1_sw01")->connectUpTo(
        "en02_01_1_sw02");

    this->addEunetSwitch("en02_03_1_sw02", 48);
    this->findEunetSwitch("en02_03_1_sw02")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("en02_03_1_sw02")->connectUpTo(
        "en02_03_1_sw01");

    this->addEunetSwitch("en02_03_1_sw03", 48);
    this->findEunetSwitch("en02_03_1_sw03")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("en02_03_1_sw03")->connectUpTo(
        "en02_03_1_sw01");

    this->addEunetSwitch("en02_03_1_sw04", 48);
    this->findEunetSwitch("en02_03_1_sw04")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("en02_03_1_sw04")->connectUpTo(
        "en02_03_1_sw01");

    this->addEunetSwitch("en02_04_1_sw01", 48);
    this->findEunetSwitch("en02_04_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("en02_04_1_sw01")->connectUpTo(
        "en02_01_1_sw02");

    this->addEunetSwitch("en02_04_1_sw02", 48);
    this->findEunetSwitch("en02_04_1_sw02")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("en02_04_1_sw02")->connectUpTo(
        "en02_04_1_sw01");

    this->addEunetSwitch("en02_04_1_sw03", 48);
    this->findEunetSwitch("en02_04_1_sw03")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("en02_04_1_sw03")->connectUpTo(
        "en02_04_1_sw01");

    this->addEunetSwitch("en02_04_1_sw04", 48);
    this->findEunetSwitch("en02_04_1_sw04")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("en02_04_1_sw04")->connectUpTo(
        "en02_04_1_sw01");

    this->addEunetSwitch("enk_04_1_sw01", 96);
    this->findEunetSwitch("enk_04_1_sw01")->setUplinkDataRate(
        ns3::DataRate("10Gbps"));
    this->findEunetSwitch("enk_04_1_sw01")->connectUpTo(
        "dpc_02_01_sw01");

    this->addEunetSwitch("enk_01_1_sw01", 48);
    this->findEunetSwitch("enk_01_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("enk_01_1_sw01")->connectUpTo(
        "en02_01_1_sw01");

    this->addEunetSwitch("eng_01_1_sw01", 48);
    this->findEunetSwitch("eng_01_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("eng_01_1_sw01")->connectUpTo(
        "en02_01_1_sw02");

    this->addEunetSwitch("sche_01_1_sw01", 48);
    this->findEunetSwitch("sche_01_1_sw01")->setUplinkDataRate(
        ns3::DataRate("10Gbps"));
    this->findEunetSwitch("sche_01_1_sw01")->connectUpTo(
        "dpc_02_core01");

    this->addEunetSwitch("sche_01_1_sw02", 24);
    this->findEunetSwitch("sche_01_1_sw02")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("sche_01_1_sw02")->connectUpTo(
        "sche_01_1_sw01");

    this->addEunetSwitch("sche_01_2_sw01", 48);
    this->findEunetSwitch("sche_01_2_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("sche_01_2_sw01")->connectUpTo(
        "sche_01_1_sw01");

    this->addEunetSwitch("sche_02_1_sw01", 48);
    this->findEunetSwitch("sche_02_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("sche_02_1_sw01")->connectUpTo(
        "sche_01_1_sw01");

    this->addEunetSwitch("sche_03_1_sw01", 48);
    this->findEunetSwitch("sche_03_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("sche_03_1_sw01")->connectUpTo(
        "sche_01_1_sw01");

    this->addEunetSwitch("sche_04_1_sw01", 48);
    this->findEunetSwitch("sche_04_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("sche_04_1_sw01")->connectUpTo(
        "sche_01_1_sw01");

    this->addEunetSwitch("sche_05_1_sw01", 48);
    this->findEunetSwitch("sche_05_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("sche_05_1_sw01")->connectUpTo(
        "sche_01_1_sw01");

    this->addEunetSwitch("sche_05_2_sw01", 48);
    this->findEunetSwitch("sche_05_2_sw01")->setUplinkDataRate(
        ns3::DataRate("10Gbps"));
    this->findEunetSwitch("sche_05_2_sw01")->connectUpTo(
        "dpc_02_01_sw01");

    this->addEunetSwitch("sc2_01_1_sw01", 48);
    this->findEunetSwitch("sc2_01_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("sc2_01_1_sw01")->connectUpTo(
        "sche_01_1_sw01");

    this->addEunetSwitch("sc2_02_1_sw01", 24);
    this->findEunetSwitch("sc2_02_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("sc2_02_1_sw01")->connectUpTo(
        "sc2_01_1_sw01");

    this->addEunetSwitch("sc2_03_1_sw01", 48);
    this->findEunetSwitch("sc2_03_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("sc2_03_1_sw01")->connectUpTo(
        "sc2_01_1_sw01");

    this->addEunetSwitch("sc2_04_1_sw01", 24);
    this->findEunetSwitch("sc2_04_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("sc2_04_1_sw01")->connectUpTo(
        "sc2_01_1_sw01");

    this->addEunetSwitch("sck_02_1_sw01", 48);
    this->findEunetSwitch("sck_02_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("sck_02_1_sw01")->connectUpTo(
        "sche_01_1_sw02");

    this->addEunetSwitch("en0w_01_1_sw01", 24);
    this->findEunetSwitch("en0w_01_1_sw01")->setUplinkDataRate(
        ns3::DataRate("10Gbps"));
    this->findEunetSwitch("en0w_01_1_sw01")->connectUpTo(
        "dpc_02_core01");

    this->addEunetSwitch("en0w_01_1_sw02", 48);
    this->findEunetSwitch("en0w_01_1_sw02")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("en0w_01_1_sw02")->connectUpTo(
        "en0w_01_1_sw01");

    this->addEunetSwitch("en0w_02_1_sw01", 48);
    this->findEunetSwitch("en0w_02_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("en0w_02_1_sw01")->connectUpTo(
        "en0w_01_1_sw01");

    this->addEunetSwitch("en0w_03_1_sw01", 48);
    this->findEunetSwitch("en0w_03_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("en0w_03_1_sw01")->connectUpTo(
        "en0w_01_1_sw01");

    this->addEunetSwitch("en0w_04_1_sw01", 72);
    this->findEunetSwitch("en0w_04_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("en0w_04_1_sw01")->connectUpTo(
        "en0w_01_1_sw01");

    this->addEunetSwitch("en0w_05_1_sw01", 48);
    this->findEunetSwitch("en0w_05_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("en0w_05_1_sw01")->connectUpTo(
        "en0w_01_1_sw01");

    this->addEunetSwitch("en0w_06_1_sw01", 48);
    this->findEunetSwitch("en0w_06_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("en0w_06_1_sw01")->connectUpTo(
        "en0w_01_1_sw01");

    this->addEunetSwitch("en0w_07_1_sw01", 48);
    this->findEunetSwitch("en0w_07_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("en0w_07_1_sw01")->connectUpTo(
        "en0w_01_1_sw01");

    this->addEunetSwitch("en0e_01_1_sw01", 72);
    this->findEunetSwitch("en0e_01_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("en0e_01_1_sw01")->connectUpTo(
        "en0w_01_1_sw02");

    this->addEunetSwitch("en0e_02_1_sw01", 72);
    this->findEunetSwitch("en0e_02_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("en0e_02_1_sw01")->connectUpTo(
        "en0w_01_1_sw02");

    this->addEunetSwitch("en0e_03_1_sw01", 72);
    this->findEunetSwitch("en0e_03_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("en0e_03_1_sw01")->connectUpTo(
        "en0w_01_1_sw02");

    this->addEunetSwitch("en0e_04_1_sw01", 72);
    this->findEunetSwitch("en0e_04_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("en0e_04_1_sw01")->connectUpTo(
        "en0w_01_1_sw02");

    this->addEunetSwitch("en0e_05_1_sw01", 48);
    this->findEunetSwitch("en0e_05_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("en0e_05_1_sw01")->connectUpTo(
        "en0w_01_1_sw02");

    this->addEunetSwitch("en0e_06_1_sw01", 48);
    this->findEunetSwitch("en0e_06_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("en0e_06_1_sw01")->connectUpTo(
        "en0w_01_1_sw02");

    this->addEunetSwitch("en0e_07_1_sw01", 48);
    this->findEunetSwitch("en0e_07_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("en0e_07_1_sw01")->connectUpTo(
        "en0w_01_1_sw02");

    this->addEunetSwitch("schw_01_1_sw01", 48);
    this->findEunetSwitch("schw_01_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("schw_01_1_sw01")->connectUpTo(
        "sche_01_1_sw02");

    this->addEunetSwitch("schw_02_1_sw01", 72);
    this->findEunetSwitch("schw_02_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("schw_02_1_sw01")->connectUpTo(
        "schw_01_1_sw01");

    this->addEunetSwitch("schw_03_1_sw01", 72);
    this->findEunetSwitch("schw_03_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("schw_03_1_sw01")->connectUpTo(
        "schw_01_1_sw01");

    this->addEunetSwitch("schw_04_1_sw01", 48);
    this->findEunetSwitch("schw_04_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("schw_04_1_sw01")->connectUpTo(
        "schw_01_1_sw01");

    this->addEunetSwitch("schw_05_1_sw01", 48);
    this->findEunetSwitch("schw_05_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("schw_05_1_sw01")->connectUpTo(
        "schw_01_1_sw01");

    this->addEunetSwitch("llh_01_2_sw02", 48);
    this->findEunetSwitch("llh_01_2_sw02")->setUplinkDataRate(
        ns3::DataRate("10Gbps"));
    this->findEunetSwitch("llh_01_2_sw02")->connectUpTo(
        "dpc_02_01_sw01");

    this->addEunetSwitch("llh_01_1_sw01", 24);
    this->findEunetSwitch("llh_01_1_sw01")->setUplinkDataRate(
        ns3::DataRate("10Gbps"));
    this->findEunetSwitch("llh_01_1_sw01")->connectUpTo(
        "dpc_02_core01");

    this->addEunetSwitch("llh_01_1_sw02", 24);
    this->findEunetSwitch("llh_01_1_sw02")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("llh_01_1_sw02")->connectUpTo(
        "llh_01_1_sw01");

    this->addEunetSwitch("llh_01_2_sw01", 48);
    this->findEunetSwitch("llh_01_2_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("llh_01_2_sw01")->connectUpTo(
        "llh_01_1_sw01");

    this->addEunetSwitch("llh_02_1_sw01", 48);
    this->findEunetSwitch("llh_02_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("llh_02_1_sw01")->connectUpTo(
        "llh_01_1_sw01");

    this->addEunetSwitch("llh_03_1_sw01", 24);
    this->findEunetSwitch("llh_03_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("llh_03_1_sw01")->connectUpTo(
        "llh_01_1_sw02");

    this->addEunetSwitch("llh_04_1_sw01", 48);
    this->findEunetSwitch("llh_04_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("llh_04_1_sw01")->connectUpTo(
        "llh_01_1_sw02");

    this->addEunetSwitch("llh_05_1_sw01", 48);
    this->findEunetSwitch("llh_05_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("llh_05_1_sw01")->connectUpTo(
        "llh_01_1_sw02");

    this->addEunetSwitch("llh_05_2_sw01", 24);
    this->findEunetSwitch("llh_05_2_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("llh_05_2_sw01")->connectUpTo(
        "llh_05_1_sw01");

    this->addEunetSwitch("llh_06_1_sw01", 48);
    this->findEunetSwitch("llh_06_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("llh_06_1_sw01")->connectUpTo(
        "llh_05_1_sw01");

    this->addEunetSwitch("llh_07_1_sw01", 48);
    this->findEunetSwitch("llh_07_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("llh_07_1_sw01")->connectUpTo(
        "llh_05_1_sw01");

    this->addEunetSwitch("llh_08_1_sw01", 48);
    this->findEunetSwitch("llh_08_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("llh_08_1_sw01")->connectUpTo(
        "llh_05_1_sw01");

    this->addEunetSwitch("ll2_01_1_sw01", 48);
    this->findEunetSwitch("ll2_01_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("ll2_01_1_sw01")->connectUpTo(
        "llh_01_1_sw01");

    this->addEunetSwitch("ll2_01_2_sw01", 24);
    this->findEunetSwitch("ll2_01_2_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("ll2_01_2_sw01")->connectUpTo(
        "ll2_01_1_sw01");

    this->addEunetSwitch("ll2_02_1_sw01", 24);
    this->findEunetSwitch("ll2_02_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("ll2_02_1_sw01")->connectUpTo(
        "ll2_01_1_sw01");

    this->addEunetSwitch("ll2_03_1_sw01", 48);
    this->findEunetSwitch("ll2_03_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("ll2_03_1_sw01")->connectUpTo(
        "ll2_01_1_sw01");

    this->addEunetSwitch("ed2_02_1_sw01", 48);
    this->findEunetSwitch("ed2_02_1_sw01")->setUplinkDataRate(
        ns3::DataRate("10Gbps"));
    this->findEunetSwitch("ed2_02_1_sw01")->connectUpTo(
        "dpc_02_core01");

    this->addEunetSwitch("ed2_02_1_sw02", 24);
    this->findEunetSwitch("ed2_02_1_sw02")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("ed2_02_1_sw02")->connectUpTo(
        "ed2_02_1_sw01");

    this->addEunetSwitch("ed2_01_1_sw01", 72);
    this->findEunetSwitch("ed2_01_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("ed2_01_1_sw01")->connectUpTo(
        "ed2_02_1_sw01");

    this->addEunetSwitch("ed2_03_1_sw01", 72);
    this->findEunetSwitch("ed2_03_1_sw01")->setUplinkDataRate(
        ns3::DataRate("10Gbps"));
    this->findEunetSwitch("ed2_03_1_sw01")->connectUpTo(
        "dpc_02_01_sw01");

    this->addEunetSwitch("ed2_03_2_sw01", 48);
    this->findEunetSwitch("ed2_03_2_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("ed2_03_2_sw01")->connectUpTo(
        "ed2_02_1_sw01");

    this->addEunetSwitch("ed2_03_2_sw02", 24);
    this->findEunetSwitch("ed2_03_2_sw02")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("ed2_03_2_sw02")->connectUpTo(
        "ed2_03_2_sw01");

    this->addEunetSwitch("ed2_04_1_sw01", 48);
    this->findEunetSwitch("ed2_04_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("ed2_04_1_sw01")->connectUpTo(
        "ed2_02_1_sw01");

    this->addEunetSwitch("ed2_04_1_sw02", 24);
    this->findEunetSwitch("ed2_04_1_sw02")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("ed2_04_1_sw02")->connectUpTo(
        "ed2_04_1_sw01");

    this->addEunetSwitch("ed2_05_1_sw01", 48);
    this->findEunetSwitch("ed2_05_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("ed2_05_1_sw01")->connectUpTo(
        "ed2_02_1_sw01");

    this->addEunetSwitch("ed3_02_1_sw01", 24);
    this->findEunetSwitch("ed3_02_1_sw01")->setUplinkDataRate(
        ns3::DataRate("10Gbps"));
    this->findEunetSwitch("ed3_02_1_sw01")->connectUpTo(
        "dpc_02_core01");

    this->addEunetSwitch("ed3_02_1_sw02", 24);
    this->findEunetSwitch("ed3_02_1_sw02")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("ed3_02_1_sw02")->connectUpTo(
        "ed3_02_1_sw01");

    this->addEunetSwitch("ed3_01_1_sw01", 24);
    this->findEunetSwitch("ed3_01_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("ed3_01_1_sw01")->connectUpTo(
        "ed3_02_1_sw01");

    this->addEunetSwitch("ed3_03_1_sw01", 24);
    this->findEunetSwitch("ed3_03_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("ed3_03_1_sw01")->connectUpTo(
        "ed3_02_1_sw01");

    this->addEunetSwitch("ed3_04_1_sw01", 48);
    this->findEunetSwitch("ed3_04_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("ed3_04_1_sw01")->connectUpTo(
        "ed3_02_1_sw01");

    this->addEunetSwitch("ed3_05_1_sw01", 24);
    this->findEunetSwitch("ed3_05_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("ed3_05_1_sw01")->connectUpTo(
        "ed3_02_1_sw01");

    this->addEunetSwitch("ed3_06_1_sw01", 24);
    this->findEunetSwitch("ed3_06_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("ed3_06_1_sw01")->connectUpTo(
        "ed3_02_1_sw01");

    this->addEunetSwitch("su_02_1_sw01", 24);
    this->findEunetSwitch("su_02_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("su_02_1_sw01")->connectUpTo(
        "dpc_02_01_sw01");

    this->addEunetSwitch("edh_01_1_sw01", 48);
    this->findEunetSwitch("edh_01_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("edh_01_1_sw01")->connectUpTo(
        "ed3_02_1_sw01");

    this->addEunetSwitch("edh_02_1_sw01", 48);
    this->findEunetSwitch("edh_02_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("edh_02_1_sw01")->connectUpTo(
        "edh_01_1_sw01");

    this->addEunetSwitch("edh_03_1_sw01", 48);
    this->findEunetSwitch("edh_03_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("edh_03_1_sw01")->connectUpTo(
        "edh_01_1_sw01");

    this->addEunetSwitch("edh_03_1_sw02", 24);
    this->findEunetSwitch("edh_03_1_sw02")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("edh_03_1_sw02")->connectUpTo(
        "edh_03_1_sw01");

    this->addEunetSwitch("edh_04_1_sw01", 24);
    this->findEunetSwitch("edh_04_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("edh_04_1_sw01")->connectUpTo(
        "edh_01_1_sw01");

    this->addEunetSwitch("ed4_01_1_sw01", 24);
    this->findEunetSwitch("ed4_01_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("ed4_01_1_sw01")->connectUpTo(
        "ed3_02_1_sw02");

    this->addEunetSwitch("ed4_01_2_sw01", 24);
    this->findEunetSwitch("ed4_01_2_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("ed4_01_2_sw01")->connectUpTo(
        "ed3_02_1_sw02");

    this->addEunetSwitch("ed4_01_3_sw01", 24);
    this->findEunetSwitch("ed4_01_3_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("ed4_01_3_sw01")->connectUpTo(
        "ed4_01_2_sw01");

    this->addEunetSwitch("ed4_02_1_sw01", 24);
    this->findEunetSwitch("ed4_02_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("ed4_02_1_sw01")->connectUpTo(
        "ed4_01_2_sw01");

    this->addEunetSwitch("ed4_03_1_sw01", 24);
    this->findEunetSwitch("ed4_03_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("ed4_03_1_sw01")->connectUpTo(
        "ed4_01_2_sw01");

    this->addEunetSwitch("ed4_04_1_sw01", 24);
    this->findEunetSwitch("ed4_04_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("ed4_04_1_sw01")->connectUpTo(
        "ed4_01_2_sw01");

    this->addEunetSwitch("ph1_01_1_sw01", 8);
    this->findEunetSwitch("ph1_01_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("ph1_01_1_sw01")->connectUpTo(
        "ed3_02_1_sw01");

    this->addEunetSwitch("ph3_01_1_sw01", 8);
    this->findEunetSwitch("ph3_01_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("ph3_01_1_sw01")->connectUpTo(
        "ph1_01_1_sw01");

    this->addEunetSwitch("gk_04_1_sw01", 24);
    this->findEunetSwitch("gk_04_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("gk_04_1_sw01")->connectUpTo("ed3_02_1_sw01");

    this->addEunetSwitch("gee_01_1_sw01", 24);
    this->findEunetSwitch("gee_01_1_sw01")->setUplinkDataRate(
        ns3::DataRate("10Gbps"));
    this->findEunetSwitch("gee_01_1_sw01")->connectUpTo(
        "dpc_02_core01");

    this->addEunetSwitch("gee_01_1_sw02", 24);
    this->findEunetSwitch("gee_01_1_sw02")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("gee_01_1_sw02")->connectUpTo(
        "gee_01_1_sw01");

    this->addEunetSwitch("gee_01_1_sw03", 24);
    this->findEunetSwitch("gee_01_1_sw03")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("gee_01_1_sw03")->connectUpTo(
        "gee_01_1_sw01");

    this->addEunetSwitch("gee_02_1_sw01", 24);
    this->findEunetSwitch("gee_02_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("gee_02_1_sw01")->connectUpTo(
        "gee_01_1_sw01");

    this->addEunetSwitch("gee_02_1_sw02", 24);
    this->findEunetSwitch("gee_02_1_sw02")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("gee_02_1_sw02")->connectUpTo(
        "gee_02_1_sw01");

    this->addEunetSwitch("gee_03_1_sw01", 24);
    this->findEunetSwitch("gee_03_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("gee_03_1_sw01")->connectUpTo(
        "gee_01_1_sw01");

    this->addEunetSwitch("gew_01_1_sw01", 48);
    this->findEunetSwitch("gew_01_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("gew_01_1_sw01")->connectUpTo(
        "gee_01_1_sw03");

    this->addEunetSwitch("gew_02_1_sw01", 48);
    this->findEunetSwitch("gew_02_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("gew_02_1_sw01")->connectUpTo(
        "gew_01_1_sw01");

    this->addEunetSwitch("gew_03_1_sw01", 48);
    this->findEunetSwitch("gew_03_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("gew_03_1_sw01")->connectUpTo(
        "gew_01_1_sw01");

    this->addEunetSwitch("gew_03_1_sw02", 24);
    this->findEunetSwitch("gew_03_1_sw02")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("gew_03_1_sw02")->connectUpTo(
        "gew_03_1_sw01");

    this->addEunetSwitch("ges_02_2_sw01", 72);
    this->findEunetSwitch("ges_02_2_sw01")->setUplinkDataRate(
        ns3::DataRate("10Gbps"));
    this->findEunetSwitch("ges_02_2_sw01")->connectUpTo(
        "dpc_02_01_sw01");

    this->addEunetSwitch("ges_03_2_sw01", 72);
    this->findEunetSwitch("ges_03_2_sw01")->setUplinkDataRate(
        ns3::DataRate("10Gbps"));
    this->findEunetSwitch("ges_03_2_sw01")->connectUpTo(
        "dpc_02_01_sw01");

    this->addEunetSwitch("ges_01_1_sw01", 48);
    this->findEunetSwitch("ges_01_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("ges_01_1_sw01")->connectUpTo(
        "gee_01_1_sw02");

    this->addEunetSwitch("ges_02_1_sw01", 48);
    this->findEunetSwitch("ges_02_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("ges_02_1_sw01")->connectUpTo(
        "ges_01_1_sw01");

    this->addEunetSwitch("ges_03_1_sw01", 48);
    this->findEunetSwitch("ges_03_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("ges_03_1_sw01")->connectUpTo(
        "ges_01_1_sw01");

    this->addEunetSwitch("gek_01_1_sw01", 48);
    this->findEunetSwitch("gek_01_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("gek_01_1_sw01")->connectUpTo(
        "gee_01_1_sw02");

    this->addEunetSwitch("ven_01_1_sw01", 24);
    this->findEunetSwitch("ven_01_1_sw01")->setUplinkDataRate(
        ns3::DataRate("10Gbps"));
    this->findEunetSwitch("ven_01_1_sw01")->connectUpTo(
        "dpc_02_core01");

    this->addEunetSwitch("ven_02_1_sw01", 24);
    this->findEunetSwitch("ven_02_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("ven_02_1_sw01")->connectUpTo(
        "ven_01_1_sw01");

    this->addEunetSwitch("ven_03_1_sw01", 24);
    this->findEunetSwitch("ven_03_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("ven_03_1_sw01")->connectUpTo(
        "ven_01_1_sw01");

    this->addEunetSwitch("ven_04_1_sw01", 24);
    this->findEunetSwitch("ven_04_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("ven_04_1_sw01")->connectUpTo(
        "ven_01_1_sw01");

    this->addEunetSwitch("ccr_01_1_sw01", 24);
    this->findEunetSwitch("ccr_01_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("ccr_01_1_sw01")->connectUpTo(
        "ven_01_1_sw01");

    this->addEunetSwitch("ccr_02_1_sw01", 24);
    this->findEunetSwitch("ccr_02_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("ccr_02_1_sw01")->connectUpTo(
        "ven_01_1_sw01");

    this->addEunetSwitch("ccr_03_1_sw01", 24);
    this->findEunetSwitch("ccr_03_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("ccr_03_1_sw01")->connectUpTo(
        "ven_01_1_sw01");

    this->addEunetSwitch("ci_01_1_sw01", 48);
    this->findEunetSwitch("ci_01_1_sw01")->setUplinkDataRate(
        ns3::DataRate("10Gbps"));
    this->findEunetSwitch("ci_01_1_sw01")->connectUpTo("dpc_02_core01");

    this->addEunetSwitch("ci_02_1_sw01", 24);
    this->findEunetSwitch("ci_02_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("ci_02_1_sw01")->connectUpTo("ci_01_1_sw01");

    this->addEunetSwitch("ci_03_1_sw01", 24);
    this->findEunetSwitch("ci_03_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("ci_03_1_sw01")->connectUpTo("ci_01_1_sw01");

    this->addEunetSwitch("libs_02_1_sw01", 24);
    this->findEunetSwitch("libs_02_1_sw01")->setUplinkDataRate(
        ns3::DataRate("10Gbps"));
    this->findEunetSwitch("libs_02_1_sw01")->connectUpTo(
        "dpc_02_core01");

    this->addEunetSwitch("libw_01_1_sw01", 48);
    this->findEunetSwitch("libw_01_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("libw_01_1_sw01")->connectUpTo(
        "libs_02_1_sw01");

    this->addEunetSwitch("libe_01_1_sw01", 72);
    this->findEunetSwitch("libe_01_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("libe_01_1_sw01")->connectUpTo(
        "libw_01_1_sw01");

    this->addEunetSwitch("libw_02_1_sw01", 24);
    this->findEunetSwitch("libw_02_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("libw_02_1_sw01")->connectUpTo(
        "libw_01_1_sw01");

    this->addEunetSwitch("libe_02_1_sw01", 72);
    this->findEunetSwitch("libe_02_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("libe_02_1_sw01")->connectUpTo(
        "libe_01_1_sw01");

    this->addEunetSwitch("libe_02_1_sw02", 24);
    this->findEunetSwitch("libe_02_1_sw02")->setUplinkDataRate(
        ns3::DataRate("10Gbps"));
    this->findEunetSwitch("libe_02_1_sw02")->connectUpTo(
        "dpc_02_01_sw01");

    this->addEunetSwitch("libw_03_1_sw01", 24);
    this->findEunetSwitch("libw_03_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("libw_03_1_sw01")->connectUpTo(
        "libw_01_1_sw01");

    this->addEunetSwitch("libe_03_1_sw01", 24);
    this->findEunetSwitch("libe_03_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("libe_03_1_sw01")->connectUpTo(
        "libe_01_1_sw01");

    this->addEunetSwitch("libw_04_1_sw01", 24);
    this->findEunetSwitch("libw_04_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("libw_04_1_sw01")->connectUpTo(
        "libw_01_1_sw01");

    this->addEunetSwitch("libe_04_1_sw01", 24);
    this->findEunetSwitch("libe_04_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("libe_04_1_sw01")->connectUpTo(
        "libe_01_1_sw01");

    this->addEunetSwitch("jim_02_1_sw01", 72);
    this->findEunetSwitch("jim_02_1_sw01")->setUplinkDataRate(
        ns3::DataRate("10Gbps"));
    this->findEunetSwitch("jim_02_1_sw01")->connectUpTo(
        "dpc_02_core01");

    this->addEunetSwitch("odpc_01_1_sw01", 24);
    this->findEunetSwitch("odpc_01_1_sw01")->setUplinkDataRate(
        ns3::DataRate("10Gbps"));
    this->findEunetSwitch("odpc_01_1_sw01")->connectUpTo(
        "dpc_02_01_sw01");
}//default constructor of JohokuSwitches



