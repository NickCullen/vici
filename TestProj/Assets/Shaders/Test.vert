#version 330 core

in vec3 aVertex;
in vec3 aUV;
in vec3 aNormal;

uniform mat4 uMVP;
uniform mat4 uNormalMatrix;

void main() 
{ 
    gl_Position = uMVP * vec4(aVertex,1.0);
}	