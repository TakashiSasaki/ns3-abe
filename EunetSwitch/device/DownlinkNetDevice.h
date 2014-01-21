#ifndef DOWNLINKNETDEVICE_H_
#define DOWNLINKNETDEVICE_H_
#include "ns3/csma-net-device.h"

class DownlinkNetDevice: public CsmaNetDevice {
public:
	static ns3::TypeId GetTypeId(void);
	DownlinkNetDevice();
	virtual ~DownlinkNetDevice();
};

#endif /* DOWNLINKNETDEVICE_H_ */
