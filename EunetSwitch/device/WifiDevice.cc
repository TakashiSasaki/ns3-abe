#define NS3_LOG_ENABLE 1
#include "ns3/log.h"
NS_LOG_COMPONENT_DEFINE("WifiDevice");
#define NS3_ASSERT_ENABLE 1
#include "ns3/assert.h"
#include "ns3/names.h"
#include "ns3/yans-wifi-helper.h"
#include "WifiDevice.h"

WifiDevice::WifiDevice() {
	// TODO 自動生成されたコンストラクター・スタブ

}

WifiDevice::~WifiDevice() {
	// TODO !CodeTemplates.destructorstub.tododesc!
}

void WifiDevice::enablePcap(const bool promiscuous) {
	auto name = ns3::Names::FindName(this);
	if (name.empty()) {
		std::ostringstream oss;
		oss << this->GetInstanceTypeId() << "-" << this->GetNode()->GetId()
				<< "-" << this->GetIfIndex();
		name = oss.str();
	}
	{
		NS_LOG_DEBUG("enablePcap on node " << name);
		ns3::YansWifiPhyHelper yans_wifi_phy_helper;
		yans_wifi_phy_helper.EnablePcap(name, this, promiscuous);
	}
}//enablePcap
