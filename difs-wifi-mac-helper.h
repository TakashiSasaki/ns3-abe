/*
 * difs-wifi-mac-helper.h
 *
 *  Created on: 2013/10/09
 *      Author: sasaki
 */

#ifndef DIFS_WIFI_MAC_HELPER_H_
#define DIFS_WIFI_MAC_HELPER_H_

#include "ns3/nqos-wifi-mac-helper.h"
#include "ns3/boolean.h"
#include "difs-wifi-mac.h"

class DifsWifiMacHelper: public ns3::NqosWifiMacHelper {
	uint32_t aifsn;
	uint32_t cwmin;
	uint32_t cwmax;
	ns3::ObjectFactory objectFactory;


	static DifsWifiMacHelper Default(void);

public:
	DifsWifiMacHelper(uint32_t aifsn = 2, uint32_t cwmin = 31, uint32_t cwmax =
			1023) :
		aifsn(aifsn), cwmin(cwmin), cwmax(cwmax) {
		objectFactory.SetTypeId("DifsWifiMac");
		objectFactory.Set("QosSupported", ns3::BooleanValue(false));
	}// constructor

	virtual ns3::Ptr<DifsWifiMac> Create(void) {
		ns3::Ptr<DifsWifiMac> ptr_difs_wifi_mac = objectFactory.Create<DifsWifiMac> ();
		return ptr_difs_wifi_mac;
	}// Create

	virtual ~DifsWifiMacHelper() {
	}// destructor
};//DifsWifiMacHelper

#endif /* DIFS_WIFI_MAC_HELPER_H_ */
