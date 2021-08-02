#pragma once
#pragma warning(disable : 4996) // std::localtime
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <chrono>
#include <ctime>
#include <iomanip>

#include <winsock2.h>
#include <iphlpapi.h>
#include <ws2tcpip.h>

template<typename To, typename From>
inline To string_transform(From string) noexcept
{
	To returnValue;
	if (string.empty())
	{
		returnValue = {};
	}
	else
	{
		returnValue = { std::begin(string), std::end(string) };
	}
	return returnValue;
}

inline std::string getTimestamp()
{
	std::stringstream stream;
	std::time_t current = std::time(NULL);
	std::tm tm = *std::localtime(&current);
	stream << std::put_time(&tm, "%H_%M_%S");
	return stream.str();
}

class AdapterCheck
{
public:
	AdapterCheck(unsigned long flag = GAA_FLAG_INCLUDE_ALL_INTERFACES);
	AdapterCheck(const AdapterCheck& that);
	~AdapterCheck();

	std::wstring toString();
	//bool writeToFile(const std::string& file);
	bool dumpToFile(const std::string& file = std::string("adapter_dump_" + getTimestamp() + ".txt"));
protected:
private:
	PIP_ADAPTER_ADDRESSES addresses;
};

