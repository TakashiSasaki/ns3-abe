#ifndef CSMACHANNELNODE_H_
#define CSMACHANNELNODE_H_
#include "ns3/node.h"
#include "CsmaNode.h"
#include "ns3/csma-channel.h"

class CsmaChannelNode: public CsmaNode {
	ns3::Ptr<ns3::CsmaChannel> ptrCsmaChannel;
	ns3::ObjectFactory csmaChannelFactory;

public:
	static ns3::TypeId GetTypeId(void);
	CsmaChannelNode(const int n_devices = 1); // TODO: should support multiple devices
	virtual ~CsmaChannelNode();
	void bring(ns3::Ptr<CsmaChannelNode>);
};

#endif /* CSMACHANNELNODE_H_ */
