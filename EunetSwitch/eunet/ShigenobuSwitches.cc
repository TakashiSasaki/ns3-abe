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
#include "EunetSwitches.h"
#include "EunetTerminal.h"
#include "ShigenobuSwitches.h"
NS_LOG_COMPONENT_DEFINE ("ShigenobuSwitches");

ShigenobuSwitches::ShigenobuSwitches() :
    NamedSwitches("133.71.0.0", "255.255.0.0") {
    //ns3::AnimationInterface animation_interface("EunetSimulation.xml");
    //NamedSwitches named_switches("133.71.0.0", "255.255.0.0");
    this->addEunetSwitch("キャンパス間接続L2", 64);

    //重信キャンパスネットワーク
    //医学部寮
    this->addEunetSwitch("me0_02_1_core01", 64);
    this->findEunetSwitch("me0_02_1_core01")->setUplinkDataRate(
        ns3::DataRate("10Gbps"));
    this->findEunetSwitch("me0_02_1_core01")->connectUpTo("キャンパス間接続L2");

    this->addEunetSwitch("me0_02_1_sw01", 64);
    this->findEunetSwitch("me0_02_1_sw01")->setUplinkDataRate(
        ns3::DataRate("10Gbps"));
    this->findEunetSwitch("me0_02_1_sw01")->connectUpTo("キャンパス間接続L2");

    this->addEunetSwitch("me0_02_1_sw02", 24);
    this->findEunetSwitch("me0_02_1_sw02")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("me0_02_1_sw02")->connectUpTo(
        "me0_02_1_core01");

    this->addEunetSwitch("me0_02_1_sw03", 24);
    this->findEunetSwitch("me0_02_1_sw03")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("me0_02_1_sw03")->connectUpTo(
        "me0_02_1_core01");

    this->addEunetSwitch("me0_02_1_sw04", 48);
    this->findEunetSwitch("me0_02_1_sw04")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("me0_02_1_sw04")->connectUpTo(
        "me0_02_1_core01");

    this->addEunetSwitch("me0_02_2_sw01", 48);
    this->findEunetSwitch("me0_02_2_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("me0_02_2_sw01")->connectUpTo(
        "me0_02_1_core01");

    this->addEunetSwitch("me0_02_3_sw01", 48);
    this->findEunetSwitch("me0_02_3_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("me0_02_3_sw01")->connectUpTo(
        "me0_02_1_sw04");

    this->addEunetSwitch("me0_01_1_sw01", 48);
    this->findEunetSwitch("me0_01_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("me0_01_1_sw01")->connectUpTo(
        "me0_02_1_sw02");

    this->addEunetSwitch("me0_03_1_sw01", 72);
    this->findEunetSwitch("me0_03_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("me0_03_1_sw01")->connectUpTo(
        "me0_02_1_sw02");

    this->addEunetSwitch("me0_04_1_sw01", 48);
    this->findEunetSwitch("me0_04_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("me0_04_1_sw01")->connectUpTo(
        "me0_02_1_sw02");

    this->addEunetSwitch("me0_05_1_sw01", 48);
    this->findEunetSwitch("me0_05_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("me0_05_1_sw01")->connectUpTo(
        "me0_02_1_sw02");

    this->addEunetSwitch("me0_06_1_sw01", 48);
    this->findEunetSwitch("me0_06_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("me0_06_1_sw01")->connectUpTo(
        "me0_02_1_sw03");

    this->addEunetSwitch("me0_07_1_sw01", 72);
    this->findEunetSwitch("me0_07_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("me0_07_1_sw01")->connectUpTo(
        "me0_02_1_sw03");

    this->addEunetSwitch("me0_08_1_sw01", 72);
    this->findEunetSwitch("me0_08_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("me0_08_1_sw01")->connectUpTo(
        "me0_02_1_sw03");

    this->addEunetSwitch("me0_09_1_sw01", 72);
    this->findEunetSwitch("me0_09_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("me0_09_1_sw01")->connectUpTo(
        "me0_02_1_sw03");

    //総合科学研究支援センタ
    this->addEunetSwitch("mes_02_1_sw01", 24);
    this->findEunetSwitch("mes_02_1_sw01")->setUplinkDataRate(
        ns3::DataRate("10Gbps"));
    this->findEunetSwitch("mes_02_1_sw01")->connectUpTo(
        "me0_02_1_sw01");

    this->addEunetSwitch("mes_01_1_sw01", 24);
    this->findEunetSwitch("mes_01_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("mes_01_1_sw01")->connectUpTo(
        "mes_02_1_sw01");

    //総合教育棟
    this->addEunetSwitch("mej_02_1_sw02", 144);
    this->findEunetSwitch("mej_02_1_sw02")->setUplinkDataRate(
        ns3::DataRate("10Gbps"));
    this->findEunetSwitch("mej_02_1_sw02")->connectUpTo(
        "me0_02_1_sw01");

    this->addEunetSwitch("mej_02_1_sw01", 72);
    this->findEunetSwitch("mej_02_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("mej_02_1_sw01")->connectUpTo(
        "me0_02_1_sw02");

    this->addEunetSwitch("mej_01_1_sw01", 24);
    this->findEunetSwitch("mej_01_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("mej_01_1_sw01")->connectUpTo(
        "me0_02_1_core01");

    //臨床研究棟
    this->addEunetSwitch("mer_01_1_sw01", 24);
    this->findEunetSwitch("mer_01_1_sw01")->setUplinkDataRate(
        ns3::DataRate("10Gbps"));
    this->findEunetSwitch("mer_01_1_sw01")->connectUpTo(
        "me0_02_1_core01");

    this->addEunetSwitch("mer_02_1_sw01", 24);
    this->findEunetSwitch("mer_02_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("mer_02_1_sw01")->connectUpTo(
        "mer_01_1_sw01");

    this->addEunetSwitch("mer_03_1_sw01", 24);
    this->findEunetSwitch("mer_03_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("mer_03_1_sw01")->connectUpTo(
        "mer_01_1_sw01");

    //看護学科校舎
    this->addEunetSwitch("men_03_1_sw01", 24);
    this->findEunetSwitch("men_03_1_sw01")->setUplinkDataRate(
        ns3::DataRate("10Gbps"));
    this->findEunetSwitch("men_03_1_sw01")->connectUpTo(
        "me0_02_1_core01");

    this->addEunetSwitch("men_01_1_sw01", 24);
    this->findEunetSwitch("men_01_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("men_01_1_sw01")->connectUpTo(
        "men_03_1_sw01");

    this->addEunetSwitch("men_02_1_sw01", 24);
    this->findEunetSwitch("men_02_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("men_02_1_sw01")->connectUpTo(
        "men_03_1_sw01");

    this->addEunetSwitch("men_04_1_sw01", 24);
    this->findEunetSwitch("men_04_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("men_04_1_sw01")->connectUpTo(
        "men_03_1_sw01");

    this->addEunetSwitch("men_04_2_sw01", 48);
    this->findEunetSwitch("men_04_2_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("men_04_2_sw01")->connectUpTo(
        "men_03_1_sw01");

    this->addEunetSwitch("men_04_2_sw02", 96);
    this->findEunetSwitch("men_04_2_sw02")->setUplinkDataRate(
        ns3::DataRate("10Gbps"));
    this->findEunetSwitch("men_04_2_sw02")->connectUpTo(
        "men_03_1_sw01");

    this->addEunetSwitch("men_05_1_sw01", 24);
    this->findEunetSwitch("men_05_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("men_05_1_sw01")->connectUpTo(
        "men_03_1_sw01");

    this->addEunetSwitch("men_06_1_sw01", 24);
    this->findEunetSwitch("men_06_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("men_06_1_sw01")->connectUpTo(
        "men_03_1_sw01");

    //管理棟
    this->addEunetSwitch("mek_03_1_sw01", 24);
    this->findEunetSwitch("mek_03_1_sw01")->setUplinkDataRate(
        ns3::DataRate("10Gbps"));
    this->findEunetSwitch("mek_03_1_sw01")->connectUpTo(
        "me0_02_1_core01");

    this->addEunetSwitch("mek_02_1_sw01", 24);
    this->findEunetSwitch("mek_02_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("mek_02_1_sw01")->connectUpTo(
        "me0_02_1_sw01");

    //付属図書館医学部分館
    this->addEunetSwitch("melib_01_1_sw01", 72);
    this->findEunetSwitch("melib_01_1_sw01")->setUplinkDataRate(
        ns3::DataRate("10Gbps"));
    this->findEunetSwitch("melib_01_1_sw01")->connectUpTo(
        "me0_02_1_core01");

    //付属病院1号館
    this->addEunetSwitch("me1_02_1_sw01", 48);
    this->findEunetSwitch("me1_02_1_sw01")->setUplinkDataRate(
        ns3::DataRate("10Gbps"));
    this->findEunetSwitch("me1_02_1_sw01")->connectUpTo(
        "me0_02_1_core01");

    this->addEunetSwitch("me1_02_1_sw02", 24);
    this->findEunetSwitch("me1_02_1_sw02")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("me1_02_1_sw02")->connectUpTo(
        "me1_02_1_sw01");

    this->addEunetSwitch("me1_02_1_sw03", 24);
    this->findEunetSwitch("me1_02_1_sw03")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("me1_02_1_sw03")->connectUpTo(
        "me1_02_1_sw01");

    this->addEunetSwitch("me1_02_1_sw04", 24);
    this->findEunetSwitch("me1_02_1_sw04")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("me1_02_1_sw04")->connectUpTo(
        "me1_02_1_sw01");

    this->addEunetSwitch("me1_02_1_sw05", 24);
    this->findEunetSwitch("me1_02_1_sw05")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("me1_02_1_sw05")->connectUpTo(
        "me1_02_1_sw01");

    this->addEunetSwitch("me1_02_1_sw06", 24);
    this->findEunetSwitch("me1_02_1_sw06")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("me1_02_1_sw06")->connectUpTo(
        "me1_02_1_sw01");

    this->addEunetSwitch("me1_02_1_sw07", 24);
    this->findEunetSwitch("me1_02_1_sw07")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("me1_02_1_sw07")->connectUpTo(
        "me1_02_1_sw01");

    this->addEunetSwitch("me1_02_1_sw08", 24);
    this->findEunetSwitch("me1_02_1_sw08")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("me1_02_1_sw08")->connectUpTo(
        "me1_02_1_sw01");

    this->addEunetSwitch("me1_02_1_sw09", 48);
    this->findEunetSwitch("me1_02_1_sw09")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("me1_02_1_sw09")->connectUpTo(
        "me1_02_1_sw01");

    this->addEunetSwitch("me1_02_2_sw01", 24);
    this->findEunetSwitch("me1_02_2_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("me1_02_2_sw01")->connectUpTo(
        "me1_02_1_sw04");

    this->addEunetSwitch("me1_02_3_sw01", 24);
    this->findEunetSwitch("me1_02_3_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("me1_02_3_sw01")->connectUpTo(
        "me1_02_1_sw05");

    this->addEunetSwitch("me1_01_1_sw01", 24);
    this->findEunetSwitch("me1_01_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("me1_01_1_sw01")->connectUpTo(
        "me1_02_1_sw05");

    this->addEunetSwitch("me1_01_2_sw01", 24);
    this->findEunetSwitch("me1_01_2_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("me1_01_2_sw01")->connectUpTo(
        "me1_02_1_sw05");

    this->addEunetSwitch("me1_03_1_sw01", 24);
    this->findEunetSwitch("me1_03_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("me1_03_1_sw01")->connectUpTo(
        "me1_02_1_sw04");

    this->addEunetSwitch("me1_03_2_sw01", 48);
    this->findEunetSwitch("me1_03_2_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("me1_03_2_sw01")->connectUpTo(
        "me1_02_1_sw04");

    this->addEunetSwitch("me1_04_1_sw01", 24);
    this->findEunetSwitch("me1_04_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("me1_04_1_sw01")->connectUpTo(
        "me1_02_1_sw04");

    this->addEunetSwitch("me1_05_1_sw01", 24);
    this->findEunetSwitch("me1_05_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("me1_05_1_sw01")->connectUpTo(
        "me1_02_1_sw03");

    this->addEunetSwitch("me1_06_1_sw01", 24);
    this->findEunetSwitch("me1_06_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("me1_06_1_sw01")->connectUpTo(
        "me1_02_1_sw03");

    this->addEunetSwitch("me1_07_1_sw01", 24);
    this->findEunetSwitch("me1_07_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("me1_07_1_sw01")->connectUpTo(
        "me1_02_1_sw03");

    this->addEunetSwitch("me1_08_1_sw01", 24);
    this->findEunetSwitch("me1_08_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("me1_08_1_sw01")->connectUpTo(
        "me1_02_1_sw03");

    this->addEunetSwitch("me1_09_1_sw01", 24);
    this->findEunetSwitch("me1_09_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("me1_09_1_sw01")->connectUpTo(
        "me1_02_1_sw03");

    this->addEunetSwitch("me1_10_1_sw01", 24);
    this->findEunetSwitch("me1_10_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("me1_10_1_sw01")->connectUpTo(
        "me1_02_1_sw03");

    //付属病院2号館
    this->addEunetSwitch("me2_01_1_sw01", 48);
    this->findEunetSwitch("me2_01_1_sw01")->setUplinkDataRate(
        ns3::DataRate("10Gbps"));
    this->findEunetSwitch("me2_01_1_sw01")->connectUpTo(
        "me0_02_1_core01");

    this->addEunetSwitch("me2_01_1_sw02", 24);
    this->findEunetSwitch("me2_01_1_sw02")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("me2_01_1_sw02")->connectUpTo(
        "me2_01_1_sw01");

    this->addEunetSwitch("me2_01_1_sw03", 24);
    this->findEunetSwitch("me2_01_1_sw03")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("me2_01_1_sw03")->connectUpTo(
        "me2_01_1_sw01");

    this->addEunetSwitch("me2_B1_1_sw01", 24);
    this->findEunetSwitch("me2_B1_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("me2_B1_1_sw01")->connectUpTo(
        "me2_01_1_sw03");

    this->addEunetSwitch("me2_03_1_sw01", 48);
    this->findEunetSwitch("me2_03_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("me2_03_1_sw01")->connectUpTo(
        "me2_01_1_sw03");

    this->addEunetSwitch("me2_04_1_sw01", 24);
    this->findEunetSwitch("me2_04_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("me2_04_1_sw01")->connectUpTo(
        "me2_01_1_sw03");

    this->addEunetSwitch("me2_05_1_sw01", 24);
    this->findEunetSwitch("me2_05_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("me2_05_1_sw01")->connectUpTo(
        "me2_01_1_sw02");

    this->addEunetSwitch("me2_06_1_sw01", 24);
    this->findEunetSwitch("me2_06_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("me2_06_1_sw01")->connectUpTo(
        "me2_01_1_sw02");

    this->addEunetSwitch("me2_07_1_sw01", 24);
    this->findEunetSwitch("me2_07_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("me2_07_1_sw01")->connectUpTo(
        "me2_01_1_sw02");

    this->addEunetSwitch("me2_08_1_sw01", 24);
    this->findEunetSwitch("me2_08_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("me2_08_1_sw01")->connectUpTo(
        "me2_01_1_sw02");

    //付属病院病歴棟
    this->addEunetSwitch("meb_03_1_sw01", 24);
    this->findEunetSwitch("meb_03_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("meb_03_1_sw01")->connectUpTo(
        "me0_02_1_core01");

    //地域医療支援センター
    this->addEunetSwitch("mels_01_1_sw01", 24);
    this->findEunetSwitch("mels_01_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("mels_01_1_sw01")->connectUpTo(
        "me1_02_1_sw01");

    this->addEunetSwitch("mels_02_1_sw01", 24);
    this->findEunetSwitch("mels_02_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("mels_02_1_sw01")->connectUpTo(
        "me1_02_1_sw01");

    this->addEunetSwitch("mels_03_1_sw01", 24);
    this->findEunetSwitch("mels_03_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("mels_03_1_sw01")->connectUpTo(
        "me1_02_1_sw01");

    //総合学習棟
    this->addEunetSwitch("melng_02_1_sw01", 72);
    this->findEunetSwitch("melng_02_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("melng_02_1_sw01")->connectUpTo(
        "melib_01_1_sw01");

    //付属病院3号棟
    this->addEunetSwitch("me3_01_1_sw01", 24);
    this->findEunetSwitch("me3_01_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("me3_01_1_sw01")->connectUpTo(
        "me1_02_1_sw01");

    this->addEunetSwitch("me3_02_1_sw01", 24);
    this->findEunetSwitch("me3_02_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("me3_02_1_sw01")->connectUpTo(
        "me1_02_1_sw01");

    this->addEunetSwitch("me3_03_1_sw01", 24);
    this->findEunetSwitch("me3_03_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("me3_03_1_sw01")->connectUpTo(
        "me1_02_1_sw01");

    //MRI-CT-PET装置棟
    this->addEunetSwitch("memcp_01_1_sw01", 24);
    this->findEunetSwitch("memcp_01_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("memcp_01_1_sw01")->connectUpTo(
        "me1_02_1_sw01");

    this->addEunetSwitch("memcp_B1_1_sw01", 24);
    this->findEunetSwitch("memcp_B1_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("memcp_B1_1_sw01")->connectUpTo(
        "me1_02_1_sw01");

    //講義棟(東ウイング北)
    this->addEunetSwitch("mekg_01_1_sw01", 24);
    this->findEunetSwitch("mekg_01_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("mekg_01_1_sw01")->connectUpTo(
        "me0_02_1_core01");

    this->addEunetSwitch("mekg_02_1_sw01", 24);
    this->findEunetSwitch("mekg_02_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("mekg_02_1_sw01")->connectUpTo(
        "mekg_01_1_sw01");

    //講義棟(東ウイング南)
    this->addEunetSwitch("mekg_01_2_sw01", 24);
    this->findEunetSwitch("mekg_01_2_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("mekg_01_2_sw01")->connectUpTo(
        "mekg_01_1_sw01");

    this->addEunetSwitch("mekg_02_2_sw01", 24);
    this->findEunetSwitch("mekg_02_2_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("mekg_02_2_sw01")->connectUpTo(
        "mekg_01_2_sw01");

    //解剖棟(西ウイング)
    this->addEunetSwitch("meds_02_1_sw01", 24);
    this->findEunetSwitch("meds_02_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("meds_02_1_sw01")->connectUpTo(
        "me0_02_1_core01");

    this->addEunetSwitch("meds_01_1_sw01", 24);
    this->findEunetSwitch("meds_01_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("meds_01_1_sw01")->connectUpTo(
        "meds_02_1_sw01");

    //職員福利棟
    this->addEunetSwitch("mesh_01_1_sw01", 24);
    this->findEunetSwitch("mesh_01_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("mesh_01_1_sw01")->connectUpTo(
        "me0_02_1_sw01");

    //看護師宿舎
    this->addEunetSwitch("ns_01_1_sw01", 24);
    this->findEunetSwitch("ns_01_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("ns_01_1_sw01")->connectUpTo(
        "me0_02_1_core01");

    //外来棟
    this->addEunetSwitch("meg_01_1_sw01", 48);
    this->findEunetSwitch("meg_01_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("meg_01_1_sw01")->connectUpTo(
        "me0_02_1_core01");

    this->addEunetSwitch("meg_01_2_sw01", 24);
    this->findEunetSwitch("meg_01_2_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("meg_01_2_sw01")->connectUpTo(
        "me1_02_1_sw02");

    this->addEunetSwitch("meg_01_3_sw01", 48);
    this->findEunetSwitch("meg_01_3_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("meg_01_3_sw01")->connectUpTo(
        "me1_02_1_sw01");

    this->addEunetSwitch("meg_01_4_sw01", 48);
    this->findEunetSwitch("meg_01_4_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("meg_01_4_sw01")->connectUpTo(
        "me1_02_1_sw01");

    this->addEunetSwitch("meg_02_1_sw01", 24);
    this->findEunetSwitch("meg_02_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("meg_02_1_sw01")->connectUpTo(
        "meg_01_2_sw01");

    this->addEunetSwitch("meg_02_2_sw01", 48);
    this->findEunetSwitch("meg_02_2_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("meg_02_2_sw01")->connectUpTo(
        "me1_02_1_sw01");

    this->addEunetSwitch("meg_02_3_sw01", 48);
    this->findEunetSwitch("meg_02_3_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("meg_02_3_sw01")->connectUpTo(
        "me1_02_1_sw01");

    this->addEunetSwitch("meg_03_1_sw01", 24);
    this->findEunetSwitch("meg_03_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("meg_03_1_sw01")->connectUpTo(
        "me1_02_1_sw02");

    this->addEunetSwitch("meg_03_2_sw01", 24);
    this->findEunetSwitch("meg_03_2_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("meg_03_2_sw01")->connectUpTo(
        "me1_02_1_sw01");

    this->addEunetSwitch("meg_04_1_sw01", 24);
    this->findEunetSwitch("meg_04_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("meg_04_1_sw01")->connectUpTo(
        "me1_02_1_sw01");

    //コミュニティハウス
    this->addEunetSwitch("huku_01_1_sw01", 48);
    this->findEunetSwitch("huku_01_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("huku_01_1_sw01")->connectUpTo(
        "me2_01_1_sw01");
}//default constructor



