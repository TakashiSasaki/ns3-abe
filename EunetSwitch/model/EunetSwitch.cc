#include <memory>
#define NS3_LOG_ENABLE 1
#include "ns3/log.h"
NS_LOG_COMPONENT_DEFINE("EunetSwitch");
#define NS3_ASSERT_ENABLE 1
#include "ns3/assert.h"
#include "ns3/applications-module.h"
#include "ns3/network-module.h"
#include "ns3/ipv4-address.h"
#include "ns3/inet-socket-address.h"
#include "EunetSwitch.h"
#include "EunetTerminal.h"
#include "EunetTerminals.h"
#include "SimpleSwitch.h"

NS_OBJECT_ENSURE_REGISTERED(EunetSwitch);

ns3::TypeId EunetSwitch::GetTypeId(void) {
	static ns3::TypeId type_id = ns3::TypeId("EunetSwitch").SetParent<
			SimpleSwitch> ().AddConstructor<EunetSwitch> ();
	return type_id;
}//GetTypeId


const char* const EunetSwitch::pcapPrefix = "EunetSwitch";
const char* const EunetSwitch::asciiTracePrefix = "EunetSwitch";

EunetSwitch::EunetSwitch(/*const unsigned n_downlink_ports,
 const unsigned n_uplink_ports*/) :
	SimpleSwitch(/*n_downlink_ports, n_uplink_ports), eunetTerminals(
	 n_downlink_ports*/), INIT_DIDDNCC_FLAGS {
	NS_LOG_INFO("constructing EunetSwitch");
	//ns3::Simulator::Schedule(ns3::Seconds(0.0), ns3::MakeCallback(&bridgeAllPorts, this));
#if 0
	{
		ns3::AsciiTraceHelper ascii_trace_helper;
		this->oswAsciiTrace = ascii_trace_helper.CreateFileStream(
				this->asciiTraceFileName);
	}
#endif

}//a constructor

EunetSwitch::~EunetSwitch() {
}

void EunetSwitch::DoInitialize() {
	ASSERT_DI;
	SimpleSwitch::DoInitialize();
	this->eunetTerminals.initialize(this->nDownlinkPorts);
	NS_LOG_INFO("attaching " << this->eunetTerminals.GetN() << " terminal(s) to corresponding port(s)");
	for (unsigned i = 0; i < this->eunetTerminals.GetN(); ++i) {
		NS_LOG_INFO("attaching terminal " << i << " to corresponding port");
		this->bring<DownlinkNetDevice, ns3::CsmaNetDevice> (i,
				this->eunetTerminals.Get(i), 0);
	}//for
}//DoInitialize

void EunetSwitch::DoDispose() {
	ASSERT_DD;
	SimpleSwitch::DoDispose();
}//DoDispose

void EunetSwitch::NotifyConstructionCompleted() {
	ASSERT_NCC;
	SimpleSwitch::NotifyConstructionCompleted();
}//NotifyConstructionCompleted

void EunetSwitch::attachTerminals() {
	for (unsigned i = 0; i < this->nDownlinkPorts; ++i) {
		ns3::Ptr<DownlinkNetDevice> ptr_downlink_port = this->getNetDevice<
				DownlinkNetDevice> (i);
		ns3::Ptr<ns3::CsmaChannel> ptr_downlink_channel =
				ptr_downlink_port->GetChannel()->GetObject<ns3::CsmaChannel> ();
		ns3::Ptr<ns3::CsmaNetDevice>
				ptr_terminal_port = this->eunetTerminals.Get(i)->getNetDevice<
						ns3::CsmaNetDevice> ();
		ptr_terminal_port->Attach(ptr_downlink_channel);
	}//for
}

void EunetSwitch::detachTerminals() {
	for (unsigned i = 0; i < this->nDownlinkPorts; ++i) {
		ns3::Ptr<DownlinkNetDevice> ptr_downlink_port = this->getNetDevice<
				DownlinkNetDevice> (i);
		ns3::Ptr<ns3::CsmaChannel> ptr_downlink_channel =
				ptr_downlink_port->GetChannel()->GetObject<ns3::CsmaChannel> ();
		ns3::Ptr<ns3::CsmaNetDevice>
				ptr_terminal_port = this->eunetTerminals.Get(i)->getNetDevice<
						ns3::CsmaNetDevice> ();
		ptr_downlink_channel->Detach(ptr_terminal_port);
	}//for
}

