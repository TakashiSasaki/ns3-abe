/*
 * Ipv4NodeContainer.h
 *
 *  Created on: 2013/10/29
 *      Author: sasaki
 */

#ifndef IPV4NODECONTAINER_H_
#define IPV4NODECONTAINER_H_

#include "ConstantMobilityNodeContainer.h"

namespace abe {

class Ipv4NodeContainer: public abe::ConstantMobilityNodeContainer {
public:
	Ipv4NodeContainer();
	virtual ~Ipv4NodeContainer();
};

}

#endif /* IPV4NODECONTAINER_H_ */
