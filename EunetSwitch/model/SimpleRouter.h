#ifndef SIMPLEROUTER_H_
#define SIMPLEROUTER_H_
#include "ns3/nstime.h"
#include "ns3/core-module.h"
#include "ns3/internet-module.h"
#include "ns3/dce-application-helper.h"
#include "CsmaInternetNode.h"
#include "CsmaDevice.h"
using namespace ns3;

class SimpleRouter: public CsmaInternetNode {
	ns3::DceApplicationHelper dceApplicationHelper;
	static const ns3::DataRate defaultlinkDataRate;
	static const ns3::TimeValue defaultlinkDelay;

public:

	static ns3::TypeId GetTypeId(void);
	SimpleRouter();
	virtual ~SimpleRouter();
	//	ns3::Ptr<ns3::CsmaNetDevice>
	//getLinkPort(const unsigned i_link_port);
	void connectTo(const unsigned i_link_port,
			ns3::Ptr<SimpleRouter> connect_to_device,
			const unsigned connect_i_link_port);
	void connectTo(std::string router_name);
	unsigned getUnusedlinkPort();
	void enableOspf(ns3::Ptr<CsmaDevice>);
private:
	std::unique_ptr<std::vector<std::string> > getAllNetworks();
DECLARE_DIDDNCC
}; // class SimpleRouter

#endif /* SIMPLEROUTER_H_ */
