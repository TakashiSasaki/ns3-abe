#define NS3_LOG_ENABLE 1
#include "ns3/log.h"
#include "ns3/csma-helper.h"
#include "ns3/ipv4-address-helper.h"
#include "ns3/internet-stack-helper.h"
NS_LOG_COMPONENT_DEFINE("EunetTerminals");
#include "EunetTerminal.h"
#include "EunetTerminals.h"

EunetTerminals::EunetTerminals(const int n_terminals) {
	for (int i = 0; i < n_terminals; ++i) {
		ns3::Ptr<ns3::Node> ptr_eunet_terminal(
				ns3::CreateObject<EunetTerminal>());
		ptr_eunet_terminal->GetObject<EunetTerminal> ()->startOnOffApplication(
				ns3::Seconds(0.0));
		ptr_eunet_terminal->GetObject<EunetTerminal> ()->stopOnOffApplication(
				ns3::Seconds(10.0));
		this->terminals.Add(ptr_eunet_terminal);
	}//for
	ns3::CsmaHelper csma_helper;
	csma_helper.Install(this->terminals);
	ns3::InternetStackHelper internet_stack_helper;
	internet_stack_helper.Install(this->terminals);
	ns3::Ipv4AddressHelper ipv4_address_helper;
	ipv4_address_helper.Assign(this->getDevicesAll());
}// a constructor

EunetTerminals::~EunetTerminals() {
	// TODO !CodeTemplates.destructorstub.tododesc!
}

ns3::Ptr<EunetTerminal> EunetTerminals::getEunetTerminal(
		const int i_eunet_terminal) {
	return this->terminals.Get(i_eunet_terminal)->GetObject<EunetTerminal> ();
}

ns3::NetDeviceContainer EunetTerminals::getDevicesAll() {
	ns3::NetDeviceContainer net_device_container;
	for (unsigned i = 0; i < this->terminals.GetN(); ++i) {
		net_device_container.Add(this->terminals.Get(i)->GetDevice(0));
	}//for
	return net_device_container;
}//getDevicesAll

