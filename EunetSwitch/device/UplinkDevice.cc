#define NS3_LOG_ENABLE 1
#include "ns3/log.h"
NS_LOG_COMPONENT_DEFINE("UplinkDevice");
#define NS3_ASSERT_ENABLE 1
#include "ns3/assert.h"
#include "ns3/csma-net-device.h"
#include "UplinkDevice.h"
#include "CsmaDevice.h"
NS_OBJECT_ENSURE_REGISTERED(UplinkDevice);

ns3::TypeId UplinkDevice::GetTypeId(void) {
	static ns3::TypeId type_id = ns3::TypeId("UplinkDevice"). SetParent<
			CsmaDevice> () .AddConstructor<UplinkDevice> ();
	return type_id;
}//GetTypeId

UplinkDevice::UplinkDevice() {
}

UplinkDevice::~UplinkDevice() {
}
