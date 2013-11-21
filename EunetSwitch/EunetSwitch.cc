#define NS3_LOG_ENABLE 1
#include "ns3/log.h"
#include "ns3/applications-module.h"
#include "ns3/internet-module.h"
#include "ns3/network-module.h"
#include "ns3/ipv4-address.h"
#include "ns3/inet-socket-address.h"
#include "EunetSwitch.h"
#include "EunetTerminal.h"
NS_LOG_COMPONENT_DEFINE("EunetSwitch");

const char* const EunetSwitch::pcapPrefix = "EunetSwitch";
const char* const EunetSwitch::asciiTraceFileName = "EunetSwitch.tr";

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
	for (int i = 0; i < n_downlink_ports; ++i) {
		this->ncTerminals.Add(ns3::CreateObject<EunetTerminal>());
	}
	//this->ncTerminals.Create(n_downlink_ports);
	this->deployTerminals();
	ns3::InternetStackHelper internet_stack_helper;
	internet_stack_helper.Install(ncTerminals);
	//internet_stack_helper.Install(ncTerminals.getTerminals());
	//ns3::Simulator::Schedule(ns3::Seconds(0.0), ns3::MakeCallback(&bridgeAllPorts, this));
	this->nCreated += 1;
	NS_LOG_INFO("constructing EunetSwitch " << this->nCreated);
	{
		ns3::AsciiTraceHelper ascii_trace_helper;
		this->oswAsciiTrace = ascii_trace_helper.CreateFileStream(
				this->asciiTraceFileName);
	}
}//a constructor

void EunetSwitch::deployTerminal(const int i_downlink_port) {
	const int n_devices_before = this->GetNDevices();
	ns3::NetDeviceContainer link = this->getDownlinkCsmaHelper()->Install(
			ns3::NodeContainer(ns3::NodeContainer(this->ncTerminals.Get(
					i_downlink_port)), ns3::NodeContainer(this)));
	assert(this->ncTerminals.Get(i_downlink_port)->GetNDevices()==1);
	//this->ncTerminals.Get(0)->AddDevice(link.Get(0));
	const int n_devices_after = this->GetNDevices();
	NS_LOG_INFO("# of devices " << "on switch " << this->GetId() << " was changed from " << n_devices_before << " to " << n_devices_after);
	this->downlinkPortIndices[i_downlink_port] = this->GetNDevices() - 1;
}//deployTerminal
