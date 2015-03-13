#version 120

varying vec3 modelVertex;
varying vec3 vertexEye;
varying vec3 normal;
varying vec2 uv;

const int MAX_LIGHTS = 8;

struct Material
{
	vec4 ka;
	vec4 kd;
	vec4 ks;
	float ns;	
	float d;
};

struct Light
{
	int type;
	float constantAttenuation;
	float linearAttenuation;
	float quadraticAttenuation;	
	vec3 position;
	vec3 direction;
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
};

uniform Light uLights[MAX_LIGHTS];
uniform int uLightCount;

uniform Material uMaterial;
uniform sampler2D uDiffuse;
uniform vec4 uSceneAmbience;

void DirectionalLight(const in Light light, in vec3 eye, inout vec4 amb, inout vec4 diff, inout vec4 spec)
{
	float nDotVP;	//normal . light direction
	float nDotHV;	//normal . light half vector
	float pf;		//power factor

	nDotVP = max(0.0, dot(normal, -light.direction));

	vec3 halfVec = normalize(-light.direction + eye);

	nDotHV = max(0.0, dot(normal, halfVec));

	if(nDotVP == 0.0)
		pf = 0.0;
	else
		pf = pow(nDotHV, uMaterial.ns);

	amb += light.ambient;
	diff += light.diffuse * nDotVP;
	spec += light.specular * pf;	
}

void PointLight(const in Light light, in vec3 eye, inout vec4 amb, inout vec4 diff, inout vec4 spec)
{
	float nDotVP;		//normal . light direction
	float nDotHV;		//normal . light half vector
	float pf;			//power factor
	float attenuation;	//computed attenuation factor
	float d;			//distance from surface to light source
	vec3 VP;			//direction from surface to light position
	vec3 halfVector;	//direction of maximum highlights

	//compute vector from surface to light position
	VP = light.position - modelVertex;

	//compute distance between surface and light position
	d = length(VP);

	//normalize the vector from surface to light position
	VP = normalize(VP);
	
	//compute attenuation
	attenuation = 1.0 / (light.constantAttenuation +
					(light.linearAttenuation * d) +
					(light.quadraticAttenuation * d * d));

	halfVector = normalize(VP + vertexEye);
			
	nDotVP = max(0.0, dot(normal, VP));
	nDotHV = max(0.0, dot(normal, halfVector));

	if(nDotVP == 0.0)
		pf = 0.0;
	else
	{
		pf = pow(nDotHV, uMaterial.ns);

		amb += light.ambient * attenuation;
		diff += light.diffuse * nDotVP * attenuation;
		spec += light.specular * pf * attenuation;
	}
	
}

void main()
{
	vec3 eye = -normalize(vertexEye);

	vec4 ambient = vec4(0,0,0,0);
	vec4 diffuse = vec4(0,0,0,0);
	vec4 specular = vec4(0,0,0,0);
	for(int i =0 ; i < uLightCount; i++)
	{	
		//directional
		if(uLights[i].type == 0)
			DirectionalLight(uLights[i], eye, ambient, diffuse, specular);
		//point
		else if(uLights[i].type == 1)
			PointLight(uLights[i], eye, ambient, diffuse, specular);
	}

	gl_FragColor = uSceneAmbience * ambient * uMaterial.ka + diffuse * uMaterial.kd + specular * uMaterial.ks;
}