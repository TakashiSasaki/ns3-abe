#define NS3_LOG_ENABLE 1
#include "ns3/log.h"
NS_LOG_COMPONENT_DEFINE("AddressGetterMixin");
#define NS3_ASSERT_ENABLE 1
#include "ns3/assert.h"
#include "ns3/node.h"
#include "ns3/ipv4.h"
#include "AddressGetterMixin.h"

AddressGetterMixin::AddressGetterMixin() {
}

AddressGetterMixin::~AddressGetterMixin() {
}

#if 0
ns3::Ipv4Address AddressGetterMixin::getAddress() {
	auto device = this->getNetDevice1();
	NS_ASSERT(device != NULL);
	auto node = device->GetNode();
	NS_ASSERT(node != NULL);
	auto ipv4 = node->GetObject<ns3::Ipv4> ();
	NS_ASSERT(ipv4 != NULL);
	const auto i_interface = ipv4->GetInterfaceForDevice(device);
	NS_ASSERT(i_interface != -1);
	const auto n_addresses = ipv4->GetNAddresses(i_interface);
	NS_ASSERT(n_addresses == 0);
	auto ipv4_interface_address = ipv4->GetAddress(i_interface, 0);
	auto ipv4_address = ipv4_interface_address.GetLocal();
	return ipv4_address;
}

ns3::Ptr<ns3::NetDevice> AddressGetterMixin::getNetDevice3() {
	return ns3::CreateObject<ns3::CsmaNetDevice>();
}
#endif

int AddressGetterMixin::getInt() {
	return 1234567;
}
