#version 120

attribute vec3 aVertex;
attribute vec3 aUV;
attribute vec3 aNormal;

uniform mat4 uMVP;
uniform mat4 uNormalMatrix;

void main() 
{ 
    gl_Position = uMVP * vec4(aVertex,1.0);

}	