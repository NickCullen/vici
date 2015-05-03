#!/usr/bin/python

import os
import sys

#class which loads up the paths.dirs file in the tools folder
class Paths:
	def __init__(self):
		f = open("paths.dirs","r")
		
		#root folder
		root = os.path.dirname(os.path.realpath(__file__))

		#the table of paths
		self.paths = {}

		#add the paths
		for line in f:
			kv = line.split(':')
			path = kv[1].replace("\n","")
			self.paths[kv[0]] = self.PlatformURL(root + "/" + path)


	#returns the value of a path
	def Path(self, path):
		return self.paths[path]

	#converts specified path to a platform sensible path (i.e. sensible slashes)
	def PlatformURL(self, path):
		return os.path.normpath(path)

def main():
	print(len(sys.argv))
	
	print(str(sys.argv))