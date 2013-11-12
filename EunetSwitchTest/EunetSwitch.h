#ifndef EUNETSWITCH_H_
#define EUNETSWITCH_H_
#include <cassert>
#include <stdexcept>
#include <memory>
#include <strstream>
#include "ns3/node.h"
#include "ns3/csma-channel.h"

class EunetSwitch: public ns3::Node {

        std::vector<int> uplinkPortIndices;
        std::vector<int> downlinkPortIndices;
        ns3::NodeContainer ncTerminals;
        ns3::BridgeHelper bridge_helper;
        const int nDownlinkPorts;
        const int nDownlinkBps;
        const int nDownlinkDelayMilliseconds;
        const int nUplinkPorts;
        const int nUplinkBps;
        const int nUplinkDelayMilliseconds;
        //ns3::CsmaHelper downlinkCsmaHelper;
        //ns3::CsmaHelper uplinkCsmaHelper;
        //ns3::CsmaHelper siblingCsmaHelper;

public:
        EunetSwitch(const int n_downlink_ports = 48, const int n_downlink_bps =
        		1000000000, const int n_downlink_delay_milliseconds = 1,
        		const int n_uplink_ports = 4, const int n_uplink_bps = 1000000000,
        		const int n_uplink_delay_milliseconds = 1) :
                uplinkPortIndices(n_uplink_ports),downlinkPortIndices(n_downlink_ports),
                nDownlinkPorts(n_downlink_ports), nDownlinkBps(n_downlink_bps),nDownlinkDelayMilliseconds(n_downlink_delay_milliseconds),
                nUplinkPorts(n_uplink_ports), nUplinkBps(n_uplink_bps),nUplinkDelayMilliseconds(n_uplink_delay_milliseconds) {
                this->ncTerminals.Create(n_downlink_ports);
                this->deployTerminals();
                ns3::InternetStackHelper internet_stack_helper;
                internet_stack_helper.Install(ncTerminals);
                //internet_stack_helper.Install(ncTerminals.getTerminals());
        }//a constructor

        std::shared_ptr<ns3::CsmaHelper> getDownlinkCsmaHelper() const {
        	std::shared_ptr<ns3::CsmaHelper> csma_helper(new ns3::CsmaHelper());
                csma_helper->SetChannelAttribute("DataRate", ns3::DataRateValue(
                                this->nDownlinkBps));
                csma_helper->SetChannelAttribute("Delay", ns3::TimeValue(
                                ns3::MilliSeconds(this->nDownlinkDelayMilliseconds)));
                csma_helper->SetChannelAttribute("DataRate", ns3::DataRateValue(
                                this->nDownlinkBps));
                csma_helper->SetChannelAttribute("Delay", ns3::TimeValue(
                                ns3::MilliSeconds(this->nDownlinkDelayMilliseconds)));
                return csma_helper;
        }//getDownlinkCsmaHelper

        std::shared_ptr<ns3::CsmaHelper> getUplinkCsmaHelper() const {
                std::shared_ptr<ns3::CsmaHelper> csma_helper(new ns3::CsmaHelper());
                csma_helper->SetChannelAttribute("DataRate", ns3::DataRateValue(
                                this->nUplinkBps));
                csma_helper->SetChannelAttribute("Delay", ns3::TimeValue(
                                ns3::MilliSeconds(this->nUplinkDelayMilliseconds)));
                csma_helper->SetChannelAttribute("DataRate", ns3::DataRateValue(
                                this->nUplinkBps));
                csma_helper->SetChannelAttribute("Delay", ns3::TimeValue(
                                ns3::MilliSeconds(this->nUplinkDelayMilliseconds)));
                return csma_helper;
        }//getUplinkCsmaHelper

        ns3::Ptr<ns3::NetDevice> getUplinkPort(const int i_uplink_port) const {
                return this->GetDevice(this->uplinkPortIndices[i_uplink_port]);
        }//getUplinkPort

        ns3::Ptr<ns3::NetDevice> getDownlinkPort(const int i_downlink_port) const {
                return this->GetDevice(this->downlinkPortIndices[i_downlink_port]);
        }//getDownlinkPort

        ns3::NetDeviceContainer getUplinkDevices() const {
                ns3::NetDeviceContainer ndc;
                for (int i = 0; i < this->nUplinkPorts; ++i) {
                        ndc.Add(this->getUplinkPort(i));
                }//for
                return ndc;
        }//getUplinkDevices

        ns3::NetDeviceContainer getDownlinkDevices() const {
                ns3::NetDeviceContainer ndc;
                for (int i = 0; i < this->nDownlinkPorts; ++i) {
                        ndc.Add(this->getDownlinkPort(i));
                }//for
                return ndc;
        }//getDownlinkDevices

        void setUplinkPortIndex(const int i_uplink_port) {
                this->setUplinkPortIndex(i_uplink_port, this->GetNDevices() - 1);
        }//setUplinkPortIndex

        void setUplinkPortIndex(const int i_uplink_port,
                        const uint32_t i_net_device) {
                if (0 > i_uplink_port || this->uplinkPortIndices.size()
                                <= i_uplink_port) {
                        std::stringstream ss;
                        ss << "max uplink port index is ";
                        ss << this->uplinkPortIndices.size();
                        ss << " while ";
                        ss << i_uplink_port;
                        ss << " is given.";
                        throw std::invalid_argument(ss.str());
                }//if
                this->uplinkPortIndices[i_uplink_port] = i_net_device;
        }//setUplinkPortIndex

        void setDownlinkPortIndex(const int i_downlink_port) {
                this->setDownlinkPortIndex(i_downlink_port, this->GetNDevices() - 1);
        }//setUplinkPortIndex

        void setDownlinkPortIndex(const int i_downlink_port,
                        const uint32_t i_net_device) {
                if (0 > i_downlink_port || this->downlinkPortIndices.size()
                                <= i_downlink_port) {
                        std::stringstream ss;
                        ss << "max downlink port index is ";
                        ss << this->downlinkPortIndices.size();
                        ss << " while ";
                        ss << i_downlink_port;
                        ss << " is given.";
                        throw std::invalid_argument(ss.str());
                }//if
                this->downlinkPortIndices[i_downlink_port] = i_net_device;
        }//setUplinkPortIndex

        void connectUpTo(const int i_uplink_port,
                        ns3::Ptr<EunetSwitch> upstream_switch, const int i_downlink_port) {
                ns3::NetDeviceContainer link = this->getUplinkCsmaHelper()->Install(
                                ns3::NodeContainer(ns3::NodeContainer(this),
                                                ns3::NodeContainer(upstream_switch)));
                this->setUplinkPortIndex(i_uplink_port);
                upstream_switch->setDownlinkPortIndex(i_downlink_port);
                this->bridgeAllPorts();
        }//connectUpTo

        void connectDownTo(const int i_downlink_port,
                        ns3::Ptr<EunetSwitch> downstream_switch, const int i_uplink_port) {
                ns3::NetDeviceContainer link = this->getDownlinkCsmaHelper()->Install(
                                ns3::NodeContainer(ns3::NodeContainer(this),
                                                ns3::NodeContainer(downstream_switch)));
                this->setDownlinkPortIndex(i_downlink_port);
                downstream_switch->setUplinkPortIndex(i_uplink_port);
                this->bridgeAllPorts();
        }//connectDownTo

        void connectSibling(const int i_uplink_port, EunetSwitch& sibling_switch,
                        const int i_sibling_uplink_port) {
                ns3::NetDeviceContainer link = this->getUplinkCsmaHelper()->Install(
                                ns3::NodeContainer(ns3::NodeContainer(this),
                                                ns3::NodeContainer(&sibling_switch)));
                this->uplinkPortIndices[i_uplink_port] = this->GetNDevices() - 1;
                sibling_switch.downlinkPortIndices[i_sibling_uplink_port]
                                = sibling_switch.GetNDevices() - 1;
        }//connectSibling

        virtual ~EunetSwitch() {
        }//the destructor

        const ns3::NodeContainer& getTerminals() const {
                return this->ncTerminals;
        }//getTerminals

        ns3::NetDeviceContainer getTerminalDevices() const {
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
                                        this->getDownlinkCsmaHelper()->Install(ns3::NodeContainer(
                                                        ns3::NodeContainer(this->ncTerminals.Get(i)),
                                                        ns3::NodeContainer(this)));
                        assert(this->ncTerminals.Get(i)->GetNDevices()==1);
                        //this->ncTerminals.Get(0)->AddDevice(link.Get(0));
                        this->downlinkPortIndices[i] = this->GetNDevices() - 1;
                }//for
                //this->bridgeAllPorts();
        }//deployTerminals

        void bridgeAllPorts() {
                ns3::NetDeviceContainer all_devices;
                all_devices.Add(this->getUplinkDevices());
                all_devices.Add(this->getDownlinkDevices());
                bridge_helper.Install(this, all_devices);
        }//bridgeAllPorts

};//class EunetSwitch

#endif /* EUNETSWITCH_H_ */
