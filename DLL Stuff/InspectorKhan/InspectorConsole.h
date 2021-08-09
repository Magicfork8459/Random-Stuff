#pragma once
#include <iostream>
#include <msclr\marshal_cppstd.h>

#include <boost\program_options\options_description.hpp>
#include <boost\program_options\variables_map.hpp>
#include <boost\program_options\parsers.hpp>
#include <boost\tokenizer.hpp>

#include "DLLInspector.h"

using namespace System::Windows::Forms;
namespace bpo = boost::program_options;

namespace silverware
{
	class InspectorConsole
	{
	public:
		InspectorConsole(const int& argc, char** argv);
		InspectorConsole(const InspectorConsole& that);

		void run();

	private:
		std::unique_ptr<DLLInspector> inspector;
		bpo::options_description commandLineOptions;
		bpo::options_description menuOptions {"Inspector Khan"};
		bpo::variables_map variables;
		bool quit { false };
	};
}


