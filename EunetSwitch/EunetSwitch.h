#ifndef EUNETSWITCH_H_
#define EUNETSWITCH_H_
#include <cassert>
#include <stdexcept>
#if 100000L < __cplusplus && __cplusplus <= 199711L
#include <strstream>
#include <boost/shared_ptr.hpp>
namespace std {
	using boost::shared_ptr;
}
#else
#include <memory>
#include <sstream>
#endif
#include "ns3/node.h"
#include "ns3/csma-helper.h"
#include "ns3/csma-channel.h"
#include "ns3/internet-stack-helper.h"
#include "ns3/bridge-helper.h"
#include "EunetTerminals.h"
#include "CsmaChannelNode.h"
#include "SimpleSwitch.h"

class EunetSwitch: public SimpleSwitch {
	typedef SimpleSwitch Base;
	EunetTerminals eunetTerminals;
	//std::vector<int> uplinkPortIndices;
	//std::vector<int> downlinkPortIndices;
	ns3::Ptr<ns3::OutputStreamWrapper> oswAsciiTrace;
	static const char* const pcapPrefix;
	static const char* const asciiTraceFileName;

public:
	static ns3::TypeId GetTypeId(void);
	EunetSwitch(const unsigned n_downlink_ports = 48,
			const unsigned n_uplink_ports = 4);
	virtual ~EunetSwitch();

	void setAsciiTraceFilename(const std::string& file_name) {
		ns3::AsciiTraceHelper ascii_trace_helper;
		this->oswAsciiTrace = ascii_trace_helper.CreateFileStream(file_name);
	}//createFileStream

	void enableAsciiTraceDownlink(const int i_downlink_port) {
		ns3::CsmaHelper csma_helper;
		csma_helper.EnableAscii(this->oswAsciiTrace, this->getDownlinkPort(
				i_downlink_port));
	}

	void enableAsciiTraceUplink(const int i_uplink_port) {
		ns3::CsmaHelper csma_helper;
		csma_helper.EnableAscii(this->oswAsciiTrace, this->getUplinkPort(
				i_uplink_port));
	}

	void enablePcapDownlink(const int i_downlink_port, const bool promiscuous =
			false) {
		ns3::CsmaHelper csma_helper;
		csma_helper.EnablePcap(EunetSwitch::pcapPrefix, this->getDownlinkPort(
				i_downlink_port), promiscuous);
	}

	void enablePcapUplink(const int i_uplink_port, const bool promiscuous =
			false) {
		ns3::CsmaHelper csma_helper;
		csma_helper.EnablePcap(EunetSwitch::pcapPrefix, this->getUplinkPort(
				i_uplink_port), promiscuous);
	}

#if 0
	std::shared_ptr<ns3::CsmaHelper> getDownlinkCsmaHelper() const {
		std::shared_ptr<ns3::CsmaHelper> csma_helper(new ns3::CsmaHelper());
		csma_helper->SetChannelAttribute("DataRate", ns3::DataRateValue(
						this->nDownlinkBps));
		csma_helper->SetChannelAttribute("Delay", ns3::TimeValue(
						ns3::MilliSeconds(this->nDownlinkDelayMilliseconds)));
		return csma_helper;
	}//getDownlinkCsmaHelper

	std::shared_ptr<ns3::CsmaHelper> getUplinkCsmaHelper() const {
		std::shared_ptr<ns3::CsmaHelper> csma_helper(new ns3::CsmaHelper());
		csma_helper->SetChannelAttribute("DataRate", ns3::DataRateValue(
						this->nUplinkBps));
		csma_helper->SetChannelAttribute("Delay", ns3::TimeValue(
						ns3::MilliSeconds(this->nUplinkDelayMilliseconds)));
		return csma_helper;
	}//getUplinkCsmaHelper
#endif
#if 0
	ns3::NetDeviceContainer getUplinkDevices() {
		ns3::NetDeviceContainer ndc;
		for (unsigned i = 0; i < this->nUplinkPorts; ++i) {
			ndc.Add(this->getUplinkPort(i));
		}//for
		return ndc;
	}//getUplinkDevices

	ns3::NetDeviceContainer getDownlinkDevices() {
		ns3::NetDeviceContainer ndc;
		for (uint32_t i = 0; i < this->nDownlinkPorts; ++i) {
			ndc.Add(this->getDownlinkPort(i));
		}//for
		return ndc;
	}//getDownlinkDevices
#endif
#if 0
	void setUplinkPortIndex(const int i_uplink_port) {
		this->setUplinkPortIndex(i_uplink_port, this->GetNDevices() - 1);
	}//setUplinkPortIndex

	void setUplinkPortIndex(const uint32_t i_uplink_port,
			const uint32_t i_net_device) {
		if (0 > i_uplink_port || this->uplinkPortIndices.size()
				<= i_uplink_port) {
			std::stringstream ss;
			ss << "max uplink port index is ";
			ss << this->uplinkPortIndices.size();
			ss << " while ";
			ss << i_uplink_port;
			ss << " is given.";
			throw std::invalid_argument(ss.str());
		}//if
		this->uplinkPortIndices[i_uplink_port] = i_net_device;
	}//setUplinkPortIndex

	void setDownlinkPortIndex(const uint32_t i_downlink_port) {
		this->setDownlinkPortIndex(i_downlink_port, this->GetNDevices() - 1);
	}//setUplinkPortIndex

	void setDownlinkPortIndex(const uint32_t i_downlink_port,
			const uint32_t i_net_device) {
		if (0 > i_downlink_port || this->downlinkPortIndices.size()
				<= i_downlink_port) {
			std::stringstream ss;
			ss << "max downlink port index is ";
			ss << this->downlinkPortIndices.size();
			ss << " while ";
			ss << i_downlink_port;
			ss << " is given.";
			throw std::invalid_argument(ss.str());
		}//if
		this->downlinkPortIndices[i_downlink_port] = i_net_device;
	}//setUplinkPortIndex
#endif

	EunetTerminals& getTerminals() {
		return this->eunetTerminals;
		//return this->ncTerminals;
	}//getTerminals

	ns3::NetDeviceContainer getTerminalDevices() {
		ns3::NetDeviceContainer ndc;
		for (unsigned i = 0; i < this->eunetTerminals.GetN(); ++i) {
			ndc.Add(this->eunetTerminals.Get(i)->getCsmaNetDevice(0));
		}//for
		return ndc;
	}//getTerminalDevices

	ns3::Ptr<EunetTerminal> getTerminal(const int i_downlink_port) {
		return this->eunetTerminals.Get(i_downlink_port);
	}//getTerminal

private:
	virtual void DoInitialize();
	virtual void NotifyConstructionCompleted();
};//class EunetSwitch

#endif /* EUNETSWITCH_H_ */

