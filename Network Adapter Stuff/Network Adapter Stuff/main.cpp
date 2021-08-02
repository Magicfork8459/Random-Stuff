#include <iostream>
#include "AdapterCheck.h"


int main()
{
	int exitCode = 0;
	AdapterCheck adapters;
	//std::wcout << adapters.toString() << std::endl;
	adapters.dumpToFile();
	return exitCode;
}