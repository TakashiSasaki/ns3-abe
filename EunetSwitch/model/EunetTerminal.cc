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

EunetTerminal::EunetTerminal() :
	INIT_DIDDNCC_FLAGS
{
	NS_LOG_INFO("the constructor of EunetTerminal");
	//this->installInternetStack();
	//this->installPacketSink();
}

void EunetTerminal::NotifyConstructionCompleted() {
	ASSERT_NCC;
	NS_ASSERT(this->GetNDevices()==0);
	//NS_ASSERT_MSG(this->GetNDevices() == 1, this->GetNDevices() << " " << this->getNDevices<ns3::CsmaNetDevice>());
	OnOffNode::NotifyConstructionCompleted();
	//NS_ASSERT(this->GetNDevices() == 2);
	NS_ASSERT(this->GetNDevices()==nPorts+1);
}
void EunetTerminal::DoInitialize() {
	ASSERT_DI;
	NS_ASSERT(this->GetNDevices()==nPorts+1);
	OnOffNode::DoInitialize();
	NS_ASSERT_MSG(this->GetNDevices() == nPorts+1, "GetNDevices=" << this->GetNDevices() << " csma=" << this->getNDevices<ns3::CsmaNetDevice>() << " loopback=" << this->getNDevices<ns3::LoopbackNetDevice>());
}

void EunetTerminal::DoDispose() {
	ASSERT_DD;
	OnOffNode::DoDispose();
}

