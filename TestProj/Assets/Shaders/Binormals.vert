#version 120

attribute vec3 aVertex;
attribute vec3 aTangent;
attribute vec3 aBinormal;

uniform mat4 uModelViewProjectionMatrix;

varying vec3 tangent;
varying vec3 binormal;

void main() 
{ 
    gl_Position = uModelViewProjectionMatrix * vec4(aVertex.xyz,1.0);

    tangent = aTangent;
    binormal = aBinormal;
}	