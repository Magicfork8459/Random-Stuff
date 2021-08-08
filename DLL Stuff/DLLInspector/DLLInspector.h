#pragma once
#include <string>

#include <boost/dll.hpp>
#include <boost/dll/runtime_symbol_info.hpp>
#include <boost/dll/smart_library.hpp>
#include <boost/filesystem.hpp>

namespace silverware
{
	using LibraryVector = std::vector<boost::dll::experimental::smart_library>;

	class DLLInspector
	{
	public:
		DLLInspector();
		LibraryVector::iterator loadLibrary(const std::string& filePath);

	private:
		LibraryVector libraries;
	};

}

