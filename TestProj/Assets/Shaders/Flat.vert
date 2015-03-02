#version 120

attribute vec3 aVertex;
attribute vec2 aUV;
attribute vec3 aNormal;

uniform mat4 uMVP;
uniform mat4 uMV;
uniform mat4 uModelMatrix;
uniform mat3 uNormalMatrix;

varying vec3 modelVertex;
varying vec3 vertexEye;
varying vec3 normal;
varying vec2 uv;

void main() 
{ 
	modelVertex = vec3(uModelMatrix * vec4(aVertex,1.0));

    gl_Position = uMVP * vec4(aVertex,1.0);
    normal = normalize(uNormalMatrix * aNormal);
    uv = aUV;

    //eye space
    vertexEye = vec3(uMV * vec4(aVertex, 1.0));
}	