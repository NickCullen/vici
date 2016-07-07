#Info

Game engine and editor written in C++. Currently being developed on Windows and is very much in a work in progress state.

#Setup

The engine relies on some submodules, so be sure to run the following commands after cloning the repo.
- > git submodule init
- > git submodule update

You will also need to setup a few system env vars - don't worry this is easy!
- Right click setup.bat (or setup.sh if you're not on windows) and run as admin

## CMAKE

The project uses CMake to generate its project files (Visual Studio Solution, XCode project etc.) so make sure you install CMake. The GUI
is pretty straight forward so the following setup instructions are for CMakes cli.

### Windows
- > cd %VICI_HOME% 
- > mkdir Project
- > cd Project
- > cmake ..

You will now see the Visual studio solution in the Project folder.
- Open Project/Vici.sln
- ctrl + shift + B to build

### Mac
So far this project will only run on Windows, but using Cmake it is pretty straight forward to run on Mac (when I get around
to implementing its layer).
Setup process will be as follows

- > cd $VICI_HOME
- > mkdir Project
- > cd Project
- > cmake -G XCode ..
OR (if you want to use make files)
- > cmake -G "Unix Makefiles" ..

If you went the makefile way, simply enter the following to compile the project
- > make

If you generated an XCode project, you will find the XCode solution under Project/Vici.xcode

### Linux
So far this project will only run on Windows, but using Cmake it is pretty straight forward to run on Linux (when I get around
to implementing its layer).
Setup process will be as follows

- > cd $VICI_HOME
- > mkdir Project
- > cd Project
- > cmake ..
- > make


