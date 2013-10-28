#ifndef CONSTANTMOBILITYNODECONTAINER_H_
#define CONSTANTMOBILITYNODECONTAINER_H_
#include "ns3/node-container.h"
namespace abe {
class ConstantMobilityNodeContainer: public ns3::NodeContainer {
public:
	ConstantMobilityNodeContainer(const int n_nodes = 4);
	virtual ~ConstantMobilityNodeContainer();
};//ConstantMobilityNodeContainer
}//abe
#endif /* CONSTANTMOBILITYNODECONTAINER_H_ */
