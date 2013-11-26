#ifndef SIMPLESWITCH_H_
#define SIMPLESWITCH_H_
#include "CsmaChannelNode.h"

class SimpleSwitch: public CsmaChannelNode {
public:
	static ns3::TypeId GetTypeId(void);
	SimpleSwitch();
	virtual ~SimpleSwitch();
};

#endif /* SIMPLESWITCH_H_ */
