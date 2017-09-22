#include <stdio.h>
#include <boost/program_options.hpp>
#include <iostream>
#include <string>

#include <windows.h>

using namespace std;
namespace po = boost::program_options;


int main(int ac, char** av)
{
    // Declare the supported options.
    po::options_description desc("Vici header tool.");
    desc.add_options()
        ("help", "produce help message")
        ("i", po::value<string>(), "Input Header file to process")
        ("o", po::value<string>(), "Output header file to generate")
    ;

    po::variables_map vm;
    po::store(po::parse_command_line(ac, av, desc), vm);
    po::notify(vm);    

    if (vm.count("help")) {
        cout << desc << "\n";
        return 1;
    }
    
    printf("FROM HEADER TOOL\n");

    return 0;
}