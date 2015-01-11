#Install
To build the engine you must have cmake installed as there are no project solutions available (i.e. cmake will generate these on the given platform)

###Command line install
- cd Path/of/vici/root
- mkdir build
- cd build
- cmake ..

Once you have run cmake the project files will have been built in the build directory. Simply open up testing.sln (windows) and right click testing project in the project explorer to set it as the startup project.
Now hit complete/run and the project will start building. There are post-build scripts that are defined in CMAKE to copy over the TestProj folder and all the required shared libraries used in the project.

#Description
This is a side project I am working on just out of interest and for learning new things in game engine architecture. I don't plan on selling this so feel free to download and have a poke around, just remember I have recently started this so a lot of clean-up is required!
Being a frequent user of the Unity engine, the GameObject and Component design pattern has been favoured.  

#Support Platorms
Given that this project is new, so far only windows is supported. Although, thanks to CMAKE, making this cross-platform will be soon implemented. I am just working on logic at the moment before looking at other platforms.