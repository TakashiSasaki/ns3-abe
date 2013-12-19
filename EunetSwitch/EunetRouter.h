#ifndef EUNETROUTER_H_
#define EUNETROUTER_H_
#include <cassert>
#include <stdexcept>
#include <memory>
#include <sstream>
#include "ns3/node.h"
#include "ns3/csma-helper.h"
#include "ns3/csma-channel.h"
#include "ns3/internet-stack-helper.h"
#include "ns3/bridge-helper.h"
#include "EunetTerminals.h"
#include "CsmaChannelNode.h"
#include "ns3/log.h"
#include "SimpleRouter.h"

using namespace ns3;

class EunetRouter: public SimpleRouter {
	typedef SimpleRouter Base;

	static const char* const pcapPrefix;
	static const char* const asciiTracePrefix;

public:
	static ns3::TypeId GetTypeId(void);
	EunetRouter(const unsigned n_ports = 48, const unsigned n_devices = 2);
	virtual ~EunetRouter();

	void enablePcap(const int i_port, const bool promiscuous = false) {
		ns3::CsmaHelper csma_helper;
		csma_helper.EnablePcap(EunetRouter::pcapPrefix, this->getlinkPort(
				i_port), promiscuous);
	}

	void enableAsciiTrace(const int i_port) {
		ns3::CsmaHelper csma_helper;
		csma_helper.EnableAscii(EunetRouter::asciiTracePrefix, this->getlinkPort(i_port));
	}



};//class EunetRouter
#endif /* EUNETROUTER_H_ */
