#pragma once
#include <string>

#include <boost/dll.hpp>
#include <boost/dll/runtime_symbol_info.hpp>
#include <boost/dll/smart_library.hpp>
#include <boost/filesystem.hpp>

namespace bd = boost::dll;
namespace bde = bd::experimental;
namespace silverware
{
	using LibraryVector = std::vector<std::unique_ptr<bde::smart_library>>;

	class DLLInspector
	{
	public:
		DLLInspector();
		DLLInspector(const DLLInspector& that);
		~DLLInspector();
		LibraryVector::iterator loadLibrary(const std::string& filePath);
		std::string toString();

	private:
		LibraryVector libraries;
	};

}

