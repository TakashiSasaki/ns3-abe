#define NS3_LOG_ENABLE 1
#include "ns3/log.h"
NS_LOG_COMPONENT_DEFINE("UplinkNetDevice");
#define NS3_ASSERT_ENABLE 1
#include "ns3/assert.h"
#include "ns3/csma-net-device.h"
#include "UplinkNetDevice.h"
NS_OBJECT_ENSURE_REGISTERED(UplinkNetDevice);

ns3::TypeId UplinkNetDevice::GetTypeId(void) {
	static ns3::TypeId type_id = ns3::TypeId("CsmaChannelNode"). SetParent<
			ns3::CsmaNetDevice> () .AddConstructor<UplinkNetDevice> ();
	return type_id;
}//GetTypeId

UplinkNetDevice::UplinkNetDevice() {
}

UplinkNetDevice::~UplinkNetDevice() {
}
