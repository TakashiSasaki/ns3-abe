/*
 * Ipv4NodeContainer.h
 *
 *  Created on: 2013/10/29
 *      Author: sasaki
 */

#ifndef IPV4NODECONTAINER_H_
#define IPV4NODECONTAINER_H_

#include "ns3/address.h"
#include "ns3/ipv4-l3-protocol.h"
#include "WifiNodeContainer.h"

namespace abe {

class Ipv4NodeContainer: public abe::WifiNodeContainer {
	uint32_t packetSize;
public:
	Ipv4NodeContainer(const uint32_t n_nodes, const int packetSize = 500);
	virtual ~Ipv4NodeContainer();
	void scheduleSendPacket(const ns3::Time& t, const int i_source_node, const int i_destination_node);
private:
	ns3::Address getAddress(const int i_node);
	ns3::Ptr<ns3::Ipv4L3Protocol> getIpv4L3Protocol(const int i_node) const;
	ns3::Ptr<ns3::Socket> getIpv4RawSocket(const int i_node);
	void receiveCallback(ns3::Ptr<ns3::Socket> p_socket);
	void sendPacket(const ns3::Ptr<ns3::Socket> p_socket,
			const ns3::Address& destination_address);
};//Ipv4NodeContainer

}//abe

#endif /* IPV4NODECONTAINER_H_ */
