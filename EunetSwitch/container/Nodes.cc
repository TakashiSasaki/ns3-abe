#define NS3_LOG_ENABLE 1
#include "ns3/log.h"
NS_LOG_COMPONENT_DEFINE("Nodes");
#define NS3_ASSERT_ENABLE 1
#include "ns3/assert.h"
#include "Nodes.h"

Nodes::Nodes() {
}

Nodes::~Nodes() {
}

template ns3::Ptr<ns3::Node> Nodes::get<ns3::Node>(const unsigned i_node);
