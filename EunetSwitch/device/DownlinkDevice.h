#ifndef DOWNLINKNETDEVICE_H_
#define DOWNLINKNETDEVICE_H_
#include "ns3/csma-net-device.h"
#include "CsmaDevice.h"

class DownlinkDevice: public CsmaDevice {
public:
	static ns3::TypeId GetTypeId(void);
	DownlinkDevice();
	virtual ~DownlinkDevice();
};

#endif /* DOWNLINKNETDEVICE_H_ */
