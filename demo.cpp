#include "option.hpp"
#include <iostream>

bool fitsize_constraint(const int& value) { return value == 3 || value == 5 || value == 7 || value == 9; }

int main(int argc, char** argv)
{
	using namespace mbas;

	command cmd;

	cmd.add_options()
		("i,initial", "Path to picture of initial undeformed picture.", value_type<std::string>(), "TIFF_FILE", false)
		("o,outpics", "If specified, the program will write offsets into pictures and save them in specified folder.", value_type<std::string>(), "FOLDER")
		("f,fitsize", "Specifies size of neighbourhood that is used to fitting and finding subpixel maximum. Allowed values: 3, 5, 7, 9", value_type<int>(), "SIZE", std::function<bool(int)>(&fitsize_constraint))
		("h,help", "Print a usage message on standard output and exit successfully.");


	auto parsed = cmd.parse(argc, argv);

	if (!parsed.parse_ok())
	{
		std::cerr << "Argument parsing error." << "\n";
		std::cerr << cmd.help() << "\n";
		return 1;
	}
	if (parsed["help"])
	{
		std::cerr << cmd.help() << "\n";
		return 1;
	}

	std::string initial_file_name = parsed["initial"]->get_value<std::string>();
    std::cout << "initial_file_name is " << initial_file_name << std::endl; 

	std::string out_dir;
	if (parsed["outpics"]) 
	{
        out_dir = parsed["outpics"]->get_value<std::string>();
        std::cout << "out_dir is " << out_dir << std::endl; 
	}

	int fitsize;
    if (parsed["fitsize"])
    {
        fitsize = parsed["fitsize"]->get_value<int>();
        std::cout << "fitsize is " << fitsize << std::endl; 
    }

	return 0;
}