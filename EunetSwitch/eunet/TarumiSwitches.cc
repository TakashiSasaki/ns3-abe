#define NS3_LOG_ENABLE 1
#include "ns3/log.h"
NS_LOG_COMPONENT_DEFINE ("TarumiSwitches");
#include "ns3/netanim-module.h"
#include "TarumiSwitches.h"

TarumiSwitches::TarumiSwitches() :
	NamedSwitches("133.71.0.0", "255.255.0.0") {
	ns3::AnimationInterface animation_interface("EunetSimulation.xml");

	this->addEunetSwitch("キャンパス間接続L2", 64);

	//樽味キャンパスネットワーク
	//農学部2号館
	this->addEunetSwitch("ag2_03_1_core01", 64);
	this->findEunetSwitch("ag2_03_1_core01")->setUplinkDataRate(ns3::DataRate(
			"10Gbps"));
	this->findEunetSwitch("ag2_03_1_core01")->connectUpTo("キャンパス間接続L2");

	this->addEunetSwitch("ag2_03_1_sw01", 64);
	this->findEunetSwitch("ag2_03_1_sw01")->setUplinkDataRate(ns3::DataRate(
			"10Gbps"));
	this->findEunetSwitch("ag2_03_1_sw01")->connectUpTo("キャンパス間接続L2");

	this->addEunetSwitch("ag2_03_1_sw02", 48);
	this->findEunetSwitch("ag2_03_1_sw02")->setUplinkDataRate(ns3::DataRate(
			"10Gbps"));
	this->findEunetSwitch("ag2_03_1_sw02")->connectUpTo("ag2_03_1_core01");

	this->addEunetSwitch("ag2_03_1_sw03", 48);
	this->findEunetSwitch("ag2_03_1_sw03")->setUplinkDataRate(ns3::DataRate(
			"10Gbps"));
	this->findEunetSwitch("ag2_03_1_sw03")->connectUpTo("ag2_03_1_core01");

	this->addEunetSwitch("ag2_03_1_sw04", 24);
	this->findEunetSwitch("ag2_03_1_sw04")->setUplinkDataRate(ns3::DataRate(
			"1Gbps"));
	this->findEunetSwitch("ag2_03_1_sw04")->connectUpTo("ag2_03_1_sw02");

	this->addEunetSwitch("ag2_03_1_sw05", 24);
	this->findEunetSwitch("ag2_03_1_sw05")->setUplinkDataRate(ns3::DataRate(
			"1Gbps"));
	this->findEunetSwitch("ag2_03_1_sw05")->connectUpTo("ag2_03_1_core01");

	this->addEunetSwitch("ag2_03_1_sw06", 24);
	this->findEunetSwitch("ag2_03_1_sw06")->setUplinkDataRate(ns3::DataRate(
			"1Gbps"));
	this->findEunetSwitch("ag2_03_1_sw06")->connectUpTo("ag2_03_1_core01");

	this->addEunetSwitch("ag2_03_2_sw01", 48);
	this->findEunetSwitch("ag2_03_2_sw01")->setUplinkDataRate(ns3::DataRate(
			"10Gbps"));
	this->findEunetSwitch("ag2_03_2_sw01")->connectUpTo("ag2_03_1_sw01");

	this->addEunetSwitch("ag2_02_2_sw01", 48);
	this->findEunetSwitch("ag2_02_2_sw01")->setUplinkDataRate(ns3::DataRate(
			"1Gbps"));
	this->findEunetSwitch("ag2_02_2_sw01")->connectUpTo("ag2_03_1_core01");

	this->addEunetSwitch("ag2_02_2_sw02", 24);
	this->findEunetSwitch("ag2_02_2_sw02")->setUplinkDataRate(ns3::DataRate(
			"1Gbps"));
	this->findEunetSwitch("ag2_02_2_sw02")->connectUpTo("ag2_03_2_sw01");

	this->addEunetSwitch("ag2_02_1_sw01", 48);
	this->findEunetSwitch("ag2_02_1_sw01")->setUplinkDataRate(ns3::DataRate(
			"1Gbps"));
	this->findEunetSwitch("ag2_02_1_sw01")->connectUpTo("ag2_02_2_sw01");

	this->addEunetSwitch("ag2_03_3_sw01", 48);
	this->findEunetSwitch("ag2_03_3_sw01")->setUplinkDataRate(ns3::DataRate(
			"10Gbps"));
	this->findEunetSwitch("ag2_03_3_sw01")->connectUpTo("ag2_02_2_sw01");

	//農学部本館(北)
	this->addEunetSwitch("aghn_01_1_sw01", 48);
	this->findEunetSwitch("aghn_01_1_sw01")->setUplinkDataRate(ns3::DataRate(
			"10Gbps"));
	this->findEunetSwitch("aghn_01_1_sw01")->connectUpTo("ag2_03_1_core01");

	this->addEunetSwitch("aghn_01_1_sw02", 48);
	this->findEunetSwitch("aghn_01_1_sw02")->setUplinkDataRate(ns3::DataRate(
			"1Gbps"));
	this->findEunetSwitch("aghn_01_1_sw02")->connectUpTo("aghn_01_1_sw01");

	this->addEunetSwitch("aghn_02_1_sw01", 48);
	this->findEunetSwitch("aghn_02_1_sw01")->setUplinkDataRate(ns3::DataRate(
			"1Gbps"));
	this->findEunetSwitch("aghn_02_1_sw01")->connectUpTo("aghn_01_1_sw01");

	this->addEunetSwitch("aghn_03_1_sw01", 72);
	this->findEunetSwitch("aghn_03_1_sw01")->setUplinkDataRate(ns3::DataRate(
			"1Gbps"));
	this->findEunetSwitch("aghn_03_1_sw01")->connectUpTo("aghn_01_1_sw01");

	this->addEunetSwitch("aghn_06_1_sw01", 48);
	this->findEunetSwitch("aghn_06_1_sw01")->setUplinkDataRate(ns3::DataRate(
			"1Gbps"));
	this->findEunetSwitch("aghn_06_1_sw01")->connectUpTo("aghn_01_1_sw01");

	this->addEunetSwitch("aghn_06_2_sw01", 48);
	this->findEunetSwitch("aghn_06_2_sw01")->setUplinkDataRate(ns3::DataRate(
			"1Gbps"));
	this->findEunetSwitch("aghn_06_2_sw01")->connectUpTo("aghn_06_1_sw01");

	this->addEunetSwitch("aghn_05_1_sw01", 48);
	this->findEunetSwitch("aghn_05_1_sw01")->setUplinkDataRate(ns3::DataRate(
			"1Gbps"));
	this->findEunetSwitch("aghn_05_1_sw01")->connectUpTo("aghn_06_1_sw01");

	this->addEunetSwitch("aghn_04_1_sw01", 72);
	this->findEunetSwitch("aghn_04_1_sw01")->setUplinkDataRate(ns3::DataRate(
			"1Gbps"));
	this->findEunetSwitch("aghn_04_1_sw01")->connectUpTo("aghn_06_1_sw01");

	//農学部3号館
	this->addEunetSwitch("ag3_04_1_sw01", 48);
	this->findEunetSwitch("ag3_04_1_sw01")->setUplinkDataRate(ns3::DataRate(
			"10Gbps"));
	this->findEunetSwitch("ag3_04_1_sw01")->connectUpTo("ag2_03_1_core01");

	this->addEunetSwitch("ag3_04_1_sw02", 48);
	this->findEunetSwitch("ag3_04_1_sw02")->setUplinkDataRate(ns3::DataRate(
			"1Gbps"));
	this->findEunetSwitch("ag3_04_1_sw02")->connectUpTo("ag3_04_1_sw01");

	this->addEunetSwitch("ag3_03_1_sw01", 24);
	this->findEunetSwitch("ag3_03_1_sw01")->setUplinkDataRate(ns3::DataRate(
			"1Gbps"));
	this->findEunetSwitch("ag3_03_1_sw01")->connectUpTo("ag3_04_1_sw01");

	this->addEunetSwitch("ag3_02_1_sw01", 24);
	this->findEunetSwitch("ag3_02_1_sw01")->setUplinkDataRate(ns3::DataRate(
			"1Gbps"));
	this->findEunetSwitch("ag3_02_1_sw01")->connectUpTo("ag3_04_1_sw01");

	this->addEunetSwitch("ag3_02_2_sw01", 24);
	this->findEunetSwitch("ag3_02_2_sw01")->setUplinkDataRate(ns3::DataRate(
			"1Gbps"));
	this->findEunetSwitch("ag3_02_2_sw01")->connectUpTo("ag3_04_1_sw01");

	this->addEunetSwitch("ag3_01_1_sw01", 24);
	this->findEunetSwitch("ag3_01_1_sw01")->setUplinkDataRate(ns3::DataRate(
			"1Gbps"));
	this->findEunetSwitch("ag3_01_1_sw01")->connectUpTo("ag3_04_1_sw01");

	this->addEunetSwitch("ag3_05_1_sw01", 24);
	this->findEunetSwitch("ag3_05_1_sw01")->setUplinkDataRate(ns3::DataRate(
			"1Gbps"));
	this->findEunetSwitch("ag3_05_1_sw01")->connectUpTo("ag3_04_1_sw01");

	this->addEunetSwitch("ag3_05_2_sw01", 24);
	this->findEunetSwitch("ag3_05_2_sw01")->setUplinkDataRate(ns3::DataRate(
			"1Gbps"));
	this->findEunetSwitch("ag3_05_2_sw01")->connectUpTo("ag3_04_1_sw01");

	//総合科学研究支援センター
	this->addEunetSwitch("ags_02_1_sw01", 48);
	this->findEunetSwitch("ags_02_1_sw01")->setUplinkDataRate(ns3::DataRate(
			"1Gbps"));
	this->findEunetSwitch("ags_02_1_sw01")->connectUpTo("ag2_03_1_sw01");

	//三科実験室
	this->addEunetSwitch("agm_01_1_sw01", 48);
	this->findEunetSwitch("agm_01_1_sw01")->setUplinkDataRate(ns3::DataRate(
			"1Gbps"));
	this->findEunetSwitch("agm_01_1_sw01")->connectUpTo("ag2_03_1_sw01");

	//連合農学研究科
	this->addEunetSwitch("agr_02_1_sw01", 48);
	this->findEunetSwitch("agr_02_1_sw01")->setUplinkDataRate(ns3::DataRate(
			"1Gbps"));
	this->findEunetSwitch("agr_02_1_sw01")->connectUpTo("ag2_03_1_sw01");

	this->addEunetSwitch("agr_03_1_sw01", 48);
	this->findEunetSwitch("agr_03_1_sw01")->setUplinkDataRate(ns3::DataRate(
			"1Gbps"));
	this->findEunetSwitch("agr_03_1_sw01")->connectUpTo("agr_02_1_sw01");

	this->addEunetSwitch("agr_01_1_sw01", 24);
	this->findEunetSwitch("agr_01_1_sw01")->setUplinkDataRate(ns3::DataRate(
			"1Gbps"));
	this->findEunetSwitch("agr_01_1_sw01")->connectUpTo("agr_02_1_sw01");

	//ユーカリ会館
	this->addEunetSwitch("agu_02_1_sw01", 24);
	this->findEunetSwitch("agu_02_1_sw01")->setUplinkDataRate(ns3::DataRate(
			"1Gbps"));
	this->findEunetSwitch("agu_02_1_sw01")->connectUpTo("agr_02_1_sw01");

	//附属高校校舎(南)
	this->addEunetSwitch("agfs_01_1_sw01", 24);
	this->findEunetSwitch("agfs_01_1_sw01")->setUplinkDataRate(ns3::DataRate(
			"1Gbps"));
	this->findEunetSwitch("agfs_01_1_sw01")->connectUpTo("ag2_03_1_sw01");

	this->addEunetSwitch("agfs_01_1_sw02", 48);
	this->findEunetSwitch("agfs_01_1_sw02")->setUplinkDataRate(ns3::DataRate(
			"10Gbps"));
	this->findEunetSwitch("agfs_01_1_sw02")->connectUpTo("ag2_03_1_sw01");

	this->addEunetSwitch("agfs_05_1_sw01", 24);
	this->findEunetSwitch("agfs_05_1_sw01")->setUplinkDataRate(ns3::DataRate(
			"1Gbps"));
	this->findEunetSwitch("agfs_05_1_sw01")->connectUpTo("ag2_03_1_sw01");

	this->addEunetSwitch("agfs_05_1_sw02", 48);
	this->findEunetSwitch("agfs_05_1_sw02")->setUplinkDataRate(ns3::DataRate(
			"10Gbps"));
	this->findEunetSwitch("agfs_05_1_sw02")->connectUpTo("ag2_03_1_sw01");

	//附属高校舎（北）
	this->addEunetSwitch("agfn_03_1_sw01", 48);
	this->findEunetSwitch("agfn_03_1_sw01")->setUplinkDataRate(ns3::DataRate(
			"10Gbps"));
	this->findEunetSwitch("agfn_03_1_sw01")->connectUpTo("ag2_03_1_core01");

	//環境産業研究施設
	this->addEunetSwitch("agk_01_1_sw01", 24);
	this->findEunetSwitch("agk_01_1_sw01")->setUplinkDataRate(ns3::DataRate(
			"1Gbps"));
	this->findEunetSwitch("agk_01_1_sw01")->connectUpTo("ag2_03_1_sw01");

	//農学部本館（南）
	this->addEunetSwitch("aghs_03_1_sw01", 48);
	this->findEunetSwitch("aghs_03_1_sw01")->setUplinkDataRate(ns3::DataRate(
			"10Gbps"));
	this->findEunetSwitch("aghs_03_1_sw01")->connectUpTo("ag2_03_1_core01");

	this->addEunetSwitch("aghs_03_1_sw02", 48);
	this->findEunetSwitch("aghs_03_1_sw02")->setUplinkDataRate(ns3::DataRate(
			"1Gbps"));
	this->findEunetSwitch("aghs_03_1_sw02")->connectUpTo("aghs_03_1_sw01");

	this->addEunetSwitch("aghs_02_1_sw01", 48);
	this->findEunetSwitch("aghs_02_1_sw01")->setUplinkDataRate(ns3::DataRate(
			"1Gbps"));
	this->findEunetSwitch("aghs_02_1_sw01")->connectUpTo("aghs_03_1_sw01");

	this->addEunetSwitch("aghs_02_2_sw01", 24);
	this->findEunetSwitch("aghs_02_2_sw01")->setUplinkDataRate(ns3::DataRate(
			"1Gbps"));
	this->findEunetSwitch("aghs_02_2_sw01")->connectUpTo("aghs_03_1_sw01");

	this->addEunetSwitch("aghs_01_1_sw01", 48);
	this->findEunetSwitch("aghs_01_1_sw01")->setUplinkDataRate(ns3::DataRate(
			"1Gbps"));
	this->findEunetSwitch("aghs_01_1_sw01")->connectUpTo("aghs_03_1_sw01");

	this->addEunetSwitch("aghs_04_1_sw01", 72);
	this->findEunetSwitch("aghs_04_1_sw01")->setUplinkDataRate(ns3::DataRate(
			"1Gbps"));
	this->findEunetSwitch("aghs_04_1_sw01")->connectUpTo("aghs_03_1_sw01");

	this->addEunetSwitch("aghs_05_1_sw01", 48);
	this->findEunetSwitch("aghs_05_1_sw01")->setUplinkDataRate(ns3::DataRate(
			"1Gbps"));
	this->findEunetSwitch("aghs_05_1_sw01")->connectUpTo("aghs_03_1_sw01");

	//植物工場棟
	this->addEunetSwitch("agp_02_1_sw01", 48);
	this->findEunetSwitch("agp_02_1_sw01")->setUplinkDataRate(ns3::DataRate(
			"1Gbps"));
	this->findEunetSwitch("agp_02_1_sw01")->connectUpTo("agk_01_1_sw01");

	//農学部制御化実験施設
	this->addEunetSwitch("agce_01_1_sw01", 24);
	this->findEunetSwitch("agce_01_1_sw01")->setUplinkDataRate(ns3::DataRate(
			"1Gbps"));
	this->findEunetSwitch("agce_01_1_sw01")->connectUpTo("ag3_02_1_sw01");

	//附属高校（中_北）2棟 廊下
	this->addEunetSwitch("agfcn_02_1_sw01", 48);
	this->findEunetSwitch("agfcn_02_1_sw01")->setUplinkDataRate(ns3::DataRate(
			"1Gbps"));
	this->findEunetSwitch("agfcn_02_1_sw01")->connectUpTo("agfn_03_1_sw01");

}// default constructor
