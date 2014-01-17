#ifndef DOWNLINKNETDEVICE_H_
#define DOWNLINKNETDEVICE_H_
#include "ns3/csma-net-device.h"

class DownlinkNetDevice : public ns3::CsmaNetDevice {
public:
	static ns3::TypeId GetTypeId(void);
	DownlinkNetDevice();
	virtual ~DownlinkNetDevice();
};

#endif /* DOWNLINKNETDEVICE_H_ */
