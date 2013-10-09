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

NS_LOG_COMPONENT_DEFINE("DifsWifiMac");


class DifsWifiMac: public ns3::AdhocWifiMac {
	ns3::AdhocWifiMac* pAdhocWifiMac;
	ns3::RegularWifiMac* pRegularWifiMac;
	ns3::WifiMac* pWifiMac;
	uint32_t aifsn;
	uint32_t cwmin;
	uint32_t cwmax;

public:
	DifsWifiMac(uint32_t aifsn = 2, uint32_t cwmin = 31, uint32_t cwmax = 1023) ://default value is for 802.11b standard
		AdhocWifiMac(), aifsn(aifsn), cwmin(cwmin), cwmax(cwmax) {
		NS_LOG_FUNCTION(this);
		pAdhocWifiMac = this;
		pRegularWifiMac = this;
		pWifiMac = this;
	}//constructor

	virtual ~DifsWifiMac() {
		NS_LOG_FUNCTION(this);
	}//destructor

	static ns3::TypeId GetTypeId(void) {
		static ns3::TypeId type_id = ns3::TypeId("DifsWifiMac").SetParent<
				AdhocWifiMac> ().AddConstructor<DifsWifiMac> ();
		return type_id;
	}//GetTypeId

protected:
	virtual void FinishConfigureStandard(enum ns3::WifiPhyStandard standard) {
		ns3::AdhocWifiMac::FinishConfigureStandard(standard);
		ns3::AdhocWifiMac::ConfigureDcf(ns3::AdhocWifiMac::m_dca, cwmin, cwmax,
				ns3::AC_BE_NQOS);
		ns3::AdhocWifiMac::m_dca->SetAifsn(aifsn);
	}//FinishConfigureStandard

};//DifsWifiMac

NS_OBJECT_ENSURE_REGISTERED(DifsWifiMac);

#endif /* DIFS_WIFI_MAC_H_ */
