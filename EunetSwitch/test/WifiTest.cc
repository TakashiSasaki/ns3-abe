#include <iostream>
#define NS3_LOG_ENABLE 1
#include "ns3/log.h"
NS_LOG_COMPONENT_DEFINE("WifiTest");
#define NS3_ASSERT_ENABLE 1
#include "ns3/assert.h"
#include "ns3/test.h"
#include "ns3/yans-wifi-channel.h"
#include "ns3/yans-wifi-helper.h"
#include "ns3/yans-error-rate-model.h"
#include "ns3/mobility-helper.h"
#include "ns3/constant-position-mobility-model.h"
#include "ns3/constant-acceleration-mobility-model.h"
#include "ns3/regular-wifi-mac.h"
#include "ns3/sta-wifi-mac.h"
#include "ns3/adhoc-wifi-mac.h"
#include "ns3/yans-wifi-phy.h"
#include "ns3/mac-rx-middle.h"
#include "ns3/wifi-net-device.h"
#include "ns3/dca-txop.h"
#include "ns3/aarf-wifi-manager.h"
#include "ns3/propagation-delay-model.h"
#include "ns3/propagation-loss-model.h"
#include "ns3/ap-wifi-mac.h"
#include "ns3/names.h"
#include "WifiPhyTrace.h"
#include "WifiMacTrace.h"

class WifiTestCase: public ns3::TestCase {
	ns3::Ptr<ns3::YansWifiChannel> ptrYansWifiChannel;
	ns3::Ptr<ns3::PropagationDelayModel> ptrPropagationDelayModel;
	ns3::Ptr<ns3::PropagationLossModel> ptrPropagationLossModel;
	ns3::Ptr<ns3::Node> ptrNode1;
	ns3::Ptr<ns3::Node> ptrNode2;
	ns3::Ptr<ns3::Node> ptrNode3;
	ns3::Ptr<ns3::WifiNetDevice> ptrWifiNetDevice1;
	ns3::Ptr<ns3::WifiNetDevice> ptrWifiNetDevice2;
	ns3::Ptr<ns3::WifiNetDevice> ptrWifiNetDevice3;
	ns3::Ptr<ns3::ConstantPositionMobilityModel> ptrMobilityModel1;
	ns3::Ptr<ns3::ConstantPositionMobilityModel> ptrMobilityModel2;
	ns3::Ptr<ns3::ConstantPositionMobilityModel> ptrMobilityModel3;
	ns3::Ptr<ns3::YansErrorRateModel> ptrErrorRateModel1;
	ns3::Ptr<ns3::YansErrorRateModel> ptrErrorRateModel2;
	ns3::Ptr<ns3::YansErrorRateModel> ptrErrorRateModel3;
	ns3::Ptr<ns3::WifiMac> ptrWifiMac1;
	ns3::Ptr<ns3::WifiMac> ptrWifiMac2;
	ns3::Ptr<ns3::WifiMac> ptrWifiMac3;
	ns3::Ptr<ns3::YansWifiPhy> ptrYansWifiPhy1;
	ns3::Ptr<ns3::YansWifiPhy> ptrYansWifiPhy2;
	ns3::Ptr<ns3::YansWifiPhy> ptrYansWifiPhy3;
	ns3::Mac48Address mac48Address1;
	ns3::Mac48Address mac48Address2;
	ns3::Mac48Address mac48Address3;
	ns3::Ptr<ns3::WifiRemoteStationManager> ptrWifiRemoteStationManager1;
	ns3::Ptr<ns3::WifiRemoteStationManager> ptrWifiRemoteStationManager2;
	ns3::Ptr<ns3::WifiRemoteStationManager> ptrWifiRemoteStationManager3;

public:
	WifiTestCase();
	virtual void DoRun();
	virtual ~WifiTestCase();
	void SendOnePacket();
};//WifiTest

WifiTestCase::WifiTestCase() :
	ns3::TestCase("WifiTestCase") {
	this->mac48Address1 = ns3::Mac48Address("01:11:11:11:11:10");
	this->mac48Address2 = ns3::Mac48Address("02:22:22:22:22:20");
	this->mac48Address3 = ns3::Mac48Address("03:33:33:33:33:30");
}
WifiTestCase::~WifiTestCase() {
}

void WifiTestCase::SendOnePacket() {
	uint8_t buffer[] = { 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88,
			0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff };
	ns3::Ptr<ns3::Packet> ptr_packet = ns3::Create<ns3::Packet>(buffer,
			sizeof buffer);
	//this->ptrWifiNetDevice2->Send(ptr_packet,
	//		this->ptrWifiNetDevice2->GetBroadcast(), 1);
	this->ptrWifiNetDevice1->Send(ptr_packet,
			this->ptrWifiNetDevice1->GetBroadcast(), 1);
	//this->ptrWifiNetDevice1->Send(ptr_packet, this->mac48Address3 ,1);
}

void WifiTestCase::DoRun() {
	auto wifi_channel_helper = ns3::YansWifiChannelHelper::Default();
	this->ptrYansWifiChannel = wifi_channel_helper.Create();
	this->ptrPropagationDelayModel = ns3::CreateObject<
			ns3::RandomPropagationDelayModel>();
	this->ptrPropagationLossModel = ns3::CreateObject<
			ns3::RandomPropagationLossModel>();
	this->ptrMobilityModel1 = ns3::CreateObject<
			ns3::ConstantPositionMobilityModel>();
	this->ptrMobilityModel2 = ns3::CreateObject<
			ns3::ConstantPositionMobilityModel>();
	this->ptrMobilityModel3 = ns3::CreateObject<
			ns3::ConstantPositionMobilityModel>();
	this->ptrMobilityModel1->SetPosition(ns3::Vector(0.0, 0.0, 0.0));
	this->ptrMobilityModel2->SetPosition(ns3::Vector(-5.0, 0.0, 0.0));
	this->ptrMobilityModel3->SetPosition(ns3::Vector(+5.0, 0.0, 0.0));
	this->ptrErrorRateModel1 = ns3::CreateObject<ns3::YansErrorRateModel>();
	this->ptrErrorRateModel2 = ns3::CreateObject<ns3::YansErrorRateModel>();
	this->ptrErrorRateModel3 = ns3::CreateObject<ns3::YansErrorRateModel>();
	this->ptrNode1 = ns3::CreateObject<ns3::Node>();
	this->ptrNode2 = ns3::CreateObject<ns3::Node>();
	this->ptrNode3 = ns3::CreateObject<ns3::Node>();
	this->ptrNode1->AggregateObject(this->ptrMobilityModel1);
	this->ptrNode2->AggregateObject(this->ptrMobilityModel2);
	this->ptrNode3->AggregateObject(this->ptrMobilityModel3);
	this->ptrWifiNetDevice1 = ns3::CreateObject<ns3::WifiNetDevice>();
	this->ptrWifiNetDevice2 = ns3::CreateObject<ns3::WifiNetDevice>();
	this->ptrWifiNetDevice3 = ns3::CreateObject<ns3::WifiNetDevice>();
	this->ptrYansWifiPhy1 = ns3::CreateObject<ns3::YansWifiPhy>();
	this->ptrYansWifiPhy2 = ns3::CreateObject<ns3::YansWifiPhy>();
	this->ptrYansWifiPhy3 = ns3::CreateObject<ns3::YansWifiPhy>();
	this->ptrYansWifiPhy1->SetChannel(this->ptrYansWifiChannel);
	this->ptrYansWifiPhy2->SetChannel(this->ptrYansWifiChannel);
	this->ptrYansWifiPhy3->SetChannel(this->ptrYansWifiChannel);
	this->ptrYansWifiPhy1->SetErrorRateModel(this->ptrErrorRateModel1);
	this->ptrYansWifiPhy2->SetErrorRateModel(this->ptrErrorRateModel2);
	this->ptrYansWifiPhy3->SetErrorRateModel(this->ptrErrorRateModel3);
	this->ptrYansWifiPhy1->ConfigureStandard(ns3::WIFI_PHY_STANDARD_80211a);
	this->ptrYansWifiPhy2->ConfigureStandard(ns3::WIFI_PHY_STANDARD_80211a);
	this->ptrYansWifiPhy3->ConfigureStandard(ns3::WIFI_PHY_STANDARD_80211a);
	this->ptrYansWifiPhy1->SetMobility(this->ptrNode1);
	this->ptrYansWifiPhy2->SetMobility(this->ptrNode2);
	this->ptrYansWifiPhy3->SetMobility(this->ptrNode3);
	this->ptrYansWifiPhy1->SetDevice(this->ptrWifiNetDevice1);
	this->ptrYansWifiPhy2->SetDevice(this->ptrWifiNetDevice2);
	this->ptrYansWifiPhy3->SetDevice(this->ptrWifiNetDevice3);
	this->ptrWifiMac1 = ns3::CreateObject<ns3::AdhocWifiMac>();
	this->ptrWifiMac2 = ns3::CreateObject<ns3::AdhocWifiMac>();
	this->ptrWifiMac3 = ns3::CreateObject<ns3::ApWifiMac>();
	this->ptrWifiMac1->ConfigureStandard(ns3::WIFI_PHY_STANDARD_80211a);
	this->ptrWifiMac2->ConfigureStandard(ns3::WIFI_PHY_STANDARD_80211a);
	this->ptrWifiMac3->ConfigureStandard(ns3::WIFI_PHY_STANDARD_80211a);
	this->ptrWifiMac1->SetAddress(this->mac48Address1);
	this->ptrWifiMac2->SetAddress(this->mac48Address2);
	this->ptrWifiMac3->SetAddress(this->mac48Address3);
	this->ptrWifiRemoteStationManager1
			= ns3::CreateObject<ns3::AarfWifiManager>();
	this->ptrWifiRemoteStationManager2
			= ns3::CreateObject<ns3::AarfWifiManager>();
	this->ptrWifiRemoteStationManager3
			= ns3::CreateObject<ns3::AarfWifiManager>();
	this->ptrWifiNetDevice1->SetMac(this->ptrWifiMac1);
	this->ptrWifiNetDevice2->SetMac(this->ptrWifiMac2);
	this->ptrWifiNetDevice3->SetMac(this->ptrWifiMac3);
	this->ptrWifiNetDevice1->SetPhy(this->ptrYansWifiPhy1);
	this->ptrWifiNetDevice2->SetPhy(this->ptrYansWifiPhy2);
	this->ptrWifiNetDevice3->SetPhy(this->ptrYansWifiPhy3);
	this->ptrWifiNetDevice1->SetRemoteStationManager(
			this->ptrWifiRemoteStationManager1);
	this->ptrWifiNetDevice2->SetRemoteStationManager(
			this->ptrWifiRemoteStationManager2);
	this->ptrWifiNetDevice3->SetRemoteStationManager(
			this->ptrWifiRemoteStationManager3);
	this->ptrNode1->AddDevice(this->ptrWifiNetDevice1);
	this->ptrNode2->AddDevice(this->ptrWifiNetDevice2);
	this->ptrNode3->AddDevice(this->ptrWifiNetDevice3);
	NS_ASSERT(this->ptrNode1->GetNDevices() > 0);
	NS_ASSERT(this->ptrNode2->GetNDevices() > 0);
	NS_ASSERT(this->ptrNode3->GetNDevices() > 0);
	WifiMacTrace wifi_mac_trace_1(this->ptrNode1.operator ->());
	WifiMacTrace wifi_mac_trace_2(this->ptrNode2.operator ->());
	WifiMacTrace wifi_mac_trace_3(this->ptrNode3.operator ->());
	WifiPhyTrace wifi_phy_trace_1(this->ptrNode1.operator ->());
	WifiPhyTrace wifi_phy_trace_2(this->ptrNode2.operator ->());
	WifiPhyTrace wifi_phy_trace_3(this->ptrNode3.operator ->());
	wifi_mac_trace_1.DoInitialize();
	wifi_mac_trace_2.DoInitialize();
	wifi_mac_trace_3.DoInitialize();
	wifi_phy_trace_1.DoInitialize();
	wifi_phy_trace_2.DoInitialize();
	wifi_phy_trace_3.DoInitialize();
	ns3::Simulator::Schedule(ns3::Seconds(1.0), &WifiTestCase::SendOnePacket,
			this);
	ns3::Simulator::Stop(ns3::Seconds(1.001));
	ns3::Simulator::Run();
	ns3::Simulator::Destroy();
}

class WifiL2TestCase: public ns3::TestCase {
public:
	WifiL2TestCase() :
		ns3::TestCase("WifiL2TestCase") {
	}
	virtual ~WifiL2TestCase() {
	}
	virtual void DoRun() {
		NS_LOG_UNCOND("WifiL2TestCase::DoRun");
		auto n1 = createNode(ns3::Vector3D(0, 0, 0), std::string("channel1"));
		auto n2 = createNode(ns3::Vector3D(1, 0, 0), std::string("channel1"));
		ns3::Simulator::Schedule(ns3::Seconds(1.0),
				&WifiL2TestCase::SendOnePacket, n1);
	}

private:

	static void SendOnePacket(ns3::Ptr<ns3::Node> node) {
		auto device = node->GetObject<ns3::WifiNetDevice> ();
		NS_ASSERT(device != NULL);
		ns3::Ptr<ns3::Packet> packet = ns3::Create<ns3::Packet>();
		device->Send(packet, device->GetBroadcast(), 1);
	}

	static ns3::Ptr<ns3::Node> createNode(ns3::Vector3D position,
			const std::string channel_name) {
		auto mac11 = createMac();
		auto device11 = createDevice(mac11);
		auto mobility11 = createMobility(position);
		auto node11 = createNode(device11, mobility11);
		auto channel = ns3::Names::Find<ns3::YansWifiChannel>(channel_name);
		if (channel == NULL) {
			channel = createChannel();
		}
		auto phy1 = createPhy(channel);
		bindDeviceAndPhy(device11, phy1);
		return node11;
	}

	static ns3::Ptr<ns3::YansWifiChannel> createChannel(
			std::string s_delay_type_id =
					"ns3::ConstantSpeedPropagationDelayModel") {
		auto channel = ns3::CreateObject<ns3::YansWifiChannel>();
		auto of = ns3::ObjectFactory();
		of.SetTypeId(s_delay_type_id);
		auto delay = of.Create<ns3::PropagationDelayModel> ();
		channel->SetPropagationDelayModel(delay);
		auto loss = ns3::CreateObject<ns3::RandomPropagationLossModel>();
		channel->SetPropagationLossModel(loss);
		return channel;
	}

	static ns3::Ptr<ns3::WifiMac> createMac(
			const std::string s_type_id = "ns3::AdhocWifiMac") {
		ns3::ObjectFactory of;
		of.SetTypeId(s_type_id);
		ns3::Ptr<ns3::WifiMac> mac = of.Create<ns3::WifiMac> ();
		mac->ConfigureStandard(ns3::WIFI_PHY_STANDARD_80211a);
		mac->SetAddress(ns3::Mac48Address::Allocate());
		return mac;
	}

	static ns3::Ptr<ns3::MobilityModel> createMobility(ns3::Vector3D vector) {
		auto mobility = ns3::CreateObject<ns3::ConstantPositionMobilityModel>();
		mobility->SetPosition(vector);
		return mobility;
	}

	static ns3::Ptr<ns3::YansWifiPhy> createPhy(
			ns3::Ptr<ns3::YansWifiChannel> channel) {
		auto phy = ns3::CreateObject<ns3::YansWifiPhy>();
		auto error = ns3::CreateObject<ns3::YansErrorRateModel>();
		phy->SetErrorRateModel(error);
		phy->SetChannel(channel);
		phy->ConfigureStandard(ns3::WIFI_PHY_STANDARD_80211a);
		return phy;
	}

	static ns3::Ptr<ns3::WifiNetDevice> createDevice(
			ns3::Ptr<ns3::WifiMac> mac,
			std::string s_manager_type_id = "ns3::IdealWifiManager") {
		auto device = ns3::CreateObject<ns3::WifiNetDevice>();
		device->SetMac(mac);
		//device->SetPhy(phy);
		ns3::ObjectFactory of;
		of.SetTypeId(s_manager_type_id);
		auto manager = of.Create<ns3::WifiRemoteStationManager> ();
		device->SetRemoteStationManager(manager);
		return device;
	}

	static ns3::Ptr<ns3::Node> createNode(ns3::Ptr<ns3::WifiNetDevice> device,
			ns3::Ptr<ns3::MobilityModel> mobility) {
		auto node = ns3::CreateObject<ns3::Node>();
		node->AddDevice(device);
		node->AggregateObject(mobility);
		return node;
	}

	static void bindDeviceAndPhy(ns3::Ptr<ns3::WifiNetDevice> device,
			ns3::Ptr<ns3::YansWifiPhy> phy) {
		device->SetPhy(phy);
		phy->SetDevice(device);
		phy->SetMobility(device->GetNode());
	}

};

class WifiTestSuite: public ns3::TestSuite {
public:
	WifiTestSuite() :
		ns3::TestSuite("WifiTestSuite", UNIT) {
		NS_LOG_DEBUG("constructing WifiTestSuite");
		AddTestCase(new WifiTestCase, ns3::TestCase::QUICK);
		AddTestCase(new WifiL2TestCase, ns3::TestCase::QUICK);
	}
};

static WifiTestSuite wifi_test_suite;
