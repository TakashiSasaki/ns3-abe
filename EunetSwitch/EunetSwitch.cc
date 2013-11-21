#define NS3_LOG_ENABLE 1
#include "ns3/log.h"
#include "EunetSwitch.h"
NS_LOG_COMPONENT_DEFINE("EunetSwitch");

const char* const EunetSwitch::pcapPrefix = "EunetSwitch";

EunetSwitch::~EunetSwitch() {
}

int EunetSwitch::nCreated = 0;

EunetSwitch::EunetSwitch(const int n_downlink_ports, const int n_downlink_bps,
		const int n_downlink_delay_milliseconds, const int n_uplink_ports,
		const int n_uplink_bps, const int n_uplink_delay_milliseconds) :
	uplinkPortIndices(n_uplink_ports), downlinkPortIndices(n_downlink_ports),
			nDownlinkPorts(n_downlink_ports), nDownlinkBps(n_downlink_bps),
			nDownlinkDelayMilliseconds(n_downlink_delay_milliseconds),
			nUplinkPorts(n_uplink_ports), nUplinkBps(n_uplink_bps),
			nUplinkDelayMilliseconds(n_uplink_delay_milliseconds) {
	this->ncTerminals.Create(n_downlink_ports);
	this->deployTerminals();
	ns3::InternetStackHelper internet_stack_helper;
	internet_stack_helper.Install(ncTerminals);
	//internet_stack_helper.Install(ncTerminals.getTerminals());
	//ns3::Simulator::Schedule(ns3::Seconds(0.0), ns3::MakeCallback(&bridgeAllPorts, this));
	this->nCreated += 1;
	NS_LOG_INFO("constructing EunetSwitch " << this->nCreated);
}//a constructor
