#version 120

varying vec3 normal;
varying vec2 uv;

struct Material
{
	vec4 ks;
	vec4 ns;
}

uniform sampler2D uAmbient;
uniform sampler2D uDiffuse;

uniform Material uMaterial;

uniform vec3 uSceneAmbience;

void main()
{
	float intensity = max(0, dot(normal, vec3(0,0.8,0.2)));

	vec4 amb = uSceneAmbience * texture2D(uAmbient, uv);
	vec4 diff = intensity * texture2D(UDiffuse, uv);

	gl_FragColor = amb + diff;
}