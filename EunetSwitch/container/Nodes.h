#ifndef NODES_H_
#define NODES_H_
#include "ns3/node-container.h"
class Nodes: public ns3::NodeContainer {
public:
	Nodes();
	virtual ~Nodes();
	template<class NodeT> ns3::Ptr<NodeT> get(const unsigned);
};

template<class NodeT> ns3::Ptr<NodeT> Nodes::get(const unsigned i_node) {
	unsigned counter = 0;
	for (unsigned i = 0; i < this->GetN(); ++i) {
		auto node = this->Get(i);
		if (node->GetInstanceTypeId() == NodeT::GetTypeId()) {
			if (i_node == counter) {
				return node->GetObject<NodeT> ();
			}//if
			counter++;
		}//if
	}//for
	NS_FATAL_ERROR("node " << NodeT::GetTypeId() << " " << i_node << " was not found.");
}

#endif /* NODES_H_ */
