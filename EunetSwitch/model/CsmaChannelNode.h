#ifndef CSMACHANNELNODE_H_
#define CSMACHANNELNODE_H_
#include "ns3/node.h"
#include "ns3/csma-channel.h"
#include "CsmaNode.h"

class CsmaChannelNode: public CsmaNode {
	ns3::ObjectFactory csmaChannelFactory;
	ns3::DataRate csmaChannelDataRate;
	ns3::Time csmaChannelDelay;
public:
	static ns3::TypeId GetTypeId(void);
	CsmaChannelNode();
	virtual ~CsmaChannelNode() {
	}
	;
	void bring(ns3::Ptr<CsmaNode> ptr_their_csma_node,
			const unsigned i_their_csma_device = 0);
	void bring(const unsigned i_our_csma_device,
			ns3::Ptr<CsmaNode> ptr_their_csma_node,
			const unsigned i_their_csma_device = 0);
	ns3::Ptr<ns3::CsmaChannel> getCsmaChannel(unsigned i_channel);
	void setCsmaChannelDataRate(const ns3::DataRateValue&,
			const unsigned i_channel = 0);
	void setCsmaChannelDataRateAll(const ns3::DataRateValue&);
	void setCsmaChannelDelay(const ns3::TimeValue&, const unsigned i_channel =
			0);
	void setCsmaChannelDelayAll(const ns3::TimeValue&);
DECLARE_DIDDNCC
};

#endif /* CSMACHANNELNODE_H_ */
