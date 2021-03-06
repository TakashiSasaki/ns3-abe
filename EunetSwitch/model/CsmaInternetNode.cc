#define NS3_LOG_ENABLE 1
#include "ns3/log.h"
NS_LOG_COMPONENT_DEFINE("CsmaInternetNode");
#define NS3_ASSERT_ENABLE 1
#include "ns3/assert.h"
#include "ns3/applications-module.h"
#include "ns3/ipv4.h"
#include "ns3/internet-module.h"
#include "CsmaNode.h"
#include "CsmaChannelNode.h"
#include "CsmaInternetNode.h"
#include "CsmaDevice.h"

NS_OBJECT_ENSURE_REGISTERED(CsmaInternetNode);

const ns3::Ipv4InterfaceAddress CsmaInternetNode::dummyAddress(
		ns3::Ipv4Address("0.0.0.0"), ns3::Ipv4Mask("255.255.255.255"));

ns3::TypeId CsmaInternetNode::GetTypeId(void) {
	static ns3::TypeId
			type_id =
					ns3::TypeId("CsmaInternetNode").SetParent<CsmaChannelNode> ().AddConstructor<
							CsmaInternetNode> ().AddAttribute(
							"willAssignDummyAddress", "willAssignDummyAddress",
							ns3::BooleanValue(false), ns3::MakeBooleanAccessor(
									&CsmaInternetNode::willAssignDummyAddress),
							ns3::MakeBooleanChecker());
	return type_id;
}//GetTypeId

CsmaInternetNode::CsmaInternetNode(const int n_devices) :
	CsmaChannelNode(), INIT_DIDDNCC_FLAGS {
}// a constructor

void CsmaInternetNode::DoDispose() {
	ASSERT_DD;
	CsmaChannelNode::DoDispose();
}// DoDispose

void CsmaInternetNode::NotifyConstructionCompleted() {
	ASSERT_NCC;
	NS_ASSERT(this->GetNDevices()==0);
	CsmaChannelNode::NotifyConstructionCompleted();
	NS_ASSERT_MSG(this->getNDevices<CsmaDevice>() == this->nPorts, this->getNDevices<CsmaDevice>() << ", " << this->nPorts);
	const unsigned n_devices_before = this->GetNDevices();

	ns3::InternetStackHelper internet_stack_helper;
	internet_stack_helper.SetIpv4StackInstall(true);
	internet_stack_helper.SetIpv6StackInstall(true);
	NS_ASSERT(this->GetNDevices() == n_devices_before);
	this->logAllDevices();
	internet_stack_helper.Install(ns3::NodeContainer(this));
	NS_LOG_INFO("InternetStackHelper::Install finished");
	this->logAllDevices();
	NS_ASSERT(this->GetNDevices() == n_devices_before+1);
	NS_ASSERT(this->GetDevice(n_devices_before)->GetObject<ns3::LoopbackNetDevice>(ns3::LoopbackNetDevice::GetTypeId()));

	for (unsigned i = 0; i < this->getNDevices<CsmaDevice> (); ++i) {
		auto ptr_csma_net_device = getNetDevice<CsmaDevice> (i);
		auto ptr_ipv4 = this->GetObject<ns3::Ipv4> ();
		int32_t i_interface = ptr_ipv4->GetInterfaceForDevice(
				ptr_csma_net_device);
		NS_ASSERT(i_interface==-1);
		i_interface = ptr_ipv4->AddInterface(ptr_csma_net_device);
		NS_ASSERT(i_interface>=0);

		if (this->willAssignDummyAddress) {
			this->assignDummyAddress(ptr_csma_net_device);
		}//if
	}//for
}//NotifyConstructionCompleted

void CsmaInternetNode::assignDummyAddress(
		ns3::Ptr<ns3::NetDevice> ptr_csma_net_device) {
	auto ptr_ipv4 = this->GetObject<ns3::Ipv4> ();
	int32_t i_interface = ptr_ipv4->GetInterfaceForDevice(ptr_csma_net_device);
	NS_ASSERT(i_interface>=0);
	if (i_interface == -1) {
		i_interface = ptr_ipv4->AddInterface(ptr_csma_net_device);
	}//if
	ptr_ipv4->AddAddress(i_interface, dummyAddress);
	ptr_ipv4->SetMetric(i_interface, 255);
	ptr_ipv4->SetUp(i_interface);
}

void CsmaInternetNode::removeAllAddresses(
		ns3::Ptr<ns3::NetDevice> ptr_csma_net_device) {
	//auto ptr_csma_net_device = this->getNetDevice<ns3::CsmaNetDevice> (
	//		i_csma_port);
	auto ptr_ipv4 = this->GetObject<ns3::Ipv4> ();
	int32_t i_interface = ptr_ipv4->GetInterfaceForDevice(ptr_csma_net_device);
	if (i_interface == -1)
		return;
	for (unsigned i_address = 0; i_address < ptr_ipv4->GetNAddresses(
			i_interface); ++i_address) {
		auto iia = ptr_ipv4->GetAddress(i_interface, i_address);
		ptr_ipv4->RemoveAddress(i_interface, iia.GetLocal());
	}//for
	NS_ASSERT(ptr_ipv4->GetNAddresses(i_interface) == 0);
}

void CsmaInternetNode::DoInitialize() {
	ASSERT_DI;
	NS_ASSERT_MSG(this->getNDevices<CsmaDevice>()==this->nPorts, this->getNDevices<CsmaDevice>() << "," << this->nPorts);
	NS_ASSERT_MSG(this->getNDevices<ns3::LoopbackNetDevice>()==1, this->getNDevices<ns3::LoopbackNetDevice>());
	CsmaChannelNode::DoInitialize();
#if 0
	const unsigned n_devices_before = this->GetNDevices();
	//NS_ASSERT(this->GetNDevices() == 1);
	ns3::InternetStackHelper internet_stack_helper;
	internet_stack_helper.SetIpv4StackInstall(true);
	internet_stack_helper.SetIpv6StackInstall(true);
	NS_ASSERT(this->GetNDevices() == n_devices_before);
	this->logAllDevices();
	internet_stack_helper.Install(ns3::NodeContainer(this));
	NS_LOG_INFO("InternetStackHelper::Install finished");
	this->logAllDevices();
	NS_ASSERT(this->GetNDevices() == n_devices_before+1);
	NS_ASSERT(this->GetDevice(n_devices_before)->GetObject<ns3::LoopbackNetDevice>(ns3::LoopbackNetDevice::GetTypeId()));
#endif
}//DoInitialize

#if 0
ns3::Ipv4Address CsmaInternetNode::getCsmaNetDeviceAddress() {
	this->logAllDevices(ns3::LOG_LEVEL_INFO);
	const unsigned n_devices_before = this->GetNDevices();
	NS_ASSERT(this->GetNDevices()>=2);
	ns3::Ptr<ns3::Ipv4> ptr_ipv4 = this->GetObject<ns3::Ipv4> ();
	ns3::Ptr<ns3::CsmaNetDevice> ptr_csma_net_device = this->getCsmaNetDevice();
	NS_ASSERT(ptr_csma_net_device != 0);
	const int n_interface =
	ptr_ipv4->GetInterfaceForDevice(ptr_csma_net_device);
	NS_ASSERT(n_interface != -1);
	ns3::Ipv4InterfaceAddress ipv4_interface_address = ptr_ipv4->GetAddress(
			n_interface, 0);
	ns3::Ipv4Address ipv4_address = ipv4_interface_address.GetLocal();
	NS_ASSERT(this->GetNDevices()==n_devices_before);
	return ipv4_address;
}//getCsmaNetDeviceAddress
#endif

#if 0
void CsmaInternetNode::assignAddress(
		ns3::Ipv4AddressHelper& ipv4_address_helper) {
	this->assignAddress(0, ipv4_address_helper);
}//assignAddress

void CsmaInternetNode::assignAddress(const unsigned i_port,
		ns3::Ipv4AddressHelper& ipv4_address_helper) {
	NS_ASSERT(this->GetNDevices()==2);
	ipv4_address_helper.Assign(ns3::NetDeviceContainer(this->getNetDevice<
					ns3::CsmaNetDevice> (i_port)));
	//this->setRemote(this);
	NS_LOG_INFO(this->getAddress<ns3::CsmaNetDevice>(i_port) << " node " << this->GetId());
}//assignAddress
#endif

void CsmaInternetNode::assignAddress(
		ns3::Ptr<ns3::NetDevice> ptr_csma_net_device,
		ns3::Ipv4Address ipv4_address, ns3::Ipv4Mask ipv4_mask) {
	NS_ASSERT(ptr_csma_net_device != NULL);
	NS_ASSERT(this->GetId()==ptr_csma_net_device->GetNode()->GetId());
	ns3::Ptr<CsmaInternetNode> ptr_this(this, true);
	auto ptr_ipv4 = ptr_this->GetObject<ns3::Ipv4> ();
	NS_ASSERT(ptr_ipv4 != NULL);
	removeAllAddresses(ptr_csma_net_device);
	int32_t i_interface = ptr_ipv4->GetInterfaceForDevice(ptr_csma_net_device);
	if (i_interface == -1) {
		i_interface = ptr_ipv4->AddInterface(ptr_csma_net_device);
	}//if
	NS_ASSERT(i_interface >= 0);
	NS_ASSERT_MSG(ptr_ipv4->GetNAddresses(i_interface) == 0,ptr_ipv4->GetNAddresses(i_interface));
	const auto mask = ipv4_mask.Get();
	ns3::Ipv4InterfaceAddress ipv4_interface_address(ipv4_address, mask);
	ptr_ipv4->AddAddress(i_interface, ipv4_interface_address);
	ptr_ipv4->SetMetric(i_interface, 1);
	ptr_ipv4->SetUp(i_interface);
}//assignAddress

void CsmaInternetNode::logAddress(const ns3::Ipv4Address& ipv4_address) {
	NS_LOG_INFO(ipv4_address << " to node " << this->GetId());
}

#if 0
ns3::Ipv4InterfaceAddress CsmaInternetNode::getIpv4InterfaceAddress(
		const unsigned i_net_device) {
	NS_ASSERT(this->GetNDevices()>=2);
	ns3::Ptr<ns3::Ipv4> ptr_ipv4 = this->GetObject<ns3::Ipv4> ();
	auto ptr_net_device = this->getNetDevice<ns3::NetDevice> (i_net_device);
	NS_ASSERT(ptr_net_device != 0);
	NS_ASSERT(ptr_net_device->GetInstanceTypeId().IsChildOf(ns3::NetDevice::GetTypeId()));
	const auto i_interface = ptr_ipv4->GetInterfaceForDevice(ptr_net_device);
	NS_ASSERT(i_interface != -1);
	const auto n_addresses = ptr_ipv4->GetNAddresses(i_interface);
	NS_ASSERT(n_addresses == 1);
	ns3::Ipv4InterfaceAddress ipv4_interface_address = ptr_ipv4->GetAddress(
			i_interface, 0);
	return ipv4_interface_address;
}//getIpv4InterfaceAddress
#endif

template ns3::Ipv4InterfaceAddress CsmaInternetNode::getIpv4InterfaceAddress<
		ns3::CsmaNetDevice>(const unsigned i_port);

void CsmaInternetNode::assignAddress(
		ns3::Ptr<ns3::NetDevice> ptr_csma_net_device,
		ns3::Ipv4AddressHelper& ipv4_address_helper) {
	NS_ASSERT(ptr_csma_net_device != NULL);
	removeAllAddresses(ptr_csma_net_device);
	{
		auto ptr_ipv4 = this->GetObject<ns3::Ipv4> ();
		auto i_interface = ptr_ipv4->GetInterfaceForDevice(ptr_csma_net_device);
		NS_ASSERT_MSG(i_interface >=0, i_interface);
		NS_ASSERT_MSG(ptr_ipv4->GetNAddresses(i_interface) == 0,ptr_ipv4->GetNAddresses(i_interface));
	}
	ipv4_address_helper.Assign(ns3::NetDeviceContainer(ptr_csma_net_device));
	//this->setRemote(this);
	//this->logAddress(this->getAddress<T> ());
}

ns3::Ipv4Address CsmaInternetNode::getAddress(
		ns3::Ptr<ns3::NetDevice> ptr_csma_net_device) {
	NS_ASSERT(ptr_csma_net_device->GetNode()->GetId()==this->GetId());
	ns3::Ptr<ns3::Ipv4> ptr_ipv4 = this->GetObject<ns3::Ipv4> ();
	NS_ASSERT(ptr_csma_net_device->GetInstanceTypeId().IsChildOf(ns3::NetDevice::GetTypeId()));
	const auto i_interface = ptr_ipv4->GetInterfaceForDevice(
			ptr_csma_net_device);
	NS_ASSERT_MSG(i_interface != -1, i_interface);
	const auto n_addresses = ptr_ipv4->GetNAddresses(i_interface);
	for (unsigned i_address = 0; i_address < n_addresses; ++i_address) {
		NS_LOG_DEBUG(ptr_ipv4->GetAddress(i_interface, i_address));
	}//for
	NS_ASSERT_MSG(n_addresses == 1, n_addresses);
	ns3::Ipv4InterfaceAddress ipv4_interface_address = ptr_ipv4->GetAddress(
			i_interface, 0);
	ns3::Ipv4Address ipv4_address = ipv4_interface_address.GetLocal();
	return ipv4_address;
}

ns3::Ptr<ns3::CsmaNetDevice> CsmaInternetNode::getDevice(
		ns3::Ipv4Address ipv4_address) {
	auto ipv4 = this->GetObject<ns3::Ipv4> ();
	int32_t i_interface = ipv4->GetInterfaceForAddress(ipv4_address);
	auto device = ipv4->GetNetDevice(i_interface);
	return device->GetObject<ns3::CsmaNetDevice> ();
}
