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
    po::options_description desc("Command Line Interface for Vici Game Engine.");
    desc.add_options()
        ("help", "produce help message")
        ("cmd", po::value<string>(), "Execute the specified command")
    ;

    po::variables_map vm;
    po::store(po::parse_command_line(ac, av, desc), vm);
    po::notify(vm);    

   
    if(vm.count("cmd"))
    {
        string cmd = vm["cmd"].as<string>();
        if(cmd.size() > 0)
        {
            //string cmdWithArgs = "./Commands/";
            string cmdWithArgs = cmd;
            
            for(int i = 1; i < ac; i++)
            {
                string arg = av[i];

                if(arg == "--cmd" || arg == cmd)
                    continue;

                cmdWithArgs += " ";
                cmdWithArgs += av[i];
            }

            return system (cmdWithArgs.c_str()); // As an example. Change [notepad] to any executable file //    
        }
    }

    if (vm.count("help")) {
        cout << desc << "\n";
        return 1;
    }
    
    return 0;
}