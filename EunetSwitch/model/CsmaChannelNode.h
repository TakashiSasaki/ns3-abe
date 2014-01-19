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
	virtual ~CsmaChannelNode();
	void bring(ns3::Ptr<CsmaNode> ptr_their_csma_node,
			const unsigned i_their_csma_device = 0);
	template<class T, class U>
	void bring(const unsigned i_our_csma_device,
			ns3::Ptr<CsmaNode> ptr_their_csma_node,
			const unsigned i_their_csma_device = 0);
	template<class T>
	ns3::Ptr<ns3::CsmaChannel> getCsmaChannel(unsigned i_channel);
	template<class NetDeviceT>
	ns3::Ptr<NetDeviceT> getUnusedPort() const;
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

template<class T>
ns3::Ptr<ns3::CsmaChannel> CsmaChannelNode::getCsmaChannel(unsigned i_port) {
	NS_ASSERT_MSG(T::GetTypeId().IsChildOf(ns3::CsmaNetDevice::GetTypeId()) || T::GetTypeId()==ns3::CsmaNetDevice::GetTypeId(), T::GetTypeId());
	NS_ASSERT_MSG((i_port < this->getNDevices<T>()), "node " << this->GetId() << " has " << this->getNDevices<T>() << " " << ns3::CsmaNetDevice::GetTypeId() << " devices, while port " << i_port << " is specified.");
	auto ptr_csma_net_device = this->getNetDevice<T> (i_port);
	auto ptr_channel = ptr_csma_net_device->GetChannel();
	auto ptr_csma_channel = ptr_channel->GetObject<ns3::CsmaChannel> ();
	return ptr_csma_channel;
}

template<class T, class U>
void CsmaChannelNode::bring(const unsigned i_our_csma_device,
		ns3::Ptr<CsmaNode> ptr_their_node, const unsigned i_their_csma_device) {
	auto ptr_our_csma_channel = this->getCsmaChannel<T> (i_our_csma_device);
	auto their_csma_device = ptr_their_node->getNetDevice<U> (
			i_their_csma_device);
	//auto ptr_newcomer_device = ptr_newcomer->getCsmaNetDevice();
	their_csma_device->Attach(ptr_our_csma_channel);
}

template<class NetDeviceT>
ns3::Ptr<NetDeviceT> CsmaChannelNode::getUnusedPort() const {
	NS_LOG_DEBUG(NetDeviceT::GetTypeId());
	NS_ASSERT(NetDeviceT::GetTypeId().IsChildOf(ns3::NetDevice::GetTypeId()));
	for (unsigned i = 0; i < this->GetNDevices(); ++i) {
		ns3::Ptr<ns3::NetDevice> ptr_net_device = this->GetDevice(i);
		NS_LOG_DEBUG("inspecting ns3::NetDevice" << ptr_net_device << " actual type is " << ptr_net_device->GetInstanceTypeId());
		if (ptr_net_device->GetInstanceTypeId() == NetDeviceT::GetTypeId()) {
			ns3::Ptr<ns3::Channel> ptr_channel = ptr_net_device->GetChannel();
			bool has_remote_net_device = false;
			for (unsigned j = 0; j < ptr_channel->GetNDevices(); ++j) {
				ns3::Ptr<ns3::NetDevice> ptr_remote_net_device =
						ptr_channel->GetDevice(j);
				NS_LOG_DEBUG("remote device " << ptr_remote_net_device << " " << ptr_remote_net_device->GetInstanceTypeId());
				if (ptr_remote_net_device == ptr_net_device) {
					continue;
				} else {
					has_remote_net_device = true;
					break;
				}//if
			}//for
			if (has_remote_net_device == false) {
				return ptr_net_device->GetObject<NetDeviceT> ();
			}//if
		}//if
	}//for
	NS_LOG_DEBUG("no unused port of " << NetDeviceT::GetTypeId());
	return NULL;
}

#endif /* CSMACHANNELNODE_H_ */
