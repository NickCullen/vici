#!/usr/bin/python

#Script to take command line arguments and build for specific platforms

#for input args
import sys

#build platform (-windows/-mac/-linux/-android/-ios)
build_platform = "NotSet"

#build target(-32 -64)
build_target = "32"

#builds for win32
def BuildWin32():
	print("Building for Win32")
	os.system("rm -rf build && mkdir build/win32 && cd build/win32")
	
#builds for win64
def BuildWin64():
	print("Building for Win64")

#builds for mac
def BuildMac():
	print("Building for Mac")

def BuildLinux():
	print("Building for linux")

def BuildAndroid():
	print("Building for android")

def BuildIOS():
	print("Building for ios")




if __name__ == '__main__':
	#need at least 2 args - path and the type of build
	#type of build can be -windows/-mac/-linux/-android/-ios
	#third optional arg is target ie. -32 -64
	if(len(sys.argv) >= 2):
		build_platform = sys.argv[1]
		print("Build Platform = " + build_platform)

		if(len(sys.argv) >= 3):
			build_target = sys.argv[2]
			print("Build Target = " + build_target)

	#if we get here that means build_platform has been set and possibly build_target
	if build_platform == "-windows":
		if build_target == "-32":
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