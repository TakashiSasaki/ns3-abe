#define NS3_LOG_ENABLE 1
#include "ns3/log.h"
NS_LOG_COMPONENT_DEFINE("EunetTerminals");
#define NS3_ASSERT_ENABLE 1
#include "ns3/assert.h"
#include "ns3/csma-helper.h"
#include "ns3/ipv4-address-helper.h"
#include "ns3/internet-stack-helper.h"
#include "ns3/mobility-helper.h"
#include "ns3/csma-net-device.h"
#include "ns3/loopback-net-device.h"
#include "EunetTerminal.h"
#include "EunetTerminals.h"

EunetTerminals::EunetTerminals() {
#if 0
	for (unsigned i = 0; i < this->GetN(); ++i) {
		NS_LOG_INFO("getting source EunetTerminal");
		auto ptr_source = this->terminals.Get(i)->GetObject<EunetTerminal> ();
		NS_LOG_INFO("getting remote EunetTerminal");
		auto ptr_remote = this->terminals.Get(0)->GetObject<EunetTerminal> ();
		NS_LOG_INFO("setting remote EunetTerminal");
		ptr_source->setRemote(ptr_remote);
		ptr_source->startAt(ns3::Seconds(0.0));
		ptr_source->stopAt(ns3::Seconds(2.0));
	}
#endif
}// a constructor

EunetTerminals::~EunetTerminals() {
	// TODO !CodeTemplates.destructorstub.tododesc!
}

void EunetTerminals::initialize(const uint32_t n_terminals) {
	NS_LOG_INFO("constructing EunetTerminals with " << n_terminals << " terminals");
	ns3::ObjectFactory object_factory;
	object_factory.SetTypeId("EunetTerminal");
	for (unsigned i = 0; i < n_terminals; ++i) {
		NS_LOG_INFO("creating EunetTerminal node " << i);
		ns3::Ptr<EunetTerminal> ptr_eunet_terminal = object_factory.Create<
				EunetTerminal> ();
		ptr_eunet_terminal->Initialize();
		NS_LOG_INFO(ptr_eunet_terminal->GetNDevices() << " device(s)");
		//auto ptr_eunet_terminal = object_factory.Create<EunetTerminal> ();
		//ns3::Ptr<ns3::Node> ptr_eunet_terminal(
		//		ns3::CreateObject<EunetTerminal>());
		NS_ASSERT_MSG(ptr_eunet_terminal->GetNDevices()==2,
				"devices=" <<
				ptr_eunet_terminal->GetNDevices() << " csma=" <<
				ptr_eunet_terminal->getNDevices<ns3::CsmaNetDevice>() << " loopback="
				<< ptr_eunet_terminal->getNDevices<ns3::LoopbackNetDevice>());
		//ptr_eunet_terminal->assignAddress(ipv4_address_helper);
		this->Add(ptr_eunet_terminal);
	}//for
	NS_ASSERT(n_terminals == this->GetN());

#if 0
	ns3::MobilityHelper mobility_helper;
	mobility_helper.SetMobilityModel("ns3::ConstantPositionMobilityModel");
	mobility_helper.Install(*this);
#endif
}

void EunetTerminals::assignAddresses(const char* network_address,
		const char* netmask) {
	ns3::Ipv4Address ipv4_address(network_address);
	ns3::Ipv4Mask ipv4_mask(netmask);
	ns3::Ipv4AddressHelper ipv4_address_helper(ipv4_address, ipv4_mask);
	this->assignAddresses(ipv4_address_helper);
}//assignAddresses

void EunetTerminals::assignAddresses(
		ns3::Ipv4AddressHelper& ipv4_address_helper) {
	for (unsigned i = 0; i < this->GetN(); ++i) {
		NS_ASSERT(this->Get(i)-> GetNDevices()==2);
		auto ptr_csma_net_device = this->Get(i)->getNetDevice<CsmaDevice> (0);
		this->Get(i)->assignAddress(ptr_csma_net_device, ipv4_address_helper);
	}//for
}//assignAddresses

ns3::Ptr<EunetTerminal> EunetTerminals::Get(const int i_eunet_terminal) {
	auto ptr = ns3::NodeContainer::Get(i_eunet_terminal)->GetObject<
			EunetTerminal> ();
	NS_ASSERT(ptr != NULL);
	NS_ASSERT(ptr->GetInstanceTypeId() == EunetTerminal::GetTypeId());
	NS_ASSERT_MSG(ptr->GetNDevices()==2, ptr->GetNDevices());
	return ptr;
}

ns3::NetDeviceContainer EunetTerminals::getDevicesAll() {
	ns3::NetDeviceContainer net_device_container;
	for (unsigned i = 0; i < this->GetN(); ++i) {
		//auto ptr_eunet_terminal = getEunetTerminal(i);
		//NS_ASSERT(ptr_eunet_terminal->GetNDevices()==1);
		//auto ptr_net_device = ptr_eunet_terminal->GetDevice(0);
		net_device_container.Add(
				this->Get(i)->getNetDevice<ns3::CsmaNetDevice> (0));
	}//for
	return net_device_container;
}//getDevicesAll

unsigned EunetTerminals::getTotalRx() {
	unsigned count = 0;
	for (auto i = this->Begin(); i != this->End(); ++i) {
		auto total_rx = (*i)->GetObject<EunetTerminal> ()->getTotalRx();
		count += total_rx;
	}//for
	return count;
}//getTotalRx

void EunetTerminals::bringAtoB(const unsigned i_eunet_terminal_a,
		const unsigned i_eunet_terminal_b) {
	NS_ASSERT(i_eunet_terminal_a < this->GetN());
	NS_ASSERT(i_eunet_terminal_b < this->GetN());

	NS_LOG_INFO("getting terminal " << i_eunet_terminal_a << " of " << this->GetN());
	auto a = this->Get(i_eunet_terminal_a);
	NS_LOG_INFO("getting terminal " << i_eunet_terminal_b << " of " << this->GetN());
	auto b = this->Get(i_eunet_terminal_b);
	NS_LOG_INFO("bringing node " << a->GetId() << " into CSMA domain of node " << b->GetId());
	b->bring(a);
}

void EunetTerminals::setRemoteOfAtoB(const unsigned i_eunet_terminal_a,
		const unsigned i_eunet_terminal_b) {
	auto node_a = this->Get(i_eunet_terminal_a);
	NS_ASSERT(node_a != NULL);
	auto node_b = this->Get(i_eunet_terminal_b);
	NS_ASSERT(node_b != NULL);
	auto device_b = node_b->getNetDevice<CsmaDevice> (0);
	NS_ASSERT(device_b != NULL);
	auto ipv4_address = node_b->getAddress(device_b);
	NS_LOG_DEBUG("setting remote address " << ipv4_address << " to node " << node_a->GetId());
	node_a->setRemote(ipv4_address);
}
