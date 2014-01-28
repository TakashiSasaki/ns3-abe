#ifndef SIMPLESWITCH_H_
#define SIMPLESWITCH_H_
#include "ns3/nstime.h"
#include "init.h"
#include "CsmaChannelNode.h"
#include "UplinkDevice.h"
#include "DownlinkDevice.h"

class SimpleSwitch: public CsmaChannelNode {
protected:
	ns3::DataRate uplinkDataRate;
	ns3::Time uplinkDelay;
	ns3::DataRate downlinkDataRate;
	ns3::Time downlinkDelay;
	unsigned nUplinkPorts;
	unsigned nDownlinkPorts;
public:

	static ns3::TypeId GetTypeId(void);
	SimpleSwitch();
	virtual ~SimpleSwitch();

	void connectUpTo(const unsigned i_uplink_port,
			ns3::Ptr<SimpleSwitch> upstream_switch,
			const unsigned i_downlink_port);
	void connectUpTo(std::string upstream_switch_name);
	void connectDownTo(const std::string downstream_switch_name);
	void connectSibling(const unsigned i_uplink_port,
			ns3::Ptr<SimpleSwitch> sibling_switch,
			const unsigned i_sibling_uplink_port);
	void enableAsciiTraceDownlink(const int i_downlink_port);
	void enableAsciiTraceUplink(const int i_uplink_port);
#if 0
protected:
	template<class D, class N>
	bool isConnectedTo(const unsigned i_port);
#endif
DECLARE_DIDDNCC
};

#if 0
template<class D, class N>
bool SimpleSwitch::isConnectedTo(const unsigned i_port) {
	ns3::Ptr<ns3::CsmaChannel> ptr_csma_channel = this->getCsmaChannel<D> (
			i_port);
	NS_LOG_INFO("node=" << this->GetId() << " port=" << i_port
			<< " channel is attached to " << ptr_csma_channel->GetNDevices()
			<< " devices ");
	for (unsigned i = 0; i < ptr_csma_channel->GetNDevices(); ++i) {
		NS_LOG_INFO("inspecting port " << i);
		ns3::Ptr<ns3::NetDevice> ptr_net_device =
		ptr_csma_channel->GetDevice(i);
		NS_LOG_INFO("expecting NetDevice .. " << ptr_net_device->GetTypeId());
		auto ptr_node = ptr_net_device->GetNode();
		NS_LOG_INFO("expecting Node .. " << ptr_node->GetTypeId());
		if (ptr_node->GetId() == this->GetId()) {
			continue;
		}//if
		ns3::Ptr<N> ptr_n = ptr_node->GetObject<N> ();
		NS_LOG_INFO("expecting " << N::GetTypeId() << " .. "
				<< ptr_node->GetTypeId());
		if (ptr_n) {
			return true;
		}//if
	}//for
	return false;
}//isConnectedToSimpleSwitch
#endif

#endif /* SIMPLESWITCH_H_ */
