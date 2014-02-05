#include <iostream>
#include <iomanip>
#define NS3_LOG_ENABLE 1
#include "ns3/log.h"
NS_LOG_COMPONENT_DEFINE("WifiPhyTrace");
#define NS3_ASSERT_ENABLE 1
#include "ns3/assert.h"
#include "ns3/simulator.h"
#include "ns3/wifi-phy.h"
#include "ns3/wifi-net-device.h"
#include "WifiPhyTrace.h"

WifiPhyTrace::WifiPhyTrace(ns3::Ptr<ns3::Node> p_node) :
	TraceBase(p_node) {
	NS_LOG_DEBUG("WifiPhyTrace::WifiPhyTrace");
	for (unsigned i = 0; i < this->ptrNode->GetNDevices(); ++i) {
		auto ptr_net_device = this->ptrNode->GetDevice(i);
		auto type_id = ptr_net_device->GetInstanceTypeId();
		NS_LOG_INFO(type_id);
		if (!(type_id.IsChildOf(ns3::WifiNetDevice::GetTypeId()) || type_id
				== ns3::WifiNetDevice::GetTypeId()))
			continue;
		auto ptr_wifi_net_device =
				ptr_net_device->GetObject<ns3::WifiNetDevice> ();
		//auto ptr_wifi_mac = ptr_wifi_net_device->GetMac();
		auto ptr_wifi_phy = ptr_wifi_net_device->GetPhy();
		ptr_wifi_phy->TraceConnectWithoutContext("PhyTxBegin",
				ns3::MakeCallback(&WifiPhyTrace::tracePhyTxBegin, this));
		ptr_wifi_phy->TraceConnectWithoutContext("PhyTxEnd",
				ns3::MakeCallback(&WifiPhyTrace::tracePhyTxEnd, this));
		ptr_wifi_phy->TraceConnectWithoutContext("PhyTxDrop",
				ns3::MakeCallback(&WifiPhyTrace::tracePhyTxDrop, this));
		ptr_wifi_phy->TraceConnectWithoutContext("PhyRxBegin",
				ns3::MakeCallback(&WifiPhyTrace::tracePhyRxBegin, this));
		ptr_wifi_phy->TraceConnectWithoutContext("PhyRxEnd",
				ns3::MakeCallback(&WifiPhyTrace::tracePhyRxEnd, this));
		ptr_wifi_phy->TraceConnectWithoutContext("PhyRxDrop",
				ns3::MakeCallback(&WifiPhyTrace::tracePhyRxDrop, this));
	}//for
}

WifiPhyTrace::~WifiPhyTrace() {
}

void WifiPhyTrace::tracePhyTxBegin(ns3::Ptr<const ns3::Packet> ptr_packet) const {
	std::ostringstream oss;
	getHex(oss, ptr_packet);
	NS_LOG_INFO(ns3::Simulator::Now() << "\t" << ptr_packet->GetSize()
			<< " bytes " << "PhyTxBegin\ton node " << this->ptrNode->GetId()
			<< " " << oss.str());
}

void WifiPhyTrace::tracePhyTxEnd(ns3::Ptr<const ns3::Packet> ptr_packet) const {
	std::ostringstream oss;
	getHex(oss, ptr_packet);
	NS_LOG_INFO(ns3::Simulator::Now() << "\t" << ptr_packet->GetSize()
			<< " bytes " << "PhyTxEnd\ton node " << this->ptrNode->GetId()
			<< " " << oss.str());
}

void WifiPhyTrace::tracePhyTxDrop(ns3::Ptr<const ns3::Packet> ptr_packet) const {
	std::ostringstream oss;
	getHex(oss, ptr_packet);
	NS_LOG_INFO(ns3::Simulator::Now() << "\t" << ptr_packet->GetSize()
			<< " bytes " << "PhyTxDrop\ton node " << this->ptrNode->GetId()
			<< " " << oss.str());
}

void WifiPhyTrace::tracePhyRxBegin(ns3::Ptr<const ns3::Packet> ptr_packet) const {
	std::ostringstream oss;
	getHex(oss, ptr_packet);
	NS_LOG_INFO(ns3::Simulator::Now() << "\t" << ptr_packet->GetSize()
			<< " bytes " << "PhyRxBegin\ton node " << this->ptrNode->GetId()
			<< " " << oss.str());
}

void WifiPhyTrace::tracePhyRxEnd(ns3::Ptr<const ns3::Packet> ptr_packet) const {
	std::ostringstream oss;
	getHex(oss, ptr_packet);
	NS_LOG_INFO(ns3::Simulator::Now() << "\t" << ptr_packet->GetSize()
			<< " bytes " << "PhyRxEnd\ton node " << this->ptrNode->GetId()
			<< " " << oss.str());
}

void WifiPhyTrace::tracePhyRxDrop(ns3::Ptr<const ns3::Packet> ptr_packet) const {
	std::ostringstream oss;
	getHex(oss, ptr_packet);
	NS_LOG_INFO(ns3::Simulator::Now() << "\t" << ptr_packet->GetSize()
			<< " bytes " << "PhyRxDrop\ton node " << this->ptrNode->GetId()
			<< " " << oss.str());
}
