#ifndef SIMPLEAP_H_
#define SIMPLEAP_H_

#include "ns3/ssid.h"
#include "ns3/vector.h"
#include "SimpleSwitch.h"

class SimpleAp: public SimpleSwitch {
	typedef SimpleSwitch Base;
	ns3::Vector position;
	ns3::Ssid ssid;
public:
	static ns3::TypeId GetTypeId(void);
	SimpleAp();
	SimpleAp(ns3::Ssid ssid, ns3::Vector position);
	virtual ~SimpleAp();
	void setPosition(const ns3::Vector& position);
	void setSsid(const ns3::Ssid& ssid);
protected:
	virtual void DoInitialize();
	virtual void NotifyConstructionCompleted();
};

#endif /* SIMPLEAP_H_ */
