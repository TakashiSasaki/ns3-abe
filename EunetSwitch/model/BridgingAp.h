#ifndef BRIDGINGAP_H_
#define BRIDGINGAP_H_

#include "SimpleAp.h"

class BridgingAp: public SimpleAp {
public:
	static ns3::TypeId GetTypeId(void);
	BridgingAp();
	virtual ~BridgingAp(){};
DECLARE_DIDDNCC;
};

#endif /* BRIDGINGAP_H_ */
