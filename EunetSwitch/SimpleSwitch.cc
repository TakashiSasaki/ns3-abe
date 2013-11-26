#define NS3_LOG_ENABLE 1
#include "ns3/log.h"
NS_LOG_COMPONENT_DEFINE("SimpleSwitch");
#define NS3_ASSERT_ENABLE 1
#include "ns3/assert.h"
#include "ns3/type-id.h"
#include "SimpleSwitch.h"
NS_OBJECT_ENSURE_REGISTERED( SimpleSwitch);

ns3::TypeId SimpleSwitch::GetTypeId(void) {
	static ns3::TypeId type_id = ns3::TypeId("SimpleSwitch").SetParent<
			CsmaChannelNode> ().AddConstructor<SimpleSwitch> ();
	return type_id;
}//GetTypeId


SimpleSwitch::SimpleSwitch() {
	// TODO 自動生成されたコンストラクター・スタブ

}

SimpleSwitch::~SimpleSwitch() {
	// TODO !CodeTemplates.destructorstub.tododesc!
}
