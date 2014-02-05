#include <iostream>
#include <iomanip>
#define NS3_LOG_ENABLE 1
#include "ns3/log.h"
NS_LOG_COMPONENT_DEFINE("TraceBase");
#define NS3_ASSERT_ENABLE 1
#include "ns3/assert.h"
#include "ns3/node.h"
#include "TraceBase.h"

void TraceBase::getHex(std::ostream& os, ns3::Ptr<const ns3::Packet> ptr_packet) {

	uint8_t buffer[ptr_packet->GetSize()];
	ptr_packet->CopyData(buffer, sizeof buffer);
	for (unsigned i = 0; i < sizeof buffer; ++i) {
		os << std::hex << std::setw(2) << std::setfill('0')
				<< (unsigned) buffer[i];
	}//for
}//getHex

TraceBase::TraceBase(ns3::Node* p_node) :
	ptrNode(p_node, true) {
}

TraceBase::TraceBase(ns3::Ptr<ns3::Node> node) :
	ptrNode(node) {
}

TraceBase::~TraceBase() {
	// TODO !CodeTemplates.destructorstub.tododesc!
}
