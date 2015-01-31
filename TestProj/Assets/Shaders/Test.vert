#version 150

attribute vec3 aVertex;
attribute vec3 aUV;
attribute vec3 aNormal;

uniform mat4 uMVP;
uniform mat3 uNormalMatrix;

varying out vec3 normal;

void main() 
{ 
    gl_Position = uMVP * vec4(aVertex,1.0);
    normal = uNormalMatrix * aNormal;
}	