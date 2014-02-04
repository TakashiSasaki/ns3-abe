#ifndef WIFIDEVICE_H_
#define WIFIDEVICE_H_
#include "ns3/wifi-net-device.h"
#include "AddressGetterMixin.h"
#include "init.h"

class WifiDevice: public ns3::WifiNetDevice, public AddressGetterMixin {
	std::string phyMode;
	double rss;
	std::string wifiMacType;
	ns3::Ptr<ns3::WifiMac> createMac();
	ns3::Ptr<ns3::YansWifiChannel> createChannel();
	ns3::Ptr<ns3::WifiPhy> createPhy();
	ns3::Ptr<ns3::WifiRemoteStationManager> createRemoteStationManager();
	ns3::Ptr<ns3::ErrorRateModel> createErrorRateModel();
public:
	static ns3::TypeId GetTypeId(void);
	WifiDevice();
	virtual ~WifiDevice();
	void enablePcap(const bool promiscuous = false);
	virtual int getInt(const int);
	virtual ns3::Ptr<ns3::NetDevice> getNetDevice();
DECLARE_DIDDNCC
	;
};

#endif /* WIFIDEVICE_H_ */
