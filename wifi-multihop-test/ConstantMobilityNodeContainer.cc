#include "ns3/mobility-module.h"
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
	for (int n = 0; n < this->GetN(); n++) {
		positionAlloc->Add(ns3::Vector(x, 0.0, 0.0));
		x += 5.0;
	}//for
	mobility_helper.SetPositionAllocator(positionAlloc);
	mobility_helper.SetMobilityModel("ns3::ConstantPositionMobilityModel");
	mobility_helper.Install(*this);
}// a constructor

abe::ConstantMobilityNodeContainer::~ConstantMobilityNodeContainer() {
	// TODO !CodeTemplates.destructorstub.tododesc!
}// the destructor

