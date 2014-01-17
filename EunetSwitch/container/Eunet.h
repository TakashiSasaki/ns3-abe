#ifndef EUNET_H_
#define EUNET_H_
#include <cmath>
#define NS3_ASSERT_ENABLE 1
#include "ns3/assert.h"
#include "ns3/node-container.h"
#include "Eunet.h"
#include "EunetSwitch.h"
#include "EunetRouter.h"

class Eunet: public ns3::NodeContainer {
public:
	Eunet();
	virtual ~Eunet();

	template<class SrcNodeT, class SrcDeviceT, class DstNodeT, class DstDeviceT>
	void connect(std::string src_name, std::string dst_name);

	template<class NodeT, class DeviceT>
	void enablePcap(const unsigned i_port);

	template<class NodeT, class DeviceT>
	void enableAsciiTrace(const unsigned i_port);
private:
};

template<class SrcNodeT, class SrcDeviceT, class DstNodeT, class DstDeviceT>
void Eunet::connect(std::string src_name, std::string dst_name) {
	NS_ASSERT((SrcNodeT::GetTypeId()==EunetSwitch::GetTypeId())
			|| (SrcNodeT::GetTypeId()==EunetRouter::GetTypeId()));
	ns3::Ptr<CsmaChannelNode> ptr_src = ns3::Names::Find<SrcNodeT>(src_name);
	if (ptr_src == NULL) {
		auto ptr_node = ns3::CreateObject<SrcNodeT>();
		NS_ASSERT(ptr_node != NULL);
		this->Add(ptr_node);
	}//if
	ns3::Ptr<CsmaChannelNode> ptr_dst = ns3::Names::Find<DstNodeT>(dst_name);
	if (ptr_dst == NULL) {
		auto ptr_node = ns3::CreateObject<DstNodeT>();
		NS_ASSERT(ptr_node != NULL);
		this->Add(ptr_node);
	}//if
}

#endif /* EUNET_H_ */
