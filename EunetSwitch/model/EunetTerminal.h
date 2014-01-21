#ifndef EUNETTERMINAL_H_
#define EUNETTERMINAL_H_

#include "ns3/node.h"
#include "ns3/application-container.h"
#include "ns3/nstime.h"
#include "ns3/ipv4-static-routing.h"
#include "OnOffNode.h"

class EunetTerminal: public OnOffNode {
	ns3::Ipv4Address defaultGateway;
	ns3::Ptr<ns3::Ipv4StaticRouting> ipv4StaticRouting;
public:
	static ns3::TypeId GetTypeId(void);
	EunetTerminal();
	virtual ~EunetTerminal();
	void setDefaultRoute(ns3::Ipv4Address next_hop);

DECLARE_DIDDNCC
};//EunetTerminal

#endif /* EUNETTERMINAL_H_ */
