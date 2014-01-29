#ifndef CSMANETDEVICE_H_
#define CSMANETDEVICE_H_
#include "ns3/csma-net-device.h"
#include "AddressGetterMixin.h"

class CsmaDevice: public ns3::CsmaNetDevice, public AddressGetterMixin {
	ns3::DataRate uplinkChannelDataRate;
	ns3::Time uplinkChannelDelay;
public:
	static ns3::TypeId GetTypeId(void);
	CsmaDevice();
	virtual ~CsmaDevice();
	void joinTo(ns3::Ptr<CsmaDevice>);
	void enablePcap(const bool promiscuous = false);
	virtual int getInt(const int);
	virtual ns3::Ptr<ns3::NetDevice> getNetDevice();
};

#endif
