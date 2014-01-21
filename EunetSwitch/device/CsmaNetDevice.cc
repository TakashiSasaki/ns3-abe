#define NS3_LOG_ENABLE 1
#include "ns3/log.h"
NS_LOG_COMPONENT_DEFINE("CsmaNetDevice");
#define NS3_ASSERT_ENABLE 1
#include "ns3/assert.h"
#include "ns3/csma-net-device.h"
#include "CsmaNetDevice.h"
NS_OBJECT_ENSURE_REGISTERED(CsmaNetDevice);

ns3::TypeId CsmaNetDevice::GetTypeId(void) {
	static ns3::TypeId type_id = ns3::TypeId("CsmaNetDevice"). SetParent<
			ns3::CsmaNetDevice> () .AddConstructor<CsmaNetDevice> ();
	return type_id;
}//GetTypeId

CsmaNetDevice::CsmaNetDevice() {
}

CsmaNetDevice::~CsmaNetDevice() {
}
