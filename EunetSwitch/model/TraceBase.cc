#include <iostream>
#include <iomanip>
#include "ns3/node.h"
#include "TraceBase.h"

void TraceBase::getHex(std::ostream& os, ns3::Ptr<const ns3::Packet> ptr_packet) {

	uint8_t buffer[ptr_packet->GetSize()];
	for (unsigned i = 0; i < sizeof buffer; ++i) {
		os << std::hex << std::setw(2) << std::setfill('0')
				<< (unsigned) buffer[i];
	}//for
}//getHex

TraceBase::TraceBase(ns3::Node* p_node) :
	ptrNode(p_node, true) {
}

TraceBase::~TraceBase() {
	// TODO !CodeTemplates.destructorstub.tododesc!
}
