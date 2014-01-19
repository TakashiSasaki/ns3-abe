#include <string>
#define NS3_LOG_ENABLE 1
#include "ns3/log.h"
NS_LOG_COMPONENT_DEFINE("Eunet");
#define NS3_ASSERT_ENABLE 1
#include "ns3/assert.h"
#include "ns3/ipv4-address-helper.h"
#include "ns3/mobility-helper.h"
#include "Eunet.h"
#include "UplinkNetDevice.h"
#include "DownlinkNetDevice.h"

Eunet::Eunet() {
	this->eunetRouterFactory.SetTypeId(EunetRouter::GetTypeId());
	this->eunetSwitchFactory.SetTypeId(EunetSwitch::GetTypeId());
	this->eunetTerminalFactory.SetTypeId(EunetTerminal::GetTypeId());
}// a constructor

Eunet::~Eunet() {
}

template void Eunet::connect<EunetSwitch, UplinkNetDevice, EunetSwitch,
		DownlinkNetDevice>(std::string src_name, std::string dst_name,
		bool use_source_channel);
