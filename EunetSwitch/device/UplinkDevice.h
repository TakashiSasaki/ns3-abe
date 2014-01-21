#ifndef UPLINKNETDEVICE_H_
#define UPLINKNETDEVICE_H_
#include "ns3/data-rate.h"
#include "CsmaDevice.h"

class UplinkDevice: public CsmaDevice {
	ns3::DataRate uplinkChannelDataRate;
	ns3::Time uplinkChannelDelay;
public:
	static ns3::TypeId GetTypeId(void);
	UplinkDevice();
	virtual ~UplinkDevice();
};

#endif /* UPLINKNETDEVICE_H_ */
