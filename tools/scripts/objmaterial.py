#!/usr/bin/python

from Paths import *
from Geometry import *
import shutil

class Texture:
	def __init__(self, id, path):
		self.id = id
		self.path = path
		
#the structure containing material data
class Material:
	def __init__(self):
		self.ns = 0
		self.ka = Colour(0,0,0,0)
		self.kd = Colour(0,0,0,0)
		self.ks = Colour(0,0,0,0)
		self.d = 0
		self.illum = 1
		self.textures = dict()
		self.id = "UnknownID"

	def WriteToFile(self, file):
		file.write("<root>\n")
		file.write("\t<id>" + self.id + "</id>\n")
		file.write("\t<ns>" + str(self.ns) + "</ns>\n")
		file.write("\t<ka>" + str(self.ka.r) + " " + str(self.ka.g) + " " + str(self.ka.b) + " " + str(self.ka.a) + "</ka>\n")
		file.write("\t<kd>" + str(self.kd.r) + " " + str(self.kd.g) + " " + str(self.kd.b) + " " + str(self.kd.a) + "</kd>\n")
		file.write("\t<ks>" + str(self.ks.r) + " " + str(self.ks.g) + " " + str(self.ks.b) + " " + str(self.ks.a) + "</ks>\n")
		file.write("\t<d>" + str(self.d) + "</d>\n")
		file.write("\t<illum>" + str(self.illum) + "</illum>\n")
		file.write("</root>")

	def GetTextures(self):
		return self.textures

#class to create and output the vici material files
#from the given obj material file
class ObjMaterial:
	def __init__(self, obj_mat_file):
		#so we know where to output stuff
		self.paths = Paths()

		#the materials to output
		self.materials = dict()

		#open the obj material file
		self.file = open(self.paths.PlatformURL(self.paths.Path("tools") + "/" + obj_mat_file),"r")

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
					#write the file
					self.WriteMaterial(current)
					#add to materials list
					self.materials[current.id] = current

				#now create a new one
				current = Material()
				current.id = split[1]

			elif split[0] == "Ns":
				current.ns = float(split[1])
			elif split[0] == "Ka":
				#determine if its a 4 component (rgba) or just rgb
				no_comp = len(split)-1 #(minus 1 to ignore the line identifier)
				if no_comp == 3:
					current.ka = Colour(float(split[1]), float(split[2]), float(split[3]), 0)
				else:
					current.ka = Colour(float(split[1]), float(split[2]), float(split[3]), float(split[4]))
			elif split[0] == "Kd":
				#determine if its a 4 component (rgba) or just rgb
				no_comp = len(split)-1 #(minus 1 to ignore the line identifier)
				if no_comp == 3:
					current.kd = Colour(float(split[1]), float(split[2]), float(split[3]), 0)
				else:
					current.kd = Colour(float(split[1]), float(split[2]), float(split[3]), float(split[4]))
			elif split[0] == "Ks":
				#determine if its a 4 component (rgba) or just rgb
				no_comp = len(split)-1 #(minus 1 to ignore the line identifier)
				if no_comp == 3:
					current.ks = Colour(float(split[1]), float(split[2]), float(split[3]), 0)
				else:
					current.ks = Colour(float(split[1]), float(split[2]), float(split[3]), float(split[4]))
			elif split[0] == "d":
				current.d = float(split[1])
			elif split[0] == "illum":
				current.illum = float(split[1])
			#texture maps
			elif split[0] == "map_Ka":	#ambient map
				current.textures["Ambient"] = split[1]
				#copy texture
				self.CopyTexture(split[1])
			elif split[0] == "map_Kd":	#diffuse map
				current.textures["Diffuse"] = split[1]
				self.CopyTexture(split[1])
			elif split[0] == "map_Ks":	#specular map
				current.textures["Specular"] = split[1]
				self.CopyTexture(split[1])
			elif split[0] == "map_Ns":	#specular highlight map
				current.textures["Highlight"] = split[1]
				self.CopyTexture(split[1])
			elif split[0] == "map_d":	#alpha texture map
				current.textures["Alpha"] = split[1]
				self.CopyTexture(split[1])
			elif split[0] == "map_bump" or split[0] == "bump":	#bump map
				current.textures["Bump"] = split[1]
				self.CopyTexture(split[1])
			elif split[0] == "disp":	#displacement map
				current.textures["Displacement"] = split[1]
				self.CopyTexture(split[1])
			elif split[0] == "decal":	#stencil decaul map
				current.textures["Decal"] = split[1]
				self.CopyTexture(split[1])

		#write the current material
		self.WriteMaterial(current)
		#add it to the list
		self.materials[current.id] = current

	def WriteMaterial(self, mat):
		#open the file to write in the materials folder
		f = open(self.paths.PlatformURL(self.paths.Path("assets") + "/Materials/" + mat.id + ".material"), "w")
		#write the material to the file
		mat.WriteToFile(f)
		#close
		f.close()

	def GetMaterial(self, id):
		return self.materials[id]

	#copies a texture to the textures folder
	def CopyTexture(self, tex):
		#check if file exists
		if os.path.isfile(tex):
			#get the name of the texture
			head, tail = os.path.split(tex)

			#get the destination directory
			dest = self.paths.PlatformURL(self.paths.Path("assets") + "/Textures/" + tail)

			#copy over texture
			shutil.copy2(tex, dest)
		else:
			print("Could not find texture: " + tex)

	def WriteAssetExcerpt(self, out, name):
		''' Material example
		<asset type="MaterialAsset" id="lizardman_material">
			<path>Assets/Materials/lizardman.material</path>
		</asset>
		'''

		#write Materials
		out.write("<!-- Materials -->\n")
		for k,v in self.materials.items():
			out.write("<asset type=\"MaterialAsset\" id=\""+v.id+"\">\n")
			out.write("\t<path>Assets/Materials/"+v.id+".material</path>\n")
			out.write("</asset>\n")

		''' Texture example
		<asset type="TextureAsset" id="LizardManDiffuse">
			<path>Assets/Textures/Lizardman_col.png</path>
			<format>rgba</format>
			<type>2d</type>
		</asset>
		'''

		#construct textures
		textures = dict()

		#for k,v in self.materials.items():

		#write textures
		out.write("<!-- Textures -->\n")
		for k,v in self.materials.items():
			out.write("<asset type=\"TextureAsset\" id=\""+v.id+"\">\n")
			out.write("\t<path>Assets/Materials/"+v.id+".material\n")
			out.write("</asset>\n")
		


