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

NS_OBJECT_ENSURE_REGISTERED(EunetRouter);

ns3::TypeId EunetRouter::GetTypeId(void) {
	static ns3::TypeId type_id = ns3::TypeId("EunetRouter").SetParent<
			SimpleRouter> ().AddConstructor<EunetRouter> ();
	return type_id;
}//GetTypeId

void EunetRouter::DoDispose() {
	ASSERT_DD;
	SimpleRouter::DoDispose();
}//DoDispose

EunetRouter::EunetRouter() :
	INIT_DIDDNCC_FLAGS {
}// the constructor

void EunetRouter::DoInitialize() {
	ASSERT_DI;
	SimpleRouter::DoInitialize();
}//DoInitialize

void EunetRouter::NotifyConstructionCompleted() {
	ASSERT_NCC;
	SimpleRouter::NotifyConstructionCompleted();
}//NotifyConstructionCompleted

