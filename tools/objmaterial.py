#!/usr/bin/python

from Paths import *

#vector for colors
class Vector:
	def __init__(self, r,g,b,a):
		self.r = r
		self.g = g
		self.b = b
		self.a = a

#the structure containing material data
class Material:
	def __init__(self):
		self.ns = 0
		self.ka = Vector(0,0,0,0)
		self.kd = Vector(0,0,0,0)
		self.ks = Vector(0,0,0,0)
		self.d = 0
		self.illum = 1
		self.textures = []
		self.id = "UnknownID"

	def WriteToFile(self, file):
		file.write("<root>\n")
		file.write("<id>" + self.id + "</id>\n")
		file.write("<ns>" + str(self.ns) + "</ns>\n")
		file.write("<ka>" + str(self.ka.r) + " " + str(self.ka.g) + " " + str(self.ka.b) + " " + str(self.ka.a) + "</ka>\n")
		file.write("<kd>" + str(self.kd.r) + " " + str(self.kd.g) + " " + str(self.kd.b) + " " + str(self.kd.a) + "</kd>\n")
		file.write("<ks>" + str(self.ks.r) + " " + str(self.ks.g) + " " + str(self.ks.b) + " " + str(self.ks.a) + "</ks>\n")
		file.write("<d>" + str(self.d) + "</d>\n")
		file.write("<illum>" + str(self.illum) + "</illum>\n")

		##write textures is a little different

		file.write("</root>")

#class to create and output the vici material files
#from the given obj material file
class ObjMaterial:
	def __init__(self, obj_mat_file):
		#so we know where to output stuff
		self.paths = Paths()

		#the materials to output
		self.materials = []

		#open the obj material file
		self.file = open(obj_mat_file, "r")

		#parse the file
		self.Parse()

	def Parse(self):

		#the current material
		current = 0

		for line in self.file:
			split = line.split()

			#ignore comments and empty lines
			if not split or split[0] == "#": 
				continue

			#create a new material
			if split[0] == "newmtl":
				#if there is already a current - write it to the file
				if current != 0:
					self.WriteMaterial(current)

				#now create a new one
				current = Material()
				current.id = split[1]

			elif split[0] == "Ns":
				current.ns = float(split[1])
			elif split[0] == "Ka":
				#determine if its a 4 component (rgba) or just rgb
				no_comp = len(split)-1 #(minus 1 to ignore the line identifier)
				if no_comp == 3:
					current.ka = Vector(float(split[1]), float(split[2]), float(split[3]), 0)
				else:
					current.ka = Vector(float(split[1]), float(split[2]), float(split[3]), float(split[4]))
			elif split[0] == "Kd":
				#determine if its a 4 component (rgba) or just rgb
				no_comp = len(split)-1 #(minus 1 to ignore the line identifier)
				if no_comp == 3:
					current.kd = Vector(float(split[1]), float(split[2]), float(split[3]), 0)
				else:
					current.kd = Vector(float(split[1]), float(split[2]), float(split[3]), float(split[4]))
			elif split[0] == "Ks":
				#determine if its a 4 component (rgba) or just rgb
				no_comp = len(split)-1 #(minus 1 to ignore the line identifier)
				if no_comp == 3:
					current.ks = Vector(float(split[1]), float(split[2]), float(split[3]), 0)
				else:
					current.ks = Vector(float(split[1]), float(split[2]), float(split[3]), float(split[4]))
			elif split[0] == "d":
				current.d = float(split[1])
			elif split[0] == "illum":
				current.illum = float(split[1])

		#write the current material
		self.WriteMaterial(current)

	def WriteMaterial(self, mat):
		#open the file to write in the materials folder
		f = open(self.paths.PlatformURL(self.paths.Path("assets") + "/Materials/" + mat.id + ".material"), "w")
		#write the material to the file
		mat.WriteToFile(f)
		#close
		f.close()
