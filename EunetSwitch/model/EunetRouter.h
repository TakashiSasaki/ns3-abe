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
	//typedef SimpleRouter Base;
	EunetTerminals eunetTerminals;

	static const char* const pcapPrefix;
	static const char* const asciiTracePrefix;

public:
	static ns3::TypeId GetTypeId(void);
	EunetRouter(const unsigned n_ports = 48);
	virtual ~EunetRouter();

	void enablePcap(const int i_port, const bool promiscuous = false) {
		ns3::CsmaHelper csma_helper;
		csma_helper.EnablePcap(EunetRouter::pcapPrefix, this->getLinkPort(
				i_port), promiscuous);
	}

	void enableAsciiTrace(const int i_port) {
		ns3::CsmaHelper csma_helper;
		csma_helper.EnableAscii(EunetRouter::asciiTracePrefix, this->getLinkPort(i_port));
	}
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
};//class EunetRouter
#endif /* EUNETROUTER_H_ */
