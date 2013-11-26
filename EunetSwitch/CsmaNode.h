#ifndef CSMANODE_H_
#define CSMANODE_H_
#include "ns3/node.h"
#include "ns3/net-device-container.h"
#include "ns3/object-factory.h"
#include "ns3/csma-net-device.h"

class CsmaNode: public ns3::Node {
	typedef Node Base;
	const uint32_t nCsmaNetDevices;
	ns3::ObjectFactory deviceFactory;
	ns3::ObjectFactory queueFactory;
public:
	static ns3::TypeId GetTypeId(void);
	CsmaNode(const uint32_t n_csma_net_devices = 0);
	virtual ~CsmaNode();
	ns3::Ptr<ns3::CsmaNetDevice> getCsmaNetDevice(const unsigned i = 0);
	void logAllDevices(const ns3::LogLevel log_level = ns3::LOG_LEVEL_INFO);
protected:
	virtual void NotifyConstructionCompleted();
	virtual void DoInitialize();
private:
	uint32_t countCsmaNetDevices();
};

#endif /* CSMANODE_H_ */
