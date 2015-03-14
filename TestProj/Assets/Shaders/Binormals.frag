#version 120

varying vec3 tangent;
varying vec3 binormal;

void main()
{
	gl_FragColor = vec4(binormal,1);
}