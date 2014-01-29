#include "DeviceGetterMixin.h"
#include "CsmaDevice.h"

DeviceGetterMixin::DeviceGetterMixin() {
}

DeviceGetterMixin::~DeviceGetterMixin() {
}

template ns3::Ptr<CsmaDevice> DeviceGetterMixin::getDevice<CsmaDevice>(
		ns3::Ipv4Address ipv4_address);

int DeviceGetterMixin::getInt() {
	return 12345;
}
