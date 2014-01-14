#ifndef WIFINODE_H_
#define WIFINODE_H_
#include "OnOffNode.h"

class WifiNode: public OnOffNode {
	typedef OnOffNode Base;
public:
	static ns3::TypeId GetTypeId(void);
	WifiNode();
	virtual ~WifiNode() {
	}
	;
DECLARE_DIDDNCC
};

#endif /* WIFONODE_H_ */
