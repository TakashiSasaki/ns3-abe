#include <memory>
#include <sstream>
#define NS3_LOG_ENABLE 1
#include "ns3/log.h"
NS_LOG_COMPONENT_DEFINE("EunetRouter");
#define NS3_ASSERT_ENABLE 1
#include "ns3/assert.h"
#include "ns3/type-id.h"
#include "ns3/bridge-helper.h"
#include "ns3/quagga-helper.h"
#include "ns3/dce-application-helper.h"
#include "EunetRouter.h"
#include "SimpleRouter.h"
//#include "CsmaChannelNode.h"

NS_OBJECT_ENSURE_REGISTERED(EunetRouter);

ns3::TypeId EunetRouter::GetTypeId(void) {
	static ns3::TypeId type_id = ns3::TypeId("EunetRouter").SetParent<
			SimpleRouter> ().AddConstructor<EunetRouter> ();
	return type_id;
}//GetTypeId

const char* const EunetRouter::pcapPrefix = "EunetRouter";
const char* const EunetRouter::asciiTracePrefix = "EunetRouter";

void EunetRouter::DoDispose() {
	NS_ASSERT(!this->isDoDisposeCalled);
	this->isDoDisposeCalled = true;
	NS_ASSERT(this->isNotifyConstructionCompletedCalled);
	NS_ASSERT(this->isDoInitializeCalled);
	SimpleRouter::DoDispose();
}//DoDispose

EunetRouter::EunetRouter(const unsigned n_ports) :
	SimpleRouter(n_ports), eunetTerminals(n_ports),
			isNotifyConstructionCompletedCalled(false), isDoInitializeCalled(
					false), isDoDisposeCalled(false) {
	NS_LOG_INFO("constructing EunetRouter");
	//	NS_LOG_INFO("attaching " << this->eunetTerminals.GetN() << " terminal(s) to corresponding port(s)");
	//	for (unsigned i = 0; i < this->eunetTerminals.GetN(); ++i) {
	//		NS_LOG_INFO("attaching terminal " << i << " to corresponding port");
	//		this->bring(i, this->eunetTerminals.Get(i), 0);
	//	}
}// the constructor

void EunetRouter::DoInitialize() {
	NS_ASSERT(!this->isDoInitializeCalled);
	this->isDoInitializeCalled = true;
	NS_LOG_INFO("just calling up");
	SimpleRouter::DoInitialize();
}//DoInitialize

void EunetRouter::NotifyConstructionCompleted() {
	NS_ASSERT(!this->isNotifyConstructionCompletedCalled);
	this->isNotifyConstructionCompletedCalled = true;
	NS_LOG_INFO("just calling up");
	SimpleRouter::NotifyConstructionCompleted();
}//NotifyConstructionCompleted
