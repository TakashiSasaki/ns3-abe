#ifndef CSMAINTERNETNODE_H_
#define CSMAINTERNETNODE_H_
#include "CsmaChannelNode.h"

class CsmaInternetNode: public CsmaChannelNode {
public:
	static ns3::TypeId GetTypeId(void);
	CsmaInternetNode(const int n_devices = 1);
	virtual ~CsmaInternetNode();
};

#endif /* CSMAINTERNETNODE_H_ */
