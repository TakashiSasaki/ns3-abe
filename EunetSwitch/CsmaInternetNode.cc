#define NS3_LOG_ENABLE 1
#include "ns3/log.h"
NS_LOG_COMPONENT_DEFINE("CsmaInternetNode");
#define NS3_ASSERT_ENABLE 1
#include "ns3/assert.h"
#include "ns3/applications-module.h"
#include "ns3/ipv4.h"
#include "ns3/internet-module.h"
#include "CsmaNode.h"
#include "CsmaChannelNode.h"
#include "CsmaInternetNode.h"

NS_OBJECT_ENSURE_REGISTERED(CsmaInternetNode);

ns3::TypeId CsmaInternetNode::GetTypeId(void) {
	static ns3::TypeId type_id = ns3::TypeId("CsmaInternetNode").SetParent<
			CsmaChannelNode> ().AddConstructor<CsmaInternetNode> ();
	return type_id;
}//GetTypeId

CsmaInternetNode::CsmaInternetNode(const int n_devices) :
	CsmaChannelNode(n_devices) {
}

CsmaInternetNode::~CsmaInternetNode() {
	// TODO !CodeTemplates.destructorstub.tododesc!
}
