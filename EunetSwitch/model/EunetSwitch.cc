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
#include "SimpleSwitch.h"

NS_OBJECT_ENSURE_REGISTERED(EunetSwitch);

ns3::TypeId EunetSwitch::GetTypeId(void) {
	static ns3::TypeId type_id = ns3::TypeId("EunetSwitch").SetParent<
			SimpleSwitch> ().AddConstructor<EunetSwitch> ();
	return type_id;
}//GetTypeId


const char* const EunetSwitch::pcapPrefix = "EunetSwitch";
const char* const EunetSwitch::asciiTracePrefix = "EunetSwitch";

EunetSwitch::EunetSwitch(const unsigned n_downlink_ports,
		const unsigned n_uplink_ports) :
	SimpleSwitch(n_downlink_ports, n_uplink_ports), eunetTerminals(
			n_downlink_ports), isNotifyConstructionCompletedCalled(false),
			isDoInitializeCalled(false), isDoDisposeCalled(false) {
	NS_LOG_INFO("constructing EunetSwitch");
	//ns3::Simulator::Schedule(ns3::Seconds(0.0), ns3::MakeCallback(&bridgeAllPorts, this));
#if 0
	{
		ns3::AsciiTraceHelper ascii_trace_helper;
		this->oswAsciiTrace = ascii_trace_helper.CreateFileStream(
				this->asciiTraceFileName);
	}
#endif

	NS_LOG_INFO("attaching " << this->eunetTerminals.GetN() << " terminal(s) to corresponding port(s)");
	for (unsigned i = 0; i < this->eunetTerminals.GetN(); ++i) {
		NS_LOG_INFO("attaching terminal " << i << " to corresponding port");
		this->bring(i, this->eunetTerminals.Get(i), 0);
	}
}//a constructor

void EunetSwitch::DoInitialize() {
	NS_ASSERT(!this->isDoInitializeCalled);
	this->isDoInitializeCalled = true;
	SimpleSwitch::DoInitialize();
}//DoInitialize

void EunetSwitch::DoDispose() {
	NS_ASSERT(!this->isDoDisposeCalled);
	NS_ASSERT(this->isNotifyConstructionCompletedCalled);
	this->isDoDisposeCalled = true;
	SimpleSwitch::DoDispose();
}//DoDispose

void EunetSwitch::NotifyConstructionCompleted() {
	NS_ASSERT(!this->isNotifyConstructionCompletedCalled);
	this->isNotifyConstructionCompletedCalled = true;
	SimpleSwitch::NotifyConstructionCompleted();
}//NotifyConstructionCompleted
