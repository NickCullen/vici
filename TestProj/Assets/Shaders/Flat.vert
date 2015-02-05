#version 120

attribute vec3 aVertex;
attribute vec2 aUV;
attribute vec3 aNormal;

uniform mat4 uMVP;
uniform mat3 uNormalMatrix;

varying vec3 normal;
varying vec2 uv;

void main() 
{ 
    gl_Position = uMVP * vec4(aVertex,1.0);
    normal = uNormalMatrix * aNormal;
    uv = aUV;
}	