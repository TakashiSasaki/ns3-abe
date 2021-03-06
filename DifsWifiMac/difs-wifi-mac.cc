#define NS3_LOG_ENABLE 1
#include "ns3/log.h"
#include "ns3/uinteger.h"
#include "difs-wifi-mac.h"

NS_LOG_COMPONENT_DEFINE("DifsWifiMac");
namespace abe{
NS_OBJECT_ENSURE_REGISTERED(DifsWifiMac);

DifsWifiMac::DifsWifiMac(uint32_t aifsn, uint32_t cwmin, uint32_t cwmax) ://default value is for 802.11b standard
	AdhocWifiMac(), aifsn(aifsn), cwmin(cwmin), cwmax(cwmax) {
	NS_LOG_FUNCTION(this);
	pAdhocWifiMac = this;
	pRegularWifiMac = this;
	pWifiMac = this;
}//constructor

DifsWifiMac::~DifsWifiMac() {
	//NS_LOG_FUNCTION(this);
}//destructor

ns3::TypeId DifsWifiMac::GetTypeId(void) {
	static ns3::TypeId type_id = ns3::TypeId("abe::DifsWifiMac")
		.SetParent<ns3::AdhocWifiMac> ()
		.AddConstructor<DifsWifiMac> ()
		.AddAttribute("Aifsn","Aifsn",ns3::UintegerValue(2),
			ns3::MakeUintegerAccessor(&DifsWifiMac::aifsn),
			ns3::MakeUintegerChecker<uint32_t>())
		.AddAttribute("cwmin", "cwmin", ns3::UintegerValue(31),
			ns3::MakeUintegerAccessor(&DifsWifiMac::cwmin),
			ns3::MakeUintegerChecker<uint32_t>())
		.AddAttribute("cwmax", "cwmax", ns3::UintegerValue(1023),
			ns3::MakeUintegerAccessor(&DifsWifiMac::cwmax),
			ns3::MakeUintegerChecker<uint32_t>());
	return type_id;
}//GetTypeId

void DifsWifiMac::FinishConfigureStandard(enum ns3::WifiPhyStandard standard) {
	NS_LOG_FUNCTION(this);
	ns3::AdhocWifiMac::FinishConfigureStandard(standard);
	ns3::AdhocWifiMac::ConfigureDcf(ns3::AdhocWifiMac::m_dca, cwmin, cwmax,
			ns3::AC_BE_NQOS);
	ns3::AdhocWifiMac::m_dca->SetAifsn(aifsn);
}//FinishConfigureStandard

void DifsWifiMac::Enqueue (ns3::Ptr<const ns3::Packet> packet, ns3::Mac48Address to){
	NS_LOG_FUNCTION(this);
	NS_LOG_INFO("L2 frame is enqueued in MAC layer.");
	ns3::AdhocWifiMac::Enqueue(packet, to);
}//Enqueue

}//abe
