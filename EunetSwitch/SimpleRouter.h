#ifndef SIMPLEROUTER_H_
#define SIMPLEROUTER_H_
#include "ns3/nstime.h"
#include "ns3/core-module.h"
#include "ns3/internet-module.h"
#include "ns3/dce-module.h"
#include "ns3/quagga-helper.h"
#include "CsmaChannelNode.h"

using namespace ns3;

class SimpleRouter: public CsmaChannelNode {
	typedef CsmaChannelNode Base;
	ns3::DceApplicationHelper dceApplicationHelper;

public:
	static ns3::TypeId GetTypeId(void);
	SimpleRouter();
	virtual ~SimpleRouter();
protected:
	virtual void DoInitialize();
	virtual void NotifyConstructionCompleted();
private:
	bool isConnectedToSimpleRouter(const unsigned i_port);
	void assignIpAddressToDevice(unsigned i_net_device, ns3::Ipv4Address, ns3::Ipv4Mask);
	std::unique_ptr<std::vector<std::string> > getAllNetworks();
};

#endif /* SIMPLEROUTER_H_ */
