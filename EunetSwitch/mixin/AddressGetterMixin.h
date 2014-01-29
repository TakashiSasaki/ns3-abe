#ifndef ADDRESSGETTERMIXIN_H_
#define ADDRESSGETTERMIXIN_H_
#include "ns3/net-device.h"
#include "ns3/csma-net-device.h"

class AddressGetterMixin {
public:
	AddressGetterMixin();
	virtual ~AddressGetterMixin();
	ns3::Ipv4Address getAddress();
	virtual ns3::Ptr<ns3::NetDevice> getNetDevice() = 0;
	virtual int getInt(const int);
};

#endif /* ADDRESSGETTERMIXIN_H_ */
