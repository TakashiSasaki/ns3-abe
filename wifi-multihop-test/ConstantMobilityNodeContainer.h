#ifndef CONSTANTMOBILITYNODECONTAINER_H_
#define CONSTANTMOBILITYNODECONTAINER_H_
#include "ns3/node-container.h"
#include "ns3/net-device-container.h"
namespace abe {
class ConstantMobilityNodeContainer: public ns3::NodeContainer {
public:
	ConstantMobilityNodeContainer(const int n_nodes);
	ns3::NetDeviceContainer getNetDeviceContainer();
	ns3::Ptr<ns3::NetDevice> getNetDevice(const int i_node);
	virtual ~ConstantMobilityNodeContainer();
};//ConstantMobilityNodeContainer
}//abe
#endif /* CONSTANTMOBILITYNODECONTAINER_H_ */
