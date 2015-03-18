#Install
It is essential to first install Cmake and optional to install python to use the build.py script. The build.py script is very much recommended!

####Without python 
 - cd Path/To/Vici/Root
 - mkdir build && cd build
 - Windows : cmake -DVICI_TARGET_32:BOOL=true -DVICI_WINDOWS:BOOL=true ..
 - Mac : cmake -DVICI_MAC:BOOL=true .. && make

####With python
 - cd Path/To/Vici/Root
 - python build.py -h (for arguments to build script)
 - python build.py -p [windows/mac] -t [32/64/all] -b [release/debug] -g [Unix Makefiles/Xcode... (see cmake --help for list of genereators)]

You can also simply run
 - python build.py 
from the root of the Vici directory and it will build for the current platform.

Whatever you choose the Visual Studio/ Make File / XCode project will be in the build directory.

#Description
This is a project I am working on in my spare time purely for learning. I am blogging about updates here ( www.blog.nickcullen.net ). This engine will not be sold not is it being made for the purpose of being sold so feel free to download and have a play about with it!

Anyone who wants to contribute drop me a message. 

#Supported Platforms
 - Windows (x86 & x64)
 - Mac