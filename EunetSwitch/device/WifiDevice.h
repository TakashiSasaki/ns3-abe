#ifndef WIFIDEVICE_H_
#define WIFIDEVICE_H_
#include "ns3/wifi-net-device.h"

class WifiDevice: public ns3::WifiNetDevice {
public:
	WifiDevice();
	virtual ~WifiDevice();
	void enablePcap(const bool promiscuous = false);
};

#endif /* WIFIDEVICE_H_ */
