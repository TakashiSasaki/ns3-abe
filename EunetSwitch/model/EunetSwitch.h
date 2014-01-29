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
	uint32_t nTerminals;
	bool dontAttachTerminals;

	//ns3::Ptr<ns3::OutputStreamWrapper> oswAsciiTrace;
	static const char* const pcapPrefix;
	static const char* const asciiTracePrefix;

public:
	EunetTerminals eunetTerminals;
	static ns3::TypeId GetTypeId(void);
	EunetSwitch();
	virtual ~EunetSwitch();

	void attachTerminals();
	void detachTerminals();

	EunetTerminals& getTerminals() {
		return eunetTerminals;
		//return this->ncTerminals;
	}//getTerminals

	ns3::NetDeviceContainer getTerminalDevices() {
		ns3::NetDeviceContainer ndc;
		for (unsigned i = 0; i < this->eunetTerminals.GetN(); ++i) {
			ndc.Add(this->eunetTerminals.Get(i)->getDevice<CsmaDevice> (0));
		}//for
		return ndc;
	}//getTerminalDevices

	ns3::Ptr<EunetTerminal> getTerminal(const int i_downlink_port) {
		return this->eunetTerminals.Get(i_downlink_port);
	}//getTerminal

DECLARE_DIDDNCC
};//class EunetSwitch

#endif /* EUNETSWITCH_H_ */
