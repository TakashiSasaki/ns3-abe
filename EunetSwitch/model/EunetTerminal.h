#ifndef EUNETTERMINAL_H_
#define EUNETTERMINAL_H_

#include "ns3/node.h"
#include "ns3/application-container.h"
#include "ns3/nstime.h"
#include "OnOffNode.h"

class EunetTerminal: public OnOffNode {
	typedef OnOffNode Base;
public:
	static ns3::TypeId GetTypeId(void);
	EunetTerminal();
	virtual ~EunetTerminal();
protected:
	virtual void DoInitialize();
	virtual void NotifyConstructionCompleted();
};//EunetTerminal

#endif /* EUNETTERMINAL_H_ */
