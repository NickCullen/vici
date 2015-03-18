#!/usr/bin/python

#Script to take command line arguments and build for specific platforms

#for input args
import sys
import os

#build platform (-windows/-mac/-linux/-android/-ios)
build_platform = "NotSet"

#build target(-32 -64 -all)
build_target = "-32"

#optional generator for xml (Unix Makefiles / XCode etc)
generator = "Unix Makefiles"	

#builds for win32
def BuildWin32():
	print("Building for Win32")
	#refresh and make new win32 directory
	os.system("rm -rf build\win32 && mkdir build\win32")
	os.system("cd build\win32 && cmake -DVICI_TARGET_32:BOOL=true -G \"Visual Studio 12 2013\" ..\..")

#builds for win64
def BuildWin64():
	#refresh and make new win32 directory
	os.system("rm -rf build\win64 && mkdir build\win64")
	os.system("cd build\win64 && cmake -DVICI_TARGET_64:BOOL=true -G \"Visual Studio 12 2013 Win64\" ..\..")

#builds for mac
def BuildMac():
	print("Building for Mac")
	os.system("rm -rf build/mac && mkdir build/mac")
	os.system("cd build/mac && cmake ../..")
	#os.system("cd build/mac && cmake -G \"" + generator + "\" ../..")

	#if it was a make file run make!
	if generator == "Unix Makefiles":
		os.system("cd build/mac && make")

def BuildLinux():
	print("Building for linux")

def BuildAndroid():
	print("Building for android")

def BuildIOS():
	print("Building for ios")




if __name__ == '__main__':
	#need at least 2 args - path and the type of build
	#type of build can be -windows/-mac/-linux/-android/-ios
	#third optional arg is target ie. -32 -64 or -all for both
	if(len(sys.argv) >= 2):
		build_platform = sys.argv[1]
		print("Build Platform = " + build_platform)

		if(len(sys.argv) >= 3):
			build_target = sys.argv[2]
			print("Build Target = " + build_target)

		if(len(sys.argv) >= 4):
			generator = sys.argv[3]
			print("generator = " + generator)

		#if we get here that means build_platform has been set and possibly build_target
		if build_platform == "-windows":
			if build_target == "-all":
				BuildWin32()
				BuildWin64()
			elif build_target == "-32":
				BuildWin32()
			elif build_target == "-64":
				BuildWin64()
		#build targets dont matter for mac
		elif build_platform == "-mac":
			BuildMac()

		#build targets dont matter for linux either (for now?)
		elif build_platform == "-linux":
			BuildLinux()

		elif build_platform == "-android":
			BuildAndroid()

		elif build_platform == "-ios":
			BuildIOS()
	#else no platform was specified so lets try and be smart and build
	#for the given platform
	#else:
