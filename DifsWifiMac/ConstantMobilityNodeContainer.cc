#include <cassert>
#include "ns3/mobility-module.h"
#include "ns3/net-device.h"
#include "ConstantMobilityNodeContainer.h"

abe::ConstantMobilityNodeContainer::ConstantMobilityNodeContainer(
		const int n_nodes) {
	this->Create(n_nodes);
	for (int i = 0; i < n_nodes; ++i) {
		this->Get(i)->AggregateObject(ns3::CreateObject<
				ns3::ConstantPositionMobilityModel>());
	}//for
	ns3::MobilityHelper mobility_helper;
	ns3::Ptr<ns3::ListPositionAllocator> positionAlloc = ns3::CreateObject<
			ns3::ListPositionAllocator>();
	double x = 0;
	for (uint32_t n = 0; n < this->GetN(); n++) {
		positionAlloc->Add(ns3::Vector(x, 0.0, 0.0));
		x += 5.0;
	}//for
	mobility_helper.SetPositionAllocator(positionAlloc);
	mobility_helper.SetMobilityModel("ns3::ConstantPositionMobilityModel");
	mobility_helper.Install(*this);
	for (uint32_t i = 0; i < this->GetN(); ++i) {
		assert(this->Get(i)->GetNDevices() == 0);
	}//for
}// a constructor

ns3::NetDeviceContainer abe::ConstantMobilityNodeContainer::getNetDeviceContainer() {
	ns3::NetDeviceContainer ndc;
	for (uint32_t i = 0; i < this->GetN(); ++i) {
		assert(this->Get(i)->GetNDevices() >= 1);
		ndc.Add(this->Get(i)->GetDevice(0));
	}//for
	return ndc;
}//getNetDevices

ns3::Ptr<ns3::NetDevice> abe::ConstantMobilityNodeContainer::getNetDevice(
		const int i_node) {
	//return this->getNetDeviceContainer().Get(i_node);
	return this->Get(i_node)->GetDevice(0);
}//getNetDevice

abe::ConstantMobilityNodeContainer::~ConstantMobilityNodeContainer() {
	// TODO !CodeTemplates.destructorstub.tododesc!
}// the destructor

