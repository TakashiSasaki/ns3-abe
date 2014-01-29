#include "DeviceGetterMixin.h"
#include "CsmaDevice.h"

DeviceGetterMixin::DeviceGetterMixin() {
	// TODO 自動生成されたコンストラクター・スタブ

}

DeviceGetterMixin::~DeviceGetterMixin() {
	// TODO !CodeTemplates.destructorstub.tododesc!
}

template ns3::Ptr<CsmaDevice> DeviceGetterMixin::getDevice<CsmaDevice>(
		ns3::Ipv4Address ipv4_address);
