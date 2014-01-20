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

NS_OBJECT_ENSURE_REGISTERED(CsmaInternetNode);

const ns3::Ipv4InterfaceAddress CsmaInternetNode::dummyAddress(
		ns3::Ipv4Address("0.0.0.0"), ns3::Ipv4Mask("255.255.255.255"));

ns3::TypeId CsmaInternetNode::GetTypeId(void) {
	static ns3::TypeId type_id = ns3::TypeId("CsmaInternetNode").SetParent<
			CsmaChannelNode> ().AddConstructor<CsmaInternetNode> ();
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

	for (unsigned i = 0; i < this->getNDevices<ns3::CsmaNetDevice> (); ++i) {
		//NS_LOG_DEBUG("add ns3::IPv4 to node " << this->GetId() << " device " << i);
		this->assignDummyAddress(i);
	}//for
}//NotifyConstructionCompleted

void CsmaInternetNode::assignDummyAddress(const unsigned i_csma_port) {
	auto ptr_csma_net_device = this->getNetDevice<ns3::CsmaNetDevice> (
			i_csma_port);
	auto ptr_ipv4 = this->GetObject<ns3::Ipv4> ();
	int32_t i_interface = ptr_ipv4->GetInterfaceForDevice(ptr_csma_net_device);
	if (i_interface == -1) {
		ptr_ipv4->AddInterface(ptr_csma_net_device);
	}//if
	ptr_ipv4->AddAddress(i_interface, dummyAddress);
	ptr_ipv4->SetMetric(i_interface, 255);
	ptr_ipv4->SetUp(i_interface);
}

void CsmaInternetNode::removeAllAddresses(const unsigned i_csma_port) {
	auto ptr_csma_net_device = this->getNetDevice<ns3::CsmaNetDevice> (
			i_csma_port);
	auto ptr_ipv4 = this->GetObject<ns3::Ipv4> ();
	int32_t i_interface = ptr_ipv4->GetInterfaceForDevice(ptr_csma_net_device);
	if (i_interface == -1)
		return;
	for (unsigned i_address = 0; i_address < ptr_ipv4->GetNAddresses(i_interface); ++i_address) {
		auto iia = ptr_ipv4->GetAddress(i_interface, i_address);
		ptr_ipv4->RemoveAddress(i_interface, iia.GetLocal());
	}//for
	ptr_ipv4->AddAddress(i_interface, dummyAddress);
	ptr_ipv4->SetMetric(i_interface, 255);
	ptr_ipv4->SetUp(i_interface);
}

void CsmaInternetNode::DoInitialize() {
	ASSERT_DI;
	NS_ASSERT(this->GetNDevices()==1);
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

void CsmaInternetNode::assignAddress(const unsigned i_port,
		ns3::Ipv4Address ipv4_address, ns3::Ipv4Mask ipv4_mask) {
	ns3::Ptr<CsmaInternetNode> ptr_this(this, true);
	auto ptr_ipv4 = ptr_this->GetObject<ns3::Ipv4> ();
	const auto ptr_net_device = this->getNetDevice<ns3::CsmaNetDevice> (i_port);
	NS_ASSERT(ptr_net_device != 0);
	int32_t i_interface = ptr_ipv4->GetInterfaceForDevice(ptr_net_device);
	//NS_ASSERT_MSG(i_interface != -1, i_interface);
	if (i_interface == -1) {
		i_interface = ptr_ipv4->AddInterface(ptr_net_device);
	}//if
	const auto mask = ipv4_mask.Get();
	ns3::Ipv4InterfaceAddress ipv4_interface_address(ipv4_address, mask);
	ptr_ipv4->AddAddress(i_interface, ipv4_interface_address);
	ptr_ipv4->SetMetric(i_interface, 1);
	ptr_ipv4->SetUp(i_interface);
}//assignAddress

void CsmaInternetNode::logAddress(const ns3::Ipv4Address& ipv4_address) {
	NS_LOG_INFO(ipv4_address << " to node " << this->GetId());
}

template ns3::Ipv4Address CsmaInternetNode::getAddress<ns3::CsmaNetDevice>(
		const unsigned i_device);

template void CsmaInternetNode::assignAddress<ns3::CsmaNetDevice>(
		ns3::Ipv4AddressHelper&, const unsigned i_port);

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
