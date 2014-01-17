#define NS3_LOG_ENABLE 1
#include "ns3/log.h"
NS_LOG_COMPONENT_DEFINE("CsmaNode");
#define NS3_ASSERT_ENABLE 1
#include "ns3/assert.h"
#include "ns3/queue.h"
#include "ns3/ipv4-interface.h"
#include "ns3/ipv4-l3-protocol.h"
#include "ns3/uinteger.h"
#include "ns3/loopback-net-device.h"
#include "CsmaNode.h"
NS_OBJECT_ENSURE_REGISTERED(CsmaNode);

ns3::TypeId CsmaNode::GetTypeId(void) {
	static ns3::TypeId type_id =
			ns3::TypeId("CsmaNode").SetParent<ns3::Node> ().AddConstructor<
					CsmaNode> (). AddAttribute("nPorts",
					"the number of CSMA port", ns3::UintegerValue(1),
					ns3::MakeUintegerAccessor(&CsmaNode::getNPorts,
							&CsmaNode::setNPorts), ns3::MakeUintegerChecker<
							uint32_t>());
	return type_id;
}//GetTypeId

CsmaNode::CsmaNode() :
	nCsmaNetDevices(0), INIT_DIDDNCC_FLAGS {
	this->deviceFactory.SetTypeId("ns3::CsmaNetDevice");
	this->queueFactory.SetTypeId("ns3::DropTailQueue");
}
void CsmaNode::NotifyConstructionCompleted() {
	ASSERT_NCC;
	NS_LOG_INFO("GetNDevices=" << this->GetNDevices());
	NS_ASSERT(this->GetNDevices()==0);
	ns3::Node::NotifyConstructionCompleted();
	NS_ASSERT(this->GetNDevices()==0);
	NS_LOG_INFO("GetNDevices=" << this->GetNDevices());
}
void CsmaNode::DoInitialize() {
	NS_LOG_INFO("CsmaNode::DoInitialize");
	ASSERT_DI;
	NS_LOG_INFO("1 GetNDevices=" << this->GetNDevices());
	NS_ASSERT_MSG (this->getNDevices<ns3::LoopbackNetDevice>()==0, this->getNDevices<ns3::LoopbackNetDevice>());
	NS_LOG_INFO("2 GetNDevices=" << this->GetNDevices());
	ns3::Node::DoInitialize();
	NS_LOG_INFO("3 GetNDevices=" << this->GetNDevices());
	NS_LOG_INFO("constructing CsmaNode with " << this->nCsmaNetDevices << " devices");
	NS_ASSERT_MSG(this->GetNDevices()==0, "devices=" << this->GetNDevices() << " csma="
			<< this->getNDevices<ns3::CsmaNetDevice>() << " loopback=" <<this->getNDevices<ns3::LoopbackNetDevice>() );
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
void CsmaNode::DoDispose() {
	NS_LOG_INFO("disposing CsmaNode " << this->GetId());
	ASSERT_DD;
	ns3::Node::DoDispose();
}
void CsmaNode::setNPorts(uint32_t n_ports) {
	NS_LOG_INFO("n_ports = " << n_ports);
	NS_ASSERT(!this->isDoInitializeCalled);
	this->nCsmaNetDevices = n_ports;
}

uint32_t CsmaNode::getNPorts(void) const {
	return this->nCsmaNetDevices;
}

// the constructor

//DoInitialize

//DoDispose

//NotifyConstructionCompleted

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

#if 0
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
#endif

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
template
void CsmaNode::enablePcap<ns3::CsmaNetDevice>(const int i_port,
		const bool promiscous);

template
void CsmaNode::enableAsciiTrace<ns3::CsmaNetDevice>(const unsigned i_port);
