#version 120

attribute vec3 aVertex;

uniform mat4 uModelViewProjectionMatrix;

void main() 
{ 
    gl_Position = uModelViewProjectionMatrix * vec4(aVertex,1.0);
}	