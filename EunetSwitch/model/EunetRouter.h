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
#include "CsmaDevice.h"

using namespace ns3;

class EunetRouter: public SimpleRouter {

public:
	EunetTerminals eunetTerminals;
	static ns3::TypeId GetTypeId(void);
	EunetRouter();
	virtual ~EunetRouter() {
	}
	;

	EunetTerminals& getTerminals() {
		return this->eunetTerminals;
		//return this->ncTerminals;
	}//getTerminals

	ns3::NetDeviceContainer getTerminalDevices() {
		ns3::NetDeviceContainer ndc;
		for (unsigned i = 0; i < this->eunetTerminals.GetN(); ++i) {
			ndc.Add(this->eunetTerminals.Get(i)->getNetDevice<CsmaDevice> (0));
		}//for
		return ndc;
	}//getTerminalDevices

	ns3::Ptr<EunetTerminal> getTerminal(const int i_downlink_port) {
		return this->eunetTerminals.Get(i_downlink_port);
	}//getTerminal

private:
	bool isNotifyConstructionCompletedCalled;
	bool isDoInitializeCalled;
	bool isDoDisposeCalled;
protected:
	virtual void DoInitialize();
	virtual void NotifyConstructionCompleted();
	virtual void DoDispose();
};//class EunetRouter
#endif /* EUNETROUTER_H_ */
