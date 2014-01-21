#ifndef EUNETMOBILE_H_
#define EUNETMOBILE_H_

#include "ns3/node.h"
#include "ns3/application-container.h"
#include "ns3/nstime.h"
#include "WifiBase.h"
#include "MobilityBase.h"
#include "OnOffNode.h"

class EunetMobile: public OnOffNode/*, public MobilityBase, public WifiBase*/{
	std::string phyMode;
	double rss;
	ns3::Vector position;
	std::string wifiMacType;
public:
	static ns3::TypeId GetTypeId(void);
	EunetMobile();
	virtual ~EunetMobile();
	void joinTo(ns3::Ptr<EunetMobile>);
	void setPosition(ns3::Vector);
DECLARE_DIDDNCC
};//EunetMobile

#endif /* EUNETMOBILE_H_ */
