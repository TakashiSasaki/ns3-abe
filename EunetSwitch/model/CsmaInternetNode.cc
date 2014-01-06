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

ns3::TypeId CsmaInternetNode::GetTypeId(void) {
	static ns3::TypeId type_id =
			ns3::TypeId("CsmaInternetNode").SetParent<Base> ().AddConstructor<
					CsmaInternetNode> ();
	return type_id;
}//GetTypeId

CsmaInternetNode::CsmaInternetNode(const int n_devices) :
	CsmaChannelNode(n_devices) {
}

CsmaInternetNode::~CsmaInternetNode() {
	// TODO !CodeTemplates.destructorstub.tododesc!
}

void CsmaInternetNode::NotifyConstructionCompleted() {
	Base::NotifyConstructionCompleted();
	NS_ASSERT(this->GetNDevices() == 1);
	ns3::InternetStackHelper internet_stack_helper;
	internet_stack_helper.SetIpv4StackInstall(true);
	internet_stack_helper.SetIpv6StackInstall(false);
	NS_ASSERT(this->GetNDevices() == 1);
	this->logAllDevices();
	internet_stack_helper.Install(ns3::NodeContainer(this));
	NS_LOG_INFO("InternetStackHelper::Install finished");
	this->logAllDevices();
	NS_ASSERT(this->GetNDevices() == 2);
	NS_ASSERT(this->GetDevice(1)->GetObject<ns3::LoopbackNetDevice>(ns3::LoopbackNetDevice::GetTypeId()));
}

ns3::Ipv4Address CsmaInternetNode::getCsmaNetDeviceAddress() {
	NS_ASSERT(this->GetNDevices()==2);
	ns3::Ptr<ns3::Ipv4> ptr_ipv4 = this->GetObject<ns3::Ipv4> ();
	ns3::Ptr<ns3::CsmaNetDevice> ptr_csma_net_device = this->getCsmaNetDevice();
	const int i_interface =
			ptr_ipv4->GetInterfaceForDevice(ptr_csma_net_device);
	ns3::Ipv4InterfaceAddress ipv4_interface_address = ptr_ipv4->GetAddress(
			i_interface, 0);
	ns3::Ipv4Address ipv4_address = ipv4_interface_address.GetLocal();
	return ipv4_address;
}//getCsmaNetDeviceAddress

void CsmaInternetNode::assignAddress(
		ns3::Ipv4AddressHelper& ipv4_address_helper) {
	NS_ASSERT(this->GetNDevices()==2);
	ipv4_address_helper.Assign(
			ns3::NetDeviceContainer(this->getCsmaNetDevice()));
	//this->setRemote(this);
	NS_LOG_INFO(this->getCsmaNetDeviceAddress() << " node " << this->GetId());
}