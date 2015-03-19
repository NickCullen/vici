#version 120

#include common

varying vec3 normal;
varying vec2 uv;

uniform sampler2D uDiffuse;

void main()
{
	gl_FragColor = texture2D(uDiffuse, vec2(uv.x, 1.0 - uv.y));
}