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
	// TODO
	// return a formatted string of the following structure
	// [INDEX] : [FRIENDLY NAME]
	//
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

//LibraryVector::iterator DLLInspector::getLibraries()
//{
//	return LibraryVector::iterator(std::begin(libraries));
//}

const LibraryVector& DLLInspector::getLibraries()
{
	return libraries;
}

std::vector<std::string> DLLInspector::getDemangledSymbols(const int& index)
{
	std::vector<std::string> functionNames;
	const auto& library = libraries.find(index);

	if (library != libraries.end())
	{
		for (const auto& symbol : library->get()->symbol_storage().get_storage())
		{
			functionNames.insert(functionNames.end(), symbol.demangled);
		}
	}

	return functionNames;
}

void DLLInspector::enumerateLibrary(int index)
{
	try
	{
		const bde::smart_library& library = *libraries.at(index);
		
		//library.
		//library.get_constructor();
	}
	catch (const std::out_of_range& oor)
	{
		printError(errorOutput, oor, __FUNCTION__);
	}
}