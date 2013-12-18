#define NS3_LOG_ENABLE 1
#include "ns3/log.h"
NS_LOG_COMPONENT_DEFINE("BridgingAp");
#define NS3_ASSERT_ENABLE 1
#include "ns3/assert.h"
#include "ns3/wifi-helper.h"
#include "ns3/nqos-wifi-mac-helper.h"
#include "ns3/yans-wifi-helper.h"
#include "ns3/ssid.h"
#include "ns3/boolean.h"
#include "ns3/mobility-helper.h"
#include "ns3/ap-wifi-mac.h"
#include "ns3/wifi-net-device.h"
#include "ns3/bridge-net-device.h"
#include "SimpleAp.h"
#include "BridgingAp.h"
NS_OBJECT_ENSURE_REGISTERED(BridgingAp);

ns3::TypeId SimpleAp::GetTypeId(void) {
	static ns3::TypeId type_id =
			ns3::TypeId("BridgingAp").SetParent<SimpleAp> ().AddConstructor<
					BridgingAp> ();
	return type_id;
}//GetTypeId

BridgingAp::BridgingAp() {
	// TODO 自動生成されたコンストラクター・スタブ

}

BridgingAp::~BridgingAp() {
	// TODO !CodeTemplates.destructorstub.tododesc!
}

void SimpleAp::DoInitialize() {
	NS_LOG_INFO("calling up SimpleAp::DoInitialize");
	Base::DoInitialize();
}

void BridgingAp::NotifyConstructionCompleted() {
	ns3::Ptr<ns3::BridgeNetDevice> ptr_bridge_net_device = this->getNetDevice<
			ns3::BridgeNetDevice> ();
	NS_ASSERT(ptr_bridge_net_device != 0);
	ns3::Ptr<ns3::WifiNetDevice> ptr_wifi_net_device = this->getNetDevice<
			ns3::WifiNetDevice> ();
	NS_ASSERT(ptr_wifi_net_device != 0);
	ptr_bridge_net_device->AddBridgePort(ptr_wifi_net_device);
	NS_LOG_INFO("just calling up SimpleAp::NotifyConstructionCompleted");
	Base::NotifyConstructionCompleted();
}
