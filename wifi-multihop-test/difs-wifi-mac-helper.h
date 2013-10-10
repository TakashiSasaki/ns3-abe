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

namespace abe{
class DifsWifiMacHelper: public ns3::NqosWifiMacHelper {
	uint32_t aifsn;
	uint32_t cwmin;
	uint32_t cwmax;
	ns3::ObjectFactory objectFactory;


public:
	static DifsWifiMacHelper Default(void){
  		DifsWifiMacHelper difs_wifi_mac_helper;
		difs_wifi_mac_helper.SetType ("abe::DifsWifiMac");
		//difs_wifi_mac_helper.SetType ("abe::DifsWifiMac";
                //		"Aifsn", ns3::UintegerValue (2),
		//		"cwmin", ns3::UintegerValue(31),
		//		"cwmax", ns3::UintegerValue(1023));

        	return difs_wifi_mac_helper;
	}

	DifsWifiMacHelper(uint32_t aifsn = 2, uint32_t cwmin = 31, uint32_t cwmax =
			1023) :
		aifsn(aifsn), cwmin(cwmin), cwmax(cwmax) {
		objectFactory.SetTypeId("abe::DifsWifiMac");
		objectFactory.Set("QosSupported", ns3::BooleanValue(false));
	}// constructor

	virtual ns3::Ptr<DifsWifiMac> Create(void) {
		ns3::Ptr<DifsWifiMac> ptr_difs_wifi_mac = objectFactory.Create<DifsWifiMac> ();
		return ptr_difs_wifi_mac;
	}// Create

	virtual ~DifsWifiMacHelper() {
	}// destructor
};//DifsWifiMacHelper
};//abe
#endif /* DIFS_WIFI_MAC_HELPER_H_ */
