#ifndef CSMAINTERNETNODE_H_
#define CSMAINTERNETNODE_H_
#include "ns3/ipv4-address-helper.h"
#include "CsmaChannelNode.h"

class CsmaInternetNode: public CsmaChannelNode {
public:
	static ns3::TypeId GetTypeId(void);
	CsmaInternetNode(const int n_devices = 1);
	virtual ~CsmaInternetNode() {
	}
	;
	//ns3::Ipv4Address getCsmaNetDeviceAddress();

	template<class T>
	ns3::Ipv4Address getAddress(const unsigned i_device);
	template<class T>
	ns3::Ipv4InterfaceAddress getIpv4InterfaceAddress(const unsigned i_port);

	//void setAddress(ns3::Ipv4AddressHelper& ipv4_address_helper);
	void assignAddress(ns3::Ptr<ns3::CsmaNetDevice>, ns3::Ipv4AddressHelper&);
	//void assignAddress(const unsigned i_device, ns3::Ipv4AddressHelper&);
	void assignAddress(ns3::Ptr<ns3::CsmaNetDevice>, ns3::Ipv4Address ipv4_address,
			ns3::Ipv4Mask ipv4_mask);
private:
	static const ns3::Ipv4InterfaceAddress dummyAddress;
	void logAddress(const ns3::Ipv4Address& ipv4_address);
	void assignDummyAddress(ns3::Ptr<ns3::CsmaNetDevice>);
	void removeAllAddresses(ns3::Ptr<ns3::CsmaNetDevice>);
DECLARE_DIDDNCC
};

template<class T>
ns3::Ipv4Address CsmaInternetNode::getAddress(const unsigned i_device) {
	//this->logAllDevices(ns3::LOG_LEVEL_INFO);
	const unsigned n_devices_before = this->GetNDevices();
	NS_ASSERT(this->GetNDevices()>=2);
	ns3::Ptr<ns3::Ipv4> ptr_ipv4 = this->GetObject<ns3::Ipv4> ();
	ns3::Ptr<T> ptr_net_device = this->getNetDevice<T> (i_device);
	NS_ASSERT(ptr_net_device != 0);
	NS_ASSERT(ptr_net_device->GetInstanceTypeId().IsChildOf(ns3::NetDevice::GetTypeId()));
	const auto i_interface = ptr_ipv4->GetInterfaceForDevice(ptr_net_device);
	if (i_interface == -1) {
		NS_FATAL_ERROR("node " << this->GetId() << " " << T::GetTypeId() << " " << i_device <<
				" has no IPv4 interface.");
	}
	NS_ASSERT(i_interface != -1);
	const auto n_addresses = ptr_ipv4->GetNAddresses(i_interface);
	for (unsigned i_address = 0; i_address < n_addresses; ++i_address) {
		NS_LOG_DEBUG(ptr_ipv4->GetAddress(i_interface, i_address));
	}//for
	NS_ASSERT(n_addresses == 1);
	ns3::Ipv4InterfaceAddress ipv4_interface_address = ptr_ipv4->GetAddress(
			i_interface, 0);
	ns3::Ipv4Address ipv4_address = ipv4_interface_address.GetLocal();
	NS_ASSERT(this->GetNDevices()==n_devices_before);
	return ipv4_address;
}


template<class T>
ns3::Ipv4InterfaceAddress CsmaInternetNode::getIpv4InterfaceAddress(
		const unsigned i_port) {
	NS_ASSERT_MSG(this->getNDevices<T>()>i_port,
			"node " << this->GetId() << " has " << this->getNDevices<T>()<< " " << T::GetTypeId() << " devices, while looking for port "<< i_port);
	ns3::Ptr<ns3::Ipv4> ptr_ipv4 = this->GetObject<ns3::Ipv4> ();
	auto ptr_net_device = this->getNetDevice<T> (i_port);
	NS_ASSERT(ptr_net_device->GetInstanceTypeId()==T::GetTypeId());
	NS_ASSERT(ptr_net_device != 0);
	NS_ASSERT(ptr_net_device->GetInstanceTypeId().IsChildOf(ns3::NetDevice::GetTypeId()));
	const auto i_interface = ptr_ipv4->GetInterfaceForDevice(ptr_net_device);
	NS_ASSERT_MSG(i_interface != -1, "maybe IPv4 address is not assigned yet.");
	const auto n_addresses = ptr_ipv4->GetNAddresses(i_interface);
	for (unsigned i_address = 0; i_address < n_addresses; ++i_address) {
		NS_LOG_DEBUG(ptr_ipv4->GetAddress(i_interface, i_address));
	}//for
	NS_ASSERT_MSG(n_addresses == 1, n_addresses);
	ns3::Ipv4InterfaceAddress ipv4_interface_address = ptr_ipv4->GetAddress(
			i_interface, 0);
	return ipv4_interface_address;
}//getIpv4InterfaceAddress

#endif /* CSMAINTERNETNODE_H_ */
