#ifndef CSMANODE_H_
#define CSMANODE_H_
#include "ns3/node.h"
#include "ns3/net-device-container.h"
#include "ns3/object-factory.h"
#include "ns3/csma-net-device.h"
#include "ns3/uinteger.h"
#include "ns3/application.h"
#include "ns3/csma-helper.h"
#include "ns3/queue.h"
#include "ns3/drop-tail-queue.h"
#include "init.h"
#include "CsmaDevice.h"

class CsmaNode: public ns3::Node {
protected:
	uint32_t nPorts;
public:
	static ns3::TypeId GetTypeId(void);
	CsmaNode();
	virtual ~CsmaNode();
	//ns3::Ptr<ns3::CsmaNetDevice> getCsmaNetDevice(const unsigned i_device = 0);
	template<class T>
	ns3::Ptr<T> getNetDevice(const unsigned i_port = 0);
	template<class T>
	unsigned getNDevices();
	void logAllDevices(const ns3::LogLevel log_level = ns3::LOG_LEVEL_INFO);
	template<class T>
	ns3::Ptr<T> getApplication();

	void enablePcap(ns3::Ptr<ns3::NetDevice>, const bool promiscuous = false);

	template<class T>
	void enableAsciiTrace(const unsigned i_port);
	template<class T>
	ns3::NetDeviceContainer getNetDevices();
	void enableAsciiTrace(ns3::Ptr<CsmaDevice> ptr_csma_net_device);
protected:
	template<class T>
	ns3::Ptr<T> addCsmaNetDevice();
private:
	uint32_t countCsmaNetDevices();
DECLARE_DIDDNCC
};

template<class T>
ns3::Ptr<T> CsmaNode::getNetDevice(const unsigned i_port) {
	//NS_ASSERT(this->countCsmaNetDevices()==1);
	unsigned j = 0;
	bool has_device_T = false;
	for (unsigned i = 0; i < this->GetNDevices(); ++i) {
		//NS_LOG(log_level, this->GetDevice(i)->GetTypeId() << ", " << this->GetDevice(i)->GetInstanceTypeId());
		if (this->GetDevice(i)->GetInstanceTypeId() == T::GetTypeId()) {
			has_device_T = true;
			if (j == i_port) {
				return this->GetDevice(i)->GetObject<T> (T::GetTypeId());

			}//if
			++j;
		}//if
	}//for
	if (has_device_T) {
		NS_FATAL_ERROR("only " << this->getNDevices<T>() << " " << T::GetTypeId() << " exists." );
	}
	NS_FATAL_ERROR("node " << this->GetId() << " has no " << T::GetTypeId() << "." );
}

template<class T>
unsigned CsmaNode::getNDevices() {
	unsigned count = 0;
	for (unsigned i = 0; i < this->GetNDevices(); ++i) {
		if (this->GetDevice(i)->GetInstanceTypeId() == T::GetTypeId()) {
			++count;
		}//if
	}//for
	return count;
}//getNDevices

template<class T>
ns3::Ptr<T> CsmaNode::getApplication() {
	for (unsigned i = 0; this->GetNApplications(); ++i) {
		auto ptr_application = this->GetApplication(i);
		if (ptr_application->GetInstanceTypeId() == T::GetTypeId()) {
			return ptr_application->GetObject<T> ();
		}//if
	}//for
	return NULL;
}//getApplication

template<class T>
void CsmaNode::enableAsciiTrace(const unsigned i_port) {
	ns3::CsmaHelper csma_helper;
	csma_helper.EnableAscii(this->GetInstanceTypeId().GetName(),
			this->getNetDevice<T> (i_port));
}//enableAsciiTrace

template<class T>
ns3::NetDeviceContainer CsmaNode::getNetDevices() {
	ns3::NetDeviceContainer ndc;
	for (unsigned i = 0; i < this->GetNDevices(); ++i) {
		if (this->GetDevice(i)->GetInstanceTypeId() == T::GetTypeId()) {
			ndc.Add(this->GetDevice(i));
		}//if
	}//for
	return ndc;
}//getNDevices

template<class T>
ns3::Ptr<T> CsmaNode::addCsmaNetDevice() {
	//this->deviceFactory.SetTypeId(T::GetTypeId());
	//auto ptr_t = this->deviceFactory.Create<T> ();
	auto ptr_t = ns3::CreateObject<T>();
	ns3::Ptr<ns3::CsmaNetDevice> ptr_csma_net_device(ptr_t);
	ptr_csma_net_device->SetAddress(ns3::Mac48Address::Allocate());
	this->AddDevice(ptr_csma_net_device);
	//ns3::Ptr<ns3::Queue> ptr_queue = this->queueFactory.Create<ns3::Queue> ();
	ns3::Ptr<ns3::Queue> ptr_queue = ns3::CreateObject<ns3::DropTailQueue>();
	ptr_csma_net_device->SetQueue(ptr_queue);
	return ptr_t;
}

#endif /* CSMANODE_H_ */
