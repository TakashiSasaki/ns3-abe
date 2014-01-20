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
			CsmaNode> ().AddConstructor<CsmaChannelNode> ().AddAttribute(
			"csmaChannelDataRate", "csmaChannelDataRate", ns3::DataRateValue(
					1000000), ns3::MakeDataRateAccessor(
					&CsmaChannelNode::csmaChannelDataRate),
			ns3::MakeDataRateChecker()) .AddAttribute("csmaChannelDelay",
			"csmaChannelDelay", ns3::TimeValue(ns3::MilliSeconds(10)),
			ns3::MakeTimeAccessor(&CsmaChannelNode::csmaChannelDelay),
			ns3::MakeTimeChecker());
	return type_id;
}//GetTypeId

CsmaChannelNode::CsmaChannelNode() :
	CsmaNode(), INIT_DIDDNCC_FLAGS {
}

CsmaChannelNode::~CsmaChannelNode() {
}

void CsmaChannelNode::NotifyConstructionCompleted() {
	ASSERT_NCC;
	NS_ASSERT(this->GetNDevices()==0);
	CsmaNode::NotifyConstructionCompleted();
	NS_ASSERT_MSG(GetNDevices()==nPorts, GetNDevices() << ","<<nPorts);
}

void CsmaChannelNode::DoInitialize() {
	ASSERT_DI;
	//NS_ASSERT_MSG(this->GetNDevices()==1, "GetNDevices=" << this->GetNDevices() << " getNPorts=" << this->getNPorts());
	CsmaNode::DoInitialize();
	NS_ASSERT(this->getNDevices<ns3::CsmaNetDevice>()==this->nPorts);
	NS_LOG_INFO("constructing CsmaChannelNode with " << this->nPorts << " ports");
	this->csmaChannelFactory.SetTypeId("ns3::CsmaChannel");
	this->csmaChannelFactory.Set("DataRate", ns3::DataRateValue(
			this->csmaChannelDataRate));
	this->csmaChannelFactory.Set("Delay",
			ns3::TimeValue(this->csmaChannelDelay));
	for (unsigned i = 0; i < this->getNDevices<ns3::CsmaNetDevice> (); ++i) {
		ns3::Ptr<ns3::CsmaChannel>
				ptr_csma_channel =
						this->csmaChannelFactory.Create()->GetObject<
								ns3::CsmaChannel> ();
		NS_LOG_INFO("attaching a channel to device #" << i);
		this->getNetDevice<ns3::CsmaNetDevice> (i)->Attach(ptr_csma_channel);
	}//for
}

void CsmaChannelNode::DoDispose() {
	ASSERT_DD;
	CsmaNode::DoDispose();
}

void CsmaChannelNode::bring(ns3::Ptr<CsmaNode> ptr_newcomer,
		const unsigned i_their_csma_device) {
	this->bring<ns3::CsmaNetDevice, ns3::CsmaNetDevice> (0, ptr_newcomer,
			i_their_csma_device);
}

void CsmaChannelNode::setCsmaChannelDataRate(
		const ns3::DataRateValue& data_rate, const unsigned i_channel) {
	auto ptr_csma_channel =
			this->getCsmaChannel<ns3::CsmaNetDevice> (i_channel);
	ptr_csma_channel->SetAttribute("DataRate", data_rate);
}

void CsmaChannelNode::setCsmaChannelDataRateAll(
		const ns3::DataRateValue& data_rate) {
	for (unsigned i = 0; i < this->getNDevices<ns3::CsmaNetDevice> (); ++i) {
		this->setCsmaChannelDataRate(data_rate, i);
	}//for
}

void CsmaChannelNode::setCsmaChannelDelay(const ns3::TimeValue& delay,
		const unsigned i_channel) {
	auto p = this->getCsmaChannel<ns3::CsmaNetDevice> (i_channel);
	p->SetAttribute("Delay", delay);
}

void CsmaChannelNode::setCsmaChannelDelayAll(const ns3::TimeValue& delay) {
	for (unsigned i = 0; i < this->getNDevices<ns3::CsmaNetDevice> (); ++i) {
		this->setCsmaChannelDelay(delay, i);
	}
}

template void CsmaChannelNode::addCsmaChannel<ns3::CsmaNetDevice>(
		const unsigned i_port, const ns3::DataRate& data_rate,
		const ns3::Time& delay);

template
ns3::Ptr<ns3::CsmaChannel> CsmaChannelNode::getCsmaChannel<ns3::CsmaNetDevice>(
		unsigned i_port);

template
void CsmaChannelNode::bring<ns3::CsmaNetDevice, ns3::CsmaNetDevice>(
		const unsigned i_our_csma_device, ns3::Ptr<CsmaNode> ptr_their_node,
		const unsigned i_their_csma_device);

template
ns3::Ptr<ns3::CsmaNetDevice> CsmaChannelNode::getUnusedPort();
