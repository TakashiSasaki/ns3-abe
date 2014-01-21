#ifndef CSMANETDEVICE_H_
#define CSMANETDEVICE_H_
#include "ns3/csma-net-device.h"

class CsmaDevice: public ns3::CsmaNetDevice {
	ns3::DataRate uplinkChannelDataRate;
	ns3::Time uplinkChannelDelay;
public:
	static ns3::TypeId GetTypeId(void);
	CsmaDevice();
	virtual ~CsmaDevice();
	void joinTo(ns3::Ptr<CsmaDevice>);
};

#endif
