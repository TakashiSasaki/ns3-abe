#ifndef CSMAINTERNETNODE_H_
#define CSMAINTERNETNODE_H_
#include "CsmaChannelNode.h"

class CsmaInternetNode: public CsmaChannelNode {
public:
	static ns3::TypeId GetTypeId(void);
	CsmaInternetNode(const int n_devices = 1);
	virtual ~CsmaInternetNode();
	ns3::Ipv4Address getCsmaNetDeviceAddress();
	void assignAddress(ns3::Ipv4AddressHelper&);
protected:
	virtual void NotifyConstructionCompleted();
};

#endif /* CSMAINTERNETNODE_H_ */
