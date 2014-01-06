#include <memory>
#include <sstream>
#define NS3_LOG_ENABLE 1
#include "ns3/log.h"
NS_LOG_COMPONENT_DEFINE("SimpleRouter");
#define NS3_ASSERT_ENABLE 1
#include "ns3/assert.h"
#include "ns3/type-id.h"
#include "ns3/bridge-helper.h"
#include "ns3/dce-module.h"
#include "ns3/dce-application-helper.h"
#include "ns3/quagga-helper.h"
#include "ns3/names.h"
#include "SimpleRouter.h"

NS_OBJECT_ENSURE_REGISTERED( SimpleRouter);

const ns3::DataRate SimpleRouter::defaultlinkDataRate("1000000000bps");
const ns3::TimeValue SimpleRouter::defaultlinkDelay(ns3::MilliSeconds(1));

ns3::TypeId SimpleRouter::GetTypeId(void) {
	static ns3::TypeId type_id =
			ns3::TypeId("SimpleRouter").SetParent<Base> ().AddConstructor<
					SimpleRouter> ();
	return type_id;
}//GetTypeId


SimpleRouter::SimpleRouter(const unsigned n_ports) :
	CsmaChannelNode(n_ports, defaultlinkDataRate, defaultlinkDelay),
			nlinkPorts(n_ports) {
	this->setlinkDataRate(defaultlinkDataRate);
	this->setlinkDelay(defaultlinkDelay);
	NS_LOG_INFO("constructing SimpleSwitch");
	for (unsigned i = 0; i < nlinkPorts; ++i) {
		NS_LOG_INFO("investigating port " << i);
		NS_ASSERT(!this->isConnectedToSimpleRouter(i));
	}
}

SimpleRouter::~SimpleRouter() {
}

void SimpleRouter::setlinkDataRate(ns3::DataRateValue data_rate) {
	for (unsigned i = 0; i < nlinkPorts; ++i) {
		this->setDataRate(data_rate, i);
	}
}

void SimpleRouter::setlinkDelay(ns3::TimeValue delay) {
	for (unsigned i = 0; i < nlinkPorts; ++i) {
		this->setDelay(delay, i);
	}
}

ns3::Ptr<ns3::CsmaNetDevice> SimpleRouter::getLinkPort(const unsigned i_port) {
	NS_ASSERT(i_port < nlinkPorts);
	auto p = this->getCsmaNetDevice(i_port);
	return p;
}//getlinkPort

void SimpleRouter::connectTo(const unsigned i_link_port,
		ns3::Ptr<SimpleRouter> connect_router,
		const unsigned connect_i_link_port) {
	this->bring(i_link_port, connect_router, connect_i_link_port);
	NS_ASSERT(this->isConnectedToSimpleRouter(i_link_port));
	NS_ASSERT(connect_router->isConnectedToSimpleRouter(connect_i_link_port));
}//connectTo

void SimpleRouter::connectTo(std::string connect_router_name) {
	ns3::Ptr<ns3::Node> ptr_node = ns3::Names::Find<ns3::Node>(
			connect_router_name);
	auto ptr_connect_router = ptr_node->GetObject<SimpleRouter> ();
	const unsigned unused_link_port = this->getUnusedlinkPort();
	const unsigned connect_unused_link_port =
			ptr_connect_router->getUnusedlinkPort();
	this->connectTo(unused_link_port, ptr_connect_router,
			connect_unused_link_port);
}//connectTo

unsigned SimpleRouter::getUnusedlinkPort() {
	for (unsigned i = 0; i < this->nlinkPorts; ++i) {
		if (!this->isConnectedToSimpleRouter(i)) {
			return i;
		}//if
	}//for
	NS_FATAL_ERROR("no unused downlink port");
}

void SimpleRouter::DoInitialize() {
	NS_LOG_INFO("just calling up");
	Base::DoInitialize();
}

void SimpleRouter::NotifyConstructionCompleted() {
	ns3::Ptr<SimpleRouter> ptr_this(this, true);
	const auto n_devices_before = ptr_this->GetNDevices();

	ns3::InternetStackHelper stack; // IPv4 is required for GlobalRouteMan
	ns3::Ipv4DceRoutingHelper ipv4RoutingHelper;
	stack.SetRoutingHelper(ipv4RoutingHelper);
	stack.Install(ptr_this);

	const auto n_devices_after = ptr_this->GetNDevices();
	NS_ASSERT(n_devices_before +1 == n_devices_after);
	NS_ASSERT(this->GetDevice(n_devices_before)->GetObject<ns3::LoopbackNetDevice>(ns3::LoopbackNetDevice::GetTypeId()));

	//assignIpAddressToDevice();
	//Ipv4GlobalRoutingHelper::PopulateRoutingTables();

	ns3::DceManagerHelper processManager;
	processManager.SetNetworkStack("ns3::Ns3SocketFdFactory");
	processManager.Install(ns3::NodeContainer(ptr_this));

	ns3::QuaggaHelper quagga;
	auto all_networks = this->getAllNetworks();
	for (auto i = all_networks->begin(); i != all_networks->end(); ++i) {
		quagga.EnableOspf(ns3::NodeContainer(ptr_this), (*i).c_str());
	}//for
	quagga.EnableOspfDebug(ns3::NodeContainer(ptr_this));
	quagga.EnableZebraDebug(ns3::NodeContainer(ptr_this));
	quagga.Install(ns3::NodeContainer(ptr_this));

	NS_LOG_INFO("routing all devices");
	Base::NotifyConstructionCompleted();
}//NotifyConstructionCompleted

bool SimpleRouter::isConnectedToSimpleRouter(const unsigned i_port) {
	ns3::Ptr<ns3::CsmaChannel> ptr_csma_channel = this->getCsmaChannel(i_port);
	NS_LOG_INFO("SimpleRouter "<< this->GetId() << " port " << i_port
			<< " channel is attached to " << ptr_csma_channel->GetNDevices()<< " devices ");
	for (unsigned i = 0; i < ptr_csma_channel->GetNDevices(); ++i) {
		NS_LOG_INFO("inspecting port " << i);
		ns3::Ptr<ns3::NetDevice> ptr_net_device =
				ptr_csma_channel->GetDevice(i);
		NS_LOG_INFO("expecting NetDevice .. " << ptr_net_device->GetTypeId());
		ns3::Ptr<ns3::Node> ptr_node = ptr_net_device->GetNode();
		NS_LOG_INFO("expecting Node .. " << ptr_node->GetTypeId());
		if (ptr_node->GetId() == this->GetId()) {
			continue;
		}//if
		ns3::Ptr<SimpleRouter> ptr_simple_router = ptr_node->GetObject<
				SimpleRouter> ();
		NS_LOG_INFO("expecting SimpleRouter .. " << ptr_simple_router->GetTypeId());
		if (ptr_simple_router) {
			return true;
		}//if
	}//for
	return false;
}//isConnectedToSimpleRouter

void SimpleRouter::assignIpAddressToDevice(const unsigned i_device,
		ns3::Ipv4Address ipv4_address, ns3::Ipv4Mask ipv4_mask) {
	ns3::Ptr<SimpleRouter> ptr_this(this, true);
	auto ptr_ipv4 = ptr_this->GetObject<ns3::Ipv4> ();
	const auto ptr_net_device = this->GetDevice(i_device);
	const int32_t n_interface = ptr_ipv4->GetInterfaceForDevice(ptr_net_device);
	NS_ASSERT(n_interface >= 1);
	const auto mask = ipv4_mask.Get();
	ns3::Ipv4InterfaceAddress ipv4_interface_address(ipv4_address, mask);
	ptr_ipv4->AddAddress(n_interface, ipv4_interface_address);
	ptr_ipv4->SetMetric(n_interface, 1);
	ptr_ipv4->SetUp(n_interface);
}//assignIpAddressToDevice

std::unique_ptr<std::vector<std::string> > SimpleRouter::getAllNetworks() {
	std::unique_ptr<std::vector<std::string> > p_networks(new std::vector<
			std::string>());
	ns3::Ptr<SimpleRouter> ptr_this(this, true);
	auto ptr_ipv4 = ptr_this->GetObject<ns3::Ipv4> ();
	for (unsigned i = 0; i < this->GetNDevices(); ++i) {
		auto p_net_device = this->GetDevice(i);
		auto p_loopback_device =
				p_net_device->GetObject<ns3::LoopbackNetDevice> ();
		if (p_loopback_device)
			continue;
		auto i_interface = ptr_ipv4->GetInterfaceForDevice(p_net_device);
		auto n_addresses = ptr_ipv4->GetNAddresses(i_interface);
		for (unsigned j = 0; n_addresses > j; ++j) {
			auto ipv4_interface_address = ptr_ipv4->GetAddress(i_interface, j);
			NS_LOG_INFO(ipv4_interface_address);
			auto ipv4_address = ipv4_interface_address.GetLocal();
			auto ipv4_mask = ipv4_interface_address.GetMask();
			ipv4_address.CombineMask(ipv4_mask);
			std::ostringstream oss;
			oss << ipv4_address;
			auto s = oss.str();
			NS_LOG_INFO("network address " << s);
			p_networks->push_back(s);
		}//for
	}//for
	return p_networks;
}