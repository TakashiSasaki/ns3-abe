#define NS3_LOG_ENABLE 1
#include "ns3/log.h"
NS_LOG_COMPONENT_DEFINE("DownlinkDevice");
#define NS3_ASSERT_ENABLE 1
#include "ns3/assert.h"
#include "ns3/csma-net-device.h"
#include "DownlinkDevice.h"
NS_OBJECT_ENSURE_REGISTERED(DownlinkDevice);

ns3::TypeId DownlinkDevice::GetTypeId(void) {
	static ns3::TypeId type_id = ns3::TypeId("DownlinkDevice").SetParent<
			CsmaDevice> ().AddConstructor<DownlinkDevice> ();
	return type_id;
}//GetTypeId

DownlinkDevice::DownlinkDevice() {
}

DownlinkDevice::~DownlinkDevice() {
}
