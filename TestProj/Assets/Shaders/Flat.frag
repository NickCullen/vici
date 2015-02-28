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

const int MAX_LIGHTS = 8;

struct Light
{
	int type;
	float attenuation;	
	vec4 position;
	vec4 direction;
};

uniform Light uLights[MAX_LIGHTS];
uniform int uLightCount;

uniform Material uMaterial;
uniform vec4 uSceneAmbience;

void main()
{
	float intensity = max(0, dot(normal, vec3(uLights[0].direction)));

	//ambience
	vec4 amb = uSceneAmbience * uMaterial.ka;

	//diffuse
	vec4 diff = intensity * uMaterial.kd;

	gl_FragColor = amb + diff;
}