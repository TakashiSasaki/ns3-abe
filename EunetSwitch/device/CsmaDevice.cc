#define NS3_LOG_ENABLE 1
#include "ns3/log.h"
NS_LOG_COMPONENT_DEFINE("CsmaDevice");
#define NS3_ASSERT_ENABLE 1
#include "ns3/assert.h"
#include "ns3/csma-net-device.h"
#include "ns3/csma-channel.h"
#include "CsmaDevice.h"
NS_OBJECT_ENSURE_REGISTERED(CsmaDevice);

ns3::TypeId CsmaDevice::GetTypeId(void) {
	static ns3::TypeId type_id = ns3::TypeId("CsmaDevice"). SetParent<
			ns3::CsmaNetDevice> () .AddConstructor<CsmaDevice> ();
	return type_id;
}//GetTypeId

CsmaDevice::CsmaDevice() {
}

CsmaDevice::~CsmaDevice() {
}

void CsmaDevice::joinTo(ns3::Ptr<CsmaDevice> their_device) {
	auto their_channel =
			their_device->GetChannel()->GetObject<ns3::CsmaChannel> ();
	this->Attach(their_channel);
}
