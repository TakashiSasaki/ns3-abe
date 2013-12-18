#ifndef SIMPLEAP_H_
#define SIMPLEAP_H_

#include "SimpleSwitch.h"

class SimpleAp: public SimpleSwitch {
	typedef SimpleSwitch Base;
public:
	static ns3::TypeId GetTypeId(void);
	SimpleAp();
	virtual ~SimpleAp();
protected:
	virtual void DoInitialize();
	virtual void NotifyConstructionCompleted();
};

#endif /* SIMPLEAP_H_ */
