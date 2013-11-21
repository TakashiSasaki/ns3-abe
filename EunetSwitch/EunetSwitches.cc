#define NS3_LOG_ENABLE 1
#include "ns3/log.h"
#include "ns3/ipv4-address-helper.h"
NS_LOG_COMPONENT_DEFINE("EunetSwitches");
#include <cmath>
#include "EunetSwitches.h"

EunetSwitches::EunetSwitches(const int depth, const int width) :
	nDepth(depth), nWidth(width) {
	for (int i = 0; i < depth; ++i) {
		std::vector<ns3::Ptr<EunetSwitch> > switches;
		for (int j = 0; j < pow(width, i); ++j) {
			NS_LOG_INFO("creating EunetSwitch "<< i << "," << j);
			ns3::Ptr<EunetSwitch> p_switch(new EunetSwitch());
			switches.push_back(p_switch);
		}//for
		this->switches.push_back(switches);
	}//for

	for (auto i = this->switches.begin(); i != this->switches.end(); ++i) {
		for (auto j = i->begin(); j != i->end(); ++j) {
			NS_LOG_INFO("tarversing EunetSwitch " << (**j).GetId());
		}//for
	}//for

	for (unsigned i = 1; i < this->switches.size(); ++i) {
		for (unsigned j = 0; j < this->switches[i].size(); ++j) {
			NS_LOG_INFO("connecting EunetSwitch " << i << "," << j << " to " << i-1 << "," << j/width << "," << j%width);
			this->switches[i][j]->connectUpTo(0, ns3::Ptr<EunetSwitch>(
					switches[i - 1][j / width]), j % width);
		}//for
	}//for

	this->assignAddresses();
}// a constructor

EunetSwitches::~EunetSwitches() {
	// TODO !CodeTemplates.destructorstub.tododesc!
}

ns3::NetDeviceContainer EunetSwitches::getTerminalDevices() {
	ns3::NetDeviceContainer ndc;
	for (auto i = switches.begin(); i != switches.end(); ++i) {
		for (auto j = i->begin(); j != i->end(); ++j) {
			ndc.Add((**j).getTerminalDevices());
		}
	}//for
	return ndc;
}

void EunetSwitches::assignAddresses() {
	NS_LOG_INFO ("assigning IP addresses.");
	ns3::Ipv4AddressHelper ipv4_address_helper;
	ipv4_address_helper.SetBase("10.0.0.0", "255.0.0.0");
	ipv4_address_helper.Assign(this->getTerminalDevices());
}
