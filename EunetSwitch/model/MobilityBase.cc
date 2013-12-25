#define NS3_LOG_ENABLE 1
#include "ns3/log.h"
NS_LOG_COMPONENT_DEFINE("MobilityBase");
#define NS3_ASSERT_ENABLE 1
#include "ns3/assert.h"
#include "ns3/mobility-helper.h"
#include "MobilityBase.h"

MobilityBase::MobilityBase(ns3::Node* p_node,
		const ns3::Vector initial_position) :
	ptrNode(p_node, true), initialPosition(initialPosition) {
}

MobilityBase::~MobilityBase() {
}

void MobilityBase::DoInitialize() {
	//auto ptr_node = ns3::Ptr<SimpleAp>(this, true);
	this->setPosition(this->initialPosition);
}

void MobilityBase::setPosition(const ns3::Vector& position) {
	NS_LOG_INFO("setting position to " << position);
	ns3::MobilityHelper mobility_helper;
	auto ptr_position_allocator =
			ns3::CreateObject<ns3::ListPositionAllocator>();
	ptr_position_allocator->Add(position);
	mobility_helper.SetPositionAllocator(ptr_position_allocator);
	mobility_helper.SetMobilityModel("ns3::ConstantPositionMobilityModel");
	mobility_helper.Install(ptrNode);
}//setPosition
