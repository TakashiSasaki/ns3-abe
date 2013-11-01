#include <iostream>
#include <cstdlib>
#include <cassert>
#define NS3_LOG_ENABLE 1
#include "ns3/log.h"

//NS_LOG_COMPONENT_DEFINE("HelloNsLog");

static ns3::LogComponent g_log = ns3::LogComponent ("HelloNsLog");

void foo(){
	ns3::LogComponentEnable("HelloNsLog", ns3::LOG_LEVEL_ALL);
	//ns3::LogComponentPrintList();
	NS_LOG_UNCOND("HelloNsLog NS_LOG_UNCOND");
	NS_LOG_INFO("HelloNsLog NS_LOG_INFO");
}

int main(int argc, char** argv){
	std::cerr << "main std:cerr" << std::endl;
	std::clog << "main std:clog" << std::endl;
	foo();
	return EXIT_SUCCESS;
}//main

