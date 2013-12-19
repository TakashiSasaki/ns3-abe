#include <memory>
#include <sstream>
#define NS3_LOG_ENABLE 1
#include "ns3/log.h"
NS_LOG_COMPONENT_DEFINE("SimpleRouter");
#define NS3_ASSERT_ENABLE 1
#include "ns3/assert.h"
#include "ns3/type-id.h"
#include "ns3/bridge-helper.h"
#include "ns3/quagga-helper.h"
#include "EunetRouter.h"
#include "SimpleRouter.h"
#include "CsmaChannelNode.h"

NS_OBJECT_ENSURE_REGISTERED(EunetRouter);

EunetRouter::~EunetRouter() {
}

EunetRouter::EunetRouter(const unsigned n_port, const unsigned n_devices) :
	SimpleRouter(48) {
	NS_LOG_INFO("constructing EunetRouter");
	for (unsigned i = 0; i < n_devices; ++i) {
		NS_LOG_INFO("attaching " << i << " to corresponding port");
		this->bring(i,SimpleRouter);

	}
}
