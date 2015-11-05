#!$VICI_PYTHON

#for args
import sys, getopt, struct
from array import array
from Paths import *
from objmaterial import *
from Geometry import *

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

#the material class containing all the materials from the obj material file
materials = []

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
		if values[0] == "o" or values[0] == "g":
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
			global materials
			materials = ObjMaterial(values[1])
			print("Set Material File: " + values[1])
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
	m = dict(verts = [], uvs = [], norms = [], tangents = [], binormal = [])

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
		m['tangents'].append(v.tangent.x)
		m['tangents'].append(v.tangent.y)
		m['tangents'].append(v.tangent.z)
		m['binormal'].append(v.binormal.x)
		m['binormal'].append(v.binormal.y)
		m['binormal'].append(v.binormal.z)
		
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
		
		#write len of tangents array
		out.write(struct.pack('i',(int(len(m['tangents'])/3))))
		#write norms
		array("f",m['tangents']).tofile(out)
		
		#write len of binorms array
		out.write(struct.pack('i',(int(len(m['binormal'])/3))))
		#write norms
		array("f",m['binormal']).tofile(out)

def WriteExcerpt(out, name):
	#example
	'''
	<gameobject id="Object" indestructable="false" enabled="true" layer="0">
		<transform>
			<position>0 0 0</position>
			<rotation>0 0 0</rotation>
			<scale>1 1 1</scale>
		</transform>
	</gameobject>
	'''

	out.write("<gameobject id=\"" + name + "\" indestructable=\"false\" enabled=\"true\" layer=\"0\">\n")
	for m in meshes:
		out.write("\t<gameobject id=\"" + m.id + "\" indestructable=\"false\" enabled=\"true\" layer=\"0\">\n")
		out.write("\t\t<transform>\n")
		out.write("\t\t\t<position>0 0 0</position>\n")
		out.write("\t\t\t<rotation>0 0 0</rotation>\n")
		out.write("\t\t\t<scale>1 1 1</scale>\n")
		out.write("\t\t</transform>\n")

		#write the mesh
		m.WriteExcerpt(out, name, meshes, materials)

		out.write("\t</gameobject>\n")
	out.write("</gameobject>\n")

def WriteAssetExcerpt(out, name):
	'''Mesh example
	<asset type="MeshAsset" id="LizardMan">
		<path>Assets/Models/lizardman.mesh</path>
	</asset>
	'''

	#write mesh asset
	out.write("<!-- Mesh -->\n")
	out.write("<asset type=\"MeshAsset\" id=\"" + name + "\">\n")
	out.write("\t<path>Assets/Models/"+name+".mesh\n")
	out.write("</asset>\n")

	materials.WriteAssetExcerpt(out, name)

if __name__ == "__main__":
	paths = Paths()

	#open obj file
	f = open(paths.PlatformURL(paths.Path("tools") + "/" + sys.argv[1]),"r")

	print("Reading OBJ File")
	#read obj
	ReadObj()

	#the output mesh file
	out_path = paths.PlatformURL(paths.Path("assets") + "/Models/" + sys.argv[2] + ".mesh")
	out = open(out_path,"wb")

	print("Constructing mesh filter indices")
	#construct mesh indices (thus creating opengl friendly arrays)
	for m in meshes:
		m.ConstructIndices(o_verts)

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

	print("Outputting Asset Excerpt_assets.xml")
	#output asset excerpt
	xml = open("Excerpt_assets.xml","w")
	WriteAssetExcerpt(xml, sys.argv[2])
	xml.close()

	#close file
	f.close()
	out.close()