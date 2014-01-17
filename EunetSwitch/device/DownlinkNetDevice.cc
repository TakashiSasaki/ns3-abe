#define NS3_LOG_ENABLE 1
#include "ns3/log.h"
NS_LOG_COMPONENT_DEFINE("DownlinkNetDevice");
#define NS3_ASSERT_ENABLE 1
#include "ns3/assert.h"
#include "ns3/csma-net-device.h"
#include "DownlinkNetDevice.h"
NS_OBJECT_ENSURE_REGISTERED(DownlinkNetDevice);

ns3::TypeId DownlinkNetDevice::GetTypeId(void) {
	static ns3::TypeId type_id = ns3::TypeId("DownlinkNetDevice");
	type_id.SetParent<ns3::CsmaNetDevice> ();
	type_id.AddConstructor<DownlinkNetDevice> ();
	return type_id;
}//GetTypeId

DownlinkNetDevice::DownlinkNetDevice() {
}

DownlinkNetDevice::~DownlinkNetDevice() {
}
