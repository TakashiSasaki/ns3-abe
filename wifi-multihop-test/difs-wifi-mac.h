/*
 * difs-wifi-mac.h
 *
 *  Created on: 2013/10/09
 *      Author: sasaki
 */

#ifndef DIFS_WIFI_MAC_H_
#define DIFS_WIFI_MAC_H_

#include "ns3/wifi-mac.h"
#include "ns3/adhoc-wifi-mac.h"
#include "ns3/regular-wifi-mac.h"
#include "ns3/qos-utils.h"
#include "ns3/wifi-phy-standard.h"
namespace abe{
class DifsWifiMac: public ns3::AdhocWifiMac {
	ns3::AdhocWifiMac* pAdhocWifiMac;
	ns3::RegularWifiMac* pRegularWifiMac;
	ns3::WifiMac* pWifiMac;
	uint32_t aifsn;
	uint32_t cwmin;
	uint32_t cwmax;

public:
	DifsWifiMac(uint32_t aifsn = 2, uint32_t cwmin = 31, uint32_t cwmax = 1023);//default value is for 802.11b standard
	virtual ~DifsWifiMac();
	static ns3::TypeId GetTypeId(void);

protected:
	virtual void FinishConfigureStandard(enum ns3::WifiPhyStandard standard);

};//DifsWifiMac
};//abe

#endif /* DIFS_WIFI_MAC_H_ */
