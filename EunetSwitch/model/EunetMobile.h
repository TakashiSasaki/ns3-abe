#ifndef EUNETMOBILE_H_
#define EUNETMOBILE_H_

#include "ns3/node.h"
#include "ns3/application-container.h"
#include "ns3/nstime.h"
#include "WifiBase.h"
#include "MobilityBase.h"
#include "OnOffNode.h"

class EunetMobile: public OnOffNode, public MobilityBase, public WifiBase {
public:
	static ns3::TypeId GetTypeId(void);
	EunetMobile();
	virtual ~EunetMobile() {
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
};//EunetMobile

#endif /* EUNETMOBILE_H_ */
