#!/usr/bin/python

#Script to take command line arguments and build for specific platforms

#for input args
import sys, getopt
import os
import platform
import glob
import shutil

#location of vici instal dir
home = "NotSet"

#build platform (windows/mac/linux/android/ios)
build_platform = "NotSet"

#build target(32 64 all)
build_target = "all"

#build_type (Debug Release)
build_type = "Debug"

#optional generator for xml (Unix Makefiles / XCode etc)
generator = "Unix Makefiles"	

#builds for win32
def BuildWin32():
	print("Building for Win32")

	#refresh and make new win32 directory if needed
	if not os.path.isdir("tmp\win32"):
		os.system("mkdir tmp\win32")

	#copy required cmake file from windows template
	shutil.copyfile(home+"Templates\Windows\CMakeLists.txt", "tmp\win32\CMakeLists.txt")

	#generate visual studio project
	os.system("cd tmp\win32 && cmake -G \"Visual Studio 12 2013\" .")

#builds for win64
def BuildWin64():
	#refresh and make new win64 directory if needed
	if not os.path.isdir("tmp\win64"):
		os.system("mkdir tmp\win64")

	#copy required cmake file from windows template
	shutil.copyfile(home+"Templates\Windows\CMakeLists.txt", "tmp\win64\CMakeLists.txt")

	#generate visual studio project
	os.system("cd tmp\win64 && cmake -G \"Visual Studio 12 2013 Win64\" .")
#builds for mac
def BuildMac():
	print("Building for Mac")

	#refresh and make new win32 directory if needed
	if not os.path.isdir("build/mac"):
		os.system("mkdir build/mac")

	#generate cmake
	os.system("cd build/mac && cmake -DVICI_MAC:BOOL=true -G \"" + generator + "\" ../..")

	#if it was a make file run make!
	if generator == "Unix Makefiles":
		os.system("cd build/mac && make")
	elif generator == "Xcode":
		#find name of file with .xcodeproj that cmake created
		os.chdir("build/mac")
		for f in glob.glob("*.xcodeproj"):
			#trim .xcodeproj
			target = f
			if target.endswith('.xcodeproj'):
			    target = target[:-10]
			cmd = "xcodebuild -target " + target
			os.system(cmd)

def BuildLinux():
	print("Building for linux (Unfortunatly not supported yet)")

def BuildAndroid():
	print("Building for android (Unfortunatly not supported yet)")

def BuildIOS():
	print("Building for ios (Unfortunatly not supported yet)")

#HERE FOR REFERENCE TO GET ENVIRONMENT VARS
#print os.environ.get('HOME')


#main function
if __name__ == '__main__':

	home = os.environ.get('VICI_HOME', 'NotSet')

	if home == "NotSet":
		print("VICI_HOME has not been set! Please run setup.bat (windows as admin) or setup.sh (Mac/Linux)")
		sys.exit()
	else:
		print("VICI_HOME = " + home)

	#make sure tmp directory exists
	if not os.path.isdir("tmp"):
		os.system("mkdir tmp")

	#ignore first arg
	arg_list = sys.argv[1:]

	#optional argument handling :)
	try:
		opts, args = getopt.getopt(arg_list,"hp:t:b:g:",["platform=","target=","build=","generator="])
	except getopt.GetoptError:
		print ("test.py -p [windows/mac/linux/android/ios] -t [32/64] -b [Release/Debug] -g [Xcode/Unix Makefiles etc. etc.]")
		sys.exit(2)
	for opt, arg in opts:
		if opt == '-h':
			print ("test.py -p [windows/mac/linux/android/ios] -t [32/64/all] -b [Release/Debug] -g [Xcode/Unix Makefiles etc. etc.]")
			sys.exit()
		elif opt in ("-p", "--platform"):
	 		build_platform = arg
		elif opt in ("-t", "--target"):
	 		build_target = arg
		elif opt in ("-b", "--build"):
 			build_type = arg
		elif opt in ("-g", "--generator"):
			generator = arg

	#if build was specified....
	if build_platform != "NotSet":
		#if we get here that means build_platform has been set and possibly build_target
		if build_platform == "windows":
			if build_target == "all":
				BuildWin32()
				BuildWin64()
			elif build_target == "32":
				BuildWin32()
			elif build_target == "64":
				BuildWin64()
		#build targets dont matter for mac
		elif build_platform == "mac":
			BuildMac()

		#build targets dont matter for linux either (for now?)
		elif build_platform == "linux":
			BuildLinux()

		elif build_platform == "android":
			BuildAndroid()

		elif build_platform == "ios":
			BuildIOS()
	#else no platform was specified so lets try and be smart and build
	#for the given platform
	else:
		print("Bulding on " + platform.system() + " Computer")

		#mac
		if platform.system() == "Darwin":
			BuildMac()
		#windows
		elif platform.system() == "Windows":
			BuildWin32()
			BuildWin64()
		elif platform.system() == "Linux":
			BuildLinux()
