#pragma once
#include <iostream>
#include <string>

#include <boost/dll.hpp>
#include <boost/dll/runtime_symbol_info.hpp>
#include <boost/dll/smart_library.hpp>
#include <boost/filesystem.hpp>

namespace bd = boost::dll;
namespace bde = bd::experimental;
namespace silverware
{
	//using LibraryVector = std::vector<std::unique_ptr<bde::smart_library>>;
	inline void printError(std::ostream& stream, const std::exception& exception, const std::string& prepend)
	{
		stream << '[' << prepend << "]\t" << exception.what() << std::endl;
	}

	class LibraryVector : public std::vector<std::unique_ptr<bde::smart_library>>
	{
	public:
		LibraryVector::iterator find(const int& index)
		{
			LibraryVector::iterator iterator = this->begin();

			if (index <= this->size())
			{
				iterator += index;
			}
			else
			{
				iterator = this->end();
			}

			return iterator;
		}

		LibraryVector::iterator find(const bde::smart_library& library)
		{
			LibraryVector::iterator iterator = this->begin();

			for (iterator; iterator != this->end(); iterator++)
			{
				if (library == *iterator->get())
				{
					break;
				}
			}

			return iterator;
		}
	};

	class DLLInspector
	{
	public:
		DLLInspector();
		DLLInspector(const DLLInspector& that);
		~DLLInspector();
		LibraryVector::iterator loadLibrary(const std::string& filePath);
		std::vector<std::string> getDemangledSymbols(const int& index);
		//LibraryVector::iterator getLibraries();
		const LibraryVector& getLibraries();
		void enumerateLibrary(int index);
		std::string toString();

	private:
		std::ostream& output { std::cout };
		std::ostream& errorOutput { std::cerr };
		LibraryVector libraries;
	};
}
