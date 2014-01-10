#define NS3_LOG_ENABLE 1
#include "ns3/log.h"
NS_LOG_COMPONENT_DEFINE("EunetTerminal");
#define NS3_ASSERT_ENABLE 1
#include "ns3/assert.h"
#include "ns3/ipv4.h"
#include "ns3/internet-module.h"
#include "ns3/mobility-helper.h"
#include "EunetTerminal.h"
NS_OBJECT_ENSURE_REGISTERED(EunetTerminal);

ns3::TypeId EunetTerminal::GetTypeId(void) {
	static ns3::TypeId type_id = ns3::TypeId("EunetTerminal").SetParent<
			OnOffNode> ().AddConstructor<EunetTerminal> ();
	return type_id;
}//GetTypeId

EunetTerminal::EunetTerminal() {
	NS_ASSERT(this->GetNDevices() == 1);
	//this->installInternetStack();
	//this->installPacketSink();
}

void EunetTerminal::DoInitialize() {
	OnOffNode::DoInitialize();
}

void EunetTerminal::DoDispose(){
}

void EunetTerminal::NotifyConstructionCompleted() {
	NS_LOG_INFO("notified the completion of EunetTerminal");
	NS_ASSERT(this->GetNDevices() == 1);
	OnOffNode::NotifyConstructionCompleted();
	NS_ASSERT(this->GetNDevices() == 2);
}
