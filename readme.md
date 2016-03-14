#Info
Game engine and editor written in C++. Currently being developed on Windows and is very much in a work in progress state.

#Setup

The engine relies on some submodules, so be sure to run the following commands after cloning the repo.
- git submodule init
- git submodule update

##Windows
Currently, there are only project files for Visual Studio 2015. Moved away from Cmake whilst I get the barebones of the engine in place.
Steps for first time setup:
- Run setup.bat as admin
- Open Visual studio solution found in 'Projects/vs2015' directory