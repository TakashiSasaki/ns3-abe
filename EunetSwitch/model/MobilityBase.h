#ifndef CONSTANTMOBILITY_H_
#define CONSTANTMOBILITY_H_
#include "ns3/node.h"
#include "ns3/vector.h"

class MobilityBase {
	//ns3::Node* pNode;
	ns3::Ptr<ns3::Node> ptrNode;
	ns3::Vector position;
public:
	void setPosition(const ns3::Vector& position);
protected:
	MobilityBase(ns3::Node* p_node);
	virtual ~MobilityBase();
	void DoInitialize();
};

#endif /* CONSTANTMOBILITY_H_ */
