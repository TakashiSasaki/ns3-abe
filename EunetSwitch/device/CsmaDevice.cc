#define NS3_LOG_ENABLE 1
#include "ns3/log.h"
NS_LOG_COMPONENT_DEFINE("CsmaDevice");
#define NS3_ASSERT_ENABLE 1
#include "ns3/assert.h"
#include "ns3/csma-net-device.h"
#include "ns3/csma-channel.h"
#include "ns3/csma-helper.h"
#include "ns3/names.h"
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

void CsmaDevice::enablePcap(const bool promiscuous) {
	auto name = ns3::Names::FindName(this);
	if (name.empty()) {
		std::ostringstream oss;
		auto type_id = this->GetInstanceTypeId();
		auto node_id = this->GetNode()->GetId();
		auto if_index = this->GetIfIndex();
		oss << type_id << "-" << node_id << "-" << if_index;
		name = oss.str();
	}
	NS_LOG_DEBUG("enablePcap on node " << name);
	ns3::CsmaHelper csma_helper;
	csma_helper.EnablePcap(name, this, promiscuous);
}//enablePcap

int CsmaDevice::getInt(const int i) {
	return i + 123;
}
