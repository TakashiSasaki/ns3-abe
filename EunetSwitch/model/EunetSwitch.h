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
	EunetTerminals eunetTerminals;
	//ns3::Ptr<ns3::OutputStreamWrapper> oswAsciiTrace;
	static const char* const pcapPrefix;
	static const char* const asciiTracePrefix;

public:
	static ns3::TypeId GetTypeId(void);
	EunetSwitch(const unsigned n_downlink_ports = 48,
			const unsigned n_uplink_ports = 4);
	virtual ~EunetSwitch() {
	}
	;

#if 0
	void setAsciiTraceFilename(const std::string& file_name) {
		ns3::AsciiTraceHelper ascii_trace_helper;
		this->oswAsciiTrace = ascii_trace_helper.CreateFileStream(file_name);
	}//createFileStream
#endif

	void enableAsciiTraceDownlink(const int i_downlink_port) {
		ns3::CsmaHelper csma_helper;
		csma_helper.EnableAscii(asciiTracePrefix, this->getDownlinkPort(
				i_downlink_port));
	}

	void enableAsciiTraceUplink(const int i_uplink_port) {
		ns3::CsmaHelper csma_helper;
		csma_helper.EnableAscii(asciiTracePrefix, this->getUplinkPort(
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

	EunetTerminals& getTerminals() {
		return this->eunetTerminals;
		//return this->ncTerminals;
	}//getTerminals

	ns3::NetDeviceContainer getTerminalDevices() {
		ns3::NetDeviceContainer ndc;
		for (unsigned i = 0; i < this->eunetTerminals.GetN(); ++i) {
			ndc.Add(this->eunetTerminals.Get(i)->getNetDevice<
					ns3::CsmaNetDevice> (0));
		}//for
		return ndc;
	}//getTerminalDevices

	ns3::Ptr<EunetTerminal> getTerminal(const int i_downlink_port) {
		return this->eunetTerminals.Get(i_downlink_port);
	}//getTerminal

DECLARE_DIDDNCC
};//class EunetSwitch

#endif /* EUNETSWITCH_H_ */
