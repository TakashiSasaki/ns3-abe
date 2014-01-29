#ifndef DEVICEGETTERMIXIN_H_
#define DEVICEGETTERMIXIN_H_
#define NS3_ASSERT_ENABLE 1
#include "ns3/assert.h"
#include "ns3/ptr.h"
#include "ns3/node.h"
#include "ns3/ipv4.h"

class DeviceGetterMixin {
public:
	DeviceGetterMixin();
	virtual ~DeviceGetterMixin();
	template<class T>
	ns3::Ptr<T> getDevice(const unsigned i_port);
	template<class DeviceT>
	ns3::Ptr<DeviceT> getDevice(ns3::Ipv4Address ipv4_address);
	virtual ns3::Ptr<ns3::Node> getNode() = 0;
	virtual int getInt();
};

template<class T>
ns3::Ptr<T> DeviceGetterMixin::getDevice(const unsigned i_port) {
	//NS_ASSERT(this->countCsmaNetDevices()==1);
	unsigned j = 0;
	bool has_device_T = false;
	for (unsigned i = 0; i < getNode()->GetNDevices(); ++i) {
		//NS_LOG(log_level, this->GetDevice(i)->GetTypeId() << ", " << this->GetDevice(i)->GetInstanceTypeId());
		if (getNode()->GetDevice(i)->GetInstanceTypeId() == T::GetTypeId()) {
			has_device_T = true;
			if (j == i_port) {
				return getNode()->GetDevice(i)->GetObject<T> (T::GetTypeId());

			}//if
			++j;
		}//if
	}//for
	if (has_device_T) {
		NS_FATAL_ERROR("only " << j << " " << T::GetTypeId() << "ports exist.");
	}
	NS_FATAL_ERROR("node " << getNode()->GetId() << " has no " << T::GetTypeId()
			<< ".");
}

template<class DeviceT>
ns3::Ptr<DeviceT> DeviceGetterMixin::getDevice(ns3::Ipv4Address ipv4_address) {
	auto ipv4 = getNode()->GetObject<ns3::Ipv4> ();
	NS_ASSERT(ipv4 != NULL);
	int32_t i_interface = ipv4->GetInterfaceForAddress(ipv4_address);
	auto device = ipv4->GetNetDevice(i_interface);
	NS_ASSERT(device != NULL);
	auto device_t = device->GetObject<DeviceT> ();
	NS_ASSERT(device_t != NULL);
	return device_t;
}

#endif /* DEVICEGETTERMIXIN_H_ */
