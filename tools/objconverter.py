#!/usr/bin/python

#for args
import sys, getopt, struct
from array import array
from Paths import *
from objmaterial import *

#the file to open
f = {}

#list of points, uvs and norms
points = []
uvs = []
normals = []

#opengl array friendly vertices
o_verts = []

#list of mesh objects
meshes = []

#structure to hold a 3D point (x,y,z) 
class Point:
	def __init__(self,x,y,z):
		self.x = x
		self.y = y
		self.z = z

#structure holding the uv coordinates of a texture
class TextureUV:
	def __init__(self, u, v):
		self.u = u
		self.v = v

#structure holding the x,y,z coordinate of a normal
class Normal:
	def __init__(self, x,y,z):
		self.x = x
		self.y = y
		self.z = z

#structure to hold the position, normal and uv coordinate at a point
class Vertex:
	def __init__(self, point, uv, norm):
		self.point = point
		self.uv = uv
		self.normal = norm

	def __eq__(self, other):
		if isinstance(other, Vertex):
			return (self.point == other.point and self.uv == other.uv and self.normal == other.normal)
		return NotImplemented

#structure to hold the three vertices (3 Vertex classes) 
#which make up this face
class Face:
	def __init__(self, v1, v2, v3):
		self.v1 = v1
		self.v2 = v2
		self.v3 = v3

#mesh file to hold a list of faces
class Mesh:
	def __init__(self, id):
		self.id = id

		self.faces = [] 	#list of faces (vertex, vertex, vertex)

		#the indices into the arrays
		self.indices = []

	#constructs the indices of the mesh (will also create the opengl friend arrays)
	def ConstructIndices(self):

		#convert into friendly arrays
		for face in self.faces:
			
			#first vertex
			if not face.v1 in o_verts:
				o_verts.append(face.v1)
				self.indices.append(len(o_verts)-1)
			else:
				self.indices.append(o_verts.index(face.v1))

			#second vertex
			if not face.v2 in o_verts:
				o_verts.append(face.v2)
				self.indices.append(len(o_verts)-1)
			else:
				self.indices.append(o_verts.index(face.v2))

			#third vertex
			if not face.v3 in o_verts:
				o_verts.append(face.v3)
				self.indices.append(len(o_verts)-1)
			else:
				self.indices.append(o_verts.index(face.v3))

	#write indices to file
	def WriteIndices(self, out):
		#write len of indices array
		out.write(struct.pack('i',(int(len(self.indices)))))
		#write indices
		array("i",self.indices).tofile(out)

	def WriteExcerpt(self, out, name):
		#example
		'''
		<component type="MeshRenderer">

		</component>
		<component type="Mesh">
			<mesh>Assets/Models/monkey.mesh</mesh>
		</component>
		<component type="Material">
			<vert>Assets/Shaders/Test.vert</vert>
			<frag>Assets/Shaders/Test.frag</frag>
			<texture format="rgb" id="SimpleTexture">
				<path>Assets/Textures/Thatched.jpg</path>
				<type>2d</type>
			</texture>
			<texture format="rgba" id="RedTexture">
				<path>Assets/Textures/red.png</path>
				<type>2d</type>
			</texture>
		</component>
		'''
		out.write("\t<component type=\"MeshRenderer\">\n")
		out.write("\t\t<indices>" + str(meshes.index(self)) + "</indices>\n")
		out.write("\t</component>\n")
		out.write("\t<component type=\"Mesh\">\n")
		out.write("\t\t<mesh>Assets/Models/"+name+".mesh</mesh>\n")
		out.write("\t</component>\n")
		out.write("\t<component type=\"Material\">\n")
		out.write("\t<vert>Assets/Shaders/Test.vert</vert>\n")
		out.write("\t<frag>Assets/Shaders/Test.frag</frag>\n")
		out.write("\t<texture format=\"rgb\" id=\"SimpleTexture\">\n")
		out.write("\t	<path>Assets/Textures/Thatched.jpg</path>\n")
		out.write("\t	<type>2d</type>\n")
		out.write("\t</texture>\n")
		out.write("\t<texture format=\"rgba\" id=\"RedTexture\">\n")
		out.write("\t	<path>Assets/Textures/red.png</path>\n")
		out.write("\t	<type>2d</type>\n")
		out.write("\t</texture>\n")
		out.write("\t</component>\n")

#called when obj file loaded
def ReadObj():
	#the current mesh
	current = 0

	#flag indicating if more than one material is being used 
	#on the current object. if this is the case we need to make 
	#a new object!
	material_used = 0


	for line in f:
		#skip # lines
		if line.startswith('#'): continue	

		#split with spaces
		values = line.split()

		#skip if nothing
		if not values: continue

		#creating a new mesh
		if values[0] == "o":
			#If there is already a current mesh add it to the meshes list
			if current != 0:
				meshes.append(current)

			#reset
			material_used = 0

			#create a new mesh
			current = Mesh(values[1])
		#if we are dealing with a vert
		elif values[0] == "v": 
			#add a point to the points list
			points.append(Point(float(values[1]), float(values[2]), float(values[3])))
		#texture coord
		elif values[0] == "vt": 
			#add a uv to the uv list
			uvs.append(TextureUV(float(values[1]), float(values[2])))
		#normal
		elif values[0] == "vn": 
			#add a normal to the normals list
			normals.append(Normal(float(values[1]), float(values[2]), float(values[3])))
		#if we get to f (the faces) we need to break out
		elif values[0] == "f":
			#get the index into the arrays (note this are in string form)
			v1_data = values[1].split("/")
			v2_data = values[2].split("/")
			v3_data = values[3].split("/")

			try:
				#create the three verts that make up this face
				v1 = Vertex(points[int(v1_data[0])-1], uvs[int(v1_data[1])-1], normals[int(v1_data[2])-1])
			except:
				print("Could not create vertex for face " + values[1])
				sys.exit()
			try:
				v2 = Vertex(points[int(v2_data[0])-1], uvs[int(v2_data[1])-1], normals[int(v2_data[2])-1])
			except:
				print("Could not create vertex for face " + values[2])
				sys.exit()
			try:
				v3 = Vertex(points[int(v3_data[0])-1], uvs[int(v3_data[1])-1], normals[int(v3_data[2])-1])
			except:
				print("Could not create vertex for face " + values[3])
				sys.exit()
			

			#append this face to the faces list of the mesh
			current.faces.append(Face(v1,v2,v3))
		elif values[0] == "mtllib":
			#output the material file
			materials = ObjMaterial(values[1])
		elif values[0] == "usemtl":
			#check to see if a material has already been set
			#if so make a new mesh as 2 materials cannot be 
			#assigned to one mesh!
			if material_used == 1:
				meshes.append(current)	#add current to the list
				current = Mesh("Child") #create a new mesh

			#assign the material to the mesh
			current.material = values[1]

			#set true
			material_used = 1

		else: continue

	#write the last mesh
	if current != 0:
		meshes.append(current)

def WriteArrays(out):
	m = dict(verts = [], uvs = [], norms = [])

	#add them to the mesh construct
	for v in o_verts:
		m['verts'].append(v.point.x)
		m['verts'].append(v.point.y)
		m['verts'].append(v.point.z)
		m['uvs'].append(v.uv.u)
		m['uvs'].append(v.uv.v)
		m['norms'].append(v.normal.x)
		m['norms'].append(v.normal.y)
		m['norms'].append(v.normal.z)

	if(out):
		#write len of vert array
		out.write(struct.pack('i',(int(len(m['verts'])/3))))
		#write verts
		array("f",m['verts']).tofile(out)

		#write len of uv array
		out.write(struct.pack('i',(int(len(m['uvs'])/2))))
		#write uvs
		array("f",m['uvs']).tofile(out)

		#write len of norms array
		out.write(struct.pack('i',(int(len(m['norms'])/3))))
		#write norms
		array("f",m['norms']).tofile(out)

def WriteExcerpt(out, name):
	#example
	'''
	<gameobject id="Object" indestructable="false" enabled="true" layer="0">
		<transform>
			<position>0 0 -15</position>
			<rotation>0 0 0</rotation>
			<scale>1 1 1</scale>
		</transform>
		
		... mesh excerpt here ...

	</gameobject>
	'''

	out.write("<gameobject id=\"" + name + "\" indestructable=\"false\" enabled=\"true\" layer=\"0\">\n")
	for m in meshes:
		out.write("<gameobject id=\"" + m.id + "\" indestructable=\"false\" enabled=\"true\" layer=\"0\">\n")
		out.write("\t<transform>\n")
		out.write("\t\t<position>0 0 -15</position>\n")
		out.write("\t\t<rotation>0 0 0</rotation>\n")
		out.write("\t\t<scale>1 1 1</scale>\n")
		out.write("\t</transform>\n")

		#write the mesh
		m.WriteExcerpt(out, name)

		out.write("</gameobject>")
	out.write("</gameobject>")

if __name__ == "__main__":
	
	#open obj file
	f = open(sys.argv[1],"r")

	print("Reading OBJ File")
	#read obj
	ReadObj()

	#the output mesh file
	paths = Paths()
	out_path = paths.PlatformURL(paths.Path("assets") + "/Models/" + sys.argv[2] + ".mesh")
	out = open(out_path,"wb")

	print("Constructing mesh filter indices")
	#construct mesh indices (thus creating opengl friendly arrays)
	for m in meshes:
		m.ConstructIndices()

	print("Writing Vertex Arrays to file")
	#write vertex arrays
	WriteArrays(out)

	print("A total of " + str(len(meshes)) + " Meshes contstructed")
	#write ehow many meshes (num of index arrays) there are
	out.write(struct.pack('i', int(len(meshes))))

	print("Writing Indices to file")
	#write mesh indices per mesh
	for m in meshes:
		m.WriteIndices(out)

	print("Outputting Excerpt.xml")
	#output excerpt
	xml = open("Excerpt.xml","w")
	WriteExcerpt(xml, sys.argv[2])
	xml.close()
	#close file
	f.close()
	out.close()