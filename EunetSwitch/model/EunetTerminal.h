#ifndef EUNETTERMINAL_H_
#define EUNETTERMINAL_H_

#include "ns3/node.h"
#include "ns3/application-container.h"
#include "ns3/nstime.h"
#include "OnOffNode.h"

class EunetTerminal: public OnOffNode {
public:
	static ns3::TypeId GetTypeId(void);
	EunetTerminal();
	virtual ~EunetTerminal() {
	}
	;
private:
	bool isNotifyConstructionCompletedCalled;
	bool isDoInitializeCalled;
	bool isDoDisposeCalled;
protected:
	virtual void DoInitialize();
	virtual void NotifyConstructionCompleted();
	virtual void DoDispose();
};//EunetTerminal

#endif /* EUNETTERMINAL_H_ */
