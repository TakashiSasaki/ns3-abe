#define NS3_LOG_ENABLE 1
#include "ns3/log.h"
NS_LOG_COMPONENT_DEFINE("EunetMobile");
#define NS3_ASSERT_ENABLE 1
#include "ns3/assert.h"
#include "ns3/wifi-helper.h"
#include "ns3/nqos-wifi-mac-helper.h"
#include "ns3/yans-wifi-helper.h"
#include "ns3/ssid.h"
#include "ns3/wifi-net-device.h"
#include "ns3/mobility-helper.h"
#include "EunetMobile.h"
NS_OBJECT_ENSURE_REGISTERED(EunetMobile);

ns3::TypeId EunetMobile::GetTypeId(void) {
	static ns3::TypeId type_id =
			ns3::TypeId("EunetMobile").SetParent<OnOffNode> ().AddConstructor<
					EunetMobile> ();
	return type_id;
}//GetTypeId

EunetMobile::EunetMobile() :
	TraceBase(this), MobilityBase(this, ns3::Vector(0, /*this->GetId()*/0, 0)),
			WifiBase(this, WifiBase::StaWifiMac, true),
			isNotifyConstructionCompletedCalled(false), isDoInitializeCalled(
					false), isDoDisposeCalled(false) {
}// the default constructor

void EunetMobile::DoInitialize() {
	NS_ASSERT(!this->isDoInitializeCalled);
	this->isDoInitializeCalled = true;
	MobilityBase::DoInitialize();
	WifiBase::DoInitialize();
	OnOffNode::DoInitialize();
}//DoInitialize

void EunetMobile::NotifyConstructionCompleted() {
	NS_ASSERT(!this->isNotifyConstructionCompletedCalled);
	this->isNotifyConstructionCompletedCalled = true;
	for (unsigned i = 0; i < this->GetNDevices(); ++i) {
		NS_LOG_INFO(this->GetDevice(i)->GetTypeId().GetName());
	}//for
	NS_ASSERT(this->GetNDevices() == 2);
	OnOffNode::NotifyConstructionCompleted();
	NS_ASSERT(this->GetNDevices() == 3);
}//NotifyConstructionCompleted
