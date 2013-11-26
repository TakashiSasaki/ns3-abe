#define NS3_LOG_ENABLE 1
#include "ns3/log.h"
NS_LOG_COMPONENT_DEFINE("CsmaNode");
#define NS3_ASSERT_ENABLE 1
#include "ns3/assert.h"
#include "ns3/queue.h"
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
}

void CsmaNode::DoInitialize() {
	ns3::Node::DoInitialize();
}

CsmaNode::~CsmaNode() {
	// TODO !CodeTemplates.destructorstub.tododesc!
}

void CsmaNode::logAllDevices(const ns3::LogLevel log_level) {
	for (unsigned i = 0; i < this->GetNDevices(); ++i) {
		NS_LOG(log_level, this->GetDevice(i)->GetTypeId() << ", " << this->GetDevice(i)->GetInstanceTypeId());
	}
}//logAllDevices

ns3::Ptr<ns3::CsmaNetDevice> CsmaNode::getCsmaNetDevice(const unsigned i_device) {
	NS_ASSERT(this->countCsmaNetDevices()==1);
	unsigned j = 0;
	for (unsigned i = 0; i < this->GetNDevices(); ++i) {
		//NS_LOG(log_level, this->GetDevice(i)->GetTypeId() << ", " << this->GetDevice(i)->GetInstanceTypeId());
		if (this->GetDevice(i)->GetInstanceTypeId()
				== ns3::CsmaNetDevice::GetTypeId()) {
			if (j == i_device) {
				return this->GetDevice(i)->GetObject<ns3::CsmaNetDevice> (
						ns3::CsmaNetDevice::GetTypeId());

			}//if
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
