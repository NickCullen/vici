#Install
It is essential to first install Cmake.

First run the following setup script in the vici home directory
 - setup.bat (Windows)
 - setup.sh (Mac/Linux)

This will create the required environment variables 'VICI_HOME', 'VICI_TOOLS' and 'VICI_PYTHON'. Note if you move the Vici directory - please run this script again! It is required for the engine tools.

Restart your terminal 

#Compiling

####Windows
 - cd %VICI_HOME%
 - $ vicipy %VICI_TOOLS%\build.py
 - $ mkdir build && cd build
 - $ cmake ..
 
This will use cmake to create the Visual Studio project solutions to build the engine.
The engine has been created using Visual Studio 2015.

####Mac
 - cd $VICI_HOME
 - $ vicipy $VICI_TOOLS/build.py
 - $ mkdir build && cd build
 - $ cmake .. && make
 OR
 - $ cmake -G Xcode ..
 
 The latter cmake option will create an Xcode project in the build directory.


#Description
This is a project I am working on in my spare time purely for learning. I am blogging about updates here ( www.blog.nickcullen.net ). This engine will not be sold nor is it being made for the purpose of being sold so feel free to download and have a play about with it!

Anyone who wants to contribute drop me a message. 

#Supported Platforms
 - Windows (x86 & x64)
 - Mac