#include "AdapterCheck.h"

//! This only supports IPV4, but could be made to support IPV6 too

AdapterCheck::AdapterCheck(unsigned long flag)
	: addresses(NULL)
{
	unsigned long bufferLength = 0;

	GetAdaptersAddresses(AF_INET, flag, NULL, NULL, &bufferLength); // Get the buffer size first because windows
	addresses = static_cast<PIP_ADAPTER_ADDRESSES>(malloc(bufferLength));
	GetAdaptersAddresses(AF_INET, flag, NULL, addresses, &bufferLength);
}

AdapterCheck::AdapterCheck(const AdapterCheck& that)
	: addresses(that.addresses)
{
}

AdapterCheck::~AdapterCheck()
{
	if (addresses)
	{
		free(addresses);
	}
}

std::wstring AdapterCheck::toString()
{
	PIP_ADAPTER_ADDRESSES working = addresses;
	std::wstringstream returnString;

	while (working)
	{
		int addressIndex = 0;

		returnString
			<< "Properties for " << std::wstring(working->FriendlyName) << '\n'
			<< "-----------------------------------------------------------------------------------------\n"
			<< "[AdapterName]\t\t" << working->AdapterName << '\n'
			<< "[Description]\t\t" << working->Description << '\n'
			;
		PIP_ADAPTER_UNICAST_ADDRESS_LH unicast = working->FirstUnicastAddress;
		if (unicast)
		{
			returnString << "[IPV4 Unicast Addresses]\n";
		}
		while (unicast)
		{
			std::string address;
			DWORD netMaskRaw;
			std::string netMask;

			address = inet_ntop(unicast->Address.lpSockaddr->sa_family, (&((struct sockaddr_in*)unicast->Address.lpSockaddr)->sin_addr), &address[0], INET_ADDRSTRLEN);
			ConvertLengthToIpv4Mask(unicast->OnLinkPrefixLength, &netMaskRaw);
			netMask = inet_ntop(unicast->Address.lpSockaddr->sa_family, &netMaskRaw, &netMask[0], INET_ADDRSTRLEN);

			if(!address.empty())
			{
				returnString 
					<< "\t[" << addressIndex++ << "]\t" << string_transform<std::wstring>(address)
					<< " | " << string_transform<std::wstring>(netMask) << '\n'
					;
			}

			unicast = unicast->Next;
		}

		PIP_ADAPTER_GATEWAY_ADDRESS_LH gateway = working->FirstGatewayAddress;
		if (gateway)
		{
			returnString << "[Gateway Addresses]\n";
			addressIndex = 0;
		}
		while (gateway)
		{
			std::string address;

			address = inet_ntop(gateway->Address.lpSockaddr->sa_family, (&((struct sockaddr_in*)gateway->Address.lpSockaddr)->sin_addr), & address[0], INET_ADDRSTRLEN);

			if (!address.empty())
			{
				returnString << "\t[" << addressIndex++ << "]\t" << string_transform<std::wstring>(address);
			}

			gateway = gateway->Next;
		}

		returnString << '\n';

		working = working->Next;
	}

	return returnString.str();
}

bool AdapterCheck::dumpToFile(const std::string& file)
{
	std::wstring dump(toString());
	
	if (!dump.empty())
	{
		std::wofstream output(file, std::ios_base::out);
		output << dump;
		output.close();
	}

	return !dump.empty();
}