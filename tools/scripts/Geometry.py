import sys, getopt, struct
from array import array
from Paths import *
from objmaterial import *

#structure to hold a 3D point (x,y,z) 
class Point:
	def __init__(self,x,y,z):
		self.x = x
		self.y = y
		self.z = z

	def __sub__(self, other):
		return Point(self.x - other.x, self.y - other.y, self.z - other.z)
		
	def __mul__(self, other):
		return Point(self.x * other, self.y * other, self.z * other)
		
#structure holding the uv coordinates of a texture
class TextureUV:
	def __init__(self, u, v):
		self.u = u
		self.v = v
		
	def __sub__(self, other):
		return TextureUV(self.u - other.u, self.v - other.v)
		
#structure holding the x,y,z coordinate of a normal
class Normal:
	def __init__(self, x,y,z):
		self.x = x
		self.y = y
		self.z = z

#vector for colors
class Colour:
	def __init__(self, r,g,b,a):
		self.r = r
		self.g = g
		self.b = b
		self.a = a

#structure to hold the position, normal and uv coordinate at a point
class Vertex:
	def __init__(self, point, uv, norm):
		self.point = point
		self.uv = uv
		self.normal = norm
		self.tangent = Point(0,0,0)
		self.binormal = Point(0,0,0)
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
	def ConstructIndices(self, o_verts):

		for face in self.faces:
			#calculate the edge  directions
			deltaPos1 = face.v2.point - face.v1.point
			deltaPos2 = face.v3.point - face.v1.point
			
			#calculate the uv directions
			deltaUV1 = face.v2.uv - face.v1.uv
			deltaUV2 = face.v3.uv - face.v1.uv
			
			#compute the tangent and binormals
			val = (deltaUV1.u * deltaUV2.v - deltaUV1.v * deltaUV2.u)

			#prevent division by 0
			r = 1.0
			if val != 0:
				r = 1.0 / val

			tangent = (deltaPos1 * deltaUV2.v - deltaPos2 * deltaUV1.v) * r
			binormal = (deltaPos2 * deltaUV1.u - deltaPos1 * deltaUV2.u) * r
			
			#Set the face tangents and binormals
			face.v1.tangent = face.v2.tangent = face.v3.tangent = tangent
			face.v1.binormal = face.v2.binormal = face.v3.binormal = binormal
			
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

	def WriteExcerpt(self, out, name, meshes, materials):
		#example
		'''
		<component type="MeshRenderer">
			<mesh>LizardMan</mesh>
		</component>
		<component type="Material">
			<shader>DiffuseShader</shader>
			<material>lizardman_material</material>
			<texture uniform="SimpleTexture">LizardManDiffuse</texture>
		</component>
		'''

		#mesh renderer
		out.write("\t\t<component type=\"MeshRenderer\">\n")
		out.write("\t\t\t<indices>" + str(meshes.index(self)) + "</indices>\n")
		out.write("\t\t\t<mesh>" + self.id + "</mesh>\n")
		out.write("\t\t</component>\n")

		#material
		out.write("\t\t<component type=\"Material\">\n")
		out.write("\t\t\t<shader>DiffuseShader</shader>\n")
		out.write("\t\t\t<material>" + self.material + "</material>\n")

		#write material textures
		this_material = materials.GetMaterial(self.material)

		if this_material:
			textures = this_material.GetTextures()
			for k,v in textures.items():
				out.write("\t\t\t<texture uniform=\"" + str(k) + "\">"+name+"_"+str(k)+"_Texture</texture>\n")
		else:
			print("Could not find material for " + self.id)

		#end of material
		out.write("\t\t</component>\n")