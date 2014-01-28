#ifndef DEVICEGETTERMIXIN_H_
#define DEVICEGETTERMIXIN_H_
#include "ns3/ptr.h"
#include "ns3/node.h"

class DeviceGetterMixin {
public:
	DeviceGetterMixin();
	virtual ~DeviceGetterMixin();
	template<class T>
	ns3::Ptr<T> getNetDevice(const unsigned i_port);
	virtual ns3::Ptr<ns3::Node> getThis();
};

template<class T>
ns3::Ptr<T> DeviceGetterMixin::getNetDevice(const unsigned i_port) {
	//NS_ASSERT(this->countCsmaNetDevices()==1);
	unsigned j = 0;
	bool has_device_T = false;
	for (unsigned i = 0; i < getThis()->GetNDevices(); ++i) {
		//NS_LOG(log_level, this->GetDevice(i)->GetTypeId() << ", " << this->GetDevice(i)->GetInstanceTypeId());
		if (getThis()->GetDevice(i)->GetInstanceTypeId() == T::GetTypeId()) {
			has_device_T = true;
			if (j == i_port) {
				return getThis()->GetDevice(i)->GetObject<T> (T::GetTypeId());

			}//if
			++j;
		}//if
	}//for
	if (has_device_T) {
		NS_FATAL_ERROR("only " << j << " " << T::GetTypeId() << "ports exist.");
	}
	NS_FATAL_ERROR("node " << getThis()->GetId() << " has no " << T::GetTypeId()
			<< ".");
}

#endif /* DEVICEGETTERMIXIN_H_ */
