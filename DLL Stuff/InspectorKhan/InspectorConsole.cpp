#include "InspectorConsole.h"

using namespace silverware;

InspectorConsole::InspectorConsole(const int& argc, char** argv)
	: inspector(std::make_unique<DLLInspector>())
{
	menuOptions.add_options()
		("help,h", "Display this help message")
		("open,o", "Opens an explorer so you can pick a library to load")
		("view,v", "View the submenu for a loaded library")
		("quit,q", bpo::bool_switch(&quit), "Close the console")
		("test,t", "Test some stuff")
		;
	
	commandLineOptions.add_options()
		("load,l", bpo::value<std::string>())
		;

	bpo::store(parse_command_line(argc, argv, commandLineOptions), variables);
	bpo::notify(variables);

	std::cout << menuOptions << std::endl;
}

// TODO add inspector
InspectorConsole::InspectorConsole(const InspectorConsole& that)
	: menuOptions(that.menuOptions), quit(that.quit)
{
}

void InspectorConsole::run()
{
	do
	{
		std::string input;
		std::getline(std::cin, input);
		std::cout << std::endl;
		std::vector<std::string> tokens;
		boost::tokenizer<boost::char_separator<char>> tokenizer(input, boost::char_separator<char>(" "));

		std::copy(std::begin(tokenizer), std::end(tokenizer), std::back_inserter(tokens));
		bpo::store(bpo::command_line_parser(tokens).options(this->menuOptions).run(), variables);
		bpo::notify(variables);

		if (variables.count("help"))
		{
			std::cout << menuOptions << std::endl;
		}

		if (variables.count("open"))
		{
			OpenFileDialog fileDialog;
			fileDialog.Filter = "Application extension (*.dll)|*.dll|Object File Library (*.lib)|*.lib)";
			fileDialog.InitialDirectory = "C:";

			std::cout << "Pick a file...\n\n";

			if (fileDialog.ShowDialog() == DialogResult::OK)
			{
				System::String^ managedFilePath = fileDialog.FileName;

				try
				{
					std::string unmanagedFilePath = msclr::interop::marshal_as<std::string>(managedFilePath);
					const auto& loaded = inspector->loadLibrary(unmanagedFilePath);
					const auto& libraries = inspector->getLibraries();
					boost::format formatMessage("%1% the library at %2%\n\n");

					if (loaded != libraries.end())
					{
						formatMessage.bind_arg(1, "Successfully loaded");
					}
					else
					{
						formatMessage.bind_arg(1, "Failed to load");
					}

					formatMessage.bind_arg(2, unmanagedFilePath);
					std::cout << formatMessage.str();
					/*for (const auto& stuff : inspector->getDemangledSymbols(0))
					{
						std::cout << stuff << std::endl;
					}*/
				}
				catch (const boost::system::system_error& se)
				{
					std::cerr << se.what() << std::endl;
				}
				
				delete managedFilePath;
			}
		}

		if (variables.count("view"))
		{
			// Enumerate the loaded libraries
			const auto& libraries = inspector->getLibraries();
			
			if (!libraries.empty())
			{
				std::stringstream stream;
				int count = 1;
				int index = 0;
				bool continueGettingInput = true;

				for (const auto& library : libraries)
				{
					stream << boost::str(boost::format("[%1%]\t%2%\n") % count++ % library.get()->shared_lib().location());
				}

				stream << "Provide the index of the library you would like to view\nIndex: ";
				std::cout << stream.str();
				
				do
				{
					std::getline(std::cin, input);
					bool match = std::regex_match(input, std::regex("[[:digit:]]*"));
					if (match)
					{
						try
						{
							index = std::stoi(input);
						}
						catch (const std::invalid_argument& ia)
						{
							// TODO Only when debugging
							printError(std::cerr, ia, __FUNCTION__);
						}
						catch (const std::out_of_range& oor)
						{
							// TODO Only when debugging
							printError(std::cerr, oor, __FUNCTION__);
						}
					}

					continueGettingInput = (index <= 0 or index > libraries.size());

					if (continueGettingInput)
					{
						std::cout << "Provide a valid index: ";
						input.clear();
					}
				}
				while (continueGettingInput);
				
				const auto& symbols = inspector->getDemangledSymbols(--index);
				bpo::options_description subMenu;
				count = 1;
				for (const std::string& symbol : symbols)
				{
					subMenu.add_options()(std::to_string(count++).c_str(), symbol.c_str());
				}

				std::cout << subMenu << std::endl;
				
			}
			else
			{
				std::cout << "No libraries currently loaded" << std::endl;
			}
		}

		if (variables.count("test"))
		{
			std::cout << inspector->toString() << std::endl;
		}

		variables.clear();
		
	} while (!quit);
}

[System::STAThreadAttribute]
int main(int argc, char argv[])
{
	int exitCode = 0;
	InspectorConsole console(argc, &argv);

	console.run();
	return exitCode;
}