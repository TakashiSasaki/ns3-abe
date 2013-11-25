#define NS3_LOG_ENABLE 1
#include "ns3/log.h"
NS_LOG_COMPONENT_DEFINE("EunetTerminal");
#define NS3_ASSERT_ENABLE 1
#include "ns3/assert.h"
#include "ns3/ipv4.h"
#include "ns3/internet-module.h"
#include "EunetTerminal.h"
NS_OBJECT_ENSURE_REGISTERED(EunetTerminal);

ns3::TypeId EunetTerminal::GetTypeId(void) {
	static ns3::TypeId type_id =
			ns3::TypeId("EunetTerminal").SetParent<Base> ().AddConstructor<
					EunetTerminal> ();
	return type_id;
}//GetTypeId

EunetTerminal::EunetTerminal() {
	NS_ASSERT(this->GetNDevices() == 1);
	//this->installInternetStack();
	//this->installPacketSink();
}

void EunetTerminal::DoInitialize() {
	Base::DoInitialize();
}

void EunetTerminal::NotifyConstructionCompleted() {
	NS_LOG_INFO("notified the completion of EunetTerminal");
	NS_ASSERT(this->GetNDevices() == 1);
	Base::NotifyConstructionCompleted();
	NS_ASSERT(this->GetNDevices() == 2);
}

EunetTerminal::~EunetTerminal() {
	// TODO !CodeTemplates.destructorstub.tododesc!
}

