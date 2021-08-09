#include "InspectorConsole.h"

using namespace silverware;

InspectorConsole::InspectorConsole(const int& argc, char** argv)
	: inspector(std::make_unique<DLLInspector>())
{
	menuOptions.add_options()
		("help,h", "Display this help message")
		("open,o", "Opens an explorer so you can pick a library to load")
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
			//OpenFileDialog^ fileDialog = gcnew OpenFileDialog();
			OpenFileDialog fileDialog;
			fileDialog.Filter = "Application extension (*.dll)|*.dll|Object File Library (*.lib)|*.lib)";
			fileDialog.InitialDirectory = "C:";

			if (fileDialog.ShowDialog() == DialogResult::OK)
			{
				System::String^ filePath = fileDialog.FileName;

				inspector->loadLibrary(msclr::interop::marshal_as<std::string>(filePath));

				delete filePath;
			}

			std::cout << "Pick a file..." << std::endl;
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