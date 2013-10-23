/*
 * EunetSwitch.h
 *
 *  Created on: 2013/10/22
 *      Author: w535070h
 */

#ifndef EUNETSWITCH_H_
#define EUNETSWITCH_H_
#include <cassert>
#include <stdexcept>
#include "ns3/node.h"
#include "ns3/csma-channel.h"

class EunetSwitch: public ns3::Node {

	std::vector<int> uplinkPortIndices;
	std::vector<int> downlinkPortIndices;
	ns3::NodeContainer ncTerminals;
	const int nDownlinkPorts;
	const int nDownlinkBps;
	const int nDownlinkDelayMilliseconds;
	const int nUplinkPorts;
	const int nUplinkBps;
	const int nUplinkDelayMilliseconds;
	ns3::CsmaHelper downlinkCsmaHelper;
	ns3::CsmaHelper uplinkCsmaHelper;
	ns3::CsmaHelper siblingCsmaHelper;

public:
	EunetSwitch(const int n_downlink_ports = 2, const int n_downlink_bps =
			1000000000, const int n_downlink_delay_milliseconds = 1,
			const int n_uplink_ports = 2, const int n_uplink_bps = 1000000000,
			const int n_uplink_delay_milliseconds = 1) :
		uplinkPortIndices(n_uplink_ports),
				downlinkPortIndices(n_downlink_ports), nDownlinkPorts(
						n_downlink_ports), nDownlinkBps(n_downlink_bps),
				nDownlinkDelayMilliseconds(n_downlink_delay_milliseconds),
				nUplinkPorts(n_uplink_ports), nUplinkBps(n_uplink_bps),
				nUplinkDelayMilliseconds(n_uplink_delay_milliseconds),
				downlinkCsmaHelper(), uplinkCsmaHelper() {
		this->downlinkCsmaHelper.SetChannelAttribute("DataRate",
				ns3::DataRateValue(this->nDownlinkBps));
		this->downlinkCsmaHelper.SetChannelAttribute("Delay", ns3::TimeValue(
				ns3::MilliSeconds(this->nDownlinkDelayMilliseconds)));
		this->uplinkCsmaHelper.SetChannelAttribute("DataRate",
				ns3::DataRateValue(this->nUplinkBps));
		this->uplinkCsmaHelper.SetChannelAttribute("Delay", ns3::TimeValue(
				ns3::MilliSeconds(this->nUplinkDelayMilliseconds)));
		this->ncTerminals.Create(n_downlink_ports);
		this->deployTerminals();
		ns3::InternetStackHelper internet_stack_helper;
		internet_stack_helper.Install(ncTerminals);
		//internet_stack_helper.Install(ncTerminals.getTerminals());
	}//a constructor

	ns3::Ptr<ns3::NetDevice> getUplinkPort(const int i_uplink_port) {
		return this->GetDevice(this->uplinkPortIndices[i_uplink_port]);
	}//getUplinkPort

	ns3::Ptr<ns3::NetDevice> getDownlinkPort(const int i_downlink_port) {
		return this->GetDevice(this->downlinkPortIndices[i_downlink_port]);
	}//getDownlinkPort

	ns3::NetDeviceContainer getUplinkDevices() {
		ns3::NetDeviceContainer ndc;
		for (int i = 0; i < this->nUplinkPorts; ++i) {
			ndc.Add(this->getUplinkPort(i));
		}//for
		return ndc;
	}//getUplinkDevices

	ns3::NetDeviceContainer getDownlinkDevices() {
		ns3::NetDeviceContainer ndc;
		for (int i = 0; i < this->nDownlinkPorts; ++i) {
			ndc.Add(this->getDownlinkPort(i));
		}//for
		return ndc;
	}//getDownlinkDevices

	void setUplinkPort(ns3::Ptr<ns3::NetDevice> net_device,
			const int i_uplink_port) {
		const int device_index = this->AddDevice(net_device);
		this->uplinkPortIndices[i_uplink_port] = device_index;
		this->bridgeAllPorts();
	}//setUplinkPort

	void setDownlinkPort(ns3::Ptr<ns3::NetDevice> net_device,
			const int i_downlink_port) {
		const int device_index = this->AddDevice(net_device);
		this->downlinkPortIndices[i_downlink_port] = device_index;
		this->bridgeAllPorts();
	}//setDownlinkPort

	void connectUpTo(const int i_uplink_port, EunetSwitch& upstream_switch,
			const int i_downlink_port) {
		ns3::NetDeviceContainer link = this->uplinkCsmaHelper.Install(
				ns3::NodeContainer(ns3::NodeContainer(this),
						ns3::NodeContainer(&upstream_switch)));
		this->setUplinkPort(link.Get(0), i_uplink_port);
		upstream_switch.setDownlinkPort(link.Get(1), i_downlink_port);
	}//connectUpTo

	void connectDownTo(const int i_downlink_port,
			EunetSwitch& downstream_switch, const int i_uplink_port) {
		ns3::NetDeviceContainer link = this->downlinkCsmaHelper.Install(
				ns3::NodeContainer(ns3::NodeContainer(this),
						ns3::NodeContainer(&downstream_switch)));
		this->setDownlinkPort(link.Get(0), i_downlink_port);
		downstream_switch.setUplinkPort(link.Get(1), i_uplink_port);
	}//connectDownTo

	void connectSibling(const int i_uplink_port, EunetSwitch& sibling_switch,
			const int i_sibling_uplink_port) {
		ns3::NetDeviceContainer link = this->siblingCsmaHelper.Install(
				ns3::NodeContainer(ns3::NodeContainer(this),
						ns3::NodeContainer(&sibling_switch)));
		this->setUplinkPort(link.Get(0), i_uplink_port);
		sibling_switch.setUplinkPort(link.Get(1), i_sibling_uplink_port);
	}//connectSibling

	virtual ~EunetSwitch() {
	}//the destructor

	ns3::NodeContainer getTerminals() {
		return this->ncTerminals;
	}//getTerminals

	ns3::NetDeviceContainer getTerminalDevices() {
		ns3::NetDeviceContainer ndc;
		for (unsigned i = 0; i < ncTerminals.GetN(); ++i) {
			ndc.Add(ncTerminals.Get(i)->GetDevice(0));
		}//for
		return ndc;
	}//getTerminalDevices

private:

	void deployTerminals() {
		for (int i = 0; i < nDownlinkPorts; ++i) {
			ns3::NetDeviceContainer link =
					this->downlinkCsmaHelper.Install(ns3::NodeContainer(
							ns3::NodeContainer(this->ncTerminals.Get(i)),
							ns3::NodeContainer(this)));
			assert(this->ncTerminals.Get(i)->GetNDevices()==1);
			//this->ncTerminals.Get(0)->AddDevice(link.Get(0));
			this->setDownlinkPort(link.Get(1), i);
		}//for
		this->bridgeAllPorts();
	}// a constructor

	void bridgeAllPorts() {
		ns3::NetDeviceContainer all_devices;
		all_devices.Add(this->getUplinkDevices());
		all_devices.Add(this->getDownlinkDevices());
		ns3::BridgeHelper bridge_helper;
		bridge_helper.Install(this, all_devices);
	}//bridgeAllPorts

};//class EunetSwitch

#endif /* EUNETSWITCH_H_ */
