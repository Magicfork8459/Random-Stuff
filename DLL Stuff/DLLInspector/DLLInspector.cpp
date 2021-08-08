#include "DLLInspector.h"

using namespace silverware;

DLLInspector::DLLInspector()
{

}

LibraryVector::iterator DLLInspector::loadLibrary(const std::string& filePath)
{
	boost::filesystem::path path(filePath);
	LibraryVector::iterator returnValue = std::end(libraries);

	if (path.has_filename() and path.extension() == ".dll")
	{
		boost::dll::experimental::smart_library library(path);

		if (library.is_loaded())
		{
			returnValue = libraries.insert(std::end(libraries), library);
		}
	}

	return returnValue;
}