#version 120

varying vec3 normal;
varying vec2 uv;

struct Material
{
	vec4 ka;
	vec4 kd;
	vec4 ks;
	float ns;	
	float d;
};

uniform Material uMaterial;
uniform vec4 uSceneAmbience;

void main()
{
	float intensity = max(0, dot(normal, vec3(0,0.8,0.2)));

	//ambience
	vec4 amb = uSceneAmbience * uMaterial.ka;

	//diffuse
	vec4 diff = intensity * uMaterial.kd;

	//final contrbution
	gl_FragColor = amb + diff;
}