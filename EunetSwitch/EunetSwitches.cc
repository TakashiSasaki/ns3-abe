#define NS3_LOG_ENABLE 1
#include "ns3/log.h"
NS_LOG_COMPONENT_DEFINE("EunetSwitches");
#define NS3_ASSERT_ENABLE 1
#include "ns3/assert.h"
#include "ns3/ipv4-address-helper.h"
#include <cmath>
#include "EunetSwitches.h"

unsigned count_nodes(const unsigned height, const unsigned width) {
	return (pow(width, height) - 1) / (width - 1);
}

EunetSwitches::EunetSwitches(const unsigned depth, const unsigned width) :
	nDepth(depth), nWidth(width) {
	NS_LOG_INFO("creating EunetSwitches");
	assert(count_nodes(2,3)==4);
	for (unsigned i = 0; i < depth; ++i) {
		//std::vector<ns3::Ptr<EunetSwitch> > switches;
		for (unsigned j = 0; j < pow(width, i); ++j) {
			NS_LOG_INFO("creating EunetSwitch at depth "<< i << " and width " << j);
			auto p(ns3::CreateObject<EunetSwitch>());
			this->Add(p);
		}//for
		//this->switches.push_back(switches);
	}//for
	NS_ASSERT(this->GetN() == count_nodes(depth, width));
	for (unsigned d = 1; d < nDepth; ++d) {
		for (unsigned w = 0; w < pow(width, d); ++w) {
			NS_LOG_INFO("connecting EunetSwitch "
					<< d << "," << w << " (" << count_nodes(d,width)+w << ") to "
					<< d-1 << "," << w/width << " (" << count_nodes( d-1, width) + w/width << ")" );
			ns3::Ptr<EunetSwitch> p_from = this->getEunetSwitch(count_nodes(d,
					width) + w);
			ns3::Ptr<EunetSwitch> p_to = this->getEunetSwitch(count_nodes(
					d - 1, width) + w / width);
			p_from->connectUpTo(0, p_to, w % width);
		}//for
	}//for

	NS_LOG_INFO ("assigning IP addresses.");
	ns3::Ipv4AddressHelper ipv4_address_helper;
	ipv4_address_helper.SetBase("10.0.0.0", "255.0.0.0");
	for (unsigned i = 0; i < this->GetN(); ++i) {
		ipv4_address_helper.Assign(
				this->getEunetSwitch(i)->getTerminalDevices());
	}//for
}// a constructor

ns3::Ptr<EunetSwitch> EunetSwitches::getEunetSwitch(unsigned i_depth,
		unsigned i_width) {
	return getEunetSwitch(count_nodes(i_depth, nWidth) + i_width);
}
