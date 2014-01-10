#ifndef BRIDGINGAP_H_
#define BRIDGINGAP_H_

#include "SimpleAp.h"

class BridgingAp: public SimpleAp {
	typedef SimpleAp Base;
public:
	static ns3::TypeId GetTypeId(void);
	BridgingAp();
	virtual ~BridgingAp(){};
protected:
	virtual void DoInitialize();
	virtual void NotifyConstructionCompleted();
	virtual void DoDispose();
};

#endif /* BRIDGINGAP_H_ */
