#ifndef CSMANODE_H_
#define CSMANODE_H_
#include "ns3/node.h"
#include "ns3/net-device-container.h"
#include "ns3/object-factory.h"
#include "ns3/csma-net-device.h"
#include "ns3/uinteger.h"
#include "ns3/application.h"
#include "ns3/csma-helper.h"
#include "init.h"

class CsmaNode: public ns3::Node {
	//typedef Node Base;
	uint32_t nCsmaNetDevices;
	ns3::ObjectFactory deviceFactory;
	ns3::ObjectFactory queueFactory;
public:
	static ns3::TypeId GetTypeId(void);
	CsmaNode();
	virtual ~CsmaNode() {
	}
	;
	//ns3::Ptr<ns3::CsmaNetDevice> getCsmaNetDevice(const unsigned i_device = 0);
	template<class T>
	ns3::Ptr<T> getNetDevice(const unsigned i_device = 0);
	template<class T>
	unsigned getNDevices();
	void logAllDevices(const ns3::LogLevel log_level = ns3::LOG_LEVEL_INFO);
	void setNPorts(uint32_t);
	uint32_t getNPorts() const;
	template<class T>
	ns3::Ptr<T> getApplication();
	template<class T>
	void enablePcap(const int i_port, const bool promiscuous = false);
private:
	uint32_t countCsmaNetDevices();
DECLARE_DIDDNCC
};

template<class T>
ns3::Ptr<T> CsmaNode::getNetDevice(const unsigned i_device) {
	//NS_ASSERT(this->countCsmaNetDevices()==1);
	unsigned j = 0;
	bool has_device_T = false;
	for (unsigned i = 0; i < this->GetNDevices(); ++i) {
		//NS_LOG(log_level, this->GetDevice(i)->GetTypeId() << ", " << this->GetDevice(i)->GetInstanceTypeId());
		if (this->GetDevice(i)->GetInstanceTypeId() == T::GetTypeId()) {
			has_device_T = true;
			if (j == i_device) {
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
void CsmaNode::enablePcap(const int i_port, const bool promiscuous) {
	ns3::CsmaHelper csma_helper;
	std::ostringstream oss;
	oss << T::GetTypeId() << "-" << this->GetId() << "-" << i_port;
	csma_helper.EnablePcap(oss.str(), this->getNetDevice<T> (i_port),
			promiscuous);
}//enablePcap

#endif /* CSMANODE_H_ */
