#include "Tester.h"

PlugAlyzer::Tester::Tester() 
{

}

PlugAlyzer::Tester::~Tester()
{
	
}

void PlugAlyzer::Tester::addProcess(const std::string& processString)
{
	std::lock_guard lockGuard(processMutex);
	processQueue.push(processString);
}
