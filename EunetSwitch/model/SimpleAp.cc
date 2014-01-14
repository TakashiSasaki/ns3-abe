#define NS3_LOG_ENABLE 1
#include "ns3/log.h"
NS_LOG_COMPONENT_DEFINE("SimpleAp");
#define NS3_ASSERT_ENABLE 1
#include "ns3/assert.h"
#include "ns3/wifi-helper.h"
#include "ns3/nqos-wifi-mac-helper.h"
#include "ns3/yans-wifi-helper.h"
#include "ns3/ssid.h"
#include "ns3/boolean.h"
#include "ns3/ap-wifi-mac.h"
#include "ns3/wifi-net-device.h"
#include "SimpleAp.h"
NS_OBJECT_ENSURE_REGISTERED(SimpleAp);

ns3::TypeId SimpleAp::GetTypeId(void) {
	static ns3::TypeId type_id =
			ns3::TypeId("SimpleAp").SetParent<SimpleSwitch> ().AddConstructor<
					SimpleAp> ();
	return type_id;
}//GetTypeId

SimpleAp::SimpleAp() :
	TraceBase(this), WifiBase(this, WifiBase::ApWifiMac, false), MobilityBase(
			this, ns3::Vector(
			/*this->GetId()*/0, 0, 0)), INIT_DIDDNCC_FLAGS {
}

void SimpleAp::DoInitialize() {
	ASSERT_DI;
	MobilityBase::DoInitialize();
	WifiBase::DoInitialize();
	Base::DoInitialize();
}

void SimpleAp::NotifyConstructionCompleted() {
	ASSERT_NCC;
	Base::NotifyConstructionCompleted();
}
