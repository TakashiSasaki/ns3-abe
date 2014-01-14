#ifndef CSMANODE_H_
#define CSMANODE_H_
#include "ns3/node.h"
#include "ns3/net-device-container.h"
#include "ns3/object-factory.h"
#include "ns3/csma-net-device.h"
#include "init.h"

class CsmaNode: public ns3::Node {
	//typedef Node Base;
	const uint32_t nCsmaNetDevices;
	ns3::ObjectFactory deviceFactory;
	ns3::ObjectFactory queueFactory;
public:
	static ns3::TypeId GetTypeId(void);
	CsmaNode(const uint32_t n_csma_net_devices = 0);
	virtual ~CsmaNode() {
	}
	;
	ns3::Ptr<ns3::CsmaNetDevice> getCsmaNetDevice(const unsigned i_device = 0);
	template<class T>
	ns3::Ptr<T> getNetDevice(const unsigned i_device = 0);
	void logAllDevices(const ns3::LogLevel log_level = ns3::LOG_LEVEL_INFO);
private:
	uint32_t countCsmaNetDevices();
DECLARE_DIDDNCC
};

template<class T>
ns3::Ptr<T> CsmaNode::getNetDevice(const unsigned i_device) {
	//NS_ASSERT(this->countCsmaNetDevices()==1);
	unsigned j = 0;
	for (unsigned i = 0; i < this->GetNDevices(); ++i) {
		//NS_LOG(log_level, this->GetDevice(i)->GetTypeId() << ", " << this->GetDevice(i)->GetInstanceTypeId());
		if (this->GetDevice(i)->GetInstanceTypeId() == T::GetTypeId()) {
			if (j == i_device) {
				return this->GetDevice(i)->GetObject<T> (T::GetTypeId());

			}//if
			++j;
		}//if
	}//for
	NS_FATAL_ERROR("no " << T::GetTypeId());
}

#endif /* CSMANODE_H_ */
