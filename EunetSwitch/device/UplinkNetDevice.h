#ifndef UPLINKNETDEVICE_H_
#define UPLINKNETDEVICE_H_
#include "ns3/csma-net-device.h"

class UplinkNetDevice: public ns3::CsmaNetDevice {
	ns3::DataRate uplinkChannelDataRate;
	ns3::Time uplinkChannelDelay;
public:
	static ns3::TypeId GetTypeId(void);
	UplinkNetDevice();
	virtual ~UplinkNetDevice();
};

#endif /* UPLINKNETDEVICE_H_ */
