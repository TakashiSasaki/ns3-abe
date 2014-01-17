#ifndef SIMPLESWITCH_H_
#define SIMPLESWITCH_H_
#include "ns3/nstime.h"
#include "init.h"
#include "CsmaChannelNode.h"
#include "UplinkNetDevice.h"
#include "DownlinkNetDevice.h"

class SimpleSwitch: public CsmaChannelNode {
	//	const int nDownlinkBps;
	//	const int nDownlinkDelayMilliseconds;
	//	const int nUplinkBps;
	//	const int nUplinkDelayMilliseconds;
	//static const ns3::DataRate defaultUplinkDataRate;
	//static const ns3::DataRate defaultDownlinkDataRate;
	//static const ns3::TimeValue defaultUplinkDelay;
	//static const ns3::TimeValue defaultDownlinkDelay;
	ns3::DataRate uplinkDataRate;
	ns3::Time uplinkDelay;
	ns3::DataRate downlinkDataRate;
	ns3::Time downlinkDelay;
	unsigned nUplinkPorts;
	unsigned nDownlinkPorts;
public:

	static ns3::TypeId GetTypeId(void);
	SimpleSwitch(/*const unsigned n_downlink_ports = 4,
	 const unsigned n_uplink_ports = 1*/);
	virtual ~SimpleSwitch() {
	}
	;
	void setNUplinkPorts(uint32_t n_uplink_ports);
	uint32_t getNUplinkPorts() const;
	void setNDownlinkPorts(uint32_t n_downlink_ports);
	uint32_t getNDownlinkPorts() const;
	void setUplinkDataRate(ns3::DataRate uplink_data_rate);
	ns3::DataRate getUplinkDataRate() const;
	void setDownlinkDataRate(ns3::DataRate downlink_data_rate);
	ns3::DataRate getDownlinkDataRate() const;
	void setUplinkDelay(ns3::Time uplink_delay);
	ns3::Time getUplinkDelay() const;
	void setDownlinkDelay(ns3::Time downlink_delay);
	ns3::Time getDownlinkDelay() const;

	//	void setDownlinkDataRate(ns3::DataRateValue = defaultDownlinkDataRate);
	//	void setDownlinkDelay(ns3::TimeValue = defaultDownlinkDelay);
	//	void setUplinkDataRate(ns3::DataRateValue = defaultUplinkDataRate);
	//	void setUplinkDelay(ns3::TimeValue = defaultUplinkDelay);
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
	void enableAsciiTraceDownlink(const int i_downlink_port);
	void enableAsciiTraceUplink(const int i_uplink_port);
	void enablePcapDownlink(const int i_downlink_port, const bool promiscuous =
			false);
	void enablePcapUplink(const int i_uplink_port, const bool promiscuous =
			false);
private:
	bool isNotifyConstructionCompletedCalled;
	bool isDoInitializeCalled;
	bool isDoDisposeCalled;
protected:
	virtual void DoInitialize();
	virtual void NotifyConstructionCompleted();
	virtual void DoDispose();
private:
	bool isConnectedToSimpleSwitch(const unsigned i_port);
};

#endif /* SIMPLESWITCH_H_ */
