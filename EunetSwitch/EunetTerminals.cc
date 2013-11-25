#define NS3_LOG_ENABLE 1
#include "ns3/log.h"
#define NS3_ASSERT_ENABLE 1
#include "ns3/assert.h"
#include "ns3/csma-helper.h"
#include "ns3/ipv4-address-helper.h"
#include "ns3/internet-stack-helper.h"
NS_LOG_COMPONENT_DEFINE("EunetTerminals");
#include "EunetTerminal.h"
#include "EunetTerminals.h"

EunetTerminals::EunetTerminals(const int n_terminals) {
	NS_LOG_INFO("constructing EunetTerminals");
	ns3::Ipv4AddressHelper ipv4_address_helper(ns3::Ipv4Address("10.0.0.0"),
			ns3::Ipv4Mask("255.0.0.0"));
	ns3::ObjectFactory object_factory;
	object_factory.SetTypeId("EunetTerminal");
	for (int i = 0; i < n_terminals; ++i) {
		NS_LOG_INFO("creating EunetTerminal node " << i);
		ns3::Ptr<EunetTerminal> ptr_eunet_terminal = object_factory.Create<
				EunetTerminal> ();
		NS_LOG_INFO(ptr_eunet_terminal->GetNDevices() << " device(s)");
		//auto ptr_eunet_terminal = object_factory.Create<EunetTerminal> ();
		//ns3::Ptr<ns3::Node> ptr_eunet_terminal(
		//		ns3::CreateObject<EunetTerminal>());
		NS_ASSERT(ptr_eunet_terminal->GetNDevices()==2);
		ptr_eunet_terminal->assignAddress(ipv4_address_helper);
		this->terminals.Add(ptr_eunet_terminal);
	}//for

	for (unsigned i = 0; i < terminals.GetN(); ++i) {
		NS_LOG_INFO("getting source EunetTerminal");
		auto ptr_source = this->terminals.Get(i)->GetObject<EunetTerminal> ();
		NS_LOG_INFO("getting remote EunetTerminal");
		auto ptr_remote = this->terminals.Get(0)->GetObject<EunetTerminal> ();
		NS_LOG_INFO("setting remote EunetTerminal");
		ptr_source->setRemote(ptr_remote);
		ptr_source->startAt(ns3::Seconds(0.0));
		ptr_source->stopAt(ns3::Seconds(2.0));
	}
}// a constructor

EunetTerminals::~EunetTerminals() {
	// TODO !CodeTemplates.destructorstub.tododesc!
}

ns3::Ptr<EunetTerminal> EunetTerminals::getEunetTerminal(
		const int i_eunet_terminal) {
	auto ptr =
			this->terminals.Get(i_eunet_terminal)->GetObject<EunetTerminal> ();
	NS_ASSERT(ptr->GetNDevices()==1);
	return ptr;
}

ns3::NetDeviceContainer EunetTerminals::getDevicesAll() {
	NS_ASSERT_MSG(false, "a");
	ns3::NetDeviceContainer net_device_container;
	for (unsigned i = 0; i < this->terminals.GetN(); ++i) {
		auto ptr_eunet_terminal = getEunetTerminal(i);
		NS_ASSERT(ptr_eunet_terminal->GetNDevices()==1);
		auto ptr_net_device = ptr_eunet_terminal->GetDevice(0);
		net_device_container.Add(ptr_net_device);
	}//for
	return net_device_container;
}//getDevicesAll

void EunetTerminals::logTotalRx(ns3::LogLevel log_level) {
	for (auto i = this->terminals.Begin(); i != this->terminals.End(); ++i) {
		(**i).GetObject<EunetTerminal> ()-> logTotalRx(log_level);
	}
}
