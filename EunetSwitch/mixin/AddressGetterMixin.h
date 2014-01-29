#ifndef ADDRESSGETTERMIXIN_H_
#define ADDRESSGETTERMIXIN_H_
#include "ns3/net-device.h"
#include "ns3/csma-net-device.h"

class AddressGetterMixin {
public:
	virtual int getInt(const int);
	AddressGetterMixin();
	virtual ~AddressGetterMixin();
	ns3::Ipv4Address getAddress();
};

#endif /* ADDRESSGETTERMIXIN_H_ */
