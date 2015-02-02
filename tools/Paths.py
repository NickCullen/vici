import os

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
			self.paths[kv[0]] = self.Pathify(root + "/" + kv[1])

	#returns the value of a path
	def Path(self, path):
		return self.paths[path]

	#converts specified path to a platform sensible path (i.e. sensible slashes)
	def Pathify(self, path):
		return os.path.normpath(path)

tmp = Paths()