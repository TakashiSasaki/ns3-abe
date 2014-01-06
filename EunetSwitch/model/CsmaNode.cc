#define NS3_LOG_ENABLE 1
#include "ns3/log.h"
NS_LOG_COMPONENT_DEFINE("CsmaNode");
#define NS3_ASSERT_ENABLE 1
#include "ns3/assert.h"
#include "ns3/queue.h"
#include "ns3/ipv4-interface.h"
#include "ns3/ipv4-l3-protocol.h"
#include "CsmaNode.h"
NS_OBJECT_ENSURE_REGISTERED(CsmaNode);

ns3::TypeId CsmaNode::GetTypeId(void) {
	static ns3::TypeId type_id =
			ns3::TypeId("CsmaNode").SetParent<ns3::Node> ().AddConstructor<
					CsmaNode> ();
	return type_id;
}//GetTypeId

CsmaNode::CsmaNode(const uint32_t n_csma_net_devices) :
	nCsmaNetDevices(n_csma_net_devices) {
	NS_LOG_INFO("constructing CsmaNode with " << n_csma_net_devices << " devices");
	this->deviceFactory.SetTypeId("ns3::CsmaNetDevice");
	this->queueFactory.SetTypeId("ns3::DropTailQueue");
	NS_ASSERT(this->GetNDevices()==0);
	for (uint32_t i = 0; i < this->nCsmaNetDevices; ++i) {
		ns3::Ptr<ns3::CsmaNetDevice> ptr_csma_net_device =
				this->deviceFactory.Create<ns3::CsmaNetDevice> ();
		ptr_csma_net_device->SetAddress(ns3::Mac48Address::Allocate());
		this->AddDevice(ptr_csma_net_device);
		ns3::Ptr<ns3::Queue> ptr_queue =
				this->queueFactory.Create<ns3::Queue> ();
		ptr_csma_net_device->SetQueue(ptr_queue);
	}//for
	NS_ASSERT(this->GetNDevices()==this->nCsmaNetDevices);
	NS_LOG_INFO("constructed with " << this->GetNDevices() << " devices");
}

void CsmaNode::DoInitialize() {
	NS_LOG_INFO("just calling up");
	Base::DoInitialize();
}

void CsmaNode::NotifyConstructionCompleted() {
	NS_LOG_INFO("just calling up");
	Base::NotifyConstructionCompleted();
}

CsmaNode::~CsmaNode() {
	// TODO !CodeTemplates.destructorstub.tododesc!
}

void CsmaNode::logAllDevices(const ns3::LogLevel log_level) {
	//TODO: separate this method to other mixin class
	NS_LOG_INFO("listing all devices installed in a node");
	for (unsigned i = 0; i < this->GetNDevices(); ++i) {
		auto ptr_net_device = this->GetDevice(i);
		auto ptr_ipv4 = this->GetObject<ns3::Ipv4L3Protocol> ();
		if (ptr_ipv4 == 0) {
			NS_LOG_INFO("this node has no IPv4 stack");
		} else {
			const int i_interface = ptr_ipv4->GetInterfaceForDevice(
					ptr_net_device);
			if (i_interface == -1) {
				NS_LOG_INFO(ptr_net_device->GetInstanceTypeId() << "\tno Ipv4InterfaceAddress");
			} else {
				auto ipv4_interface = ptr_ipv4->GetInterface(i_interface);
				const int n_addresses = ipv4_interface->GetNAddresses();
				for (int j = 0; j < n_addresses; ++j) {
					auto ipv4_interface_address = ipv4_interface->GetAddress(j);
					NS_LOG_INFO(ptr_net_device->GetInstanceTypeId() << "\t" << ipv4_interface_address.GetLocal());
				}//for
			}//if
		}//if
	}
}//logAllDevices

ns3::Ptr<ns3::CsmaNetDevice> CsmaNode::getCsmaNetDevice(const unsigned i_device) {
	//NS_ASSERT(this->countCsmaNetDevices()==1);
	unsigned j = 0;
	for (unsigned i = 0; i < this->GetNDevices(); ++i) {
		//NS_LOG(log_level, this->GetDevice(i)->GetTypeId() << ", " << this->GetDevice(i)->GetInstanceTypeId());
		if (this->GetDevice(i)->GetInstanceTypeId()
				== ns3::CsmaNetDevice::GetTypeId()) {
			if (j == i_device) {
				return this->GetDevice(i)->GetObject<ns3::CsmaNetDevice> (
						ns3::CsmaNetDevice::GetTypeId());

			}//if
			++j;
		}//if
	}//for
	NS_FATAL_ERROR("no CsmaNetDevice");
}//getCsmaNetDevice

uint32_t CsmaNode::countCsmaNetDevices() {
	uint32_t n_csma_net_devices = 0;
	for (unsigned i = 0; i < this->GetNDevices(); ++i) {
		//NS_LOG(log_level, this->GetDevice(i)->GetTypeId() << ", " << this->GetDevice(i)->GetInstanceTypeId());
		if (this->GetDevice(i)->GetInstanceTypeId()
				== ns3::CsmaNetDevice::GetTypeId()) {
			++n_csma_net_devices;
		}//if
	}//for
	return n_csma_net_devices;
}
