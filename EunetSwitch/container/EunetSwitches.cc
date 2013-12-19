#define NS3_LOG_ENABLE 1
#include "ns3/log.h"
NS_LOG_COMPONENT_DEFINE("EunetSwitches");
#define NS3_ASSERT_ENABLE 1
#include "ns3/assert.h"
#include "ns3/ipv4-address-helper.h"
#include "ns3/mobility-helper.h"
#include "EunetSwitches.h"

EunetSwitches::EunetSwitches(const unsigned depth, const unsigned width) :
	nDepth(depth), nWidth(width) {
	NS_LOG_INFO("creating as a regular tree with depth " << nDepth << " and width " << nWidth);
	for (unsigned i = 0; i < depth; ++i) {
		//std::vector<ns3::Ptr<EunetSwitch> > switches;
		for (unsigned j = 0; j < pow(width, i); ++j) {
			NS_LOG_INFO("creating EunetSwitch at depth "<< i << " and width " << j);
			auto p(ns3::CreateObject<EunetSwitch>());
			this->Add(p);
		}//for
		//this->switches.push_back(switches);
	}//for
	NS_ASSERT(this->GetN() == countTriangle(nDepth));
	for (unsigned d = 1; d < nDepth; ++d) {
		for (unsigned w = 0; w < pow(width, d); ++w) {
			NS_LOG_INFO("connecting EunetSwitch "
					<< d << "," << w << " (" << countTriangle(d)+w << ") to "
					<< d-1 << "," << w/width << " (" << countTriangle(d-1) + w/width << ")" << ", " << w%width );
			ns3::Ptr<EunetSwitch> p_from = this->getEunetSwitch(
					countTriangle(d) + w);
			ns3::Ptr<EunetSwitch> p_to = this->getEunetSwitch(countTriangle(d
					- 1) + w / width);
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

	ns3::MobilityHelper mobility_helper;
	mobility_helper.SetMobilityModel("ns3::ConstantPositionMobilityModel");
	mobility_helper.Install(*this);

}// a constructor

ns3::Ptr<EunetSwitch> EunetSwitches::getEunetSwitch(unsigned i_depth,
		unsigned i_width) {
	return getEunetSwitch(countTriangle(i_depth) + i_width);
}
