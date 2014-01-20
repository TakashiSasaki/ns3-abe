#ifndef INIT_H_
#define INIT_H_


#define DECLARE_DIDDNCC private: bool isNotifyConstructionCompletedCalled; bool isDoInitializeCalled;	bool isDoDisposeCalled;protected:	virtual void DoInitialize();	virtual void NotifyConstructionCompleted();	virtual void DoDispose();
#define INIT_DIDDNCC_FLAGS isNotifyConstructionCompletedCalled(false),isDoInitializeCalled(false), isDoDisposeCalled(false)
#define ASSERT_DI 	{NS_ASSERT(!this->isDoInitializeCalled); this->isDoInitializeCalled = true;}
#define ASSERT_DD    {NS_ASSERT(!this->isDoDisposeCalled);	this->isDoDisposeCalled = true; NS_ASSERT(this->isNotifyConstructionCompletedCalled); NS_ASSERT(this->isDoInitializeCalled);}
#define ASSERT_NCC   {NS_ASSERT(!this->isNotifyConstructionCompletedCalled);	this->isNotifyConstructionCompletedCalled = true; NS_ASSERT(!this->isDoInitializeCalled);}

#include "ns3/csma-net-device.h"
#include "ns3/ipv4.h"

inline unsigned getNAddresses(ns3::Ptr<ns3::CsmaNetDevice> csma_net_device) {
	auto node = csma_net_device->GetNode();
	ns3::Ptr<ns3::Ipv4> ipv4 = node->GetObject<ns3::Ipv4> ();
	auto i_interface = ipv4->GetInterfaceForDevice(csma_net_device);
	NS_ASSERT(i_interface != -1);
	auto n_addresses = ipv4->GetNAddresses(i_interface);
	return n_addresses;
}

#endif /* INIT_H_ */
