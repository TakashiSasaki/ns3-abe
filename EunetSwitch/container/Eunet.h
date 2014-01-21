#ifndef EUNET_H_
#define EUNET_H_
#include <cmath>
#define NS3_ASSERT_ENABLE 1
#include "ns3/assert.h"
#include "ns3/node-container.h"
#include "ns3/csma-channel.h"
#include "Eunet.h"
#include "EunetSwitch.h"
#include "EunetRouter.h"

class Eunet: public ns3::NodeContainer {
public:
	enum ActiveChannel {
		SRC = 0, DST = 1, SLOWER = 2
	};
	ns3::ObjectFactory eunetRouterFactory;
	ns3::ObjectFactory eunetSwitchFactory;
	ns3::ObjectFactory eunetTerminalFactory;
	Eunet();
	virtual ~Eunet();

	template<class SrcNodeT = CsmaChannelNode,
			class SrcDeviceT = ns3::CsmaNetDevice,
			class DstNodeT = CsmaChannelNode,
			class DstDeviceT = ns3::CsmaNetDevice>
	ns3::NetDeviceContainer connect(const std::string& src_name,
			const std::string& dst_name, Eunet::ActiveChannel = SRC);
	ns3::NetDeviceContainer connectUpTo(const std::string& src_name,
			const std::string& dst_name, Eunet::ActiveChannel = SRC);
	ns3::NetDeviceContainer connectDownTo(const std::string& src_name,
			const std::string& dst_name, ActiveChannel = SRC);
	ns3::NetDeviceContainer connectToRouter(std::string src_name,
			std::string dst_name, ns3::Ipv4Address dst_address,
			ns3::Ipv4Mask dst_mask, ActiveChannel = SRC);
	ns3::NetDeviceContainer connectRouters(std::string src_name,
			std::string dst_name, ns3::Ipv4Address src_address,
			ns3::Ipv4Address dst_address, ns3::Ipv4Mask ipv4_mask,
			ActiveChannel = SRC);

	template<class NodeT, class DeviceT>
	void enablePcap(const unsigned i_port);

	template<class NodeT, class DeviceT>
	void enableAsciiTrace(const unsigned i_port);

	ns3::Ptr<EunetSwitch> addEunetSwitch(std::string name,
			const unsigned n_uplink_ports, const unsigned n_downlik_ports,
			const ns3::DataRate& uplink_data_rate,
			const ns3::DataRate& downlink_data_rate,
			const ns3::Time& uplink_delay = ns3::MilliSeconds(1),
			const ns3::Time& downlink_delay = ns3::MilliSeconds(1));

	ns3::Ptr<EunetRouter> addEunetRouter(std::string name);

	void attachEunetTerminals();
private:
};

#if 0
template<class SrcNodeT, class SrcDeviceT, class DstNodeT, class DstDeviceT>
void Eunet::connectNew(std::string src_name, std::string dst_name,
		bool use_source_channel) {
	NS_ASSERT((SrcNodeT::GetTypeId()==EunetSwitch::GetTypeId())
			|| (SrcNodeT::GetTypeId()==EunetRouter::GetTypeId()));
	ns3::Ptr<CsmaChannelNode> ptr_src = ns3::Names::Find<SrcNodeT>(src_name);
	if (ptr_src == NULL) {
		auto ptr_node = ns3::CreateObject<SrcNodeT>();
		NS_ASSERT(ptr_node != NULL);
		this->Add(ptr_node);
	}//if
	ns3::Ptr<CsmaChannelNode> ptr_dst = ns3::Names::Find<DstNodeT>(dst_name);
	if (ptr_dst == NULL) {
		auto ptr_node = ns3::CreateObject<DstNodeT>();
		NS_ASSERT(ptr_node != NULL);
		this->Add(ptr_node);
	}//if

	ns3::Ptr<SrcDeviceT> ptr_src_device = ptr_src->getUnusedPort<SrcDeviceT> ();
	ns3::Ptr<DstDeviceT> ptr_dst_device = ptr_dst->getUnusedPort<DstDeviceT> ();
	ns3::Ptr<ns3::Channel> ptr_src_channel = ptr_src_device->GetChannel();
	auto ptr_src_csma_channel = ptr_src_channel->GetObject<ns3::CsmaChannel> ();
	ptr_dst_device->Attach(ptr_src_csma_channel);
}
#endif

template<class SrcNodeT, class SrcDeviceT, class DstNodeT, class DstDeviceT>
ns3::NetDeviceContainer Eunet::connect(const std::string& src_name,
		const std::string& dst_name, Eunet::ActiveChannel active_channel) {
	//NS_ASSERT((SrcNodeT::GetTypeId()==EunetSwitch::GetTypeId())	|| (SrcNodeT::GetTypeId()==EunetRouter::GetTypeId()));
	ns3::Ptr<CsmaChannelNode> ptr_src = ns3::Names::Find<SrcNodeT>(src_name);
	NS_ASSERT_MSG((ptr_src != 0), "cannot find node " << src_name);
	ns3::Ptr<CsmaChannelNode> ptr_dst = ns3::Names::Find<DstNodeT>(dst_name);
	NS_ASSERT_MSG((ptr_dst != 0), "cannot find node " << dst_name);
	ns3::Ptr<CsmaDevice> ptr_src_port = ptr_src->getUnusedPort<SrcDeviceT> ();
	NS_ASSERT_MSG(ptr_src_port != 0, ptr_src_port);
	ns3::Ptr<CsmaDevice> ptr_dst_port = ptr_dst->getUnusedPort<DstDeviceT> ();
	NS_ASSERT_MSG(ptr_dst_port != 0, ptr_dst_port);
	auto ptr_src_channel = ptr_src_port->GetChannel()->GetObject<
			ns3::CsmaChannel> ();
	auto ptr_dst_channel = ptr_dst_port->GetChannel()->GetObject<
			ns3::CsmaChannel> ();
	switch (active_channel) {
	case SRC:
		ptr_dst_port->Attach(ptr_src_channel);
		{
			ns3::NetDeviceContainer ndc;
			ndc.Add(ptr_src_port);
			ndc.Add(ptr_dst_port);
			return ndc;
		}
	case DST:
		ptr_src_port->Attach(ptr_dst_channel);
		{
			ns3::NetDeviceContainer ndc;
			ndc.Add(ptr_src_port);
			ndc.Add(ptr_dst_port);
			return ndc;
		}
	default:
		NS_FATAL_ERROR("only SRC and DST are supported.");
	}//switch
}

#endif /* EUNET_H_ */
