#pragma once
#include <iostream>
#include <future>

#include <boost\program_options\options_description.hpp>
#include <boost\program_options\variables_map.hpp>
#include <boost\program_options\parsers.hpp>
#include <boost\tokenizer.hpp>

#ifdef WIN32
#include <ShObjIdl_core.h>
#endif

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
		bpo::options_description commandLineOptions;
		bpo::options_description menuOptions {"Inspector Khan"};
		bpo::variables_map variables;
		bool quit { false };
	};
}


