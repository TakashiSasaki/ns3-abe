#ifndef SIMPLEAP_H_
#define SIMPLEAP_H_

#include "ns3/ssid.h"
#include "ns3/vector.h"
#include "SimpleSwitch.h"
#include "WifiBase.h"
#include "MobilityBase.h"
#include "init.h"

class SimpleAp: public SimpleSwitch, public WifiBase, MobilityBase {
	typedef SimpleSwitch Base;
public:
	static ns3::TypeId GetTypeId(void);
	SimpleAp();
	SimpleAp(ns3::Ssid ssid, ns3::Vector position);
	virtual ~SimpleAp() {
	}
	;
DECLARE_DIDDNCC
};//SimpleAp

#endif /* SIMPLEAP_H_ */
