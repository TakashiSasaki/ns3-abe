#include <cstdlib>
#include "ns3/log.h"
#include <cstdlib>

NS_LOG_COMPONENT_DEFINE("HelloNsLog");
void foo(){
	ns3::LogComponentEnableAll(ns3::LOG_LEVEL_ALL);
	ns3::LogComponentPrintList();
	NS_LOG_UNCOND("HelloNsLog NS_LOG_UNCOND");
	NS_LOG_INFO("HelloNsLog NS_LOG_INFO");
}

int main(int argc, char** argv){
	g_log.Enable(ns3::LOG_LEVEL_ALL);
	std::cerr << "main" << std::endl;
	foo();
	return EXIT_SUCCESS;
}//main

