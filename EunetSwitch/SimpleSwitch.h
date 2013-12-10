#ifndef SIMPLESWITCH_H_
#define SIMPLESWITCH_H_
#include "ns3/nstime.h"
#include "CsmaChannelNode.h"

class SimpleSwitch: public CsmaChannelNode {
	typedef CsmaChannelNode Base;
	//	const int nDownlinkBps;
	//	const int nDownlinkDelayMilliseconds;
	//	const int nUplinkBps;
	//	const int nUplinkDelayMilliseconds;
	static const ns3::DataRate defaultUplinkDataRate;
	static const ns3::DataRate defaultDownlinkDataRate;
	static const ns3::TimeValue defaultUplinkDelay;
	static const ns3::TimeValue defaultDownlinkDelay;
public:
	const unsigned nUplinkPorts;
	const unsigned nDownlinkPorts;

	static ns3::TypeId GetTypeId(void);
	SimpleSwitch(const unsigned n_downlink_ports = 4,
			const unsigned n_uplink_ports = 1);
	virtual ~SimpleSwitch();
	void setDownlinkDataRate(ns3::DataRateValue = defaultDownlinkDataRate);
	void setDownlinkDelay(ns3::TimeValue = defaultDownlinkDelay);
	void setUplinkDataRate(ns3::DataRateValue = defaultUplinkDataRate);
	void setUplinkDelay(ns3::TimeValue = defaultUplinkDelay);
	ns3::Ptr<ns3::CsmaNetDevice>
	getUplinkPort(const unsigned i_uplink_port);
	ns3::Ptr<ns3::CsmaNetDevice>
	getDownlinkPort(const unsigned i_downlink_port);
	void connectUpTo(const unsigned i_uplink_port,
			ns3::Ptr<SimpleSwitch> upstream_switch,
			const unsigned i_downlink_port);
	void connectUpTo(std::string upstream_switch_name);
	void connectDownTo(const unsigned i_downlink_port,
			ns3::Ptr<SimpleSwitch> downstream_switch,
			const unsigned i_uplink_port);
	void connectDownTo(const std::string downstream_switch_name);
	void connectSibling(const unsigned i_uplink_port,
			ns3::Ptr<SimpleSwitch> sibling_switch,
			const unsigned i_sibling_uplink_port);
	unsigned getUnusedUplinkPort();
	unsigned getUnusedDownlinkPort();
protected:
	virtual void DoInitialize();
	virtual void NotifyConstructionCompleted();
private:
	bool isConnectedToSimpleSwitch(const unsigned i_port);
};

#endif /* SIMPLESWITCH_H_ */
