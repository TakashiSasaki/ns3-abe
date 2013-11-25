#define NS3_LOG_ENABLE 1
#include "ns3/log.h"
NS_LOG_COMPONENT_DEFINE("PacketSinkNode");
#define NS3_ASSERT_ENABLE 1
#include "ns3/assert.h"
#include "ns3/applications-module.h"
#include "ns3/ipv4.h"
#include "ns3/internet-module.h"
#include "CsmaNode.h"
#include "CsmaChannelNode.h"
#include "CsmaInternetNode.h"
#include "PacketSinkNode.h"
NS_OBJECT_ENSURE_REGISTERED(PacketSinkNode);

ns3::TypeId PacketSinkNode::GetTypeId(void) {
	static ns3::TypeId type_id = ns3::TypeId("PacketSinkNode").SetParent<
			CsmaInternetNode> ().AddConstructor<PacketSinkNode> ();
	return type_id;
}//GetTypeId

PacketSinkNode::PacketSinkNode() {
}

PacketSinkNode::~PacketSinkNode() {
	// TODO !CodeTemplates.destructorstub.tododesc!
}

void PacketSinkNode::DoInitialize() {

}

void PacketSinkNode::NotifyConstructionCompleted() {

}
