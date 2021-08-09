#include "DLLInspector.h"

using namespace silverware;

DLLInspector::DLLInspector()
{

}

DLLInspector::DLLInspector(const DLLInspector& that)
{

}

DLLInspector::~DLLInspector()
{
	libraries.clear();
}

std::string DLLInspector::toString()
{
	std::stringstream out;

	for (const auto& library : libraries)
	{
		out << library.get()->shared_lib().location() << std::endl;
	}

	return out.str();
}

LibraryVector::iterator DLLInspector::loadLibrary(const std::string& filePath)
{
	boost::filesystem::path path(filePath);
	LibraryVector::iterator returnValue = std::end(libraries);

	if (boost::filesystem::exists(path) and path.has_filename() and path.extension() == ".dll")
	{
		boost::dll::experimental::smart_library library(path);

		if (library.is_loaded())
		{
			returnValue = libraries.insert(std::end(libraries), std::make_unique<bde::smart_library>(library));
		}
	}

	return returnValue;
}