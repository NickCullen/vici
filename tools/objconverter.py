#!/usr/bin/python

#for args
import sys, getopt, struct
from array import array

#the file to open
f = {}

#the file to write to
out = {}

#through faces we can access all possible data
faces = []

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

#called when obj file loaded
def ReadObj():
	#internal lists
	points = []		#list of Points
	uvs = []		#list of TextureUVs
	normals = []	#list of Normals

	#list of vertices
	vertices = []

	for line in f:
		#skip # lines
		if line.startswith('#'): continue	

		#split with spaces
		values = line.split()

		#skip if nothing
		if not values: continue

		#if we are dealing with a vert
		if values[0] == "v": 
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

			#create the three verts that make up this face
			v1 = Vertex(points[int(v1_data[0])-1], uvs[int(v1_data[1])-1], normals[int(v1_data[2])-1])
			v2 = Vertex(points[int(v2_data[0])-1], uvs[int(v2_data[1])-1], normals[int(v2_data[2])-1])
			v3 = Vertex(points[int(v3_data[0])-1], uvs[int(v3_data[1])-1], normals[int(v3_data[2])-1])

			#append this face to the faces list
			faces.append(Face(v1,v2,v3))
		#else - not supported
		else: continue

	#print counts
	print("obj Verts = " + str(len(points)))
	print("obj UVs = " + str(len(uvs)))
	print("obj Norms = " + str(len(normals)))
	print("obj face count = " +str(len(faces)))
	print("\n")

#call when OBJ file is loaded to construct the Vici engine friendly mesh file
def ConstructMesh():
	#the mesh construct
	m = dict(verts = [],uvs = [],norms = [],indices = [])

	#array friendly vertices
	o_verts = []

	index = 0

	#convert into friendly arrays
	for face in faces:
		
		#first vertex
		if not face.v1 in o_verts:
			o_verts.append(face.v1)
			m['indices'].append(index)
			index+=1
		else:
			m['indices'].append(o_verts.index(face.v1))

		#second vertex
		if not face.v2 in o_verts:
			o_verts.append(face.v2)
			m['indices'].append(index)
			index+=1
		else:
			m['indices'].append(o_verts.index(face.v2))

		#third vertex
		if not face.v3 in o_verts:
			o_verts.append(face.v3)
			m['indices'].append(index)
			index+=1
		else:
			m['indices'].append(o_verts.index(face.v3))

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

	#return mesh construct
	return m

	

#called after mesh file has been constructed
def WriteMesh(m):
	print("Writing mesh")

	#print count
	print("Ended up with: ")
	print("Verts = " + str(len(m['verts'])/3))
	print("UVs = " + str(len(m['uvs'])/2))
	print("Norms = " + str(len(m['norms'])/3))
	print("Indices = " + str(len(m['indices'])))

	#check if open
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

		#write len of indices array
		out.write(struct.pack('i',(int(len(m['indices'])))))
		#write indices
		array("i",m['indices']).tofile(out)
		

if __name__ == "__main__":
	
	#open
	f = open(sys.argv[1],"r")
	out = open(sys.argv[2],"wb")

	print("Reading obj file")
	#read obj
	ReadObj()

	#construct mesh
	m = ConstructMesh()

	#write .mesh file
	WriteMesh(m)

	#close files
	f.close();
	out.close()

	out = open(sys.argv[2],"rb")
	length = struct.unpack('i', out.read(4))[0]
	verts = array('f')
	verts.fromfile(out,length)

	print(length)
	print(verts)
	out.close()
