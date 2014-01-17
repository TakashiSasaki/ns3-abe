#ifndef CSMACHANNELNODE_H_
#define CSMACHANNELNODE_H_
#include "ns3/node.h"
#include "ns3/csma-channel.h"
#include "CsmaNode.h"

class CsmaChannelNode: public CsmaNode {
	ns3::ObjectFactory csmaChannelFactory;
	ns3::DataRate csmaChannelDataRate;
	ns3::Time csmaChannelDelay;
	void setCsmaChannelDataRate(const ns3::DataRateValue&,
			const unsigned i_channel = 0);
	void setCsmaChannelDataRateAll(const ns3::DataRateValue&);
	void setCsmaChannelDelay(const ns3::TimeValue&, const unsigned i_channel =
			0);
	void setCsmaChannelDelayAll(const ns3::TimeValue&);
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
protected:
	template<class T>
	void addCsmaChannel(const unsigned i_port, const ns3::DataRate& data_rate,
			const ns3::Time& delay);
DECLARE_DIDDNCC
};

template<class T>
void CsmaChannelNode::addCsmaChannel(const unsigned i_port,
		const ns3::DataRate& data_rate, const ns3::Time& delay) {
	ns3::Ptr<ns3::CsmaNetDevice> ptr_csma_net_device = this->getNetDevice<T> (
			i_port);
	ns3::Ptr<ns3::CsmaChannel> ptr_csma_channel =
			this->csmaChannelFactory.Create()->GetObject<ns3::CsmaChannel> ();
	//NS_LOG_INFO("attaching a channel to device #" << i);
	//this->getNetDevice<ns3::CsmaNetDevice> (i)->Attach(ptr_csma_channel);
	ptr_csma_net_device->Attach(ptr_csma_channel);
}//addCsmaChannel

#endif /* CSMACHANNELNODE_H_ */
