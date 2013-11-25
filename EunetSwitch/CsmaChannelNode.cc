#define NS3_LOG_ENABLE 1
#include "ns3/log.h"
NS_LOG_COMPONENT_DEFINE("CsmaChannelNode");
#define NS3_ASSERT_ENABLE 1
#include "ns3/assert.h"
#include "ns3/queue.h"
#include "ns3/node.h"
#include "CsmaNode.h"
#include "CsmaChannelNode.h"
NS_OBJECT_ENSURE_REGISTERED(CsmaChannelNode);

ns3::TypeId CsmaChannelNode::GetTypeId(void) {
	static ns3::TypeId type_id = ns3::TypeId("CsmaChannelNode").SetParent<
			CsmaNode> ().AddConstructor<CsmaChannelNode> ();
	return type_id;
}//GetTypeId

CsmaChannelNode::CsmaChannelNode() {
	this->csmaChannelFactory.SetTypeId("ns3::CsmaChannel");
	this->ptrCsmaChannel = this->csmaChannelFactory.Create()->GetObject<
			ns3::CsmaChannel> ();
	this->getCsmaNetDevice()->Attach(this->ptrCsmaChannel);
}

CsmaChannelNode::~CsmaChannelNode() {
	// TODO !CodeTemplates.destructorstub.tododesc!
}

void CsmaChannelNode::bring(ns3::Ptr<CsmaChannelNode> ptr_newcomer) {
	auto ptr_newcomer_device = ptr_newcomer->getCsmaNetDevice();
	ptr_newcomer_device->Attach(this->ptrCsmaChannel);
}
