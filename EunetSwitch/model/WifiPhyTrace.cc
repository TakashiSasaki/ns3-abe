#include <iostream>
#include <iomanip>
#define NS3_LOG_ENABLE 1
#include "ns3/log.h"
NS_LOG_COMPONENT_DEFINE("WifiPhyTrace");
#define NS3_ASSERT_ENABLE 1
#include "ns3/assert.h"
#include "ns3/simulator.h"
#include "WifiPhyTrace.h"

WifiPhyTrace::WifiPhyTrace(ns3::Node* p_node) :
	TraceBase(p_node) {
}

WifiPhyTrace::~WifiPhyTrace() {
	// TODO !CodeTemplates.destructorstub.tododesc!
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
