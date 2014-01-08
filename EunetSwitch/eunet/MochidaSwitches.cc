#define NS3_LOG_ENABLE 1
#include "ns3/log.h"
NS_LOG_COMPONENT_DEFINE ("MochidaSwitches");
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
#include "MochidaSwitches.h"

MochidaSwitches::MochidaSwitches() : NamedSwitches("133.71.0.0", "255.255.0.0") {
    //ns3::AnimationInterface animation_interface("EunetSimulation.xml");
    this->addEunetSwitch("キャンパス間接続L2", 64);

    /*
     //持田キャンパス
     //附属小学校校舎（事務室）
     this->addEunetSwitch("syou_01_2_sw01", 24);
     this->findEunetSwitch("syou_01_2_sw01")->setUplinkDataRate(
     ns3::DataRate("10Gbps"));
     this->findEunetSwitch("syou_01_2_sw01")->connectUpTo("キャンパス間接続L2");

     //附属小学校・センター棟
     this->addEunetSwitch("syou_01_1_core01", 72);
     this->findEunetSwitch("syou_01_1_core01")->setUplinkDataRate(
     ns3::DataRate("10Gbps"));
     this->findEunetSwitch("syou_01_1_core01")->connectUpTo(
     "syou_01_2_sw01");

     this->addEunetSwitch("syou_01_1_sw01", 48);
     this->findEunetSwitch("syou_01_1_sw01")->setUplinkDataRate(
     ns3::DataRate("1Gbps"));
     this->findEunetSwitch("syou_01_1_sw01")->connectUpTo(
     "syou_01_1_core01");

     //附属小学校校舎（視聴覚室）
     this->addEunetSwitch("syou_02_1_sw01", 24);
     this->findEunetSwitch("syou_02_1_sw01")->setUplinkDataRate(
     ns3::DataRate("1Gbps"));
     this->findEunetSwitch("syou_02_1_sw01")->connectUpTo(
     "syou_01_1_core01");

     this->addEunetSwitch("syou_02_1_sw02", 48);
     this->findEunetSwitch("syou_02_1_sw02")->setUplinkDataRate(
     ns3::DataRate("10Gbps"));
     this->findEunetSwitch("syou_02_1_sw02")->connectUpTo(
     "syou_01_1_core01");

     //附属中学校本館
     this->addEunetSwitch("tyuu_01_1_sw02", 48);
     this->findEunetSwitch("tyuu_01_1_sw02")->setUplinkDataRate(
     ns3::DataRate("10Gbps"));
     this->findEunetSwitch("tyuu_01_1_sw02")->connectUpTo(
     "syou_01_1_core01");

     this->addEunetSwitch("tyuu_01_1_sw01", 24);
     this->findEunetSwitch("tyuu_01_1_sw01")->setUplinkDataRate(
     ns3::DataRate("1Gbps"));
     this->findEunetSwitch("tyuu_01_1_sw01")->connectUpTo(
     "syou_01_1_sw01");

     this->addEunetSwitch("tyuu_02_1_sw01", 24);
     this->findEunetSwitch("tyuu_02_1_sw01")->setUplinkDataRate(
     ns3::DataRate("1Gbps"));
     this->findEunetSwitch("tyuu_02_1_sw01")->connectUpTo(
     "syou_01_1_sw01");

     //附属特別支援学校校舎
     this->addEunetSwitch("yougo_02_1_sw01", 24);
     this->findEunetSwitch("yougo_02_1_sw01")->setUplinkDataRate(
     ns3::DataRate("10Gbps"));
     this->findEunetSwitch("yougo_02_1_sw01")->connectUpTo(
     "syou_01_1_sw01");

     this->addEunetSwitch("yougo_01_1_sw01", 24);
     this->findEunetSwitch("yougo_01_1_sw01")->setUplinkDataRate(
     ns3::DataRate("1Gbps"));
     this->findEunetSwitch("yougo_01_1_sw01")->connectUpTo(
     "yougo_02_1_sw01");

     //附属幼稚園本館
     this->addEunetSwitch("youchi_01_1_sw01", 24);
     this->findEunetSwitch("youchi_01_1_sw01")->setUplinkDataRate(
     ns3::DataRate("1Gbps"));
     this->findEunetSwitch("youchi_01_1_sw01")->connectUpTo(
     "syou_01_1_sw01");
     */

    //持田キャンパス
    //附属小学校校舎（事務室）
    this->addEunetSwitch("syou_01_2_sw01", 24);
    this->findEunetSwitch("syou_01_2_sw01")->setUplinkDataRate(
        ns3::DataRate("10Gbps"));
    this->findEunetSwitch("syou_01_2_sw01")->connectUpTo("キャンパス間接続L2");

    //附属小学校・センター棟
    this->addEunetSwitch("syou_01_1_core01", 72);
    this->findEunetSwitch("syou_01_1_core01")->setUplinkDataRate(
        ns3::DataRate("10Gbps"));
    this->findEunetSwitch("syou_01_1_core01")->connectUpTo(
        "syou_01_2_sw01");

    this->addEunetSwitch("syou_01_1_sw01", 48);
    this->findEunetSwitch("syou_01_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("syou_01_1_sw01")->connectUpTo(
        "syou_01_1_core01");

    //附属小学校校舎（視聴覚室）
    this->addEunetSwitch("syou_02_1_sw01", 24);
    this->findEunetSwitch("syou_02_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("syou_02_1_sw01")->connectUpTo(
        "syou_01_1_core01");

    this->addEunetSwitch("syou_02_1_sw02", 48);
    this->findEunetSwitch("syou_02_1_sw02")->setUplinkDataRate(
        ns3::DataRate("10Gbps"));
    this->findEunetSwitch("syou_02_1_sw02")->connectUpTo(
        "syou_01_1_core01");

    //附属中学校本館
    this->addEunetSwitch("tyuu_01_1_sw02", 48);
    this->findEunetSwitch("tyuu_01_1_sw02")->setUplinkDataRate(
        ns3::DataRate("10Gbps"));
    this->findEunetSwitch("tyuu_01_1_sw02")->connectUpTo(
        "syou_01_1_core01");

    this->addEunetSwitch("tyuu_01_1_sw01", 24);
    this->findEunetSwitch("tyuu_01_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("tyuu_01_1_sw01")->connectUpTo(
        "syou_01_1_sw01");

    this->addEunetSwitch("tyuu_02_1_sw01", 24);
    this->findEunetSwitch("tyuu_02_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("tyuu_02_1_sw01")->connectUpTo(
        "syou_01_1_sw01");

    //附属特別支援学校校舎
    this->addEunetSwitch("yougo_02_1_sw01", 24);
    this->findEunetSwitch("yougo_02_1_sw01")->setUplinkDataRate(
        ns3::DataRate("10Gbps"));
    this->findEunetSwitch("yougo_02_1_sw01")->connectUpTo(
        "syou_01_1_sw01");

    this->addEunetSwitch("yougo_01_1_sw01", 24);
    this->findEunetSwitch("yougo_01_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("yougo_01_1_sw01")->connectUpTo(
        "yougo_02_1_sw01");

    //附属幼稚園本館
    this->addEunetSwitch("youchi_01_1_sw01", 24);
    this->findEunetSwitch("youchi_01_1_sw01")->setUplinkDataRate(
        ns3::DataRate("1Gbps"));
    this->findEunetSwitch("youchi_01_1_sw01")->connectUpTo(
        "syou_01_1_sw01");
}

